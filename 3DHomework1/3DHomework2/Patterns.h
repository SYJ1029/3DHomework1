#pragma once

#include "stdafx.h"



class CMovePattern
{
public:
	CMovePattern();
	virtual ~CMovePattern();
protected:
	XMFLOAT3 m_xmf3MoveDirection;
	float m_fMoveSpeed;

public:
	void SetMoveSpeed(float fMoveSpeed) { m_fMoveSpeed = fMoveSpeed; };
	void SetMoveDirection(XMFLOAT3 xmf3MoveDirection) {
		m_xmf3MoveDirection = xmf3MoveDirection;
	}
};

class CRotationPattern
{

public:
	CRotationPattern();
	virtual ~CRotationPattern();
protected:
	XMFLOAT3 m_xmf3RotationAxis;
	float m_fRotationSpeed;
public:
	void SetRotationSpeed(float fRotationSpeed) { m_fRotationSpeed = fRotationSpeed; }
	void SetRotationAxis(XMFLOAT3 xmf3RotationAxis) {
		m_xmf3RotationAxis = xmf3RotationAxis;
	}
};