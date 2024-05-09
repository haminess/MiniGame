#pragma once
#include "CMissile.h"

class CMonster;

class CGuidedMissile :
    public CMissile
{
private:
    CMonster*   m_TargetObj;
    float       m_DetectRange;  

public:
    virtual void Tick() override;

private:
    void FindTarget();

public:
    CGuidedMissile();
    ~CGuidedMissile();
};

