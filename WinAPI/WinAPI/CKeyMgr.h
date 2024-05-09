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
	TAP,		// 막 눌린 상태
	PRESSED,	// 계속 눌려있는 상태
	RELEASED,	// 막 뗀 상태
	NONE,		// 눌려있지 않은 상태
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

