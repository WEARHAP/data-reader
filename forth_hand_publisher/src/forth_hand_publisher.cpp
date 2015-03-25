
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctime>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <string.h>
#include <cstring>
#include <complex>
#include <signal.h>

// ROS headers
#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <sensor_msgs/PointCloud.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/point_cloud_conversion.h>
#include <visualization_msgs/Marker.h>

#include <geometry_msgs/WrenchStamped.h>

#include </opt/ros/indigo/include/tf/transform_listener.h>
#include </opt/ros/indigo/include/tf/transform_broadcaster.h>
#include </opt/ros/indigo/include/tf/transform_datatypes.h>

#include <eigen3/Eigen/Eigen>
#include <fstream>
#include <eigen3/Eigen/SVD>

using namespace std;
using namespace Eigen;


float pi = 3.141592;
float dof_1,dof_2,dof_3,dof_4,dof_5,dof_6,dof_7,dof_8,dof_9,dof_10,dof_11,dof_12,dof_13,dof_14,dof_15,dof_16,dof_17,dof_18,dof_19,dof_20;
int campioni = 3175;


int main(int argc, char** argv)
{

    // ROS dependant code
    
    dof_1 = 0; dof_2 = 0; dof_3 = 0; dof_4 = 0;
    dof_5 = 0; dof_6 = 0; dof_7 = 0; dof_8 = 0;
    dof_9 = 0; dof_10 = 0; dof_11 = 0; dof_12 = 0;
    dof_13 = 0; dof_14 = 0; dof_15 = 0; dof_16 = 0;
    dof_17 = 0; dof_18 = 0; dof_19 = 0; dof_20 = 0;
    
    int k;
    ros::init(argc, argv, "joint_publisher");
    ros::NodeHandle n;

    //definizioni per Joint States
    ros::Publisher pub_joints = n.advertise<sensor_msgs::JointState>("/joint_states", 1000); 
    sensor_msgs::JointState my_joint_state;
    my_joint_state.name.resize(23);
    my_joint_state.position.resize(23);

// ROS dependant // QUI DEVO CAMBIARE TUTTI I NOMI

            //palm's joints
                 my_joint_state.name[0] = "box_wrist_right_joint_1";
                 my_joint_state.position[0] = 0;
                 my_joint_state.name[1] = "box_wrist_right_joint_2";
                 my_joint_state.position[1] = 0;
                 my_joint_state.name[2] = "box_wrist_right_joint_3";
                 my_joint_state.position[2] = 0;

                my_joint_state.name[3] = "forth_hand_right_thumb_abd_joint";
                my_joint_state.position[3] = dof_2 ;
                my_joint_state.name[4] = "forth_hand_right_thumb_rot_joint";
                my_joint_state.position[4] = dof_1 ;
                my_joint_state.name[5] = "forth_hand_right_thumb_inner_joint";
                my_joint_state.position[5] = dof_3;
                my_joint_state.name[6] = "forth_hand_right_thumb_outer_joint";
                my_joint_state.position[6] = dof_4;     

            //index joints
                my_joint_state.name[7] = "forth_hand_right_index_abd_joint";
                my_joint_state.position[7] = dof_5;
                my_joint_state.name[8] = "forth_hand_right_index_inner_joint";
                my_joint_state.position[8] = dof_6;
                my_joint_state.name[9] = "forth_hand_right_index_middle_joint";
                my_joint_state.position[9] = dof_7;
                my_joint_state.name[10] = "forth_hand_right_index_outer_joint";
                my_joint_state.position[10] = dof_8;


            //middle joints
                my_joint_state.name[11] = "forth_hand_right_middle_abd_joint";
                my_joint_state.position[11] = dof_9;
                my_joint_state.name[12] = "forth_hand_right_middle_inner_joint";
                my_joint_state.position[12] = dof_10;
                my_joint_state.name[13] = "forth_hand_right_middle_middle_joint";
                my_joint_state.position[13] = dof_11;
                my_joint_state.name[14] = "forth_hand_right_middle_outer_joint";
                my_joint_state.position[14] = dof_12;


            //ring joints
                my_joint_state.name[15] = "forth_hand_right_ring_abd_joint";
                my_joint_state.position[15] = dof_13;
                my_joint_state.name[16] = "forth_hand_right_ring_inner_joint";
                my_joint_state.position[16] = dof_14;
                my_joint_state.name[17] = "forth_hand_right_ring_middle_joint";
                my_joint_state.position[17] = dof_15;
                my_joint_state.name[18] = "forth_hand_right_ring_outer_joint";
                my_joint_state.position[18] = dof_16;
                
                

            //little's joints
                my_joint_state.name[19] = "forth_hand_right_little_abd_joint";
                my_joint_state.position[19] = dof_17;
                my_joint_state.name[20] = "forth_hand_right_little_inner_joint";
                my_joint_state.position[20] = dof_18;
                my_joint_state.name[21] = "forth_hand_right_little_middle_joint";
                my_joint_state.position[21] = dof_19;
                my_joint_state.name[22] = "forth_hand_right_little_outer_joint";
                my_joint_state.position[22] = dof_20;
                
                     
             
    
        my_joint_state.header.stamp=ros::Time::now();
        pub_joints.publish(my_joint_state);
    
// ROS dependant

        int row = campioni;
        int column = 20;

        MatrixXf Matrice(row,column);
    
        FILE *joints_data=fopen("/home/centropiaggio/catkin_ws/src/forth_hand_publisher/seq0.txt", "r");
    
        for(k=0; k<row; k++ ){
            fscanf(joints_data, "%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n", &Matrice(k,0),&Matrice(k,1),&Matrice(k,2),&Matrice(k,3),&Matrice(k,4),&Matrice(k,5),&Matrice(k,6),&Matrice(k,7),&Matrice(k,8),&Matrice(k,9),&Matrice(k,10),&Matrice(k,11),&Matrice(k,12),&Matrice(k,13),&Matrice(k,14),&Matrice(k,15),&Matrice(k,16),&Matrice(k,17),&Matrice(k,18),&Matrice(k,19));
        }
        fclose(joints_data);


       

    // INIZIO CICLO WHILE //

        getchar();
        int current = 0;
    //while (current < campioni){
    while (1){

                dof_1 = Matrice(current,0);
                dof_2 = Matrice(current,1);
                dof_3 = Matrice(current,2);
                dof_4 = Matrice(current,3);
                dof_5 = Matrice(current,4);
                dof_6 = Matrice(current,5);
                dof_7 = Matrice(current,6);
                dof_8 = Matrice(current,7);
                dof_9 = Matrice(current,8);
                dof_10 = Matrice(current,9);
                dof_11 = Matrice(current,10);
                dof_12 = Matrice(current,11);
                dof_13 = Matrice(current,12);
                dof_14 = Matrice(current,13);
                dof_15 = Matrice(current,14);
                dof_16 = Matrice(current,15);
                dof_17 = Matrice(current,16);
                dof_18 = Matrice(current,17);
                dof_19 = Matrice(current,18);
                dof_20 = Matrice(current,19);
                

    /*            dof_1 = 0; dof_2 = 0; dof_3 = 0; dof_4 = 0;
                dof_5 = 0; dof_6 = 0; dof_7 = 0; dof_8 = 0;
                dof_9 = 0; dof_10 = 0; dof_11 = 0; dof_12 = 0;
                dof_13 = 0; dof_14 = 0; dof_15 = 0; dof_16 = 0;
                dof_17 = 0; dof_18 = 0; dof_19 = 0; dof_20 = 0;
    */
            // ROS dependant

            //palm's joints
                 my_joint_state.name[0] = "box_wrist_right_joint_1";
                 my_joint_state.position[0] = 0;
                 my_joint_state.name[1] = "box_wrist_right_joint_2";
                 my_joint_state.position[1] = 0;
                 my_joint_state.name[2] = "box_wrist_right_joint_3";
                 my_joint_state.position[2] = 0;


                my_joint_state.name[3] = "forth_hand_right_thumb_abd_joint";
                my_joint_state.position[3] = dof_2;
                my_joint_state.name[4] = "forth_hand_right_thumb_rot_joint";
                my_joint_state.position[4] = - dof_1;
                my_joint_state.name[5] = "forth_hand_right_thumb_inner_joint";
                my_joint_state.position[5] = dof_3;
                my_joint_state.name[6] = "forth_hand_right_thumb_outer_joint";
                my_joint_state.position[6] = dof_4;     

            //index joints
                my_joint_state.name[7] = "forth_hand_right_index_abd_joint";
                my_joint_state.position[7] = dof_5;
                my_joint_state.name[8] = "forth_hand_right_index_inner_joint";
                my_joint_state.position[8] = dof_6;
                my_joint_state.name[9] = "forth_hand_right_index_middle_joint";
                my_joint_state.position[9] = dof_7;
                my_joint_state.name[10] = "forth_hand_right_index_outer_joint";
                my_joint_state.position[10] = dof_8;


            //middle joints
                my_joint_state.name[11] = "forth_hand_right_middle_abd_joint";
                my_joint_state.position[11] = dof_9;
                my_joint_state.name[12] = "forth_hand_right_middle_inner_joint";
                my_joint_state.position[12] = dof_10;
                my_joint_state.name[13] = "forth_hand_right_middle_middle_joint";
                my_joint_state.position[13] = dof_11;
                my_joint_state.name[14] = "forth_hand_right_middle_outer_joint";
                my_joint_state.position[14] = dof_12;


            //ring joints
                my_joint_state.name[15] = "forth_hand_right_ring_abd_joint";
                my_joint_state.position[15] = dof_13;
                my_joint_state.name[16] = "forth_hand_right_ring_inner_joint";
                my_joint_state.position[16] = dof_14;
                my_joint_state.name[17] = "forth_hand_right_ring_middle_joint";
                my_joint_state.position[17] = dof_15;
                my_joint_state.name[18] = "forth_hand_right_ring_outer_joint";
                my_joint_state.position[18] = dof_16;
                
                

            //little's joints
                my_joint_state.name[19] = "forth_hand_right_little_abd_joint";
                my_joint_state.position[19] = dof_17;
                my_joint_state.name[20] = "forth_hand_right_little_inner_joint";
                my_joint_state.position[20] = dof_18;
                my_joint_state.name[21] = "forth_hand_right_little_middle_joint";
                my_joint_state.position[21] = dof_19;
                my_joint_state.name[22] = "forth_hand_right_little_outer_joint";
                my_joint_state.position[22] = dof_20;
            


            my_joint_state.header.stamp=ros::Time::now();
            pub_joints.publish(my_joint_state);

            current++;
            if (current > (campioni - 1)) {current = 0;} 
            //sleep(1);
    		usleep(33400);
            
                        
    } // end while(1)
    return 0;
}//fine main
