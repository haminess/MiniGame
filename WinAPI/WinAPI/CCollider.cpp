#include "pch.h"
#include "CCollider.h"

#include "CDebugMgr.h"
#include "CCollisionMgr.h"

CCollider::CCollider()
	: CComponent(COMPONENT_TYPE::COLLIDER)
	, m_OverlapCount(0)
{
}

CCollider::~CCollider()
{
}

void CCollider::FinalTick()
{
	// �浹ü�� ���� ��ġ ���
	m_FinalPos = GetOwner()->GetPos() + m_OffsetPos;

	// �浹ü�� ���̾� ��ȣ�� �°� �浹�Ŵ����� ���
	CCollisionMgr::Get()->RegisterCollider(this, (LAYER_TYPE)GetOwner()->GetLayerType());

	// �浹ü�� ����� ������ ��û
	if(m_OverlapCount)
		DrawDebugShape(DEBUG_SHAPE::RECT, PEN_TYPE::RED, BRUSH_TYPE::HOLLOW, m_FinalPos, m_Scale);	
	else
		DrawDebugShape(DEBUG_SHAPE::RECT, PEN_TYPE::GREEN, BRUSH_TYPE::HOLLOW, m_FinalPos, m_Scale);
}

void CCollider::BeginOverlap(CCollider* _Other)
{
	++m_OverlapCount;

	GetOwner()->BeginOverlap(this, _Other->GetOwner(), _Other);	
}

void CCollider::Overlap(CCollider* _Other)
{
	GetOwner()->Overlap(this, _Other->GetOwner(), _Other);
}

void CCollider::EndOverlap(CCollider* _Other)
{
	--m_OverlapCount;

	GetOwner()->EndOverlap(this, _Other->GetOwner(), _Other);	
}
