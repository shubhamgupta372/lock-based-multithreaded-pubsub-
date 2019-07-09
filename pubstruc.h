#pragma once

#ifndef _PUBSTRUC_H
#define _PUBSTRUC_H


#include<iostream>
#include"pubsubservice.h"
#include"message.h"
using namespace std;

struct publish_str{
	message * message_obj;
	pubsubservice * sevice_obj;
};

#endif;