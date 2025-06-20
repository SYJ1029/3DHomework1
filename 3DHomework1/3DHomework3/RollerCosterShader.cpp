#include "Shader.h"

CRollerCosterShader::CRollerCosterShader()
{
}

CRollerCosterShader::~CRollerCosterShader()
{
	ReleaseObjects();
	ReleaseShaderVariables();
}

void CRollerCosterShader::SetFileName(std::string filename)
{
	m_filename = filename;
}

void CRollerCosterShader::CreateShader(ID3D12Device* pd3dDevice, ID3D12RootSignature* pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState * [m_nPipelineStates];
	CInstancingShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}

void CRollerCosterShader::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
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
		pExplosiveObject->SetPosition(0.0f, 0.0f, 0.0f);
		pExplosiveObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
		pExplosiveObject->SetRotationSpeed(0.0f);
		m_ppObjects[i] = pExplosiveObject;
	}

	std::list<std::pair<CDiffusedVertex*, CDiffusedVertex*>> lines;

	//인스턴싱을 사용하여 렌더링하기 위하여 하나의 게임 객체만 메쉬를 가진다.
	CMeshBuilder* pNameMesh = new CMeshBuilder(pd3dDevice, pd3dCommandList,
		m_filename, lines,
		12.0f, 3.0f, 12.0f);
	m_ppObjects[0]->SetMesh(0, pNameMesh);


	//인스턴싱을 위한 버퍼(Structured Buffer)를 생성한다.
	CreateShaderVariables(pd3dDevice, pd3dCommandList);
}

void CRollerCosterShader::ReleaseObjects()
{

}

