#include "MonsterManager.h"
#include "Player.h"
#include "Kong.h"
#include "Monkey.h"
#include "Ent.h"
#include "Subject.h"

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
		vecKongs[i]->Render(hdc);
	}
	for (int i = 0; i < vecMonkeys.size(); ++i)
	{
		vecMonkeys[i]->Render(hdc);
	}
	for (int i = 0; i < vecEnts.size(); ++i)
	{
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
	/*kongMaxCount = RANDOM(1, kongMaxCount);
	vecKongs.resize(kongMaxCount);
	float spawnPosX[] = { 350.0f, 500.0f, 850.0f };
	float spawnPosY[] = { 360.0f, 275.0f, 382.0f };*/

	// ������ �׽�Ʈ��
	vecKongs.resize(4);
	float spawnPosX[] = { 350.0f, 500.0f, 850.0f, 1500.0f };
	float spawnPosY[] = { 360.0f, 275.0f, 382.0f, 360.0f };
	for (int i = 0; i < vecKongs.size(); ++i)
	{
		vecKongs[i] = new Kong;
		vecKongs[i]->Init(target, { spawnPosX[i],spawnPosY[i] });
		if (i == 3)
		{
			vecKongs[i]->GetSubject()->AddObserver(this);
		}
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
	}
}


void MonsterManager::EntSpawn()
{
	EntMaxCount = RANDOM(1, EntMaxCount);
	vecEnts.resize(EntMaxCount);

	float spawnPosX[] = { 380.0f, 550.0f, 900.0f };
	float spawnPosY[] = { 340.0f, 250.0f, 360.0f };

	for (int i = 0; i < vecEnts.size(); ++i)
	{
		vecEnts[i] = new Ent;
		vecEnts[i]->Init(target, { spawnPosX[i],spawnPosY[i] });
	}


}
void MonsterManager::OnNotify(Subject* subject, SubjectTag subjectTag, EventTag eventTag)
{
	switch (subjectTag)
	{
	case SubjectTag::ENEMY:
		switch (eventTag)
		{
		case EventTag::IDLE:
			cout << "ȭ�� ������ ����" << "\n";
			for (int i = 0; i < vecKongs.size(); ++i)
			{
				
				if (vecKongs[i]->GetSubject() == subject)
				{
					cout << "��ü�� Ư���ߴ�" << "\n";
					cout << " index : " << i << "\n";
				}
				else
				{
					cout << "��ü�� ��ã�Ҵ�." << "\n";
				}

			}
			break;
		case EventTag::RELEASE:
			cout << "ȭ�� ������ ���� " << "\n";
			break;
		}
		break;
	}
}

