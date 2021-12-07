#pragma once
#include "Config.h"
#include "GameEntity.h"


class CollisionManager : public GameEntity
{
public:
	virtual ~CollisionManager() = default;

	virtual HRESULT Init(CollisionManager* target, POINTFLOAT pos);
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	void AddObject(SubjectTag iff, EventTag object, RECT* shape);
	void CheckCollision(SubjectTag iff, EventTag object, RECT shape);
						
private:
	vector<RECT*> vecRects = {};

};

