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
	//for (int i = 0; i < EXPLOSION_DEBRISES; i++) XMStoreFloat3(&m_pxmf3SphereVectors[i], ::RandomUnitVectorOnSphere());

	//m_pExplosionMesh = new CCubeMeshDiffused(0.5f, 0.5f, 0.5f);
}