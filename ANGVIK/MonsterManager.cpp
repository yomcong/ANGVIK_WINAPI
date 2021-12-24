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
	for (int i = 0; i < vecKongs.size(); ++i)
	{
		vecKongs[i]->Update();
	}

	for (int i = 0; i < vecMonkeys.size(); ++i)
	{

		vecMonkeys[i]->Update();
	}

	for (int i = 0; i < vecEnts.size(); ++i)
	{
		vecEnts[i]->Update();
	}

}

void MonsterManager::Render(HDC hdc)
{
	// 각 객체수 만큼 불타입 배열을 선언.
	// 윈도우 영역에 들어온 객체들은 true , 밖에있으면 false;
	// 포문을 돌때 false인 객체는 continue;

	for (int i = 0; i < vecKongs.size(); ++i)
	{
		if (false == kongWindow[i])
		{
			continue;
		}
		vecKongs[i]->Render(hdc);
	}
	for (int i = 0; i < vecMonkeys.size(); ++i)
	{
		if (false == monkeyWindow[i])
		{
			continue;
		}
		vecMonkeys[i]->Render(hdc);
	}
	for (int i = 0; i < vecEnts.size(); ++i)
	{
		if (false == entWindow[i])
		{
			continue;
		}
		vecEnts[i]->Render(hdc);
	}

}

void MonsterManager::Release()
{
	for (int i = 0; i < vecKongs.size(); ++i)
	{
		SAFE_RELEASE(vecKongs[i]);
	}
	vecKongs.clear();

	for (int i = 0; i < vecMonkeys.size(); ++i)
	{
		SAFE_RELEASE(vecMonkeys[i]);
	}
	vecMonkeys.clear();

	for (int i = 0; i < vecEnts.size(); ++i)
	{
		SAFE_RELEASE(vecEnts[i]);
	}
	vecEnts.clear();
}

void MonsterManager::KongSpawn()
{
	//kongMaxCount = RANDOM(1, kongMaxCount);
	vecKongs.resize(kongMaxCount);
	float spawnPosX[] = { 880.0f, 1475.0f, 1910.0f, 2500.0f };
	float spawnPosY[] = { 385.0, 265.0f, 388.0f, 508.0f };

	for (int i = 0; i < vecKongs.size(); ++i)
	{
		vecKongs[i] = new Kong;
		vecKongs[i]->Init({ spawnPosX[i],spawnPosY[i] }, ammoManager);
		vecKongs[i]->GetSubject()->AddObserver(this);
	}
}

void MonsterManager::MonkeySpawn()
{
	//MonkeyMaxCount = RANDOM(1, MonkeyMaxCount);
	vecMonkeys.resize(MonkeyMaxCount);

	// 5,6번째 옵저버 활용해서 트리거로 이닛해주기
	float spawnPosX[] = { 500.0f, 850.0f, 1100.0f, 1400.0f, 2200.0f, 2300.0f };
	float spawnPosY[] = { 350.0f, 382.0f, 390.0f, 390.0f, 300.0f, 300.0f };

	for (int i = 0; i < vecMonkeys.size(); ++i)
	{
		vecMonkeys[i] = new Monkey;
		vecMonkeys[i]->Init({ spawnPosX[i],spawnPosY[i] });
		vecMonkeys[i]->GetSubject()->AddObserver(this);
	}
}


void MonsterManager::EntSpawn()
{
	//EntMaxCount = RANDOM(1, EntMaxCount);
	vecEnts.resize(EntMaxCount);

	float spawnPosX[] = { 380.0f, 550.0f, 900.0f };
	float spawnPosY[] = { 340.0f, 250.0f, 360.0f };

	for (int i = 0; i < vecEnts.size(); ++i)
	{
		vecEnts[i] = new Ent;
		vecEnts[i]->Init({ spawnPosX[i],spawnPosY[i] }, ammoManager);
		vecEnts[i]->GetSubject()->AddObserver(this);
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
			if (false == kongWindow[i] || false == vecKongs[i]->GetIsAlive())
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
			if (false == monkeyWindow[i] || false == vecMonkeys[i]->GetIsAlive())
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
			if (false == entWindow[i] || false == vecEnts[i]->GetIsAlive())
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
			if (false == kongWindow[i] || false == vecKongs[i]->GetIsAlive())
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
			if (false == monkeyWindow[i] || false == vecMonkeys[i]->GetIsAlive())
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
			if (false == entWindow[i] || false == vecEnts[i]->GetIsAlive())
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

void MonsterManager::OnNotify(Subject* subject, MonsterType monsterType, SubjectTag subjectTag, EventTag eventTag)
{
	switch (subjectTag)
	{
	case SubjectTag::MONSTER:
		switch (monsterType)
		{
		case MonsterType::KONG:
			switch (eventTag)
			{
			case EventTag::INWINDOW:
				for (int i = 0; i < vecKongs.size(); ++i)
				{
					if (vecKongs[i]->GetSubject() == subject)
					{
						kongWindow[i] = true;
						//cout << i << " 몽키 인 " << "\n";
						break;
					}
					if (i == vecKongs.size() - 1)
					{

					}
					//cout << "콩를 못찾았다." << "\n";
				}
				break;
			case EventTag::OUTWINDOW:
				for (int i = 0; i < vecKongs.size(); ++i)
				{
					if (vecKongs[i]->GetSubject() == subject)
					{
						kongWindow[i] = false;
						//cout << i << " 몽키 아웃 " << "\n";
						break;
					}
					if (i == vecKongs.size() - 1)
					{

					}
					//cout << "콩를 못찾았다." << "\n";
				}
				break;
			case EventTag::RELEASE:
				break;
			}
			break;
		case MonsterType::MONKEY:
			switch (eventTag)
			{
			case EventTag::INWINDOW:
				for (int i = 0; i < vecMonkeys.size(); ++i)
				{
					if (vecMonkeys[i]->GetSubject() == subject)
					{
						monkeyWindow[i] = true;
						//cout << i << " 몽키 인 " << "\n";
						break;
					}
					if (i == vecMonkeys.size() - 1)
					{

					}
					//cout << "몽키를 못찾았다." << "\n";
				}
				break;
			case EventTag::OUTWINDOW:
				for (int i = 0; i < vecMonkeys.size(); ++i)
				{
					if (vecMonkeys[i]->GetSubject() == subject)
					{
						monkeyWindow[i] = false;
						//cout << i << " 몽키 아웃 " << "\n";
						break;
					}
					if (i == vecMonkeys.size() - 1)
					{

					}
					//cout << "몽키를 못찾았다." << "\n";
				}
				break;
			case EventTag::RELEASE:
				break;
			}
			break;
		case MonsterType::ENT:
			switch (eventTag)
			{
			case EventTag::INWINDOW:
				for (int i = 0; i < vecEnts.size(); ++i)
				{
					if (vecEnts[i]->GetSubject() == subject)
					{
						entWindow[i] = true;
						//cout << i << " 나무 인 " << "\n";
						break;
					}
					if (i == vecEnts.size() - 1)
					{

					}
					//cout << "나무를 못찾았다." << "\n";
				}
				break;
			case EventTag::OUTWINDOW:
				for (int i = 0; i < vecEnts.size(); ++i)
				{
					if (vecEnts[i]->GetSubject() == subject)
					{
						entWindow[i] = false;
						//cout <<i << " 나무 아웃 " << "\n";
						break;
					}
					if (i == vecEnts.size() - 1)
					{

					}
					//cout << "나무를 못찾았다." << "\n";
				}
				break;
			case EventTag::RELEASE:
				break;
			}
			break;
		}
	}
}
