#pragma once
#include "GameEntity.h"
#include "Config.h"

//enum class Action{ Idle, JUMP, ATTACK, HIT };

//struct Player
//{
//	POINTFLOAT pos = {};
//	RECT collider = {};
//	int bodySize_X = 0;
//	int bodySize_Y = 0;
//	Action action = Action::Idle;
//};
//

class Player;
class Kong;
class Image;
class StageScene : public GameEntity	
{
public:
	virtual ~StageScene() = default;

	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

private:
	Image* stageBackgruond = nullptr;
	Image* stageBackgruond2 = nullptr;
	Image* stagePixelMap = nullptr;


	POINT mapPos = {};

	Player* player = nullptr;
	Kong* kong = nullptr;

	// 픽셀 충돌
	//COLORREF color = {};
	//WORD r, g, b = {};

	//디버그용
	bool debugPixelMap = false;
	



};

