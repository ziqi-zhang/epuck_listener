#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/Char.h"
#include "CommThread.h"

CommThread* commThread;
geometry_msgs::Twist preTwist;

bool goUpNow, goDownNow, goLeftNow, goRightNow, stopNow;
bool bLed0On, bLed1On, bLed2On, bLed3On, bLed4On, bLed5On, bLed6On, bLed7On, bLed8On, bLed9On;

void keyVelCallback(const geometry_msgs::Twist& twist)
{
//  if(twist.linear.x!=preTwist.linear.x || twist.angular.z!=preTwist.angular.z)
//    ROS_INFO("Heard message from keyboard x=%f z=%f", twist.linear.x, twist.angular.z);
//  if(twist.linear.x>0 && preTwist.linear.x<=0)
//    commThread->goUpSlot(300);
//  else if(twist.linear.x<0 && preTwist.linear.x>=0)
//    commThread->goDownSlot(300);
//  else if(twist.linear.x==0 && preTwist.linear.x!=0)
//    commThread->stopSlot();

//  if(twist.angular.z>0&&preTwist.angular.z<=0)
//    commThread->goLeftSlot(300);
//  else if(twist.angular.z<0&&preTwist.angular.z>=0)
//    commThread->goRightSlot(300);
//  else if(twist.angular.z==0&&preTwist.angular.z!=0)
//    commThread->stopSlot();


  if(twist.linear.y!=preTwist.linear.y || twist.angular.z!=preTwist.angular.z)
    ROS_INFO("Heard message from keyboard y=%f z=%f", twist.linear.y, twist.angular.z);

  if(twist.linear.y!=0 && twist.angular.z!=0){
    ROS_ERROR("Both y and z angular speed are not 0, can't execute");
    return;
  }

  if(twist.linear.y!=preTwist.linear.y){
    int speed = std::min(abs(twist.linear.y)*100, 1000);
    if(twist.linear.y>0){
      commThread->goUpSlot(speed);
    }
    else if(twist.linear.y<0){
//      commThread->stopSlot();
      commThread->goDownSlot(speed);
    }
    else if(twist.linear.y==0 && preTwist.linear.y!=0)
      commThread->stopSlot();
  }
  if(twist.angular.z!=preTwist.angular.z){
    int speed = std::max(abs(twist.angular.z)*100, 1000);
    if(twist.angular.z>0){
//      commThread->stopSlot();
      commThread->goLeftSlot(speed);
    }
    else if(twist.angular.z<0){
//      commThread->stopSlot();
      commThread->goRightSlot(speed);
    }
    else if(twist.angular.z==0 && preTwist.angular.z!=0)
      commThread->stopSlot();
  }

  preTwist = twist;
}

void keyCmdCallback(const std_msgs::Char& c){
  switch (c.data) {
  case 'p':
    //ROS_INFO("Received char %c", c.data);
    if(bLed0On){
      commThread->sendUpdateLed0(Qt::Unchecked);
      bLed0On = false;
    }
    else{
      commThread->sendUpdateLed0(Qt::Checked);
      bLed0On = true;
    }
    break;
  case 'o':
    //ROS_INFO("Received char %c", c.data);
    if(bLed1On){
      commThread->sendUpdateLed1(Qt::Unchecked);
      bLed1On = false;
    }
    else{
      commThread->sendUpdateLed1(Qt::Checked);
      bLed1On = true;
    }
    break;
  case 'i':
    //ROS_INFO("Received char %c", c.data);
    if(bLed2On){
      commThread->sendUpdateLed2(Qt::Unchecked);
      bLed2On = false;
    }
    else{
      commThread->sendUpdateLed2(Qt::Checked);
      bLed2On = true;
    }
    break;
  case 'u':
    //ROS_INFO("Received char %c", c.data);
    if(bLed3On){
      commThread->sendUpdateLed3(Qt::Unchecked);
      bLed3On = false;
    }
    else{
      commThread->sendUpdateLed3(Qt::Checked);
      bLed3On = true;
    }
    break;




  case 'h':
    //ROS_INFO("Received char %c", c.data);
    if(bLed4On){
      commThread->sendUpdateLed4(Qt::Unchecked);
      bLed4On = false;
    }
    else{
      commThread->sendUpdateLed4(Qt::Checked);
      bLed4On = true;
    }
    break;
  case 'j':
    //ROS_INFO("Received char %c", c.data);
    if(bLed5On){
      commThread->sendUpdateLed5(Qt::Unchecked);
      bLed5On = false;
    }
    else{
      commThread->sendUpdateLed5(Qt::Checked);
      bLed5On = true;
    }
    break;
  case 'k':
    //ROS_INFO("Received char %c", c.data);
    if(bLed6On){
      commThread->sendUpdateLed6(Qt::Unchecked);
      bLed6On = false;
    }
    else{
      commThread->sendUpdateLed6(Qt::Checked);
      bLed6On = true;
    }
    break;
  case 'l':
    //ROS_INFO("Received char %c", c.data);
    if(bLed7On){
      commThread->sendUpdateLed7(Qt::Unchecked);
      bLed7On = false;
    }
    else{
      commThread->sendUpdateLed7(Qt::Checked);
      bLed7On = true;
    }
    break;

  case 'n':
    //ROS_INFO("Received char %c", c.data);
    if(bLed8On){
      commThread->sendUpdateLed8(Qt::Unchecked);
      bLed8On = false;
    }
    else{
      commThread->sendUpdateLed8(Qt::Checked);
      bLed8On = true;
    }
    break;

  case 'm':
    //ROS_INFO("Received char %c", c.data);
    if(bLed9On){
      commThread->sendUpdateLed9(Qt::Unchecked);
      bLed9On = false;
    }
    else{
      commThread->sendUpdateLed9(Qt::Checked);
      bLed9On = true;
    }
    break;

  default:
    break;
  }

}

void disconnect(){
  ROS_INFO("Disconnect");
  commThread->getSensors(false);
  commThread->getCamera(false);
  commThread->abortThread = true;
  commThread->wait();
}

int main(int argc, char **argv)
{
  ROS_INFO("HEllo\n");
  ros::init(argc, argv, "epuck_listener");
  ros::NodeHandle nh("~");
  std::string name, port;
  commThread = new CommThread();
  ROS_INFO("Arg number is %d", argc);
  for(int i=0; i<argc; i++)
    ROS_INFO("%s", argv[i]);

  if(argc>1){
    ROS_INFO("Port %s", argv[1]);
    while(!commThread->connectionBuild)
      commThread->initConnection(argv[1]);
  }
  else{
    ROS_ERROR("Fail to get port");
  }
  //commThread->goUpSlot(300);



  ros::Subscriber key_vel_sub = nh.subscribe("/key_vel", 1000, keyVelCallback);
  ros::Subscriber key_cmd_sub = nh.subscribe("/key_cmd", 10, keyCmdCallback);

  ros::spin();

  return 0;
}
