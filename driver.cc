#include"threadbase.h"
#include<iostream>
#include<pthread.h>
#include<iostream>
#include"message.h"
#include"pubsubservice.h"
#include"subscriber.h"
#include"publisher.h"
#include"pubstruc.h"
#include<string>
using namespace std;

int main()
{
	pubsubservice service;
	publisher  pobj[10];
	message cplusplusMsg[5]={{"cplusplus", "Core cplusplus Concepts"},
	{"cplusplus", "Dependency and AOP"},{"cplusplus", "STL library"},
	{"cplusplus","Boost"},{"cplusplus","pubsub"}};
	publish_str *pstr[10];
	subscriber sobj[2]={{"cplusplussub"},{"pythonsub"}};
	service.addSubscriber("cplusplus",&sobj[0]);
	
	for(int i=0;i<10;i++)
	{
		pstr[i]= (publish_str *)malloc(sizeof(publish_str));
		pstr[i]->message_obj=&cplusplusMsg[i%5];
		pstr[i]->sevice_obj=&service;
		//pobj[i]=(publisher *)malloc(sizeof(publisher));
		pobj[i].publisher_args=pstr[i];
		/*  int tid=pthread_create(&thread[i],NULL, pobj[i]->publish,pstr[i]); */
		string name="Publisher Thread " + std::to_string(i+1);
        bool status=pobj[i].Start(name.c_str());
		if(!status){
			cout<<"Publisher Thread "<<i+1<<" not created successfully \n";
		}
		std::cout<<pobj[i].GetThreadName()<<" created \n";
	}
	cout<<"Hello \n";
	cout<< service.messagesQueue.size()<<endl;

	bool status=service.Start("Service_Thread");
		if(!status){
			cout<<"Service Thread not created successfully \n";
		}
	for(int i=0;i<2;i++){
		string name="Subscriber Thread " + std::to_string(i+1);
        bool status=sobj[i].Start(name.c_str());
		if(!status){
			cout<<"Subscriber Thread "<< i+1 <<" not created successfully \n";
		}
	}
    
 	for(int i=0;i<10;i++){
 		pobj[i].Join();
	}
	service.Join();
	sobj[0].Join();
	sobj[1].Join();


	cout<<"Size of main service msg queue"<<service.messagesQueue.size()<<endl;
	//cout<<service.messagesQueue.front().getTopic();
	//cout<<"cplusplus subs message count is "<<sobj.subscriberMessages.size();
    return 0;
}