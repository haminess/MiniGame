#pragma once
#include "CMonster.h"
class CBlock :
    public CMonster
{
private:
    BRUSH_TYPE m_Brush;
    COLORREF m_Color;

    bool m_Delete;

public:
    void SetColor(BRUSH_TYPE _brush) { m_Brush = _brush; }
    void SetDelete(bool _bool) { m_Delete = _bool; }
    CBlock();
    ~CBlock();

public:
    void Init();
    virtual void Tick() override;
    virtual void Render() override;

    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider);
};

