#include "MonsterManager.h"
#include "Player.h"
#include "Kong.h"
#include "Monkey.h"
#include "Ent.h"
#include "Subject.h"
#include "CollisionManager.h"

// ���� ������ġ�� �������ִ� ��ǥ �ȿ��� �������� �������� 
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
	// �� ��ü�� ��ŭ ��Ÿ�� �迭�� ����.
	// ������ ������ ���� ��ü���� true , �ۿ������� false;
	// ������ ���� false�� ��ü�� continue;

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
		if (IntersectRect(&tempRect, &shape, vecMonkeys[i]->GetShapeAddress()))
		{
			if (tempRect.left >= vecMonkeys[i]->GetShapeAddress()->left &&
				tempRect.right <= vecMonkeys[i]->GetShapeAddress()->right &&
				(((vecMonkeys[i]->GetShapeAddress()->top + vecMonkeys[i]->GetShapeAddress()->bottom) / 2) + vecMonkeys[i]->GetShapeAddress()->top) / 2 > tempRect.bottom)
			{
				toStepOn = true;
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
		if (IntersectRect(&tempRect, &shape, vecEnts[i]->GetShapeAddress()))
		{
			if (tempRect.left >= vecEnts[i]->GetShapeAddress()->left &&
				tempRect.right <= vecEnts[i]->GetShapeAddress()->right &&
				(((vecEnts[i]->GetShapeAddress()->top + vecEnts[i]->GetShapeAddress()->bottom) / 2) + vecEnts[i]->GetShapeAddress()->top) / 2 > tempRect.bottom)
			{
				toStepOn = true;
				vecEnts[i]->ToBeHit();
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
						cout << "�� in :  " << i << "\n";
						break;
					}
					if (i == vecKongs.size() - 1)
						cout << "�Ḧ ��ã�Ҵ�." << "\n";
				}
				break;
			case EventTag::OUTWINDOW:
				for (int i = 0; i < vecKongs.size(); ++i)
				{
					if (vecKongs[i]->GetSubject() == subject)
					{
						kongWindow[i] = false;
						cout << "�� out: " << i << "\n";
						break;
					}
					if (i == vecKongs.size() - 1)
						cout << "�Ḧ ��ã�Ҵ�." << "\n";
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
						cout << "��Ű in: " << i << "\n";
						break;
					}
					if (i == vecMonkeys.size() - 1)
						cout << "��Ű�� ��ã�Ҵ�." << "\n";
				}
				break;
			case EventTag::OUTWINDOW:
				for (int i = 0; i < vecMonkeys.size(); ++i)
				{
					if (vecMonkeys[i]->GetSubject() == subject)
					{
						monkeyWindow[i] = false;
						cout << "��Ű out: " << i << "\n";
						break;
					}
					if (i == vecMonkeys.size() - 1)
						cout << "��Ű�� ��ã�Ҵ�." << "\n";
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
						cout << "���� in : " << i << "\n";
						break;
					}
					if (i == vecEnts.size() - 1)
						cout << "������ ��ã�Ҵ�." << "\n";
				}
				break;
			case EventTag::OUTWINDOW:
				for (int i = 0; i < vecEnts.size(); ++i)
				{
					if (vecEnts[i]->GetSubject() == subject)
					{
						entWindow[i] = false;
						cout << "���� out: " << i << "\n";
						break;
					}
					if (i == vecEnts.size() - 1)
						cout << "������ ��ã�Ҵ�." << "\n";
				}
				break;
			case EventTag::RELEASE:
				break;
			}
			break;
		}
	}
}
