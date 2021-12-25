//#include "stdafx.h"
#include "Kong.h"
#include "Image.h"
#include "AmmoManager.h"

// 플레이어 조준하는 삼각함수 계산 다시해야함

HRESULT Kong::Init(POINTFLOAT pos, AmmoManager* _ammoManager)
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

	ammoManager = _ammoManager;


	this->pos = pos;

	b_isAlive = true;

	bodySize.x = 35;
	bodySize.y = 35;

	shape.left = (int)pos.x - bodySize.x / 2;
	shape.top = (int)pos.y - bodySize.y / 2;
	shape.right = (int)pos.x + bodySize.x / 2;
	shape.bottom = (int)pos.y + bodySize.y / 2;

	rangeRect.left = (int)pos.x - bodySize.x * 10;
	rangeRect.top = (int)pos.y - bodySize.y * 8;
	rangeRect.right = (int)pos.x + bodySize.x * 10;
	rangeRect.bottom = (int)pos.y + bodySize.y * 8;

	renderPos = pos;

	return S_OK;
}

void Kong::Update()
{
	PlayAnimation();
	CheckAttackRange();
	CheckWindow();

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

		if (b_rangeInTarget)
		{
			if (dir == direction::RIGHT)
			{
				attackMotion->Render(hdc, (int)renderPos.x, (int)renderPos.y + 10, attackFrame.x, attackFrame.y);
			}
			else
			{
				R_attackMotion->Render(hdc, (int)renderPos.x, (int)renderPos.y + 10, attackFrame.x, attackFrame.y);
			}
		}
		else
		{
			if (dir == direction::RIGHT)
			{
				basicMotion->Render(hdc, (int)renderPos.x, (int)renderPos.y, basicFrame.x, basicFrame.y);
			}
			else
			{
				R_basicMotion->Render(hdc, (int)renderPos.x, (int)renderPos.y, basicFrame.x, basicFrame.y);
			}

		}

		//attackMotion->Render(hdc, 375, 350, attackFrame.x, attackFrame.y);

		if (DBrect)
			Rectangle(hdc, shape.left - (int)CameraManager::GetSingleton()->GetPos().x,
				shape.top - (int)CameraManager::GetSingleton()->GetPos().y,
				shape.right - (int)CameraManager::GetSingleton()->GetPos().x,
				shape.bottom - (int)CameraManager::GetSingleton()->GetPos().y);
	}
}

void Kong::Release()
{

}

void Kong::ToBeHit()
{
	if (b_isAlive)
	{
		ParticleManager::GetSingleton()->CallParticle(pos);
		b_isAlive = false;
	}
}

void Kong::PlayAnimation()
{
	frameCount += Timer::GetDeltaTime();
	if (frameCount > 0.100)
	{
		if (b_rangeInTarget)
		{
			if (attackFrame.x == 7)
			{
				attackFrame.x = 0;
			}
			else
			{
				++attackFrame.x;
			}
		}
		else
		{
			if (basicFrame.x == 5)
			{
				basicFrame.x = 0;
			}
			else
			{
				++basicFrame.x;
			}

		}
		frameCount = 0;
	}
}

void Kong::CheckWindow()
{
	if (renderPos.x > 0 && renderPos.x < WIN_SIZE_X &&
		renderPos.y > 0 && renderPos.y < WIN_SIZE_Y)
	{
		if (false == b_windowIn)
		{
			Notify(this, subTag, EventTag::INWINDOW, myType);
			b_windowIn = true;
		}
	}
	else
	{
		if (b_windowIn)
		{
			Notify(this, subTag, EventTag::OUTWINDOW, myType);
			b_windowIn = false;
		}
	}
}

void Kong::CheckAttackRange()
{
	POINTFLOAT tempPos = CollisionManager::GetSingleton()->RangeCheckCollision(subTag, rangeRect, EventTag::RANGECOLLISION);

	if (tempPos.x > 0 ||
		tempPos.y > 0)
	{
		AttackDeleyCount += Timer::GetDeltaTime();

		if (b_rangeInTarget == false)
		{
			b_rangeInTarget = true;
			attackFrame.x = 0;
		}

		if (AttackDeleyCount > 0.700f)
		{

			float targetAngle = atan2f(
				-(tempPos.y - pos.y),
				tempPos.x - pos.x);

			int dir = tempPos.x > (int)pos.x;

			if (dir > 0)
			{
				this->dir = direction::RIGHT;
			}
			else
			{
				this->dir = direction::LEFT;
			}

			ammoManager->KongFire(pos, targetAngle, dir);

			AttackDeleyCount = 0.0f;
		}
	}
	else
	{
		if (b_rangeInTarget)
		{
			b_rangeInTarget = false;
			AttackDeleyCount = 0.0f;
			basicFrame.x = 0;
		}
	}


}
