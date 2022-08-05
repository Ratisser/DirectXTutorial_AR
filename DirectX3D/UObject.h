#pragma once

class UObject
{
public:
	UObject();
	~UObject();
	UObject(const UObject& _other) = delete;
	UObject(UObject&& _other) = delete;
	UObject& operator=(const UObject& _other) = delete;
	UObject& operator=(const UObject&& _other) = delete;

public:
	void Activate() { bUpdate_ = true; }
	void Deactivate() { bUpdate_ = false; }
	void Release() { bRelease_ = true; }

	bool IsObjectToUpdate() { return bUpdate_; }
	bool IsObjectToRelease() { return bRelease_; }

private:
	bool bUpdate_;
	bool bRelease_;
};

