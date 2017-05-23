/****************************************/
/*  Bas Janssen 			                  */
/*  Dimitri Waard                       */
/*  Fontys 2017                         */
/****************************************/



#include <ros/ros.h>
#include <ros/package.h>
#include <boost/thread.hpp>
#include <boost/foreach.hpp>
#define forEach BOOST_FOREACH

//Include the simple_action_client
#include <actionlib/client/simple_action_client.h>
//Include the msg definitions for movebase.
#include <move_base_msgs/MoveBaseAction.h>

#include <move_base/move_base.h>

#include <nav_msgs/GetPlan.h>

#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/Pose.h>

//Maybe revise msg to fit to all commands, not just pickup
#include <multirob_test/cmdPickup.h>
#include <multirob_test/r2rpickupresponse.h>

//The headers to access files.
#include <iostream>
#include <fstream>

#include <math.h>

#include <tf/transform_listener.h>

tf::TransformListener* listener = NULL;

//Define a struct to keep the pickup commands for the robot
struct robotPickupCommand {
  std::string source;
  std::string destination;
  std::string product;
  int amount;
  bool done;
};

//Keep a records of the previous/active pickup command
volatile robotPickupCommand previousPickupCommand;

std::vector<multirob_test::r2rpickupresponse> robotResponses;

volatile bool RobotHasCommand = false;

std::vector<std::string> dockNames;
//Design a struct to store the data for a location, then build a vector with this struct.
std::vector<geometry_msgs::Pose> dockLocations;

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

ros::Publisher robotComms; //This would not be thread safe

std::string robotName;
int numberOfRobots;
int storageSize;
bool sim;
int productsToCarry;
int productsLoaded;

bool sortByDistance(multirob_test::r2rpickupresponse response1, multirob_test::r2rpickupresponse response2)
{
  return response1.distance < response2.distance;
}

//Function to send the robot to a location. Pass the locatation as an x,y coordinate and a rotation in quaternion notation.
void moveToLocation(geometry_msgs::Pose pose)
{
  //Create an actionlib client for move_base. Using this client a goal can be assigned to move_base.
  MoveBaseClient ac("move_base", true);
  while(!ac.waitForServer(ros::Duration(5.0)))
  {
    ROS_INFO("Waiting for action server");
  }

  //Create and assign the goal.
  move_base_msgs::MoveBaseGoal goal;

  goal.target_pose.header.frame_id = "/map";
  goal.target_pose.header.stamp = ros::Time::now();

  goal.target_pose.pose = pose;

  if(sim)
  {
    //Send the goal to move_base
    ac.sendGoal(goal);
    //Wait for the action to complete.
    ac.waitForResult();
  }
}

void executeCommand(std::string source, std::string destination)
{
  ROS_INFO("%s will execute the command.", robotName.c_str());
  RobotHasCommand = true;
  //numberOfRobots = numberOfRobots -1;
  //ROS_INFO("numberOfRobots before executing command %u",numberOfRobots);
  for(int i=0; i<dockNames.size(); i++)
  {
    if(source.compare(dockNames[i]) == 0)
    {
      moveToLocation(dockLocations[i]);
      break;
    }
  }
  
  productsLoaded = productsToCarry;
  ROS_INFO("%s productsLoaded %i", robotName.c_str(), productsLoaded);
  
  for(int i=0; i<dockNames.size(); i++)
  {
    if(destination.compare(dockNames[i]) == 0)
    {
      moveToLocation(dockLocations[i]);
      break;
    }
  }
  
  productsLoaded = 0;
  ROS_INFO("%s productsLoaded %i", robotName.c_str(), productsLoaded);
  RobotHasCommand = false;
  //numberOfRobots = numberOfRobots + 1;
  //ROS_INFO("numberOfRobots after executing command %u",numberOfRobots);
}

