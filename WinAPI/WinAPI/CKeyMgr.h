#pragma once

enum class KEY
{
	W,
	S,
	A,
	D,

	LEFT,
	RIGHT,
	UP,
	DOWN,

	SPACE,

	END,
};



enum class KEY_STATE
{
	TAP,		// �� ���� ����
	PRESSED,	// ��� �����ִ� ����
	RELEASED,	// �� �� ����
	NONE,		// �������� ���� ����
};


struct tKeyInfo
{
	KEY_STATE	State;
	bool		PrevPressed;
};


class CKeyMgr
{
	SINGLE(CKeyMgr);
private:
	vector<tKeyInfo>	m_vecKey;

public:
	void Init();
	void Tick();

	KEY_STATE GetKeyState(KEY _Key)
	{
		return m_vecKey[(int)_Key].State;
	}
};

