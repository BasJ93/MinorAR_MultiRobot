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
#include <multirob_test/pickupProducts.h>
#include <multirob_test/transfer.h>

//The headers to access files.
#include <iostream>
#include <fstream>

#include <math.h>

#include <tf/transform_listener.h>

tf::TransformListener* listener = NULL;

//Define a struct to keep the pickup commands for the robot
struct transferstruct
{
  std::string robotName;
  std::vector<int> amount;
};

struct pickupProductsResponse
{
  std::string robot;
  geometry_msgs::Pose pose;
};

struct robotPickupCommand {
  std::string robotName;
  std::string source;
  std::string destination;
  std::string product;
  int amountTotal;
  std::vector<int> amount;
  bool sendLocation;
  bool done;
};

//Keep a records of the previous/active pickup command
volatile robotPickupCommand previousPickupCommand;

std::vector<multirob_test::r2rpickupresponse> robotResponses;

volatile bool RobotHasCommand = false;
bool transferComming = false;
std::vector<int> amountToCarry = {0,0,0,0,0};

std::vector<std::string> dockNames;
//Design a struct to store the data for a location, then build a vector with this struct.
std::vector<geometry_msgs::Pose> dockLocations;

std::vector<int> amountLeft = {0,0,0,0,0};
std::string amountLeftSource;

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

ros::Publisher robotComms; //This would not be thread safe
ros::Publisher robotMsg;
ros::Publisher pickupProducts;
ros::Publisher transfer;

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

/*void leftOvers()
{
  int amountLeftTotal=0;
  for(int i = 0; i < amountLeft.size(); i++)
  {
    amountLeftTotal = amountLeftTotal + amountLeft[i];
  }  
  ROS_INFO("SEND NEW MESSAGE WITH %i Products",amountLeftTotal);
  multirob_test::cmdPickup msg;
  msg.source = amountLeftSource ;
  msg.destination= "";
  msg.product= "";
  msg.amountTotal= 0;
  msg.amount= amountLeft;
  msg.sendLocation = false; 
  robotMsg.publish(msg);
}*/
void moveToDestinations(std::vector<int> amount)
{
  int amountLeftTotal = 0;
  for(int i = 0; i < amount.size(); i++)
  {
    if(amount[i] == 0)
    {
      ROS_INFO("No products of this locations");
    }
    if(amount[i] > 0)
    {
      moveToLocation(dockLocations[i]); 
      productsLoaded = productsLoaded - amount[i];
      ROS_INFO("%s productsLoaded %i", robotName.c_str(), productsLoaded);
    }
    if(productsLoaded == 0)
    {
      break;
    } 
  }
  RobotHasCommand = false;
  
  for(int i = 0; i < amountLeft.size(); i++)
  {
    amountLeftTotal = amountLeftTotal + amountLeft[i];
  }  
  
  if(amountLeftTotal > 0)
  {
    ROS_INFO("SEND NEW MESSAGE WITH %i Products",amountLeftTotal);
    multirob_test::cmdPickup msg;
    msg.robotName = robotName.c_str();
    msg.source = amountLeftSource ;
    msg.destination= "";
    msg.product= "";
    msg.amountTotal= 0;
    msg.amount= amountLeft;
    msg.sendLocation = false; 
    robotMsg.publish(msg);
  }
  else
  {
    ROS_INFO("%s Robot is able to receive new command", robotName.c_str());
  }

}

