#pragma once
#include "FEngineWindow.h"
#include "FGraphicDevice.h"

#include <memory>

#include "Object.hpp"

class FEngineCore
{
public:
	FEngineCore();
	virtual ~FEngineCore();

public:
	static FEngineCore* GetInstance() { static FEngineCore instance; return &instance; }

	void Initialize(std::string _windowCaption, std::string _windowClassName, float4 _windowPosition, float4 _windowSize);
	void Run();
	
	void DrawObject();

public:
	FEngineWindow* GetWindow() { return window_.get(); }

private:
	static void GameLoop();

	void release();

private:
	std::unique_ptr<FEngineWindow> window_;
	std::unique_ptr<FGraphicDevice> device_;

	Object tempObject_;
};

