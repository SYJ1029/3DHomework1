#include "Shader.h"



CTankShader::CTankShader()
{
}

CTankShader::~CTankShader()
{
	ReleaseObjects();
	ReleaseShaderVariables();
}

void CTankShader::SetFileName(std::string filename)
{
	m_filename = filename;
}

void CTankShader::CreateShader(ID3D12Device* pd3dDevice, ID3D12RootSignature* pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState * [m_nPipelineStates];
	CInstancingShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}

void CTankShader::CreateShaderVariables(ID3D12Device* pd3dDevice,
	ID3D12GraphicsCommandList* pd3dCommandList)
{
	//�ν��Ͻ� ������ ������ ���� ���۸� ���ε� �� �������� �����Ѵ�.
	m_pd3dcbGameObjects = ::CreateBufferResource(pd3dDevice, pd3dCommandList, NULL,
		sizeof(VS_VB_INSTANCE) * m_nObjects * EXPLOSION_DEBRISES, D3D12_HEAP_TYPE_UPLOAD,
		D3D12_RESOURCE_STATE_GENERIC_READ, NULL);
	//���� ����(���ε� ��)�� ���� �����͸� �����Ѵ�.
	HRESULT hResult = m_pd3dcbGameObjects->Map(0, NULL, (void**)&m_pcbMappedGameObjects);
}

void CTankShader::UpdateShaderVariables(ID3D12GraphicsCommandList
	* pd3dCommandList)
{

	pd3dCommandList->SetGraphicsRootShaderResourceView(2,
		m_pd3dcbGameObjects->GetGPUVirtualAddress());


	int nObjects = m_nObjects;
	int exploseIndex = -1;
	for (int j = 0; j < nObjects; j++) {
		if (dynamic_cast<CExplosiveObject*>(m_ppObjects[j])->m_bBlowingUp) {
			nObjects = EXPLOSION_DEBRISES;
			exploseIndex = j;
			break;
		}
	}

	for (int j = 0; j < m_nObjects; j++)
	{
		m_pcbMappedGameObjects[j].m_xmcColor = (j % 2) ? XMFLOAT4(0.5f, 0.0f, 0.0f, 0.0f) :
			XMFLOAT4(0.0f, 0.0f, 0.5f, 0.0f);
		XMStoreFloat4x4(&m_pcbMappedGameObjects[j].m_xmf4x4Transform,
			XMMatrixTranspose(XMLoadFloat4x4(&m_ppObjects[j]->GetMatrix(j))));


	}

	if (m_nObjects != nObjects)
		for (int j = 0; j < nObjects; j++) {
			m_pcbMappedGameObjects[j].m_xmcColor = (j % 2) ? XMFLOAT4(0.5f, 0.0f, 0.0f, 0.0f) :
				XMFLOAT4(0.0f, 0.0f, 0.5f, 0.0f);
			XMStoreFloat4x4(&m_pcbMappedGameObjects[j].m_xmf4x4Transform,
				XMMatrixTranspose(XMLoadFloat4x4(&m_ppObjects[exploseIndex]->GetMatrix(j))));
		}


}



