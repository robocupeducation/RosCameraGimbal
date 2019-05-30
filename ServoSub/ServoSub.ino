// Arduino waits for someone who had published in toggle_led topic and then blinks
// led attached at 13 pin.

#include <ros.h>
#include <std_msgs/Byte.h>
#include <std_msgs/Empty.h>
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

    void messageCallback( const std_msgs::Byte &msg){
      digitalWrite(13, HIGH);
      for (pos = 0; pos <= 180; pos++){
        XServo.write(pos);
        delay(15);
      }
        for (pos = 180; pos > 0; pos--){
        XServo.write(pos);
        delay(15);
      }
      digitalWrite(13, LOW);
    }

  private:
    ros::NodeHandle nh_;
    ros::Subscriber <std_msgs::Byte,CameraTools::Servocontrol> sub;
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
