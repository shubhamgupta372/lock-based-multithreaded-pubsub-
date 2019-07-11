#pragma once

#ifndef _PUBSTRUC_H
#define _PUBSTRUC_H


#include<iostream>
#include"pubsubservice.h"
#include"message.h"
using namespace std;

struct publishArguments{
	message * message_obj;
	pubsubservice * sevice_obj;
};

#endif;