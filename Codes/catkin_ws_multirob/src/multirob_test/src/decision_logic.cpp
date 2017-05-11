/****************************************/
/*  Bas Janssen 			*/
/*  Dimitri Waard                       */
/*  Fontys 2017                         */
/****************************************/



#include <ros/ros.h>
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

//Maybe revise msg to fit to all commands, not just pickup
#include <multirob_test/cmdPickup.h>
#include <multirob_test/r2rpickupresponse.h>

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

//volatile
multirob_test::r2rpickupresponse robotResponses[10];

volatile bool RobotHasCommand = false;

//Change this to be vectors std::vector<std::string> words1 {"the", "frogurt", "is", "also", "cursed"};
std::vector<std::string> dockNames {"A", "B", "C", "D", "E"};
//std::string dockNames[3] = {"A", "B", "C"};
//Design a struct to store the data for a location, then build a vector with this struct.
float dockLocations[5][6] = {{-5.162, -5.257, 0.000, 0.000, 0.998, -0.066}, {-3.219, -2.244, 0.000, -0.000, -0.607, 0.794}, {8.782, -5.734, -0.000, -0.000, 0.803, 0.595}, {6.000, 6.000, -0.000, -0.000, 0.803, 0.595}, {-6.000, 6.000, -0.000, -0.000, 0.803, 0.595}};

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

ros::Publisher robotComms; //This would not be thread safe

std::string robotName;
int numberOfRobots;
int storageSize;
bool sim;

//Function to send the robot to a location. Pass the locatation as an x,y coordinate and a rotation in quaternion notation.
void moveToLocation(float x, float y, float qx, float qy, float qz, float qw)
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

  goal.target_pose.pose.position.x = x;
  goal.target_pose.pose.position.y = y;

  goal.target_pose.pose.orientation.x = qx;
  goal.target_pose.pose.orientation.y = qy;
  goal.target_pose.pose.orientation.z = qz;
  goal.target_pose.pose.orientation.w = qw;

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
  ROS_INFO(" %s will execute the command.", robotName.c_str());
  RobotHasCommand = true;
  
  for(int i=0; i<5; i++)
  {
    if(source.compare(dockNames[i]) == 0)
    {
      moveToLocation(dockLocations[i][0], dockLocations[i][1], dockLocations[i][2], dockLocations[i][3], dockLocations[i][4], dockLocations[i][5]);
      break;
    }
  }
  for(int i=0; i<5; i++)
  {
    if(destination.compare(dockNames[i]) == 0)
    {
      moveToLocation(dockLocations[i][0], dockLocations[i][1], dockLocations[i][2], dockLocations[i][3], dockLocations[i][4], dockLocations[i][5]);
      break;
    }
  }
  RobotHasCommand = false;
}

//Function to calculate the disatance from the robot to a given target location, in the x,y and quaternion notation. Returns a float representing the lenght of the path.\
//TODO the distance to the goal is sometimes closes because the robot isn't sure of its position, this is a problem on small scale but on big scale this would not be a problem. 
float calcGoalDistance(float x, float y, float qx, float qy, float qz, float qw)
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
    plan.request.goal.pose.position.x = x;
    plan.request.goal.pose.position.y = y;
    plan.request.goal.pose.orientation.x = qx;
    plan.request.goal.pose.orientation.y = qy;
    plan.request.goal.pose.orientation.z = qz;
    plan.request.goal.pose.orientation.w = qw;

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
          //ROS_INFO("Point %i x,y: %f,%f", i, plan.response.plan.poses[i].pose.position.x, plan.response.plan.poses[i].pose.position.y);
          //ROS_INFO("xP,yP: %f, %f", xP, yP);
          //ROS_INFO("Path: %f", pathLenght);
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

int checkInventory(void)
{
  //Normaly we would check the I/O's representing the loaded products, but we currently have a simulation.
  if(sim)
  {
    return storageSize;
  }
  else
  {
    return 0;
  }
}

int sendToOtherRobots(multirob_test::r2rpickupresponse response)
{
  robotComms.publish(response);
}


void checkWithExisting(robotPickupCommand command)
{
  ROS_INFO("Robot had a command running already.");
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
      distance = calcGoalDistance(dockLocations[i][0], dockLocations[i][1], dockLocations[i][2], dockLocations[i][3], dockLocations[i][4], dockLocations[i][5]);
      ROS_INFO("Robot %i :Distance to goal %s: %f", (robotName.at(robotName.size() - 1)) - 48, dockNames[i].c_str(), distance);
      break;
    }
    else
    {
      distance = -1;
    }
  }

  int space = checkInventory();

  multirob_test::r2rpickupresponse response;
  response.robot = int(robotName.at(robotName.size() - 1)) - 48;
  response.pickup.source = command.source;
  response.pickup.destination = command.destination;
  response.pickup.amount = command.amount;
  if(distance != -1 && space > 0)
  {
    response.canDo = true;
    response.distance = int(distance * 1000);
    response.space = space;
  }
  else
  {
    response.canDo = false;
    response.distance = distance;
    response.space = 0;
  }

  sendToOtherRobots(response);
