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

	CCubeMesh* pCubeMesh = new CCubeMesh(2.0f, 1.0f, 2.0f);

	m_pPlayer->SetMesh(pCubeMesh);

	m_nObjects = 1;
	m_ppObjects = new CGameObject * [m_nObjects];

	std::list<std::pair<CVertex*, CVertex*>> lines;

	CNameMesh* pNameMesh = new CNameMesh(24.0f, 4.0f, 2.0f, "Rail.txt", lines);

	m_ppObjects[0] = new CExplosiveObject();
	m_ppObjects[0]->SetMesh(pNameMesh);
	m_ppObjects[0]->SetColor(RGB(255, 0, 0));
	m_ppObjects[0]->SetPosition(-3.0f, 3.0f, 10.0f);
	m_ppObjects[0]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	m_ppObjects[0]->SetRotationSpeed(0.0f);
	m_ppObjects[0]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 0.0f));
	m_ppObjects[0]->SetMovingSpeed(0.0f);
}
void CLevel1Scene::ReleaseObjects()
{
	if (CExplosiveObject::m_pExplosionMesh) CExplosiveObject::m_pExplosionMesh->Release();

	for (int i = 0; i < m_nObjects; i++) if (m_ppObjects[i]) delete m_ppObjects[i];
	if (m_ppObjects) delete[] m_ppObjects;

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
	for (int i = 0; i < m_nObjects; i++) {
		m_ppObjects[i]->Animate(fElapsedTime);
	
	}
	m_pPlayer->Animate(fElapsedTime);
}
void CLevel1Scene::Render(HDC hDCFrameBuffer, CCamera* pCamera)
{
	CGraphicsPipeline::SetViewport(&pCamera->m_Viewport);

	CGraphicsPipeline::SetViewPerspectiveProjectTransform(&pCamera->m_xmf4x4ViewPerspectiveProject);

	for (int i = 0; i < m_nObjects; i++) m_ppObjects[i]->Render(hDCFrameBuffer, pCamera);
	if (m_pPlayer) m_pPlayer->Render(hDCFrameBuffer, pCamera);
}

void CLevel1Scene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{

}
void CLevel1Scene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			Setlevel(3);
			SetScene();
			break;
		case 'N':
			Setlevel(2);
			SetScene();
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

CGameObject* CLevel1Scene::PickObjectPointedByCursor(int xClient, int yClient, CCamera* pCamera)
{

	return NULL;
}