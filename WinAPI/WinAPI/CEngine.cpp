#include "pch.h"
#include "CEngine.h"

#include "CTimeMgr.h"
#include "CLevelMgr.h"
#include "CKeyMgr.h"
#include "CLevel.h"
#include "CPathMgr.h"
#include "CDebugMgr.h"
#include "CTaskMgr.h"
#include "CCollisionMgr.h"
#include "CGameMgr.h"

CEngine::CEngine()
	: m_hMainWnd(nullptr)
	, m_DC(nullptr)
	, m_hBackBuffer(nullptr)
	, m_hBackBufferDC(nullptr)
	, m_Pen{}
	, m_Brush{}	
{
}

CEngine::~CEngine()
{
	ReleaseDC(m_hMainWnd, m_DC);

	DeleteObject(m_hBackBuffer);
	DeleteDC(m_hBackBufferDC);

	for (int i = 0; i < (int)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_Pen[i]);
	}

	for (int i = 0; i < (int)BRUSH_TYPE::HOLLOW; ++i)
	{
		DeleteObject(m_Brush[i]);
	}
}

void CEngine::Init(HWND _MainHwnd, UINT _Width, UINT _Height)
{
	m_hMainWnd = _MainHwnd;

	// DC(Device Context)
	// 화면에 그리기(Rendering) 작업을 담당하는 장치
	// 렌더링에 필요한 데이터 집합
	// Pen(Black), Brush(White), Bitmap
	m_DC = GetDC(m_hMainWnd);

	// 윈도우 해상도 적용
	ChangeWindowResolution(_Width, _Height);

	// BackBuffer 생성
	m_hBackBuffer = CreateCompatibleBitmap(m_DC, _Width, _Height);

	// BackBuffer 용 DC 생성
	m_hBackBufferDC = CreateCompatibleDC(m_DC);

	// BackBufferDC 가 BackBuffer 비트맵을 렌더링 타겟으로 지정하고, 
	// DC 가 원래 들고있던 1픽셀짜리 비트맵을 폐기한다.
	DeleteObject(SelectObject(m_hBackBufferDC, m_hBackBuffer));

	// 자주 사용할 펜 및 브러쉬 생성
	CreateGDIObject();
	
	// Manager 초기화
	CPathMgr::Get()->Init();
	CTimeMgr::Get()->Init();
	CKeyMgr::Get()->Init();
	CLevelMgr::Get()->Init();
	CGameMgr::Get()->Init();
}


void CEngine::Progress()
{	
	CTimeMgr::Get()->Tick();
	CKeyMgr::Get()->Tick();
	CLevelMgr::Get()->Tick();
	CCollisionMgr::Get()->Tick();
	CGameMgr::Get()->Tick();

	// Level 물체들 렌더링
	Render();	

	// 다음 프레임에 적용되야 할 작업들을 처리
	CTaskMgr::Get()->Tick();
}

void CEngine::Render()
{
	// Rendering
	// 윈도우 화면(비트맵) 을 특정 색상으로 Clear 해준다.
	HBRUSH hPrevBrush = (HBRUSH)SelectObject(m_hBackBufferDC, m_Brush[(int)BRUSH_TYPE::GRAY]);
	Rectangle(m_hBackBufferDC, -1, -1, (int)m_Resolution.x + 1, (int)m_Resolution.y + 1);
	SelectObject(m_hBackBufferDC, hPrevBrush);
	
	// 레벨에 물체들을 화면에 렌더링
	CLevelMgr::Get()->Render();

	// GetCurrentDirectory 테스트
	wchar_t CurDir[256] = {};
	GetCurrentDirectory(256, CurDir);
	TextOut(m_hBackBufferDC, 10, 10, CurDir, wcslen(CurDir));

	WCHAR score[256] = {};
	wsprintf(score, L"Score : %d", CGameMgr::Get()->GetScore());
	TextOut(m_hBackBufferDC, 10, 30, score, wcslen(score));

	// Debug 렌더링
	CDebugMgr::Get()->Tick();

	// BackBuffer 그림을 MainDC 버퍼로 복사
	BitBlt(m_DC, 0, 0, (int)m_Resolution.x, (int)m_Resolution.y, m_hBackBufferDC, 0, 0, SRCCOPY);
}

void CEngine::CreateGDIObject()
{
	m_Pen[(int)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_Pen[(int)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_Pen[(int)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	m_Pen[(int)PEN_TYPE::YELLOW] = CreatePen(PS_SOLID, 1, RGB(0, 255, 255));
	m_Pen[(int)PEN_TYPE::MAGENTA] = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));


	m_Brush[(int)BRUSH_TYPE::RED] = CreateSolidBrush(RGB(255, 0, 0));
	m_Brush[(int)BRUSH_TYPE::GREEN] = CreateSolidBrush(RGB(0, 255, 0));
	m_Brush[(int)BRUSH_TYPE::BLUE] = CreateSolidBrush(RGB(0, 0, 255));
	m_Brush[(int)BRUSH_TYPE::GRAY] = CreateSolidBrush(RGB(100, 100, 100));
	m_Brush[(int)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
}

void CEngine::ChangeWindowResolution(UINT _Width, UINT _Height)
{
	// 변경하고자 하는 해상도 정보를 Engine 객체에 저장
	m_Resolution.x = (float)_Width;
	m_Resolution.y = (float)_Height;

	// 크기를 변경하려는 윈도우의 메뉴 존재여부를 확인
	HMENU hMenu = GetMenu(m_hMainWnd);

	// 윈도우의 그리기영역(비트맵) 의 해상도를 원하는 수치로 만들기 위해서
	// 실제 윈도우가 가져야 하는 크기를 계산
	RECT rt = {0, 0, _Width, _Height};
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, (bool)hMenu);

	// 최종으로 계산된 윈도우 크기값으로 윈도우 크기를 변경
	SetWindowPos(m_hMainWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
}