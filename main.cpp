#include<iostream>
#include"message.h"
#include"pubsubservice.h"
#include"subscriber.h"
#include"publisher.h"
#include<pthread.h>
#include"publisharguments.h"
using namespace std;
//class publisher;
//typedef void * (*THREADFUNCPTR)(void *);
# define TOTAL_THREADS 50

int main()
{
	pthread_t thread[TOTAL_THREADS];
	//publisher pub[5];
	pubsubservice service(10);
	publisher * pobj[50];
	//message cplusplusMsg[5];
	message cplusplusMsg[5]={{"cplusplus", "Core cplusplus Concepts"},
	{"cplusplus", "Dependency and AOP"},{"cplusplus", "STL library"},
	{"cplusplus","Boost"},{"cplusplus","pubsub"}};
	publishArguments *pstr[50];

	
	for(int i=0;i<TOTAL_THREADS;i++)
	{
		pstr[i]= (publishArguments *)malloc(sizeof(publishArguments));
		pstr[i]->message_obj=&cplusplusMsg[i%5];
		pstr[i]->sevice_obj=&service;
		int tid=pthread_create(&thread[i],NULL, pobj[i]->publish,pstr[i]);
		if(tid!=0){
			cout<<"Thread not created successfully \n";
		}
	}

	for(int i=0;i<50;i++){
		pthread_join(thread[i],NULL);
	}

	cout<< service.messagesQueue.size()<<endl;
	// publisher cpluspluspublisher; 
	// publisher pythonpublisher;

	// subscriber cplusplussubscriber("cplusplussubscriber");
	// subscriber allLanguagessubscriber("allLanguagessubscriber");
	// subscriber pythonsubscriber("pythonsubscriber");

	// pubsubservice service;

	// //Declare Messages and Publish Messages to pubsubservice
	// message cplusplusMsg1("cplusplus", "Core cplusplus Concepts");
	// message cplusplusMsg2("cplusplus", "Dependency and AOP");
	// message cplusplusMsg3("cplusplus", "STL library");

	// cpluspluspublisher.publish(cplusplusMsg1, service);
	// cout << service.messagesQueue.size()<<endl;
	// cpluspluspublisher.publish(cplusplusMsg2, service);
	// cpluspluspublisher.publish(cplusplusMsg3, service);
	// cout << service.messagesQueue.size() << endl;

	// message pythonMsg1("Python", "Easy and Powerful programming language");
	// message pythonMsg2("Python", "Advanced Python message");

	// pythonpublisher.publish(pythonMsg1, service);
	// pythonpublisher.publish(pythonMsg2, service);
	// cout << service.messagesQueue.size() << endl;

	// //Declare subscribers 
	// service.addSubscriber("cplusplus", &cplusplussubscriber);
	// //cplusplussubscriber.addSubscriber("cplusplus", service);		//cplusplus subscriber only subscribes to cplusplus topics
	// pythonsubscriber.addSubscription("Python", service);   //Python subscriber only subscribes to Python topics
	// allLanguagessubscriber.addSubscription("cplusplus", service);	//all subscriber, subscribes to both cplusplus and Python
	// allLanguagessubscriber.addSubscription("Python", service);

	// cout << "map size"<<service.subscribersTopicMap.size() << endl;
	// //Trying unSubscribing a subscriber
	// //pythonsubscriber.unSubscribe("Python", pubsubservice);

	// //Broadcast message to all subscribers. After broadcast, messageQueue will be empty in pubsubservice
	// map<string, vector<subscriber *>>::iterator it;
	// for (it = service.subscribersTopicMap.begin(); it != service.subscribersTopicMap.end(); it++) {
	// 	cout << "key : " << it->first << " value : ";
	// 		for (int i = 0; i < it->second.size(); i++) {
	// 			cout << it->second[i]->name << " : no of msgs's " << it->second[i]->subscriberMessages.size() << " , ";
	// 		}
	// 		cout << endl;
	// }
	// cout << endl;
	// service.broadcast();

	// cout << "after bradcast \n cplusplus subscriber msg size "<<cplusplussubscriber.subscriberMessages.size()<<endl;
	// cout << "after bradcast \n python subscriber msg size " << pythonsubscriber.subscriberMessages.size() << endl;
	// cout << "after bradcast \n all subscriber msg size " << allLanguagessubscriber.subscriberMessages.size() << endl;
	// //Print messages of each subscriber to see which messages they got

	// //map<string, vector<subscriber>>::iterator it;
	// for (it = service.subscribersTopicMap.begin(); it != service.subscribersTopicMap.end(); it++) {
	// 	cout << "key : " << it->first << " value : ";
	// 	for (int i = 0; i < it->second.size(); i++) {
	// 		cout << it->second[i]->name << " : no of msgs's " << it->second[i]->subscriberMessages.size() << " , ";
	// 	}
	// 	cout << endl;
	// }
	// cout << endl;


	// cout<<"messages of cplusplus subscriber are: ";
	// cplusplussubscriber.printMessages();

	// cout<<"\nmessages of Python subscriber are: ";
	// pythonsubscriber.printMessages();

	// cout<<"\nmessages of All Languages subscriber are: ";
	// allLanguagessubscriber.printMessages();

	// //After broadcast the messagesQueue will be empty, so publishing new messages to server
	// cout<<"\nPublishing 2 more cplusplus messages...";
	// message cplusplusMsg4("cplusplus", "Boost library");
	// message cplusplusMsg5("cplusplus", "pubsub framework");

	// cpluspluspublisher.publish(cplusplusMsg4, service);
	// cpluspluspublisher.publish(cplusplusMsg5, service);
	// cplusplussubscriber.getMessagesForSubscriberOfTopic("cplusplus", service);
	// cout<<"\nmessages of cplusplus subscriber now are: ";
	// cplusplussubscriber.printMessages();
	// //system("pause");
	return 0;
}