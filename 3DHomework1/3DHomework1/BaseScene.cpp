#include "stdafx.h"
#include "Scene.h"


CBaseScene::CBaseScene()
{
	level = 0;
}
CBaseScene::~CBaseScene()
{

}


void CBaseScene::Setlevel(int newLevel)
{
	level = newLevel;

	levelFlag = true;
}

CBaseScene* CBaseScene::SetScene()
{
	switch (level) {
	case 0:
		return new CStartScene();
	case 1: 
		return new CLevel1Scene();
	case 2:
		return new CTankScene(); 
	case 3:
		return new CMenuScene();
	}

	return new CBaseScene();
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
	m_pPlayer = pPlayer;
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
