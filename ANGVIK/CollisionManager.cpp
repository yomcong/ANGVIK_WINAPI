#include "CollisionManager.h"
#include "Player.h"
#include "MonsterManager.h"
#include "TrapManager.h"

HRESULT CollisionManager::Init(Player* player, MonsterManager* monsterManager, TrapManager* trapManager)
{
	this->player = player;
	this->monsterManager = monsterManager;
	this->trapManager = trapManager;

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

SubjectTag CollisionManager::testCheck(SubjectTag subjectTag, RECT shape)
{
	switch (subjectTag)
	{
	case SubjectTag::PLAYER:
		if (monsterManager->CheckCollision(shape))
		{
			return SubjectTag::MONSTER;
		}
		if (trapManager->CheckCollision(shape))
		{
			return SubjectTag::TRAP;
		}
		break;
	case SubjectTag::MONSTER:
		break;
	default:
		break;
	}
	
	return SubjectTag::IDLE;
}
