//#include "stdafx.h"
#include "ParticleManager.h"
#include "Image.h"

//HRESULT ParticleManager::Init()
//{
//	
//	return S_OK;
//}

void ParticleManager::Update()
{
	frameCount += Timer::GetDeltaTime();

	if (frameCount > 0.0625)
	{
		for (int i = 0; i < vecEffects.size(); ++i)
		{
			++vecEffects[i].EffectFrame.x;
			if (vecEffects[i].EffectFrame.x == vecEffects[i].EffectMaxFrame)
			{
				vecEffects.erase(vecEffects.begin() + i);
			}
		}

		frameCount = 0.0f;

		for (int i = 0; i < vecEffects.size();)
		{
			if (vecEffects[i].EffectFrame.x == vecEffects[i].EffectMaxFrame)
			{
				vecEffects.erase(vecEffects.begin() + i);
			}
			else
			{
				++i;
			}
		}
	}

}

void ParticleManager::Render(HDC hdc)
{
	for (int i = 0; i < vecEffects.size(); ++i)
	{
		vecEffects[i].effect->Render(hdc,
			(int)vecEffects[i].pos.x - (int)CameraManager::GetSingleton()->GetPos().x, (int)vecEffects[i].pos.y - (int)CameraManager::GetSingleton()->GetPos().y,
			vecEffects[i].EffectFrame.x, vecEffects[i].EffectFrame.y);
	}
}

void ParticleManager::Release()
{
	vecEffects.clear();
}

void ParticleManager::CallParticle(SubjectTag _subTag, POINTFLOAT _pos, int _dir , MonsterType _monsterType)
{
	switch (_subTag)
	{
	case SubjectTag::PLAYER:
		break;
	case SubjectTag::MONSTER:
		vecEffects.emplace_back();
		vecEffects[vecEffects.size() - 1].pos = _pos;
		vecEffects[vecEffects.size() - 1].EffectMaxFrame = deathEffectMaxFrame;
		vecEffects[vecEffects.size() - 1].effect = ImageManager::GetSingleton()->FindImage("image/effect.bmp");
		break;
	case SubjectTag::ITEM:
		break;
	case SubjectTag::TRAP:
		break;
	case SubjectTag::PLATFORM:
		break;
	case SubjectTag::AMMO:
		vecEffects.emplace_back();
		vecEffects[vecEffects.size() - 1].pos = _pos;
		vecEffects[vecEffects.size() - 1].EffectMaxFrame = kongAmmoEffectMaxFrame;
		if (_dir > 0)
		{
			vecEffects[vecEffects.size() - 1].effect = ImageManager::GetSingleton()->FindImage("image/monster/¸ð´ÙÇÇ_ÃÑ¾Ë.bmp");
		}
		else
		{
			vecEffects[vecEffects.size() - 1].effect = ImageManager::GetSingleton()->FindImage("image/monster/R_¸ð´ÙÇÇ_ÃÑ¾Ë.bmp");
		}
		break;
	case SubjectTag::WEAPON:
		vecEffects.emplace_back();
		vecEffects[vecEffects.size() - 1].pos = _pos;
		vecEffects[vecEffects.size() - 1].EffectMaxFrame = WeaponMapEffectMaxFrame;
		vecEffects[vecEffects.size() - 1].effect = ImageManager::GetSingleton()->FindImage("image/weaponEffect.bmp");
		break;
	}
	
}
