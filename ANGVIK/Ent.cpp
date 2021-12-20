#include "Ent.h"
#include "Player.h"
#include "Image.h"
#include "EntAmmoManager.h"
#include "Subject.h"

HRESULT Ent::Init(Player* target, POINTFLOAT pos)
{
	basicEnt = ImageManager::GetSingleton()->FindImage("image/monster/Ent_move_6f.bmp");
	if (basicEnt == nullptr)
	{
		return E_FAIL;
	}
	entAttack = ImageManager::GetSingleton()->FindImage("image/monster/Ent_atk_6f.bmp");
	if (entAttack == nullptr)
	{
		return E_FAIL;
	}
	R_basicEnt = ImageManager::GetSingleton()->FindImage("image/monster/R_Ent_move_6f.bmp");
	if (R_basicEnt == nullptr)
	{
		return E_FAIL;
	}
	R_entAttack = ImageManager::GetSingleton()->FindImage("image/monster/R_Ent_atk_6f.bmp");
	if (R_entAttack == nullptr)
	{
		return E_FAIL;
	}
	attackEffect = ImageManager::GetSingleton()->FindImage("image/monster/모다피_총알.bmp");
	if (attackEffect == nullptr)
	{
		return E_FAIL;
	}
	R_attackEffect = ImageManager::GetSingleton()->FindImage("image/monster/R_모다피_총알.bmp");
	if (R_attackEffect == nullptr)
	{
		return E_FAIL;
	}
	/*deathEffect = ImageManager::GetSingleton()->FindImage("image/effect.bmp");
	if (deathEffect == nullptr)
	{
		return E_FAIL;
	}*/
	ammoManager = new EntAmmoManager;
	ammoManager->Init(target);

	this->target = target;
	this->pos = pos;

	b_isAlive = true;

	bodySize.x = 50;
	bodySize.y = 85;

	moveSpeed = 100.0f;

	shape.left = (int)pos.x - bodySize.x / 2;
	shape.top = (int)pos.y - bodySize.y / 2;
	shape.right = (int)pos.x + bodySize.x / 2;
	shape.bottom = (int)pos.y + bodySize.y / 2;

	dir = direction::RIGHT;

	subject = new Subject;

	renderPos = pos;

	return S_OK;
}

void Ent::Update()
{
	ammoManager->Update();
	

	// 행동(이동,공격)
	if (b_isAlive)
	{
		DoAction();
		PlayAnimation();
	}
	// 윈도우 영역에 있는지 확인
	PosUpdate();
	CheckWindow();
	// 애니메이션 
	// pos 업데이트
	
	// 디버깅
	if (Input::GetButtonDown(VK_NUMPAD9))
	{
		DBrect == false ? DBrect = true : DBrect = false;
	}

}

void Ent::Render(HDC hdc)
{
	ammoManager->Render(hdc);

	if (b_isAlive)
	{
		// 공격 또는 공격준비 상태일경우
		if (b_attackReady || b_attack)
		{
			if (dir == direction::RIGHT)
			{
				entAttack->Render(hdc, (int)renderPos.x, (int)renderPos.y, attackFrame.x, attackFrame.y);
			}
			else
			{
				R_entAttack->Render(hdc, (int)renderPos.x, (int)renderPos.y, attackFrame.x, attackFrame.y);
			}

			if (dir == direction::RIGHT)
			{
				entAttack->Render(hdc, (int)renderPos.x, (int)renderPos.y, attackFrame.x, attackFrame.y);
			}
			else
			{
				R_entAttack->Render(hdc, (int)renderPos.x, (int)renderPos.y, attackFrame.x, attackFrame.y);
			}

			if (b_attackReady)
			{
				if (dir == direction::RIGHT)
				{
					attackEffect->Render(hdc, (int)renderPos.x + 15, (int)renderPos.y + 10, attackEffectFrame.x, attackEffectFrame.y);
				}
				else
				{
					R_attackEffect->Render(hdc, (int)renderPos.x - 15, (int)renderPos.y + 10, attackEffectFrame.x, attackEffectFrame.y);
				}
			}
		}
		else
		{
			if (dir == direction::RIGHT)
			{
				basicEnt->Render(hdc, (int)renderPos.x, (int)renderPos.y, basicFrame.x, basicFrame.y);
			}
			else
			{
				R_basicEnt->Render(hdc, (int)renderPos.x, (int)renderPos.y, basicFrame.x, basicFrame.y);
			}
		}
		if (DBrect)
			Rectangle(hdc, shape.left - (int)CameraManager::GetSingleton()->GetPos().x,
				shape.top - (int)CameraManager::GetSingleton()->GetPos().y,
				shape.right - (int)CameraManager::GetSingleton()->GetPos().x,
				shape.bottom - (int)CameraManager::GetSingleton()->GetPos().y);
	}
	/*else
	{
		deathEffect->Render(hdc, (int)renderPos.x, (int)renderPos.y, deathEffectFrame.x, deathEffectFrame.y);
	}*/

}

