#include "pch.h"
#include "CMissile.h"

#include "CTimeMgr.h"
#include "CEngine.h"
#include "CCollider.h"

CMissile::CMissile()
	: m_Velocity(1.f, -1.f)
{
	m_Velocity.Normalize();
	m_Velocity *= 200.f;

	CCollider* pCollider = AddComponent(new CCollider);
	pCollider->SetScale(Vec2(20.f, 20.f));
}

CMissile::~CMissile()
{
}

void CMissile::Tick()
{
	Vec2 vPos = GetPos();

	vPos += m_Velocity * DT;

	SetPos(vPos);
}

void CMissile::Render()
{
	HDC dc = CEngine::Get()->GetBackDC();

	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	Ellipse(dc, vPos.x - (vScale.x / 2.f), vPos.y - (vScale.y / 2.f)
		, vPos.x + (vScale.x / 2.f), vPos.y + (vScale.y / 2.f));
}

void CMissile::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{

	//if (L"Player" != _OtherObj->GetName())
	//	DeleteObject(this);
	static bool isDone = false;

	if (isDone)
	{
		isDone = false;
	}
	else
	{
		Vec2 old = GetVelocity();
		Vec2 newV = Vec2(-1 * old.x, -1 * old.y);
		SetVelocity(newV, GetVelocity().Length());
		isDone = true;
	}
}
