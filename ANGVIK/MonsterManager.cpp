#include "MonsterManager.h"
#include "Player.h"
#include "Kong.h"
#include "Monkey.h"
#include "Ent.h"
#include "Subject.h"
#include "CollisionManager.h"

// 몬스터 스폰위치는 정해져있는 좌표 안에서 랜덤으로 구현예정 
//  

HRESULT MonsterManager::Init(Player* target)
{
	this->target = target;
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
	kongMaxCount = RANDOM(1, kongMaxCount);
	vecKongs.resize(kongMaxCount);
	float spawnPosX[] = { 350.0f, 500.0f, 850.0f };
	float spawnPosY[] = { 360.0f, 275.0f, 382.0f };

	for (int i = 0; i < vecKongs.size(); ++i)
	{
		vecKongs[i] = new Kong;
		vecKongs[i]->Init(target, { spawnPosX[i],spawnPosY[i] });
		vecKongs[i]->GetSubject()->AddObserver(this);
	}
}

void MonsterManager::MonkeySpawn()
{
	MonkeyMaxCount = RANDOM(1, MonkeyMaxCount);
	vecMonkeys.resize(MonkeyMaxCount);

	float spawnPosX[] = { 350.0f, 500.0f, 850.0f };
	float spawnPosY[] = { 360.0f, 275.0f, 382.0f };

	for (int i = 0; i < vecMonkeys.size(); ++i)
	{
		vecMonkeys[i] = new Monkey;
		vecMonkeys[i]->Init(target, { spawnPosX[i],spawnPosY[i] });
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
		vecEnts[i]->Init(target, { spawnPosX[i],spawnPosY[i] });
		vecEnts[i]->GetSubject()->AddObserver(this);
	}
}

bool MonsterManager::CheckCollision(RECT shape, bool &toStepOn)
{
	RECT tempRect = {};

	for (int i = 0; i < vecKongs.size(); ++i)
	{
		if (false == kongWindow[i] || false == vecKongs[i]->GetIsAlive())
		{
			continue;
		}

		if (IntersectRect(&tempRect, &shape, vecKongs[i]->GetShapeAddress()))
		{
			if (tempRect.left >= vecKongs[i]->GetShapeAddress()->left &&
				tempRect.right <= vecKongs[i]->GetShapeAddress()->right &&
				(((vecKongs[i]->GetShapeAddress()->top + vecKongs[i]->GetShapeAddress()->bottom) / 2) + vecKongs[i]->GetShapeAddress()->top) /2 > tempRect.bottom)
			{
				toStepOn = true;
				//vecKongs[i]->SetIsAlive(false);
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
		if (IntersectRect(&tempRect, &shape, vecMonkeys[i]->GetShapeAddress()))
		{
			if (tempRect.left >= vecMonkeys[i]->GetShapeAddress()->left &&
				tempRect.right <= vecMonkeys[i]->GetShapeAddress()->right &&
				(((vecMonkeys[i]->GetShapeAddress()->top + vecMonkeys[i]->GetShapeAddress()->bottom) / 2) + vecMonkeys[i]->GetShapeAddress()->top) / 2 > tempRect.bottom)
			{
				toStepOn = true;
				//vecMonkeys[i]->SetIsAlive(false);
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
		if (IntersectRect(&tempRect, &shape, vecEnts[i]->GetShapeAddress()))
		{
			if (tempRect.left >= vecEnts[i]->GetShapeAddress()->left &&
				tempRect.right <= vecEnts[i]->GetShapeAddress()->right &&
				(((vecEnts[i]->GetShapeAddress()->top + vecEnts[i]->GetShapeAddress()->bottom) / 2) + vecEnts[i]->GetShapeAddress()->top) / 2 > tempRect.bottom)
			{
				toStepOn = true;
				//vecEnts[i]->SetIsAlive(false);
			}
			return true;
		}
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
						cout << "콩 in :  " << i << "\n";
						break;
					}
					if (i == vecKongs.size() - 1)
						cout << "콩를 못찾았다." << "\n";
				}
				break;
			case EventTag::OUTWINDOW:
				for (int i = 0; i < vecKongs.size(); ++i)
				{
					if (vecKongs[i]->GetSubject() == subject)
					{
						kongWindow[i] = false;
						cout << "콩 out: " << i << "\n";
						break;
					}
					if (i == vecKongs.size() - 1)
						cout << "콩를 못찾았다." << "\n";
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
						cout << "몽키 in: " << i << "\n";
						break;
					}
					if (i == vecMonkeys.size() - 1)
						cout << "몽키를 못찾았다." << "\n";
				}
				break;
			case EventTag::OUTWINDOW:
				for (int i = 0; i < vecMonkeys.size(); ++i)
				{
					if (vecMonkeys[i]->GetSubject() == subject)
					{
						monkeyWindow[i] = false;
						cout << "몽키 out: " << i << "\n";
						break;
					}
					if (i == vecMonkeys.size() - 1)
						cout << "몽키를 못찾았다." << "\n";
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
						cout << "나무 in : " << i << "\n";
						break;
					}
					if (i == vecEnts.size() - 1)
						cout << "나무를 못찾았다." << "\n";
				}
				break;
			case EventTag::OUTWINDOW:
				for (int i = 0; i < vecEnts.size(); ++i)
				{
					if (vecEnts[i]->GetSubject() == subject)
					{
						entWindow[i] = false;
						cout << "나무 out: " << i << "\n";
						break;
					}
					if (i == vecEnts.size() - 1)
						cout << "나무를 못찾았다." << "\n";
				}
				break;
			case EventTag::RELEASE:
				break;
			}
			break;
		}
	}
}
/*switch (eventTag)
{
case EventTag::INWINDOW:
	cout << "화면 영역에 들어옴" << "\n";
	for (int i = 0; i < vecKongs.size(); ++i)
	{
		if (vecKongs[i]->GetSubject() == subject)
		{
			kongWindow[i] = true;
		}
		else
		{
			cout << "객체를 못찾았다." << "\n";
		}

	}
	break;
case EventTag::OUTWINDOW:
	cout << "화면 영역 밖으로 나감" << "\n";
	for (int i = 0; i < vecKongs.size(); ++i)
	{
		if (vecKongs[i]->GetSubject() == subject)
		{
			kongWindow[i] = false;
		}
		else
		{
			cout << "객체를 못찾았다." << "\n";
		}

	}
	break;
case EventTag::RELEASE:
	for (int i = 0; i < vecKongs.size(); ++i)
	{

		if (vecKongs[i]->GetSubject() == subject)
		{
			cout << "객체를 특정했다" << "\n";
			cout << " index : " << i << "\n";
			kongWindow[i] = true;
		}
		else
		{
			cout << "객체를 못찾았다." << "\n";
		}

	}
	cout << "화면 밖으로 나감 " << "\n";
	break;
}
break;
}*/


