#include "Kong.h"
#include "Image.h"
#include "KongAmmoManager.h"
#include "Player.h"

// �÷��̾� �����ϴ� �ﰢ�Լ� ��� �ٽ��ؾ���

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

	// �ӽ� �׽�Ʈ
	pos.x = 350;
	pos.y = 350;

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

	// ������ �Ƹ�߽�
	if (KeyManager::GetSingleton()->IsOnceKeyDown('G'))
	{
		// �÷��̾� �����ϴ� �ﰢ�Լ� ��� �ٽ��ؾ���

		float targetAngle = atan2f(-(target->GetPos().y - (pos.y - CameraManager::GetSingleton()->GetPos().y)),
			(target->GetPos().x - (pos.x - CameraManager::GetSingleton()->GetPos().x)));

		int dir = (int)target->GetPos().x > (int)pos.x - CameraManager::GetSingleton()->GetPos().x;

		cout << dir << "\n";
		ammoManager->Fire(pos, targetAngle, dir);
	}

	renderPos.x = pos.x - CameraManager::GetSingleton()->GetPos().x;
	renderPos.y = pos.y - CameraManager::GetSingleton()->GetPos().y;
	
	//cout << pos.x << "\n";
	
}

void Kong::Render(HDC hdc)
{
	basicMotion->Render(hdc, (int)renderPos.x, (int)renderPos.y, basicFrame.x, basicFrame.y);

	//attackMotion->Render(hdc, 375, 350, atackFrame.x, atackFrame.y);

	ammoManager->Render(hdc);
}

void Kong::Release()
{
	SAFE_DELETE(ammoManager);
	//SAFE_RELEASE(target);	
}
