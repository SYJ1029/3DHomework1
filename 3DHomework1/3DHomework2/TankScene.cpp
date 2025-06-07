#include "Scene.h"


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
	switch (nMessageID)
	{
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
		//���콺 ĸ�ĸ� �ϰ� ���� ���콺 ��ġ�� �����´�.
		::SetCapture(hWnd);
		::GetCursorPos(&mousePoint);
		break;
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
		//���콺 ĸ�ĸ� �����Ѵ�.
		::ReleaseCapture();
		break;
	}

	return S_SAFE;
}
bool CTankScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM
	lParam)
{
	return true;
}