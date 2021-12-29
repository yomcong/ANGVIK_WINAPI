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

	void Update();
	void Render(HDC hdc);
	void Release();

	void CallParticle(SubjectTag _subTag, POINTFLOAT _pos, int _dir = 1, MonsterType _monsterType = MonsterType::IDLE);
private:
	float frameCount = 0.0f;

	const int deathEffectMaxFrame = 5;
	const int WeaponMapEffectMaxFrame =3;
	const int kongAmmoEffectMaxFrame = 5;

	vector<Particle> vecEffects = {};
};

