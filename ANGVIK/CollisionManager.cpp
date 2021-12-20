#include "CollisionManager.h"
#include "Player.h"
#include "MonsterManager.h"
#include "TrapManager.h"
#include "ItemManager.h"

HRESULT CollisionManager::Init()
{
	return S_OK;
}

void CollisionManager::AddPlayer(Player* player)
{
	this->player = player;
}

void CollisionManager::AddMonsterManager(MonsterManager* monsterManager)
{
	this->monsterManager = monsterManager;
}

void CollisionManager::AddTrapManager(TrapManager* trapManager)
{
	this->trapManager = trapManager;
}

void CollisionManager::AddItem(ItemManager* itemManager)
{
	this->itemManager = itemManager;
}

void CollisionManager::AddObject(SubjectTag subject, EventTag object, RECT* shape)
{
	vector<RECT*>::iterator iter = find(vecRects.begin(), vecRects.end(), shape);

	if (iter == vecRects.end())
	{
		vecRects.push_back(shape);
	}
}

bool CollisionManager::CheckCollision(SubjectTag subject, RECT shape, EventTag eventTag)
{
	bool b_temp = false;
	switch (subject)
	{
	case SubjectTag::IDLE:
		break;
	case SubjectTag::PLAYER:
	{
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
		if (trapManager->CheckCollision(shape, b_temp))
		{
			if (b_temp)
			{
				player->SetIsPlatform(true);
			}
			else
			{
				player->ToBeHit();
			}
		}
		else
		{
			player->SetIsPlatform(false);
		}
		break;
	}
	case SubjectTag::MONSTER:
		player->CheckCollision(subject, shape);

		if (trapManager->CheckCollision(shape, b_temp))
		{
			//return true;
		}
		break;
	case SubjectTag::ITEM:
		break;
	case SubjectTag::TRAP:
		break;
	case SubjectTag::PLATFORM:
		if (player->CheckCollision(subject, shape))
		{
			return true;
		}
	
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

void CollisionManager::CheckItem(RECT shape)
{
	ItemType tempType;
	ItemGrade tempGrade;
	WeaponType tempWeapon;
	if (itemManager->CheckCollision(shape, tempType, tempGrade, tempWeapon))
	{
		player->EquipItem(tempType, tempGrade, tempWeapon);
	}
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
