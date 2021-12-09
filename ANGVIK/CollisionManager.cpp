#include "CollisionManager.h"

HRESULT CollisionManager::Init(CollisionManager* target, POINTFLOAT pos)
{


	return S_OK;
}

void CollisionManager::Update()
{
}

void CollisionManager::Render(HDC hdc)
{
}

void CollisionManager::Release()
{
}

void CollisionManager::AddObject(SubjectTag subject, EventTag object, RECT* shape)
{
	vector<RECT*>::iterator iter = find(vecRects.begin(), vecRects.end(), shape);

	if (iter == vecRects.end())
	{
		vecRects.push_back(shape);
	}

	
	
}

void CollisionManager::CheckCollision(SubjectTag subject, EventTag object, RECT shape)
{

}
