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

bool CollisionManager::CheckCollision(SubjectTag _subject, RECT _shape, EventTag _eventTag)
{
	bool b_temp = false;


	switch (_subject)
	{
	case SubjectTag::IDLE:
		break;
	case SubjectTag::PLAYER:
	{
		if (monsterManager->CheckCollision(SubjectTag::PLAYER, _shape, b_temp))
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
		if (trapManager->CheckCollision(_shape, b_temp))
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
		player->CheckCollision(_subject, _shape, _eventTag);
		

		if (trapManager->CheckCollision(_shape, b_temp))
		{
			//return true;
		}
		break;
	case SubjectTag::ITEM:
		break;
	case SubjectTag::TRAP:
		break;
	case SubjectTag::PLATFORM:
		if (player->CheckCollision(_subject, _shape))
		{
			return true;
		}
	
		break;
	case SubjectTag::AMMO:
		if (player->CheckCollision(_subject, _shape))
		{
			return true;
		}
		break;
	case SubjectTag::WEAPON:
		if (monsterManager->CheckCollision(SubjectTag::WEAPON, _shape, b_temp))
		{
			player->AttackHit();
			return true;
		}
		break;
	}
	return false;
}

POINTFLOAT CollisionManager::RangeCheckCollision(SubjectTag _subject, RECT _shape, EventTag _eventTag)
{
	switch (_subject)
	{
	case SubjectTag::PLAYER:
		break;
	case SubjectTag::MONSTER:
		if (player->CheckCollision(_subject, _shape, _eventTag))
		{
			if (_eventTag == EventTag::RANGECOLLISION)
			{
				return player->GetPos();
			}
		}
		break;
	case SubjectTag::WEAPON:
		break;
	}
	return POINTFLOAT({ 0,0 });
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

