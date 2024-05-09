#include "pch.h"
#include "CCollisionMgr.h"

#include "CCollider.h"

CCollisionMgr::CCollisionMgr()
	: m_Matrix{}
{
}

CCollisionMgr::~CCollisionMgr()
{

}


void CCollisionMgr::Init()
{
}

void CCollisionMgr::Tick()
{
	for (UINT Row = 0; Row < (int)LAYER_TYPE::END; ++Row)
	{
		for (UINT Col = Row; Col < (int)LAYER_TYPE::END; ++Col)
		{
			if (m_Matrix[Row] & (1 << Col))
			{
				CollisionLayer(Row, Col);
			}
		}
	}

	// ��ϵ� �浹ü���� ���� �����Ѵ�.
	for (int i = 0; i < (int)LAYER_TYPE::END; ++i)
	{
		m_vecCollider[i].clear();
	}
}

void CCollisionMgr::CollisionCheck(UINT _Layer1, UINT _Layer2, bool _Check)
{
	// ��Ʈ������ ��� �κ��� �������ؼ�, Row �� �� ���� ���� ����Ѵ�.
	UINT Row = _Layer1;
	UINT Col = _Layer2;

	if (_Layer2 < _Layer1)
	{
		Row = _Layer2;
		Col = _Layer1;
	}

	if (_Check)
	{
		m_Matrix[Row] |= (1 << Col);
	}
	else
	{
		m_Matrix[Row] &= ~(1 << Col);
	}
}



void CCollisionMgr::CollisionLayer(int Left, int Right)
{
	vector<CCollider*>& vecLeft = m_vecCollider[Left];
	vector<CCollider*>& vecRight = m_vecCollider[Right];

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			COLLIDER_ID id = {};
			id.LeftID = vecLeft[i]->GetID();
			id.RightID = vecRight[j]->GetID();

			map<DWORD_PTR, bool>::iterator iter = m_ColInfo.find(id.ID);

			// ������ ���� ==> ���ʵ��
			if (iter == m_ColInfo.end())
			{
				m_ColInfo.insert(make_pair(id.ID, false));
				iter = m_ColInfo.find(id.ID);
			}
			
			// �浹ü�� ���� �浹 ���̴�.
			if (Collision(vecLeft[i], vecRight[j]))
			{
				if (iter->second)
				{
					vecLeft[i]->Overlap(vecRight[j]);
					vecRight[j]->Overlap(vecLeft[i]);
				}
				else
				{
					vecLeft[i]->BeginOverlap(vecRight[j]);
					vecRight[j]->BeginOverlap(vecLeft[i]);
					iter->second = true;
				}
			}

			// ���� �浹���� �ƴϴ�.
			else
			{
				// �������� �浹�ߴ�.
				if (iter->second)
				{
					vecLeft[i]->EndOverlap(vecRight[j]);
					vecRight[j]->EndOverlap(vecLeft[i]);
					iter->second = false;
				}
			}
		}
	}
}

bool CCollisionMgr::Collision(CCollider* _Left, CCollider* _Right)
{
	Vec2 vDiff = _Left->GetFinalPos() - _Right->GetFinalPos();

	// �� �浹ü�� �� �ະ �Ÿ���
	vDiff.x = abs(vDiff.x);
	vDiff.y = abs(vDiff.y);

	// �� �浹ü�� ũ�⸦ ���ݾ� ��ģ ��
	float ScaleX = _Left->GetScale().x / 2.f + _Right->GetScale().x / 2.f;
	float ScaleY = _Left->GetScale().y / 2.f + _Right->GetScale().y / 2.f;

	if (vDiff.x <= ScaleX && vDiff.y <= ScaleY)
	{
		return true;
	}

	return false;
}
