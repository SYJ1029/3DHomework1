#include "Player.h"

#include "Shader.h"

CTankPlayer::CTankPlayer(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList, ID3D12RootSignature* pd3dGraphicsRootSignature)
{
	//����� �޽��� �����Ѵ�.
	CMesh* pTankMesh = new CTankMeshDiffused(pd3dDevice, pd3dCommandList, 12.0f,
		4.0f, 12.0f, XMFLOAT4(0.0f, 0.5f, 0.0f, 0.0f));
	SetMesh(pTankMesh);
	//�÷��̾��� ī�޶� �����̽�-�� ī�޶�� ����(����)�Ѵ�.
	m_pCamera = ChangeCamera(THIRD_PERSON_CAMERA, 0.0f);
	//�÷��̾ ���� ���̴� ������ �����Ѵ�.
	CreateShaderVariables(pd3dDevice, pd3dCommandList);
	//�÷��̾��� ��ġ�� �����Ѵ�.
	SetPosition(XMFLOAT3(0.0f, 0.0f, -15.0f));
	//�÷��̾�(�����) �޽��� �������� �� ����� ���̴��� �����Ѵ�.

	bullets = new CBulletObject * [BULLETS];
	CCubeMeshDiffused* pCubeMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList,
		3.0f, 3.0f, 3.0f);

	for (int i = 0; i < BULLETS; ++i) {
		bullets[i] = new CBulletObject(m_fBulletEffectiveRange);
		bullets[i]->SetMesh(pCubeMesh);
	}

	CDiffusedShader* pShader = new CDiffusedShader();
	pShader->CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
	SetShader(pShader);


}
CTankPlayer::~CTankPlayer()
{
}

void CTankPlayer::CreateShaderVariables(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList)
{
	CGameObject::CreateShaderVariables(pd3dDevice, pd3dCommandList);
	if (m_pCamera) m_pCamera->CreateShaderVariables(pd3dDevice, pd3dCommandList);
}

void CTankPlayer::FireBullet(CGameObject* pLockedObject, bool bLock)
{

	//if (pLockedObject) 
	//{
	//	LookAt(pLockedObject->GetPosition(), XMFLOAT3(0.0f, 1.0f, 0.0f));
	//	OnUpdateTransform();
	//}


	CBulletObject* pBulletObject = NULL;
	for (int i = 0; i < BULLETS; i++)
	{
		if (!bullets[i]->IsActive())
		{
			pBulletObject = bullets[i];
			break;
		}
	}


	if (pBulletObject)
	{
		XMFLOAT3 xmf3Position = GetPosition();
		XMFLOAT3 xmf3Direction = GetLook();
		XMFLOAT3 xmf3FirePosition = Vector3::Add(xmf3Position, Vector3::ScalarProduct(xmf3Direction, 6.0f, false));

		pBulletObject->m_xmf4x4World = m_xmf4x4World;

		pBulletObject->SetFirePosition(xmf3FirePosition);
		pBulletObject->SetMoveDirection(xmf3Direction);
		pBulletObject->SetMoveSpeed(100.0f);
		pBulletObject->SetActive(true);


		if (pLockedObject && bLock)
		{
			pBulletObject->m_pLockedObject = pLockedObject;
		}
	}
}

void CTankPlayer::OnPrepareRender()
{
	CPlayer::OnPrepareRender();
	// x-������ 90�� ȸ���Ѵ�.
	//XMMATRIX mtxRotate = XMMatrixRotationRollPitchYaw(XMConvertToRadians(90.0f), 0.0f,
	//	0.0f);
	//m_xmf4x4World = Matrix4x4::Multiply(mtxRotate, m_xmf4x4World);
}