void Ent::Release()
{
	SAFE_RELEASE(ammoManager);
	SAFE_DELETE(subject);
}

void Ent::PlayAnimation()
{
	frameCount += TimerManager().GetSingleton()->GetDeltaTime();

	if (b_isAlive)
	{
		if (frameCount > 0.125)
		{
			if (b_attackReady)
			{
				if (false == (attackFrame.x == attackMaxFrame.x))
				{
					++attackFrame.x;
				}

				if (attackEffectFrame.x <= 0)
				{
					b_attack = true;
					b_attackReady = false;
					attackEffectFrame.x = attackEffectMaxFrame.x;
					ammoManager->Fire(pos, (int)dir);

				}
				else
				{
					--attackEffectFrame.x;
				}

			}
			else if (b_attack)
			{
				if (attackEffectFrame.x == 0)
				{
					b_attack = false;
					basicFrame.x = 0;
				}
				else
				{
					--attackEffectFrame.x;
				}
			}
			else
			{
				if (basicFrame.x == basicMaxFrame.x)
				{
					basicFrame.x = 0;
				}
				else
				{
					++basicFrame.x;
				}

			}

			frameCount = 0.0f;
		}
	}
	/*else
	{
		if (frameCount > 0.0625)
		{
			if (deathEffectFrame.x == deathEffectMaxFrame.x)
			{
				deathEffectFrame.x = 0;
			}
			else
			{
				++deathEffectFrame.x;
			}
			frameCount = 0.0f;
		}
	}*/
}

void Ent::PosUpdate()
{
	renderPos.x = pos.x - CameraManager::GetSingleton()->GetPos().x;
	renderPos.y = pos.y - CameraManager::GetSingleton()->GetPos().y;

	shape.left = (int)pos.x - bodySize.x / 2;
	shape.top = (int)pos.y - bodySize.y / 2;
	shape.right = (int)pos.x + bodySize.x / 2;
	shape.bottom = (int)pos.y + bodySize.y / 2;
}

void Ent::ToBeHit()
{
	if (b_isAlive)
	{
		ParticleManager::GetSingleton()->CallParticle(pos);
		b_isAlive = false;
	}
}

void Ent::CheckWindow()
{
	if (renderPos.x > 0 && renderPos.x < WIN_SIZE_X &&
		renderPos.y > 0 && renderPos.y < WIN_SIZE_Y)
	{
		if (false == windowIn)
		{
			subject->Notify(subject, myType, subTag, EventTag::INWINDOW);
			windowIn = true;
		}
	}
	else
	{
		if (windowIn)
		{
			subject->Notify(subject, myType, subTag, EventTag::OUTWINDOW);
			windowIn = false;
		}
	}
}

void Ent::DoAction()
{
	// 공격, 공격 준비 상태가 아닐경우 이동
	if (false == (b_attackReady || b_attack))
	{
		if (MapColliderManager::GetSingleton()->IsFalling(pos, shape, moveSpeed, bodySize))
		{
			pos.y += 3.0f;
		}
		else
		{
			attackDeley += TimerManager().GetSingleton()->GetDeltaTime();
			if (attackDeley > 1.0)
			{
				b_attackReady = true;
				attackFrame.x = 0;
				attackDeley = 0.0f;
				attackEffectFrame.x = attackEffectMaxFrame.x;
			}
		}

		POINTFLOAT tempPos = MapColliderManager::GetSingleton()->
			Move(pos, shape, moveSpeed, (int)dir, bodySize);

		if (tempPos.x == 0.0f)
		{
			dir == direction::RIGHT ? dir = direction::LEFT : dir = direction::RIGHT;
		}

		pos.x += tempPos.x;
		pos.y += tempPos.y;

		if (CollisionManager::GetSingleton()->CheckCollision(subTag, shape))
		{
			ToBeHit();
		}

	}
}
