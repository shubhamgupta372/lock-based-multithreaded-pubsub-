#include<iostream>
#include"message.h"
#include"pubsubservice.h"
#include"subscriber.h"
#include<set>
#include<algorithm>
using namespace std;
Mutex mutx;

pubsubservice::pubsubservice(int size)
{
	this->size=size;
}
void pubsubservice::adMessageToQueue(message &msg)
{
	while(1){
		if(messagesQueue.size()<this->size){
			int status = mutx.lock();
			messagesQueue.push(msg);
			// compare with spdk enque behaviour.
			status = mutx.unlock();
			break;
		}
		else
		{
			sleep(5);/* code */
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
			cout << "No messages from publisher to display \n";
			sleep(4);

		}
		else {
			int status= mutx.lock();
			while (messagesQueue.size()) {
				message Message = messagesQueue.front();
				messagesQueue.pop();
				string topic = Message.getTopic();
				map<string, vector<subscriber*>>::iterator it;
				it = subscribersTopicMap.find(topic);
				if (it != subscribersTopicMap.end()) {
					vector<subscriber*> subscribers = subscribersTopicMap[topic];
					for (subscriber* a : subscribers) {
						a->subMutex.lock();
						vector<message> subMessages = a->getSubscriberMessages();
						subMessages.push_back(Message);
						a->setSubscriberMessages(subMessages);
						if(subMessages.size()){
							pthread_cond_signal(&a->subCond);
						}
						cout << "\nNumber of messages for current sub " <<a->name <<" are " << subMessages.size() << " : " <<a->subscriberMessages.size() << endl;
						a->printMessages();
						a->subMutex.unlock();
					}
				}
				else
				{
					cout<<"No subscriber for "<< topic << " topic. pushing to default subscriber" <<endl;
					vector<message> subMessages = defSubscriber->getSubscriberMessages();
					subMessages.push_back(Message);
					defSubscriber->setSubscriberMessages(subMessages);
					cout << "\nNumber of messages for current sub " <<defSubscriber->name <<" are " << subMessages.size() << " : " <<defSubscriber->subscriberMessages.size() << endl;
					defSubscriber->printMessages();
				}
				
			}
			status= mutx.unlock();
		}
	}
}
void pubsubservice::getMessagesForSubscriberOfTopic(string topic, subscriber &Subscriber)
{
	if (!messagesQueue.size()) {
		cout << "No messages from publisher to display";
	}
	else {
		while (messagesQueue.size()) {
			message Message = messagesQueue.front();
			messagesQueue.pop();
			if (Message.getTopic() == topic) {
				vector<subscriber*> &subscribers = subscribersTopicMap[topic];
				for (subscriber* a : subscribers) {
					vector<message> subMessages = a->getSubscriberMessages();
					subMessages.push_back(Message);
					a->setSubscriberMessages(subMessages);
				}
			}
		}
	}

}

void pubsubservice::Run()
{
	this->broadcast();
}