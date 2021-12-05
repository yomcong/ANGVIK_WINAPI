#include "CameraManager.h"

HRESULT CameraManager::Init()
{
	return S_OK;
}

void CameraManager::Update()
{
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_NUMPAD6))
	{
		pos.x += 5;
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_NUMPAD4))
	{
		if (pos.x > 0)
			pos.x -= 5;
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_NUMPAD2))
	{
		pos.y += 5;
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_NUMPAD8))
	{
		if (pos.y > 0)
			pos.y -= 5;
	}

}
