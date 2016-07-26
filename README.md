# SIM800_MQTT

#AutoConnect CallBack function
* Use this function if you want to use autoconnect(and auto reconnect) facility
* This function is called whenever TCP connection is established (or re-established).


#connect function
* This function can be used to connect your client to MQTT broker.
* Use only if you do not use Auto connect functionality.
* Optionally  you can use username, password, WILL topic and WILL Message.


#OnConnect CallBack function
* This call back function is called when MQTT connection is established.
* You can call subscription and publish functions inside it (according to your need).


# publish function
* This function can be used to publish messages to different topics.
* You can select  QoS levels and RETAIN flag according to your need.


# subscribe function
* This function can be used to subscribe messages from different topics.


# OnMessage CallBack function
* This callback function is called when messages are received from  subscribed topics
* Topic, TopicLength, Message, MessageLength are the arguments of  OnMessage callback function.
* Inside this, you can write your custom code.


#unsubscribe function
* This function can be used to unsubscribe from a previously subscribed topic.


#disconnect function
* This function can be used to disconnect your client from MQTT broker.


#available function
* return true when connection with mqtt brocker is existing


# Other Features
* You can specify your KeepAlive duration while initializing.
* Ping requests are sent and received automatically.
* QoS 0,1,2

## To Do: 

