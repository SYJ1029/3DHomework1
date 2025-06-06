#include "Player.h"

#include "Shader.h"


CRollerCosterPlayer::CRollerCosterPlayer(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList, ID3D12RootSignature* pd3dGraphicsRootSignature)
	:CAirplanePlayer(pd3dDevice, pd3dCommandList, pd3dGraphicsRootSignature)
{
	
}
CRollerCosterPlayer::~CRollerCosterPlayer()
{
}

