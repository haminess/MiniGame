#pragma once

class CTexture;

class CAssetMgr
{
	SINGLE(CAssetMgr);
private:
	map<wstring, CTexture*>		m_mapTex;


public:
	void Init();

public:
	CTexture* LoadTexture(const wstring& _strKey, const wstring& _RelativePath);
	CTexture* FindTexture(const wstring& _strKey);
};

