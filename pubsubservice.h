#ifndef _PUBSUBSERVICE_H
#define _PUBSUBSERVICE_H

#include<iostream>
#include"message.h"
#include<map>
#include<vector>
#include"subscriber.h"
#include<queue>
#include"threadbase.h"
#include"mutexcv.h"
#include<chrono>
using namespace std;

static const auto start_time= chrono::steady_clock::now();
class pubsubservice:public ThreadBase {
public:
	pubsubservice(int);
    void Run();
	void adMessageToQueue(message *message);
	void addSubscriber(string topic, subscriber *Subscriber);
	void removeSubscriber(string topic, subscriber *Subscriber);
	void broadcast();
	//void getMessagesForSubscriberOfTopic(string topic, subscriber &Subscriber);

private:
	map<string, vector<subscriber *>> subscribersTopicMap;
	queue<message *> messagesQueue;
	subscriber *defSubscriber; // default subscriber to contain message not subscribed by any subscriber
	int size; // dummy size to replicate fixed size circular buffer
	Mutex serviceMutex; // lock for main message queue to be shared by publisher and service
	long unsigned int msgcount;
};

#endif
