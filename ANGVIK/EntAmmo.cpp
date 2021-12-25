//#include "stdafx.h"
#include "EntAmmo.h"
#include "Image.h"

HRESULT EntAmmo::Init()
{
	ammoRight = ImageManager::GetSingleton()->FindImage("image/monster/leaf4.bmp");
	if (ammoRight == nullptr)
	{
		return E_FAIL;
	}
	ammoLeft = ImageManager::GetSingleton()->FindImage("image/monster/R_leaf4.bmp");
	if (ammoLeft == nullptr)
	{
		return E_FAIL;
	}

	moveSpeed = 100.0f;

	bodySize.x = 6;
	bodySize.y = 6;

	return S_OK;
}

void EntAmmo::Update()
{
	if (b_IsAlive)
	{
		DoAction();
		PlayAnimation();
		PosUpdate();
		// µð¹ö±ë
		if (Input::GetButtonDown(VK_NUMPAD1))
			DBrect == false ? DBrect = true : DBrect = false;
	}
}

void EntAmmo::Render(HDC hdc)
{
	if (b_IsAlive)
	{
		if (dir == direction::RIGHT)
		{
			ammoRight->Render(hdc, (int)renderPos.x, (int)renderPos.y);
		}
		else
		{
			ammoLeft->Render(hdc, (int)renderPos.x, (int)renderPos.y);
		}
		// µð¹ö±ë
		if (DBrect)
			Rectangle(hdc, shape.left - (int)CameraManager::GetSingleton()->GetPos().x
				, shape.top - (int)CameraManager::GetSingleton()->GetPos().y
				, shape.right - (int)CameraManager::GetSingleton()->GetPos().x
				, shape.bottom - (int)CameraManager::GetSingleton()->GetPos().y);
	}
}

void EntAmmo::Release()
{

}

void EntAmmo::PlayAnimation()
{
	frameCount += Timer::GetDeltaTime();

	if (frameCount > 0.8)
	{
		b_IsAlive = false;
		frameCount = 0.0f;
	}
}

void EntAmmo::PosUpdate()
{
	shape.left = (int)pos.x - bodySize.x;
	shape.top = (int)pos.y - bodySize.y;
	shape.right = (int)pos.x + bodySize.x;
	shape.bottom = (int)pos.y + bodySize.y;

	renderPos.x = pos.x - CameraManager::GetSingleton()->GetPos().x;
	renderPos.y = pos.y - CameraManager::GetSingleton()->GetPos().y;
}

void EntAmmo::DoAction()
{
	pos.x += cos(moveAngle) * moveSpeed * Timer::GetDeltaTime();
	pos.y -= sin(moveAngle) * moveSpeed * Timer::GetDeltaTime();

	if (renderPos.x <0 || renderPos.x >WIN_SIZE_X ||
		renderPos.y <0 || renderPos.y > WIN_SIZE_Y ||
		MapColliderManager::GetSingleton()->checkCollision(subTag, shape, (int)dir, bodySize) ||
		CollisionManager::GetSingleton()->CheckCollision(subTag, shape))
	{
		b_IsAlive = false;
	}
}

void EntAmmo::IsFire(POINTFLOAT pos, float angle, int dir, float moveSpeed)
{
	b_IsAlive = true;

	this->moveAngle = angle;
	if (dir > 0)
	{
		this->dir = direction::RIGHT;
	}
	else
	{
		this->dir = direction::LEFT;
	}
	this->pos.x = pos.x;
	this->pos.y = pos.y + 10;
	this->moveSpeed = moveSpeed;
	renderPos.x = pos.x - CameraManager::GetSingleton()->GetPos().x;;
	renderPos.y = pos.y - CameraManager::GetSingleton()->GetPos().y;

	shape.left = (int)pos.x - bodySize.x;
	shape.top = (int)pos.y - bodySize.y;
	shape.right = (int)pos.x + bodySize.x;
	shape.bottom = (int)pos.y + bodySize.y;
}
