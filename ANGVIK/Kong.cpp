#include "Kong.h"
#include "Image.h"
#include "KongAmmoManager.h"
#include "Player.h"
#include "Subject.h"

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
	
	b_isAlive = true;

	bodySize.x = 35;
	bodySize.y = 35;

	subject = new Subject;

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
		
		if (attackFrame.x == 7)
		{
			attackFrame.x = 0;
		}
		else
		{
			++attackFrame.x;
		}
		frameCount = 0;
	}

	if (renderPos.x > 0 && renderPos.x < WIN_SIZE_X &&
		renderPos.y > 0 && renderPos.y < WIN_SIZE_Y)
	{
		if (false == windowIn)
		{
			subject->Notify(subject, myType, subTag, EventTag::INWINDOW);
			windowIn = true;
		}
	}
	else
	{
		if (windowIn)
		{
			subject->Notify(subject, myType, subTag, EventTag::OUTWINDOW);
			windowIn = false;
		}
	}

	// 테스트용 아모발싸 함수화하기
	if (IntersectRect(&testRect, target->GetShapeAddress(), &rangeRect))
	{
		testElpsedCount += TimerManager::GetSingleton()->GetDeltaTime();

		if (testElpsedCount > 1)
		{
			float targetAngle = atan2f(
				-(target->GetPos().y - pos.y),
				target->GetPos().x - pos.x);

			int dir = (int)target->GetPos().x > (int)pos.x;
			if (dir > 0)
			{
				this->dir = direction::RIGHT;
			}
			else
			{
				this->dir = direction::LEFT;
			}

			ammoManager->Fire(pos, targetAngle, dir);

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

	rangeRect.left = (int)pos.x - bodySize.x*3;
	rangeRect.top = (int)pos.y - bodySize.y*3;
	rangeRect.right = (int)pos.x + bodySize.x*3;
	rangeRect.bottom = (int)pos.y + bodySize.y*3;
	
}

void Kong::Render(HDC hdc)
{
	if (b_isAlive)
	{
		if (DBRangeRect)
			Rectangle(hdc, rangeRect.left - (int)CameraManager::GetSingleton()->GetPos().x,
				rangeRect.top - (int)CameraManager::GetSingleton()->GetPos().y,
				rangeRect.right - (int)CameraManager::GetSingleton()->GetPos().x,
				rangeRect.bottom - (int)CameraManager::GetSingleton()->GetPos().y);

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

		//attackMotion->Render(hdc, 375, 350, attackFrame.x, attackFrame.y);

		ammoManager->Render(hdc);

		if (DBrect)
			Rectangle(hdc, shape.left - (int)CameraManager::GetSingleton()->GetPos().x,
				shape.top - (int)CameraManager::GetSingleton()->GetPos().y,
				shape.right - (int)CameraManager::GetSingleton()->GetPos().x,
				shape.bottom - (int)CameraManager::GetSingleton()->GetPos().y);
	}
}

void Kong::Release()
{
	SAFE_RELEASE(ammoManager);
	SAFE_DELETE(subject);
	//SAFE_RELEASE(target);	
}

void Kong::OnNotify(Subject* subject, MonsterType monsterType, SubjectTag subjectTag, EventTag eventTag)
{
	
}
