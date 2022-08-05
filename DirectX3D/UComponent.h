#pragma once

#include "UObject.h"

class UComponent : public UObject
{
public:
	UComponent(); 
	~UComponent();

	UComponent(const UComponent& _other) = delete; 
	UComponent(UComponent&& _other) = delete; 

	UComponent& operator=(const UComponent& _other) = delete;
	UComponent& operator=(const UComponent&& _other) = delete;

};

