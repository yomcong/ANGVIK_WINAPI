//#include "stdafx.h"
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

	moveSpeed = 200.0f;

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
		PlayAnimation();
		DoAction();
		PosUpdate();

		if (Input::GetButtonDown(VK_NUMPAD1))
			DBrect = !DBrect;
	}
}

void KongAmmo::Render(HDC hdc)
{
	if (b_IsAlive)
	{
		if (dir == direction::RIGHT)
		{
			ammoRight->Render(hdc, (int)renderPos.x, (int)renderPos.y, ammoFrame.x, ammoFrame.y);
		}
		else
		{
			ammoLeft->Render(hdc, (int)renderPos.x, (int)renderPos.y, ammoFrame.x, ammoFrame.y);
		}
		// ??????
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

void KongAmmo::PlayAnimation()
{
	frameCount += Timer::GetDeltaTime();

	if (frameCount > 0.0625)
	{
		if (ammoFrame.x == ammoMaxFrame.x)
		{
			ammoFrame.x = 0;
		}
		else
		{
			++ammoFrame.x;
		}
		frameCount = 0;
	}
}

void KongAmmo::PosUpdate()
{
	shape.left = (int)pos.x - bodySize.x;
	shape.top = (int)pos.y - bodySize.y;
	shape.right = (int)pos.x + bodySize.x;
	shape.bottom = (int)pos.y + bodySize.y;

	renderPos.x = pos.x - CameraManager::GetSingleton()->GetPos().x;
	renderPos.y = pos.y - CameraManager::GetSingleton()->GetPos().y;
}

void KongAmmo::DoAction()
{
	pos.x += cos(moveAngle) * moveSpeed * Timer::GetDeltaTime();
	pos.y -= sin(moveAngle) * moveSpeed * Timer::GetDeltaTime();

	if (MapColliderManager::GetSingleton()->checkCollision(subTag, shape, (int)dir, bodySize))
	{
		b_IsAlive = false;
	}

	if (CollisionManager::GetSingleton()->CheckCollision(subTag, shape))
	{
		ParticleManager::GetSingleton()->CallParticle(subTag, pos, (int)dir);
		b_IsAlive = false;

	}

	if (renderPos.x <0 || renderPos.x >WIN_SIZE_X ||
		renderPos.y <0 || renderPos.y > WIN_SIZE_Y)
	{
		b_IsAlive = false;
	}

}

void KongAmmo::IsFire(POINTFLOAT pos, float angle, int dir)
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
	this->pos.y = pos.y;
	renderPos.x = pos.x - CameraManager::GetSingleton()->GetPos().x;;
	renderPos.y = pos.y - CameraManager::GetSingleton()->GetPos().y;

	shape.left = (int)pos.x - bodySize.x;
	shape.top = (int)pos.y - bodySize.y;
	shape.right = (int)pos.x + bodySize.x;
	shape.bottom = (int)pos.y + bodySize.y;
}
