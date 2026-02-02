#include "RollerCosterScript.h"

void RollerCosterScript::Init()
{
	player = reinterpret_cast<CPlayer*>(m_pOwner);

	CMeshBuilder token;

	token.Loadlines("Rail.txt", lineList);
}

void RollerCosterScript::Update(float fTimeElapsed)
{

	// 직선의 시작점과 끝점 가져오기
	auto [start, end] = lineList.front();

	// 플레이어의 현재 위치와 직선의 끝점을 XMVECTOR로 변환
	XMFLOAT3 m_xmf3Position = player->GetPosition();
	XMVECTOR playerPos = XMLoadFloat3(&m_xmf3Position);
	XMVECTOR endPos = XMLoadFloat3(&end->GetPosition());

	XMVECTOR dir = XMVectorSubtract(endPos, playerPos);
	dir = XMVector3Normalize(dir);

	// 이동 속도
	float speed = 30.0f; // 예시

	// 이동
	playerPos = XMVectorAdd(playerPos, XMVectorScale(dir, speed * fTimeElapsed));
	XMStoreFloat3(&m_xmf3Position, playerPos);



	// 목표에 거의 다 왔으면 다음 선으로
	XMVECTOR diff = XMVectorSubtract(endPos, playerPos);
	if (XMVectorGetX(XMVector3Length(diff)) < 0.1f) {
		player->SetPosition(end->GetPosition());
		lineList.pop_front();

		// 씬 전환을 프레임워크를 통해 하고 있다
		// 임시로 이건 막아놓자
		//if (lineList.size() <= 0) {
		//	m_backref->ChangeScene(S_TANK);
		//	m_backref->ReleaseObjects();
		//	m_backref->BuildObjects();
		//}

	}

	// GetCamera() 함수는 CCamera 클래스의 객체 포인터를 반환하므로
	// Get - 작업 - Set이 필요가 없다. 그냥 포인터에 들이대면 바뀌니까
	// 편의상 카메라 객체를 가져올 포인터만 적당히 만들자

	CCamera* pCamera = player->GetCamera();
	DWORD nCameraMode = pCamera->GetMode();

	//플레이어의 위치가 변경되었으므로 3인칭 카메라를 갱신한다.
	if (nCameraMode == THIRD_PERSON_CAMERA)pCamera->Update(m_xmf3Position,
		fTimeElapsed);
	//카메라의 위치가 변경될 때 추가로 수행할 작업을 수행한다. 
	// 하지만 이 함수는 당장 하는 역할이 없다
	//if (m_pCameraUpdatedContext) OnCameraUpdateCallback(fTimeElapsed);

	//카메라가 3인칭 카메라이면 카메라가 변경된 플레이어 위치를 바라보도록 한다.
	if (nCameraMode == THIRD_PERSON_CAMERA)pCamera->SetLookAt(m_xmf3Position);

	pCamera->RegenerateViewMatrix();
}

void RollerCosterScript::Render()
{
}

void RollerCosterScript::Release()
{
}
