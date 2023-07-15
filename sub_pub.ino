#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/UInt16.h>

#define button_pin 2
#define led_pin 13

bool last_reading;
long last_debounce_time = 0;
long debounce_delay = 50;
bool published = true;

ros::NodeHandle node_handle;

std_msgs::String button_msg;
std_msgs::UInt16 led_msg;

void subscriberCallback(const std_msgs::UInt16& led_msg) {
  if (led_msg.data  == 1) {
    digitalWrite(led_pin, HIGH);
  } else {
    digitalWrite(led_pin, LOW);
  }
}

ros::Publisher button_publisher("button_press", &button_msg);
ros::Subscriber<std_msgs::UInt16> led_subscriber("toggle_led", &subscriberCallback);

void setup()
{
  pinMode(led_pin, OUTPUT);
  pinMode(button_pin, INPUT_PULLUP);

  node_handle.initNode();
  node_handle.advertise(button_publisher);
  node_handle.subscribe(led_subscriber);

  //The button is a normally button
  last_reading = ! digitalRead(button_pin);
}

void loop()
{
  bool reading = ! digitalRead(button_pin);
  if (last_reading != reading) {
    last_debounce_time = millis();
    published = false;
  }

  //if the button value has not changed for the debounce delay, we know its stable
  if ( !published && (millis() - last_debounce_time)  > debounce_delay) {
    if (reading)
      button_msg.data = "PRESS";
    else
      button_msg.data = "NOT pressed";
    button_publisher.publish( &button_msg );
    published = true;
  }

  last_reading = reading;
  node_handle.spinOnce();
}
