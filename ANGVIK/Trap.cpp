//#include "stdafx.h"
#include "Trap.h"

HRESULT Trap::Init(POINTFLOAT pos, POINT bodySize)
{
	this->pos = pos;

	b_isAlive = true;

	this->bodySize.x = bodySize.x;
	this->bodySize.y = bodySize.y;

	shape.left = (int)pos.x - bodySize.x / 2;
	shape.top = (int)pos.y - bodySize.y / 2;
	shape.right = (int)pos.x + bodySize.x / 2;
	shape.bottom = (int)pos.y + bodySize.y / 2;

	renderPos = pos;

	return S_OK;
}

void Trap::Update()
{

	renderPos.x = pos.x - CameraManager::GetSingleton()->GetPos().x;
	renderPos.y = pos.y - CameraManager::GetSingleton()->GetPos().y;

	shape.left = (int)pos.x - bodySize.x / 2;
	shape.top = (int)pos.y - bodySize.y / 2;
	shape.right = (int)pos.x + bodySize.x / 2;
	shape.bottom = (int)pos.y + bodySize.y / 2;

	if (renderPos.x > 0 && renderPos.x < WIN_SIZE_X &&
		renderPos.y > 0 && renderPos.y < WIN_SIZE_Y)
	{
		if (false == b_windowIn)
		{
			Notify(this, subTag, EventTag::INWINDOW);
			b_windowIn = true;
		}
	}
	else
	{
		if (b_windowIn)
		{
			Notify(this, subTag, EventTag::OUTWINDOW);
			b_windowIn = false;
		}
	}

	if (Input::GetButtonDown(VK_NUMPAD9))
	{
		DBrect = !DBrect;
	}
}

void Trap::Render(HDC hdc)
{
	if (DBrect)
		Rectangle(hdc, shape.left - (int)CameraManager::GetSingleton()->GetPos().x,
			shape.top - (int)CameraManager::GetSingleton()->GetPos().y,
			shape.right - (int)CameraManager::GetSingleton()->GetPos().x,
			shape.bottom - (int)CameraManager::GetSingleton()->GetPos().y);

}

void Trap::Release()
{

}
