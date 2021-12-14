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

bool TrapManager::CheckCollision(RECT rect, bool& b_temp)
{
	bool isCollision = false;
	for (int i = 0; i < trapMaxCount; ++i)
	{
		// �浹 ����ȭ �غ���
		if (false == vecTraps[i]->GetIsAlive())
		{
			continue;
		}

		// ��Ʈ�浹�񱳰� �ƴ϶� ���� �ؾ���
		RECT testRect = {};
		if (IntersectRect(&testRect, vecTraps[i]->GetShapeAddress(), &rect))
		{
			vecTraps[i]->SetIsCollision(true);
			b_temp = true;
			isCollision = true;
			continue;
		}
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