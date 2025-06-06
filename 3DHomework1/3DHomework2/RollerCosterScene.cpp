#include "Scene.h"

CRollerCosterScene::CRollerCosterScene()
{

}

CRollerCosterScene::~CRollerCosterScene()
{

}


void CRollerCosterScene::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList)
{
	m_pd3dGraphicsRootSignature = CreateGraphicsRootSignature(pd3dDevice);
	m_nShaders = 1;
	m_pShaders = new CInstancingShader * [m_nShaders];

	m_pShaders[0] = new CRollerCosterShader;

	m_pShaders[0]->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature);
	m_pShaders[0]->SetFileName("Rail.txt");
	m_pShaders[0]->BuildObjects(pd3dDevice, pd3dCommandList);
	m_pShaders[0]->SetObjPos(XMFLOAT3(0.0f, 6.0f, 0.0f));

}

void CRollerCosterScene::AnimateObjects(float fTimeElapsed)
{

}


UINT CRollerCosterScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM
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
bool CRollerCosterScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM
	lParam)
{
	return true;
}