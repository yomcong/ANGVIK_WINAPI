#include "Kong.h"
#include "Image.h"
#include "KongAmmoManager.h"
#include "Player.h"

// 플레이어 조준하는 삼각함수 계산 다시해야함

HRESULT Kong::Init(Player* target, POINTFLOAT pos)
{
	attackMotion = ImageManager::GetSingleton()->FindImage("image/monster/kong_atk_8f.bmp");
	if (attackMotion == nullptr)
	{
		return E_FAIL;
	}
	basicMotion = ImageManager::GetSingleton()->FindImage("image/monster/kong_idle_6f.bmp");
	if (basicMotion == nullptr)
	{
		return E_FAIL;
	}
	
	ammoManager = new KongAmmoManager;
	ammoManager->Init(target);

	this->target = target;
	this->pos = pos;
	
	bodySize = 35;
	shape.left = pos.x - bodySize / 2;
	shape.top = pos.y - bodySize / 2;
	shape.right = pos.x + bodySize / 2;
	shape.bottom = pos.y + bodySize / 2;
	renderPos = pos;

	return S_OK;
}

void Kong::Update()
{
	ammoManager->Update();

	frameCount += TimerManager().GetSingleton()->GetDeltaTime();
	if (frameCount > 0.125)
	{
		if (basicFrame.x == 5)
		{
			basicFrame.x = 0;
		}
		else
		{
			++basicFrame.x;
		}
		
		if (atackFrame.x == 7)
		{
			atackFrame.x = 0;
		}
		else
		{
			++atackFrame.x;
		}
		frameCount = 0;
	}

	// 디버깅용 아모발싸
	if (KeyManager::GetSingleton()->IsOnceKeyDown('G'))
	{
		// 플레이어 조준하는 삼각함수 계산 다시해야함

		float targetAngle = atan2f(
			-(target->GetPos().y - pos.y),
			target->GetPos().x - pos.x);

		int dir = (int)target->GetPos().x > (int)pos.x - CameraManager::GetSingleton()->GetPos().x;

		ammoManager->Fire(renderPos, targetAngle, dir);
	}


	if (IntersectRect(&testRect, target->GetShapeAddress(), &DBrect))
	{
		testElpsedCount += TimerManager::GetSingleton()->GetDeltaTime();

		if (testElpsedCount > 1)
		{
			float targetAngle = atan2f(
				-(target->GetPos().y - pos.y),
				target->GetPos().x - pos.x);

			int dir = (int)target->GetPos().x > (int)pos.x - CameraManager::GetSingleton()->GetPos().x;
			ammoManager->Fire(renderPos, targetAngle, dir);

			testElpsedCount = 0.0f;
		}
	}

	renderPos.x = pos.x - CameraManager::GetSingleton()->GetPos().x;
	renderPos.y = pos.y - CameraManager::GetSingleton()->GetPos().y;
	
	//cout << pos.x << "\n";
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_NUMPAD9))
	{
		DBKongRect == false ? DBKongRect = true : DBKongRect = false;
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_NUMPAD1))
	{
		DBRangeRect == false ? DBRangeRect = true : DBRangeRect = false;
	}
	
	shape.left = pos.x - bodySize / 2;
	shape.top = pos.y - bodySize / 2;
	shape.right = pos.x + bodySize / 2;
	shape.bottom = pos.y + bodySize / 2;

	DBrect.left = pos.x - bodySize*3;
	DBrect.top = pos.y - bodySize*3;
	DBrect.right = pos.x + bodySize*3;
	DBrect.bottom = pos.y + bodySize*3;
	
}

void Kong::Render(HDC hdc)
{
	if(DBRangeRect)
		Rectangle(hdc, DBrect.left- CameraManager::GetSingleton()->GetPos().x,
			DBrect.top - CameraManager::GetSingleton()->GetPos().y,
			DBrect.right - CameraManager::GetSingleton()->GetPos().x,
			DBrect.bottom - CameraManager::GetSingleton()->GetPos().y);

	basicMotion->Render(hdc, (int)renderPos.x, (int)renderPos.y, basicFrame.x, basicFrame.y);

	//attackMotion->Render(hdc, 375, 350, atackFrame.x, atackFrame.y);

	ammoManager->Render(hdc);

	if (DBKongRect)
		Rectangle(hdc, shape.left, shape.top, shape.right, shape.bottom);

	
}

void Kong::Release()
{
	SAFE_DELETE(ammoManager);
	//SAFE_RELEASE(target);	
}
