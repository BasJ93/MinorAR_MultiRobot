/****************************************/
/*  Bas Janssen                         */
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

bool RobotHasCommand = false;

float dockLocations[3][6] = {{-5.162, -5.257, 0.000, 0.000, 0.998, -0.066}, {-3.219, -2.244, 0.000, -0.000, -0.607, 0.794}, {8.782, -5.734, -0.000, -0.000, 0.803, 0.595}};

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

void moveToLocation(float x, float y, float qx, float qy, float qz, float qw)
{
  MoveBaseClient ac("move_base", true);
  while(!ac.waitForServer(ros::Duration(5.0)))
  {
    ROS_INFO("Waiting for action server");
  }

  move_base_msgs::MoveBaseGoal goal;

  goal.target_pose.header.frame_id = "/map";
  goal.target_pose.header.stamp = ros::Time::now();

  goal.target_pose.pose.position.x = x;
  goal.target_pose.pose.position.y = y;

  goal.target_pose.pose.orientation.x = qx;
  goal.target_pose.pose.orientation.y = qy;
  goal.target_pose.pose.orientation.z = qz;
  goal.target_pose.pose.orientation.w = qw;

  ac.sendGoal(goal);

  ac.waitForResult();
}

float calcGoalDistance(float x, float y, float qx, float qy, float qz, float qw)
{
  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<nav_msgs::GetPlan>("move_base/make_plan");
  nav_msgs::GetPlan plan;

  tf::StampedTransform transform;
  bool canTransform = true;
  try{
    listener->lookupTransform("robot1/base_footprint", "/map", ros::Time(0), transform);
  }
  catch (tf::TransformException ex){
    ROS_ERROR("%s",ex.what());
    ros::Duration(1.0).sleep();
    canTransform = false;
  }

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
        ROS_INFO("Path has %u points.", plan.response.plan.poses.size());
        float pathLenght;
        for (int i=0; i<plan.response.plan.poses.size(); i++)
        {
          float xP = plan.response.plan.poses[i].pose.position.x - plan.response.plan.poses[i+1].pose.position.x;
          float yP = plan.response.plan.poses[i].pose.position.y - plan.response.plan.poses[i+1].pose.position.y;
          pathLenght = pathLenght + sqrtf(pow(xP, 2.0) + pow(yP, 2.0));
          //ROS_INFO("Point %i x,y: %f,%f", i, plan.response.plan.poses[i].pose.position.x, plan.response.plan.poses[i].pose.position.y);
          //ROS_INFO("xP,yP: %f, %f", xP, yP);
          //ROS_INFO("Path: %f", pathLenght);
        }
        return pathLenght;
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

void checkWithExisting(robotPickupCommand command)
{
  ROS_INFO("Robot had a command running already.");
}

void startNewCommand(robotPickupCommand command)
{
  ROS_INFO("executing new command.");
  
//Tell all other robots that the command can be executed by the this robot
  if(command.source.compare("A") == 0)
  {
    float distance = calcGoalDistance(dockLocations[0][0], dockLocations[0][1], dockLocations[0][2], dockLocations[0][3], dockLocations[0][4], dockLocations[0][5]);
    ROS_INFO("Distance to goal: %f", distance);
  }
//  getDistance(source);
//Send distance to other robots
  //RobotHasCommand = true;
}

//Callback function when a new command msg is received
void commandReceived(multirob_test::cmdPickup command)
{
  //Check if the robot is already executing a command
  //If true, go to the function checking the possibility of adding the command
  //If false, respond to the group, and start executing the command

  ROS_INFO("Received new command");
  ROS_INFO("Source: %s", command.source.c_str());
  ROS_INFO("Destination: %s", command.destination.c_str());
  ROS_INFO("Amount: %i", command.amount);

 robotPickupCommand newCommand;

  newCommand.source = command.source;
  newCommand.destination = command.destination;
  newCommand.amount = command.amount;

  //Possibly launch a new thread with these functions. Keep track of the amount of threads spun up.
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

  ros::Subscriber pickup_command = node.subscribe("pickup_command", 1, commandReceived);

  listener = new(tf::TransformListener);

  ros::spin();

  return 0;

}
