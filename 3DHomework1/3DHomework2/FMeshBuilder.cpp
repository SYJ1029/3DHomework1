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

	std::list<CDiffusedVertex> vertexList;
	std::list<UINT> IndexList;

	LinesToCube(pd3dDevice, pd3dCommandList, lines, vertexList, IndexList);
}
CMeshBuilder::~CMeshBuilder()
{

}
void CMeshBuilder::SingleLineToCube(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList, CDiffusedVertex* dot1, CDiffusedVertex* dot2, float depth, int index, 
	std::list<CDiffusedVertex>& vertexList, std::list<UINT>& IndexList)
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


	//8개의 꼭짓점을 리스트에 추가
	vertexList.emplace_back(p1, RANDOM_COLOR);
	vertexList.emplace_back(p5, RANDOM_COLOR);
	vertexList.emplace_back(p6, RANDOM_COLOR);
	vertexList.emplace_back(p2, RANDOM_COLOR);

	vertexList.emplace_back(p0, RANDOM_COLOR);
	vertexList.emplace_back(p4, RANDOM_COLOR);
	vertexList.emplace_back(p7, RANDOM_COLOR);
	vertexList.emplace_back(p3, RANDOM_COLOR);

	//직육면체는 꼭지점(정점)이 8개이다. 

	
	/*인덱스 버퍼는 직육면체의 6개의 면(사각형)에 대한 기하 정보를 갖는다. 삼각형 리스트로 직육면체를 표현할 것이
	므로 각 면은 2개의 삼각형을 가지고 각 삼각형은 3개의 정점이 필요하다. 즉, 인덱스 버퍼는 전체 36(=6*2*3)개의 인
	덱스를 가져야 한다.*/
	
	UINT pnIndices[36];
	//ⓐ 앞면(Front) 사각형의 위쪽 삼각형
	pnIndices[0] = 3; pnIndices[1] = 1; pnIndices[2] = 0;
	//ⓑ 앞면(Front) 사각형의 아래쪽 삼각형
	pnIndices[3] = 2; pnIndices[4] = 1; pnIndices[5] = 3;
	//ⓒ 윗면(Top) 사각형의 위쪽 삼각형
	pnIndices[6] = 0; pnIndices[7] = 5; pnIndices[8] = 4;
	//ⓓ 윗면(Top) 사각형의 아래쪽 삼각형
	pnIndices[9] = 1; pnIndices[10] = 5; pnIndices[11] = 0;
	//ⓔ 뒷면(Back) 사각형의 위쪽 삼각형
	pnIndices[12] = 3; pnIndices[13] = 4; pnIndices[14] = 7;
	//ⓕ 뒷면(Back) 사각형의 아래쪽 삼각형
	pnIndices[15] = 0; pnIndices[16] = 4; pnIndices[17] = 3;
	//ⓖ 아래면(Bottom) 사각형의 위쪽 삼각형
	pnIndices[18] = 1; pnIndices[19] = 6; pnIndices[20] = 5;
	//ⓗ 아래면(Bottom) 사각형의 아래쪽 삼각형
	pnIndices[21] = 2; pnIndices[22] = 6; pnIndices[23] = 1;
	//ⓘ 옆면(Left) 사각형의 위쪽 삼각형
	pnIndices[24] = 2; pnIndices[25] = 7; pnIndices[26] = 6;
	//ⓙ 옆면(Left) 사각형의 아래쪽 삼각형
	pnIndices[27] = 3; pnIndices[28] = 7; pnIndices[29] = 2;
	//ⓚ 옆면(Right) 사각형의 위쪽 삼각형
	pnIndices[30] = 6; pnIndices[31] = 4; pnIndices[32] = 5;
	//ⓛ 옆면(Right) 사각형의 아래쪽 삼각형
	pnIndices[33] = 7; pnIndices[34] = 4; pnIndices[35] = 6;



	for (int i = 0; i < 36; ++i) {
		// 인덱스는 만들고자 하는 육면체가 바뀌면 새로운 인덱스들을 할당해주어야 한다
		IndexList.push_back(pnIndices[i] + index);
	}
}

void CMeshBuilder::LinesToCube(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList, std::list<std::pair<CDiffusedVertex*, CDiffusedVertex*>>& lines, 
	std::list<CDiffusedVertex>& vertexList, std::list<UINT>& IndexList)
{
	// 선을 이루는 두 점으로 육면체를 생성합니다.
	float depth{ 0.5f };


	int i{ 0 };
	while (lines.size() > 0) {
		auto [dot1, dot2] = lines.front();
		lines.pop_front();

		SingleLineToCube(pd3dDevice, pd3dCommandList, dot1, dot2, depth, i, vertexList, IndexList);

		i += 8;
	}

	m_nStride = sizeof(CDiffusedVertex);
	m_d3dPrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	std::vector<CDiffusedVertex> pVertices{ vertexList.begin(), vertexList.end() };
	m_nVertices = pVertices.size();
	std::vector<UINT> pnIndices{ IndexList.begin(), IndexList.end() };
	m_nIndices = pnIndices.size();

	//정점 버퍼는 직육면체의 꼭지점 8개에 대한 정점 데이터를 가진다. 
	m_pd3dVertexBuffer = ::CreateBufferResource(pd3dDevice, pd3dCommandList, pVertices.data(),
		m_nStride * m_nVertices, D3D12_HEAP_TYPE_DEFAULT,
		D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, &m_pd3dVertexUploadBuffer);
	m_d3dVertexBufferView.BufferLocation = m_pd3dVertexBuffer->GetGPUVirtualAddress();
	m_d3dVertexBufferView.StrideInBytes = m_nStride;
	m_d3dVertexBufferView.SizeInBytes = m_nStride * m_nVertices;



	//인덱스 버퍼를 생성한다. 
	m_pd3dIndexBuffer = ::CreateBufferResource(pd3dDevice, pd3dCommandList, pnIndices.data(),
		sizeof(UINT) * m_nIndices, D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_INDEX_BUFFER,
		&m_pd3dIndexUploadBuffer);

	//인덱스 버퍼 뷰를 생성한다. 
	m_d3dIndexBufferView.BufferLocation = m_pd3dIndexBuffer->GetGPUVirtualAddress();
	m_d3dIndexBufferView.Format = DXGI_FORMAT_R32_UINT;
	m_d3dIndexBufferView.SizeInBytes = sizeof(UINT) * m_nIndices;

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