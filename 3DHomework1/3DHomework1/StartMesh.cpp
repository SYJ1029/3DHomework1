#include "stdafx.h"
#include "Mesh.h"
#include "GraphicsPipeline.h"


CNameMesh::CNameMesh(float fWidth, float fHeight, float fDepth) : CMesh(24)
{

	float fHalfWidth = fWidth / 2;
	float fHalfHeight = fHeight / 8;
	float fHalfDepth = fDepth / 2;

	int i;
	for (i = 0; i < 3; ++i) {
		CPolygon* pFrontFace = new CPolygon(4);
		pFrontFace->SetVertex(0, CVertex(-fHalfWidth, +fHalfHeight - 2 * i, -fHalfDepth));
		pFrontFace->SetVertex(1, CVertex(+fHalfWidth, +fHalfHeight - 2 * i, -fHalfDepth));
		pFrontFace->SetVertex(2, CVertex(+fHalfWidth, -fHalfHeight - 2 * i, -fHalfDepth));
		pFrontFace->SetVertex(3, CVertex(-fHalfWidth, -fHalfHeight - 2 * i, -fHalfDepth));
		SetPolygon(i * 6, pFrontFace);

		CPolygon* pTopFace = new CPolygon(4);
		pTopFace->SetVertex(0, CVertex(-fHalfWidth, +fHalfHeight - 2 * i, +fHalfDepth));
		pTopFace->SetVertex(1, CVertex(+fHalfWidth, +fHalfHeight - 2 * i, +fHalfDepth));
		pTopFace->SetVertex(2, CVertex(+fHalfWidth, +fHalfHeight - 2 * i, -fHalfDepth));
		pTopFace->SetVertex(3, CVertex(-fHalfWidth, +fHalfHeight - 2 * i, -fHalfDepth));
		SetPolygon(i * 6 + 1, pTopFace);

		CPolygon* pBackFace = new CPolygon(4);
		pBackFace->SetVertex(0, CVertex(-fHalfWidth, -fHalfHeight - 2 * i, +fHalfDepth));
		pBackFace->SetVertex(1, CVertex(+fHalfWidth, -fHalfHeight - 2 * i, +fHalfDepth));
		pBackFace->SetVertex(2, CVertex(+fHalfWidth, +fHalfHeight - 2 * i, +fHalfDepth));
		pBackFace->SetVertex(3, CVertex(-fHalfWidth, +fHalfHeight - 2 * i, +fHalfDepth));
		SetPolygon(i * 6 + 2, pBackFace);

		CPolygon* pBottomFace = new CPolygon(4);
		pBottomFace->SetVertex(0, CVertex(-fHalfWidth, -fHalfHeight - 2 * i, -fHalfDepth));
		pBottomFace->SetVertex(1, CVertex(+fHalfWidth, -fHalfHeight - 2 * i, -fHalfDepth));
		pBottomFace->SetVertex(2, CVertex(+fHalfWidth, -fHalfHeight - 2 * i, +fHalfDepth));
		pBottomFace->SetVertex(3, CVertex(-fHalfWidth, -fHalfHeight - 2 * i, +fHalfDepth));
		SetPolygon(i * 6 + 3, pBottomFace);

		CPolygon* pLeftFace = new CPolygon(4);
		pLeftFace->SetVertex(0, CVertex(-fHalfWidth, +fHalfHeight - 2 * i, +fHalfDepth));
		pLeftFace->SetVertex(1, CVertex(-fHalfWidth, +fHalfHeight - 2 * i, -fHalfDepth));
		pLeftFace->SetVertex(2, CVertex(-fHalfWidth, -fHalfHeight - 2 * i, -fHalfDepth));
		pLeftFace->SetVertex(3, CVertex(-fHalfWidth, -fHalfHeight - 2 * i, +fHalfDepth));
		SetPolygon(i * 6 + 4, pLeftFace);

		CPolygon* pRightFace = new CPolygon(4);
		pRightFace->SetVertex(0, CVertex(+fHalfWidth, +fHalfHeight - 2 * i, -fHalfDepth));
		pRightFace->SetVertex(1, CVertex(+fHalfWidth, +fHalfHeight - 2 * i, +fHalfDepth));
		pRightFace->SetVertex(2, CVertex(+fHalfWidth, -fHalfHeight - 2 * i, +fHalfDepth));
		pRightFace->SetVertex(3, CVertex(+fHalfWidth, -fHalfHeight - 2 * i, -fHalfDepth));
		SetPolygon(i * 6 + 5, pRightFace);

	}
	fHalfHeight *= 8.0f;
	fHalfWidth /= 2.0f;
	CPolygon* pFrontFace = new CPolygon(4);
	pFrontFace->SetVertex(0, CVertex(-fHalfWidth + 1.0f, +fHalfHeight - 2.0f, -fHalfDepth));
	pFrontFace->SetVertex(1, CVertex(+fHalfWidth + 1.0f, +fHalfHeight - 2.0f, -fHalfDepth));
	pFrontFace->SetVertex(2, CVertex(+fHalfWidth + 1.0f, -fHalfHeight - 2.0f, -fHalfDepth));
	pFrontFace->SetVertex(3, CVertex(-fHalfWidth + 1.0f, -fHalfHeight - 2.0f, -fHalfDepth));
	SetPolygon(i * 6, pFrontFace);

	CPolygon* pTopFace = new CPolygon(4);
	pTopFace->SetVertex(0, CVertex(-fHalfWidth + 1.0f, +fHalfHeight - 2.0f, +fHalfDepth));
	pTopFace->SetVertex(1, CVertex(+fHalfWidth + 1.0f, +fHalfHeight - 2.0f, +fHalfDepth));
	pTopFace->SetVertex(2, CVertex(+fHalfWidth + 1.0f, +fHalfHeight - 2.0f, -fHalfDepth));
	pTopFace->SetVertex(3, CVertex(-fHalfWidth + 1.0f, +fHalfHeight - 2.0f, -fHalfDepth));
	SetPolygon(i * 6 + 1, pTopFace);

	CPolygon* pBackFace = new CPolygon(4);
	pBackFace->SetVertex(0, CVertex(-fHalfWidth + 1.0f, -fHalfHeight - 2.0f, +fHalfDepth));
	pBackFace->SetVertex(1, CVertex(+fHalfWidth + 1.0f, -fHalfHeight - 2.0f, +fHalfDepth));
	pBackFace->SetVertex(2, CVertex(+fHalfWidth + 1.0f, +fHalfHeight - 2.0f, +fHalfDepth));
	pBackFace->SetVertex(3, CVertex(-fHalfWidth + 1.0f, +fHalfHeight - 2.0f, +fHalfDepth));
	SetPolygon(i * 6 + 2, pBackFace);

	CPolygon* pBottomFace = new CPolygon(4);
	pBottomFace->SetVertex(0, CVertex(-fHalfWidth + 1.0f, -fHalfHeight - 2.0f, -fHalfDepth));
	pBottomFace->SetVertex(1, CVertex(+fHalfWidth + 1.0f, -fHalfHeight - 2.0f, -fHalfDepth));
	pBottomFace->SetVertex(2, CVertex(+fHalfWidth + 1.0f, -fHalfHeight - 2.0f, +fHalfDepth));
	pBottomFace->SetVertex(3, CVertex(-fHalfWidth + 1.0f, -fHalfHeight - 2.0f, +fHalfDepth));
	SetPolygon(i * 6 + 3, pBottomFace);

	CPolygon* pLeftFace = new CPolygon(4);
	pLeftFace->SetVertex(0, CVertex(-fHalfWidth + 1.0f, +fHalfHeight - 2.0f, +fHalfDepth));
	pLeftFace->SetVertex(1, CVertex(-fHalfWidth + 1.0f, +fHalfHeight - 2.0f, -fHalfDepth));
	pLeftFace->SetVertex(2, CVertex(-fHalfWidth + 1.0f, -fHalfHeight - 2.0f, -fHalfDepth));
	pLeftFace->SetVertex(3, CVertex(-fHalfWidth + 1.0f, -fHalfHeight - 2.0f, +fHalfDepth));
	SetPolygon(i * 6 + 4, pLeftFace);

	CPolygon* pRightFace = new CPolygon(4);
	pRightFace->SetVertex(0, CVertex(+fHalfWidth + 1.0f, +fHalfHeight - 2.0f, -fHalfDepth));
	pRightFace->SetVertex(1, CVertex(+fHalfWidth + 1.0f, +fHalfHeight - 2.0f, +fHalfDepth));
	pRightFace->SetVertex(2, CVertex(+fHalfWidth + 1.0f, -fHalfHeight - 2.0f, +fHalfDepth));
	pRightFace->SetVertex(3, CVertex(+fHalfWidth + 1.0f, -fHalfHeight - 2.0f, -fHalfDepth));
	SetPolygon(i * 6 + 5, pRightFace);
	

	m_xmOOBB = BoundingOrientedBox(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(fHalfWidth, fHalfHeight, fHalfDepth), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
}

CNameMesh::~CNameMesh()
{

}