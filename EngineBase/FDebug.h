#pragma once

class FDebug
{
public:
	static void SetMemoryLeakCheckFlag();

	static void AssertFalse()
	{
		assert(false);
	}

	static void OutPutDebugString(const std::string& text)
	{
		OutputDebugStringA(text.c_str());
	}

	static void MsgBox(const std::string& text)
	{
		MessageBoxA(nullptr, text.c_str(), "Error", MB_OK);
	}

	static void MsgBoxError(const std::string& text)
	{
		MessageBoxA(nullptr, text.c_str(), "Error", MB_OK);
		assert(false);
	}

private:
	FDebug();
	~FDebug();

};

