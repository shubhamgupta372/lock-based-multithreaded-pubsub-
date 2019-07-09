#include<iostream>
#include"message.h"
#include"pubsubservice.h"
#include"subscriber.h"
using namespace std;


subscriber::subscriber(string name)
{
	this->name = name;
}
vector<message> subscriber::getSubscriberMessages() 
{
	return subscriberMessages;
}
void subscriber::setSubscriberMessages(vector<message> &subscriberMessagesarg)
{
	this->subscriberMessages = subscriberMessagesarg;
}
void subscriber::addSubscription(string topic, pubsubservice &pubSubService)
{
	pubSubService.addSubscriber(topic, this);
}
void subscriber::removeSubscription(string topic, pubsubservice &pubSubService)
{
	pubSubService.removeSubscriber(topic, this);
}
void subscriber::getMessagesForSubscriberOfTopic(string topic, pubsubservice &pubSubService)
{
	pubSubService.getMessagesForSubscriberOfTopic(topic, *this);
}
void subscriber::printMessages() const
{
	for (message Message : subscriberMessages) {
		cout<<"Message Topic -> " + Message.getTopic() + " : " + Message.getPayload()<<endl;
	}
}
void subscriber::Run()
{
	cout<<"In Subscriber "<<this->name<<" Run method \n";
}
