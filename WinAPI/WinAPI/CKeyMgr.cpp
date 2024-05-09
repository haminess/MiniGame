#include "pch.h"
#include "CKeyMgr.h"

int g_arrKeyValue[(int)KEY::END]
=
{
	'W',
	'S',
	'A',
	'D',

	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,

	VK_SPACE,
};




CKeyMgr::CKeyMgr()
{

}

CKeyMgr::~CKeyMgr()
{

}


void CKeyMgr::Init()
{
	for (int i = 0; i < (int)KEY::END; ++i)
	{
		m_vecKey.push_back(tKeyInfo{KEY_STATE::NONE, false});
	}
}

void CKeyMgr::Tick()
{
	for (size_t i = 0; i < m_vecKey.size(); ++i)
	{
		// 키가 눌려있는지 확인
		if (GetAsyncKeyState(g_arrKeyValue[i]) & 0x8001)
		{
			// 키가 눌려있고, 이전에는 눌려있지 않았다.
			if (false == m_vecKey[i].PrevPressed)
			{
				m_vecKey[i].State = KEY_STATE::TAP;
			}

			// 키가 눌려있고, 이전에도 눌려있었다.
			else
			{
				m_vecKey[i].State = KEY_STATE::PRESSED;
			}

			m_vecKey[i].PrevPressed = true;
		}

		// 키가 눌려있지 않다면
		else
		{
			// 이전에는 눌려있었다.
			if (m_vecKey[i].PrevPressed)
			{
				m_vecKey[i].State = KEY_STATE::RELEASED;
			}
			else
			{
				m_vecKey[i].State = KEY_STATE::NONE;
			}

			m_vecKey[i].PrevPressed = false;
		}
	}
}
