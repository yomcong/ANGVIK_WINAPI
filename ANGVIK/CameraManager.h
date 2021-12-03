#pragma once
#include "Config.h"
#include "Singleton.h"



class CameraManager : public Singleton<CameraManager>
{
public:
	virtual ~CameraManager() = default;

	HRESULT Init();
	void Update();
	
	inline const POINTFLOAT GetPos() { return this->pos; }
	inline void SetPos(POINTFLOAT pos) { this->pos.x += pos.x, this->pos.y += pos.y; }
	inline void SetPosX(float pos) { this->pos.x += pos; }
	inline void SetPosY(float pos) { this->pos.y += pos; }

private:
	POINTFLOAT pos = {0, 0};

};

