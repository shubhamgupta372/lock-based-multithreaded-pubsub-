#pragma once
#ifndef _PUBSUBSERVICE_H
#define _PUBSUBSERVICE_H

#include<iostream>
#include"message.h"
#include<map>
#include<vector>
#include"subscriber.h"
#include<queue>
#include"threadbase.h"
using namespace std;

class pubsubservice:public ThreadBase {
public:
	pubsubservice(int);
    void Run();
	void adMessageToQueue(message &message);
	void addSubscriber(string topic, subscriber* Subscriber);
	void removeSubscriber(string topic, subscriber* Subscriber);
	void broadcast();
	void getMessagesForSubscriberOfTopic(string topic, subscriber &Subscriber);

public:
	map<string, vector<subscriber *>> subscribersTopicMap;// change set to vector
	queue<message> messagesQueue;
	subscriber *defSubscriber= new subscriber("default");
	int size;

};

#endif