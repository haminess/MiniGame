#pragma once
#include "CBase.h"

class CAsset :
    public CBase
{
private:
    wstring     m_Key;
    wstring     m_RelativePath;

public:
    const wstring& GetKey() { return m_Key; }
    const wstring& GetRelativePath() { return m_RelativePath; }

private:    
    virtual int Load(const wstring& _strFilePath) = 0;

public:
    CAsset();
    ~CAsset();

    friend class CAssetMgr;
};

