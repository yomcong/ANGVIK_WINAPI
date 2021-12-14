#include "Monkey.h"
#include "Image.h"
#include "Player.h"
#include "Subject.h"

HRESULT Monkey::Init(Player* target, POINTFLOAT pos)
{
	monkey = ImageManager::GetSingleton()->FindImage("image/monster/¿ø¼þÀÌ.bmp");
	if (monkey == nullptr)
	{
		return E_FAIL;
	}
	R_monkey = ImageManager::GetSingleton()->FindImage("image/monster/R_¿ø¼þÀÌ.bmp");
	if (R_monkey == nullptr)
	{
		return E_FAIL;
	}
	
	subject = new Subject;

	this->target = target;

	this->pos = pos;
	renderPos = pos;
	
	b_isAlive = true;

	bodySize.x = 20;
	bodySize.y = 20;

	moveSpeed = 100.0f;

	shape.left = (int)pos.x - bodySize.x;
	shape.top = (int)pos.y - bodySize.y;
	shape.right = (int)pos.x + bodySize.x;
	shape.bottom = (int)pos.y + bodySize.y;

	framePos.x = 0;
	framePos.y = 0;

	return S_OK;
}

void Monkey::Update()
{
	if (MapColliderManager::GetSingleton()->IsFalling(pos, shape, moveSpeed, bodySize))
	{
		pos.y += 3.0f;
	}

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
		if (framePos.x == 7)
		{
			framePos.x = 0;
		}
		else
		{
			++framePos.x;
		}

		frameCount = 0.0f;
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

	renderPos.x = pos.x - CameraManager::GetSingleton()->GetPos().x;
	renderPos.y = pos.y - CameraManager::GetSingleton()->GetPos().y;

	shape.left = (int)pos.x - bodySize.x;
	shape.top = (int)pos.y - bodySize.y;
	shape.right = (int)pos.x + bodySize.x;
	shape.bottom = (int)pos.y + bodySize.y;

	if (Input::GetButtonDown(VK_NUMPAD9))
	{
		DBrect == false ? DBrect = true : DBrect = false;
	}
}

void Monkey::Render(HDC hdc)
{
	if (dir == direction::RIGHT)
	{
		monkey->Render(hdc, (int)renderPos.x, (int)renderPos.y, framePos.x, framePos.y);
	}
	else
	{
		R_monkey->Render(hdc, (int)renderPos.x, (int)renderPos.y, framePos.x, framePos.y);
	}

	if (DBrect)
		Rectangle(hdc, shape.left - (int)CameraManager::GetSingleton()->GetPos().x,
			shape.top - (int)CameraManager::GetSingleton()->GetPos().y,
			shape.right - (int)CameraManager::GetSingleton()->GetPos().x,
			shape.bottom - (int)CameraManager::GetSingleton()->GetPos().y);
}

void Monkey::Release()
{
	SAFE_DELETE(subject);
}
