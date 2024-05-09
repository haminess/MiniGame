#include "pch.h"
#include "CObj.h"

#include "CEngine.h"
#include "CTimeMgr.h"

#include "CComponent.h"

CObj::CObj()
	: m_LayerType(-1)
	, m_bDead(false)
{
}

CObj::~CObj()
{
	Release_Vector(m_vecComponent);
}


CComponent* CObj::GetComponent(COMPONENT_TYPE _Type)
{
	for (size_t i = 0; i < m_vecComponent.size(); ++i)
	{
		if (m_vecComponent[i]->GetComponentType() == _Type)
			return m_vecComponent[i];
	}

	return nullptr;
}

void CObj::FinalTick()
{
	for (size_t i = 0; i < m_vecComponent.size(); ++i)
	{
		m_vecComponent[i]->FinalTick();
	}
}

void CObj::Render()
{
	HDC dc = CEngine::Get()->GetBackDC();

	SELECT_PEN(dc, PEN_TYPE::RED);
	SELECT_BRUSH(dc, BRUSH_TYPE::BLUE);	

	Rectangle(dc, m_Pos.x - (m_Scale.x / 2.f), m_Pos.y - (m_Scale.y / 2.f)
				, m_Pos.x + (m_Scale.x / 2.f), m_Pos.y + (m_Scale.y / 2.f));
}