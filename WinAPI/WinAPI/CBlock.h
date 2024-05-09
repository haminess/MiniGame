#pragma once
#include "CMonster.h"
class CBlock :
    public CMonster
{
private:
    BRUSH_TYPE m_Brush;
    COLORREF m_Color;

public:
    void SetColor(BRUSH_TYPE _brush) { m_Brush = _brush; }
    CBlock();
    ~CBlock();

public:
    void Init();
    virtual void Tick() override;
    virtual void Render() override;

    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider);
};

