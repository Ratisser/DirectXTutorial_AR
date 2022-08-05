#pragma once

class GameEngineLevel
{
public:
	GameEngineLevel(); 
	~GameEngineLevel();

	GameEngineLevel(const GameEngineLevel& _other) = delete; 
	GameEngineLevel(GameEngineLevel&& _other) = delete; 

	GameEngineLevel& operator=(const GameEngineLevel& _other) = delete;
	GameEngineLevel& operator=(const GameEngineLevel&& _other) = delete;

public:
	virtual void Update(float deltaTime) = 0;
	virtual void Render(float deltaTime) = 0;

private:

};

