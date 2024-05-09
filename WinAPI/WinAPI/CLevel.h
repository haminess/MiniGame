#pragma once
#include "CBase.h"

class CObj;

class CLevel :
    public CBase
{
private:    
    vector<CObj*>   m_arrLayer[(int)LAYER_TYPE::END];

public:
    void AddObject(CObj* _Obj, LAYER_TYPE _Type);
    const vector<CObj*>& GetLayer(LAYER_TYPE _Type) { return m_arrLayer[(int)_Type]; }

public:
    void Tick();
    void FinalTick();
    void Render();

public:
    CLevel();
    virtual ~CLevel();

    friend class CTaskMgr;
};

