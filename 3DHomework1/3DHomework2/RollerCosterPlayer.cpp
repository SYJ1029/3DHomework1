#include "GameFramework.h"
#include "Player.h"
#include "Shader.h"


CRollerCosterPlayer::CRollerCosterPlayer(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList, ID3D12RootSignature* pd3dGraphicsRootSignature, CGameFramework* framework)
	:CAirplanePlayer(pd3dDevice, pd3dCommandList, pd3dGraphicsRootSignature)
{
	m_backref = framework;
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

	// 이동 속도
	float speed = 10.0f; // 예시

	// 이동
	playerPos = XMVectorAdd(playerPos, XMVectorScale(dir, speed * fTimeElapsed));
	XMStoreFloat3(&m_xmf3Position, playerPos);

	// 목표에 거의 다 왔으면 다음 선으로
	XMVECTOR diff = XMVectorSubtract(endPos, playerPos);
	if (XMVectorGetX(XMVector3Length(diff)) < 0.1f) {
		SetPosition(XMFLOAT3(end->GetPosition().x, end->GetPosition().y, end->GetPosition().z));
		lineList.pop_front();
		if (lineList.size() <= 0) {
			m_backref->ChangeScene(S_TANK);
			m_backref->BuildObjects();
		}

	}
}