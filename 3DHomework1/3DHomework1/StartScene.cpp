#include "stdafx.h"
#include "Scene.h"
#include "GraphicsPipeline.h"

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

	std::list<std::pair<CVertex*, CVertex*>> lines;

	CNameMesh* pNameMesh = new CNameMesh(2.0f, 2.0f, 0.5f, "3D게임 프로그래밍.txt", lines);

	m_ppObjects[0] = new CExplosiveObject();
	m_ppObjects[0]->SetMesh(pNameMesh);
	m_ppObjects[0]->SetColor(RGB(255, 0, 0));
	m_ppObjects[0]->SetPosition(0.0f, 4.0f, 4.0f);
	m_ppObjects[0]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	m_ppObjects[0]->SetRotationSpeed(90.0f);
	m_ppObjects[0]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 0.0f));
	m_ppObjects[0]->SetMovingSpeed(0.0f);

	CNameMesh* pNameMesh2 = new CNameMesh(8.0f, 4.0f, 2.0f, "송영준.txt", lines);

	m_ppObjects[1] = new CExplosiveObject();
	m_ppObjects[1]->SetMesh(pNameMesh2);
	m_ppObjects[1]->SetColor(RGB(255, 0, 0));
	m_ppObjects[1]->SetPosition(0.0f, 0.0f, 0.0f);
	m_ppObjects[1]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	m_ppObjects[1]->SetRotationSpeed(90.0f);
	m_ppObjects[1]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 0.0f));
	m_ppObjects[1]->SetMovingSpeed(0.0f);



	//CNameMesh* pNameMesh = new CNameMesh(4.0f, 1.0f, 4.0f);
	//m_ppObjects[m_nObjects]->SetMesh(pNameMesh);
}
void CStartScene::ReleaseObjects()
{

}

void CStartScene::Animate(float fElapsedTime)
{
	if (pExplosiveObject != NULL && !(pExplosiveObject->m_bBlowingUp) && pExplosiveObject->m_bBlowingUp == false) {
		Setlevel(3);
	}

	for (int i = 0; i < m_nObjects; i++) {
		m_ppObjects[i]->Animate(fElapsedTime);
	}
}
void CStartScene::Render(HDC hDCFrameBuffer, CCamera* pCamera)
{
	CGraphicsPipeline::SetViewport(&pCamera->m_Viewport);

	CGraphicsPipeline::SetViewPerspectiveProjectTransform(&pCamera->m_xmf4x4ViewPerspectiveProject);

	for (int i = 0; i < m_nObjects; i++) m_ppObjects[i]->Render(hDCFrameBuffer, pCamera);
}

void CStartScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_RBUTTONDOWN:
		break;
	case WM_LBUTTONDOWN:
		//::SetCapture(hWnd);
	{

		pExplosiveObject = (CExplosiveObject*)PickObjectPointedByCursor(LOWORD(lParam), HIWORD(lParam), m_pPlayer->m_pCamera);
		if (pExplosiveObject != NULL)
			pExplosiveObject->m_bBlowingUp = true;
	}
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
void CStartScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
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

CGameObject* CStartScene::PickObjectPointedByCursor(int xClient, int yClient, CCamera* pCamera)
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
