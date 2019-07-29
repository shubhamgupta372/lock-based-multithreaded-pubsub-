#ifndef _SUBSCRIBER_H
#define _SUBSCRIBER_H

#include<iostream>
#include"message.h"
#include<queue>
#include"threadbase.h"
#include"mutexcv.h"
#include<pthread.h>
using namespace std;
class pubsubservice;

class subscriber:public ThreadBase {
public:
	subscriber(string);
	void Run();
	queue<message *> *getSubscriberMessages();
	void setSubscriberMessages(queue<message*> subscriberMessages);
	void addSubscription(string topic, pubsubservice &service);
	void removeSubscription(string topic, pubsubservice &service);
	void printMessages();
	string getname();
	LockCondwait *getlock();
private:
	string name;
	queue<message *> subscriberMessages;
	LockCondwait lockcw;
	size_t msgcount; 
};


#endif