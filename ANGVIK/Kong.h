#pragma once
#include "Config.h"
#include "GameObject.h"

class Image;
class Player;
class KongAmmoManager;
class Kong : public GameObject
{
public:
	virtual ~Kong() = default;

	virtual HRESULT Init(Player* target, POINTFLOAT pos);
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();


private:
	Image* attackMotion = nullptr;
	Image* basicMotion = nullptr;
	Image* R_attackMotion = nullptr;
	Image* R_basicMotion = nullptr;

	// �ִϸ��̼� ������
	POINT basicFrame = { 0,0 };
	POINT atackFrame = { 0,0 };

	// �Ѿ�
	KongAmmoManager* ammoManager = nullptr;
	// Ÿ����ǥ
	Player* target = nullptr;

	const POINT attackMotionMaxFrame = { 8, 0 };
	const POINT basicMaxFrame = { 6, 0 };

	// �浹üũ �Լ��� �����Ҷ� ��������ȭ �ϱ�.
	RECT testRect = {};


	direction dir = direction::LEFT;
	// �����Ÿ� �����
	bool DBRangeRect = false;

	float testElpsedCount = 0.0f;
	

};

