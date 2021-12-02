#pragma once
#include "Config.h"
#include "Singleton.h"

class Timer;
class TimerManager : public Singleton<TimerManager>
{
private:
	Timer* timer = nullptr;
	char szText[256] = {};

public:
	virtual ~TimerManager() = default;

	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	float GetDeltaTime();
};

