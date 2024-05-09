#include "pch.h"
#include "CMonster.h"

#include "CEngine.h"
#include "CCollider.h"

CMonster::CMonster()
{
	m_Collider = AddComponent(new CCollider);
	m_Collider->SetScale(GetScale());
}

CMonster::~CMonster()
{
}

void CMonster::Tick()
{

}

void CMonster::Render()
{
	HDC dc = CEngine::Get()->GetBackDC();

	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	Ellipse(dc, vPos.x - (vScale.x / 2.f), vPos.y - (vScale.y / 2.f)
		, vPos.x + (vScale.x / 2.f), vPos.y + (vScale.y / 2.f));
}

void CMonster::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	/*if (L"Player" == _OtherObj->GetName())
	{
		DeleteObject(this);
	}*/

	if (L"Missile" == _OtherObj->GetName())
	{
		DeleteObject(this);
	}
}