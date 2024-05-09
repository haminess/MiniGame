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
		// Ű�� �����ִ��� Ȯ��
		if (GetAsyncKeyState(g_arrKeyValue[i]) & 0x8001)
		{
			// Ű�� �����ְ�, �������� �������� �ʾҴ�.
			if (false == m_vecKey[i].PrevPressed)
			{
				m_vecKey[i].State = KEY_STATE::TAP;
			}

			// Ű�� �����ְ�, �������� �����־���.
			else
			{
				m_vecKey[i].State = KEY_STATE::PRESSED;
			}

			m_vecKey[i].PrevPressed = true;
		}

		// Ű�� �������� �ʴٸ�
		else
		{
			// �������� �����־���.
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
