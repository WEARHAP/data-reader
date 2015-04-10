
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
float dof_1,dof_2,dof_3,dof_4,dof_5,dof_6,dof_7,dof_8,dof_9,dof_10,dof_11,dof_12,dof_13,dof_14,dof_15;
int pose = 144;


int main(int argc, char** argv)
{
    ros::init(argc, argv, "joint_publisher");
    ros::NodeHandle n;


    // Data loading

        ros::Publisher pub_joints = n.advertise<sensor_msgs::JointState>("/joint_states", 1000); 
        sensor_msgs::JointState my_joint_state;
        my_joint_state.name.resize(23);
        my_joint_state.position.resize(23);

        int row = pose;
        int column = 15;
        int k;

        MatrixXf MatC(15,column);
    
        FILE *joints_data2=fopen("/home/centropiaggio/catkin_ws/src/pisa_hand_publisher/datiPosture/mat_C.txt", "r");
    
        for(k=0; k<15; k++ ){
            fscanf(joints_data2, "%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n", &MatC(k,0),&MatC(k,1),&MatC(k,2),&MatC(k,3),&MatC(k,4),&MatC(k,5),&MatC(k,6),&MatC(k,7),&MatC(k,8),&MatC(k,9),&MatC(k,10),&MatC(k,11),&MatC(k,12),&MatC(k,13),&MatC(k,14));
        }
        fclose(joints_data2);



        MatrixXf Matmu(15,1);
    
        FILE *joints_pose1=fopen("/home/centropiaggio/catkin_ws/src/pisa_hand_publisher/datiPosture/vet_mu.txt", "r");
    
        for(k=0; k<15; k++ ){
            fscanf(joints_pose1, "%f\n", &Matmu(k,0));
        }
        fclose(joints_pose1);



        int data_row = 3200;
        //int data_row = 30;
        int data_column = 20;

        MatrixXf Matrice(data_row,data_column);
    
        FILE *joints_data=fopen("/home/centropiaggio/catkin_ws/src/pisa_hand_publisher/seq0.txt", "r");
    
        for(k=0; k<data_row; k++ ){
            fscanf(joints_data, "%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n", &Matrice(k,0),&Matrice(k,1),&Matrice(k,2),&Matrice(k,3),&Matrice(k,4),&Matrice(k,5),&Matrice(k,6),&Matrice(k,7),&Matrice(k,8),&Matrice(k,9),&Matrice(k,10),&Matrice(k,11),&Matrice(k,12),&Matrice(k,13),&Matrice(k,14),&Matrice(k,15),&Matrice(k,16),&Matrice(k,17),&Matrice(k,18),&Matrice(k,19));
        }
        fclose(joints_data);




        //std::cout<<MatC<<std::endl;

        //std::cout<<Matmu<<std::endl;

        //std::cout<<MatCov<<std::endl;

    //ros::init(argc, argv, "joint_publisher");
    //ros::NodeHandle n;

    //definizioni per Joint States
    /*ros::Publisher pub_joints = n.advertise<sensor_msgs::JointState>("/joint_states", 1000); 
    sensor_msgs::JointState my_joint_state;
    my_joint_state.name.resize(23);
    my_joint_state.position.resize(23);*/

// ROS dependant // 

    dof_1 = 0; dof_2 = 0; dof_3 = 0; dof_4 = 0; dof_5 = 0;
    dof_6 = 0; dof_7 = 0; dof_8 = 0; dof_9 = 0; dof_10 = 0;
    dof_11 = 0; dof_12 = 0; dof_13 = 0; dof_14 = 0; dof_15 = 0;

    //         //palm's joints
    //              my_joint_state.name[0] = "box_wrist_right_joint_1";
    //              my_joint_state.position[0] = 0;
    //              my_joint_state.name[1] = "box_wrist_right_joint_2";
    //              my_joint_state.position[1] = 0;
    //              my_joint_state.name[2] = "box_wrist_right_joint_3";
    //              my_joint_state.position[2] = 0;

    //             my_joint_state.name[3] = "pisa_hand_right_thumb_abd_joint";
    //             my_joint_state.position[3] = dof_1 ;
    //             my_joint_state.name[4] = "pisa_hand_right_thumb_rot_joint";
    //             my_joint_state.position[4] = dof_2 ;
    //             my_joint_state.name[5] = "pisa_hand_right_thumb_inner_joint";
    //             my_joint_state.position[5] = dof_3;
    //             my_joint_state.name[6] = "pisa_hand_right_thumb_outer_joint";
    //             my_joint_state.position[6] = dof_4;     

    //         //index joints
    //             my_joint_state.name[7] = "pisa_hand_right_index_abd_joint";
    //             my_joint_state.position[7] = dof_5;
    //             my_joint_state.name[8] = "pisa_hand_right_index_inner_joint";
    //             my_joint_state.position[8] = dof_6;
    //             my_joint_state.name[9] = "pisa_hand_right_index_middle_joint";
    //             my_joint_state.position[9] = dof_7;
    //             my_joint_state.name[10] = "pisa_hand_right_index_outer_joint";
    //             my_joint_state.position[10] = 0;


    //         //middle joints
    //             my_joint_state.name[11] = "pisa_hand_right_middle_abd_joint";
    //             my_joint_state.position[11] = 0;
    //             my_joint_state.name[12] = "pisa_hand_right_middle_inner_joint";
    //             my_joint_state.position[12] = dof_8;
    //             my_joint_state.name[13] = "pisa_hand_right_middle_middle_joint";
    //             my_joint_state.position[13] = dof_9;
    //             my_joint_state.name[14] = "pisa_hand_right_middle_outer_joint";
    //             my_joint_state.position[14] = 0;


    //         //ring joints
    //             my_joint_state.name[15] = "pisa_hand_right_ring_abd_joint";
    //             my_joint_state.position[15] = dof_10;
    //             my_joint_state.name[16] = "pisa_hand_right_ring_inner_joint";
    //             my_joint_state.position[16] = dof_11;
    //             my_joint_state.name[17] = "pisa_hand_right_ring_middle_joint";
    //             my_joint_state.position[17] = dof_12;
    //             my_joint_state.name[18] = "pisa_hand_right_ring_outer_joint";
    //             my_joint_state.position[18] = 0;
                
                

    //         //little's joints
    //             my_joint_state.name[19] = "pisa_hand_right_little_abd_joint";
    //             my_joint_state.position[19] = dof_13;
    //             my_joint_state.name[20] = "pisa_hand_right_little_inner_joint";
    //             my_joint_state.position[20] = dof_14;
    //             my_joint_state.name[21] = "pisa_hand_right_little_middle_joint";
    //             my_joint_state.position[21] = dof_15;
    //             my_joint_state.name[22] = "pisa_hand_right_little_outer_joint";
    //             my_joint_state.position[22] = 0;
                
                     
             
    
    //     my_joint_state.header.stamp=ros::Time::now();
    //     pub_joints.publish(my_joint_state);
    //     ros::spinOnce();
    //     sleep(2);
    
// ROS dependant

        //int row = campioni;
        //int column = 20;

        // int campioni = 44;
        // column = campioni;

        // MatrixXf Matrice(row,column);
    
        // FILE *joints_data=fopen("/home/centropiaggio/catkin_ws/src/pisa_hand_publisher/data.txt", "r");
    
        // for(k=0; k<row; k++ ){
        //     fscanf(joints_data, "%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n", &Matrice(k,0),&Matrice(k,1),&Matrice(k,2),&Matrice(k,3),&Matrice(k,4),&Matrice(k,5),&Matrice(k,6),&Matrice(k,7),&Matrice(k,8),&Matrice(k,9),&Matrice(k,10),&Matrice(k,11),&Matrice(k,12),&Matrice(k,13),&Matrice(k,14));
        // }
        // fclose(joints_data);


       

    // INIZIO CICLO WHILE //

        /*getchar();*/

        float TA,TR,TM,TI,IA,IM,IP,IF,MA,MM,MP,MF,RA,RM,RP,RF,LA,LM,LP,LF; // Pisa Hand Dofs- F are the outer joints

        int current = 0;
        //ros::Rate prova(100);
    //while (current < campioni){
    while (1){

            //     if(current == 0){

            //         dof_1 = 0; dof_2 = 0; dof_3 = 0; dof_4 = 0; dof_5 = 0;
            //         dof_6 = 0; dof_7 = 0; dof_8 = 0; dof_9 = 0; dof_10 = 0;
            //         dof_11 = 0; dof_12 = 0; dof_13 = 0; dof_14 = 0; dof_15 = 0;

            //         // ROS dependant

            // //palm's joints
            //      my_joint_state.name[0] = "box_wrist_right_joint_1";
            //      my_joint_state.position[0] = 0;
            //      my_joint_state.name[1] = "box_wrist_right_joint_2";
            //      my_joint_state.position[1] = 0;
            //      my_joint_state.name[2] = "box_wrist_right_joint_3";
            //      my_joint_state.position[2] = 0;

            //     my_joint_state.name[3] = "pisa_hand_right_thumb_abd_joint";
            //     my_joint_state.position[3] = dof_1 ;
            //     my_joint_state.name[4] = "pisa_hand_right_thumb_rot_joint";
            //     my_joint_state.position[4] = dof_2 ;
            //     my_joint_state.name[5] = "pisa_hand_right_thumb_inner_joint";
            //     my_joint_state.position[5] = dof_3;
            //     my_joint_state.name[6] = "pisa_hand_right_thumb_outer_joint";
            //     my_joint_state.position[6] = dof_4;     

            // //index joints
            //     my_joint_state.name[7] = "pisa_hand_right_index_abd_joint";
            //     my_joint_state.position[7] = dof_5;
            //     my_joint_state.name[8] = "pisa_hand_right_index_inner_joint";
            //     my_joint_state.position[8] = dof_6;
            //     my_joint_state.name[9] = "pisa_hand_right_index_middle_joint";
            //     my_joint_state.position[9] = dof_7;
            //     my_joint_state.name[10] = "pisa_hand_right_index_outer_joint";
            //     my_joint_state.position[10] = 0;


            // //middle joints
            //     my_joint_state.name[11] = "pisa_hand_right_middle_abd_joint";
            //     my_joint_state.position[11] = 0;
            //     my_joint_state.name[12] = "pisa_hand_right_middle_inner_joint";
            //     my_joint_state.position[12] = dof_8;
            //     my_joint_state.name[13] = "pisa_hand_right_middle_middle_joint";
            //     my_joint_state.position[13] = dof_9;
            //     my_joint_state.name[14] = "pisa_hand_right_middle_outer_joint";
            //     my_joint_state.position[14] = 0;


            // //ring joints
            //     my_joint_state.name[15] = "pisa_hand_right_ring_abd_joint";
            //     my_joint_state.position[15] = dof_10;
            //     my_joint_state.name[16] = "pisa_hand_right_ring_inner_joint";
            //     my_joint_state.position[16] = dof_11;
            //     my_joint_state.name[17] = "pisa_hand_right_ring_middle_joint";
            //     my_joint_state.position[17] = dof_12;
            //     my_joint_state.name[18] = "pisa_hand_right_ring_outer_joint";
            //     my_joint_state.position[18] = 0;
                
                

            // //little's joints
            //     my_joint_state.name[19] = "pisa_hand_right_little_abd_joint";
            //     my_joint_state.position[19] = dof_13;
            //     my_joint_state.name[20] = "pisa_hand_right_little_inner_joint";
            //     my_joint_state.position[20] = dof_14;
            //     my_joint_state.name[21] = "pisa_hand_right_little_middle_joint";
            //     my_joint_state.position[21] = dof_15;
            //     my_joint_state.name[22] = "pisa_hand_right_little_outer_joint";
            //     my_joint_state.position[22] = 0;
            


            // my_joint_state.header.stamp=ros::Time::now();
            // pub_joints.publish(my_joint_state);

            // sleep(1);

            // current++;


            // }

        // Definizione della GUI sul terminale

        

        // std::cout<<"--------------------------------------------------"<<std::endl;
        // std::cout<<"--------------"<<"PISA HAND URDF"<<"--------------"<<std::endl;
        // std::cout<<"--"<<" Hand Model at 15 dofs[Santello et al.]"<<"--"<<std::endl;
        // std::cout<<"--------------------------------------------------"<<std::endl;
        // std::cout<<std::endl;
        // std::cout<<std::endl;

        // std::cout <<" 1 |Thumb abduction"<<std::endl;
        // std::cout <<" 2 |Thumb rotation"<<std::endl;
        // std::cout <<" 3 |Thumb metacarpal"<<std::endl;
        // std::cout <<" 4 |Thumb interphalangeal"<<std::endl;
        // std::cout <<" 5 |Index abduction"<<std::endl;
        // std::cout <<" 6 |Index metacarpal"<<std::endl;
        // std::cout <<" 7 |Index proximal"<<std::endl;
        // std::cout <<" 8 |Middle metacarpal"<<std::endl;
        // std::cout <<" 9 |Middle proximal"<<std::endl;
        // std::cout <<"10 |Ring abduction"<<std::endl;
        // std::cout <<"11 |Ring metacarpal"<<std::endl;
        // std::cout <<"12 |Ring proximal"<<std::endl;
        // std::cout <<"13 |Little abduction"<<std::endl;
        // std::cout <<"14 |Little metacarpal"<<std::endl;
        // std::cout <<"15 |Little proximal"<<std::endl;

        // int data_num;
        // std::cout<<"Declare the number of available measurements"<<std::endl;
        // std::cin>>data_num;

        // std::cout << "-----------------------------------------------"<<std::endl;
        // std::cout <<" Declare dof's type and value"<<std::endl;
        // std::cout << "-----------------------------------------------"<<std::endl;

        // VectorXf data(data_num);
        // VectorXf indice(data_num); 
        // for(k=0;k<data_num;k++){

        //     cout<<"Declare the dof type(the number) "<<endl;
        //     cin>>indice(k);
        //     cout<<"Declare the dof value(in degrees)"<<endl;
        //     cin>>data(k);
        // }

        ros::spinOnce();

        


                TA = -(180/pi)*Matrice(current,1)+90;
                TR = -(180/pi)*Matrice(current,0);
                //TM = Matrice(current,2);
                //TI = Matrice(current,3);
                //IA = Matrice(current,4);
                IM = (180/pi)*Matrice(current,5);
                IP = (180/pi)*Matrice(current,6);
                //IF = Matrice(current,7);
                //MA = Matrice(current,8);
                MM = (180/pi)*Matrice(current,9);
                MP = (180/pi)*Matrice(current,10);
                //MF = Matrice(current,11);
                //RA = Matrice(current,12);
                RM = (180/pi)*Matrice(current,13);
                RP = (180/pi)*Matrice(current,14);
                //RF = Matrice(current,15);
                //LA = Matrice(current,16);
                LM = (180/pi)*Matrice(current,17);
                LP = (180/pi)*Matrice(current,18);
                //LF = Matrice(current,19);

        float cov_diag = 0;
        float cov_out_diag = 0;
        int data_num = 10;


        // Covariance Matrix definition

        MatrixXf MatCov(data_num,data_num);
    
        for(int i=0; i<data_num; i++ ){
            for(int j=0;j<data_num;j++){

                if(i==j)
                    MatCov(i,j)=cov_diag;
                else
                    MatCov(i,j)=cov_out_diag;

            }
        }
        
        //std::cout<<"Covariance Matrix"<<std::endl;
        //std::cout<<MatCov<<std::endl;

       // for(k=0;k<3;k++){

       //      cout<<"indice: "<<indice[k]<<endl;
       //      cout<<"dato: "<<data[k]<<endl;
       //  }

        //std::cout<<data<<endl;
        //std::cout<<indice<<endl;
        
        // MatrixXf Hs(data_num,15);
        // for(int i=0;i<data_num;i++){
        //     for(int j=0;j<15;j++){
        //         if(j==(indice(i)-1)) 
        //             Hs(i,j)=1;
        //         else
        //             Hs(i,j)=0;
        //     }
        // }

        
        //std::cout<<"Selection Matrix"<<std::endl;
        //std::cout<<Hs<<std::endl;


        /*MatrixXf MatP(15,15);
        MatP = MatC.inverse() + Hs.transpose()*MatCov.inverse()*Hs;

        MatrixXf Pp(15,15);
        Pp = MatP.inverse();*/

        //std::cout<<Pp<<std::endl;

        VectorXf data(data_num);
        data<<TA,TR,IM,IP,MM,MP,RM,RP,LM,LP;

        VectorXf index(data_num);
        index<<1,2,6,7,8,9,11,12,14,15;


        MatrixXf Hs(data_num,15);
        for(int i=0;i<data_num;i++){
             for(int j=0;j<15;j++){
                if(j==(index(i)-1)) 
                     Hs(i,j)=1;
                 else
                     Hs(i,j)=0;
             }
         }

        MatrixXf Y(data_num,data_num);
        Y = Hs*MatC*Hs.transpose() + MatCov;

        MatrixXf YY(data_num,data_num);
        YY = Y.inverse();

        MatrixXf X_Map(15,15);
        X_Map = Matmu - MatC*Hs.transpose()*YY*(Hs*Matmu - data);

        // std::cout<<std::endl;
        // std::cout<<"Dofs mapping through synergyes "<<std::endl;

        //std::cout<<"X_MAP"<<std::endl;
        //std::cout<<X_Map<<std::endl;


                dof_1 = (pi/180)*X_Map(0);
                dof_2 = (pi/180)*X_Map(1);
                dof_3 = (pi/180)*X_Map(2);
                dof_4 = (pi/180)*X_Map(3);
                dof_5 = (pi/180)*X_Map(4);
                dof_6 = (pi/180)*X_Map(5);
                dof_7 = (pi/180)*X_Map(6);
                dof_8 = (pi/180)*X_Map(7);
                dof_9 = (pi/180)*X_Map(8);
                dof_10 = (pi/180)*X_Map(9);
                dof_11 = (pi/180)*X_Map(10);
                dof_12 = (pi/180)*X_Map(11);
                dof_13 = (pi/180)*X_Map(12);
                dof_14 = (pi/180)*X_Map(13);
                dof_15 = (pi/180)*X_Map(14);



        // Synergy algorith does the following values with in input a zeros sequence

        /*1.90735e-06
        7.24792e-05
        17.211
        27.1747
        20.3433
        -7.82013e-05
        0.000141144
        -3.05176e-05
        0.00012207
        -8.82784
        -0.000160217
        1.14441e-05
        -11.5043
        -0.000110626
        5.34058e-05 */

                // dof_1 = (pi/180)*X_Map(0);
                // dof_2 = (pi/180)*X_Map(1);
                // dof_3 = (pi/180)*(X_Map(2)-32.75);
                // dof_4 = (pi/180)*(X_Map(3)-55.64);
                // dof_5 = (pi/180)*(X_Map(4)-18.35);
                // dof_6 = (pi/180)*X_Map(5);
                // dof_7 = (pi/180)*X_Map(6);
                // dof_8 = (pi/180)*X_Map(7);
                // dof_9 = (pi/180)*X_Map(8);
                // dof_10 = (pi/180)*(X_Map(9)+16.25);
                // dof_11 = (pi/180)*X_Map(10);
                // dof_12 = (pi/180)*X_Map(11);
                // dof_13 = (pi/180)*(X_Map(12)+23.17);
                // dof_14 = (pi/180)*X_Map(13);
                // dof_15 = (pi/180)*X_Map(14);


                
                


            // ROS dependant

            //palm's joints
                 my_joint_state.name[0] = "box_wrist_right_joint_1";
                 my_joint_state.position[0] = 0;
                 my_joint_state.name[1] = "box_wrist_right_joint_2";
                 my_joint_state.position[1] = 0;
                 my_joint_state.name[2] = "box_wrist_right_joint_3";
                 my_joint_state.position[2] = 0;

                my_joint_state.name[3] = "pisa_hand_right_thumb_abd_joint";
                my_joint_state.position[3] = dof_1 ;
                my_joint_state.name[4] = "pisa_hand_right_thumb_rot_joint";
                my_joint_state.position[4] = dof_2 ;
                my_joint_state.name[5] = "pisa_hand_right_thumb_inner_joint";
                my_joint_state.position[5] = dof_3;
                my_joint_state.name[6] = "pisa_hand_right_thumb_outer_joint";
                my_joint_state.position[6] = dof_4;     

            //index joints
                my_joint_state.name[7] = "pisa_hand_right_index_abd_joint";
                my_joint_state.position[7] = dof_5;
                my_joint_state.name[8] = "pisa_hand_right_index_inner_joint";
                my_joint_state.position[8] = dof_6;
                my_joint_state.name[9] = "pisa_hand_right_index_middle_joint";
                my_joint_state.position[9] = dof_7;
                my_joint_state.name[10] = "pisa_hand_right_index_outer_joint";
                my_joint_state.position[10] = (2/3)*dof_7;


            //middle joints
                my_joint_state.name[11] = "pisa_hand_right_middle_abd_joint";
                my_joint_state.position[11] = 0;
                my_joint_state.name[12] = "pisa_hand_right_middle_inner_joint";
                my_joint_state.position[12] = dof_8;
                my_joint_state.name[13] = "pisa_hand_right_middle_middle_joint";
                my_joint_state.position[13] = dof_9;
                my_joint_state.name[14] = "pisa_hand_right_middle_outer_joint";
                my_joint_state.position[14] = (2/3)*dof_9;


            //ring joints
                my_joint_state.name[15] = "pisa_hand_right_ring_abd_joint";
                my_joint_state.position[15] = dof_10;
                my_joint_state.name[16] = "pisa_hand_right_ring_inner_joint";
                my_joint_state.position[16] = dof_11;
                my_joint_state.name[17] = "pisa_hand_right_ring_middle_joint";
                my_joint_state.position[17] = dof_12;
                my_joint_state.name[18] = "pisa_hand_right_ring_outer_joint";
                my_joint_state.position[18] = (2/3)*dof_12;
                
                

            //little's joints
                my_joint_state.name[19] = "pisa_hand_right_little_abd_joint";
                my_joint_state.position[19] = dof_13;
                my_joint_state.name[20] = "pisa_hand_right_little_inner_joint";
                my_joint_state.position[20] = dof_14;
                my_joint_state.name[21] = "pisa_hand_right_little_middle_joint";
                my_joint_state.position[21] = dof_15;
                my_joint_state.name[22] = "pisa_hand_right_little_outer_joint";
                my_joint_state.position[22] = (2/3)*dof_15;
            


            my_joint_state.header.stamp=ros::Time::now();
            pub_joints.publish(my_joint_state);

            current++;
            if (current > (data_row - 1)) {current = 0;} 
            //sleep(1);

            //prova.sleep();
            usleep(30000);
            
                        
    } // end while(1)



    
    return 0;
}//fine main
