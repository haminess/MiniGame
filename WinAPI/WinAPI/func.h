#pragma once

class CObj;

void CreateObject(CObj* _Object, LAYER_TYPE _LayerType);

void DeleteObject(CObj* _Object);

void DrawDebugShape(DEBUG_SHAPE _Shape, PEN_TYPE _Pen, BRUSH_TYPE _Brush, Vec2 _vPos, Vec2 _vScale, float _Duration = 0.f);

template<typename T>
bool IsValid(T*& _Object)
{
	if (nullptr == _Object)
		return false;

	if (_Object->IsDead())
	{
		_Object = nullptr;
		return false;
	}

	return true;	
}


template<typename T>
void Release_Vector(vector<T*>& _vec)
{
	for (size_t i = 0; i < _vec.size(); ++i)
	{
		if (i == 75)
		{
			int a = 0;
		}
		if (nullptr == _vec[i])
			continue;

		delete _vec[i];		
	}

	_vec.clear();
}

template<typename T1, typename T2>
void Release_Map(map<T1, T2>& _map)
{
	typename map<T1, T2>::iterator iter = _map.begin();

	for (; iter != _map.end(); ++iter)
	{
		if (nullptr == iter->second)
			continue;

		delete iter->second;
	}

	_map.clear();
}