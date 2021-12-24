//#include "stdafx.h"
#include "ParticleManager.h"
#include "Image.h"

HRESULT ParticleManager::Init()
{
	/*deathEffect = ImageManager::GetSingleton()->FindImage("image/effect.bmp");
	if (deathEffect == nullptr)
	{
		return E_FAIL;
	}
	WeaponMapEffect = ImageManager::GetSingleton()->FindImage("image/weaponEffect.bmp");
	if (WeaponMapEffect == nullptr)
	{
		return E_FAIL;
	}*/

	
	return S_OK;
}

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

		for (int i = 0; i < vecEffects.size(); ++i)
		{
			if (vecEffects[i].EffectFrame.x == vecEffects[i].EffectMaxFrame)
			{
				vecEffects.erase(vecEffects.begin() + i);
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

// 함수하나로 호출하는법 생각하기
void ParticleManager::CallParticle(POINTFLOAT _pos)
{
	Particle tempParticl;
	tempParticl.pos = _pos;
	tempParticl.EffectFrame = { 0,0 };
	tempParticl.EffectMaxFrame = deathEffectMaxFrame;
	tempParticl.effect = ImageManager::GetSingleton()->FindImage("image/effect.bmp");
	vecEffects.push_back(tempParticl);

}

void ParticleManager::CallParticle(SubjectTag _subTag, POINTFLOAT _pos, MonsterType _monsterType)
{
	switch (_subTag)
	{
	case SubjectTag::PLAYER:
		break;
	case SubjectTag::MONSTER:
		switch (_monsterType)
		{
		case MonsterType::KONG:
			break;
		case MonsterType::MONKEY:
			break;
		case MonsterType::ENT:
			break;
		default:
			break;
		}
		break;
	case SubjectTag::ITEM:
		break;
	case SubjectTag::TRAP:
		break;
	case SubjectTag::PLATFORM:
		break;
	case SubjectTag::AMMO:
		switch (_monsterType)
		{
		case MonsterType::KONG:
			break;
		case MonsterType::ENT:
			break;
		default:
			break;
		}
		break;
	case SubjectTag::WEAPON:
		Particle tempParticl;
		tempParticl.pos = _pos;
		tempParticl.EffectFrame = { 0,0 };
		tempParticl.EffectMaxFrame = 3;
		tempParticl.effect = ImageManager::GetSingleton()->FindImage("image/weaponEffect.bmp");
		vecEffects.push_back(tempParticl);
		break;
	}
	
}
