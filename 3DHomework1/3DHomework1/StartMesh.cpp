#include "stdafx.h"
#include "Mesh.h"
#include "GraphicsPipeline.h"

void CNameMesh::Savelines(std::string filename, std::list<std::pair<CVertex*, CVertex*>>& lines)
{
	std::ofstream out(filename);
	for (auto& line : lines)
	{
		CVertex* pStart = line.first;
		CVertex* pEnd = line.second;

		out << pStart->m_xmf3Position.x << ' ' << pStart->m_xmf3Position.y << ' ' << pStart->m_xmf3Position.z << ' '
			<< pEnd->m_xmf3Position.x << ' ' << pEnd->m_xmf3Position.y << ' ' << pEnd->m_xmf3Position.z << '\n';
	}
	out.close();
}

void CNameMesh::Loadlines(std::string filename, std::list<std::pair<CVertex*, CVertex*>>& lines)
{
	std::ifstream in(filename);

	if (in.is_open() == false) {
		return;
	}

	float sx, sy, sz, ex, ey, ez;
	while (in >> sx >> sy >> sz >> ex >> ey >> ez)
	{
		lines.push_back({ new CVertex(sx, sy, sz), new CVertex(ex, ey, ez) });
	}
	in.close();
}


CNameMesh::CNameMesh(float fWidth, float fHeight, float fDepth) : CMesh(24 + 24 + 30 + 54 + 30 + 42 + 18 + 30 + 18 + 24 + 6 + 24)
{

	float fHalfWidth = fWidth / 2;
	float fHalfHeight = fHeight / 8;
	float fHalfDepth = fDepth / 2;


	std::list<std::pair<CVertex*, CVertex*>> lines;

	Loadlines("3D게임 프로그래밍.txt", lines);

	

	LinesToCube(lines);

	

	m_xmOOBB = BoundingOrientedBox(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(fHalfWidth, fHalfHeight, fHalfDepth), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	lines.clear();
}


CNameMesh::CNameMesh(float fWidth, float fHeight, float fDepth, std::string filename, std::list<std::pair<CVertex*, CVertex*>>& lines)
{


	float fHalfWidth = fWidth / 2;
	float fHalfHeight = fHeight / 8;
	float fHalfDepth = fDepth / 2;

	Loadlines(filename, lines);
	
	m_nPolygons = lines.size() * 6;
	m_ppPolygons = new CPolygon * [m_nPolygons];

	LinesToCube(lines);

	m_xmOOBB = BoundingOrientedBox(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(fHalfWidth, fHalfHeight, fHalfDepth), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

}



CNameMesh::~CNameMesh()
{

}

void CNameMesh::SingleLineToCube(CVertex* dot1, CVertex* dot2, float depth, int index)
{
	XMVECTOR v1 = XMLoadFloat3(&dot1->m_xmf3Position);
	XMVECTOR v2 = XMLoadFloat3(&dot2->m_xmf3Position);

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

	{
		CPolygon* pFrontFace = new CPolygon(4);
		pFrontFace->SetVertex(0, CVertex(p0));
		pFrontFace->SetVertex(1, CVertex(p1));
		pFrontFace->SetVertex(2, CVertex(p2));
		pFrontFace->SetVertex(3, CVertex(p3));
		SetPolygon(index, pFrontFace);

		CPolygon* pBackFace = new CPolygon(4);
		pBackFace->SetVertex(0, CVertex(p4));
		pBackFace->SetVertex(1, CVertex(p5));
		pBackFace->SetVertex(2, CVertex(p6));
		pBackFace->SetVertex(3, CVertex(p7));
		SetPolygon(index + 1, pBackFace);

		CPolygon* pTopFace = new CPolygon(4);
		pTopFace->SetVertex(0, CVertex(p1));
		pTopFace->SetVertex(1, CVertex(p5));
		pTopFace->SetVertex(2, CVertex(p6));
		pTopFace->SetVertex(3, CVertex(p2));
		SetPolygon(index + 2, pTopFace);

		CPolygon* pBottomFace = new CPolygon(4);
		pBottomFace->SetVertex(0, CVertex(p0));
		pBottomFace->SetVertex(1, CVertex(p4));
		pBottomFace->SetVertex(2, CVertex(p7));
		pBottomFace->SetVertex(3, CVertex(p3));
		SetPolygon(index + 3, pBottomFace);

		CPolygon* pLeftFace = new CPolygon(4);

		pLeftFace->SetVertex(0, CVertex(p4));
		pLeftFace->SetVertex(1, CVertex(p5));
		pLeftFace->SetVertex(2, CVertex(p1));
		pLeftFace->SetVertex(3, CVertex(p0));
		SetPolygon(index + 4, pLeftFace);

		CPolygon* pRightFace = new CPolygon(4);

		pRightFace->SetVertex(0, CVertex(p3));
		pRightFace->SetVertex(1, CVertex(p2));
		pRightFace->SetVertex(2, CVertex(p6));
		pRightFace->SetVertex(3, CVertex(p7));
		SetPolygon(index + 5, pRightFace);
	}
}

void CNameMesh::LinesToCube(std::list<std::pair<CVertex*, CVertex*>>& lines)
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