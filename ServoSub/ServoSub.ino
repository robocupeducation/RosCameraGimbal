// Arduino waits for someone who had published in toggle_led topic and then blinks
// led attached at 13 pin.

#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <Servo.h>

ros::NodeHandle  nh;
Servo XServo;  // crea el objeto servo
int pos = 0;    // posicion del servo

void messageCb( const std_msgs::String &msg){
  // digitalWrite(13, HIGH-digitalRead(13));   // blink the led
  digitalWrite(13, HIGH);
  for (pos = 0; pos <= 180; pos++){
    myservo.write(pos);              
    delay(15);                       
  }
    for (pos = 180; pos > 0; pos--){
    myservo.write(pos);              
    delay(15);                       
  }
  digitalWrite(13, LOW);
}


// void messageCb( const std_msgs::String &msg){
//   // digitalWrite(13, HIGH-digitalRead(13));   // blink the led
//   digitalWrite(13, HIGH);
//   delay(1000);
//   digitalWrite(13, LOW);
// }

ros::Subscriber<std_msgs::String> sub("/Servocontrol", messageCb );

void setup()
{
  pinMode(13, OUTPUT);
  XServo.attach(9);
  nh.initNode();
  nh.subscribe(sub);
}

void loop()
{
  nh.spinOnce();
}
