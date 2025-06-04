#include "Scene.h"

CTitleScene::CTitleScene()
{
}

CTitleScene::~CTitleScene()
{

}

void CTitleScene::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList)
{
	m_pd3dGraphicsRootSignature = CreateGraphicsRootSignature(pd3dDevice);
	m_nShaders = 2;
	m_pShaders = new CInstancingShader*[m_nShaders];
	m_pShaders[0] = new CTitleShader;
	m_pShaders[1] = new CTitleShader;
	m_pShaders[0]->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature);
	m_pShaders[0]->SetFileName("3D게임 프로그래밍.txt");
	m_pShaders[0]->BuildObjects(pd3dDevice, pd3dCommandList);
	m_pShaders[0]->SetObjPos(XMFLOAT3(0.0f, 0.0f, 0.0f));

	m_pShaders[1]->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature);
	m_pShaders[1]->SetFileName("송영준.txt");
	m_pShaders[1]->BuildObjects(pd3dDevice, pd3dCommandList);
	m_pShaders[1]->SetObjPos(XMFLOAT3(0.0f, -3.0f, 0.0f));
}

void CTitleScene::ReleaseObjects()
{
	if (m_pd3dGraphicsRootSignature) m_pd3dGraphicsRootSignature->Release();
	for (int i = 0; i < m_nShaders; i++)
	{
		m_pShaders[i]->ReleaseShaderVariables();
		m_pShaders[i]->ReleaseObjects();
	}
	if (m_pShaders) delete[] m_pShaders;
}

void CTitleScene::AnimateObjects(float fTimeElapsed)
{
	for (int i = 0; i < m_nShaders; i++)
	{
		m_pShaders[i]->AnimateObjects(fTimeElapsed);
	}
}

void CTitleScene::Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera)
{
	pCamera->SetViewportsAndScissorRects(pd3dCommandList);
	pd3dCommandList->SetGraphicsRootSignature(m_pd3dGraphicsRootSignature);
	pCamera->UpdateShaderVariables(pd3dCommandList);
	for (int i = 0; i < m_nShaders; i++)
	{
		m_pShaders[i]->Render(pd3dCommandList, pCamera);
	}
}