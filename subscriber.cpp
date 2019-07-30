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
queue<message*> *subscriber::getSubscriberMessages() 
{
	return &subscriberMessages;
}
void subscriber::setSubscriberMessages(queue<message *> subscriberMessagesarg)
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

LockCondwait *subscriber::getlock()
{
	return &lockcw;
}
void subscriber::Run()
{
	while(1){
		lockcw.lock();
		if(this->subscriberMessages.size()==0){
			lockcw.wait();
		}
		else{	
			subscriberMessages.pop();
			lockcw.unlock();
			this->msgcount++;
			cout<<"\n**************In Subscriber "<<this->name<<" Run method ***********\n";
			cout<<"performing operation for message number " << this->msgcount<<"\n";
			int fact=1,num=10;
			while(num>0){
				fact *=num;
				num --;
			}
			auto end_time = chrono::steady_clock::now();
			cout<<"factorial is : "<< fact<<endl;
			cout<< "************operation finished for " << this->msgcount <<" message***********\n";
			cout << "***********Elapsed time in milliseconds : " << chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count()<< " ms ***********" << endl;
		
		}
	}
}