void CTankShader::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList, void* pContext)
{

	CHeightMapTerrain* pTerrain = (CHeightMapTerrain*)pContext;
	float fTerrainWidth = pTerrain->GetWidth(), fTerrainLength = pTerrain->GetLength();

	m_nObjects = 1;
	m_ppObjects = new CGameObject * [m_nObjects];
	float fxPitch = 12.0f * 3.5f;
	float fyPitch = 12.0f * 3.5f;
	float fzPitch = 12.0f * 3.5f;
	CExplosiveObject* pExplosiveObject = NULL;



	std::default_random_engine dre{ std::random_device{}() };
	std::uniform_int_distribution uidX(0, int(fTerrainWidth / fxPitch));
	std::uniform_int_distribution uidZ(0, int(fTerrainLength / fzPitch));
	std::uniform_int_distribution uid(0, 255);

	float x{ static_cast<float>(uidX(dre))};
	float y{ static_cast<float>(uid(dre) / 2) };
	float z{ static_cast<float>(uidZ(dre))};

	XMFLOAT3 xmf3RotateAxis, xmf3SurfaceNormal;


	//�ν��Ͻ��� ����Ͽ� �������ϱ� ���Ͽ� �ϳ��� ���� ��ü�� �޽��� ������.
	CTankMeshDiffused* pTankMesh = new CTankMeshDiffused(pd3dDevice, pd3dCommandList,
		12.0f, 3.0f, 12.0f);
	for (int i = 0; i < m_nObjects; i++) {
		float xPosition = x * fxPitch;
		float zPosition = z * fzPitch;
		float fHeight = pTerrain->GetHeight(xPosition, zPosition);

		pExplosiveObject = new CExplosiveObject();
		pExplosiveObject->SetPosition(xPosition, fHeight + (y * 10.0f * fyPitch) + 6.0f, zPosition);

		if (y == 0)
		{
			/*������ ǥ�鿡 ��ġ�ϴ� ������ü�� ������ ���⿡ ���� ������ �ٸ��� ��ġ�Ѵ�. ������ü�� ��ġ�� ������ ����
		   ���� ����� ������ü�� y-���� ��ġ�ϵ��� �Ѵ�.*/
			xmf3SurfaceNormal = pTerrain->GetNormal(xPosition, zPosition);
			xmf3RotateAxis = Vector3::CrossProduct(XMFLOAT3(0.0f, 1.0f, 0.0f),
				xmf3SurfaceNormal);
			if (Vector3::IsZero(xmf3RotateAxis)) xmf3RotateAxis = XMFLOAT3(0.0f, 1.0f,
				0.0f);
			float fAngle = acos(Vector3::DotProduct(XMFLOAT3(0.0f, 1.0f, 0.0f),
				xmf3SurfaceNormal));
			pExplosiveObject->Rotate(&xmf3RotateAxis, XMConvertToDegrees(fAngle));
		}

		pExplosiveObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
		pExplosiveObject->SetRotationSpeed(10.0f);
		pExplosiveObject->PrepareExplosion(pd3dDevice, pd3dCommandList);
		pExplosiveObject->SetShader(this);



		float directionToken = (uid(dre) - 128.0f) / 256.0f;
		XMFLOAT3 moveDirection;
		XMStoreFloat3(&moveDirection, XMVector3Normalize(XMVectorSet(uid(dre) - 128.0f, 0.0f, uid(dre) - 128.0f, 0.0f)));

		pExplosiveObject->SetMoveDirection(moveDirection);
		pExplosiveObject->SetMoveSpeed(0.0f);
		m_ppObjects[i] = pExplosiveObject;
		m_ppObjects[i]->SetMesh(0, pTankMesh);



	}

	std::list<std::pair<CDiffusedVertex*, CDiffusedVertex*>> lines;




	//�ν��Ͻ��� ���� ����(Structured Buffer)�� �����Ѵ�.
	CreateShaderVariables(pd3dDevice, pd3dCommandList);

}

void CTankShader::ReleaseObjects()
{

}

void CTankShader::AnimateObjects(float fTimeElapsed)
{
	for (int j = 0; j < m_nObjects; j++)
	{
		if (m_ppObjects[j]->IsActive())
			m_ppObjects[j]->Animate(fTimeElapsed);
		else {
			// ��� �ϳ��� Active���� ���ϴٴ� ���� �� �ڵ忡���� Scene�� �Ѿ�� ���� �ǹ��Ѵ�.
			// Active���� ���� 
		}
	}
}

void CTankShader::Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera
	* pCamera)
{

	if (m_ppObjects[0]->IsActive()) {
		CShader::Render(pd3dCommandList, pCamera);
		//��� ���� ��ü�� �ν��Ͻ� �����͸� ���ۿ� �����Ѵ�.
		UpdateShaderVariables(pd3dCommandList);
		//�ϳ��� ���� �����͸� ����Ͽ� ��� ���� ��ü(�ν��Ͻ�)���� �������Ѵ�.
		m_ppObjects[0]->Render(pd3dCommandList, pCamera, m_nObjects);
	}
}


/// //////////////////////////////////////////////////////////////////////////////////////////////////////////

CObstacleShader::CObstacleShader()
{
}

CObstacleShader::~CObstacleShader()
{
	ReleaseObjects();
	ReleaseShaderVariables();
}




void CObstacleShader::CreateShader(ID3D12Device* pd3dDevice, ID3D12RootSignature* pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState * [m_nPipelineStates];
	CInstancingShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}