//Function to calculate the disatance from the robot to a given target location, in the x,y and quaternion notation. Returns a float representing the lenght of the path.\
//TODO the distance to the goal is sometimes closes because the robot isn't sure of its position, this is a problem on small scale but on big scale this would not be a problem. 
float calcGoalDistance(geometry_msgs::Pose pose)
{
  //Create a nodehandle and attach the make_plan client to the node.
  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<nav_msgs::GetPlan>("move_base/make_plan");
  nav_msgs::GetPlan plan;

  //Try to transform the base_footprint of the robot to the map. This represents the location of the robot in the map.
  tf::StampedTransform transform;
  bool canTransform = true;
  std::string footprint = "/" + robotName + "/base_footprint";
  try{
    listener->lookupTransform(footprint, "/map", ros::Time(0), transform);
  }
  catch (tf::TransformException ex){
    ROS_ERROR("%s",ex.what());
    ros::Duration(1.0).sleep();
    canTransform = false;
  }

  //If a transformation between the robot and the map can be found, request a path between the robot and the assigned goal. The goal has to be a location in map coordinate space.
  if(canTransform)
  {
    plan.request.start.header.frame_id = "/map";
    plan.request.start.header.stamp = ros::Time::now();
    plan.request.start.pose.position.x = transform.getOrigin().getX();
    plan.request.start.pose.position.y = transform.getOrigin().getY();

    geometry_msgs::Quaternion quat;
    tf::quaternionTFToMsg(transform.getRotation(), quat); 
    plan.request.start.pose.orientation = quat;
    

    plan.request.goal.header.frame_id = "/map";
    plan.request.goal.header.stamp = ros::Time::now();
    plan.request.goal.pose = pose;

    plan.request.tolerance = 0.10;

    if (client.call(plan))
    {
      //Loop through all poses in the path, and calculate the distances between each set of poses. Add these distances to get the full path lenght.
      if(plan.response.plan.poses.size())
      {
        ROS_INFO("Path has %lu points.", plan.response.plan.poses.size());
        float pathLenght = 0;
        for (int i=0; i<plan.response.plan.poses.size(); i++)
        {
          float xP = plan.response.plan.poses[i].pose.position.x - plan.response.plan.poses[i+1].pose.position.x;
          float yP = plan.response.plan.poses[i].pose.position.y - plan.response.plan.poses[i+1].pose.position.y;
          pathLenght = pathLenght + sqrtf(pow(xP, 2.0) + pow(yP, 2.0));
        }
        if(pathLenght < 1000 && pathLenght >= 0)
        {
          return pathLenght;
        }
        else
        {
          ROS_INFO("Invalid path lenght.");
          return -1;
        }
	//return pathLenght;
      }
      else
      {
        ROS_INFO("No path lenght.");
        return -1;
      }
    }
    else
    {
      ROS_INFO("Client call failed.");
      return -1;
    }
  }
  else
  {
    ROS_INFO("No tf available.");
    return -1;
  }
}

//Function will check the inventory of the robot and will give as result the storageused and the amount left 
std::vector<int> checkInventory(int amount)
{
  //Normaly we would check the I/O's representing the loaded products, but we currently have a simulation.
  std::vector<int> result = {0,0}; //StorageSizeUsed, Amount
  int storageSizeUsed = 0;
  if(sim)
  {
    if(storageSize < amount)
    {
      storageSizeUsed = storageSize;
      amount = amount - storageSizeUsed;
      //ROS_INFO("storageSizeUsed %u", storageSizeUsed);
      //ROS_INFO("Amountleft1 %u", amount);
      result[0] = storageSizeUsed;
      result[1] = amount;
      return result;
    }
    if(storageSize >= amount)
    {
      storageSizeUsed = amount;
      amount = 0;
      //ROS_INFO("storageSizeUsed %u", storageSizeUsed);
      //ROS_INFO("Amountleft2 %u", amount);
      result[0] = storageSizeUsed;
      result[1] = amount;
      return result;
    }
  }
  else
  {
    return result;
  }
}

int sendToOtherRobots(multirob_test::r2rpickupresponse response)
{
  robotComms.publish(response);
}


