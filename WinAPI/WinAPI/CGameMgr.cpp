#include "pch.h"
#include "CGameMgr.h"
#include "CEngine.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CBlock.h"
#include "CCollisionMgr.h"

CGameMgr::CGameMgr()
	: m_Score(0)
{}
CGameMgr::~CGameMgr()
{}

void CGameMgr::Init()
{
	RECT rt = {};
	GetClientRect(CEngine::Get()->GetMainHwnd(), &rt);
	int weight = rt.right;

	CLevel* level = CLevelMgr::Get()->GetCurrentLevel();
	// 블록 생성
	for (int PosY = 0; PosY < 300; PosY += 50)
	{
		for (int PosX = 0; PosX < weight; PosX += 100)
		{
			CBlock* pBlock = new CBlock;
			pBlock->SetScale(100, 50);
			pBlock->SetPos(PosX, PosY);
			CreateObject(pBlock, LAYER_TYPE::MONSTER);

			pBlock->Init();
		}
	}

	CCollisionMgr::Get()->CollisionCheck((UINT)LAYER_TYPE::PLAYER, (UINT)LAYER_TYPE::PLAYER_PROJECTILE, true);

}

void CGameMgr::Tick()
{
}
