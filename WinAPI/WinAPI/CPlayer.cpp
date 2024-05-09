#include "pch.h"
#include "CPlayer.h"

#include "CDebugMgr.h"

#include "CTimeMgr.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CMissile.h"
#include "CGuidedMissile.h"

#include "CKeyMgr.h"
#include "CTaskMgr.h"
#include "CEngine.h"
#include "CPathMgr.h"

#include "CAssetMgr.h"
#include "CTexture.h"

#include "CCollider.h"
#include "CGameMgr.h"


CPlayer::CPlayer()
	: m_Speed(600.f)
	, m_Texture(nullptr)
{
	m_Texture = CAssetMgr::Get()->LoadTexture(L"Fighter", L"texture\\Fighter.bmp");

	if (m_Texture)
	{
		SetScale((float)m_Texture->GetWidth(), (float)m_Texture->GetHeight());
	}

	// 컴포넌트 설정
	m_Body = AddComponent(new CCollider);
	m_Body->SetName(L"Body Collider");

	m_Face = AddComponent(new CCollider);
	m_Face->SetName(L"Face Collider");

	m_Body->SetOffset(Vec2(0.f, 20.f));
	m_Body->SetScale(Vec2(100.f, 30.f));

	m_Face->SetOffset(Vec2(0.f, -40.f));
	m_Face->SetScale(Vec2(20.f, 30.f));
}

CPlayer::~CPlayer()
{
	
}

void CPlayer::Tick()
{
	float fDT = CTimeMgr::Get()->GetDeltaTime();

	Vec2 vPos = GetPos();

	if (GetAsyncKeyState(VK_LEFT) & 0x8001)
	{
		vPos.x -= m_Speed * fDT;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8001)
	{
		vPos.x += m_Speed * fDT;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8001)
	{
		vPos.y -= m_Speed * fDT;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8001)
	{
		vPos.y += m_Speed * fDT;
	}
	
	if (KEY_TAP(KEY::SPACE))
	{		
		CMissile* pMissile = new CMissile;
		pMissile->SetName(L"Missile");
		pMissile->SetPos(GetPos().x, GetPos().y - 100.f);
		pMissile->SetScale(20.f, 20.f);	
		pMissile->SetVelocity(Vec2(0, -1), 300.f);

		CreateObject(pMissile, LAYER_TYPE::PLAYER_PROJECTILE);

		CGameMgr::Get()->AddScore(-10);
	}

	

	SetPos(vPos);
}

void CPlayer::Render()
{
	if (nullptr == m_Texture)
	{
		CObj::Render();
		return;
	}
	
	Vec2 vPos = GetPos();

	UINT Width = m_Texture->GetWidth();
	UINT Height = m_Texture->GetHeight();

	TransparentBlt(	  CEngine::Get()->GetBackDC()
					, ((UINT)vPos.x - Width / 2)
					, ((UINT)vPos.y - Height / 2)
					, Width, Height
					, m_Texture->GetDC()
					, 0, 0, Width, Height
					, RGB(255, 0, 255));
}

void CPlayer::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (_OwnCollider->GetName() == L"Body Collider")
	{
		int a = 0;
	}
	if (_OtherObj->GetName() == L"Missile")
	{
		CMissile* m = (CMissile*)_OtherObj;

		Vec2 newV; 
		newV.x = (GetPos().x - m->GetPos().x) * 0.01f;
		newV.y = 1;
		m->SetVelocity(newV);
	}

	if (_OwnCollider == m_Body)
	{
		int a = 0;
	}
}