#include "TrapManager.h"
#include "Trap.h"

HRESULT TrapManager::Init()
{
	TrapSpawn();

	return S_OK;
}

void TrapManager::Update()
{
	for (int i = 0; i < trapMaxCount; ++i)
	{
		vecTraps[i]->Update();
	}
}

void TrapManager::Render(HDC hdc)
{
	for (int i = 0; i < trapMaxCount; ++i)
	{
		vecTraps[i]->Render(hdc);
	}
}

void TrapManager::Release()
{
	for (int i = 0; i < trapMaxCount; ++i)
	{
		SAFE_RELEASE(vecTraps[i]);
	}
	vecTraps.clear();
}

void TrapManager::TrapSpawn()
{
	vecTraps.resize(trapMaxCount);

	float spawnPosX[] = { 450.0f, 90.0f };
	float spawnPosY[] = { 310.0f, 410.0f };

	for (int i = 0; i < trapMaxCount; ++i)
	{
		int dir = i < trapMaxCount / 2;
		vecTraps[i] = new Trap;
		vecTraps[i]->Init({ spawnPosX[i],spawnPosY[i] }, dir);
	}
}

bool TrapManager::CheckCollision(RECT rect)
{
	bool isCollision = false;
	for (int i = 0; i < trapMaxCount; ++i)
	{
		// 충돌 최적화 해보기
		if (false == vecTraps[i]->GetIsAlive())
		{
			continue;
		}
		if (vecTraps[i]->GetShapeAddress()->left < rect.right &&
			vecTraps[i]->GetShapeAddress()->right > rect.left &&
			vecTraps[i]->GetShapeAddress()->top > rect.bottom &&
			rect.bottom > vecTraps[i]->GetShapeAddress()->top - 2 )
		{
			vecTraps[i]->SetIsCollision(true);
			cout << vecTraps[i]->GetShapeAddress()->top << "\n";
			cout << vecTraps[i]->GetShapeAddress()->left << "\n";
			cout << vecTraps[i]->GetShapeAddress()->right << "\n";
			cout << vecTraps[i]->GetShapeAddress()->bottom<< "\n";

			cout << rect.top << "\n";
			cout << rect.left << "\n";
			cout << rect.right << "\n";
			cout << rect.bottom << "\n";

			isCollision = true;
			continue;
		}

		/*cout << vecTraps[i]->GetShapeAddress()->top << "\n";
		cout << "player : " << rect.bottom << "\n";
		RECT testRect = {};
		if (IntersectRect(&testRect, vecTraps[i]->GetShapeAddress(), &rect))
		{
			vecTraps[i]->SetIsCollision(true);
			isCollision = true;
			continue;
			
		}*/
		vecTraps[i]->SetIsCollision(false);
	}

	if (isCollision)
	{
		return true;
	}
	else
	{
		return false;
	}
}