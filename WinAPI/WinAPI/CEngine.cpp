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
	// ȭ�鿡 �׸���(Rendering) �۾��� ����ϴ� ��ġ
	// �������� �ʿ��� ������ ����
	// Pen(Black), Brush(White), Bitmap
	m_DC = GetDC(m_hMainWnd);

	// ������ �ػ� ����
	ChangeWindowResolution(_Width, _Height);

	// BackBuffer ����
	m_hBackBuffer = CreateCompatibleBitmap(m_DC, _Width, _Height);

	// BackBuffer �� DC ����
	m_hBackBufferDC = CreateCompatibleDC(m_DC);

	// BackBufferDC �� BackBuffer ��Ʈ���� ������ Ÿ������ �����ϰ�, 
	// DC �� ���� ����ִ� 1�ȼ�¥�� ��Ʈ���� ����Ѵ�.
	DeleteObject(SelectObject(m_hBackBufferDC, m_hBackBuffer));

	// ���� ����� �� �� �귯�� ����
	CreateGDIObject();
	
	// Manager �ʱ�ȭ
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

	// Level ��ü�� ������
	Render();	

	// ���� �����ӿ� ����Ǿ� �� �۾����� ó��
	CTaskMgr::Get()->Tick();
}

void CEngine::Render()
{
	// Rendering
	// ������ ȭ��(��Ʈ��) �� Ư�� �������� Clear ���ش�.
	HBRUSH hPrevBrush = (HBRUSH)SelectObject(m_hBackBufferDC, m_Brush[(int)BRUSH_TYPE::GRAY]);
	Rectangle(m_hBackBufferDC, -1, -1, (int)m_Resolution.x + 1, (int)m_Resolution.y + 1);
	SelectObject(m_hBackBufferDC, hPrevBrush);
	
	// ������ ��ü���� ȭ�鿡 ������
	CLevelMgr::Get()->Render();

	// GetCurrentDirectory �׽�Ʈ
	wchar_t CurDir[256] = {};
	GetCurrentDirectory(256, CurDir);
	TextOut(m_hBackBufferDC, 10, 10, CurDir, wcslen(CurDir));

	WCHAR score[256] = {};
	wsprintf(score, L"Score : %d", CGameMgr::Get()->GetScore());
	TextOut(m_hBackBufferDC, 10, 30, score, wcslen(score));

	// Debug ������
	CDebugMgr::Get()->Tick();

	// BackBuffer �׸��� MainDC ���۷� ����
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
	// �����ϰ��� �ϴ� �ػ� ������ Engine ��ü�� ����
	m_Resolution.x = (float)_Width;
	m_Resolution.y = (float)_Height;

	// ũ�⸦ �����Ϸ��� �������� �޴� ���翩�θ� Ȯ��
	HMENU hMenu = GetMenu(m_hMainWnd);

	// �������� �׸��⿵��(��Ʈ��) �� �ػ󵵸� ���ϴ� ��ġ�� ����� ���ؼ�
	// ���� �����찡 ������ �ϴ� ũ�⸦ ���
	RECT rt = {0, 0, _Width, _Height};
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, (bool)hMenu);

	// �������� ���� ������ ũ�Ⱚ���� ������ ũ�⸦ ����
	SetWindowPos(m_hMainWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
}