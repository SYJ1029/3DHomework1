#include "stdafx.h"
#include "Scene.h"
#include "GraphicsPipeline.h"

// CStartScene과 CMenuScene을 이곳에서 정의합니다


CStartScene::CStartScene()
{

}
CStartScene::~CStartScene()
{

}

void CStartScene::BuildObjects()
{
	CExplosiveObject::PrepareExplosion();

	m_nObjects = 4;
	m_ppObjects = new CGameObject * [m_nObjects];

	// 3의 경우엔 4개의 CubeMesh면 구성할 수 있다
	CCubeMesh* pCubeMesh = new CCubeMesh(2.0f, 0.75f, 1.0f);

	m_ppObjects[0] = new CExplosiveObject();
	m_ppObjects[0]->SetMesh(pCubeMesh);
	m_ppObjects[0]->SetColor(RGB(255, 0, 0));
	m_ppObjects[0]->SetPosition(0.0f, 2.0f, 0.0f);
	m_ppObjects[0]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	m_ppObjects[0]->SetRotationSpeed(0.0f);
	m_ppObjects[0]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 0.0f));
	m_ppObjects[0]->SetMovingSpeed(0.0f);

	m_ppObjects[1] = new CExplosiveObject();
	m_ppObjects[1]->SetMesh(pCubeMesh);
	m_ppObjects[1]->SetColor(RGB(255, 0, 0));
	m_ppObjects[1]->SetPosition(0.0f, 0.0f, 0.0f);
	m_ppObjects[1]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	m_ppObjects[1]->SetRotationSpeed(0.0f);
	m_ppObjects[1]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 0.0f));
	m_ppObjects[1]->SetMovingSpeed(0.0f);

	m_ppObjects[2] = new CExplosiveObject();
	m_ppObjects[2]->SetMesh(pCubeMesh);
	m_ppObjects[2]->SetColor(RGB(255, 0, 0));
	m_ppObjects[2]->SetPosition(0.0f, -2.0f, 0.0f);
	m_ppObjects[2]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	m_ppObjects[2]->SetRotationSpeed(0.0f);
	m_ppObjects[2]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 0.0f));
	m_ppObjects[2]->SetMovingSpeed(0.0f);

	pCubeMesh->Release();

	pCubeMesh = new CCubeMesh(0.75f, 5.0f, 1.0f);

	m_ppObjects[3] = new CExplosiveObject();
	m_ppObjects[3]->SetMesh(pCubeMesh);
	m_ppObjects[3]->SetColor(RGB(255, 0, 0));
	m_ppObjects[3]->SetPosition(1.0f, 0.0f, 0.0f);
	m_ppObjects[3]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	m_ppObjects[3]->SetRotationSpeed(0.0f);
	m_ppObjects[3]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 0.0f));
	m_ppObjects[3]->SetMovingSpeed(0.0f);
	
	//CNameMesh* pNameMesh = new CNameMesh(4.0f, 1.0f, 4.0f);
	//m_ppObjects[m_nObjects]->SetMesh(pNameMesh);
}
void CStartScene::ReleaseObjects()
{

}

void CStartScene::Animate(float fElapsedTime)
{
	for (int i = 0; i < m_nObjects; i++) m_ppObjects[i]->Animate(fElapsedTime);
}
void CStartScene::Render(HDC hDCFrameBuffer, CCamera* pCamera)
{
	CGraphicsPipeline::SetViewport(&pCamera->m_Viewport);

	CGraphicsPipeline::SetViewPerspectiveProjectTransform(&pCamera->m_xmf4x4ViewPerspectiveProject);

	for (int i = 0; i < m_nObjects; i++) m_ppObjects[i]->Render(hDCFrameBuffer, pCamera);
}

void CStartScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{

}
void CStartScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{

}

CGameObject* CStartScene::PickObjectPointedByCursor(int xClient, int yClient, CCamera* pCamera)
{

	return NULL;
}


CMenuScene::CMenuScene()
{

}
CMenuScene::~CMenuScene()
{

}

void CMenuScene::BuildObjects()
{

}
void CMenuScene::ReleaseObjects()
{

}

void CMenuScene::Animate(float fElapsedTime)
{

}
void CMenuScene::Render(HDC hDCFrameBuffer, CCamera* pCamera)
{

}

void CMenuScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{

}
void CMenuScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			::PostQuitMessage(0);
			break;
		}
		break;
	default:
		break;
	}
}

CGameObject* CMenuScene::PickObjectPointedByCursor(int xClient, int yClient, CCamera* pCamera)
{

	return NULL;
}