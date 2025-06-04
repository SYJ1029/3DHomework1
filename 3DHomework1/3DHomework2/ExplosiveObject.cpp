#include "GameObject.h"

CExplosiveObject::CExplosiveObject() 
	: CGameObject(), CRotationPattern(), CMovePattern()
{

}

CExplosiveObject::~CExplosiveObject()
{

}

void CExplosiveObject::Animate(float fTimeElapsed)
{
	CGameObject::Rotate(&m_xmf3RotationAxis, m_fRotationSpeed * fTimeElapsed);
}

void CExplosiveObject::PrepareExplosion()
{

}