#pragma once
#include "Config.h"
#include "GameObject.h"

class Player;
class Image;
class EntAmmoManager;
class Ent : public GameObject
{
public:
	virtual ~Ent() = default;

	virtual HRESULT Init(Player* target, POINTFLOAT pos);
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

private:
	Image* basicEnt = nullptr;
	Image* entAttack = nullptr;
	Image* R_basicEnt = nullptr;
	Image* R_entAttack = nullptr;

	// �ִϸ��̼� ������
	POINT basicFrame = { 0,0 };
	POINT atackFrame = { 0,0 };

	// �Ѿ�
	EntAmmoManager* ammoManager = nullptr;
	// Ÿ����ǥ
	Player* target = nullptr;

	// �ƽ� ������
	const POINT attackMotionMaxFrame = { 6, 0 };
	const POINT basicMaxFrame = { 6, 0 };

	direction dir = direction::LEFT;


};

