#include "GameFramework.h"
#include "Player.h"
#include "Shader.h"
#include "RollerCosterScript.h"


CRollerCosterPlayer::CRollerCosterPlayer(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList, ID3D12RootSignature* pd3dGraphicsRootSignature, CGameFramework* framework, int nMeshes)
	:CAirplanePlayer(pd3dDevice, pd3dCommandList, pd3dGraphicsRootSignature, nMeshes)
{
	m_backref = framework;



	CMeshBuilder token;

	token.Loadlines("Rail.txt", lineList);

	// 컴포넌트 세팅
	m_Components.emplace_back(new RollerCosterScript());

	for (auto& comp : m_Components)
	{
		comp->SetOwner(this);
	}

	m_Components.front()->Init();



}
CRollerCosterPlayer::~CRollerCosterPlayer()
{
	m_backref = nullptr;
}

void CRollerCosterPlayer::Update(float fTimeElapsed)
{
	for (auto& comp : m_Components)
	{
		comp->Update(fTimeElapsed);
	}


	//auto [start, end] = lineList.front();



	//XMVECTOR playerPos = XMLoadFloat3(&m_xmf3Position);
	//XMVECTOR endPos = XMLoadFloat3(&end->GetPosition());

	//XMVECTOR dir = XMVectorSubtract(endPos, playerPos);
	//dir = XMVector3Normalize(dir);

	//// 이동 속도
	//float speed = 30.0f; // 예시

	//// 이동
	//playerPos = XMVectorAdd(playerPos, XMVectorScale(dir, speed * fTimeElapsed));
	//XMStoreFloat3(&m_xmf3Position, playerPos);



	//// 목표에 거의 다 왔으면 다음 선으로
	//XMVECTOR diff = XMVectorSubtract(endPos, playerPos);
	//if (XMVectorGetX(XMVector3Length(diff)) < 0.1f) {
	//	SetPosition(end->GetPosition());
	//	lineList.pop_front();
	//	if (lineList.size() <= 0) {
	//		m_backref->ChangeScene(S_TANK);
	//		m_backref->ReleaseObjects();
	//		m_backref->BuildObjects();
	//	}

	//}

	//DWORD nCameraMode = m_pCamera->GetMode();
	////플레이어의 위치가 변경되었으므로 3인칭 카메라를 갱신한다.
	//if (nCameraMode == THIRD_PERSON_CAMERA)m_pCamera->Update(m_xmf3Position,
	//	fTimeElapsed);
	////카메라의 위치가 변경될 때 추가로 수행할 작업을 수행한다. 
	//if (m_pCameraUpdatedContext) OnCameraUpdateCallback(fTimeElapsed);
	////카메라가 3인칭 카메라이면 카메라가 변경된 플레이어 위치를 바라보도록 한다.
	//if (nCameraMode == THIRD_PERSON_CAMERA)m_pCamera->SetLookAt(m_xmf3Position);

	m_pCamera->RegenerateViewMatrix();

}