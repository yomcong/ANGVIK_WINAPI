//#include "stdafx.h"
#include "TrapManager.h"
#include "Trap.h"
#include "Platform.h"

HRESULT TrapManager::Init()
{
	TrapSpawn();
	PlatformSpawn();

	return S_OK;
}

void TrapManager::Update()
{
	for (int i = 0; i < vecTraps.size(); ++i)
	{
		vecTraps[i]->Update();
	}
	for (int i = 0; i < vecPlatforms.size(); ++i)
	{
		vecPlatforms[i]->Update();
	}
}

void TrapManager::Render(HDC hdc)
{
	for (int i = 0; i < vecTraps.size(); ++i)
	{
		vecTraps[i]->Render(hdc);
	}
	for (int i = 0; i < vecPlatforms.size(); ++i)
	{
		vecPlatforms[i]->Render(hdc);
	}
}

void TrapManager::Release()
{
	for (int i = 0; i < vecTraps.size(); ++i)
	{
		SAFE_RELEASE(vecTraps[i]);
	}
	//vecTraps.clear();
	for (int i = 0; i < vecPlatforms.size(); ++i)
	{
		SAFE_RELEASE(vecPlatforms[i]);
	}
	vecPlatforms.clear();
}

void TrapManager::TrapSpawn()
{
	vecTraps.resize(TrapMaxCount);

	float spawnPosX[] = { 990.0f, 1593.0f, 2260.0f, 2282.0f, 2378.0f, 2412.0f, 2755.0f, 3240.0f, 3412.0f , 3915.0f, 4690.0f , 5202.0f, 5230.0f, 5320.0f, 5940.0f};
	float spawnPosY[] = { 445.0f, 714.0f , 444.0f, 462.0f, 512.0f, 530.0f, 787.0f, 752.0f, 750.0f,343.0f,   895.0f, 808.0f, 800.0f, 750.0f, 380.0f};

	int bodySizeX[] = { 30,80, 24, 24, 30, 31, 110, 55, 155,70,  40, 30, 45, 30, 100};
	int bodySizeY[] = { 30,30, 46, 26, 30, 30, 40, 40, 40, 30,  30, 30, 30, 30, 30};

	for (int i = 0; i < TrapMaxCount; ++i)
	{
		vecTraps[i] = new Trap;
		vecTraps[i]->Init({ spawnPosX[i],spawnPosY[i] }, { bodySizeX[i], bodySizeY[i] });
		vecTraps[i]->AddObserver(this);
	}
}

void TrapManager::PlatformSpawn()
{
	vecPlatforms.resize(PlatformMaxCount);

	float spawnPosX[] = { 2628.0f, 2860.0f, 2861.0f, 3465.0f, 3465.0f, 3352.0f, 3354.0f,  2736.0f,  2740.0f, 2740.0f };
	float spawnPosY[] = { 441.0f , 485.0f , 602.0f , 382.0f , 561.0f , 477.0f , 645.0f , 417.0f , 530.0f , 643.0f };

	for (int i = 0; i < PlatformMaxCount; ++i)
	{
		int dir = i < PlatformMaxCount / 2;
		vecPlatforms[i] = new Platform;
		vecPlatforms[i]->Init({ spawnPosX[i],spawnPosY[i] }, dir);
		vecPlatforms[i]->AddObserver(this);
	}
}

bool TrapManager::CheckCollision(RECT rect, bool& b_temp)
{
	for (int i = 0; i < vecTraps.size(); ++i)
	{
		if (trapInWindow[i] == false)
		{
			continue;
		}
		// 렉트충돌비교가 아니라 따로 해야함
		RECT temprect = {};
		if (IntersectRect(&temprect, vecTraps[i]->GetShapeAddress(), &rect))
		{
			return true;
		}
	}

	for (int i = 0; i < vecPlatforms.size(); ++i)
	{
		// 충돌 최적화 해보기
		if (false == vecPlatforms[i]->GetIsAlive() || platformInWindow[i] == false)
		{
			continue;
		}

		// 렉트충돌비교가 아니라 따로 해야함
		RECT tempRect = {};
		if (IntersectRect(&tempRect, vecPlatforms[i]->GetShapeAddress(), &rect))
		{
			if (tempRect.left >= vecPlatforms[i]->GetShapeAddress()->left &&
				tempRect.right <= vecPlatforms[i]->GetShapeAddress()->right &&
				(((vecPlatforms[i]->GetShapeAddress()->top + vecPlatforms[i]->GetShapeAddress()->bottom) / 2) + vecPlatforms[i]->GetShapeAddress()->top) / 2 > tempRect.bottom)
			{
				vecPlatforms[i]->SetIsCollision(true);
				b_temp = true;
				return true;
			}
		}
	}
	return false;
}

void TrapManager::OnNotify(Subject* _subject, MonsterType _monsterType, SubjectTag _subjectTag, EventTag _eventTag)
{
	switch (_subjectTag)
	{
	case SubjectTag::TRAP:
		switch (_eventTag)
		{
		case EventTag::INWINDOW:
			for (int i = 0; i < vecTraps.size(); ++i)
			{
				if (vecTraps[i]->GetSubject() == _subject)
				{
					trapInWindow[i] = true;
					break;
				}
			}
			break;
		case EventTag::OUTWINDOW:
			for (int i = 0; i < vecTraps.size(); ++i)
			{
				if (vecTraps[i]->GetSubject() == _subject)
				{
					trapInWindow[i] = false;
					break;
				}
			}
			break;
		}
		break;
	case SubjectTag::PLATFORM:
		switch (_eventTag)
		{
		case EventTag::INWINDOW:
			for (int i = 0; i < vecPlatforms.size(); ++i)
			{
				if (vecPlatforms[i]->GetSubject() == _subject)
				{
					platformInWindow[i] = true;
					break;
				}
			}
			break;
		case EventTag::OUTWINDOW:
			for (int i = 0; i < vecPlatforms.size(); ++i)
			{
				if (vecPlatforms[i]->GetSubject() == _subject)
				{
					platformInWindow[i] = false;
					break;
				}
			}
			break;
		}
		break;

	}
}
