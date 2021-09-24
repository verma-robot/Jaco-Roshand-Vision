#include <vector>
#include "state_pub.h"

namespace kinova_roshand_state
{

    kinova_roshand::kinova_roshand(const ros::NodeHandle &nodehandle):
         nh(nodehandle)
   { 


           sub_kinova_state = nh.subscribe ("/jaco_driver/out/joint_state", 1, &kinova_roshand::get_kinova_joint_state, this);

           sub_roshand_state = nh.subscribe ("/RosHand_JointState", 1, &kinova_roshand::get_roshand_joint_state, this);


           pub_all_joint_state = nh.advertise<sensor_msgs::JointState>("/all_joint_state",1000);    



  
   }

   kinova_roshand::~kinova_roshand()
   {



   }
   
   void kinova_roshand::get_kinova_joint_state(const sensor_msgs::JointState::ConstPtr& position)
   {

        sensor_msgs::JointState kinova_state;
        kinova_state = *position;

        kinova_joint_number = kinova_state.name.size();
//std::cout << kinova_joint_number << std::endl;


int kinova_number = kinova_joint_state.name.size();

if(kinova_number != 0)
{
        for(int i = 0; i < kinova_joint_state.name.size(); i++)
        {

            kinova_joint_state.name.clear();
            kinova_joint_state.position.clear();
            kinova_joint_state.velocity.clear();
            kinova_joint_state.effort.clear();

        }
}

        if(kinova_joint_number != 0)
        {

            for(int i = 0; i < kinova_joint_number; i++)
            {

               if(kinova_state.name[i] == "jaco_joint_5")kinova_state.position[i] -= 3.1416;
               kinova_joint_state.name.push_back(kinova_state.name[i]);           
               kinova_joint_state.position.push_back(kinova_state.position[i]);
               kinova_joint_state.velocity.push_back(kinova_state.velocity[i]);    
               kinova_joint_state.effort.push_back(kinova_state.effort[i]);
             
            }


        }
   }


   void kinova_roshand::get_roshand_joint_state(const sensor_msgs::JointState::ConstPtr& position)
   {

        sensor_msgs::JointState roshand_state;
        roshand_state = *position;

        roshand_joint_number = roshand_state.name.size();
        int roshand_number = roshand_joint_state.name.size();
        if(roshand_number != 0)
        {
           for(int i = 0; i < roshand_joint_state.name.size(); i++)
           {

              roshand_joint_state.name.clear();
              roshand_joint_state.position.clear();
              roshand_joint_state.velocity.clear();
              roshand_joint_state.effort.clear();

           }
        }

        if(roshand_joint_number != 0)
        {

            for(int i = 0; i < roshand_joint_number; i++)
            {

               roshand_joint_state.name.push_back(roshand_state.name[i]);           
               roshand_joint_state.position.push_back(roshand_state.position[i]);
               roshand_joint_state.velocity.push_back(0);    
               roshand_joint_state.effort.push_back(0);
             
            }


        }
   }


   void kinova_roshand::publish_all_joint_state()
   {


        all_joint_state.header.stamp = ros::Time::now();
        all_joint_state.header.frame_id = "";



        for(int i = 0; i < roshand_joint_state.name.size(); i++)
        {

            all_joint_state.name.push_back(roshand_joint_state.name[i]);           
            all_joint_state.position.push_back(roshand_joint_state.position[i]);
            all_joint_state.velocity.push_back(roshand_joint_state.velocity[i]);    
            all_joint_state.effort.push_back(roshand_joint_state.effort[i]);
             
        } 

        for(int i = 0; i < kinova_joint_state.name.size(); i++)
        {

            all_joint_state.name.push_back(kinova_joint_state.name[i]);           
            all_joint_state.position.push_back(kinova_joint_state.position[i]);
            all_joint_state.velocity.push_back(kinova_joint_state.velocity[i]);    
            all_joint_state.effort.push_back(kinova_joint_state.effort[i]);
             
        } 

        pub_all_joint_state.publish(all_joint_state);

        for(int i = 0; i < all_joint_state.name.size(); i++)
        {

            all_joint_state.name.clear();
            all_joint_state.position.clear();
            all_joint_state.velocity.clear();
            all_joint_state.effort.clear();

        }

   }
  
;


}

int main(int argc, char** argv)
{

	ros::init(argc, argv, "kinova_roshand_state");	
								
	ros::NodeHandle nh_("~");
    

        kinova_roshand_state::kinova_roshand state_pub(nh_);
      //  ros::spin();  

	ros::Rate loop_rate(10);
	while (ros::ok()) 
	{

            try
            {
                state_pub.publish_all_joint_state();
	        ros::spinOnce();
	        loop_rate.sleep();
            }
            catch(const std::exception& e)
            {
		ROS_ERROR("//////////////ERROR/////////////.");


            }

	}

	return 0;

}

