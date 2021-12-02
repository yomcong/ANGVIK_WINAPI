#include "KongAmmo.h"
#include "Image.h"

HRESULT KongAmmo::Init()
{
	ammoRight = ImageManager::GetSingleton()->FindImage("image/monster/kongtan.bmp");
	if (ammoRight == nullptr)
	{
		return E_FAIL;
	}
	ammoLeft = ImageManager::GetSingleton()->FindImage("image/monster/kongtan22.bmp");
	if (ammoLeft == nullptr)
	{
		return E_FAIL;
	}

	moveSpeed = 100.0f;


	return S_OK;
}

void KongAmmo::Update()
{
	if (b_IsAlive)
	{
		frameCount += TimerManager().GetSingleton()->GetDeltaTime();

		if (frameCount > 0.125)
		{
			if (ammoFrame.x == 5)
			{
				ammoFrame.x = 0;
			}
			else
			{
				++ammoFrame.x;
			}

			frameCount = 0;
		}

		pos.x += cos(moveAngle) * moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
		pos.y -= sin(moveAngle) * moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();

		
	}


}

void KongAmmo::Render(HDC hdc)
{
	if (b_IsAlive)
	{
		if (direction > 0)
		{
			ammoRight->Render(hdc, pos.x, pos.y, ammoFrame.x, ammoFrame.y);
		}
		else
		{
			ammoLeft->Render(hdc, pos.x, pos.y, ammoFrame.x, ammoFrame.y);

		}
	}
}

void KongAmmo::Release()
{
}

void KongAmmo::IsFire(POINTFLOAT pos, float angle, int dir)
{
	b_IsAlive = true;
	this->moveAngle = angle;
	this->direction = dir;
	this->pos = pos;

}
