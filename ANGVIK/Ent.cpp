#include "Ent.h"
#include "Player.h"
#include "Image.h"
#include "EntAmmoManager.h"

HRESULT Ent::Init(Player* target, POINTFLOAT pos)
{
 	basicEnt = ImageManager::GetSingleton()->FindImage("image/monster/Ent_move_6f.bmp");
	if (basicEnt == nullptr)
	{
		return E_FAIL;
	}
	entAttack = ImageManager::GetSingleton()->FindImage("image/monster/Ent_atk_6f.bmp");
	if (entAttack == nullptr)
	{
		return E_FAIL;
	}
	R_basicEnt = ImageManager::GetSingleton()->FindImage("image/monster/R_Ent_move_6f.bmp");
	if (R_basicEnt == nullptr)
	{
		return E_FAIL;
	}
	R_entAttack = ImageManager::GetSingleton()->FindImage("image/monster/R_Ent_atk_6f.bmp");
	if (R_entAttack == nullptr)
	{
		return E_FAIL;
	}

	ammoManager = new EntAmmoManager;
	ammoManager->Init(target);

	this->target = target;
	this->pos = pos;

	bodySize.x = 50;
	bodySize.y = 85;

	moveSpeed = 100.0f;

	shape.left = (int)pos.x - bodySize.x / 2;
	shape.top = (int)pos.y - bodySize.y / 2;
	shape.right = (int)pos.x + bodySize.x / 2;
	shape.bottom = (int)pos.y + bodySize.y / 2;

	basicFrame.x = 0;
	basicFrame.y = 0;

	renderPos = pos;

	return S_OK;
}

void Ent::Update()
{

	if (MapColliderManager::GetSingleton()->AutoFall(pos, shape, moveSpeed, bodySize))
	{
		pos.y += 3.0f;
	}

	bodySize.x = 50;
	bodySize.y = 85;

	POINTFLOAT tempPos = MapColliderManager::GetSingleton()->
		Move(pos, shape, moveSpeed, (int)dir, bodySize);

	if (tempPos.x == 0.0f)
	{
		dir == direction::RIGHT ? dir = direction::LEFT : dir = direction::RIGHT;
	}

	pos.x += tempPos.x;
	pos.y += tempPos.y;

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

		frameCount = 0.0f;
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

void Ent::Render(HDC hdc)
{
	if (dir == direction::RIGHT)
	{
		basicEnt->Render(hdc, (int)renderPos.x, (int)renderPos.y, basicFrame.x, basicFrame.y);
	}
	else
	{
		R_basicEnt->Render(hdc, (int)renderPos.x, (int)renderPos.y, basicFrame.x, basicFrame.y);
	}

	if (DBrect)
		Rectangle(hdc, shape.left - (int)CameraManager::GetSingleton()->GetPos().x,
			shape.top - (int)CameraManager::GetSingleton()->GetPos().y,
			shape.right - (int)CameraManager::GetSingleton()->GetPos().x,
			shape.bottom - (int)CameraManager::GetSingleton()->GetPos().y);
}

void Ent::Release()
{
}
