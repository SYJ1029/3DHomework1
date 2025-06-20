#include "GameObject.h"
#include "Shader.h"

inline float RandF(float fMin, float fMax)
{
	return(fMin + ((float)rand() / (float)RAND_MAX) * (fMax - fMin));
}

XMVECTOR RandomUnitVectorOnSphere()
{
	XMVECTOR xmvOne = XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f);
	XMVECTOR xmvZero = XMVectorZero();

	while (true)
	{
		XMVECTOR v = XMVectorSet(RandF(-1.0f, 1.0f), RandF(-1.0f, 1.0f), RandF(-1.0f, 1.0f), 0.0f);
		if (!XMVector3Greater(XMVector3LengthSq(v), xmvOne)) return(XMVector3Normalize(v));
	}
}

XMFLOAT3 CExplosiveObject::m_pxmf3SphereVectors[EXPLOSION_DEBRISES];
CMesh* CExplosiveObject::m_pExplosionMesh = nullptr;

CExplosiveObject::CExplosiveObject(int nMeshes)
	: CGameObject(1), CRotationPattern(), CMovePattern()
{
	m_bBlowingUp = false;
}

CExplosiveObject::~CExplosiveObject()
{

}




void CExplosiveObject::Animate(float fTimeElapsed)
{
	if (m_bBlowingUp)
	{
		m_fElapsedTimes += fTimeElapsed;
		if (m_fElapsedTimes <= m_fDuration)
		{
			XMFLOAT3 xmf3Position = GetPosition();
			for (int i = 0; i < EXPLOSION_DEBRISES; i++)
			{
				m_pxmf4x4Transforms[i] = Matrix4x4::Identity();
				m_pxmf4x4Transforms[i]._41 = xmf3Position.x + m_pxmf3SphereVectors[i].x * m_fExplosionSpeed * m_fElapsedTimes;
				m_pxmf4x4Transforms[i]._42 = xmf3Position.y + m_pxmf3SphereVectors[i].y * m_fExplosionSpeed * m_fElapsedTimes;
				m_pxmf4x4Transforms[i]._43 = xmf3Position.z + m_pxmf3SphereVectors[i].z * m_fExplosionSpeed * m_fElapsedTimes;
				m_pxmf4x4Transforms[i] = Matrix4x4::Multiply(Matrix4x4::RotationAxis(m_pxmf3SphereVectors[i], m_fExplosionRotation * m_fElapsedTimes), m_pxmf4x4Transforms[i]);
			}
		}
		else
		{
			m_bBlowingUp = false;
			m_fElapsedTimes = 0.0f;

			// Æø¹ßÀÌ ³¡³µ´Ù¸é ±×¸®¸é ¾ÈµÊ
			SetActive(false);
		}


	}
	else {
		CGameObject::Rotate(&m_xmf3RotationAxis, m_fRotationSpeed * fTimeElapsed);
		CGameObject::MoveStrafe(m_xmf3MoveDirection.x * m_fMoveSpeed);
		CGameObject::MoveForward(m_xmf3MoveDirection.z * m_fMoveSpeed);

		UpdateBoundingBox();
	}
}




void CExplosiveObject::Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera,
	UINT nInstances)
{
	//OnPrepareRender();
	UpdateShaderVariables(pd3dCommandList);
	if(m_pShader)
		m_pShader->UpdateShaderVariables(pd3dCommandList);

	if (m_bBlowingUp)
	{



		if (m_pExplosionMesh) {
			m_pExplosionMesh->Render(pd3dCommandList, EXPLOSION_DEBRISES);
		}


	}
	else
	{
		if (m_ppMeshes) m_ppMeshes[0]->Render(pd3dCommandList, nInstances);
	}
	
}

void CExplosiveObject::SetExplosion()
{ 
	m_bBlowingUp = true; 

}

void CExplosiveObject::PrepareExplosion(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList)
{

	for (int i = 0; i < EXPLOSION_DEBRISES; i++) {
		XMStoreFloat3(&m_pxmf3SphereVectors[i], ::RandomUnitVectorOnSphere());


	}



	m_pExplosionMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList, 0.5f, 0.5f, 0.5f);
}