#include "Scene.h"

CMenuScene::CMenuScene()
{

}

CMenuScene::~CMenuScene()
{

}


void CMenuScene::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList)
{
	m_pd3dGraphicsRootSignature = CreateGraphicsRootSignature(pd3dDevice);
	m_nShaders = 5;
	m_pShaders = new CInstancingShader * [m_nShaders];

	m_pShaders[0] = new CMenuShader;
	m_pShaders[1] = new CMenuShader;
	m_pShaders[2] = new CMenuShader;
	m_pShaders[3] = new CMenuShader;
	m_pShaders[4] = new CMenuShader;

	m_pShaders[0]->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature);
	m_pShaders[0]->SetFileName("Tutorial.txt");
	m_pShaders[0]->BuildObjects(pd3dDevice, pd3dCommandList);
	m_pShaders[0]->SetObjPos(XMFLOAT3(0.0f, 6.0f, 0.0f));

	m_pShaders[1]->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature);
	m_pShaders[1]->SetFileName("Start.txt");
	m_pShaders[1]->BuildObjects(pd3dDevice, pd3dCommandList);
	m_pShaders[1]->SetObjPos(XMFLOAT3(0.0f, 3.0f, 0.0f));

	m_pShaders[2]->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature);
	m_pShaders[2]->SetFileName("Level-1.txt");
	m_pShaders[2]->BuildObjects(pd3dDevice, pd3dCommandList);
	m_pShaders[2]->SetObjPos(XMFLOAT3(0.0f, 0.0f, 0.0f));

	m_pShaders[3]->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature);
	m_pShaders[3]->SetFileName("Level-2.txt");
	m_pShaders[3]->BuildObjects(pd3dDevice, pd3dCommandList);
	m_pShaders[3]->SetObjPos(XMFLOAT3(0.0f, -3.0f, 0.0f));

	m_pShaders[4]->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature);
	m_pShaders[4]->SetFileName("End.txt");
	m_pShaders[4]->BuildObjects(pd3dDevice, pd3dCommandList);
	m_pShaders[4]->SetObjPos(XMFLOAT3(0.0f, -6.0f, 0.0f));
}