void executeCommand(std::string source, std::vector<int> amount)
{
  ROS_INFO("%s will execute the command.", robotName.c_str());
  
  RobotHasCommand = true;
  for(int i=0; i<dockNames.size(); i++)
  {
    if(source.compare(dockNames[i]) == 0)
    {
      moveToLocation(dockLocations[i]);
      break;
    }
  }
  productsLoaded = productsToCarry;
  productsToCarry =  0;
  ROS_INFO("%s productsLoaded %i", robotName.c_str(), productsLoaded);
  int amountLocations = 0;
  for(int i=0; i<amount.size();i++)
  {
    if(amount[i] > 0)
    {
      amountLocations = amountLocations + 1;
    }
    else
    {
      amountLocations = amountLocations;
    }
  }
  ROS_INFO("%s amountLocations %i", robotName.c_str(), amountLocations);  
  amountToCarry = amount;
  
  if(amountLocations ==2)
  {
    ROS_INFO("%s I need help, can anyone transfer",robotName.c_str());
    multirob_test::cmdPickup msg;
    msg.robotName = robotName;
    msg.source = amountLeftSource;
    msg.destination= "";
    msg.product= "";
    msg.amountTotal= 0;
    msg.amount= amount;
    msg.sendLocation = true; 
    robotMsg.publish(msg);
    
  }
  else
  {
    moveToDestinations(amount);
  }
}

//Function to calculate the disatance from the robot to a given target location, in the x,y and quaternion notation. Returns a float representing the lenght of the path.\
//TODO the distance to the goal is sometimes closes because the robot isn't sure of its position, this is a problem on small scale but on big scale this would not be a problem. 
void pickupLogic(geometry_msgs::Pose pose)
{
  
  ROS_INFO("%s whoop",robotName.c_str());
  moveToLocation(pose);
  ROS_INFO("%s I'm there lets transfer",robotName.c_str());
    multirob_test::transfer msg;
    msg.robotName = robotName;
    msg.amount= amountToCarry; 
    transfer.publish(msg);
  //moveToDestination(amount);
}

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
        //ROS_INFO("Path has %lu points.", plan.response.plan.poses.size());
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
std::vector<int> checkInventory(std::vector<int> amount)
{
  //Normaly we would check the I/O's representing the loaded products, but we currently have a simulation.
  //TODO goto has to be replaced 
  std::vector<int> result = {0,0,0,0,0,0,0,0,0,0}; //storageSizeUsed, amountLeft
  int storageSizeLeft = 6;
  int save = 0;
  int save2 = 0;
  int getOut = false;
  int amountTotal = 0;
  if(sim)
  {
    LOOP: if (getOut == false)
    {
      for(int i = 0; i < amount.size(); i++)
      {
        amountTotal = amountTotal + amount[i];
      }      
      
      if(storageSize < amountTotal)
      {
        for(int i = 0; i < amount.size(); i++)
        {
          if(i == 0)
          {
            save = amount[0];
            save2 = 0;
          }  
          if(save < amount[i])
          {
            save = amount[i];
            save2 = i;
          }
          else if(save >= amount[i])
          {
            save = save;
            save2 = save2; 
          }
        }
        if(save < storageSize)
        {
          for(int i = 0; i<5; i++)
          {
            if(i == save2)
            {
              result[i] = save;
              amount[i] = amount[i] - save;
              for(int i = 0; i < 5; i++)
              {
                storageSizeLeft = storageSizeLeft - result[i];
              } 
            }
            else
            {
              result[i] = 0;
            }  
          }
          for(int i = 0; i < 5; i++)
          {
            if(amount[i] <= storageSizeLeft && amount[i] >0)
            { 
              result[i] = result[i] + amount[i];
              amount[i] = 0;
              storageSizeLeft = storageSizeLeft - result[i];
            }
            else if(amount[i] > storageSizeLeft)
            {
              result[i] = result[i];
              amount[i] = amount[i];
            }
            
          }
          getOut = true;
          goto LOOP;
        }  
        if(save == storageSize)
        {
          for(int i = 0; i<5; i++)
          {
            if( i == save2)
            {
              result[i] = save;
              amount[i] = amount[i] - save;
            }
            else
            {
              result[i] = 0;
            }  
          }
          getOut = true;
          goto LOOP;
        }
        if(save> storageSize);
        {
          for(int i = 0; i<5; i++)
          {
            if( i == save2)
            {
              result[i] = storageSize;
              amount[i] = amount[i] - storageSize;
            }
            else
            {
              result[i] = 0;
            }  
          }
          getOut = true;
          goto LOOP;
        }              
      }
      else if(storageSize >= amountTotal)
      {
        for(int i = 0; i<5; i++)
        {
          result[i] = result[i] + amount[i];
          amount[i] = 0;
        }
        getOut = true;
        goto LOOP;
      }  
    }
    for(int i = 0; i<5; i++)
    {
      result[i+5] = amount[i];
    } 
  }
  return result;  
}    

