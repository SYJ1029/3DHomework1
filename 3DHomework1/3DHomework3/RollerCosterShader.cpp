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

	//�ν��Ͻ��� ����Ͽ� �������ϱ� ���Ͽ� �ϳ��� ���� ��ü�� �޽��� ������.
	CMeshBuilder* pNameMesh = new CMeshBuilder(pd3dDevice, pd3dCommandList,
		m_filename, lines,
		12.0f, 3.0f, 12.0f);
	m_ppObjects[0]->SetMesh(0, pNameMesh);


	//�ν��Ͻ��� ���� ����(Structured Buffer)�� �����Ѵ�.
	CreateShaderVariables(pd3dDevice, pd3dCommandList);
}

void CRollerCosterShader::ReleaseObjects()
{

}

