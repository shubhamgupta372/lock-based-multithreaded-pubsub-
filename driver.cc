#include"threadbase.h"
#include<iostream>
#include<pthread.h>
#include<iostream>
#include"message.h"
#include"pubsubservice.h"
#include"subscriber.h"
#include"publisher.h"
#include"publisharguments.h"
#include<string>
using namespace std;

// method to intialise arguments of publish method in publisher object
void InitialisePubObject(message *mobj, pubsubservice *psobj, publisher *pobj)
{
	publishArguments *pargs;
	pargs= new publishArguments;
	pargs->message_obj = mobj;
	pargs->sevice_obj = psobj;
	pobj->publisher_args = pargs;
}

int main()
{
//pubsub framework starts here
	pubsubservice service(1024); 
	publisher  pobj[1000];
	message cplusplusMsg[5]={{"cplusplus", "Core cplusplus Concepts"},
	{"cplusplus", "Dependency and AOP"},{"java", "STL library"},
	{"cplusplus","Boost"},{"java","pubsub"}};
	subscriber sobj[20]={{"Sub_1"},{"Sub_2"},{"Sub_3"},{"Sub_4"},{"Sub_5"},{"Sub_6"},{"Sub_7"},{"Sub_8"},{"Sub_9"},{"Sub_10"},
	{"Sub_1"},{"Sub_12"},{"Sub_13"},{"Sub_14"},{"Sub_15"},{"Sub_16"},{"Sub_17"},{"Sub_18"},{"Sub_19"},{"Sub_20"}};

	for(int i=0;i<20;i+=2)
	{
		service.addSubscriber("cplusplus",&sobj[i]);
		service.addSubscriber("java",&sobj[i+1]);

	}
	// creating thread for each publisher object and publishing meassges
	for(int i=0;i<1000;i++)
	{
		InitialisePubObject(&cplusplusMsg[i%5],&service,&pobj[i]);
		string name="Publisher Thread " + std::to_string(i+1);
        bool status=pobj[i].Start(name.c_str());
		if(!status){
			cout<<"Publisher Thread "<<i+1<<" not created successfully \n";
		}
		else{
			//std::cout<<pobj[i].GetThreadName()<<" created \n";
		}
	}

	//creating single service thread to run polling/broadcast function
	bool status=service.Start("Service_Thread");
		if(!status){
			cout<<"Service Thread not created successfully \n";
		}
		else{
			//std::cout<<service.GetThreadName()<<" created \n";
		}

	// creating 2 subscriber threads	
	for(int i=0;i<20;i++){
		string name="Subscriber Thread " + std::to_string(i+1);
        bool status=sobj[i].Start(name.c_str());
		if(!status){
			cout<<"Subscriber Thread "<< i+1 <<" not created successfully \n";
		}
		else{
			//std::cout<<sobj[i].GetThreadName()<<" created \n";
		}
	}

	// join all the publisher, subscriber and service threads
 	for(int i=0;i<1000;i++){
 		pobj[i].Join();
	}
	service.Join();
	for(int i=0;i<20;i++){
 		sobj[i].Join();
	}

    return 0;
}
