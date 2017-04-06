/****************************************/
/*  Bas Janssen                         */
/*  Fontys 2017                         */
/****************************************/



#include <ros/ros.h>
#include <boost/thread.hpp>
//Include the simple_action_client
#include <actionlib/client/simple_action_client.h>
//Include the msg definitions for movebase.
#include <move_base_msgs/MoveBaseAction.h>

//Maybe revise msg to fit to all commands, not just pickup
#include <multirob_test/cmdPickup.h>

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

float dockLocatations[3][6] = {{-5.162, -5.257, 0.000, 0.000, 0.998, -0.066}, {-3.219, -2.244, 0.000, -0.000, -0.607, 0.794}, {8.782, -5.734, -0.000, -0.000, 0.803, 0.595}};

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

void checkWithExisting(robotPickupCommand command)
{
  ROS_INFO("Robot had a command running already.");
}

void startNewCommand(robotPickupCommand command)
{
  ROS_INFO("executing new command.");
  ROS_INFO("Amount: %i", command.amount);
//Tell all other robots that the command can be executed by the this robot
//  getDistance(source);
//Send distance to other robots
  RobotHasCommand = true;
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

  ros::spin();

  return 0;

}
