// Arduino waits for someone who had published in toggle_led topic and then blinks
// led attached at 13 pin.

#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <Servo.h>


namespace CameraTools
{
class Servocontrol
{
  public:
    Servocontrol(int servoX, int servoY): sub("/Servocontrol", &CameraTools::messageCallback,this){
        pos = 0;
        XServo.attach(servoX);
        YServo.attach(servoY);
        nh_.initNode();
        nh_.subscribe(sub);
    }

    void listening(){
      nh_.spinOnce();
    }

    void messageCallback( const std_msgs::String &msg){
      digitalWrite(13, HIGH);
      for (pos = 0; pos <= 360; pos++){
        XServo.write(pos);
        delay(15);
      }
        for (pos = 360; pos > 0; pos--){
        XServo.write(pos);
        delay(15);
      }
      digitalWrite(13, LOW);
    }

  private:
    ros::NodeHandle nh_;
    ros::Subscriber <std_msgs::String,CameraTools::Servocontrol> sub;
    //ros::Subscriber <std_msgs::String> sub;
    Servo XServo;
    Servo YServo;
    int pos;
};
}
  CameraTools::Servocontrol controller(9,10);

void setup()
{
;
  pinMode(13, OUTPUT);
}

void loop()
{
  controller.listening();
}
