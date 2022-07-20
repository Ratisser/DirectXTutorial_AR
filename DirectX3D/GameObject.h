#pragma once

class GameObject
{
public:
	GameObject();
	~GameObject();
	GameObject(const GameObject& _other) = delete;
	GameObject(GameObject&& _other) = delete;
	GameObject& operator=(const GameObject& _other) = delete;
	GameObject& operator=(const GameObject&& _other) = delete;

public:
	void Activate() { bUpdate_ = true; }
	void Deactivate() { bUpdate_ = false; }

	bool IsObjectToUpdate() { return bUpdate_; }
	bool IsObjectToRelease() { return bRelease_; }

private:
	bool bUpdate_;
	bool bRelease_;
};

