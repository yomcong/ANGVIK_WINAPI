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

	bodySize.x = 8;
	bodySize.y = 8;


	shape.left = (int)pos.x - bodySize.x;
	shape.top = (int)pos.y - bodySize.y;
	shape.right = (int)pos.x + bodySize.x;
	shape.bottom = (int)pos.y + bodySize.y;


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

		shape.left = (int)pos.x - bodySize.x;
		shape.top = (int)pos.y - bodySize.y;
		shape.right = (int)pos.x + bodySize.x ;
		shape.bottom = (int)pos.y + bodySize.y;

		if (MapColliderManager::GetSingleton()->checkCollision(shape, direction, bodySize))
		{
			b_IsAlive = false;
		}
		renderPos.x = pos.x - CameraManager::GetSingleton()->GetPos().x;
		renderPos.y = pos.y - CameraManager::GetSingleton()->GetPos().y;

		if (renderPos.x <0 || renderPos.x >WIN_SIZE_X ||
			renderPos.y <0 || renderPos.y > WIN_SIZE_Y)
		{
			b_IsAlive = false;
		}
	}
	// µð¹ö±ë
	if (Input::GetButtonDown(VK_NUMPAD1))
		DBrect == false ? DBrect = true : DBrect = false;
}

void KongAmmo::Render(HDC hdc)
{
	if (b_IsAlive)
	{
		if (direction > 0)
		{
			ammoRight->Render(hdc, (int)renderPos.x, (int)renderPos.y, ammoFrame.x, ammoFrame.y);
		}
		else
		{
			ammoLeft->Render(hdc, (int)renderPos.x, (int)renderPos.y, ammoFrame.x, ammoFrame.y);

		}

		// µð¹ö±ë
		if (DBrect)
			Rectangle(hdc, shape.left - (int)CameraManager::GetSingleton()->GetPos().x
				, shape.top - (int)CameraManager::GetSingleton()->GetPos().y
				, shape.right - (int)CameraManager::GetSingleton()->GetPos().x
				, shape.bottom - (int)CameraManager::GetSingleton()->GetPos().y);
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
	this->pos.x = pos.x + CameraManager::GetSingleton()->GetPos().x;
	this->pos.y = pos.y + CameraManager::GetSingleton()->GetPos().y;
	renderPos = pos;
}
