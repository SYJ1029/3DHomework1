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


void CTankShader::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList)
{
	std::default_random_engine dre{ std::random_device{}() };
	std::uniform_int_distribution uid(0, 255);


	m_nObjects = 9;
	m_ppObjects = new CGameObject * [m_nObjects];
	float fxPitch = 12.0f * 2.5f;
	float fyPitch = 12.0f * 2.5f;
	float fzPitch = 12.0f * 2.5f;
	CExplosiveObject* pExplosiveObject = NULL;
	for (int i = 0; i < m_nObjects; i++) {
		pExplosiveObject = new CExplosiveObject();
		pExplosiveObject->SetPosition(uid(dre) - 128, 0.0f, uid(dre) - 128);
		pExplosiveObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
		pExplosiveObject->SetRotationSpeed(0.0f);

		float directionToken = (uid(dre) - 128.0f) / 256.0f;
		XMFLOAT3 moveDirection;
		XMStoreFloat3(&moveDirection, XMVector3Normalize(XMVectorSet(uid(dre) - 128.0f, 0.0f, uid(dre) - 128.0f, 0.0f)));

		pExplosiveObject->SetMoveDirection(moveDirection);
		pExplosiveObject->SetMoveSpeed(0.0625f);
		m_ppObjects[i] = pExplosiveObject;
	}

	std::list<std::pair<CDiffusedVertex*, CDiffusedVertex*>> lines;

	//인스턴싱을 사용하여 렌더링하기 위하여 하나의 게임 객체만 메쉬를 가진다.
	CTankMeshDiffused* pTankMesh = new CTankMeshDiffused(pd3dDevice, pd3dCommandList,
		12.0f, 3.0f, 12.0f);
	m_ppObjects[0]->SetMesh(pTankMesh);


	//인스턴싱을 위한 버퍼(Structured Buffer)를 생성한다.
	CreateShaderVariables(pd3dDevice, pd3dCommandList);
}

void CTankShader::ReleaseObjects()
{

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
	* pd3dCommandList)
{
	std::default_random_engine dre{ std::random_device{}() };
	std::uniform_int_distribution uid(0, 255);

	m_nObjects = 10;
	m_ppObjects = new CGameObject * [m_nObjects];
	float fxPitch = 12.0f * 2.5f;
	float fyPitch = 12.0f * 2.5f;
	float fzPitch = 12.0f * 2.5f;
	CExplosiveObject* pExplosiveObject = NULL;
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
	}


	//인스턴싱을 사용하여 렌더링하기 위하여 하나의 게임 객체만 메쉬를 가진다.
	CCubeMeshDiffused* pCubeMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList,
		12.0f, 10.0f, 10.0f);
	m_ppObjects[0]->SetMesh(pCubeMesh);


	//인스턴싱을 위한 버퍼(Structured Buffer)를 생성한다.
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
	* pd3dCommandList)
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


	//인스턴싱을 사용하여 렌더링하기 위하여 하나의 게임 객체만 메쉬를 가진다.
	CCubeMeshDiffused* pCubeMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList,
		1024.0f, 1.0f, 1024.0f);
	m_ppObjects[0]->SetMesh(pCubeMesh);


	//인스턴싱을 위한 버퍼(Structured Buffer)를 생성한다.
	CreateShaderVariables(pd3dDevice, pd3dCommandList);
}

void CWallShader::ReleaseObjects()
{

}