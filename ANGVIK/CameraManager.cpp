#include "CameraManager.h"

HRESULT CameraManager::Init()
{
	return S_OK;
}

void CameraManager::Update()
{
	 //µð¹ö±ë
	if (Input::GetButton(VK_NUMPAD6))
	{
		pos.x += 10;
	}
	if (Input::GetButton(VK_NUMPAD4))
	{
		if (pos.x > 0)
			pos.x -= 10;
	}
	if (Input::GetButton(VK_NUMPAD2))
	{
		pos.y += 10;
	}
	if (Input::GetButton(VK_NUMPAD8))
	{
		if (pos.y > 0)
			pos.y -= 10;
	}

}
