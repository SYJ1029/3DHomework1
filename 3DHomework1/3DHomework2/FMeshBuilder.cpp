#include "Mesh.h"

CMeshBuilder::CMeshBuilder(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList, float fWidth = 20.0f, float fHeight = 20.0f, float fDepth = 4.0f,
	XMFLOAT4 xmf4Color = XMFLOAT4(1.0f, 1.0f, 0.0f, 0.0f)) 
	
	: CMesh(pd3dDevice,pd3dCommandList)
{

}
CMeshBuilder::CMeshBuilder(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList, float fWidth = 20.0f, float fHeight = 20.0f, float fDepth = 4.0f,
	XMFLOAT4 xmf4Color = XMFLOAT4(1.0f, 1.0f, 0.0f, 0.0f),
	std::string filename, std::list<std::pair<CVertex*, CVertex*>>&)

	: CMesh(pd3dDevice,	pd3dCommandList)
{

}
CMeshBuilder::~CMeshBuilder()
{

}
void CMeshBuilder::SingleLineToCube(CDiffusedVertex* start, CDiffusedVertex* end, float depth, int index)
{

}
void CMeshBuilder::LinesToCube(std::list<std::pair<CDiffusedVertex*, CDiffusedVertex*>>& lines)
{
	// 선을 이루는 두 점으로 육면체를 생성합니다.
	float depth{ 0.5f };


	int i{ 0 };
	while (lines.size() > 0) {
		auto [dot1, dot2] = lines.front();
		lines.pop_front();

		SingleLineToCube(dot1, dot2, depth, i);

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