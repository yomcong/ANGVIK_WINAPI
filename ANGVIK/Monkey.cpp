//#include "stdafx.h"
#include "Monkey.h"
#include "Image.h"
#include "Subject.h"

HRESULT Monkey::Init(POINTFLOAT pos)
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

	this->pos = pos;
	renderPos = pos;

	b_isAlive = true;

	bodySize.x = 20;
	bodySize.y = 20;

	moveSpeed = 150.0f;

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
	if (b_isAlive)
	{
		PlayAnimation();
		DoAction();
	}

	PosUpdate();
	CheckWindow();

	if (Input::GetButtonDown(VK_NUMPAD9))
	{
		DBrect = !DBrect;
	}
}

void Monkey::Render(HDC hdc)
{
	if (b_isAlive)
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
}

void Monkey::Release()
{
	SAFE_DELETE(subject);
}

void Monkey::ToBeHit()
{
	if (b_isAlive)
	{
		ParticleManager::GetSingleton()->CallParticle(pos);
		b_isAlive = false;
	}
}

void Monkey::PlayAnimation()
{
	frameCount += Timer::GetDeltaTime();

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
}

void Monkey::PosUpdate()
{
	renderPos.x = pos.x - CameraManager::GetSingleton()->GetPos().x;
	renderPos.y = pos.y - CameraManager::GetSingleton()->GetPos().y;

	shape.left = (int)pos.x - bodySize.x;
	shape.top = (int)pos.y - bodySize.y;
	shape.right = (int)pos.x + bodySize.x;
	shape.bottom = (int)pos.y + bodySize.y;
}

void Monkey::CheckWindow()
{
	if (renderPos.x > 0 && renderPos.x < WIN_SIZE_X &&
		renderPos.y > 0 && renderPos.y < WIN_SIZE_Y)
	{
		if (false == b_windowIn)
		{
			subject->Notify(subject, myType, subTag, EventTag::INWINDOW);
			b_windowIn = true;
		}
	}
	else
	{
		if (b_windowIn)
		{
			subject->Notify(subject, myType, subTag, EventTag::OUTWINDOW);
			b_windowIn = false;
		}
	}
}

void Monkey::DoAction()
{
	if (MapColliderManager::GetSingleton()->IsFalling(pos, shape, moveSpeed, bodySize))
	{
		pos.y += moveSpeed * Timer::GetDeltaTime();
	}

	POINTFLOAT tempPos = MapColliderManager::GetSingleton()->
		Move(pos, shape, moveSpeed, (int)dir, bodySize);
	if (tempPos.x == 0.0f)
	{
		dir == direction::RIGHT ? dir = direction::LEFT : dir = direction::RIGHT;
	}
	pos.x += tempPos.x;
	pos.y += tempPos.y;

	if (CollisionManager::GetSingleton()->CheckCollision(subTag, shape))
	{
		ToBeHit();
	}
}
