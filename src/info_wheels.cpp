//Manuel Esteban Contreras Betancourt
//manuel.contreras@unipamplona.edu.co
//Incluyendo librerias


#include <ros/ros.h>
#include "geometry_msgs/Twist.h"
#include <roly_v2/info_wheels.h>
#define R 0.106478
#define L 0.14


float wheel_rigth=0.0;
float wheel_left=0.0;

float v=0.0;
float w=0.0;


void info (const geometry_msgs::TwistConstPtr& wheels){

  v=wheels->linear.x;
  w=wheels->angular.z;

  wheel_rigth= (2*v + w*L)/(2*R);
  wheel_left=  (2*v - w*L)/(2*R);




  //printf("%f \n",wheel_rigth );

}




int main(int argc, char** argv)  
{

  //geometry_msgs::Twist msg_1,msg_2;
  roly_v2::info_wheels msg;


  ros::init(argc, argv, "Info_Wheels");

  ros::start();//se hace la comunicacion con el nodo maestro (roscore)
   ROS_INFO("File %s compiled on %s %s.",__FILE__, __DATE__, __TIME__);

   //creamos un nodo
   ros::NodeHandle info_wheels;

   //Creamos un topico para publicar la posicion del falcon en /cmd_vel
   ros::Publisher  pub = info_wheels.advertise<roly_v2::info_wheels>("/Info_Wheels", 0);
    

    //Se crea un topico que suscriba la posicion del falcon en el nodo (falcon_node)

    ros::Subscriber suscriber = info_wheels.subscribe("/cmd_vel",0, info);
    

    while(info_wheels.ok())
    {
      
      msg.wheel_rigth=wheel_rigth;
      msg.wheel_left=wheel_left;
      
      pub.publish(msg);

      ros::spinOnce();

    }
 
    
}