//Send distance to other robots
  //RobotHasCommand = true;
}

//Change the checking to use a vector. Sort by a weight, e.g. distance, or space, or canDo
void responseReceived(multirob_test::r2rpickupresponse response)
{
  robotResponses[response.robot].robot = response.robot;
  robotResponses[response.robot].pickup.source = response.pickup.source;
  robotResponses[response.robot].pickup.destination = response.pickup.destination;
  robotResponses[response.robot].pickup.amount = response.pickup.amount;
  robotResponses[response.robot].canDo = response.canDo;
  robotResponses[response.robot].distance = response.distance;
  robotResponses[response.robot].space = response.space;

  bool runCommand = true;

  //@TODO:Problem is that sometimes the robots start comparing without having all the data.
  if(robotResponses[1].robot == 1 && robotResponses[2].robot == 2 && robotResponses[3].robot == 3 && robotResponses[4].robot == 4)
  {
    //ROS_INFO("Robot %i :stage 1 ",(robotName.at(robotName.size() - 1)) - 48);
    if(robotResponses[int(robotName.at(robotName.size() - 1)) - 48].canDo)
    {
      for(int i=0; i<numberOfRobots+1; i++)
      {
        //ROS_INFO("Robot %i :stage 2 ",(robotName.at(robotName.size() - 1)) - 48);
        if(robotResponses[i].robot == int(robotName.at(robotName.size() - 1)) - 48) 
        {
          runCommand = runCommand;
	  //ROS_INFO("Robot %i runCommand %s: its me don't compare : ",(robotName.at(robotName.size() - 1)) - 48, runCommand ? "true" : "false");
        }
        else
        {
          if(robotResponses[i].canDo)
          {
            if(robotResponses[int(robotName.at(robotName.size() - 1)) - 48].distance < robotResponses[i].distance)
            {
              runCommand = runCommand;
	      //ROS_INFO("Robot %i runCommand %s: compare = true ",(robotName.at(robotName.size() - 1)) - 48, runCommand ? "true" : "false");	     
            }
            else
            {
              runCommand = false;
	      //ROS_INFO("Robot %i runCommand %s: compare = false",(robotName.at(robotName.size() - 1)) - 48, runCommand ? "true" : "false");
            }
          }
          else 
          {
            runCommand = runCommand;
	    //ROS_INFO("Robot %i runCommand %s: otherrobot.cando = false",(robotName.at(robotName.size() - 1)) - 48, runCommand ? "true" : "false");
          }
        }
      }
      if(runCommand)
      {
        executeCommand(robotResponses[int(robotName.at(robotName.size() - 1)) - 48].pickup.source, robotResponses[int(robotName.at(robotName.size() - 1)) - 48].pickup.destination);
        ROS_INFO("Execute Command");
      }
    }
    for(int i=0; i<numberOfRobots; i++)
    {
      robotResponses[i].robot = 0;
    }
  }
}

//Callback function when a new command msg is received
void commandReceived(multirob_test::cmdPickup command)
{
  //Check if the robot is already executing a command
  //If true, go to the function checking the possibility of adding the command
  //If false, respond to the group, and start executing the command

/*
  ROS_INFO("Received new command");
  ROS_INFO("Source: %s", command.source.c_str());
  ROS_INFO("Destination: %s", command.destination.c_str());
  ROS_INFO("Amount: %i", command.amount);
*/
  robotPickupCommand newCommand;

  newCommand.source = command.source;
  newCommand.destination = command.destination;
  newCommand.amount = command.amount;

  //Launch a new thread with these functions. @TODO Keep track of the amount of threads spun up. This can be as simple as a mutex to prevent a new thread from launching when the old one isn't finished yet.
  if(RobotHasCommand)
  {
    boost::thread t{checkWithExisting, newCommand};//, arg1, arg2}; //Add values to pass
  }
  else
  {
    boost::thread t{startNewCommand, newCommand};//, arg1, arg2}; //Add values to pass
  }
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "decision_logic");

  ros::NodeHandle node;
  ros::NodeHandle nh("~");

  ros::Subscriber pickup_command = node.subscribe("/pickup_command", 1, commandReceived);
  robotComms = node.advertise<multirob_test::r2rpickupresponse>( "/pickup_responses", 0 );
  ros::Subscriber pick_responses = node.subscribe("/pickup_responses", 1, responseReceived);

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
  ros::spin();

  return 0;

}
