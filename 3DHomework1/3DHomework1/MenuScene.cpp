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

void CMenuScene::CheckLevel(CGameObject* picked) 
{
	if (picked == nullptr) return;

	switch ((int)picked->m_xmf4x4World._42 / 3) {
	case 1:
		break;
	case 0:
		Setlevel(1);
		SetScene();
		break;
	case -1:
		Setlevel(1);
		SetScene();
		break;
	case -2:
		Setlevel(2);
		SetScene();
		break;
	case -3:
		::PostQuitMessage(0);
		break;
	default:
		::PostQuitMessage(15578884);
	}

}

void CMenuScene::BuildObjects()
{
	

	CExplosiveObject::PrepareExplosion();

	m_nObjects = 5;
	m_ppObjects = new CGameObject * [m_nObjects];

	std::list<std::pair<CVertex*, CVertex*>> lines;

	CNameMesh* pNameMesh = new CNameMesh(24.0f, 4.0f, 2.0f, "Tutorial.txt", lines);

	m_ppObjects[0] = new CExplosiveObject();
	m_ppObjects[0]->SetMesh(pNameMesh);
	m_ppObjects[0]->SetColor(RGB(255, 0, 0));
	m_ppObjects[0]->SetPosition(-3.0f, 3.0f, 10.0f);
	m_ppObjects[0]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	m_ppObjects[0]->SetRotationSpeed(0.0f);
	m_ppObjects[0]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 0.0f));
	m_ppObjects[0]->SetMovingSpeed(0.0f);

	CNameMesh* pNameMesh2 = new CNameMesh(24.0f, 4.0f, 2.0f, "Start.txt", lines);

	m_ppObjects[1] = new CExplosiveObject();
	m_ppObjects[1]->SetMesh(pNameMesh2);
	m_ppObjects[1]->SetColor(RGB(255, 0, 0));
	m_ppObjects[1]->SetPosition(-3.0f, 0.0f, 10.0f);
	m_ppObjects[1]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	m_ppObjects[1]->SetRotationSpeed(0.0f);
	m_ppObjects[1]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 0.0f));
	m_ppObjects[1]->SetMovingSpeed(0.0f);

	CNameMesh* pNameMesh3 = new CNameMesh(24.0f, 4.0f, 2.0f, "Level-1.txt", lines);

	m_ppObjects[2] = new CExplosiveObject();
	m_ppObjects[2]->SetMesh(pNameMesh3);
	m_ppObjects[2]->SetColor(RGB(255, 0, 0));
	m_ppObjects[2]->SetPosition(-3.0f, -3.0f, 10.0f);
	m_ppObjects[2]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	m_ppObjects[2]->SetRotationSpeed(0.0f);
	m_ppObjects[2]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 0.0f));
	m_ppObjects[2]->SetMovingSpeed(0.0f);

	CNameMesh* pNameMesh4 = new CNameMesh(24.0f, 4.0f, 2.0f, "Level-2.txt", lines);

	m_ppObjects[3] = new CExplosiveObject();
	m_ppObjects[3]->SetMesh(pNameMesh4);
	m_ppObjects[3]->SetColor(RGB(255, 0, 0));
	m_ppObjects[3]->SetPosition(-3.0f, -6.0f, 10.0f);
	m_ppObjects[3]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	m_ppObjects[3]->SetRotationSpeed(0.0f);
	m_ppObjects[3]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 0.0f));
	m_ppObjects[3]->SetMovingSpeed(0.0f);

	CNameMesh* pNameMesh5 = new CNameMesh(24.0f, 4.0f, 2.0f, "End.txt", lines);

	m_ppObjects[4] = new CExplosiveObject();
	m_ppObjects[4]->SetMesh(pNameMesh5);
	m_ppObjects[4]->SetColor(RGB(255, 0, 0));
	m_ppObjects[4]->SetPosition(-3.0f, -9.0f, 10.0f);
	m_ppObjects[4]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	m_ppObjects[4]->SetRotationSpeed(0.0f);
	m_ppObjects[4]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 0.0f));
	m_ppObjects[4]->SetMovingSpeed(0.0f);

}
void CMenuScene::ReleaseObjects()
{
	if (CExplosiveObject::m_pExplosionMesh) CExplosiveObject::m_pExplosionMesh->Release();

	for (int i = 0; i < m_nObjects; i++) if (m_ppObjects[i]) delete m_ppObjects[i];
	if (m_ppObjects) delete[] m_ppObjects;
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
		CheckLevel(PickObjectPointedByCursor(LOWORD(lParam), HIWORD(lParam), m_pPlayer->m_pCamera));
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
	XMFLOAT3 xmf3PickPosition;
	xmf3PickPosition.x = (((2.0f * xClient) / (float)pCamera->m_Viewport.m_nWidth) - 1) / pCamera->m_xmf4x4PerspectiveProject._11;
	xmf3PickPosition.y = -(((2.0f * yClient) / (float)pCamera->m_Viewport.m_nHeight) - 1) / pCamera->m_xmf4x4PerspectiveProject._22;
	xmf3PickPosition.z = 1.0f;

	XMVECTOR xmvPickPosition = XMLoadFloat3(&xmf3PickPosition);
	XMMATRIX xmmtxView = XMLoadFloat4x4(&pCamera->m_xmf4x4View);

	int nIntersected = 0;
	float fNearestHitDistance = FLT_MAX;
	CGameObject* pNearestObject = NULL;
	for (int i = 0; i < m_nObjects; i++)
	{
		float fHitDistance = FLT_MAX;
		nIntersected = m_ppObjects[i]->PickObjectByRayIntersection(xmvPickPosition, xmmtxView, &fHitDistance);
		if ((nIntersected > 0) && (fHitDistance < fNearestHitDistance))
		{
			fNearestHitDistance = fHitDistance;
			pNearestObject = m_ppObjects[i];
		}
	}
	return(pNearestObject);
}