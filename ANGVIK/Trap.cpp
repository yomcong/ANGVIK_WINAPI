#include "Trap.h"
#include "Image.h"

HRESULT Trap::Init(POINTFLOAT pos, int dir)
{
	trap = ImageManager::GetSingleton()->FindImage("image/Stage/treetrap.bmp");
	if (trap == nullptr)
	{
		return E_FAIL;
	}
	R_trap = ImageManager::GetSingleton()->FindImage("image/Stage/R_treetrap.bmp");
	if (R_trap == nullptr)
	{
		return E_FAIL;
	}

	this->pos = pos;
	if (dir > 0)
	{
		this->dir = direction::RIGHT;
	}
	else
	{
		this->dir = direction::LEFT;
	}

	b_isAlive = true;

	framePos.x = 0;
	framePos.y = 0;

	bodySize.x = 40;
	bodySize.y = 14;

	shape.left = (int)pos.x - bodySize.x / 2;
	shape.top = (int)pos.y - bodySize.y / 2;
	shape.right = (int)pos.x + bodySize.x / 2;
	shape.bottom = (int)pos.y + bodySize.y / 2;

	renderPos = pos;

	return S_OK;
}

void Trap::Update()
{
	if (false == b_isAlive)
	{
		respawnCount += TimerManager().GetSingleton()->GetDeltaTime();

		if (respawnCount > 1.5)
		{
			respawnCount = 0.0f;
			framePos.y = 0;
			b_isAlive = true;
		}
	}
	else
	{
		if (b_isCollision)
		{
			frameCount += TimerManager().GetSingleton()->GetDeltaTime();
			if (frameCount > 0.125)
			{
				if (framePos.y == 5)
				{
					b_isAlive = false;
					b_isCollision = false;
					framePos.y = 0;
				}
				else
				{
					++framePos.y;
				}
				frameCount = 0.0f;
			}
		}
		else
		{
			framePos.y = 0;
		}
	}


	renderPos.x = pos.x - CameraManager::GetSingleton()->GetPos().x;
	renderPos.y = pos.y - CameraManager::GetSingleton()->GetPos().y;

	shape.left = (int)pos.x - bodySize.x / 2;
	shape.top = (int)pos.y - bodySize.y / 2;
	shape.right = (int)pos.x + bodySize.x / 2;
	shape.bottom = (int)pos.y + bodySize.y / 2;

	if (Input::GetButtonDown(VK_NUMPAD9))
	{
		DBrect == false ? DBrect = true : DBrect = false;
	}
}

void Trap::Render(HDC hdc)
{
	if (b_isAlive)
	{
		if (dir == direction::RIGHT)
		{
			trap->Render(hdc, (int)renderPos.x, (int)renderPos.y, framePos.x, framePos.y);
		}
		else
		{
			R_trap->Render(hdc, (int)renderPos.x, (int)renderPos.y, framePos.x, framePos.y);
		}


		if (DBrect)
			Rectangle(hdc, shape.left - (int)CameraManager::GetSingleton()->GetPos().x,
				shape.top - (int)CameraManager::GetSingleton()->GetPos().y,
				shape.right - (int)CameraManager::GetSingleton()->GetPos().x,
				shape.bottom - (int)CameraManager::GetSingleton()->GetPos().y);
	}

	
}

void Trap::Release()
{

}
