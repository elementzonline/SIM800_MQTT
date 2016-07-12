#include "GSM_MQTT.h"
#include <SoftwareSerial.h>
String MQTT_HOST = "test.mosquitto.org";
/*
   MQTT host address
*/
String MQTT_PORT = "1883";
/*
   MQTT port
*/
SoftwareSerial mySerial(10, 11); // RX, TX
/*
 * Software Serial, through which mqtt event log is printed
 */
void GSM_MQTT::OnConnect(void)
{
  /*
     This function is called when mqqt connection is established.
     put your subscription publish codes here.
  */
  /*    void subscribe(char DUP, unsigned int MessageID, char *SubTopic, char SubQoS);
          DUP       :This flag is set when the client or server attempts to re-deliver a SUBSCRIBE message
                    :This applies to messages where the value of QoS is greater than zero (0)
                    :Possible values (0,1)
                    :Default value 0
          Message ID:The Message Identifier (Message ID) field
                    :Used only in messages where the QoS levels greater than 0 (SUBSCRIBE message is at QoS =1)
          SubTopic  :Topic names to which  subscription is needed
          SubQoS    :QoS level at which the client wants to receive messages
                    :Possible values (0,1,2)
                    :Default value 0
  */
  subscribe(0, _generateMessageID(), "SampleTopic", 1);

  
  /*  void publish(char DUP, char Qos, char RETAIN, unsigned int MessageID, char *Topic, char *Message);
      DUP       :This flag is set when the client or server attempts to re-deliver a PUBLISH message
                :This applies to messages where the value of QoS is greater than zero (0)
                :Possible values (0,1)
                :Default value 0
      QoS       :Quality of Service
                :This flag indicates the level of assurance for delivery of a PUBLISH message
                :Possible values (0,1,2)
                :Default value 0
      RETAIN    :if the Retain flag is set (1), the server should hold on to the message after it has been delivered to the current subscribers.
                :When a new subscription is established on a topic, the last retained message on that topic is sent to the subscriber
                :Possible values (0,1)
                :Default value 0
      Message ID:The Message Identifier (Message ID) field
                :Used only in messages where the QoS levels greater than 0
      Topic     :Publishing topic
      Message   :Publishing Message
  */
//  publish(0, 0, 0, _generateMessageID(), "SampleTopic", "Hello");

}
void GSM_MQTT::OnMessage(char *Topic, int TopicLength, char *Message, int MessageLength)
{
  /*
    This function is called whenever a message received from subscribed topics
    put your subscription publish codes here.
  */

  /*
     Topic        :Name of the topic from which message is coming
     TopicLength  :Number of characters in topic name
     Message      :The containing array
     MessageLength:Number of characters in message
  */
  mySerial.println(TopicLength);
  mySerial.println(Topic);
  mySerial.println(MessageLength);
  mySerial.println(Message);

}
GSM_MQTT MQTT(20);
/*
   20 is the keepalive duration in seconds
*/

void setup()
{
  // initialize mqtt:
  // GSM modem should be connected to Hardware Serial
  MQTT.begin();
  
  /*
     You can write your code here
  */

}
void loop()
{

  /*
     You can write your code here
  */

  MQTT.processing();
}