void CObstacleShader::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList, void* pContext)
{
	std::default_random_engine dre{ std::random_device{}() };
	std::uniform_int_distribution uid(0, 255);

	m_nObjects = 10;
	m_ppObjects = new CGameObject * [m_nObjects];
	float fxPitch = 12.0f * 2.5f;
	float fyPitch = 12.0f * 2.5f;
	float fzPitch = 12.0f * 2.5f;
	CExplosiveObject* pExplosiveObject = NULL;

	//�ν��Ͻ��� ����Ͽ� �������ϱ� ���Ͽ� �ϳ��� ���� ��ü�� �޽��� ������.
	CCubeMeshDiffused* pCubeMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList,
		12.0f, 10.0f, 10.0f);

	for (int i = 0; i < m_nObjects; i++) {
		pExplosiveObject = new CExplosiveObject();
		pExplosiveObject->SetPosition(uid(dre) - 128, 3.0f, uid(dre) - 128);
		pExplosiveObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
		pExplosiveObject->SetRotationSpeed(0.0f);

		float directionToken = (uid(dre) - 128.0f) / 256.0f;
		XMFLOAT3 moveDirection;
		XMStoreFloat3(&moveDirection, XMVector3Normalize(XMVectorSet(uid(dre) - 128.0f, 0.0f, uid(dre) - 128.0f, 0.0f)));

		pExplosiveObject->SetMoveDirection(moveDirection);
		pExplosiveObject->SetMoveSpeed(0.03125f);
		m_ppObjects[i] = pExplosiveObject;
		m_ppObjects[i]->SetMesh(0, pCubeMesh);
	}





	//�ν��Ͻ��� ���� ����(Structured Buffer)�� �����Ѵ�.
	CreateShaderVariables(pd3dDevice, pd3dCommandList);
}

void CObstacleShader::ReleaseObjects()
{

}

//////////////////////////////////////////////////////////////////////////////////////////


CWallShader::CWallShader()
{
}

CWallShader::~CWallShader()
{
	ReleaseObjects();
	ReleaseShaderVariables();
}




void CWallShader::CreateShader(ID3D12Device* pd3dDevice, ID3D12RootSignature* pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState * [m_nPipelineStates];
	CInstancingShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}


void CWallShader::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList, void* pContext)
{
	std::default_random_engine dre{ std::random_device{}() };
	std::uniform_int_distribution uid(0, 255);

	m_nObjects = 1;
	m_ppObjects = new CGameObject * [m_nObjects];
	float fxPitch = 12.0f * 2.5f;
	float fyPitch = 12.0f * 2.5f;
	float fzPitch = 12.0f * 2.5f;
	CGameObject* pGameObject = NULL;
	for (int i = 0; i < m_nObjects; i++) {
		pGameObject = new CGameObject();
		pGameObject->SetPosition(0.0, -3.0f, 0.0);
		m_ppObjects[i] = pGameObject;
	}


	//�ν��Ͻ��� ����Ͽ� �������ϱ� ���Ͽ� �ϳ��� ���� ��ü�� �޽��� ������.
	CCubeMeshDiffused* pCubeMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList,
		1024.0f, 1.0f, 1024.0f);
	m_ppObjects[0]->SetMesh(0, pCubeMesh);


	//�ν��Ͻ��� ���� ����(Structured Buffer)�� �����Ѵ�.
	CreateShaderVariables(pd3dDevice, pd3dCommandList);
}

