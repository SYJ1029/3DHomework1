#include "stdafx.h"
#include "Scene.h"


CBaseScene::CBaseScene()
{

}
CBaseScene::~CBaseScene()
{

}

void CBaseScene::BuildObjects()
{

}
void CBaseScene::ReleaseObjects()
{

}

void CBaseScene::CheckObjectByObjectCollisions()
{

}
void CBaseScene::CheckObjectByWallCollisions()
{

}
void CBaseScene::CheckPlayerByWallCollision()
{

}
void CBaseScene::CheckObjectByBulletCollisions()
{

}

void CBaseScene::SetPlayer(CPlayer* pPlayer)
{

}

void CBaseScene::Animate(float fElapsedTime)
{

}
void CBaseScene::Render(HDC hDCFrameBuffer, CCamera* pCamera)
{

}

void CBaseScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{

}
void CBaseScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{

}

CGameObject* CBaseScene::PickObjectPointedByCursor(int xClient, int yClient, CCamera* pCamera)
{

	return NULL;
}
