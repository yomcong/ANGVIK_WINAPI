#pragma once
#include "Config.h"
#include "GameObject.h"
#include "Observer.h"

class Image;
class Player;
class AmmoManager;
class Subject;
class Kong : public GameObject, public Observer
{
public:
	virtual ~Kong() = default;

	virtual HRESULT Init(Player* target, POINTFLOAT pos);
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	virtual void OnNotify(Subject* subject, SubjectTag subjectTag, EventTag eventTag) override;
	Subject* GetSubject() { return subject; }

private:
	Image* attackMotion = nullptr;
	Image* basicMotion = nullptr;
	Image* R_attackMotion = nullptr;
	Image* R_basicMotion = nullptr;

	// �ִϸ��̼� ������
	POINT basicFrame = { 0,0 };
	POINT attackFrame = { 0,0 };
	
	Subject* subject = nullptr;

	// �Ѿ�
	AmmoManager* ammoManager = nullptr;
	// Ÿ����ǥ
	Player* target = nullptr;

	const POINT attackMotionMaxFrame = { 8, 0 };
	const POINT basicMaxFrame = { 6, 0 };

	RECT rangeRect = {};

	// �浹üũ �Լ��� �����Ҷ� ��������ȭ �ϱ�.
	RECT testRect = {};

	// �����Ÿ� �����
	bool DBRangeRect = false;

	float testElpsedCount = 0.0f;
	
	bool windowIn = false;
};

