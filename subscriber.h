#pragma once
#ifndef _SUBSCRIBER_H
#define _SUBSCRIBER_H


#include<iostream>
#include"message.h"
#include<vector>
#include"threadbase.h"
#include<pthread.h>
using namespace std;
class pubsubservice;

class subscriber:public ThreadBase {
public:
	subscriber(string);
	void Run();
	vector<message> getSubscriberMessages();
	void setSubscriberMessages(vector<message> &subscriberMessages);
	void addSubscription(string topic, pubsubservice &service);
	void removeSubscription(string topic, pubsubservice &service);
	void getMessagesForSubscriberOfTopic(string topic, pubsubservice &service);
	void printMessages() const;
	/*bool operator< (subscriber& right) const
	{
		return subscriberMessages.size() < right.subscriberMessages.size();
	}*/
public:
	string name;
	vector<message> subscriberMessages;
	Mutex subMutex;
	pthread_cond_t subCond;
	/*bool operator ==(subscriber right) const
	{
		return subscriberMessages == right.subscriberMessages;
	}*/
};


#endif