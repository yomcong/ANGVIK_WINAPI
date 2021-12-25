//#include "stdafx.h"
#include "MonsterManager.h"
#include "Kong.h"
#include "Monkey.h"
#include "Ent.h"
#include "Subject.h"
#include "CollisionManager.h"
#include "AmmoManager.h"

// 몬스터 스폰위치는 정해져있는 좌표 안에서 랜덤으로 구현예정 
//  

HRESULT MonsterManager::Init(AmmoManager* _ammoManager)
{
	ammoManager = _ammoManager;

	KongSpawn();
	MonkeySpawn();
	EntSpawn();

	return S_OK;
}

void MonsterManager::Update()
{
	for (int i = 0; i < currKongSpawn; ++i)
	{
		if (vecKongs[i]->GetIsAlive() == false)
		{
			continue;
		}
		vecKongs[i]->Update();
	}

	for (int i = 0; i < currMonkeySpawn; ++i)
	{
		if (vecMonkeys[i]->GetIsAlive() == false)
		{
			continue;
		}
		vecMonkeys[i]->Update();
	}

	for (int i = 0; i < currEntSpawn; ++i)
	{
		if (vecEnts[i]->GetIsAlive() == false)
		{
			continue;
		}
		vecEnts[i]->Update();
	}

}

void MonsterManager::Render(HDC hdc)
{
	// 각 객체수 만큼 불타입 배열을 선언.
	// 윈도우 영역에 들어온 객체들은 true , 밖에있으면 false;
	// 포문을 돌때 false인 객체는 continue;

	for (int i = 0; i < currKongSpawn; ++i)
	{
		if (false == kongInWindow[i])
		{
			continue;
		}
		vecKongs[i]->Render(hdc);
	}
	for (int i = 0; i < currMonkeySpawn; ++i)
	{
		if (false == monkeyInWindow[i])
		{
			continue;
		}
		vecMonkeys[i]->Render(hdc);
	}
	for (int i = 0; i < currEntSpawn; ++i)
	{
		if (false == entInWindow[i])
		{
			continue;
		}
		vecEnts[i]->Render(hdc);
	}

}

void MonsterManager::Release()
{
	for (int i = 0; i < currKongSpawn; ++i)
	{
		SAFE_RELEASE(vecKongs[i]);
	}
	vecKongs.clear();

	for (int i = 0; i < currMonkeySpawn; ++i)
	{
		SAFE_RELEASE(vecMonkeys[i]);
	}
	vecMonkeys.clear();

	for (int i = 0; i < currEntSpawn; ++i)
	{
		SAFE_RELEASE(vecEnts[i]);
	}
	vecEnts.clear();
}

void MonsterManager::KongSpawn()
{
	//kongMaxCount = RANDOM(1, kongMaxCount);
	vecKongs.resize(kongMaxCount);
	
	for (int i = 0; i < vecKongs.size(); ++i)
	{
		vecKongs[i] = new Kong;
		vecKongs[i]->Init({ spawnKongPosX[i],spawnKongPosY[i] }, ammoManager);
		vecKongs[i]->GetSubject()->AddObserver(this);
		++currKongSpawn;
	}
}

void MonsterManager::MonkeySpawn()
{
	//MonkeyMaxCount = RANDOM(1, MonkeyMaxCount);
	vecMonkeys.resize(monkeyMaxCount);

	for (int i = 0; i < 4; ++i)
	{
		vecMonkeys[i] = new Monkey;
		vecMonkeys[i]->Init({ spawnMonkeyPosX[i],spawnMonkeyPosY[i] });
		vecMonkeys[i]->GetSubject()->AddObserver(this);
		++currMonkeySpawn;
	}
}


void MonsterManager::EntSpawn()
{
	//EntMaxCount = RANDOM(1, EntMaxCount);
	vecEnts.resize(entMaxCount);

	for (int i = 0; i < vecEnts.size(); ++i)
	{
		vecEnts[i] = new Ent;
		vecEnts[i]->Init({ spawnEntPosX[i],spawnEntPosY[i] }, ammoManager);
		vecEnts[i]->GetSubject()->AddObserver(this);
		++currEntSpawn;
	}
}

void MonsterManager::MonkeyTriggerSpawn()
{
	for (int i = currMonkeySpawn; i < vecMonkeys.size(); ++i)
	{
		vecMonkeys[i] = new Monkey;
		vecMonkeys[i]->Init({ spawnMonkeyPosX[i],spawnMonkeyPosY[i] });
		vecMonkeys[i]->GetSubject()->AddObserver(this);
		++currMonkeySpawn;
	}
}

