/*
  MQTT.h - Library for GSM MQTT Client.
  Created by Nithin K. Kurian, Dhanish Vijayan, Elementz Engineers Guild Pvt. Ltd, July 2, 2016.
  Released into the public domain.
*/
#ifndef GSM_MQTT_H_
#define GSM_MQTT_H_

//Arduino toolchain header, version dependent
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "pins_arduino.h"

#include <avr/pgmspace.h>

// ######################################################################################################################
#define CONNECT     1   //Client request to connect to Server                Client          Server
#define CONNACK     2   //Connect Acknowledgment                             Server/Client   Server/Client
#define PUBLISH     3   //Publish message                                    Server/Client   Server/Client
#define PUBACK      4   //Publish Acknowledgment                             Server/Client   Server/Client
#define PUBREC      5   //Publish Received (assured delivery part 1)         Server/Client   Server/Client
#define PUBREL      6   //Publish Release (assured delivery part 2)          Server/Client   Server/Client
#define PUBCOMP     7   //Publish Complete (assured delivery part 3)         Server/Client   Server/Client
#define SUBSCRIBE   8   //Client Subscribe request                           Client          Server
#define SUBACK      9   //Subscribe Acknowledgment                           Server          Client
#define UNSUBSCRIBE 10  //Client Unsubscribe request                         Client          Server
#define UNSUBACK    11  //Unsubscribe Acknowledgment                         Server          Client
#define PINGREQ     12  //PING Request                                       Client          Server
#define PINGRESP    13  //PING Response                                      Server          Client
#define DISCONNECT  14  //Client is Disconnecting                            Client          Server

//MessageTypeStr[CONNECT]     = "Client request to connect to Server"
//MessageTypeStr[CONNACK]     = "Connect Acknowledgment"
//MessageTypeStr[PUBLISH]     = "Publish message"
//MessageTypeStr[PUBACK]      = "Publish Acknowledgment"
//MessageTypeStr[PUBREC]      = "Publish Received (assured delivery part 1)"
//MessageTypeStr[PUBREL]      = "Publish Release (assured delivery part 2)"
//MessageTypeStr[PUBCOMP]     = "Publish Complete (assured delivery part 3)"
//MessageTypeStr[SUBSCRIBE]   = "Client Subscribe request"
//MessageTypeStr[SUBACK]      = "Subscribe Acknowledgment"
//MessageTypeStr[UNSUBSCRIBE] = "Client Unsubscribe request"
//MessageTypeStr[UNSUBACK]    = "Unsubscribe Acknowledgment"
//MessageTypeStr[PINGREQ]     = "PING Request"
//MessageTypeStr[PINGRESP]    = "PING Response"
//MessageTypeStr[DISCONNECT]  = "Client is Disconnecting"
//The main class of MQTT library functions

// QoS value bit 2 bit 1 Description
//   0       0       0   At most once    Fire and Forget         <=1
//   1       0       1   At least once   Acknowledged delivery   >=1
//   2       1       0   Exactly once    Assured delivery        =1
//   3       1       1   Reserved
#define DUP_Mask      8   // Duplicate delivery   Only for QoS>0
#define QoS_Mask      6   // Quality of Service
#define QoS_Scale     2   // (()&QoS)/QoS_Scale
#define RETAIN_Mask   1   // RETAIN flag

//#define ProtocolName    "MQIsdp"
//#define ProtocolVersion   3

#define User_Name_Flag_Mask  128
#define Password_Flag_Mask   64
#define Will_Retain_Mask     32
#define Will_QoS_Mask        24
#define Will_QoS_Scale       8
#define Will_Flag_Mask       4
#define Clean_Session_Mask   2

//CONNACKDict=dict()
//CONNACKDict[0]="Connection Accepted"
//CONNACKDict[1]="Connection Refused: unacceptable protocol version"
//CONNACKDict[2]="Connection Refused: identifier rejected"
//CONNACKDict[3]="Connection Refused: server unavailable"
//CONNACKDict[4]="Connection Refused: bad user name or password"
//CONNACKDict[5]="Connection Refused: not authorized"

#define DISCONNECTED          0
#define CONNECTED             1
#define NO_ACKNOWLEDGEMENT  255   

class GSM_MQTT
{
  public:
    volatile bool TCP_Flag = false;
    volatile bool MQTT_Flag = false;
    volatile int PublishIndex = 0;
    volatile int MessageFlag = false;
    volatile unsigned int LastMessaseID = 0;
    volatile int ConnectionAcknowledgement =NO_ACKNOWLEDGEMENT ;
//  char ProtocolName[7]="MQIsdp";
  volatile char ProtocolVersion=3;
    char Topic[50];
    char Message[50];
    volatile int TopicLength=0;
    volatile int MessageLength=0;
    volatile unsigned long PingPrevMillis = 0;
    volatile bool pingFlag=false;
    volatile char GSM_ReplyFlag;
    char reply[10];
      volatile char modemStatus=0;
        volatile char tcpStatus=0;
    //    volatile uint32_t length = 0;
    volatile unsigned long KeepAliveTimeOut;
    GSM_MQTT(unsigned long KeepAlive);
    void begin(void);

    void connect(char *ClientIdentifier, char UserNameFlag, char PasswordFlag, char WillRetain, char WillQoS, char WillFlag, char CleanSession, char *WillTopic, char *WillMessage, char *UserName, char *Password);
    void publish(char DUP, char Qos, char RETAIN, unsigned int MessageID, char *Topic, char *Message);
    void publishACK(unsigned int MessageID);
    void publishREC(unsigned int MessageID);
    void publishREL(char DUP, unsigned int MessageID);
    void publishCOMP(unsigned int MessageID);
    void subscribe(char DUP, unsigned int MessageID, char *SubTopic, char SubQoS);
    void unsubscribe(char DUP, unsigned int MessageID, char *SubTopic);
    void disconnect(void);
    void sendUTFString(char *string);
    void sendLength(int len);
    void ping(void);
    void printMessageType(uint8_t Message);
    void printConnectAck(uint8_t Ack);
    void OnConnect(void);
    void OnMessage(char *Topic,int TopicLength,char *Message,int MessageLength);

    void tcpInit(void);
    char sendAT(char *command,unsigned long waitms);
    char sendATreply(char *command, char *replystr,unsigned long waitms);
    unsigned int generateMessageID(void);
    void processing(void);
  private:

};
void KeepAlive(void);
#endif /* GSM_MQTT_H_ */
