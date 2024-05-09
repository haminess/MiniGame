#include "pch.h"
#include "CDebugMgr.h"

#include "CTimeMgr.h"
#include "CEngine.h"

CDebugMgr::CDebugMgr()
{

}

CDebugMgr::~CDebugMgr()
{

}

void CDebugMgr::Tick()
{
	// 디버그 쉐이프를 그릴 DC 를 가져온다(백버퍼 DC)
	HDC hBackDC = CEngine::Get()->GetBackDC();

	// 디버그 쉐이프 정보들을 모두 그리기위해서 반복문을 돈다.
	list<tDebugShapeInfo>::iterator iter = m_DbgList.begin();
	for ( ; iter != m_DbgList.end(); )
	{
		// 백버퍼 DC 가 요청된 펜을 선택하게 한다.
		SELECT_PEN(hBackDC, (*iter).Pen);

		// 백버퍼 DC 가 요청된 브러쉬를 선택하게 한다.
		SELECT_BRUSH(hBackDC, (*iter).BRUSH);

		switch ((*iter).Shape)
		{
		case DEBUG_SHAPE::RECT:
			Rectangle(hBackDC
				, (*iter).Position.x - (*iter).Scale.x / 2.f
				, (*iter).Position.y - (*iter).Scale.y / 2.f
				, (*iter).Position.x + (*iter).Scale.x / 2.f
				, (*iter).Position.y + (*iter).Scale.y / 2.f);
			break;
		case DEBUG_SHAPE::CIRCLE:
			Ellipse(hBackDC
				, (*iter).Position.x - (*iter).Scale.x / 2.f
				, (*iter).Position.y - (*iter).Scale.y / 2.f
				, (*iter).Position.x + (*iter).Scale.x / 2.f
				, (*iter).Position.y + (*iter).Scale.y / 2.f);
			break;
		case DEBUG_SHAPE::CROSS:
			MoveToEx(hBackDC, (*iter).Position.x - (*iter).Scale.x / 2.f, (*iter).Position.y, nullptr);
			LineTo(hBackDC, (*iter).Position.x + (*iter).Scale.x / 2.f, (*iter).Position.y);

			MoveToEx(hBackDC, (*iter).Position.x, (*iter).Position.y - (*iter).Scale.y / 2.f, nullptr);
			LineTo(hBackDC, (*iter).Position.x, (*iter).Position.y + (*iter).Scale.y / 2.f);
			break;		
		}

		// 시간을 체크하다가, DebugShape 유지시간을 넘기면, 리스트에서 정보를 제거한다.
		(*iter).Time += DT;
		if ((*iter).Duration < (*iter).Time)
		{
			iter = m_DbgList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}