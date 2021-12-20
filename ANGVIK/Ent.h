#pragma once
#include "Config.h"
#include "GameObject.h"

class Player;
class Image;
class Subject;
class EntAmmoManager;
class Ent : public GameObject
{
public:
	virtual ~Ent() = default;

	virtual HRESULT Init(Player* target, POINTFLOAT pos);
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
	//Image* deathEffect = nullptr;


	// �ִϸ��̼� ������
	POINT basicFrame = { 0,0 };
	POINT attackFrame = { 0,0 };
	POINT attackEffectFrame = { 6, 0 };
	//POINT deathEffectFrame = { 0,0 };

	// �Ѿ�
	EntAmmoManager* ammoManager = nullptr;
	// Ÿ����ǥ
	Player* target = nullptr;

	// �ƽ� ������
	const POINT attackMaxFrame = { 5, 0 };
	const POINT basicMaxFrame = { 5, 0 };
	const POINT attackEffectMaxFrame = { 6, 0 };
	//const POINT deathEffectMaxFrame = { 5,0 };
	// ���� , ���� �غ� ���
	bool b_attackReady = false;
	bool b_attack = false;
	
	// ���� ������
	float attackDeley = 0.0f;

	Subject* subject = nullptr;

	SubjectTag subTag = SubjectTag::MONSTER;
	MonsterType myType = MonsterType::ENT;

	bool windowIn = false;

};

