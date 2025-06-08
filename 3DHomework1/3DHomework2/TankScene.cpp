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
	m_nShaders = 3;
	m_pShaders = new CInstancingShader * [m_nShaders];

	m_pShaders[0] = new CTankShader;

	m_pShaders[0]->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature);
	m_pShaders[0]->SetFileName("You Win!.txt");
	m_pShaders[0]->BuildObjects(pd3dDevice, pd3dCommandList);

	m_pShaders[1] = new CObstacleShader;

	m_pShaders[1]->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature);
	m_pShaders[1]->SetFileName("You Win!.txt");
	m_pShaders[1]->BuildObjects(pd3dDevice, pd3dCommandList);


	m_pShaders[2] = new CWallShader;

	m_pShaders[2]->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature);
	m_pShaders[2]->SetFileName("You Win!.txt");
	m_pShaders[2]->BuildObjects(pd3dDevice, pd3dCommandList);
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
		pPlayer->pickedObject = dynamic_cast<CExplosiveObject*>(PickObjectPointedByCursor(LOWORD(lParam), HIWORD(lParam), pCamera));

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
		default:
			break;
		}
		break;
	default:
		break;
	}
	return true;
}