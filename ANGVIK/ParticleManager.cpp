#include "ParticleManager.h"
#include "Image.h"

HRESULT ParticleManager::Init()
{
	deathEffect = ImageManager::GetSingleton()->FindImage("image/effect.bmp");
	if (deathEffect == nullptr)
	{
		return E_FAIL;
	}

	return S_OK;
}

void ParticleManager::Update()
{
	frameCount += TimerManager().GetSingleton()->GetDeltaTime();

	if (frameCount > 0.0625)
	{
		for (int i = 0; i < vecDeathEffects.size(); ++i)
		{
			++vecDeathEffects[i].deathEffectFrame.x;
		}

		frameCount = 0.0f;

		if (vecDeathEffects.empty() == false && vecDeathEffects[vecDeathEffects.size() - 1].deathEffectFrame.x ==
			deathEffectMaxFrame.x)
		{
			vecDeathEffects.erase(vecDeathEffects.begin());
		}
	}

}

void ParticleManager::Render(HDC hdc)
{
	for (int i = 0; i < vecDeathEffects.size(); ++i)
	{
		vecDeathEffects[i].deathEffect->Render(hdc,
			(int)vecDeathEffects[i].pos.x - (int)CameraManager::GetSingleton()->GetPos().x, (int)vecDeathEffects[i].pos.y - (int)CameraManager::GetSingleton()->GetPos().y,
			vecDeathEffects[i].deathEffectFrame.x, vecDeathEffects[i].deathEffectFrame.y);
	}
}

void ParticleManager::Release()
{
	vecDeathEffects.clear();
}

void ParticleManager::CallParticle(POINTFLOAT pos)
{
	vecDeathEffects.reserve(vecDeathEffects.size()+1);
	vecDeathEffects.emplace_back();
	vecDeathEffects[vecDeathEffects.size() - 1].pos = pos;
	vecDeathEffects[vecDeathEffects.size() - 1].deathEffect = ImageManager::GetSingleton()->FindImage("image/effect.bmp");
}
