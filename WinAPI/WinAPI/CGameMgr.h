#pragma once
class CGameMgr
{
	SINGLE(CGameMgr);

private:
	int m_Score;

public:
	int GetScore() { return m_Score; }
	void SetScore(int _score) { m_Score = _score; }
	void AddScore(int _addValue) { m_Score += _addValue; }

public:
	void Init();
	void Tick();
};