void checkWithExisting(robotPickupCommand command)
{
  ROS_INFO("Robot had a command running already.");
  
  float distance;
  
  for(int i=0; i<5; i++)
  {
    if(command.source.compare(dockNames[i]) == 0)
    {
      distance = calcGoalDistance(dockLocations[i]);
      ROS_INFO("Robot %i :Distance to goal %s: %f", (robotName.at(robotName.size() - 1)) - 48, dockNames[i].c_str(), distance);
      break;
    }
    else
    {
      distance = -1;
    }
  }
  
  multirob_test::r2rpickupresponse response;
  response.robot = int(robotName.at(robotName.size() - 1)) - 48;
  response.pickup.source = command.source;
  response.pickup.destination = command.destination;
  response.pickup.amount = command.amount;
  
  response.canDo = false;
  response.distance = distance;
  response.space = 0;
  
  sendToOtherRobots(response);
}

void startNewCommand(robotPickupCommand command)
{
  ROS_INFO("executing new command.");
  
  float distance;
//Tell all other robots that the command can be executed by the this robot
  for(int i=0; i<5; i++)
  {
    if(command.source.compare(dockNames[i]) == 0)
    {
      distance = calcGoalDistance(dockLocations[i]);
      ROS_INFO("Robot %i :Distance to goal %s: %f", (robotName.at(robotName.size() - 1)) - 48, dockNames[i].c_str(), distance);
      break;
    }
    else
    {
      distance = -1;
    }
  }

  std::vector<int> space = checkInventory(command.amount);

  multirob_test::r2rpickupresponse response;
  response.robot = int(robotName.at(robotName.size() - 1)) - 48;
  response.pickup.source = command.source;
  response.pickup.destination = command.destination;
  response.pickup.amount = command.amount;
  if(distance != -1 && space[0] > 0)
  {
    response.canDo = true;
    response.distance = int(distance * 1000);
    response.space = space[0];
  }
  else
  {
    response.canDo = false;
    response.distance = distance;
    response.space = 0;
  }

  sendToOtherRobots(response);
}

//Change the checking to use a vector. Sort by a weight, e.g. distance, or space, or canDo
void responseReceived(multirob_test::r2rpickupresponse response)
{
  robotResponses.push_back(response);
  bool runCommand = false;

  //TODO If a robot is still executing a command while a new command is send, the robot can not calculate the distance between him and the goal. Therefore it will give a distance of -1. The program works like we want it to but for later application we need the robot to give a distance instead of -1.
  if(robotResponses.size() == numberOfRobots)
  {
    //Get rid of the robots who are unable to execute the command and put them in a new vector
    std::vector<multirob_test::r2rpickupresponse> robotResponsescanDo;
    for(int i=0; i<robotResponses.size(); i++)  
    {
      if (robotResponses[i].canDo)
      {
        robotResponsescanDo.push_back(robotResponses[i]);
      }
    }
    //Sort the vector values from low to high       
    std::sort(robotResponsescanDo.begin(), robotResponsescanDo.end(), sortByDistance);

/*    for(int i=0; i<robotResponsescanDo.size(); i++)
    {
      ROS_INFO("Robot %i distance to goal %d", robotResponsescanDo[i].robot, robotResponsescanDo[i].distance);
    }
  */  
    //Check how many robots are needed to transport the amount of products
    
    std::vector<int> Result = checkInventory(response.pickup.amount);
    //ROS_INFO("amountLeft %u", amountLeft);
    int limit = robotResponsescanDo.size();
    int amountLeft = Result[1];
    //ROS_INFO("amountleft %i", amountLeft);
    if (amountLeft <= 0)
    {
      if(robotResponsescanDo[0].robot == int(robotName.at(robotName.size() - 1) - 48))
      {
        productsToCarry = Result[0];
        ROS_INFO("%s productsToCarry %i",robotName.c_str(), productsToCarry);
        runCommand = true;
      }
    }    
    for(int i = 0; limit > 0 && amountLeft > 0 && response.canDo == true; i++)
    {
      if(robotResponsescanDo[i].robot == int(robotName.at(robotName.size() - 1) - 48))
      {
        if (i == 0)
        { 
          productsToCarry = storageSize;
          ROS_INFO("%s productsToCarry %i",robotName.c_str(), productsToCarry);          
        }
        if (i > 0)
        {
          std::vector<int> Result2 = checkInventory(amountLeft);
          amountLeft = Result2[1];
          productsToCarry = Result2[0];
          ROS_INFO("%s productsToCarry %i",robotName.c_str(), productsToCarry);
          //ROS_INFO("amountleft  %i",i, amountLeft);
        }
        runCommand = true;
        response.canDo = false;
      }
      else
      {
        if (i == 0)
        { 
          amountLeft = amountLeft;        
        }
        if (i > 0)
        {
          std::vector<int> Result2 = checkInventory(amountLeft);
          amountLeft = Result2[1];
          productsToCarry = Result2[0];
          //ROS_INFO("productsToCarry %i", productsToCarry);
          //ROS_INFO("amountleft  %i",i, amountLeft);
        }
      }
      limit = limit - 1;
    }
    if (limit <= 0 && amountLeft > 0)
    {
      ROS_INFO("!!!!!!!!!!!!!!!!!!!!!!!!!!Products left: %i!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!", amountLeft);
    }
    // If the robot got a go on the command they will execute it 
    if(runCommand)
    {
      boost::thread t{executeCommand, robotResponses[0].pickup.source, robotResponses[0].pickup.destination};
      ROS_INFO("Execute Command");
    }  
    robotResponses.clear();
    robotResponsescanDo.clear();
  }
  
}

