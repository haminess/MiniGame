#include "pch.h"
#include "CBlock.h"
#include "CCollider.h"
#include "CObj.h"
#include "CGameMgr.h"
#include "CEngine.h"
#include "CMonster.h"
#include "CMissile.h"

CBlock::CBlock()
	: m_Brush(BRUSH_TYPE::END)
	, m_Color{}
{
	// random brush
	std::random_device rd;
	std::mt19937 mt(rd());
	std::mt19937 gen(rd());
	int num = gen() % ((int)BRUSH_TYPE::HOLLOW - 1);
	//std::uniform_int_distribution<int> dist(0, (int)BRUSH_TYPE::HOLLOW - 1);
	//auto randNum = dist(mt);
  

	// random color
	auto R = gen() % 255;
	auto G = gen() % 255;
	auto B = gen() % 255;

	//srand(time(NULL));
	//int ran = rand() % (int)BRUSH_TYPE::HOLLOW;
	m_Brush = (BRUSH_TYPE)num;
	m_Color = RGB(R, G, B);
}

CBlock::~CBlock()
{
}

void CBlock::Init()
{
	GetCollider()->SetScale(GetScale());
}

void CBlock::Tick()
{
}

void CBlock::Render()
{
	Vec2 pos = GetPos();
	Vec2 scale = GetScale();

	HDC dc = CEngine::Get()->GetBackDC();

	//SELECT_BRUSH(dc, m_Brush);
	HBRUSH old = (HBRUSH)SelectObject(dc, CreateSolidBrush(m_Color));

	Rectangle(dc,
		pos.x - (scale.x / 2), pos.y - (scale.y / 2),
		pos.x + (scale.x / 2), pos.y + (scale.y / 2));

	DeleteObject(SelectObject(dc, old));
}

void CBlock::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (L"Missile" == _OtherObj->GetName())
	{
		DeleteObject(this);
		CGameMgr::Get()->AddScore(1);

	}

}
