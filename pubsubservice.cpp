#include<iostream>
#include"message.h"
#include"pubsubservice.h"
#include"subscriber.h"
#include<set>
#include<algorithm>
using namespace std;

pubsubservice::pubsubservice(int size)
{
	this->size=size;
	this->msgcount=0;
}
void pubsubservice::adMessageToQueue(message * msg)
{
	while(1){
		int status = serviceMutex.lock();
		if(messagesQueue.size()<this->size){	
			messagesQueue.push(msg);
			msgcount++;
			cout<<"New message published for '"<<msg->getTopic()<< "' topic"<< endl;
			cout<<"Count of messages published till now : "<< msgcount << endl;
			// compare with spdk enque behaviour.
			status = serviceMutex.unlock();
			break;
		}
		else
		{
			status = serviceMutex.unlock();
			sleep(1);
		}
	}
	
}
void pubsubservice::addSubscriber(string topic, subscriber* Subscriber)
{
	map<string, vector<subscriber *>>::iterator it;
	it = subscribersTopicMap.find(topic);
	if (it != subscribersTopicMap.end()){
		vector<subscriber*> &subscribers = subscribersTopicMap[topic];
		subscribers.push_back(Subscriber);
		//subscribersTopicMap[topic] = subscribers;
	}
	else {
		vector<subscriber*> subscribers;
		subscribers.push_back(Subscriber);
		subscribersTopicMap[topic] = subscribers;
	}
}
void pubsubservice::removeSubscriber(string topic, subscriber* Subscriber)
{
	map<string,vector<subscriber*>>::iterator it;
	it = subscribersTopicMap.find(topic);
	if (it != subscribersTopicMap.end()){
		vector<subscriber*> &subscribers = subscribersTopicMap[topic];
		vector<subscriber*>::iterator itv;
		itv = find(subscribers.begin(), subscribers.end(), Subscriber);
		if (itv != subscribers.end()) {
			subscribers.erase(itv);
		}
		subscribersTopicMap[topic] = subscribers;
	}
}
void pubsubservice::broadcast()
{
	while(1){
		if (!messagesQueue.size()){
			cout << "No more messages from publisher in msg queue, waiting for new msg \n";
			sleep(5);

		}
		else {
			int status= serviceMutex.lock();
			while (messagesQueue.size()) {
				message * Message = messagesQueue.front();
				messagesQueue.pop();
				string topic = Message->getTopic();
				map<string, vector<subscriber*>>::iterator it;
				it = subscribersTopicMap.find(topic);
				if (it != subscribersTopicMap.end()) {
					vector<subscriber*> subscribers = subscribersTopicMap[topic];
					for (subscriber* a : subscribers) {
						a->getlock()->lock();
						queue<message *> subMessages = a->getSubscriberMessages();
						subMessages.push(Message);
						a->setSubscriberMessages(subMessages);
						if(subMessages.size()){
							//pthread_cond_signal(&a->subCond);
							a->getlock()->signal();
						}
						cout << "Number of messages for current sub " <<a->getname() <<" are : " << subMessages.size() << endl;
						a->printMessages();
						a->getlock()->unlock();
					}
				}
				else
				{
					cout<< "No subscriber for " << topic << " topic. pushing to default subscriber" <<endl;
					queue<message*> subMessages = defSubscriber->getSubscriberMessages();
					subMessages.push(Message);
					defSubscriber->setSubscriberMessages(subMessages);
					cout << "Number of messages for current sub " <<defSubscriber->getname() <<" are : " << subMessages.size() << endl;
					defSubscriber->printMessages();
				}
				
			}
			status= serviceMutex.unlock();
		}
	}
}

void pubsubservice::Run()
{
	this->broadcast();
}