//ī�޶� ������ �� ȣ��Ǵ� �Լ��̴�. nNewCameraMode�� ���� ������ ī�޶� ����̴�. 
CCamera* CTankPlayer::ChangeCamera(DWORD nNewCameraMode, float fTimeElapsed)
{
	DWORD nCurrentCameraMode = (m_pCamera) ? m_pCamera->GetMode() : 0x00;
	if (nCurrentCameraMode == nNewCameraMode) return(m_pCamera);
	switch (nNewCameraMode)
	{
	case FIRST_PERSON_CAMERA:
		//�÷��̾��� Ư���� 1��Ī ī�޶� ��忡 �°� �����Ѵ�. �߷��� �������� �ʴ´�.
		SetFriction(200.0f);
		SetGravity(XMFLOAT3(0.0f, 0.0f, 0.0f));
		SetMaxVelocityXZ(125.0f);
		SetMaxVelocityY(400.0f);
		m_pCamera = OnChangeCamera(FIRST_PERSON_CAMERA, nCurrentCameraMode);
		m_pCamera->SetTimeLag(0.25f);
		//m_pCamera->SetTimeLag(0.0f);
		m_pCamera->SetOffset(XMFLOAT3(0.0f, 20.0f, 0.0f));
		m_pCamera->GenerateProjectionMatrix(1.01f, 5000.0f, ASPECT_RATIO, 60.0f);
		m_pCamera->SetViewport(0, 0, FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT, 0.0f,
			1.0f);
		m_pCamera->SetScissorRect(0, 0, FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT);
		break;
	case SPACESHIP_CAMERA:
		//�÷��̾��� Ư���� �����̽�-�� ī�޶� ��忡 �°� �����Ѵ�. �߷��� �������� �ʴ´�.
		SetFriction(125.0f);
		SetGravity(XMFLOAT3(0.0f, 0.0f, 0.0f));
		SetMaxVelocityXZ(400.0f);
		SetMaxVelocityY(400.0f);
		m_pCamera = OnChangeCamera(SPACESHIP_CAMERA, nCurrentCameraMode);
		m_pCamera->SetTimeLag(0.0f);
		m_pCamera->SetOffset(XMFLOAT3(0.0f, 0.0f, 0.0f));
		m_pCamera->GenerateProjectionMatrix(1.01f, 5000.0f, ASPECT_RATIO, 60.0f);
		m_pCamera->SetViewport(0, 0, FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT, 0.0f,
			1.0f);
		m_pCamera->SetScissorRect(0, 0, FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT);
		break;
	case THIRD_PERSON_CAMERA:
		//�÷��̾��� Ư���� 3��Ī ī�޶� ��忡 �°� �����Ѵ�. ���� ȿ���� ī�޶� �������� �����Ѵ�.
		SetFriction(125.0f);
		SetGravity(XMFLOAT3(0.0f, 0.0f, 0.0f));
		SetMaxVelocityXZ(125.0f);
		SetMaxVelocityY(400.0f);
		m_pCamera = OnChangeCamera(THIRD_PERSON_CAMERA, nCurrentCameraMode);
		//3��Ī ī�޶��� ���� ȿ���� �����Ѵ�. ���� 0.25f ��ſ� 0.0f�� 1.0f�� ������ ����� ���ϱ� �ٶ���.
		m_pCamera->SetTimeLag(0.0f);
		m_pCamera->SetOffset(XMFLOAT3(0.0f, 20.0f, -50.0f));
		m_pCamera->GenerateProjectionMatrix(1.01f, 5000.0f, ASPECT_RATIO, 60.0f);
		m_pCamera->SetViewport(0, 0, FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT, 0.0f,
			1.0f);
		m_pCamera->SetScissorRect(0, 0, FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT);
		break;
	default:
		break;
	}
	m_pCamera->SetPosition(Vector3::Add(m_xmf3Position, m_pCamera->GetOffset()));
	//�÷��̾ �ð��� ����� ���� ����(��ġ�� ������ ����: �ӵ�, ������, �߷� ���� ó��)�Ѵ�.
	Update(fTimeElapsed);
	return(m_pCamera);
}


void CTankPlayer::Update(float fTimeElapsed)
{
	CPlayer::Update(fTimeElapsed);

	//player�� active���� �Ѿ˿� ���Ͽ� Animate�� �����ؾ� �Ѵ�

	for (int i = 0; i < BULLETS; ++i) {
		if (bullets && bullets[i] && bullets[i]->IsActive()) {
			bullets[i]->Animate(fTimeElapsed);
		}
	}
}

void CTankPlayer::Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera) {
	OnPrepareRender();

	// �÷��̾�� �ڽ��� ������ ���οʹ� ���� ���� active�� �Ѿ˵��� Render����� �Ѵ�.


	CPlayer::Render(pd3dCommandList, pCamera);

	for (int i = 0; i < BULLETS; ++i) {
		if (bullets && bullets[i] && bullets[i]->IsActive()) {
			bullets[i]->Render(pd3dCommandList, pCamera, 1);
		}
	}
}