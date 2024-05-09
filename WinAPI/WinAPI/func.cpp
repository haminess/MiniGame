#include "pch.h"
#include "func.h"

#include "CTaskMgr.h"
#include "CObj.h"

void CreateObject(CObj* _Object, LAYER_TYPE _LayerType)
{
	tTask task = { TASK_TYPE::CREATE_OBJECT, (DWORD_PTR)_Object, (DWORD_PTR)_LayerType };

	task.TaskType = TASK_TYPE::CREATE_OBJECT;
	task.Param_0 = (DWORD_PTR)_Object;
	task.Param_1 = (DWORD_PTR)_LayerType;

	CTaskMgr::Get()->AddTask(task);
}

void DeleteObject(CObj* _Object)
{
	tTask task = {};
	task.TaskType = TASK_TYPE::DELETE_OBJECT;
	task.Param_0 = (DWORD_PTR)_Object;

	CTaskMgr::Get()->AddTask(task);
}

#include "CDebugMgr.h"

void DrawDebugShape(DEBUG_SHAPE _Shape, PEN_TYPE _Pen, BRUSH_TYPE _Brush
			      , Vec2 _vPos, Vec2 _vScale, float _Duration)
{
	tDebugShapeInfo info = {};

	info.Shape = _Shape;	
	info.Pen = _Pen;
	info.BRUSH = _Brush;
	info.Position = _vPos;
	info.Scale = _vScale;	
	info.Duration = _Duration;

	CDebugMgr::Get()->AddDebugShapeInfo(info);
}
