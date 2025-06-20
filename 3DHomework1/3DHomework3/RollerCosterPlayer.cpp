#include "GameFramework.h"
#include "Player.h"
#include "Shader.h"


CRollerCosterPlayer::CRollerCosterPlayer(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList, ID3D12RootSignature* pd3dGraphicsRootSignature, CGameFramework* framework, int nMeshes)
	:CAirplanePlayer(pd3dDevice, pd3dCommandList, pd3dGraphicsRootSignature, nMeshes)
{
	m_backref = framework;

	CMeshBuilder token;

	token.Loadlines("Rail.txt", lineList);

}
CRollerCosterPlayer::~CRollerCosterPlayer()
{
	m_backref = nullptr;
}

void CRollerCosterPlayer::Update(float fTimeElapsed)
{
	
	auto [start, end] = lineList.front();



	XMVECTOR playerPos = XMLoadFloat3(&m_xmf3Position);
	XMVECTOR endPos = XMLoadFloat3(&end->GetPosition());

	XMVECTOR dir = XMVectorSubtract(endPos, playerPos);
	dir = XMVector3Normalize(dir);

	// �̵� �ӵ�
	float speed = 30.0f; // ����

	// �̵�
	playerPos = XMVectorAdd(playerPos, XMVectorScale(dir, speed * fTimeElapsed));
	XMStoreFloat3(&m_xmf3Position, playerPos);



	// ��ǥ�� ���� �� ������ ���� ������
	XMVECTOR diff = XMVectorSubtract(endPos, playerPos);
	if (XMVectorGetX(XMVector3Length(diff)) < 0.1f) {
		SetPosition(end->GetPosition());
		lineList.pop_front();
		if (lineList.size() <= 0) {
			m_backref->ChangeScene(S_TANK);
			m_backref->ReleaseObjects();
			m_backref->BuildObjects();
		}

	}

	DWORD nCameraMode = m_pCamera->GetMode();
	//�÷��̾��� ��ġ�� ����Ǿ����Ƿ� 3��Ī ī�޶� �����Ѵ�.
	if (nCameraMode == THIRD_PERSON_CAMERA)m_pCamera->Update(m_xmf3Position,
		fTimeElapsed);
	//ī�޶��� ��ġ�� ����� �� �߰��� ������ �۾��� �����Ѵ�. 
	if (m_pCameraUpdatedContext) OnCameraUpdateCallback(fTimeElapsed);
	//ī�޶� 3��Ī ī�޶��̸� ī�޶� ����� �÷��̾� ��ġ�� �ٶ󺸵��� �Ѵ�.
	if (nCameraMode == THIRD_PERSON_CAMERA)m_pCamera->SetLookAt(m_xmf3Position);

	m_pCamera->RegenerateViewMatrix();
}