bool MonsterManager::CheckCollision(SubjectTag _subTag, RECT _shape, bool& _toStepOn)
{
	RECT tempRect = {};

	switch (_subTag)
	{
	case SubjectTag::PLAYER:
		for (int i = 0; i < vecKongs.size(); ++i)
		{
			if (false == kongInWindow[i] || false == vecKongs[i]->GetIsAlive())
			{
				continue;
			}

			if (IntersectRect(&tempRect, &_shape, vecKongs[i]->GetShapeAddress()))
			{
				if (tempRect.left >= vecKongs[i]->GetShapeAddress()->left &&
					tempRect.right <= vecKongs[i]->GetShapeAddress()->right &&
					(((vecKongs[i]->GetShapeAddress()->top + vecKongs[i]->GetShapeAddress()->bottom) / 2) + vecKongs[i]->GetShapeAddress()->top) / 2 > tempRect.bottom)
				{
					_toStepOn = true;
					vecKongs[i]->ToBeHit();
				}

				return true;
			}
		}
		for (int i = 0; i < vecMonkeys.size(); ++i)
		{
			if (false == monkeyInWindow[i] || false == vecMonkeys[i]->GetIsAlive())
			{
				continue;
			}
			if (IntersectRect(&tempRect, &_shape, vecMonkeys[i]->GetShapeAddress()))
			{
				if (tempRect.left >= vecMonkeys[i]->GetShapeAddress()->left &&
					tempRect.right <= vecMonkeys[i]->GetShapeAddress()->right &&
					(((vecMonkeys[i]->GetShapeAddress()->top + vecMonkeys[i]->GetShapeAddress()->bottom) / 2) + vecMonkeys[i]->GetShapeAddress()->top) / 2 > tempRect.bottom)
				{
					_toStepOn = true;
					vecMonkeys[i]->ToBeHit();
				}

				return true;
			}
		}
		for (int i = 0; i < vecEnts.size(); ++i)
		{
			if (false == entInWindow[i] || false == vecEnts[i]->GetIsAlive())
			{
				continue;
			}
			if (IntersectRect(&tempRect, &_shape, vecEnts[i]->GetShapeAddress()))
			{
				if (tempRect.left >= vecEnts[i]->GetShapeAddress()->left &&
					tempRect.right <= vecEnts[i]->GetShapeAddress()->right &&
					(((vecEnts[i]->GetShapeAddress()->top + vecEnts[i]->GetShapeAddress()->bottom) / 2) + vecEnts[i]->GetShapeAddress()->top) / 2 > tempRect.bottom)
				{
					_toStepOn = true;
					vecEnts[i]->ToBeHit();
				}
				return true;
			}
		}
		break;
	case SubjectTag::AMMO:
		break;
	case SubjectTag::WEAPON:
		for (int i = 0; i < vecKongs.size(); ++i)
		{
			if (false == kongInWindow[i] || false == vecKongs[i]->GetIsAlive())
			{
				continue;
			}

			if (IntersectRect(&tempRect, &_shape, vecKongs[i]->GetShapeAddress()))
			{
				vecKongs[i]->ToBeHit();

				return true;
			}
		}
		for (int i = 0; i < vecMonkeys.size(); ++i)
		{
			if (false == monkeyInWindow[i] || false == vecMonkeys[i]->GetIsAlive())
			{
				continue;
			}
			if (IntersectRect(&tempRect, &_shape, vecMonkeys[i]->GetShapeAddress()))
			{
				vecMonkeys[i]->ToBeHit();

				return true;
			}
		}
		for (int i = 0; i < vecEnts.size(); ++i)
		{
			if (false == entInWindow[i] || false == vecEnts[i]->GetIsAlive())
			{
				continue;
			}
			if (IntersectRect(&tempRect, &_shape, vecEnts[i]->GetShapeAddress()))
			{
				vecEnts[i]->ToBeHit();

				return true;
			}
		}
		break;
	}

	return false;
}

void MonsterManager::OnNotify(Subject* _subject, MonsterType _monsterType, SubjectTag _subjectTag, EventTag _eventTag)
{
	switch (_subjectTag)
	{
	case SubjectTag::MONSTER:
		switch (_monsterType)
		{
		case MonsterType::KONG:
			switch (_eventTag)
			{
			case EventTag::INWINDOW:
				for (int i = 0; i < vecKongs.size(); ++i)
				{
					if (vecKongs[i]->GetSubject() == _subject)
					{
						kongInWindow[i] = true;
						break;
					}
				}
				break;
			case EventTag::OUTWINDOW:
				for (int i = 0; i < vecKongs.size(); ++i)
				{
					if (vecKongs[i]->GetSubject() == _subject)
					{
						kongInWindow[i] = false;
						break;
					}
				}
				break;
			case EventTag::RELEASE:
				break;
			}
			break;
		case MonsterType::MONKEY:
			switch (_eventTag)
			{
			case EventTag::INWINDOW:
				for (int i = 0; i < vecMonkeys.size(); ++i)
				{
					if (vecMonkeys[i]->GetSubject() == _subject)
					{
						monkeyInWindow[i] = true;
						break;
					}
				}
				break;
			case EventTag::OUTWINDOW:
				for (int i = 0; i < vecMonkeys.size(); ++i)
				{
					if (vecMonkeys[i]->GetSubject() == _subject)
					{
						monkeyInWindow[i] = false;
						break;
					}
				}
				break;
			case EventTag::RELEASE:
				break;
			}
			break;
		case MonsterType::ENT:
			switch (_eventTag)
			{
			case EventTag::INWINDOW:
				for (int i = 0; i < vecEnts.size(); ++i)
				{
					if (vecEnts[i]->GetSubject() == _subject)
					{
						entInWindow[i] = true;
						break;
					}
				}
				break;
			case EventTag::OUTWINDOW:
				for (int i = 0; i < vecEnts.size(); ++i)
				{
					if (vecEnts[i]->GetSubject() == _subject)
					{
						entInWindow[i] = false;
						break;
					}
				}
				break;
			case EventTag::RELEASE:
				break;
			}
			break;
		}
	}
}
