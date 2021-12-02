#include "KeyManager.h"

void KeyManager::Init()
{
	for (int i = 0; i < KEY_MAX_COUNT; i++)
	{
		keyUp[i] = true;
		keyDown[i] = false;

		// �� ���� �ּ�
	}
}

void KeyManager::Release()
{
}

bool KeyManager::IsOnceKeyDown(int key)
{
	// �� ���� �ּ�
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (keyDown[key] == false)
		{
			keyDown[key] = true;
			return true;
		}
	}
	else
	{
		keyDown[key] = false;
	}
	return false;
}

bool KeyManager::IsOnceKeyUp(int key)
{
	// �ǽ�1. �� �Լ��� �ϼ��غ���.
	if (GetAsyncKeyState(key) & 0x8000)
	{
		keyUp[key] = false;
	}
	else
	{
		if (keyUp[key] == false)
		{
			keyUp[key] = true;
			return true;
		}
	}

	return false;
}

bool KeyManager::IsStayKeyDown(int key)
{
//	bool b = 0x8000 & 0x8001;

	static time_t currTime;
	// �ǽ�2. �굵 �غ���.
	if (GetAsyncKeyState(key) & 0x8001)
	{
		return true;
	}
	// �� ���� �ڵ�

	return false;
}
