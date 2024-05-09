#include "pch.h"
#include "CLevelMgr.h"

#include "CEngine.h"

#include "CLevel.h"
#include "CPlayer.h"
#include "CMonster.h"

#include "CCollisionMgr.h"


CLevelMgr::CLevelMgr()
	: m_arrLevel{}
	, m_CurLevel(nullptr)
{}

CLevelMgr::~CLevelMgr()
{
	for (int i = 0; i < (int)LEVEL_TYPE::END; ++i)
	{
		if(nullptr != m_arrLevel[i])
			delete m_arrLevel[i];
	}	
}

void CLevelMgr::Init()
{
	// Level 생성
	m_CurLevel = m_arrLevel[(int)LEVEL_TYPE::START] = new CLevel;
	

	// 오브젝트 위치 설정
	CObj* pObj = new CPlayer;
	pObj->SetName(L"Player");

	RECT rt = {};
	HWND hWnd = CEngine::Get()->GetMainHwnd();
	GetClientRect(hWnd, &rt);

	pObj->SetPos((float)((rt.right - rt.left) / 2), (float)((rt.bottom - rt.top) / 2));
	pObj->SetScale(100.f, 100.f);

	m_CurLevel->AddObject(pObj, LAYER_TYPE::PLAYER);


	pObj = new CMonster;
	GetClientRect(hWnd, &rt);
	pObj->SetPos((float)((rt.right - rt.left) / 2) + 300.f, (float)((rt.bottom - rt.top) / 2));
	pObj->SetScale(150.f, 150.f);

	m_CurLevel->AddObject(pObj, LAYER_TYPE::MONSTER);


	// 충돌 지정
	CCollisionMgr::Get()->CollisionCheck(5, 3, true);	
	CCollisionMgr::Get()->CollisionCheck((UINT)LAYER_TYPE::PLAYER_PROJECTILE, (UINT)LAYER_TYPE::MONSTER, true);
}

void CLevelMgr::Tick()
{
	m_CurLevel->Tick();
	m_CurLevel->FinalTick();
}

void CLevelMgr::Render()
{
	m_CurLevel->Render();
}
