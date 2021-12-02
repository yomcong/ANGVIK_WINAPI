#pragma once
#include <Windows.h>

class GameEntity
{
public:
	virtual ~GameEntity() = default;

	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
};

