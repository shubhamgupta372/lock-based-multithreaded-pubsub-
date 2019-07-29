#include<iostream>
#include"message.h"
#include"pubsubservice.h"
#include"subscriber.h"
#include<chrono>
using namespace std;

subscriber::subscriber(string name)
{
	this->name = name;
	this->msgcount=0;
}
queue<message*> * subscriber::getSubscriberMessages() 
{
	return &subscriberMessages;
}
void subscriber::setSubscriberMessages(queue<message*> &subscriberMessagesarg)
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
/*
void subscriber::getMessagesForSubscriberOfTopic(string topic, pubsubservice &pubSubService)
{
	pubSubService.getMessagesForSubscriberOfTopic(topic, *this);
}
*/ 
void subscriber::printMessages() 
{
	queue<message *> tempsubscriberMessages=*(this->getSubscriberMessages());
	while(tempsubscriberMessages.size())
	{
		message tempmessage=*(tempsubscriberMessages.front());
		tempsubscriberMessages.pop();
		cout<<"Message Topic -> " + tempmessage.getTopic() + " : " + tempmessage.getPayload()<<endl;
	}

}
string subscriber::getname()
{
	return name;
}

LockCondwait * subscriber::getlock()
{
	return &lockcw;
}
void subscriber::Run()
{
	while(1){
		lockcw.lock();
		if(this->subscriberMessages.size()==0){
			//wait
			//sleep(5);
			lockcw.wait();
			//pthread_cond_wait(&subCond,&subMutex.plock);
		}
		else{	
			subscriberMessages.pop();
			lockcw.unlock();
			this->msgcount++;
			cout<<"In Subscriber "<<this->name<<" Run method \n";
			cout<<"performing operation for " << this->msgcount<<" message\n";
			int fact=1,num=10;
			while(num>0){
				fact *=num;
				num --;
			}
			cout<<"factorial is : "<< fact<<endl;
			cout<< "operation finished for " << this->msgcount <<" message\n";
			auto end_time = chrono::steady_clock::now();
			cout << "Elapsed time in milliseconds : " << chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count()<< " ms" << endl;
		
		}
	}
}
