#include "Ent.h"
#include "Player.h"
#include "Image.h"
#include "AmmoManager.h"

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
	attackEffect = ImageManager::GetSingleton()->FindImage("image/monster/�����_�Ѿ�.bmp");
	if (attackEffect == nullptr)
	{
		return E_FAIL;
	}
	R_attackEffect = ImageManager::GetSingleton()->FindImage("image/monster/R_�����_�Ѿ�.bmp");
	if (R_attackEffect == nullptr)
	{
		return E_FAIL;
	}
	
	ammoManager = new AmmoManager;
	ammoManager->Init(target);

	this->target = target;
	this->pos = pos;

	bodySize.x = 50;
	bodySize.y = 85;

	moveSpeed = 100.0f;

	shape.left = (int)pos.x - bodySize.x / 2;
	shape.top = (int)pos.y - bodySize.y / 2;
	shape.right = (int)pos.x + bodySize.x / 2;
	shape.bottom = (int)pos.y + bodySize.y / 2;
	
	dir = direction::RIGHT;
	

	renderPos = pos;

	return S_OK;
}

void Ent::Update()
{
	ammoManager->Update();
	// ����, ���� �غ� ���°� �ƴҰ�� �̵�
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

		// �Լ�ȭ �ϱ� 
		POINTFLOAT tempPos = MapColliderManager::GetSingleton()->
			Move(pos, shape, moveSpeed, (int)dir, bodySize);

		if (tempPos.x == 0.0f)
		{
			dir == direction::RIGHT ? dir = direction::LEFT : dir = direction::RIGHT;
		}

		pos.x += tempPos.x;
		pos.y += tempPos.y;
		// ------- 

	}

	// �ִϸ��̼� 
	frameCount += TimerManager().GetSingleton()->GetDeltaTime();

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
				ammoManager->EntFire(pos, (int)dir);

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
	// ----

	// pos ������Ʈ
	renderPos.x = pos.x - CameraManager::GetSingleton()->GetPos().x;
	renderPos.y = pos.y - CameraManager::GetSingleton()->GetPos().y;

	shape.left = (int)pos.x - bodySize.x / 2;
	shape.top = (int)pos.y - bodySize.y / 2;
	shape.right = (int)pos.x + bodySize.x / 2;
	shape.bottom = (int)pos.y + bodySize.y / 2;
	//  --------
	if (Input::GetButtonDown(VK_NUMPAD9))
	{
		DBrect == false ? DBrect = true : DBrect = false;
	}

}

void Ent::Render(HDC hdc)
{
	// ���� �Ǵ� �����غ� �����ϰ��
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

	ammoManager->Render(hdc);
	if (DBrect)
		Rectangle(hdc, shape.left - (int)CameraManager::GetSingleton()->GetPos().x,
			shape.top - (int)CameraManager::GetSingleton()->GetPos().y,
			shape.right - (int)CameraManager::GetSingleton()->GetPos().x,
			shape.bottom - (int)CameraManager::GetSingleton()->GetPos().y);
}

void Ent::Release()
{
	SAFE_RELEASE(ammoManager);
}