int sendToOtherRobots(multirob_test::r2rpickupresponse response)
{
  robotComms.publish(response);
}

void checkWithExisting(robotPickupCommand command)
{
  ROS_INFO("%s had a command running already.",robotName.c_str());
  
  float distance = 0;
  
  /*for(int i=0; i<5; i++)
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
  }*/ 
  distance = -1;
  int amountTotal1 = 0;
  for(int i = 0; i < command.amount.size(); i++)
  {
    amountTotal1 = amountTotal1 + command.amount[i];
  }  
  multirob_test::r2rpickupresponse response;
  response.robot = int(robotName.at(robotName.size() - 1)) - 48;
  response.pickup.robotName = command.robotName;
  response.pickup.source = command.source;
  response.pickup.destination = command.destination;
  response.pickup.amountTotal = amountTotal1;
  response.pickup.amount = command.amount;
  response.pickup.sendLocation = command.sendLocation;
  ROS_INFO("SL4: %s", command.sendLocation ? "true" : "false");

  response.canDo = false;

  response.distance = distance;
  response.space = 0;
  
  sendToOtherRobots(response);
}

void startNewCommand(robotPickupCommand newCommand)
{
  float distance =0;
  int storageSizeUsed = 0;
  if(newCommand.sendLocation == true)
  {
    ROS_INFO("%s Calculate the distance to locations",robotName.c_str());
    
    for(int i=0; i< newCommand.amount.size(); i++)
    {
      if(newCommand.amount[i] > 0)
      {
        distance = distance + calcGoalDistance(dockLocations[i]);
      }
      else
      {
        distance = distance;
      }
    }
    ROS_INFO("%s :Distance to goals : %f",robotName.c_str(), distance);
    
    multirob_test::r2rpickupresponse response;
    response.robot = int(robotName.at(robotName.size() - 1)) - 48;
    response.pickup.robotName = newCommand.robotName;
    response.pickup.source = newCommand.source;
    response.pickup.destination = newCommand.destination;
    response.pickup.amountTotal = newCommand.amountTotal;
    response.pickup.amount = newCommand.amount;
    response.pickup.sendLocation = newCommand.sendLocation;
    ROS_INFO("SL2: %s", newCommand.sendLocation ? "true" : "false");
       
    if(distance != -1)
    {
      //ROS_INFO("check");
      response.canDo = true;
      response.distance = int(distance * 1000);
      response.space = storageSizeUsed;
    }
    else
    {
      //ROS_INFO("check 2");
      response.canDo = false;
      response.distance = distance;
      response.space = 0;
    }
    sendToOtherRobots(response);
  }
  
  else
  {
    ROS_INFO("Executing new command.");
    //Tell all other robots that the command can be executed by the this robot
    for(int i=0; i<5; i++)
    {
     if(newCommand.source.compare(dockNames[i]) == 0)
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
    std::vector<int> space = checkInventory(newCommand.amount);
 
    for( int i= 0; i < 5; i++)
    {
      storageSizeUsed = storageSizeUsed + space[i];
    }
    //ROS_INFO("startNewCommand storageSizeUsed %i", storageSizeUsed);
   
    multirob_test::r2rpickupresponse response;
    response.robot = int(robotName.at(robotName.size() - 1)) - 48;
    response.pickup.robotName = newCommand.robotName;
    response.pickup.source = newCommand.source;
    response.pickup.destination = newCommand.destination;
    response.pickup.amountTotal = newCommand.amountTotal;
    response.pickup.amount = newCommand.amount;
    response.pickup.sendLocation = newCommand.sendLocation;
    ROS_INFO("SL3 : %s", newCommand.sendLocation ? "true" : "false");
   
    if(distance != -1 && storageSizeUsed > 0)
    {
      //ROS_INFO("check");
      response.canDo = true;
      response.distance = int(distance * 1000);
      response.space = storageSizeUsed;
    }
    else
    {
      //ROS_INFO("check 2");
      response.canDo = false;
      response.distance = distance;
      response.space = 0;
    }
    sendToOtherRobots(response);
  } 
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
    
    //Check how many robots are needed to transport the amount of products   
    
    std::vector<int> result = checkInventory(response.pickup.amount);
    int limit = robotResponsescanDo.size();
    std::vector<int> productsPerDest = {0,0,0,0,0};   
    ROS_INFO("Amount of Robots available for the task %i", limit);
    
    for(int i = 0; i<5; i++)
    {
      productsPerDest[i] = result[i];
    } 
    
    for(int i = 0; i<5; i++)
    {
      amountLeft[i] = result[i+5];
    }

    int amountLeftTotal = 0;
    for(int i = 0; i<5; i++)
    {
      amountLeftTotal = amountLeftTotal + amountLeft[i];
    } 
    ROS_INFO("amountLeftTotal %i", amountLeftTotal);   
    
    if (amountLeftTotal <= 0)
    {
      if(robotResponsescanDo[0].robot == int(robotName.at(robotName.size() - 1) - 48))
      {
        for(int i = 0; i<productsPerDest.size(); i++)
        {
          productsToCarry = productsToCarry + productsPerDest[i];
        }
        ROS_INFO("%s productsToCarry %i and amountLeftTotal %i",robotName.c_str(), productsToCarry, amountLeftTotal);     
        runCommand = true;
      }
    }    
    for(int j = 0; limit > 0 && amountLeftTotal > 0 && response.canDo == true; j++)
    {
      ROS_INFO("%s Got in the forLoop",robotName.c_str());
      if(robotResponsescanDo[j].robot == int(robotName.at(robotName.size() - 1) - 48))
      {
        ROS_INFO("%s Got in the IfLoop",robotName.c_str());
        if (j == 0)
        { 
          ROS_INFO("%s Got in the IfLoop2",robotName.c_str());
          for(int i = 0; i<productsPerDest.size(); i++)
          {
            ROS_INFO("%s Got in the forLoop2",robotName.c_str());
            productsToCarry = productsToCarry + productsPerDest[i];
          }
          ROS_INFO("%s productsToCarry %i and amountLeftTotal %i",robotName.c_str(), productsToCarry, amountLeftTotal);          
        }
        else
        {
          std::vector<int> result2 = checkInventory(amountLeft);
          for(int i = 0; i<5; i++)
          {
            productsPerDest[i] = result2[i];
          } 
          for(int i = 0; i<5; i++)
          {
            amountLeft[i] = result2[i+5];            
          }
          amountLeftTotal = 0;
          for(int i = 0; i<5; i++)
          {
            amountLeftTotal = amountLeftTotal + amountLeft[i];            
          }
          for(int i = 0; i<productsPerDest.size(); i++)
          {
            productsToCarry = productsToCarry + productsPerDest[i];
          }
          ROS_INFO("%s productsToCarry %i and amountLeftTotal %i",robotName.c_str(), productsToCarry, amountLeftTotal);
        }
        runCommand = true;
      }
      else
      {
        if (j == 0)
        { 
          amountLeftTotal = amountLeftTotal;        
        }
        else
        {
          std::vector<int> result2 = checkInventory(amountLeft);
          for(int i = 0; i<5; i++)
          {
            amountLeft[i] = result2[i+5];
          }
          amountLeftTotal = 0;
          for(int i = 0; i<5; i++)
          {
            amountLeftTotal = amountLeftTotal + amountLeft[i];
          }
        }
      }
      limit = limit - 1;
    }
    
    // If the robot got a go on the command they will execute it 
    //ROS_INFO("I'm %s and I made it here with %i",robotName.c_str(), amountLeftTotal);
    amountLeftSource = robotResponses[0].pickup.source;
    if(runCommand)
    {
      if (limit <= 0 && amountLeftTotal > 0)
      {
          RobotHasCommand = true;
          boost::thread t{executeCommand, robotResponses[0].pickup.source, productsPerDest};
          ROS_INFO("%s will execute the Command with !!!!!!Products Left: %i !!!!!!!",robotName.c_str(), amountLeftTotal);        
      }
      else
      {
        if(response.pickup.sendLocation)
        {
          geometry_msgs::Pose pose;
          tf::StampedTransform transform;
          bool canTransform = true;
          std::string footprint = "/" + robotName + "/base_footprint";
          try
          {
            listener->lookupTransform(footprint, "/map", ros::Time(0), transform);
          }
          catch (tf::TransformException ex)
          {
            ROS_ERROR("%s",ex.what());
            ros::Duration(1.0).sleep();
            canTransform = false;
          }
          if(canTransform)
          {
            pose.position.x =transform.getOrigin().getX();
            pose.position.y =transform.getOrigin().getY();
            geometry_msgs::Quaternion quat;
            tf::quaternionTFToMsg(transform.getRotation(), quat); 
            pose.orientation = quat;
            
            ROS_INFO("%s I can help you",robotName.c_str());
            multirob_test::pickupProducts msg;
            msg.robot = response.pickup.robotName;
            msg.pose = pose;
            pickupProducts.publish(msg); 
            transferComming = true;
          }
          else
          {
            ROS_INFO("%s can't transform",robotName.c_str());
          }
          /*
          transform.getOrigin().getX();
          transform.getOrigin().getY();
          
          geometry_msgs::Quaternion quat;
          tf::quaternionTFToMsg(transform.getRotation(), quat); 
          quat
          ROS_INFO("%s Send Locations to robot X %f Y %f",robotName.c_str(),transform.getOrigin().getX(),transform.getOrigin().getY());
          pickupProducts.publish(ddsadsatransform);
          ROS_INFO("%s I can help you",robotName.c_str());
          multirob_test::pickupProducts msg;
          msg.robot = response.pickup.robotName;
          msg.robotX = transform.getOrigin().getX();  
          msg.robotY = transform.getOrigin().getY();
          msg.pose = transform;
          pickupProducts.publish(msg); 
          transferComming = true; */             
        } 
        else
        {
          RobotHasCommand = true;
          boost::thread t{executeCommand, robotResponses[0].pickup.source, productsPerDest};
          ROS_INFO("%s will execute the Command",robotName.c_str());
        }
      }
    }  
    robotResponses.clear();
    robotResponsescanDo.clear();    
  }
  
}

