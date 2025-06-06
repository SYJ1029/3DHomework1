#include "Mesh.h"

////////////////////////////////////////////////////////////////////////////////
CTankMeshDiffused::CTankMeshDiffused(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList, float fWidth, float fHeight, float fDepth,
	XMFLOAT4 xmf4Color) : CMesh(pd3dDevice,
		pd3dCommandList)
{
	m_nVertices = 24; // 8 x 3
	m_nIndices = 108; // 36 x 3
	m_nStride = sizeof(CDiffusedVertex);
	m_d3dPrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	CDiffusedVertex pVertices[24];
	UINT pnIndices[108];

	float fHalfWidth = fWidth * 0.5f;
	float fHalfHeight = fHeight * 0.5f;
	float fHalfDepth = fDepth * 0.5f;

	UINT baseIndices[36] = {
		3,1,0, 2,1,3,    // Front
		0,5,4, 1,5,0,    // Top
		3,4,7, 0,4,3,    // Back
		1,6,5, 2,6,1,    // Bottom
		2,7,6, 3,7,2,    // Left
		6,4,5, 7,4,6     // Right
	};

	for (int i = 0; i < 2; ++i) {
		// 윗면 (Top): +Y
		pVertices[0 + i * 8] = CDiffusedVertex(XMFLOAT3(-fHalfWidth, +fHalfHeight + i, -fHalfDepth), RANDOM_COLOR); // 0
		pVertices[1 + i * 8] = CDiffusedVertex(XMFLOAT3(+fHalfWidth, +fHalfHeight + i, -fHalfDepth), RANDOM_COLOR); // 1
		pVertices[2 + i * 8] = CDiffusedVertex(XMFLOAT3(+fHalfWidth, +fHalfHeight + i, +fHalfDepth), RANDOM_COLOR); // 2
		pVertices[3 + i * 8] = CDiffusedVertex(XMFLOAT3(-fHalfWidth, +fHalfHeight + i, +fHalfDepth), RANDOM_COLOR); // 3

		// 아랫면 (Bottom): -Y
		pVertices[4 + i * 8] = CDiffusedVertex(XMFLOAT3(-fHalfWidth, -fHalfHeight + i, -fHalfDepth), RANDOM_COLOR); // 4
		pVertices[5 + i * 8] = CDiffusedVertex(XMFLOAT3(+fHalfWidth, -fHalfHeight + i, -fHalfDepth), RANDOM_COLOR); // 5
		pVertices[6 + i * 8] = CDiffusedVertex(XMFLOAT3(+fHalfWidth, -fHalfHeight + i, +fHalfDepth), RANDOM_COLOR); // 6
		pVertices[7 + i * 8] = CDiffusedVertex(XMFLOAT3(-fHalfWidth, -fHalfHeight + i, +fHalfDepth), RANDOM_COLOR); // 7

		fHalfWidth /= 2.0f;
		fHalfDepth /= 2.0f;
	}

	fHalfDepth *= 2.0f; // 포신 깊이 복구
	fHalfHeight /= 2.0f;

	// 포신 (추가 블록)
	pVertices[16] = CDiffusedVertex(XMFLOAT3(-fHalfWidth, +fHalfHeight + 2.0f, -fHalfDepth + 6.0f), RANDOM_COLOR); // 0
	pVertices[17] = CDiffusedVertex(XMFLOAT3(+fHalfWidth, +fHalfHeight + 2.0f, -fHalfDepth + 6.0f), RANDOM_COLOR); // 1
	pVertices[18] = CDiffusedVertex(XMFLOAT3(+fHalfWidth, +fHalfHeight + 2.0f, +fHalfDepth + 6.0f), RANDOM_COLOR); // 2
	pVertices[19] = CDiffusedVertex(XMFLOAT3(-fHalfWidth, +fHalfHeight + 2.0f, +fHalfDepth + 6.0f), RANDOM_COLOR); // 3

	pVertices[20] = CDiffusedVertex(XMFLOAT3(-fHalfWidth, -fHalfHeight + 2.0f, -fHalfDepth + 6.0f), RANDOM_COLOR); // 4
	pVertices[21] = CDiffusedVertex(XMFLOAT3(+fHalfWidth, -fHalfHeight + 2.0f, -fHalfDepth + 6.0f), RANDOM_COLOR); // 5
	pVertices[22] = CDiffusedVertex(XMFLOAT3(+fHalfWidth, -fHalfHeight + 2.0f, +fHalfDepth + 6.0f), RANDOM_COLOR); // 6
	pVertices[23] = CDiffusedVertex(XMFLOAT3(-fHalfWidth, -fHalfHeight + 2.0f, +fHalfDepth + 6.0f), RANDOM_COLOR); // 7


	fHalfWidth *= 4.0f;
	fHalfDepth *= 4.0f;

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 36; ++j)
			pnIndices[i * 36 + j] = baseIndices[j] + i * 8;
	}


	m_d3dPrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	m_pd3dVertexBuffer = ::CreateBufferResource(pd3dDevice, pd3dCommandList, pVertices,
		m_nStride * m_nVertices, D3D12_HEAP_TYPE_DEFAULT,
		D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, &m_pd3dVertexUploadBuffer);
	m_d3dVertexBufferView.BufferLocation = m_pd3dVertexBuffer->GetGPUVirtualAddress();
	m_d3dVertexBufferView.StrideInBytes = m_nStride;
	m_d3dVertexBufferView.SizeInBytes = m_nStride * m_nVertices;
	//인덱스 버퍼를 생성한다. 
	m_pd3dIndexBuffer = ::CreateBufferResource(pd3dDevice, pd3dCommandList, pnIndices,
		sizeof(UINT) * m_nIndices, D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_INDEX_BUFFER,
		&m_pd3dIndexUploadBuffer);
	//인덱스 버퍼 뷰를 생성한다. 
	m_d3dIndexBufferView.BufferLocation = m_pd3dIndexBuffer->GetGPUVirtualAddress();
	m_d3dIndexBufferView.Format = DXGI_FORMAT_R32_UINT;
	m_d3dIndexBufferView.SizeInBytes = sizeof(UINT) * m_nIndices;

	m_xmOOBB = BoundingOrientedBox(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(fHalfWidth, fHalfHeight, fHalfDepth), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

}

CTankMeshDiffused::~CTankMeshDiffused()
{
}