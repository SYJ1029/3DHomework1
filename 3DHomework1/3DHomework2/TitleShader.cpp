#include "Shader.h"

CTitleShader::CTitleShader()
{

}

CTitleShader::~CTitleShader()
{

}

void CTitleShader::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList)
{
	m_nObjects = 1;
	m_ppObjects = new CGameObject * [m_nObjects];
	float fxPitch = 12.0f * 2.5f;
	float fyPitch = 12.0f * 2.5f;
	float fzPitch = 12.0f * 2.5f;
	CExplosiveObject* pExplosiveObject = NULL;
	for (int i = 0; i < m_nObjects; i++) {
		pExplosiveObject = new CExplosiveObject();
		pExplosiveObject->SetPosition(fxPitch * i, 0.0f, fzPitch * i);
		pExplosiveObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
		pExplosiveObject->SetRotationSpeed(30.0f);
		m_ppObjects[i] = pExplosiveObject;
	}

	std::list<std::pair<CDiffusedVertex*, CDiffusedVertex*>> lines;

	//인스턴싱을 사용하여 렌더링하기 위하여 하나의 게임 객체만 메쉬를 가진다.
	CMeshBuilder* pNameMesh = new CMeshBuilder(pd3dDevice, pd3dCommandList,
		"3D게임 프로그래밍.txt", lines,
		12.0f, 3.0f, 12.0f);
	m_ppObjects[0]->SetMesh(pNameMesh);

	//인스턴싱을 위한 버퍼(Structured Buffer)를 생성한다.
	CreateShaderVariables(pd3dDevice, pd3dCommandList);
}

void CTitleShader::ReleaseObjects()
{

}