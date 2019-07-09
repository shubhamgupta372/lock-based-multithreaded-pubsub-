#include<iostream>
#include"message.h"
#include"pubsubservice.h"
#include"publisher.h"
#include"pubstruc.h"
using namespace std;
struct publish_str;

 void *publisher::publish( void * obj1)
{
	publish_str * obj= (publish_str *) obj1;
	obj->sevice_obj->adMessageToQueue(*(obj->message_obj));
	cout<<"messahe published to queue \n";
	//pubSubService.adMessageToQueue(Message);
}

void publisher::Run()
{
	std::cout<<"in "<<this->GetThreadName()<< " Run \n";
	publish(this->publisher_args); 
}