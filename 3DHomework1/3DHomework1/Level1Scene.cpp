#include "stdafx.h"
#include "Scene.h"
#include "GraphicsPipeline.h"


CLevel1Scene::CLevel1Scene()
{

}
CLevel1Scene::~CLevel1Scene()
{

}

void CLevel1Scene::BuildObjects()
{

}
void CLevel1Scene::ReleaseObjects()
{

}

void CLevel1Scene::CheckObjectByObjectCollisions()
{

}
void CLevel1Scene::CheckObjectByWallCollisions()
{

}
void CLevel1Scene::CheckPlayerByWallCollision()
{

}
void CLevel1Scene::CheckObjectByBulletCollisions()
{

}

void CLevel1Scene::SetPlayer(CPlayer* pPlayer)
{
	m_pPlayer = pPlayer;
}

void CLevel1Scene::Animate(float fElapsedTime)
{

}
void CLevel1Scene::Render(HDC hDCFrameBuffer, CCamera* pCamera)
{

}

void CLevel1Scene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{

}
void CLevel1Scene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{

}

CGameObject* CLevel1Scene::PickObjectPointedByCursor(int xClient, int yClient, CCamera* pCamera)
{

	return NULL;
}