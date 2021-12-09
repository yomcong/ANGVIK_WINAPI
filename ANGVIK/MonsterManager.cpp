#include "MonsterManager.h"
#include "Player.h"
#include "Kong.h"
#include "Monkey.h"
#include "Ent.h"
#include "Subject.h"

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

	// 옵저버 테스트용
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
			cout << "화면 영역에 들어옴" << "\n";
			for (int i = 0; i < vecKongs.size(); ++i)
			{
				
				if (vecKongs[i]->GetSubject() == subject)
				{
					cout << "객체를 특정했다" << "\n";
					cout << " index : " << i << "\n";
				}
				else
				{
					cout << "객체를 못찾았다." << "\n";
				}

			}
			break;
		case EventTag::RELEASE:
			cout << "화면 밖으로 나감 " << "\n";
			break;
		}
		break;
	}
}

