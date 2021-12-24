#pragma once
#include "Config.h"
#include "GameObject.h"

class Image;
class Subject;
class AmmoManager;
class Ent : public GameObject
{
public:
	virtual ~Ent() = default;

	virtual HRESULT Init(POINTFLOAT pos, AmmoManager* _ammoManager);
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	void PlayAnimation();
	void PosUpdate();
	void ToBeHit();
	void CheckWindow();
	void DoAction();

	Subject* GetSubject() { return subject; }

private:
	Image* basicEnt = nullptr;
	Image* entAttack = nullptr;
	Image* R_basicEnt = nullptr;
	Image* R_entAttack = nullptr;
	Image* attackEffect = nullptr;
	Image* R_attackEffect = nullptr;


	// �ִϸ��̼� ������
	POINT basicFrame = { 0,0 };
	POINT attackFrame = { 0,0 };
	POINT attackEffectFrame = { 6, 0 };

	// �Ѿ�
	AmmoManager* ammoManager = nullptr;
	// Ÿ����ǥ
	Player* target = nullptr;

	// �ƽ� ������
	const POINT attackMaxFrame = { 5, 0 };
	const POINT basicMaxFrame = { 5, 0 };
	const POINT attackEffectMaxFrame = { 6, 0 };
	// ���� , ���� �غ� ���
	bool b_attackReady = false;
	bool b_attack = false;
	
	// ���� ������
	float attackDeley = 0.0f;

	Subject* subject = nullptr;

	SubjectTag subTag = SubjectTag::MONSTER;
	MonsterType myType = MonsterType::ENT;

	bool b_windowIn = false;

};

