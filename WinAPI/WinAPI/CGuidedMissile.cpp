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

	// 1. 추적할 대상을 찾는다.
	//  - 미사일(본인)로부터 가장 가까운 대상을 찾는다.
	FindTarget();

	// 2. 추적할 대상과 미사일이 이루는 각도를 구한다.
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
	
	// 3. 지정된 각도(방행) 로 본인(미사일)을 이동시킨다.
	CMissile::Tick();
}

void CGuidedMissile::FindTarget()
{
	if (nullptr != m_TargetObj)
		return;

	// 탐지범위
	float MinDist = m_DetectRange;

	// 미사일의 위치
	Vec2 vMissilePos = GetPos();

	// 미사일(본인)과 가장 가까운 몬스터를 찾는다.
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

// 1. 삼각함수
// 2. 스칼라(크기), 벡터(크기, 방향)
// 2. 내적
// 3. 외적
// 4. 평면의 방정식
// 5. 직선의 방정식
// 6. 평면과 직선의 교점
