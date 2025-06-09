#include "Scene.h"
#include "Player.h"


CTankScene::CTankScene()
{

}

CTankScene::~CTankScene()
{

}


void CTankScene::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList)
{
	m_pd3dGraphicsRootSignature = CreateGraphicsRootSignature(pd3dDevice);
	m_nShaders = 13;
	m_pShaders = new CInstancingShader * [m_nShaders];

	int i;

	for (i = 0; i < 10; ++i) {
		m_pShaders[i] = new CTankShader;

		m_pShaders[i]->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature);
		m_pShaders[i]->SetFileName("You Win!.txt");
		m_pShaders[i]->BuildObjects(pd3dDevice, pd3dCommandList);
	}

	
	m_pShaders[i] = new CObstacleShader;

	m_pShaders[i]->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature);
	m_pShaders[i]->SetFileName("You Win!.txt");
	m_pShaders[i++]->BuildObjects(pd3dDevice, pd3dCommandList);	

	m_pShaders[i] = new CWallShader;

	m_pShaders[i]->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature);
	m_pShaders[i]->SetFileName("You Win!.txt");
	m_pShaders[i++]->BuildObjects(pd3dDevice, pd3dCommandList);



	m_pShaders[i] = new CTitleShader;
	m_pShaders[i]->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature);
	m_pShaders[i]->SetFileName("You Win!.txt");
	m_pShaders[i]->BuildObjects(pd3dDevice, pd3dCommandList);
	m_pShaders[i++]->m_ppObjects[0]->SetActive(false);
}


void CTankScene::AnimateObjects(float fTimeElapsed)
{
	if (CheckGameEnd()) {
		m_pShaders[m_nShaders - 1]->m_ppObjects[0]->SetActive(true);
	}

	for (int i = 0; i < m_nShaders; i++)
	{
		m_pShaders[i]->AnimateObjects(fTimeElapsed);
	}

	CheckObjectByBulletCollisions();

}

bool CTankScene::CheckGameEnd()
{
	for (int i = 0; i < m_nShaders; ++i) {
		// 하나라도 Tankshader가 active 하다면 끝나지 않은 것

		if(i >= 0 && i < 10 && m_pShaders[i]->m_ppObjects[0]->IsActive())
			return false;


	}

	
	return true;
}


UINT CTankScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM
	lParam, CCamera* pCamera)
{

	CTankPlayer* pPlayer = dynamic_cast<CTankPlayer*>(pCamera->GetPlayer());
	switch (nMessageID)
	{
	case WM_LBUTTONDOWN:
		::SetCapture(hWnd);
		::GetCursorPos(&mousePoint);
		break;

	case WM_RBUTTONDOWN:
		::SetCapture(hWnd);
		::GetCursorPos(&mousePoint);
		// 이전 피킹 값은 지운다
		pPlayer->pickedObject = nullptr;

		if (usePicking) {

			pPlayer->pickedObject = dynamic_cast<CExplosiveObject*>(PickObjectPointedByCursor(LOWORD(lParam), HIWORD(lParam), pCamera));
		}


		break;
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
		//마우스 캡쳐를 해제한다.
		::ReleaseCapture();
		break;
	}

	return S_SAFE;
}

bool CTankScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM
	lParam)
{
	switch (nMessageID)
	{
	case WM_KEYUP:
		switch (wParam)
		{
		case VK_ESCAPE:
			::PostQuitMessage(0);
			break;
		
		case VK_CONTROL:
			break;
		case 'A': case 'a':
			break;
		default:
			break;
		}
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'A' : case 'a':
			usePicking = !(usePicking);
			break;
		}
	default:
		break;
	}
	return true;
}



//void CTankScene::CheckObjectByObjectCollisions()
//{
//	for (int i = 0; i < m_nShaders; i++) 
//		for (int j = 0; j < m_pShaders[i]->m_nObjects; ++j)
//			m_pShaders[i]->m_ppObjects[i]->m_pObjectCollided = NULL;
//
//	for (int i = 0; i < m_nShaders; i++)
//	{
//		for (int j = (i + 1); j < m_pShaders[i]->m_nObjects; j++)
//		{
//			if (m_pShaders[i]->m_ppObjects[j]->GetMesh()->m_xmOOBB.Intersects(m_pShaders[i]->m_ppObjects[j]->GetMesh()->m_xmOOBB))
//			{
//				m_pShaders[i]->m_ppObjects[i]->m_pObjectCollided = m_pShaders[i]->m_ppObjects[j];
//				m_pShaders[i]->m_ppObjects[j]->m_pObjectCollided = m_pShaders[i]->m_ppObjects[i];
//			}
//		}
//	}
//	for (int i = 0; i < m_nShaders; i++)
//	{
//		for (int j = 0; j < m_pShaders[i]->m_nObjects; ++j) {
//			if (m_pShaders[i]->m_ppObjects[j]->m_pObjectCollided)
//			{
//				XMFLOAT3 xmf3MovingDirection = static_cast<CExplosiveObject*>(m_pShaders[i]->m_ppObjects[i])->GetMoveDirection();
//				float fMovingSpeed = static_cast<CExplosiveObject*>(m_pShaders[i]->m_ppObjects[i])->GetMoveSpeed();
//				static_cast<CExplosiveObject*>(m_pShaders[i]->m_ppObjects[i])->GetMoveDirection() = m_pShaders[i]->m_ppObjects[i]->m_pObjectCollided->m_xmf3MovingDirection;
//				static_cast<CExplosiveObject*>(m_pShaders[i]->m_ppObjects[i])->GetMoveSpeed() = m_ppObjects[i]->m_pObjectCollided->m_fMovingSpeed;
//				static_cast<CExplosiveObject*>(m_pShaders[i]->m_ppObjects[i])->m_pObjectCollided->m_xmf3MoveDirection = xmf3MovingDirection;
//				static_cast<CExplosiveObject*>(m_pShaders[i]->m_ppObjects[i])->m_pObjectCollided->m_fMovingSpeed = fMovingSpeed;
//				static_cast<CExplosiveObject*>(m_pShaders[i]->m_ppObjects[i])->m_pObjectCollided->m_pObjectCollided = NULL;
//				static_cast<CExplosiveObject*>(m_pShaders[i]->m_ppObjects[i])->m_pObjectCollided = NULL;
//			}
//		}
//	}
//}

//void CTankScene::CheckObjectByWallCollisions()
//{
//	for (int i = 0; i < m_nShaders - 1; i++)
//	{
//		for (int j = 0; j < m_pShaders[i]->m_nObjects; ++j) {
//			if (m_pShaders[i]->m_ppObjects[j]->m_bActive == false) continue;
//			ContainmentType containType = m_pWallsObject->m_xmOOBB.Contains(m_ppObjects[i]->m_xmOOBB);
//			switch (containType)
//			{
//			case DISJOINT:
//			{
//				int nPlaneIndex = -1;
//				for (int j = 0; j < 6; j++)
//				{
//					PlaneIntersectionType intersectType = m_ppObjects[i]->m_xmOOBB.Intersects(XMLoadFloat4(&m_pWallsObject->m_pxmf4WallPlanes[j]));
//					if (intersectType == BACK)
//					{
//						nPlaneIndex = j;
//						break;
//					}
//				}
//				if (nPlaneIndex != -1)
//				{
//					XMVECTOR xmvNormal = XMVectorSet(m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].x, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].y, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].z, 0.0f);
//					XMVECTOR xmvReflect = XMVector3Reflect(XMLoadFloat3(&m_ppObjects[i]->m_xmf3MovingDirection), xmvNormal);
//					XMStoreFloat3(&m_ppObjects[i]->m_xmf3MovingDirection, xmvReflect);
//				}
//				break;
//			}
//			case INTERSECTS:
//			{
//				int nPlaneIndex = -1;
//				for (int j = 0; j < 6; j++)
//				{
//					PlaneIntersectionType intersectType = m_ppObjects[i]->m_xmOOBB.Intersects(XMLoadFloat4(&m_pWallsObject->m_pxmf4WallPlanes[j]));
//					if (intersectType == INTERSECTING)
//					{
//						nPlaneIndex = j;
//						break;
//					}
//				}
//				if (nPlaneIndex != -1)
//				{
//					XMVECTOR xmvNormal = XMVectorSet(m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].x, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].y, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].z, 0.0f);
//					XMVECTOR xmvReflect = XMVector3Reflect(XMLoadFloat3(&m_ppObjects[i]->m_xmf3MovingDirection), xmvNormal);
//					XMStoreFloat3(&m_ppObjects[i]->m_xmf3MovingDirection, xmvReflect);
//				}
//				break;
//			}
//			case CONTAINS:
//				break;
//			}
//		}
//		
//	}
//}

void CTankScene::CheckPlayerByWallCollision()
{
	BoundingOrientedBox xmOOBBPlayerMoveCheck;
	CWallShader* pWallsShader = nullptr;
	for (int i = m_nShaders - 1; i >= 0; --i) {
		// 높은 확률로 벽은 맨 마지막에 만들었기 때문에 뒤에서부터 검사한다.
		pWallsShader = dynamic_cast<CWallShader*>(m_pShaders[i]);
		if (pWallsShader)break;
	}

	if (pWallsShader) {
		for (int i = 0; i < pWallsShader->m_nObjects; ++i) {
			CExplosiveObject* pObjects = dynamic_cast<CExplosiveObject*>(pWallsShader->m_ppObjects[i]);

			pObjects->m_xmOOBB.Transform(xmOOBBPlayerMoveCheck, XMLoadFloat4x4(&pObjects->m_xmf4x4World));
			XMStoreFloat4(&xmOOBBPlayerMoveCheck.Orientation, XMQuaternionNormalize(XMLoadFloat4(&xmOOBBPlayerMoveCheck.Orientation)));

		}

		//if (!xmOOBBPlayerMoveCheck.Intersects(m_pPlayer->m_xmOOBB)) m_pWallsObject->SetPosition(m_pPlayer->m_xmf3Position);
	}
}

void CTankScene::CheckObjectByBulletCollisions()
{
	CBulletObject** ppBullets = ((CTankPlayer*)m_pPlayer)->bullets;
	for (int i = 0; i < m_nShaders; i++)
	{

		for (int j = 0; j < m_pShaders[i]->m_nObjects; ++j) {
			for (int r = 0; r < BULLETS; r++)
			{
				if (ppBullets[r]->IsActive() && (m_pShaders[i]->m_ppObjects[j]) && (m_pShaders[i]->m_ppObjects[j]->IsActive()) &&
					m_pShaders[i]->m_ppObjects[j]->m_xmOOBB.Intersects(ppBullets[r]->m_xmOOBB))
				{
					if (i >= 0 && i < 10) {
						CExplosiveObject* pExplosiveObject = (CExplosiveObject*)m_pShaders[i]->m_ppObjects[j];
						pExplosiveObject->SetExplosion();
					}


					ppBullets[r]->Reset();
				}
			}


		}


	}
}