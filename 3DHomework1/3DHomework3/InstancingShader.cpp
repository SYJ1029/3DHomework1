#include "Shader.h"

CInstancingShader::CInstancingShader()
{
}
CInstancingShader::~CInstancingShader()
{
}

D3D12_INPUT_LAYOUT_DESC CInstancingShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC* pd3dInputElementDescs = new
		D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];
	//���� ������ ���� �Է� �����̴�.
	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
   D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
   D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;
	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CInstancingShader::CreateVertexShader(ID3DBlob** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"VertexShader.hlsl", "VSInstancing", "vs_5_1",
		ppd3dShaderBlob));
}
D3D12_SHADER_BYTECODE CInstancingShader::CreatePixelShader(ID3DBlob** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"PixelShader.hlsl", "PSInstancing", "ps_5_1",
		ppd3dShaderBlob));
}

void CInstancingShader::CreateShader(ID3D12Device* pd3dDevice, ID3D12RootSignature
	* pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState * [m_nPipelineStates];
	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}

void CInstancingShader::CreateShaderVariables(ID3D12Device* pd3dDevice,
	ID3D12GraphicsCommandList* pd3dCommandList)
{
	//�ν��Ͻ� ������ ������ ���� ���۸� ���ε� �� �������� �����Ѵ�.
	m_pd3dcbGameObjects = ::CreateBufferResource(pd3dDevice, pd3dCommandList, NULL,
		sizeof(VS_VB_INSTANCE) * m_nObjects, D3D12_HEAP_TYPE_UPLOAD,
		D3D12_RESOURCE_STATE_GENERIC_READ, NULL);
	//���� ����(���ε� ��)�� ���� �����͸� �����Ѵ�.
	HRESULT hResult = m_pd3dcbGameObjects->Map(0, NULL, (void**)&m_pcbMappedGameObjects);
}

void CInstancingShader::CreateShaderVariables(ID3D12Device* pd3dDevice,
	ID3D12GraphicsCommandList* pd3dCommandList, UINT nInstances)
{
	//�ν��Ͻ� ������ ������ ���� ���۸� ���ε� �� �������� �����Ѵ�.
	m_pd3dcbGameObjects = ::CreateBufferResource(pd3dDevice, pd3dCommandList, NULL,
		sizeof(VS_VB_INSTANCE) * nInstances * EXPLOSION_DEBRISES, D3D12_HEAP_TYPE_UPLOAD,
		D3D12_RESOURCE_STATE_GENERIC_READ, NULL);
	//���� ����(���ε� ��)�� ���� �����͸� �����Ѵ�.
	HRESULT hResult = m_pd3dcbGameObjects->Map(0, NULL, (void**)&m_pcbMappedGameObjects);
}

void CInstancingShader::ReleaseShaderVariables()
{
	if (m_pd3dcbGameObjects) m_pd3dcbGameObjects->Unmap(0, NULL);
	if (m_pd3dcbGameObjects) m_pd3dcbGameObjects->Release();
}

//�ν��Ͻ� ����(��ü�� ���� ��ȯ ��İ� ����)�� ���� ���ۿ� �����Ѵ�.
void CInstancingShader::UpdateShaderVariables(ID3D12GraphicsCommandList
	* pd3dCommandList)
{

	pd3dCommandList->SetGraphicsRootShaderResourceView(2,
		m_pd3dcbGameObjects->GetGPUVirtualAddress());

	for (int j = 0; j < m_nObjects; j++)
	{
		m_pcbMappedGameObjects[j].m_xmcColor = (j % 2) ? XMFLOAT4(0.5f, 0.0f, 0.0f, 0.0f) :
			XMFLOAT4(0.0f, 0.0f, 0.5f, 0.0f);
		XMStoreFloat4x4(&m_pcbMappedGameObjects[j].m_xmf4x4Transform,
			XMMatrixTranspose(XMLoadFloat4x4(&m_ppObjects[j]->GetMatrix(j))));
	}


}

void CInstancingShader::RefreshShaderVariable(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList)
{
	// ���� �� �ٽ� �籸��
	ReleaseShaderVariables();

	CreateShaderVariables(pd3dDevice, pd3dCommandList);
}


void CInstancingShader::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
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
		pExplosiveObject->SetPosition(fxPitch * i, 0.0f, fzPitch * i);
		pExplosiveObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
		pExplosiveObject->SetRotationSpeed(10.0f * (i % 10));
		m_ppObjects[i] = pExplosiveObject;
	}
	//�ν��Ͻ��� ����Ͽ� �������ϱ� ���Ͽ� �ϳ��� ���� ��ü�� �޽��� ������.
	CTankMeshDiffused* pTankMesh = new CTankMeshDiffused(pd3dDevice, pd3dCommandList,
		12.0f, 3.0f, 12.0f);
	m_ppObjects[0]->SetMesh(0, pTankMesh);

	//�ν��Ͻ��� ���� ����(Structured Buffer)�� �����Ѵ�.
	CreateShaderVariables(pd3dDevice, pd3dCommandList);
}


void CInstancingShader::ReleaseObjects()
{

}

void CInstancingShader::Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera
	* pCamera)
{
	CShader::Render(pd3dCommandList, pCamera);
	//��� ���� ��ü�� �ν��Ͻ� �����͸� ���ۿ� �����Ѵ�.
	UpdateShaderVariables(pd3dCommandList);
	//�ϳ��� ���� �����͸� ����Ͽ� ��� ���� ��ü(�ν��Ͻ�)���� �������Ѵ�.
	if(m_ppObjects[0]->IsActive())
		m_ppObjects[0]->Render(pd3dCommandList, pCamera, m_nObjects);
}

CGameObject* CInstancingShader::GetInActiveObject()
{
	for (int i = 0; i < m_nObjects; i++) {
		if (m_ppObjects[i]->IsActive() == false)
			return m_ppObjects[i];
	}

	return NULL;
}