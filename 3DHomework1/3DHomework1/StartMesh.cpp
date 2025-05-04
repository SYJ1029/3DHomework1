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

	float offsetX = -10.0f; // x 이동 시작
	const float letterGap = 2.0f; // 글자 간 간격
	const float size = 0.5f; // 한 글자 기본 스케일
	const float rhombusSize = 0.5f; // 마름모꼴(ㅇ) 한 변 길이

	std::list<std::pair<CVertex*, CVertex*>> lines;

	Loadlines("3D게임 프로그래밍.txt", lines);

	//lines.push_back({ new CVertex(offsetX - size,  size, 0.0f), new CVertex(offsetX + size,  size, 0.0f) }); // 위 가로
	//lines.push_back({ new CVertex(offsetX - size,  0.0f, 0.0f), new CVertex(offsetX + size,  0.0f, 0.0f) }); // 중간 가로
	//lines.push_back({ new CVertex(offsetX - size, -size, 0.0f), new CVertex(offsetX + size, -size, 0.0f) }); // 아래 가로
	//lines.push_back({ new CVertex(offsetX + size,  size, 0.0f), new CVertex(offsetX + size, -size, 0.0f) }); // 오른쪽 수직

	//// D

	//offsetX += letterGap;

	//lines.push_back({ new CVertex(offsetX - size,  size, 0.0f), new CVertex(offsetX - size, -size, 0.0f) }); // 왼쪽 수직
	//lines.push_back({ new CVertex(offsetX - size,  size, 0.0f), new CVertex(offsetX + size,  size * 0.7f, 0.0f) }); // 위 사선
	//lines.push_back({ new CVertex(offsetX + size,  size * 0.7f, 0.0f), new CVertex(offsetX + size,  size * -0.7f, 0.0f) }); // 오른쪽 수직
	//lines.push_back({ new CVertex(offsetX + size,  size * -0.7f, 0.0f), new CVertex(offsetX - size, -size, 0.0f) }); // 아래 사선

	//offsetX += letterGap;


	//// ㄱ
	////lines.push_back({ new CVertex(offsetX - size,  size, 0.0f), new CVertex(offsetX,  size, 0.0f) });
	////lines.push_back({ new CVertex(offsetX - size,  size, 0.0f), new CVertex(offsetX - size,  0.0f, 0.0f) });
	//lines.push_back({ new CVertex(offsetX - 1.75f, 1.0f, 0.0f), new CVertex(offsetX - 0.25f, 1.0f, 0.0f) }); // ㄱ 가로
	//lines.push_back({ new CVertex(offsetX - 0.25f, 1.0f, 0.0f), new CVertex(offsetX - 0.25f, -0.5f, 0.0f) }); // ㄱ 수직


	//// ㅔ
	//lines.push_back({ new CVertex(offsetX + 0.5f,  size + 0.5f, 0.0f), new CVertex(offsetX + 0.5f, -size - 0.5f, 0.0f) });
	//lines.push_back({ new CVertex(offsetX + 1.0f,  size + 0.5f, 0.0f), new CVertex(offsetX + 1.0f, -size - 0.5f, 0.0f) });
	//lines.push_back({ new CVertex(offsetX,  0.5f, 0.0f), new CVertex(offsetX + 0.5f,  0.5f, 0.0f) });


	//offsetX += letterGap;
	//// ㅇ (마름모꼴) 좌상단
	//lines.push_back({ new CVertex(offsetX - 0.5f, 1.0f, 0.0f), new CVertex(offsetX, 1.5f, 0.0f) });
	//lines.push_back({ new CVertex(offsetX, 1.5f, 0.0f), new CVertex(offsetX + 0.5f, 1.0f, 0.0f) });
	//lines.push_back({ new CVertex(offsetX + 0.5f, 1.0f, 0.0f), new CVertex(offsetX, 0.5f, 0.0f) });
	//lines.push_back({ new CVertex(offsetX, 0.5f, 0.0f), new CVertex(offsetX - 0.5f, 1.0f, 0.0f) });

	//// ㅣ 우상단
	//lines.push_back({ new CVertex(offsetX + 1.0f, 1.5f, 0.0f), new CVertex(offsetX + 1.0f, 0.5f, 0.0f) });

	//// ㅁ 하단
	//lines.push_back({ new CVertex(offsetX - 0.5f, 0.0f, 0.0f), new CVertex(offsetX + 0.5f, 0.0f, 0.0f) });
	//lines.push_back({ new CVertex(offsetX + 0.5f, 0.0f, 0.0f), new CVertex(offsetX + 0.5f, -1.0f, 0.0f) });
	//lines.push_back({ new CVertex(offsetX + 0.5f, -1.0f, 0.0f), new CVertex(offsetX - 0.5f, -1.0f, 0.0f) });
	//lines.push_back({ new CVertex(offsetX - 0.5f, -1.0f, 0.0f), new CVertex(offsetX - 0.5f, 0.0f, 0.0f) });

	//offsetX += letterGap * 2;


	//lines.push_back({ new CVertex(offsetX - 1.0f,  1.0f, 0.0f), new CVertex(offsetX + 1.0f,  1.0f, 0.0f) }); // 위 가로
	//lines.push_back({ new CVertex(offsetX - 1.0f,  0.0f, 0.0f), new CVertex(offsetX + 1.0f,  0.0f, 0.0f) }); // 중간 가로
	//lines.push_back({ new CVertex(offsetX - 0.5f,  1.0f, 0.0f), new CVertex(offsetX - 0.5f, 0.0f, 0.0f) }); // 왼쪽 수직
	//lines.push_back({ new CVertex(offsetX + 0.5f,  1.0f, 0.0f), new CVertex(offsetX + 0.5f, 0.0f, 0.0f) }); // 오른쪽 수직
	//lines.push_back({ new CVertex(offsetX - 1.0f,  -1.5f, 0.0f), new CVertex(offsetX + 1.0f,  -1.5f, 0.0f) });

	//offsetX += letterGap;

	//float baseX = offsetX + 1.25f;

	//// ㄹ 부분
	//// 1. 위 가로
	//lines.push_back({ new CVertex(baseX,  1.0f, 0.0f), new CVertex(baseX - 1.0f,  1.0f, 0.0f) });
	//// 2. 오른쪽 수직
	//lines.push_back({ new CVertex(baseX,  1.0f, 0.0f), new CVertex(baseX,  0.5f, 0.0f) });
	//// 3. 중간 가로
	//lines.push_back({ new CVertex(baseX,  0.5f, 0.0f), new CVertex(baseX - 1.0f,  0.5f, 0.0f) });
	//// 4. 왼쪽 수직
	//lines.push_back({ new CVertex(baseX - 1.0f,  0.5f, 0.0f), new CVertex(baseX - 1.0f, -0.5f, 0.0f) });
	//// 5. 아래 가로
	//lines.push_back({ new CVertex(baseX - 1.0f, -0.5f, 0.0f), new CVertex(baseX, -0.5f, 0.0f) });

	//// ㅗ 부분
	//lines.push_back({ new CVertex(offsetX - 0.25f, -1.5f, 0.0f), new CVertex(offsetX + 1.75f, -1.5f, 0.0f) }); // ㅡ 가로 (늘린 버전)
	//lines.push_back({ new CVertex(offsetX + 0.75f, -1.5f, 0.0f), new CVertex(offsetX + 0.75f, -1.0f, 0.0f) }); // ㅣ 세로 (변화 없음)

	//offsetX += letterGap;



	////그
	//lines.push_back({ new CVertex(offsetX - 1.0f,  1.0f, 0.0f), new CVertex(offsetX + 0.5f,  1.0f, 0.0f) }); // ㄱ 가로
	//lines.push_back({ new CVertex(offsetX + 0.5f,  1.0f, 0.0f), new CVertex(offsetX + 0.5f, -0.5f, 0.0f) }); // ㄱ 수직
	//lines.push_back({ new CVertex(offsetX - 1.0f, -1.0f, 0.0f), new CVertex(offsetX + 1.0f, -1.0f, 0.0f) }); // ㅡ 가로

	//offsetX += letterGap;


	//// ㄹ
	//lines.push_back({ new CVertex(offsetX,  1.0f, 0.0f), new CVertex(offsetX - 1.0f,  1.0f, 0.0f) }); // 위 가로
	//lines.push_back({ new CVertex(offsetX,  1.0f, 0.0f), new CVertex(offsetX,  0.5f, 0.0f) }); // 오른쪽 수직
	//lines.push_back({ new CVertex(offsetX,  0.5f, 0.0f), new CVertex(offsetX - 1.0f,  0.5f, 0.0f) }); // 중간 가로
	//lines.push_back({ new CVertex(offsetX - 1.0f,  0.5f, 0.0f), new CVertex(offsetX - 1.0f, -0.5f, 0.0f) }); // 왼쪽 수직
	//lines.push_back({ new CVertex(offsetX - 1.0f, -0.5f, 0.0f), new CVertex(offsetX, -0.5f, 0.0f) }); // 아래 가로

	//// ㅐ
	//lines.push_back({ new CVertex(offsetX + 0.5f,  1.0f, 0.0f), new CVertex(offsetX + 0.5f, -1.0f, 0.0f) }); // 세로
	//lines.push_back({ new CVertex(offsetX + 0.5f,  0.0f, 0.0f), new CVertex(offsetX + 1.0f,  0.0f, 0.0f) }); // 가로
	//lines.push_back({ new CVertex(offsetX + 1.0f,  1.0f, 0.0f), new CVertex(offsetX + 1.0f, -1.0f, 0.0f) }); // ㅣ 세로

	//offsetX += letterGap;


	//// ㅁ
	//lines.push_back({ new CVertex(offsetX - 1.0f,  1.0f, 0.0f), new CVertex(offsetX + 1.0f,  1.0f, 0.0f) }); // 위 가로
	//lines.push_back({ new CVertex(offsetX - 1.0f, -1.0f, 0.0f), new CVertex(offsetX + 1.0f, -1.0f, 0.0f) }); // 아래 가로
	//lines.push_back({ new CVertex(offsetX - 1.0f,  1.0f, 0.0f), new CVertex(offsetX - 1.0f, -1.0f, 0.0f) }); // 왼쪽 수직
	//lines.push_back({ new CVertex(offsetX + 1.0f,  1.0f, 0.0f), new CVertex(offsetX + 1.0f, -1.0f, 0.0f) }); // 오른쪽 수직

	//// ㅣ
	//lines.push_back({ new CVertex(offsetX + 1.5f,  1.0f, 0.0f), new CVertex(offsetX + 1.5f, -1.0f, 0.0f) }); // ㅣ 세로

	//// ㅇ (받침, 마름모꼴)
	//lines.push_back({ new CVertex(offsetX, -1.5f, 0.0f), new CVertex(offsetX + 0.5f, -2.0f, 0.0f) }); // ↘
	//lines.push_back({ new CVertex(offsetX + 0.5f, -2.0f, 0.0f), new CVertex(offsetX + 1.0f, -1.5f, 0.0f) }); // ↗
	//lines.push_back({ new CVertex(offsetX + 1.0f, -1.5f, 0.0f), new CVertex(offsetX + 0.5f, -1.0f, 0.0f) }); // ↖
	//lines.push_back({ new CVertex(offsetX + 0.5f, -1.0f, 0.0f), new CVertex(offsetX, -1.5f, 0.0f) }); // ↙

	//Savelines("3D게임 프로그래밍.txt", lines);

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