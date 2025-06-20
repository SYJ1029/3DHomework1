#include "Shader.h"

CTitleShader::CTitleShader()
{
}

CTitleShader::~CTitleShader()
{
	ReleaseObjects();
	ReleaseShaderVariables();
}

void CTitleShader::SetFileName(std::string filename)
{
	m_filename = filename;
}

void CTitleShader::CreateShader(ID3D12Device* pd3dDevice, ID3D12RootSignature* pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState * [m_nPipelineStates];
	CInstancingShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}

void CTitleShader::CreateShaderVariables(ID3D12Device* pd3dDevice,
	ID3D12GraphicsCommandList* pd3dCommandList)
{
	//�ν��Ͻ� ������ ������ ���� ���۸� ���ε� �� �������� �����Ѵ�.
	m_pd3dcbGameObjects = ::CreateBufferResource(pd3dDevice, pd3dCommandList, NULL,
		sizeof(VS_VB_INSTANCE) * EXPLOSION_DEBRISES, D3D12_HEAP_TYPE_UPLOAD,
		D3D12_RESOURCE_STATE_GENERIC_READ, NULL);
	//���� ����(���ε� ��)�� ���� �����͸� �����Ѵ�.
	HRESULT hResult = m_pd3dcbGameObjects->Map(0, NULL, (void**)&m_pcbMappedGameObjects);
}

void CTitleShader::UpdateShaderVariables(ID3D12GraphicsCommandList
	* pd3dCommandList)
{

	pd3dCommandList->SetGraphicsRootShaderResourceView(2,
		m_pd3dcbGameObjects->GetGPUVirtualAddress());


	int nObjects = m_nObjects;
	int exploseIndex = -1;
	for (int j = 0; j < nObjects; j++) {
		if (dynamic_cast<CExplosiveObject*>(m_ppObjects[j])->m_bBlowingUp) {
			nObjects = EXPLOSION_DEBRISES;
			exploseIndex = j;
			break;
		}
	}

	for (int j = 0; j < m_nObjects; j++)
	{
		m_pcbMappedGameObjects[j].m_xmcColor = (j % 2) ? XMFLOAT4(0.5f, 0.0f, 0.0f, 0.0f) :
			XMFLOAT4(0.0f, 0.0f, 0.5f, 0.0f);
		XMStoreFloat4x4(&m_pcbMappedGameObjects[j].m_xmf4x4Transform,
			XMMatrixTranspose(XMLoadFloat4x4(&m_ppObjects[j]->GetMatrix(j))));


	}

	if (m_nObjects != nObjects)
	for (int j = 0; j < nObjects; j++) {
			m_pcbMappedGameObjects[j].m_xmcColor = (j % 2) ? XMFLOAT4(0.5f, 0.0f, 0.0f, 0.0f) :
				XMFLOAT4(0.0f, 0.0f, 0.5f, 0.0f);
			XMStoreFloat4x4(&m_pcbMappedGameObjects[j].m_xmf4x4Transform,
				XMMatrixTranspose(XMLoadFloat4x4(&m_ppObjects[exploseIndex]->GetMatrix(j))));
	}



}

void CTitleShader::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList, void* pContext)
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
		pExplosiveObject->SetRotationSpeed(30.0f);
		pExplosiveObject->PrepareExplosion(pd3dDevice, pd3dCommandList);
		pExplosiveObject->SetShader(this);
		m_ppObjects[i] = pExplosiveObject;
	}

	std::list<std::pair<CDiffusedVertex*, CDiffusedVertex*>> lines;

	//�ν��Ͻ��� ����Ͽ� �������ϱ� ���Ͽ� �ϳ��� ���� ��ü�� �޽��� ������.
	CMeshBuilder* pNameMesh = new CMeshBuilder(pd3dDevice, pd3dCommandList,
		m_filename, lines,
		12.0f, 3.0f, 12.0f);
	m_ppObjects[0]->SetMesh(0, pNameMesh);

	//CMeshBuilder* pNameMesh2 = new CMeshBuilder(pd3dDevice, pd3dCommandList,
	//	"�ۿ���.txt", lines,
	//	12.0f, 3.0f, 12.0f);
	//m_ppObjects[1]->SetMesh(pNameMesh2);

	//�ν��Ͻ��� ���� ����(Structured Buffer)�� �����Ѵ�.
	CreateShaderVariables(pd3dDevice, pd3dCommandList);
}

void CTitleShader::ReleaseObjects()
{

}

void CTitleShader::AnimateObjects(float fTimeElapsed)
{
	for (int j = 0; j < m_nObjects; j++)
	{
		if (m_ppObjects[j]->IsActive())
			m_ppObjects[j]->Animate(fTimeElapsed);
		else {
			// ��� �ϳ��� Active���� ���ϴٴ� ���� �� �ڵ忡���� Scene�� �Ѿ�� ���� �ǹ��Ѵ�.
			// Active���� ���� 
		}
	}
}