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

	auto topFace = { p1, p5, p6, p2 };
	auto bottomFace = { p0, p4, p7, p3 };
}

void CMeshBuilder::LinesToCube(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList, std::list<std::pair<CDiffusedVertex*, CDiffusedVertex*>>& lines)
{
	// 선을 이루는 두 점으로 육면체를 생성합니다.
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