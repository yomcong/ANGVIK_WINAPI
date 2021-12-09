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

	// 애니메이션 프레임
	POINT basicFrame = { 0,0 };
	POINT attackFrame = { 0,0 };
	
	Subject* subject = nullptr;

	// 총알
	AmmoManager* ammoManager = nullptr;
	// 타겟좌표
	Player* target = nullptr;

	const POINT attackMotionMaxFrame = { 8, 0 };
	const POINT basicMaxFrame = { 6, 0 };

	RECT rangeRect = {};

	// 충돌체크 함수로 제외할때 지역변수화 하기.
	RECT testRect = {};

	// 사정거리 디버깅
	bool DBRangeRect = false;

	float testElpsedCount = 0.0f;
	
	bool windowIn = false;
};

