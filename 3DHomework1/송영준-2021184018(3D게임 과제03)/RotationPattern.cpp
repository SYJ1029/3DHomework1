#include "Patterns.h"

CRotationPattern::CRotationPattern()
{
	m_xmf3RotationAxis = XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_fRotationSpeed = 90.0f;
}
CRotationPattern::~CRotationPattern()
{
}