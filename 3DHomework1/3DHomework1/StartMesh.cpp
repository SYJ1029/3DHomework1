#include "stdafx.h"
#include "Mesh.h"
#include "GraphicsPipeline.h"


CNameMesh::CNameMesh(float fWidth, float fHeight, float fDepth) : CMesh(6)
{

	float fHalfWidth = fWidth / 2;
	float fHalfHeight = fHeight / 8;
	float fHalfDepth = fDepth / 2;

	std::list<std::pair<CVertex*, CVertex*>> lines;

	lines.push_back(std::pair<CVertex*, CVertex*>{new CVertex(-1.0f, 0.0f, 0.0f), new CVertex(1.0f, 0.0f, 0.0f)});

	LinesToCube(lines);

	//int i;
	//for (i = 0; i < 3; ++i) {
	//	CPolygon* pFrontFace = new CPolygon(4);
	//	pFrontFace->SetVertex(0, CVertex(-fHalfWidth, +fHalfHeight - 2 * i, -fHalfDepth));
	//	pFrontFace->SetVertex(1, CVertex(+fHalfWidth, +fHalfHeight - 2 * i, -fHalfDepth));
	//	pFrontFace->SetVertex(2, CVertex(+fHalfWidth, -fHalfHeight - 2 * i, -fHalfDepth));
	//	pFrontFace->SetVertex(3, CVertex(-fHalfWidth, -fHalfHeight - 2 * i, -fHalfDepth));
	//	SetPolygon(i * 6, pFrontFace);

	//	CPolygon* pTopFace = new CPolygon(4);
	//	pTopFace->SetVertex(0, CVertex(-fHalfWidth, +fHalfHeight - 2 * i, +fHalfDepth));
	//	pTopFace->SetVertex(1, CVertex(+fHalfWidth, +fHalfHeight - 2 * i, +fHalfDepth));
	//	pTopFace->SetVertex(2, CVertex(+fHalfWidth, +fHalfHeight - 2 * i, -fHalfDepth));
	//	pTopFace->SetVertex(3, CVertex(-fHalfWidth, +fHalfHeight - 2 * i, -fHalfDepth));
	//	SetPolygon(i * 6 + 1, pTopFace);

	//	CPolygon* pBackFace = new CPolygon(4);
	//	pBackFace->SetVertex(0, CVertex(-fHalfWidth, -fHalfHeight - 2 * i, +fHalfDepth));
	//	pBackFace->SetVertex(1, CVertex(+fHalfWidth, -fHalfHeight - 2 * i, +fHalfDepth));
	//	pBackFace->SetVertex(2, CVertex(+fHalfWidth, +fHalfHeight - 2 * i, +fHalfDepth));
	//	pBackFace->SetVertex(3, CVertex(-fHalfWidth, +fHalfHeight - 2 * i, +fHalfDepth));
	//	SetPolygon(i * 6 + 2, pBackFace);

	//	CPolygon* pBottomFace = new CPolygon(4);
	//	pBottomFace->SetVertex(0, CVertex(-fHalfWidth, -fHalfHeight - 2 * i, -fHalfDepth));
	//	pBottomFace->SetVertex(1, CVertex(+fHalfWidth, -fHalfHeight - 2 * i, -fHalfDepth));
	//	pBottomFace->SetVertex(2, CVertex(+fHalfWidth, -fHalfHeight - 2 * i, +fHalfDepth));
	//	pBottomFace->SetVertex(3, CVertex(-fHalfWidth, -fHalfHeight - 2 * i, +fHalfDepth));
	//	SetPolygon(i * 6 + 3, pBottomFace);

	//	CPolygon* pLeftFace = new CPolygon(4);
	//	pLeftFace->SetVertex(0, CVertex(-fHalfWidth, +fHalfHeight - 2 * i, +fHalfDepth));
	//	pLeftFace->SetVertex(1, CVertex(-fHalfWidth, +fHalfHeight - 2 * i, -fHalfDepth));
	//	pLeftFace->SetVertex(2, CVertex(-fHalfWidth, -fHalfHeight - 2 * i, -fHalfDepth));
	//	pLeftFace->SetVertex(3, CVertex(-fHalfWidth, -fHalfHeight - 2 * i, +fHalfDepth));
	//	SetPolygon(i * 6 + 4, pLeftFace);

	//	CPolygon* pRightFace = new CPolygon(4);
	//	pRightFace->SetVertex(0, CVertex(+fHalfWidth, +fHalfHeight - 2 * i, -fHalfDepth));
	//	pRightFace->SetVertex(1, CVertex(+fHalfWidth, +fHalfHeight - 2 * i, +fHalfDepth));
	//	pRightFace->SetVertex(2, CVertex(+fHalfWidth, -fHalfHeight - 2 * i, +fHalfDepth));
	//	pRightFace->SetVertex(3, CVertex(+fHalfWidth, -fHalfHeight - 2 * i, -fHalfDepth));
	//	SetPolygon(i * 6 + 5, pRightFace);

	//}
	//fHalfHeight *= 8.0f;
	//fHalfWidth /= 2.0f;
	//CPolygon* pFrontFace = new CPolygon(4);
	//pFrontFace->SetVertex(0, CVertex(-fHalfWidth + 1.0f, +fHalfHeight - 2.0f, -fHalfDepth));
	//pFrontFace->SetVertex(1, CVertex(+fHalfWidth + 1.0f, +fHalfHeight - 2.0f, -fHalfDepth));
	//pFrontFace->SetVertex(2, CVertex(+fHalfWidth + 1.0f, -fHalfHeight - 2.0f, -fHalfDepth));
	//pFrontFace->SetVertex(3, CVertex(-fHalfWidth + 1.0f, -fHalfHeight - 2.0f, -fHalfDepth));
	//SetPolygon(i * 6, pFrontFace);

	//CPolygon* pTopFace = new CPolygon(4);
	//pTopFace->SetVertex(0, CVertex(-fHalfWidth + 1.0f, +fHalfHeight - 2.0f, +fHalfDepth));
	//pTopFace->SetVertex(1, CVertex(+fHalfWidth + 1.0f, +fHalfHeight - 2.0f, +fHalfDepth));
	//pTopFace->SetVertex(2, CVertex(+fHalfWidth + 1.0f, +fHalfHeight - 2.0f, -fHalfDepth));
	//pTopFace->SetVertex(3, CVertex(-fHalfWidth + 1.0f, +fHalfHeight - 2.0f, -fHalfDepth));
	//SetPolygon(i * 6 + 1, pTopFace);

	//CPolygon* pBackFace = new CPolygon(4);
	//pBackFace->SetVertex(0, CVertex(-fHalfWidth + 1.0f, -fHalfHeight - 2.0f, +fHalfDepth));
	//pBackFace->SetVertex(1, CVertex(+fHalfWidth + 1.0f, -fHalfHeight - 2.0f, +fHalfDepth));
	//pBackFace->SetVertex(2, CVertex(+fHalfWidth + 1.0f, +fHalfHeight - 2.0f, +fHalfDepth));
	//pBackFace->SetVertex(3, CVertex(-fHalfWidth + 1.0f, +fHalfHeight - 2.0f, +fHalfDepth));
	//SetPolygon(i * 6 + 2, pBackFace);

	//CPolygon* pBottomFace = new CPolygon(4);
	//pBottomFace->SetVertex(0, CVertex(-fHalfWidth + 1.0f, -fHalfHeight - 2.0f, -fHalfDepth));
	//pBottomFace->SetVertex(1, CVertex(+fHalfWidth + 1.0f, -fHalfHeight - 2.0f, -fHalfDepth));
	//pBottomFace->SetVertex(2, CVertex(+fHalfWidth + 1.0f, -fHalfHeight - 2.0f, +fHalfDepth));
	//pBottomFace->SetVertex(3, CVertex(-fHalfWidth + 1.0f, -fHalfHeight - 2.0f, +fHalfDepth));
	//SetPolygon(i * 6 + 3, pBottomFace);

	//CPolygon* pLeftFace = new CPolygon(4);
	//pLeftFace->SetVertex(0, CVertex(-fHalfWidth + 1.0f, +fHalfHeight - 2.0f, +fHalfDepth));
	//pLeftFace->SetVertex(1, CVertex(-fHalfWidth + 1.0f, +fHalfHeight - 2.0f, -fHalfDepth));
	//pLeftFace->SetVertex(2, CVertex(-fHalfWidth + 1.0f, -fHalfHeight - 2.0f, -fHalfDepth));
	//pLeftFace->SetVertex(3, CVertex(-fHalfWidth + 1.0f, -fHalfHeight - 2.0f, +fHalfDepth));
	//SetPolygon(i * 6 + 4, pLeftFace);

	//CPolygon* pRightFace = new CPolygon(4);
	//pRightFace->SetVertex(0, CVertex(+fHalfWidth + 1.0f, +fHalfHeight - 2.0f, -fHalfDepth));
	//pRightFace->SetVertex(1, CVertex(+fHalfWidth + 1.0f, +fHalfHeight - 2.0f, +fHalfDepth));
	//pRightFace->SetVertex(2, CVertex(+fHalfWidth + 1.0f, -fHalfHeight - 2.0f, +fHalfDepth));
	//pRightFace->SetVertex(3, CVertex(+fHalfWidth + 1.0f, -fHalfHeight - 2.0f, -fHalfDepth));
	//SetPolygon(i * 6 + 5, pRightFace);
	

	m_xmOOBB = BoundingOrientedBox(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(fHalfWidth, fHalfHeight, fHalfDepth), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
}

CNameMesh::~CNameMesh()
{

}

void CNameMesh::LinesToCube(std::list<std::pair<CVertex*, CVertex*>>& lines)
{
	// 선을 이루는 두 점으로 육면체를 생성합니다.
	float depth{ 0.5f };

	auto [dot1, dot2] = lines.back();
	lines.pop_back();
	
	XMVECTOR v1 = XMLoadFloat3(&dot1->m_xmf3Position);
	XMVECTOR v2 = XMLoadFloat3(&dot2->m_xmf3Position);
	
	XMVECTOR vdir = XMVectorSubtract(v2, v1);

	XMVECTOR right = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

	XMVECTOR appdir = XMVector3Cross(vdir, right);

	appdir = XMVectorScale(appdir, 0.2f);

	XMFLOAT3 p0; 
	XMStoreFloat3(&p0, (XMVectorAdd(v1, appdir)));
	XMFLOAT3 p1;
	XMStoreFloat3(&p1, (XMVectorSubtract(v1, appdir)));
	XMFLOAT3 p2;
	XMStoreFloat3(&p2, (XMVectorSubtract(v2, appdir)));
	XMFLOAT3 p3;
	XMStoreFloat3(&p3, (XMVectorAdd(v2, appdir)));

	




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
		SetPolygon(0, pFrontFace);

		CPolygon* pBackFace = new CPolygon(4);
		pBackFace->SetVertex(0, CVertex(p4));
		pBackFace->SetVertex(1, CVertex(p5));
		pBackFace->SetVertex(2, CVertex(p6));
		pBackFace->SetVertex(3, CVertex(p7));
		SetPolygon(1, pBackFace);

		CPolygon* pTopFace = new CPolygon(4);
		pTopFace->SetVertex(0, CVertex(p1));
		pTopFace->SetVertex(1, CVertex(p5));
		pTopFace->SetVertex(2, CVertex(p6));
		pTopFace->SetVertex(3, CVertex(p2));
		SetPolygon(2, pTopFace);

		CPolygon* pBottomFace = new CPolygon(4);
		pBottomFace->SetVertex(0, CVertex(p0));
		pBottomFace->SetVertex(1, CVertex(p4));
		pBottomFace->SetVertex(2, CVertex(p7));
		pBottomFace->SetVertex(3, CVertex(p3));
		SetPolygon(3, pBottomFace);

		CPolygon* pLeftFace = new CPolygon(4);

		pLeftFace->SetVertex(0, CVertex(p4));
		pLeftFace->SetVertex(1, CVertex(p5));
		pLeftFace->SetVertex(2, CVertex(p1));
		pLeftFace->SetVertex(3, CVertex(p0));
		SetPolygon(4, pLeftFace);

		CPolygon* pRightFace = new CPolygon(4);

		pRightFace->SetVertex(0, CVertex(p3));
		pRightFace->SetVertex(1, CVertex(p2));
		pRightFace->SetVertex(2, CVertex(p6));
		pRightFace->SetVertex(3, CVertex(p7));
		SetPolygon(5, pRightFace);
	}
}