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

#define UART_BUFFER_LENGTH 300    //Maximum length allowed for UART data
#define TOPIC_BUFFER_LENGTH 50    //Maximum length allowed Topic
#define MESSAGE_BUFFER_LENGTH 250  //Maximum length allowed data

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

// QoS value bit 2 bit 1 Description
//   0       0       0   At most once    Fire and Forget         <=1
//   1       0       1   At least once   Acknowledged delivery   >=1
//   2       1       0   Exactly once    Assured delivery        =1
//   3       1       1   Reserved
#define DUP_Mask      8   // Duplicate delivery   Only for QoS>0
#define QoS_Mask      6   // Quality of Service
#define QoS_Scale     2   // (()&QoS)/QoS_Scale
#define RETAIN_Mask   1   // RETAIN flag

#define User_Name_Flag_Mask  128
#define Password_Flag_Mask   64
#define Will_Retain_Mask     32
#define Will_QoS_Mask        24
#define Will_QoS_Scale       8
#define Will_Flag_Mask       4
#define Clean_Session_Mask   2

#define DISCONNECTED          0
#define CONNECTED             1
#define NO_ACKNOWLEDGEMENT  255

class GSM_MQTT
{
  public:
    volatile bool TCP_Flag = false;
    volatile char GSM_ReplyFlag;
    char reply[10];
    volatile bool pingFlag = false;
    volatile char tcpATerrorcount = 0;
    volatile bool MQTT_Flag = false;
    volatile int ConnectionAcknowledgement = NO_ACKNOWLEDGEMENT ;
    volatile int PublishIndex = 0;
    char Topic[TOPIC_BUFFER_LENGTH];
    volatile int TopicLength = 0;
    char Message[MESSAGE_BUFFER_LENGTH];
    volatile int MessageLength = 0;
    volatile int MessageFlag = false;
    volatile char modemStatus = 0;
    volatile uint32_t index = 0;
    volatile uint32_t length = 0, lengthLocal = 0;

    char inputString[UART_BUFFER_LENGTH]; 

    GSM_MQTT(unsigned long KeepAlive);
    void begin(void);
    void connect(char *ClientIdentifier, char UserNameFlag, char PasswordFlag, char *UserName, char *Password, char CleanSession, char WillFlag, char WillQoS, char WillRetain, char *WillTopic, char *WillMessage);
    void publish(char DUP, char Qos, char RETAIN, unsigned int MessageID, char *Topic, char *Message);
    void subscribe(char DUP, unsigned int MessageID, char *SubTopic, char SubQoS);
    void unsubscribe(char DUP, unsigned int MessageID, char *SubTopic);
    void disconnect(void);
    void processing(void);
    bool available(void);

    void AutoConnect(void);
    void OnConnect(void);
    void OnMessage(char *Topic, int TopicLength, char *Message, int MessageLength);

    void publishACK(unsigned int MessageID);
    void publishREC(unsigned int MessageID);
    void publishREL(char DUP, unsigned int MessageID);
    void publishCOMP(unsigned int MessageID);

    void printMessageType(uint8_t Message);
    void printConnectAck(uint8_t Ack);
    char sendATreply(char *command, char *replystr, unsigned long waitms);

  private:
    volatile unsigned int _LastMessaseID = 0;
    volatile char _ProtocolVersion = 3;
    volatile unsigned long _PingPrevMillis = 0;
    volatile char _tcpStatus = 0;
    volatile char _tcpStatusPrev = 0;
    volatile unsigned long _KeepAliveTimeOut;

    void _sendUTFString(char *string);
    void _sendLength(int len);
    void _ping(void);
    void _tcpInit(void);
    char _sendAT(char *command, unsigned long waitms);
    unsigned int _generateMessageID(void);
};
#endif /* GSM_MQTT_H_ */
