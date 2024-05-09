#include "pch.h"
#include "CGuidedMissile.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CMonster.h"


CGuidedMissile::CGuidedMissile()
	: m_TargetObj(nullptr)
	, m_DetectRange(500.f)
{
}

CGuidedMissile::~CGuidedMissile()
{
}

void CGuidedMissile::Tick()
{
	DrawDebugShape(DEBUG_SHAPE::CIRCLE, PEN_TYPE::GREEN, BRUSH_TYPE::HOLLOW
		         , GetPos(), Vec2(m_DetectRange * 2.f, m_DetectRange * 2.f));

	// 1. ������ ����� ã�´�.
	//  - �̻���(����)�κ��� ���� ����� ����� ã�´�.
	FindTarget();

	// 2. ������ ���� �̻����� �̷�� ������ ���Ѵ�.
	if (IsValid(m_TargetObj))
	{
		Vec2 vDir = m_TargetObj->GetPos() - GetPos();
		vDir.Normalize();
		SetVelocity(vDir, GetVelocity().Length());
	}
	else
	{		
		SetVelocity(Vec2(0.f, -1.f), GetVelocity().Length());
	}
	
	// 3. ������ ����(����) �� ����(�̻���)�� �̵���Ų��.
	CMissile::Tick();
}

void CGuidedMissile::FindTarget()
{
	if (nullptr != m_TargetObj)
		return;

	// Ž������
	float MinDist = m_DetectRange;

	// �̻����� ��ġ
	Vec2 vMissilePos = GetPos();

	// �̻���(����)�� ���� ����� ���͸� ã�´�.
	CLevel* pCurLevel = CLevelMgr::Get()->GetCurrentLevel();
	const vector<CObj*>& vecMon = pCurLevel->GetLayer(LAYER_TYPE::MONSTER);
		
	for (size_t i = 0; i < vecMon.size(); ++i)
	{
		//Vec2 vDiff = vecMon[i]->GetPos() - vMissilePos;
		//float Dist = vDiff.Length();
	
		float Dist = vMissilePos.Distance(vecMon[i]->GetPos());

		if (Dist < MinDist)
		{
			MinDist = Dist;
			m_TargetObj = dynamic_cast<CMonster*>(vecMon[i]);
		}
	}
}

// 1. �ﰢ�Լ�
// 2. ��Į��(ũ��), ����(ũ��, ����)
// 2. ����
// 3. ����
// 4. ����� ������
// 5. ������ ������
// 6. ���� ������ ����
