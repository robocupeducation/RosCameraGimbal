// Arduino waits for someone who had published in toggle_led topic and then blinks
// led attached at 13 pin.

#include <ros.h>
#include <std_msgs/Byte.h>
#include <std_msgs/UInt8.h>
#include <Servo.h>


namespace CameraTools
{
class Servocontrol
{
  public:
    Servocontrol(): sub("/Servocontrol", &CameraTools::Servocontrol::messageCallback,this){
        pos = 0;
        nh_.initNode();
        nh_.subscribe(sub);
    }
    
    void startUp(int servoX, int servoY){
        XServo.attach(servoX);
        YServo.attach(servoY);
        XServo.write(90);
        YServo.write(0);
    }

    void listening(){
      nh_.spinOnce();
    }
    
    void moveServo(Servo servo,const std_msgs::UInt8 &msg){
      int grades = int(msg.data & 00111111);
      // Turn Rigth
      if(msg.data & 01000000 == 01000000){
        servo.write(90 + grades);
      }
      // Turn Left
      else{
        servo.write(90 - grades);
      }
    }

    void messageCallback( const std_msgs::UInt8 &msg){
      digitalWrite(13, HIGH);
      if (msg.data > 127){
          moveServo(XServo,msg);
      }else{
          moveServo(YServo,msg);
      }
      digitalWrite(13, LOW);
    }

  private:
    ros::NodeHandle nh_;
    ros::Subscriber <std_msgs::UInt8,CameraTools::Servocontrol> sub;
    Servo XServo;
    Servo YServo;
    int pos;
};
}

CameraTools::Servocontrol controller;

void setup()
{
  Serial.begin(57600);
  pinMode(13, OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  controller.startUp(9,10);
}

void loop()
{
  controller.listening();
}
