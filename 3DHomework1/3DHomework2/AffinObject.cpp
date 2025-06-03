#include "GameObject.h"

CAffinObject::CAffinObject()
{
	m_xmf3RotationAxis = XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_fRotationSpeed = 90.0f;

	m_xmf3MoveDirection = XMFLOAT3(0.0f, 0.0f, 1.0f);
	m_fMoveSpeed = 0.0f;
}
CAffinObject::~CAffinObject()
{

}