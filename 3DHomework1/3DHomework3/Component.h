#pragma once


class CGameObject;

class Component
{
protected:
	CGameObject* m_pOwner = nullptr;

public:
	Component() = default;
	virtual ~Component() = default;

	virtual void Init() {}
	virtual void Update(float fTimeElapsed) {}
	virtual void Render() {}
	virtual void Release() {}


	void SetOwner(CGameObject* owner) { m_pOwner = owner; }
};

