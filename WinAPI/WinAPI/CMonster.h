#pragma once
#include "CObj.h"

class CCollider;

class CMonster :
    public CObj
{
private:
    CCollider* m_Collider;

public:
    CCollider* GetCollider() { return m_Collider; }


public:
    virtual void Tick() override;
    virtual void Render() override;

    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider);

public:
    CMonster();
    ~CMonster();
};

