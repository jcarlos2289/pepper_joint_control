/*
* Controlling Pepper Robot Arms
* using messages and angles
* @jcarlos2289
* 15-09-2017
*/

#include "ros/ros.h"
#include "naoqi_bridge_msgs/JointAnglesWithSpeed.h"
#include <string>
#include <vector>
#include <math.h>
#include <ros/console.h>

// //LIST OF VARIABLES

// arrays which keep all joint names and angles to be sent to NAO robot
std::vector<std::string> naoJointNames(0) ;
std::vector<float> naoJointAngles(0) ;

// fraction of maximum joint velocity [0:1]
float speed;
//absolute angle (0 is default) or relative change
uint8_t rel ;


void initializeArms() {
    // initialize all the joints to be controlled to zero
    naoJointNames.push_back("LShoulderRoll") ;
    naoJointAngles.push_back(0.1221730476) ;
    naoJointNames.push_back("LShoulderPitch") ;
    naoJointAngles.push_back(0.9721483934) ;
    naoJointNames.push_back("LElbowYaw") ;
    naoJointAngles.push_back(-1.066396173) ;
    naoJointNames.push_back("LElbowRoll") ;
    naoJointAngles.push_back(-1.2409290982) ;
    naoJointNames.push_back("LWristYaw") ;
    naoJointAngles.push_back(-0.5689773362) ;
    naoJointNames.push_back("RShoulderRoll") ;
    naoJointAngles.push_back(-0.1134464014) ;
    naoJointNames.push_back("RShoulderPitch") ;
    naoJointAngles.push_back(0.9826203689) ;
    naoJointNames.push_back("RElbowYaw") ;
    naoJointAngles.push_back(1.0646508437) ;
    naoJointNames.push_back("RElbowRoll") ;
    naoJointAngles.push_back(1.2479104152) ;
    naoJointNames.push_back("RWristYaw") ;
    naoJointAngles.push_back(0.5724679947) ;
    naoJointNames.push_back("RHand") ;
    naoJointAngles.push_back(0.0160570291) ;
    naoJointNames.push_back("LHand") ;
    naoJointAngles.push_back(0.0167551608) ;
}
int main( int argc , char **argv) {

    // initialize a node with name
    ros::init (argc, argv, "PepperRawJointAngles") ;

    ROS_INFO("Pepper Arm Control node Active");

    // create node handle
    ros::NodeHandle n;

     // create a function to advertise on a given topic
    //ros::Publisher joint_angles_pub = n.advertise<naoqi_bridge_msgs::JointAnglesWithSpeed>("/nao_robot/pose/joint_angles" ,000);
    ros::Publisher joint_angles_pub = n.advertise<naoqi_bridge_msgs::JointAnglesWithSpeed>("/joint_angles" ,1000);

    //choose the looping rate
    ros::Rate loop_rate(500);

    // create message element to be filled with appropriate data to be published
    naoqi_bridge_msgs::JointAnglesWithSpeed msg;

    // initialize arms to zero;
    initializeArms();

    // loop
    while(ros::ok()) {
        // Put elements into message for publishing topic
        msg.joint_names = naoJointNames;
        msg.joint_angles = naoJointAngles;  // float [] -In Radians (must be array)
        speed = 0.1;
        rel = 0;

        msg.speed = speed; // float 
        msg.relative = rel; // unit8

        // publish
        joint_angles_pub.publish(msg);

        // spin once
        ros::spinOnce() ;

        // sleep
        loop_rate.sleep() ;
    }
    return 0;
}
