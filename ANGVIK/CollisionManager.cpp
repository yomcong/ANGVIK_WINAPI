#include "CollisionManager.h"
#include "Player.h"
#include "MonsterManager.h"
#include "TrapManager.h"

HRESULT CollisionManager::Init()
{

	return S_OK;
}

void CollisionManager::AddPlayer(Player* player)
{
	this->player = player;
}

void CollisionManager::AddMonster(MonsterManager* monsterManager)
{
	this->monsterManager = monsterManager;
}

void CollisionManager::AddTrap(TrapManager* trapManager)
{
	this->trapManager = trapManager;
}

void CollisionManager::AddObject(SubjectTag subject, EventTag object, RECT* shape)
{
	vector<RECT*>::iterator iter = find(vecRects.begin(), vecRects.end(), shape);

	if (iter == vecRects.end())
	{
		vecRects.push_back(shape);
	}
}

bool CollisionManager::CheckCollision(SubjectTag subject,RECT shape, EventTag eventTag)
{
	switch (subject)
	{
	case SubjectTag::IDLE:
		break;
	case SubjectTag::PLAYER:
	{
		bool b_temp = false;
		if (monsterManager->CheckCollision(shape, b_temp))
		{
			if (b_temp)
			{
				player->ToStepOn();
			}
			else
			{
				player->ToBeHit();
			}

		}
		if (trapManager->CheckCollision(shape))
		{
			player->ToStepOn();
		}
		break;
	}
	case SubjectTag::MONSTER:
		break;
	case SubjectTag::ITEM:
		break;
	case SubjectTag::TRAP:
		break;
	case SubjectTag::PLATFORM:
		break;
	case SubjectTag::Ammo:
		if (player->CheckCollision(subject, shape))
		{
			return true;
		}
		break;
	}
	return false;
}

SubjectTag CollisionManager::testCheck(SubjectTag subjectTag, RECT shape)
{
	switch (subjectTag)
	{
	case SubjectTag::PLAYER:
		/*if (monsterManager->CheckCollision(shape))
		{
			return SubjectTag::MONSTER;
		}
		if (trapManager->CheckCollision(shape))
		{
			return SubjectTag::TRAP;
		}*/
		break;
	case SubjectTag::MONSTER:
		break;
	default:
		break;
	}
	
	return SubjectTag::IDLE;
}
