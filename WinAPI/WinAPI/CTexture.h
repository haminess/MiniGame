#pragma once
#include "CAsset.h"


class CTexture :
    public CAsset
{
private:
    HBITMAP     m_hBitmap;
    HDC         m_hDC;
    BITMAP      m_BitInfo;


public:
    UINT GetWidth() { return m_BitInfo.bmWidth; }
    UINT GetHeight() { return m_BitInfo.bmHeight; }
    HDC GetDC() { return m_hDC; }

private:
    virtual int Load(const wstring& _FilePath) override;

public:
    CTexture();
    ~CTexture();

    friend class CAssetMgr;
};

