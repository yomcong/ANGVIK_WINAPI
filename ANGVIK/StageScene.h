#pragma once
#include "GameEntity.h"
#include "Config.h"

//enum class PlayerAction{ NORMAL, JUMP, ATTACK, HIT };

//struct Player
//{
//	POINTFLOAT pos = {};
//	RECT collider = {};
//	int bodySize_X = 0;
//	int bodySize_Y = 0;
//	PlayerAction action = PlayerAction::NORMAL;
//};
//

class Player;
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

	// ÇÈ¼¿ Ãæµ¹
	COLORREF color = {};
	WORD r, g, b = {};

	bool debugPixelMap = false;
	



};

