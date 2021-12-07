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
	R_attackMotion = ImageManager::GetSingleton()->FindImage("image/monster/R_kong_atk_8f.bmp");
	if (attackMotion == nullptr)
	{
		return E_FAIL;
	}
	R_basicMotion = ImageManager::GetSingleton()->FindImage("image/monster/R_kong_idle_6f.bmp");
	if (basicMotion == nullptr)
	{
		return E_FAIL;
	}
	ammoManager = new KongAmmoManager;
	ammoManager->Init(target);

	this->target = target;
	this->pos = pos;
	
	bodySize.x = 35;
	bodySize.y = 35;

	shape.left = (int)pos.x - bodySize.x / 2;
	shape.top = (int)pos.y - bodySize.y / 2;
	shape.right = (int)pos.x + bodySize.x / 2;
	shape.bottom = (int)pos.y + bodySize.y / 2;

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


	if (IntersectRect(&testRect, target->GetShapeAddress(), &DBRenderShape))
	{
		testElpsedCount += TimerManager::GetSingleton()->GetDeltaTime();

		if (testElpsedCount > 1)
		{
			float targetAngle = atan2f(
				-(target->GetPos().y - pos.y),
				target->GetPos().x - pos.x);

			int dir = (int)target->GetPos().x > (int)pos.x - CameraManager::GetSingleton()->GetPos().x;
			if (dir > 0)
			{
				this->dir = direction::RIGHT;
			}
			else
			{
				this->dir = direction::LEFT;

			}
			ammoManager->Fire(renderPos, targetAngle, dir);

			testElpsedCount = 0.0f;
		}
	}

	renderPos.x = pos.x - CameraManager::GetSingleton()->GetPos().x;
	renderPos.y = pos.y - CameraManager::GetSingleton()->GetPos().y;
	
	if (Input::GetButtonDown(VK_NUMPAD9))
	{
		DBrect == false ? DBrect = true : DBrect = false;
	}
	if (Input::GetButtonDown(VK_NUMPAD1))
	{
		DBRangeRect == false ? DBRangeRect = true : DBRangeRect = false;
	}

	shape.left = (int)pos.x - bodySize.x / 2;
	shape.top = (int)pos.y - bodySize.y / 2;
	shape.right = (int)pos.x + bodySize.x / 2;
	shape.bottom = (int)pos.y + bodySize.y / 2;

	DBRenderShape.left = (int)pos.x - bodySize.x*3;
	DBRenderShape.top = (int)pos.y - bodySize.y*3;
	DBRenderShape.right = (int)pos.x + bodySize.x*3;
	DBRenderShape.bottom = (int)pos.y + bodySize.y*3;
	
}

void Kong::Render(HDC hdc)
{
	if(DBRangeRect)
		Rectangle(hdc, DBRenderShape.left- (int)CameraManager::GetSingleton()->GetPos().x,
			DBRenderShape.top - (int)CameraManager::GetSingleton()->GetPos().y,
			DBRenderShape.right - (int)CameraManager::GetSingleton()->GetPos().x,
			DBRenderShape.bottom - (int)CameraManager::GetSingleton()->GetPos().y);

	if (dir == direction::RIGHT)
	{
		//attackMotion->Render(hdc, (int)renderPos.x, (int)renderPos.y, basicFrame.x, basicFrame.y);
		basicMotion->Render(hdc, (int)renderPos.x, (int)renderPos.y, basicFrame.x, basicFrame.y);
	}
	else
	{
		//R_attackMotion->Render(hdc, (int)renderPos.x, (int)renderPos.y, basicFrame.x, basicFrame.y);
		R_basicMotion->Render(hdc, (int)renderPos.x, (int)renderPos.y, basicFrame.x, basicFrame.y);
	}

	//attackMotion->Render(hdc, 375, 350, atackFrame.x, atackFrame.y);

	ammoManager->Render(hdc);

	if (DBrect)
		Rectangle(hdc, shape.left - (int)CameraManager::GetSingleton()->GetPos().x,
			shape.top - (int)CameraManager::GetSingleton()->GetPos().y,
			shape.right - (int)CameraManager::GetSingleton()->GetPos().x,
			shape.bottom - (int)CameraManager::GetSingleton()->GetPos().y);

	
}

void Kong::Release()
{
	SAFE_DELETE(ammoManager);
	//SAFE_RELEASE(target);	
}
