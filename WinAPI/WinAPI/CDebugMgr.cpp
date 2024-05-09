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
	// ����� �������� �׸� DC �� �����´�(����� DC)
	HDC hBackDC = CEngine::Get()->GetBackDC();

	// ����� ������ �������� ��� �׸������ؼ� �ݺ����� ����.
	list<tDebugShapeInfo>::iterator iter = m_DbgList.begin();
	for ( ; iter != m_DbgList.end(); )
	{
		// ����� DC �� ��û�� ���� �����ϰ� �Ѵ�.
		SELECT_PEN(hBackDC, (*iter).Pen);

		// ����� DC �� ��û�� �귯���� �����ϰ� �Ѵ�.
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

		// �ð��� üũ�ϴٰ�, DebugShape �����ð��� �ѱ��, ����Ʈ���� ������ �����Ѵ�.
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