#pragma once


#include "Mesh.h"
#include "Camera.h"
#include "Patterns.h"

class CShader;

class CGameObject
{
public:
	CGameObject();
	virtual ~CGameObject();
private:
	int m_nReferences = 0;
public:
	void AddRef() { m_nReferences++; }
	void Release() { if (--m_nReferences <= 0) delete this; }
	XMFLOAT4X4 m_xmf4x4World;
protected:
	
	CMesh* m_pMesh = NULL;
	CShader* m_pShader = NULL;

	bool m_pActive = true;
public:
	void SetActive(bool active) { m_pActive = active; }
	bool IsActive() { return m_pActive; }

	void ReleaseUploadBuffers();
	virtual void SetMesh(CMesh* pMesh);
	virtual void SetShader(CShader* pShader);
	virtual void Animate(float fTimeElapsed);
	virtual void Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera);
	virtual void Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera, UINT
		nInstances);
	void Rotate(XMFLOAT3* pxmf3Axis, float fAngle);
	void OnPrepareRender();

	//상수 버퍼를 생성한다. 
	virtual void CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList 
	*pd3dCommandList);
	//상수 버퍼의 내용을 갱신한다. 
	virtual void UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void ReleaseShaderVariables();

	//게임 객체의 월드 변환 행렬에서 위치 벡터와 방향(x-축, y-축, z-축) 벡터를 반환한다. 
	XMFLOAT3 GetPosition();
	XMFLOAT3 GetLook();
	XMFLOAT3 GetUp();
	XMFLOAT3 GetRight();

	//게임 객체의 위치를 설정한다. 
	void SetPosition(float x, float y, float z);
	void SetPosition(XMFLOAT3 xmf3Position);

	//게임 객체를 로컬 x-축, y-축, z-축 방향으로 이동한다.
	void MoveStrafe(float fDistance = 1.0f);
	void MoveUp(float fDistance = 1.0f);
	void MoveForward(float fDistance = 1.0f);

	//게임 객체를 회전(x-축, y-축, z-축)한다. 
	void Rotate(float fPitch = 10.0f, float fYaw = 10.0f, float fRoll = 10.0f);

	void GenerateRayForPicking(XMVECTOR& xmvPickPosition, XMMATRIX& xmmtxView, XMVECTOR& xmvPickRayOrigin, XMVECTOR& xmvPickRayDirection);
	int PickObjectByRayIntersection(XMVECTOR& xmPickPosition, XMMATRIX& xmmtxView, float* pfHitDistance);
};

class CRotatingObject : public CGameObject
{
public:
	CRotatingObject();
	virtual ~CRotatingObject();
protected:
	XMFLOAT3 m_xmf3RotationAxis;
	float m_fRotationSpeed;
public:
	void SetRotationSpeed(float fRotationSpeed) { m_fRotationSpeed = fRotationSpeed; }
	void SetRotationAxis(XMFLOAT3 xmf3RotationAxis) {
		m_xmf3RotationAxis = xmf3RotationAxis;
	}

	virtual void Animate(float fTimeElapsed);
};



#define EXPLOSION_DEBRISES 240


class CExplosiveObject : public CGameObject, public CRotationPattern, public CMovePattern
{
public:
	CExplosiveObject();
	virtual ~CExplosiveObject();
protected:
public:
	XMFLOAT4X4					m_pxmf4x4Transforms[EXPLOSION_DEBRISES];

	bool m_bBlowingUp;
	void SetExplosion() { m_bBlowingUp = true; }

	float						m_fElapsedTimes = 0.0f;
	float						m_fDuration = 2.0f;
	float						m_fExplosionSpeed = 10.0f;
	float						m_fExplosionRotation = 720.0f;

	static CMesh* m_pExplosionMesh;
	static XMFLOAT3				m_pxmf3SphereVectors[EXPLOSION_DEBRISES];
	static void PrepareExplosion(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
		* pd3dCommandList);
	virtual void Animate(float fTimeElapsed);
	virtual void Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera, UINT
		nInstances);
};