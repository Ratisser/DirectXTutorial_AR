#pragma once

#include "UObject.h"

class UActor : public UObject
{
public:
	UActor(); 
	~UActor();

	UActor(const UActor& _other) = delete; 
	UActor(UActor&& _other) = delete; 

	UActor& operator=(const UActor& _other) = delete;
	UActor& operator=(const UActor&& _other) = delete;

};

