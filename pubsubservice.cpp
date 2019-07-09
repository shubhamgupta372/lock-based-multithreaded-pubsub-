#include<iostream>
#include"message.h"
#include"pubsubservice.h"
#include"subscriber.h"
#include<set>
#include<algorithm>
using namespace std;
Semaphore sem;

void pubsubservice::adMessageToQueue(message &msg)
{
	sem.Lock();
	messagesQueue.push(msg);
	sem.UnLock();
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
	if (!messagesQueue.size()){
		cout << "No messages from publisher to display";
	}
	else {
		sem.Lock();
		while (messagesQueue.size()) {
			message Message = messagesQueue.front();
			messagesQueue.pop();
			string topic = Message.getTopic();
			map<string, vector<subscriber*>>::iterator it;
			it = subscribersTopicMap.find(topic);
			if (it != subscribersTopicMap.end()) {
				vector<subscriber*> subscribers = subscribersTopicMap[topic];
				//std::set<subscriber>::iterator it;
				/*for (auto it = subscribers.begin(); it != subscribers.end(); it++)
				{
					subscriber obj = *it;
					vector<message> subMessages = obj.getSubscriberMessages();
					subMessages.push_back(Message);
					obj.setSubscriberMessages(subMessages);
					obj.printMessages();
					cout << "\n Number of messages for current sub " << subMessages.size() << endl;
				}*/
				/*for (int i = 0; i < subscribers.size(); i++) {
					vector<message> subMessages = subscribers[i].getSubscriberMessages();
					subMessages.push_back(Message);
					subscribers[i].setSubscriberMessages(subMessages);
					subscribers[i].printMessages();
					cout << "\n Number of messages for current sub " << subMessages.size() << endl;
				}*/
				for (subscriber* a : subscribers) {
					vector<message> subMessages = a->getSubscriberMessages();
					subMessages.push_back(Message);
					a->setSubscriberMessages(subMessages);
					cout << "\n Number of messages for current sub " <<a->name <<" are " << subMessages.size() << " : " <<a->subscriberMessages.size() << endl;
					a->printMessages();
				}
			}
		}
		sem.UnLock();
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