void CWallShader::ReleaseObjects()
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//void CTankShader::CheckObjectByObjectCollisions()
//{
//	for (int i = 0; i < m_nObjects; i++) m_ppObjects[i]->m_pObjectCollided = NULL;
//	for (int i = 0; i < m_nObjects; i++)
//	{
//		for (int j = (i + 1); j < m_nObjects; j++)
//		{
//			if (m_ppObjects[i]->m_xmOOBB.Intersects(m_ppObjects[j]->m_xmOOBB))
//			{
//				m_ppObjects[i]->m_pObjectCollided = m_ppObjects[j];
//				m_ppObjects[j]->m_pObjectCollided = m_ppObjects[i];
//			}
//		}
//	}
//	for (int i = 0; i < m_nObjects; i++)
//	{
//		if (m_ppObjects[i]->m_pObjectCollided)
//		{
//			XMFLOAT3 xmf3MovingDirection = m_ppObjects[i]->m_xmf3MovingDirection;
//			float fMovingSpeed = m_ppObjects[i]->m_fMovingSpeed;
//			m_ppObjects[i]->m_xmf3MovingDirection = m_ppObjects[i]->m_pObjectCollided->m_xmf3MovingDirection;
//			m_ppObjects[i]->m_fMovingSpeed = m_ppObjects[i]->m_pObjectCollided->m_fMovingSpeed;
//			m_ppObjects[i]->m_pObjectCollided->m_xmf3MovingDirection = xmf3MovingDirection;
//			m_ppObjects[i]->m_pObjectCollided->m_fMovingSpeed = fMovingSpeed;
//			m_ppObjects[i]->m_pObjectCollided->m_pObjectCollided = NULL;
//			m_ppObjects[i]->m_pObjectCollided = NULL;
//		}
//	}
//}
//
//void CTankShader::CheckObjectByWallCollisions()
//{
//	for (int i = 0; i < m_nObjects; i++)
//	{
//		if (m_ppObjects[i]->IsActive() == false) continue;
//		ContainmentType containType = m_pWallsObject->m_xmOOBB.Contains(m_ppObjects[i]->m_xmOOBB);
//		switch (containType)
//		{
//		case DISJOINT:
//		{
//			int nPlaneIndex = -1;
//			for (int j = 0; j < 6; j++)
//			{
//				PlaneIntersectionType intersectType = m_ppObjects[i]->m_xmOOBB.Intersects(XMLoadFloat4(&m_pWallsObject->m_pxmf4WallPlanes[j]));
//				if (intersectType == BACK)
//				{
//					nPlaneIndex = j;
//					break;
//				}
//			}
//			if (nPlaneIndex != -1)
//			{
//				XMVECTOR xmvNormal = XMVectorSet(m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].x, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].y, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].z, 0.0f);
//				XMVECTOR xmvReflect = XMVector3Reflect(XMLoadFloat3(&m_ppObjects[i]->m_xmf3MovingDirection), xmvNormal);
//				XMStoreFloat3(&m_ppObjects[i]->m_xmf3MovingDirection, xmvReflect);
//			}
//			break;
//		}
//		case INTERSECTS:
//		{
//			int nPlaneIndex = -1;
//			for (int j = 0; j < 6; j++)
//			{
//				PlaneIntersectionType intersectType = m_ppObjects[i]->m_xmOOBB.Intersects(XMLoadFloat4(&m_pWallsObject->m_pxmf4WallPlanes[j]));
//				if (intersectType == INTERSECTING)
//				{
//					nPlaneIndex = j;
//					break;
//				}
//			}
//			if (nPlaneIndex != -1)
//			{
//				XMVECTOR xmvNormal = XMVectorSet(m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].x, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].y, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].z, 0.0f);
//				XMVECTOR xmvReflect = XMVector3Reflect(XMLoadFloat3(&m_ppObjects[i]->m_xmf3MovingDirection), xmvNormal);
//				XMStoreFloat3(&m_ppObjects[i]->m_xmf3MovingDirection, xmvReflect);
//			}
//			break;
//		}
//		case CONTAINS:
//			break;
//		}
//	}
//}
//
//void CTankShader::CheckPlayerByWallCollision()
//{
//	BoundingOrientedBox xmOOBBPlayerMoveCheck;
//	m_pWallsObject->m_xmOOBBPlayerMoveCheck.Transform(xmOOBBPlayerMoveCheck, XMLoadFloat4x4(&m_pWallsObject->m_xmf4x4World));
//	XMStoreFloat4(&xmOOBBPlayerMoveCheck.Orientation, XMQuaternionNormalize(XMLoadFloat4(&xmOOBBPlayerMoveCheck.Orientation)));
//
//	//if (!xmOOBBPlayerMoveCheck.Intersects(m_pPlayer->m_xmOOBB)) m_pWallsObject->SetPosition(m_pPlayer->m_xmf3Position);
//}
//
//void CTankShader::CheckObjectByBulletCollisions()
//{
//	CBulletObject** ppBullets = ((CTankPlayer*)m_pPlayer)->m_ppBullets;
//	for (int i = 0; i < m_nShaders; i++)
//	{
//		for (int j = 0; j < BULLETS; j++)
//		{
//			if (ppBullets[j]->IsActive() && (m_pShaders[0]->) && m_ppObjects[i]->m_xmOOBB.Intersects(ppBullets[j]->m_xmOOBB))
//			{
//				CExplosiveObject* pExplosiveObject = (CExplosiveObject*)m_ppObjects[i];
//				pExplosiveObject->m_bBlowingUp = true;
//				ppBullets[j]->Reset();
//			}
//		}
//	}
//}