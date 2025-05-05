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

	CNameMesh* pNameMesh = new CNameMesh(24.0f, 4.0f, 2.0f, "Rail.txt", lines);

	pNameMesh->Loadlines("Rail.txt", lines);

	m_ppObjects[0] = new CExplosiveObject();
	m_ppObjects[0]->SetMesh(pNameMesh);
	m_ppObjects[0]->SetColor(RGB(255, 0, 0));
	m_ppObjects[0]->SetPosition(0.0f, 0.0f, 0.0f);
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

	MoveByLine(lines, fElapsedTime);
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
	switch (nMessageID)
	{
	case WM_LBUTTONDOWN:
		::SetCapture(hWnd);
		break;
	case WM_LBUTTONUP:
		::ReleaseCapture();
		break;
	case WM_RBUTTONUP:
		break;
	case WM_MOUSEMOVE:
		break;
	default:
		break;
	}
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

void CLevel1Scene::MoveByLine(std::list<std::pair<CVertex*, CVertex*>>& lines, float fElapsedTime)
{

	auto [start, end] = lines.front();
	


	XMVECTOR playerPos = XMLoadFloat3(&m_pPlayer->m_xmf3Position);
	XMVECTOR endPos = XMLoadFloat3(&end->m_xmf3Position);

	XMVECTOR dir = XMVectorSubtract(endPos, playerPos);
	dir = XMVector3Normalize(dir);

	// 이동 속도
	float speed = 5.0f; // 예시

	// 이동
	playerPos = XMVectorAdd(playerPos, XMVectorScale(dir, speed * fElapsedTime));
	XMStoreFloat3(&m_pPlayer->m_xmf3Position, playerPos);

	// 목표에 거의 다 왔으면 다음 선으로
	XMVECTOR diff = XMVectorSubtract(endPos, playerPos);
	if (XMVectorGetX(XMVector3Length(diff)) < 0.1f) {
		m_pPlayer->SetPosition(end->m_xmf3Position.x, end->m_xmf3Position.y, end->m_xmf3Position.z);
		lines.pop_front();
		if (lines.size() <= 0) {
			Setlevel(2);
		}
		
	}
}