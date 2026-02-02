#pragma once


class GameObject;

class Component
{
private:
	GameObject* m_pOwner = nullptr;

public:
	Component() = default;
	virtual ~Component() = default;

	virtual void Init() {}
	virtual void Update(float fTimeElapsed) {}
	virtual void Render() {}
	virtual void Release() {}
};