void transferLogic(std::string robotName, std::vector<int> amount)
{
  transferstruct data;
  data.robotName = robotName;
  data.amount = amount;
  int amountLocations = 0;
  
  
  for(int i=0; i<data.amount.size();i++)
  {
    if(data.amount[i] > 0)
    {
      amountLocations = amountLocations + 1;
    }
    else
    {
      amountLocations = amountLocations;
    }
  }
  
  if(transferComming)
  {
    if(amountLocations == 2)
    {
      bool getOut = false;
      for(int i =0; i< data.amount.size() ; i++)
      {
        if(getOut == false)
        {
          if(data.amount[i]>0)
          {
            amountToCarry[i] = data.amount[i];
            getOut = true;
          }
          else 
          {
            amountToCarry[i] = amountToCarry[i];
          }
        }
      } 
    }
    transferComming = false;
    moveToDestinations(amountToCarry);
  }
  if(data.robotName == robotName)
  {
    if(amountLocations ==2)
    {
      bool getOut = false;
      for(int i =0; i< data.amount.size() ; i++)
      {
        if(getOut == false)
        {
          if(data.amount[i] > 0)
          {
            amountToCarry[i] = 0;
            getOut = true;
          }
          else 
          {
            amountToCarry[i] = amountToCarry[i];
          }
        }
      }
    }
    moveToDestinations(amountToCarry);
  }    
}

