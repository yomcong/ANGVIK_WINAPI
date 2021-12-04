#include "Monkey.h"
#include "Image.h"
#include "Player.h"


HRESULT Monkey::Init(Player* target, POINTFLOAT pos)
{
	monkey = ImageManager::GetSingleton()->FindImage("image/monster/¿ø¼þÀÌ.bmp");
	if (monkey == nullptr)
	{
		return E_FAIL;
	}
	
	this->target = target;

	this->pos = pos;
	renderPos = pos;
	
	bodySize.x = 10;
	bodySize.y = 10;

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
	renderPos.x = pos.x - CameraManager::GetSingleton()->GetPos().x;
	renderPos.y = pos.y - CameraManager::GetSingleton()->GetPos().y;

	shape.left = (int)pos.x - bodySize.x;
	shape.top = (int)pos.y - bodySize.y;
	shape.right = (int)pos.x + bodySize.x;
	shape.bottom = (int)pos.y + bodySize.y;

	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_NUMPAD9))
	{
		DBrect == false ? DBrect = true : DBrect = false;
	}
}

void Monkey::Render(HDC hdc)
{
	monkey->Render(hdc, (int)renderPos.x, (int)renderPos.y, framePos.x, framePos.y);

	if (DBrect)
		Rectangle(hdc, shape.left - (int)CameraManager::GetSingleton()->GetPos().x,
			shape.top - (int)CameraManager::GetSingleton()->GetPos().y,
			shape.right - (int)CameraManager::GetSingleton()->GetPos().x,
			shape.bottom - (int)CameraManager::GetSingleton()->GetPos().y);
}

void Monkey::Release()
{
}