//Callback function when a new command msg is received
void commandReceived(multirob_test::cmdPickup command)
{
  //Check if the robot is already executing a command
  //If true, go to the function checking the possibility of adding the command
  //If false, respond to the group, and start executing the command
  robotPickupCommand newCommand;

  newCommand.source = command.source;
  newCommand.destination = command.destination;
  newCommand.amount = command.amount;

  //Launch a new thread with these functions. @TODO Keep track of the amount of threads spun up. This can be as simple as a mutex to prevent a new thread from launching when the old one isn't finished yet.
  if(RobotHasCommand)
  {
    ROS_INFO("Go to Check");
    boost::thread t{checkWithExisting, newCommand};//, arg1, arg2}; //Add values to pass
    t.detach();
  }
  else
  {
    ROS_INFO("Go to NewCommand");
    boost::thread t{startNewCommand, newCommand};//, arg1, arg2}; //Add values to pass
  }
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "decision_logic");

  ros::NodeHandle node;
  ros::NodeHandle nh("~");

  ros::Subscriber pickup_command = node.subscribe("/pickup_command", 10, commandReceived);
  robotComms = node.advertise<multirob_test::r2rpickupresponse>( "/pickup_responses", 0 );
  ros::Subscriber pick_responses = node.subscribe("/pickup_responses", 10, responseReceived);

  listener = new(tf::TransformListener);

  if (node.hasParam("robot_name"))
  {
    node.getParam("robot_name", robotName);
  }
  else
  {
    robotName = "noName";
  }
  ROS_INFO("Robot name %s", robotName.c_str());

  if(nh.hasParam("sim"))
  {
    nh.getParam("sim", sim);
  }
  else
  {
    sim = false;
  }
  ROS_INFO("Simulation: %s", sim ? "true" : "false");

  node.getParam("robots_number", numberOfRobots);
  node.getParam("storage_size", storageSize);
  
  std::string packagePath = ros::package::getPath("multirob_test");
  std::string filePath = packagePath + "/locations/locations.txt";
  ROS_INFO("File path: %s", filePath.c_str());

  std::ifstream locationfile (filePath.c_str());
  
  if (locationfile.is_open()) 
  {
    std::string line;
    geometry_msgs::Pose pose;
    while ( getline (locationfile,line) )
    {
      std::vector<std::string> location;
      boost::split(location, line, boost::is_any_of("\t"));

      dockNames.push_back(location[0]);
      pose.position.x = std::stod(location[1]);
      pose.position.y = std::stod(location[2]);
      pose.orientation.x = std::stod(location[3]);
      pose.orientation.y = std::stod(location[4]);
      pose.orientation.z = std::stod(location[5]);
      pose.orientation.w = std::stod(location[6]);
      dockLocations.push_back(pose);
    }
    locationfile.close();
  }
  
  for(int i=0; i<dockNames.size(); i++)
  {
    ROS_INFO("Dock loaded: %s", dockNames[i].c_str());
  }

  ros::spin();

  return 0;

}