void transferReceived(multirob_test::transfer response)
{
  transferstruct data;
  //std::vector<int> amount = {0,0,0,0,0};;
  //std::vector<int> amountMe = {0,0,0,0,0};
  data.robotName = response.robotName;
  data.amount = response.amount;  
  if(transferComming)
  {
    transferLogic(data.robotName, data.amount);
  }
  if(data.robotName == robotName.c_str())
  {
    transferLogic(data.robotName, data.amount);
  }
  else
  {
    ROS_INFO("%s dont need to transfer anything",robotName.c_str());  
  }
}

void pickupProductsResponseReceived(multirob_test::pickupProducts response)
{
  pickupProductsResponse data;
  data.robot = response.robot;
  data.pose = response.pose;
  /*data.robotX = response.robotX;
  data.robotY = response.robotY;
  
  geometry_msgs::Pose pose;
  pose.position.x = data.robotX;
  pose.position.y = data.robotY;
  pose.position.z = 0.0;
  pose.orientation.x = 0.0;
  pose.orientation.y = 0.0;
  pose.orientation.z = 0.0;
  pose.orientation.w = 0.0;*/
  
  if(data.robot == robotName.c_str())
  {
    ROS_INFO("%s Its me, I have to do something",robotName.c_str());
    pickupLogic(data.pose);  
  }
  else
  {
    ROS_INFO("%s Not me so dont do shit",robotName.c_str());  
  } 
}

