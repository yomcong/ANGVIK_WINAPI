#pragma once
#include "Config.h"
#include "Singleton.h"

struct Particle
{
	Image* deathEffect = nullptr;
	POINTFLOAT pos = { 0,0 };
	POINT deathEffectFrame = { 0,0 };
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

	void CallParticle(POINTFLOAT pos);
private:
	Image* deathEffect = nullptr;

	float frameCount = 0.0f;
	const POINT deathEffectMaxFrame = { 5,0 };

	vector<Particle> vecDeathEffects = {};
};

