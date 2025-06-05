#include "Shader.h"

CTankShader::CTankShader()
{
}

CTankShader::~CTankShader()
{
	ReleaseObjects();
	ReleaseShaderVariables();
}

void CTankShader::SetFileName(std::string filename)
{
	m_filename = filename;
}

void CTankShader::CreateShader(ID3D12Device* pd3dDevice, ID3D12RootSignature* pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState * [m_nPipelineStates];
	CInstancingShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}

void CTankShader::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList)
{
	m_nObjects = 9;
	m_ppObjects = new CGameObject * [m_nObjects];
	float fxPitch = 12.0f * 2.5f;
	float fyPitch = 12.0f * 2.5f;
	float fzPitch = 12.0f * 2.5f;
	CExplosiveObject* pExplosiveObject = NULL;
	for (int i = 0; i < m_nObjects; i++) {
		pExplosiveObject = new CExplosiveObject();
		pExplosiveObject->SetPosition(0.0f, 0.0f, i);
		pExplosiveObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
		pExplosiveObject->SetRotationSpeed(0.0f);
		m_ppObjects[i] = pExplosiveObject;
	}

	std::list<std::pair<CDiffusedVertex*, CDiffusedVertex*>> lines;

	//�ν��Ͻ��� ����Ͽ� �������ϱ� ���Ͽ� �ϳ��� ���� ��ü�� �޽��� ������.
	CTankMeshDiffused* pTankMesh = new CTankMeshDiffused(pd3dDevice, pd3dCommandList,
		12.0f, 3.0f, 12.0f);
	m_ppObjects[0]->SetMesh(pTankMesh);


	//�ν��Ͻ��� ���� ����(Structured Buffer)�� �����Ѵ�.
	CreateShaderVariables(pd3dDevice, pd3dCommandList);
}

void CTankShader::ReleaseObjects()
{

}