//Callback function when a new command msg is received
void commandReceived(multirob_test::cmdPickup command)
{
  //Check if the robot is already executing a command
  //If true, go to the function checking the possibility of adding the command
  //If false, respond to the group, and start executing the command
  robotPickupCommand newCommand;

  int amountTotal2 = 0;
  for(int i = 0; i < command.amount.size(); i++)
  {
    amountTotal2 = amountTotal2 + command.amount[i];
  } 
  ROS_INFO("CommandReceived amountTotal %i",amountTotal2); 
  newCommand.robotName = command.robotName;
  newCommand.source = command.source;
  newCommand.destination = command.destination;
  newCommand.amountTotal = amountTotal2;
  newCommand.amount = command.amount;
  newCommand.sendLocation = command.sendLocation;
  ROS_INFO("SL: %s", command.sendLocation ? "true" : "false");
  

  //Launch a new thread with these functions. @TODO Keep track of the amount of threads spun up. This can be as simple as a mutex to prevent a new thread from launching when the old one isn't finished yet.
  if(RobotHasCommand)
  {
    ROS_INFO("%s Go to Check",robotName.c_str());
    boost::thread t{checkWithExisting, newCommand};//, arg1, arg2}; //Add values to pass
    t.detach();
  }
  else
  {
    ROS_INFO("%s Go to NewCommand",robotName.c_str());
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
  robotMsg = node.advertise<multirob_test::cmdPickup>( "/pickup_command", 0 );
  
  ros::Subscriber pick_message = node.subscribe("/pickup_message", 10, pickupProductsResponseReceived);
  pickupProducts = node.advertise<multirob_test::pickupProducts>( "/pickup_message", 0 );
  
  ros::Subscriber pick_transfer = node.subscribe("/pickup_transfer", 10, transferReceived);
  transfer = node.advertise<multirob_test::transfer>( "/pickup_transfer", 0 );
  
  //geometry_msgs::Pose
  
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
  std::string filePath;
  if(sim)
  {
    filePath = packagePath + "/locations/locations_sim.txt";
  }
  else
  {
    filePath = packagePath + "/locations/locations.txt";
  }
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
