#ifndef STATE_PUB_H
#define STATE_PUB_H

#include<ros/ros.h> //ros标准库头文件  
#include<iostream> //C++标准输入输出库  
#include<sensor_msgs/JointState.h>   
   
namespace kinova_roshand_state
{        


	class kinova_roshand
	{


             public:
                  kinova_roshand(const ros::NodeHandle &nodehandle);
                  ~kinova_roshand();
    
             private:
                  ros::NodeHandle nh;      

                  ros::Subscriber sub_kinova_state;
                  ros::Subscriber sub_roshand_state;
            
                  ros::Publisher pub_all_joint_state;     

             public:

                   int kinova_joint_number;
                   int roshand_joint_number;

                   int all_joint_number;

                   sensor_msgs::JointState all_joint_state;
                   sensor_msgs::JointState kinova_joint_state;
                   sensor_msgs::JointState roshand_joint_state;


                   void get_kinova_joint_state(const sensor_msgs::JointState::ConstPtr& position);
                   void get_roshand_joint_state(const sensor_msgs::JointState::ConstPtr& position);

                   void publish_all_joint_state();

	};
    
}

#endif 
