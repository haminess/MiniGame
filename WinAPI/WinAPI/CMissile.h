#pragma once
#include "CObj.h"

class CMissile :
    public CObj
{
private:
    Vec2    m_Velocity;

public:
    void SetVelocity(Vec2 _vDir)
    {
        float speed = m_Velocity.Length();
        m_Velocity = _vDir;
        m_Velocity.Normalize();
        m_Velocity *= speed;
    }
    void SetVelocity(Vec2 _vDir, float _Speed)
    {
        m_Velocity = _vDir;
        m_Velocity.Normalize();
        m_Velocity *= _Speed;
    }

    Vec2 GetVelocity() { return m_Velocity; }


public:
    virtual void Tick() override;
    virtual void Render() override;

    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider);

public:
    CMissile();
    ~CMissile();
};

