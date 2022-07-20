#pragma once

#include "GameObject.h"

class GameEngineActor : public GameObject
{
public:
	GameEngineActor(); 
	~GameEngineActor();

	GameEngineActor(const GameEngineActor& _other) = delete; 
	GameEngineActor(GameEngineActor&& _other) = delete; 

	GameEngineActor& operator=(const GameEngineActor& _other) = delete;
	GameEngineActor& operator=(const GameEngineActor&& _other) = delete;

};

