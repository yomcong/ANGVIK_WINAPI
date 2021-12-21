#pragma once
#include "Config.h"
#include "Singleton.h"

struct Particle
{
	Image* effect = nullptr;
	POINTFLOAT pos = { 0,0 };
	POINT EffectFrame = { 0,0 };
	int EffectMaxFrame = 0;
};

class Image;
class ParticleManager : public Singleton<ParticleManager>
{
public:
	virtual ~ParticleManager() = default;

	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void CallParticle(POINTFLOAT _pos);
	void CallParticle(SubjectTag _subTag, POINTFLOAT _pos, MonsterType _monsterType = MonsterType::IDLE);
private:
	//Image* deathEffect = nullptr;
	//Image* WeaponMapEffect = nullptr;

	float frameCount = 0.0f;
	const int deathEffectMaxFrame = 5;
	const int WeaponMapEffectMaxFrame =3;
	//const int kongAmmoEffectMaxFrame = ;

	vector<Particle> vecEffects = {};
};

