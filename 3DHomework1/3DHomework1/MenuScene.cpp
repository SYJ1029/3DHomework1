#include "stdafx.h"
#include "Scene.h"
#include "GraphicsPipeline.h"

// CStartScene�� CMenuScene�� �̰����� �����մϴ�


CStartScene::CStartScene()
{

}
CStartScene::~CStartScene()
{

}

void CStartScene::BuildObjects()
{
	CExplosiveObject::PrepareExplosion();

	m_nObjects = 2;
	m_ppObjects = new CGameObject * [m_nObjects];
}
void CStartScene::ReleaseObjects()
{

}

void CStartScene::Animate(float fElapsedTime)
{

}
void CStartScene::Render(HDC hDCFrameBuffer, CCamera* pCamera)
{

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