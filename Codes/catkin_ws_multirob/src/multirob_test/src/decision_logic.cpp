/****************************************/
/*  Bas janssen                         */
/*  Fontys 2017                         */
/****************************************/



#include <ros/ros.h>
#include <boost/thread.hpp>

//Maybe revise msg to fit to all commands, not just pickup
#include <multirob_test/cmdPickup.h>



bool RobotHasCommand = false;

void checkWithExisting()
{
  ROS_INFO("Robot had a command running already.");
}

void startNewCommand()
{
  ROS_INFO("executing new command.");
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


  //Possibly launch a new thread with these functions. Keep track of the amount of threads spun up.
  if(RobotHasCommand)
  {
    boost::thread t{checkWithExisting};//, arg1, arg2}; //Add values to pass
  }
  else
  {
    boost::thread t{startNewCommand};//, arg1, arg2}; //Add values to pass
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
