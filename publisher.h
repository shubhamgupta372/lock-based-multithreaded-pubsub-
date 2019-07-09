#pragma once

#ifndef _PUBLISHER_H
#define _PUBLISHER_H


#include<iostream>
#include"pubsubservice.h"
#include"message.h"
#include"threadbase.h"
//#include"pubstruc.h"

struct publish_str;
using namespace std;

class publisher:public ThreadBase {
public:
	 void * publish(void * obj);
	 void Run();
	 publish_str * publisher_args;

};

#endif