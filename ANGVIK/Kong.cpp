#include "Kong.h"
#include "Image.h"
#include "KongAmmoManager.h"
#include "Player.h"

HRESULT Kong::Init(Player* target)
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

	// 임시 테스트
	pos.x = 350;
	pos.y = 350;

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
		float targetAngle = atan2f(-(target->GetPos().y - pos.y),
			(target->GetPos().x - pos.x));

		int dir = (int)target->GetPos().x - (int)pos.x;

		ammoManager->Fire(pos, targetAngle, dir);
	}
}

void Kong::Render(HDC hdc)
{
	basicMotion->Render(hdc, 350, 350, basicFrame.x, basicFrame.y);

	attackMotion->Render(hdc, 375, 350, atackFrame.x, atackFrame.y);

	ammoManager->Render(hdc);
}

void Kong::Release()
{
	SAFE_DELETE(ammoManager);
	//SAFE_RELEASE(target);	
}
