#include "stdafx.h"
#include "Scene.h"
#include "GraphicsPipeline.h"

// CStartScene과 CMenuScene을 이곳에서 정의합니다




CMenuScene::CMenuScene()
{

}
CMenuScene::~CMenuScene()
{

}

void CMenuScene::BuildObjects()
{
	CExplosiveObject::PrepareExplosion();

	m_nObjects = 2;
	m_ppObjects = new CGameObject * [m_nObjects];

	std::list<std::pair<CVertex*, CVertex*>> lines;

	CNameMesh* pNameMesh = new CNameMesh(2.0f, 2.0f, 0.5f, "Tutorial.txt", lines);

	m_ppObjects[0] = new CExplosiveObject();
	m_ppObjects[0]->SetMesh(pNameMesh);
	m_ppObjects[0]->SetColor(RGB(255, 0, 0));
	m_ppObjects[0]->SetPosition(-2.0f, 6.0f, 10.0f);
	m_ppObjects[0]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	m_ppObjects[0]->SetRotationSpeed(0.0f);
	m_ppObjects[0]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 0.0f));
	m_ppObjects[0]->SetMovingSpeed(0.0f);

	CNameMesh* pNameMesh2 = new CNameMesh(8.0f, 4.0f, 2.0f, "End.txt", lines);

	m_ppObjects[1] = new CExplosiveObject();
	m_ppObjects[1]->SetMesh(pNameMesh2);
	m_ppObjects[1]->SetColor(RGB(255, 0, 0));
	m_ppObjects[1]->SetPosition(0.0f, 0.0f, 0.0f);
	m_ppObjects[1]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	m_ppObjects[1]->SetRotationSpeed(0.0f);
	m_ppObjects[1]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 0.0f));
	m_ppObjects[1]->SetMovingSpeed(0.0f);

}
void CMenuScene::ReleaseObjects()
{

}

void CMenuScene::Animate(float fElapsedTime)
{
	for (int i = 0; i < m_nObjects; i++) {
		m_ppObjects[i]->Animate(fElapsedTime);
	}
}
void CMenuScene::Render(HDC hDCFrameBuffer, CCamera* pCamera)
{
	CGraphicsPipeline::SetViewport(&pCamera->m_Viewport);

	CGraphicsPipeline::SetViewPerspectiveProjectTransform(&pCamera->m_xmf4x4ViewPerspectiveProject);

	for (int i = 0; i < m_nObjects; i++) m_ppObjects[i]->Render(hDCFrameBuffer, pCamera);
}

void CMenuScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{

	switch (nMessageID)
	{
	case WM_RBUTTONDOWN:
		break;
	case WM_LBUTTONDOWN:
		//::SetCapture(hWnd);
		PickObjectPointedByCursor(LOWORD(lParam), HIWORD(lParam), m_pPlayer->m_pCamera);
		break;
	case WM_LBUTTONUP:
		break;
	case WM_RBUTTONUP:
		//::ReleaseCapture();
		break;
	case WM_MOUSEMOVE:
		break;
	default:
		break;
	}
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