#include "Mesh.h"

CMeshBuilder::CMeshBuilder(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList, float fWidth, float fHeight, float fDepth,
	XMFLOAT4 xmf4Color) 
	
	: CMesh(pd3dDevice,pd3dCommandList)
{

}
CMeshBuilder::CMeshBuilder(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, 
	std::string filename, std::list<std::pair<CDiffusedVertex*, CDiffusedVertex*>>& lines,
	float fWidth, float fHeight, float fDepth,
	XMFLOAT4 xmf4Color)

	: CMesh(pd3dDevice,	pd3dCommandList)
{
	
	float fHalfWidth = fWidth / 2;
	float fHalfHeight = fHeight / 8;
	float fHalfDepth = fDepth / 2;

	Loadlines(filename, lines);

	//m_nPolygons = lines.size() * 6;
	//m_ppPolygons = new CPolygon * [m_nPolygons];

	LinesToCube(pd3dDevice, pd3dCommandList, lines);
}
CMeshBuilder::~CMeshBuilder()
{

}
void CMeshBuilder::SingleLineToCube(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList, CDiffusedVertex* dot1, CDiffusedVertex* dot2, float depth, int index)
{
	XMVECTOR v1 = XMLoadFloat3(&dot1->GetPosition());
	XMVECTOR v2 = XMLoadFloat3(&dot2->GetPosition());

	XMVECTOR vdir = XMVectorSubtract(v2, v1);

	XMVECTOR right = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

	XMVECTOR appdir = XMVector3Cross(vdir, right);

	appdir = XMVectorScale(appdir, 0.1f);

	XMFLOAT3 p0;
	XMStoreFloat3(&p0, XMVectorSubtract(XMVectorAdd(v1, appdir), XMVectorSet(0, 0, depth / 2, 0)));
	XMFLOAT3 p1;
	XMStoreFloat3(&p1, XMVectorSubtract(XMVectorSubtract(v1, appdir), XMVectorSet(0, 0, depth / 2, 0)));
	XMFLOAT3 p2;
	XMStoreFloat3(&p2, XMVectorSubtract(XMVectorSubtract(v2, appdir), XMVectorSet(0, 0, depth / 2, 0)));
	XMFLOAT3 p3;
	XMStoreFloat3(&p3, XMVectorSubtract(XMVectorAdd(v2, appdir), XMVectorSet(0, 0, depth / 2, 0)));






	XMFLOAT3 p4{ p0.x, p0.y, p0.z + depth };
	XMFLOAT3 p5{ p1.x, p1.y, p1.z + depth };
	XMFLOAT3 p6{ p2.x, p2.y, p2.z + depth };
	XMFLOAT3 p7{ p3.x, p3.y, p3.z + depth };

	//auto topFace = { p1, p5, p6, p2 };
	//auto bottomFace = { p0, p4, p7, p3 };


	//������ü�� ������(����)�� 8���̴�. 
	m_nVertices = 8;
	m_nStride = sizeof(CDiffusedVertex);
	m_d3dPrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	//���� ���۴� ������ü�� ������ 8���� ���� ���� �����͸� ������. 
	CDiffusedVertex pVertices[8];
	pVertices[0] = CDiffusedVertex(p1, RANDOM_COLOR);
	pVertices[1] = CDiffusedVertex(p5, RANDOM_COLOR);
	pVertices[2] = CDiffusedVertex(p6, RANDOM_COLOR);
	pVertices[3] = CDiffusedVertex(p2, RANDOM_COLOR);
	pVertices[4] = CDiffusedVertex(p0, RANDOM_COLOR);
	pVertices[5] = CDiffusedVertex(p4, RANDOM_COLOR);
	pVertices[6] = CDiffusedVertex(p7, RANDOM_COLOR);
	pVertices[7] = CDiffusedVertex(p3, RANDOM_COLOR);
	m_pd3dVertexBuffer = ::CreateBufferResource(pd3dDevice, pd3dCommandList, pVertices,
		m_nStride * m_nVertices, D3D12_HEAP_TYPE_DEFAULT,
		D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, &m_pd3dVertexUploadBuffer);
	m_d3dVertexBufferView.BufferLocation = m_pd3dVertexBuffer->GetGPUVirtualAddress();
	m_d3dVertexBufferView.StrideInBytes = m_nStride;
	m_d3dVertexBufferView.SizeInBytes = m_nStride * m_nVertices;
	/*�ε��� ���۴� ������ü�� 6���� ��(�簢��)�� ���� ���� ������ ���´�. �ﰢ�� ����Ʈ�� ������ü�� ǥ���� ����
	�Ƿ� �� ���� 2���� �ﰢ���� ������ �� �ﰢ���� 3���� ������ �ʿ��ϴ�. ��, �ε��� ���۴� ��ü 36(=6*2*3)���� ��
	������ ������ �Ѵ�.*/
	m_nIndices = 36;
	UINT pnIndices[36];
	//�� �ո�(Front) �簢���� ���� �ﰢ��
	pnIndices[0] = 3; pnIndices[1] = 1; pnIndices[2] = 0;
	//�� �ո�(Front) �簢���� �Ʒ��� �ﰢ��
	pnIndices[3] = 2; pnIndices[4] = 1; pnIndices[5] = 3;
	//�� ����(Top) �簢���� ���� �ﰢ��
	pnIndices[6] = 0; pnIndices[7] = 5; pnIndices[8] = 4;
	//�� ����(Top) �簢���� �Ʒ��� �ﰢ��
	pnIndices[9] = 1; pnIndices[10] = 5; pnIndices[11] = 0;
	//�� �޸�(Back) �簢���� ���� �ﰢ��
	pnIndices[12] = 3; pnIndices[13] = 4; pnIndices[14] = 7;
	//�� �޸�(Back) �簢���� �Ʒ��� �ﰢ��
	pnIndices[15] = 0; pnIndices[16] = 4; pnIndices[17] = 3;
	//�� �Ʒ���(Bottom) �簢���� ���� �ﰢ��
	pnIndices[18] = 1; pnIndices[19] = 6; pnIndices[20] = 5;
	//�� �Ʒ���(Bottom) �簢���� �Ʒ��� �ﰢ��
	pnIndices[21] = 2; pnIndices[22] = 6; pnIndices[23] = 1;
	//�� ����(Left) �簢���� ���� �ﰢ��
	pnIndices[24] = 2; pnIndices[25] = 7; pnIndices[26] = 6;
	//�� ����(Left) �簢���� �Ʒ��� �ﰢ��
	pnIndices[27] = 3; pnIndices[28] = 7; pnIndices[29] = 2;
	//�� ����(Right) �簢���� ���� �ﰢ��
	pnIndices[30] = 6; pnIndices[31] = 4; pnIndices[32] = 5;
	//�� ����(Right) �簢���� �Ʒ��� �ﰢ��
	pnIndices[33] = 7; pnIndices[34] = 4; pnIndices[35] = 6;
	//�ε��� ���۸� �����Ѵ�. 
	m_pd3dIndexBuffer = ::CreateBufferResource(pd3dDevice, pd3dCommandList, pnIndices,
		sizeof(UINT) * m_nIndices, D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_INDEX_BUFFER,
		&m_pd3dIndexUploadBuffer);
	//�ε��� ���� �並 �����Ѵ�. 
	m_d3dIndexBufferView.BufferLocation = m_pd3dIndexBuffer->GetGPUVirtualAddress();
	m_d3dIndexBufferView.Format = DXGI_FORMAT_R32_UINT;
	m_d3dIndexBufferView.SizeInBytes = sizeof(UINT) * m_nIndices;
}

void CMeshBuilder::LinesToCube(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList, std::list<std::pair<CDiffusedVertex*, CDiffusedVertex*>>& lines)
{
	// ���� �̷�� �� ������ ����ü�� �����մϴ�.
	float depth{ 0.5f };


	int i{ 0 };
	while (lines.size() > 0) {
		auto [dot1, dot2] = lines.front();
		lines.pop_front();

		SingleLineToCube(pd3dDevice, pd3dCommandList, dot1, dot2, depth, i);

		i += 6;
	}

	std::cout << "end LTC" << std::endl;
}

void CMeshBuilder::Loadlines(std::string filename, std::list<std::pair<CDiffusedVertex*, CDiffusedVertex*>>& lines)
{
	std::ifstream in(filename);

	if (in.is_open() == false) {
		return;
	}

	float sx, sy, sz, ex, ey, ez;
	while (in >> sx >> sy >> sz >> ex >> ey >> ez)
	{
		lines.push_back({ new CDiffusedVertex(XMFLOAT3(sx, sy, sz), RANDOM_COLOR), new CDiffusedVertex(XMFLOAT3(ex, ey, ez), RANDOM_COLOR) });
	}
	in.close();
}