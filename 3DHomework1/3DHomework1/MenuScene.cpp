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

	switch (nMessageID)
	{
	case WM_RBUTTONDOWN:
		break;
	case WM_LBUTTONDOWN:
		//::SetCapture(hWnd);
		std::cout << "hi";
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