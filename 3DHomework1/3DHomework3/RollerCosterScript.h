#pragma once
#include "Component.h"
#include "Mesh.h"
#include "Player.h"


class RollerCosterScript :
    public Component
{
private:
	std::list<std::pair<CDiffusedVertex*, CDiffusedVertex*>> lineList;
	std::string fileName = "Rail.txt";
	CPlayer* player = nullptr;
public:
	virtual void Init() override;
	virtual void Update(float fTimeElapsed) override;
	virtual void Render() override;
	virtual void Release() override;

	void SetFileName(const std::string name) { fileName = name; }
};

