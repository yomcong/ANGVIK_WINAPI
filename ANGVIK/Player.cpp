#include "Player.h"
#include "Image.h"
#include "TrapManager.h"
#include "MonsterManager.h"

// ĳ���� �̵�
// �� �ڿ������� ���ֱ�
// ���� �Ź� ��ġ ����
// ĳ���� ��Ʈ ����ȭ ���ֱ�(���� �Ӹ� ��)
// ��Ʈ ����ȭ �� �� �κ����� �ȼ��浹�ٽ�

// ĳ���Ͱ� ������������ ���� ���� �ٲ��ֱ� ( ������ �������̰�) �� �̹��� ����ȸ��  -- O

// ī�޶� ������ ���� ������ �����������ֱ�	-- O 
// -> ��ŸŸ������ ĳ���͸� �̵���Ű�� �Ҽ����� �޶����� ����ȭ ���ã��

// ��ŸŸ�� ������Ű��....

// �������� y���� ���ҵǸ� ī�޶� ȭ�鳡���־ �ö� -- O

#define JumpPower 90.0f

#define StartPosX 120.0f
#define StartPosY 325.0f
#define StartPointX 300.0f
#define StartPointY 350.0f

// �׽�Ʈ�� �Ű�����
HRESULT Player::Init()
{
	if (false == FindImage())
	{
		return E_FAIL;
	}

	pos.x = StartPosX;
	pos.y = StartPosY;

	renderPos = pos;

	moveSpeed = 175.0f;

	bodySize.x = 20;
	bodySize.y = 50;

	shape.left = (int)pos.x - (bodySize.x / 2);
	shape.top = (int)pos.y - (bodySize.y / 2);
	shape.right = (int)pos.x + (bodySize.x / 2);
	shape.bottom = (int)pos.y + (bodySize.y / 2);

	return S_OK;
}

void Player::Update()
{
	CollisionManager::GetSingleton()->CheckCollision(subTag, shape);

	// �������°� �ƴҰ��
	if (false == (state == State::JUMP))
	{
		// ��������(�̵�+����) �ϰ�� ������Ʈ�� ��� �ٲ��ָ鼭 �ִϸ��̼��� ������ ���ڿ���������. ���ľ���
		// �׽�Ʈ�� Ʈ�� �浹üũ ����ȭ �ϱ�
		if (MapColliderManager::GetSingleton()->IsFalling(pos, shape, moveSpeed, bodySize)
			&& b_platform == false)
		{
			ChangeState(State::Fall);

			// ī�޶� ��������
			if (renderPos.y < StartPointY)
			{
				renderPos.y += 3.0f;
			}
			else
			{
				CameraManager::GetSingleton()->SetPosY(3);
			}
		}
		else
		{
			// ���� �ڼ��� �ƴҰ�쿡�� �⺻�ڼ�
			if (false == (state == State::SITDOWN))
			{
				ChangeState(State::IDLE);
			}
		}
	}
	// ���� ����
	else
	{
		// ������ �浹�˻�
		if (MapColliderManager::GetSingleton()->Jump(pos, shape, moveSpeed, bodySize))
		{
			// ī�޶� ��������
			if (CameraManager::GetSingleton()->GetPos().y <= 100)
			{
				renderPos.y -= 3.0f;
			}
			else
			{
				CameraManager::GetSingleton()->SetPosY(-3);
			}

			jumpPower -= moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();

			if (jumpPower <= 0)
			{
				ChangeState(State::Fall);
			}
		}
		else
		{
			jumpPower = 0;
			ChangeState(State::Fall);
		}
	}

	// �ִϸ��̼������� 
	DoAnimation();
	// ������ ������Ʈ
	PosUpdate();

	//�÷��̾� �̵� 
	if (false == (state == State::SITDOWN))
	{
		if (Input::GetButton(VK_LEFT))
		{
			// ī�޶� ��������
			if (CameraManager::GetSingleton()->GetPos().x <= 0)
			{
				renderPos.x += MapColliderManager::GetSingleton()->
					Move(pos, shape, moveSpeed, -1, bodySize).x;
				renderPos.y += MapColliderManager::GetSingleton()->
					Move(pos, shape, moveSpeed, -1, bodySize).y;
			}
			else
			{
				POINTFLOAT tempPos = MapColliderManager::GetSingleton()->
					Move(pos, shape, moveSpeed, -1, bodySize);
				CameraManager::GetSingleton()->SetPosX(tempPos.x);
				renderPos.y += tempPos.y;
			}
			// ���� ����
			ChangeAction(Action::LEFTMOVE);
			dir = direction::LEFT;
		}
		if (Input::GetButton(VK_RIGHT))
		{
			// ������ �� ����ó�� �ؾ���
			if (renderPos.x < StartPointX)
			{
				renderPos.x += 3.0f;
			}
			else
			{
				POINTFLOAT tempPos = MapColliderManager::GetSingleton()->
					Move(pos, shape, moveSpeed, 1, bodySize);

				CameraManager::GetSingleton()->SetPosX(tempPos.x);
				renderPos.y += tempPos.y;
			}

			// ���� ����
			ChangeAction(Action::RIGHTMOVE);
			dir = direction::RIGHT;
		}
		if (Input::GetButton(VK_UP))
		{
			// �������̰ų� ���ϻ��°� �ƴ� ���
			if (false == (state == State::JUMP) &&
				false == (state == State::Fall))
			{
				ChangeState(State::JUMP);
				jumpPower = JumpPower;
			}
		}
	}
	else
	{
		if (!Input::GetButton(VK_DOWN))
		{
			CollisionManager::GetSingleton()->CheckItem(shape);
			ChangeState(State::IDLE);
		}
	}

	// ���� �ε巴�� + ĳ���� ���� ���� ����
	if (Input::GetButton(VK_DOWN))
	{
		// �������̰ų� ���ϻ��°� �ƴҰ��
		if (false == (state == State::JUMP) &&
			false == (state == State::Fall))
		{
			ChangeState(State::SITDOWN);
		}
	}

	// �׼����� �ƴҶ� �⺻�ڼ� ���Ŀ� ���� ������ ����
	if (!Input::GetButton(VK_LEFT) &&
		!Input::GetButton(VK_RIGHT) &&
		false == (state == State::SITDOWN) &&
		false == (state == State::Fall) &&
		false == (state == State::JUMP))
	{
		action = Action::IDLE;

		frontArmFrame.x = 11;
		frontArmFrame.y = 0;

		backArmFrame.x = 13;
		backArmFrame.y = 0;

		bodyFrame.y = 0;
		bodyFrame.x = 0;
	}


	//����׿� ��ü����
#ifdef _DEBUG
	// ������
	/*if (KeyManager::GetSingleton()->IsOnceKeyDown('Y'))
		if (DBarmPos.y == 2)
			DBarmPos.y = 0;
		else
			++DBarmPos.y;
	if (KeyManager::GetSingleton()->IsOnceKeyDown('H'))
		if (DBarmPos.y == 0)
			DBarmPos.y = 2;
		else
			--DBarmPos.y;
	if (KeyManager::GetSingleton()->IsOnceKeyDown('U'))
		if (DBarmPos.x == 15)
			DBarmPos.x = 0;
		else
			++DBarmPos.x;
	if (KeyManager::GetSingleton()->IsOnceKeyDown('J'))
		if (DBarmPos.x == 0)
			DBarmPos.x = 15;
		else
			--DBarmPos.x;
	if (KeyManager::GetSingleton()->IsOnceKeyDown('I'))
		if (DBbodyPos.x == 11)
			DBbodyPos.x = 0;
		else
			++DBbodyPos.x;
	if (KeyManager::GetSingleton()->IsOnceKeyDown('K'))
		if (DBbodyPos.x == 0)
			DBbodyPos.x = 11;
		else
			--DBbodyPos.x;
	if (KeyManager::GetSingleton()->IsOnceKeyDown('O'))
		if (DBbodyPos.y == 1)
			DBbodyPos.y = 0;
		else
			++DBbodyPos.y;
	if (KeyManager::GetSingleton()->IsOnceKeyDown('L'))
		if (DBbodyPos.y == 0)
			DBbodyPos.y = 1;
		else
			--DBbodyPos.y;*/
#endif
			// ����׿� ĳ���� ��Ʈǥ��
	if (Input::GetButtonDown(VK_NUMPAD9))
	{
		DBrect == false ? DBrect = true : DBrect = false;
	}

}

void Player::Render(HDC hdc)
{
	if (invisibleTime > 0 && b_invisible)
	{
		// �ǰݽ� �������� ->�׷����� �ʴ´�.
	}
	else
	{
		// �ݴ����� ���������Ƿ� back, front �� �ݴ�
		if (dir == direction::LEFT)
		{
			if (b_equipBackWeapon)
			{
				backWeapon->Render(hdc, (int)frontArmPos.x - 10, (int)frontArmPos.y -10, backWeaponFrame.x, backWeaponFrame.y);
			}
			
			R_backArm->Render(hdc, (int)frontArmPos.x, (int)frontArmPos.y, backArmFrame.x, backArmFrame.y);	// ����

			R_body->Render(hdc, (int)bodyPos.x, (int)bodyPos.y, bodyFrame.x, bodyFrame.y);			// ��
			if (b_equipArmor)
			{
				R_armor->Render(hdc, (int)bodyPos.x, (int)bodyPos.y, bodyFrame.x, bodyFrame.y);
			}
			if (b_equipShoes)
			{
				R_shoes->Render(hdc, (int)bodyPos.x, (int)bodyPos.y, bodyFrame.x, bodyFrame.y);
			}

			R_head->Render(hdc, (int)headPos.x, (int)headPos.y);								// �Ӹ�
			if (b_equipHelmet)
			{

			}
			if (b_equipFrontWeapon)
			{
				frontWeapon->Render(hdc, (int)frontArmPos.x, (int)frontArmPos.y, frontWeaponFrame.x, frontWeaponFrame.y);
			}
			R_frontArm->Render(hdc, (int)backArmPos.x, (int)backArmPos.y, frontArmFrame.x, frontArmFrame.y);// ������
			
		}
		else
		{
			if (b_equipBackWeapon)
			{
				backWeapon->Render(hdc, (int)frontArmPos.x+20, (int)frontArmPos.y-10, backWeaponFrame.x, backWeaponFrame.y);
			}
			backArm->Render(hdc, (int)backArmPos.x, (int)backArmPos.y, backArmFrame.x, backArmFrame.y);
			body->Render(hdc, (int)bodyPos.x, (int)bodyPos.y, bodyFrame.x, bodyFrame.y);
			if (b_equipArmor)
			{
				armor->Render(hdc, (int)bodyPos.x, (int)bodyPos.y, bodyFrame.x, bodyFrame.y);
			}
			if (b_equipShoes)
			{
				shoes->Render(hdc, (int)bodyPos.x, (int)bodyPos.y, bodyFrame.x, bodyFrame.y);
			}

			head->Render(hdc, (int)headPos.x, (int)headPos.y);
			if (b_equipHelmet)
			{

			}

			frontArm->Render(hdc, (int)frontArmPos.x, (int)frontArmPos.y, frontArmFrame.x, frontArmFrame.y);
			if (b_equipFrontWeapon)
			{
				frontWeapon->Render(hdc, (int)frontArmPos.x, (int)frontArmPos.y, frontWeaponFrame.x, frontWeaponFrame.y);
			}
		}
	}

	//--�����--
	if (DBrect)
	{
		Rectangle(hdc, shape.left - (int)CameraManager::GetSingleton()->GetPos().x,
			shape.top - (int)CameraManager::GetSingleton()->GetPos().y,
			shape.right - (int)CameraManager::GetSingleton()->GetPos().x,
			shape.bottom - (int)CameraManager::GetSingleton()->GetPos().y);

		Rectangle(hdc, 320, 90, 340, 115);	// ���� ��Ʈ
		Rectangle(hdc, 325, 115, 335, 125);	// �Ź� ��Ʈ

		DBbackArm->Render(hdc, 100, 100, DBarmPos.x, DBarmPos.y);
		DBfrontArm->Render(hdc, 200, 100, DBarmPos.x, DBarmPos.y);
		DBbody->Render(hdc, 300, 100, DBbodyPos.x, DBbodyPos.y);
		DBhead0->Render(hdc, 450, 100);
		DBhead1->Render(hdc, 500, 100);
		DBhead2->Render(hdc, 550, 100);
		DBhead3->Render(hdc, 600, 100);

		DBgoldBody->Render(hdc, 350, 100, DBbodyPos.x, DBbodyPos.y);
		DBgoldFoot->Render(hdc, 350, 100, DBbodyPos.x, DBbodyPos.y);
	}

}

void Player::Release()
{

}

void Player::ChangeAction(Action action)
{
	if (this->action == action)
	{
		return;
	}
	else
	{
		// ���ο� �׼��ϰ�� �ִϸ��̼ǵ� �⺻���·� ����
		this->action = action;


		frameCount = 0.0f;
		// �������϶��� ���굿�� X
		if ((action == Action::RIGHTMOVE || action == Action::LEFTMOVE))
		{
			b_frontArmMove = true;
			b_backArmMove = true;
			frontArmFrame.x = 9;
			backArmFrame.x = 11;
			bodyFrame.y = 1;
			frontArmFrame.y = 1;
			backArmFrame.y = 1;
		}
	}
}

void Player::ChangeState(State state)
{
	if (this->state == state)
	{
		return;
	}
	else
	{
		this->state = state;

		if (state == State::IDLE)
		{
			b_frontArmMove = true;
			b_backArmMove = true;
			frontArmFrame.x = 9;
			backArmFrame.x = 11;
			bodyFrame.y = 1;
			frontArmFrame.y = 0;
			backArmFrame.y = 0;
		}
		else if (state == State::JUMP)
		{
			b_frontArmMove = true;
			b_backArmMove = true;
			frontArmFrame.x = 11;
			backArmFrame.x = 14;
			bodyFrame.x = 0;
			bodyFrame.y = 0;
			frontArmFrame.y = 0;
			backArmFrame.y = 0;
		}
		else if (state == State::Fall)
		{
			frontArmFrame.x = 9;
			backArmFrame.x = 14;
			bodyFrame.x = 2;
			bodyFrame.y = 0;
			frontArmFrame.y = 0;
			backArmFrame.y = 0;
		}
		else if (state == State::HIT)
		{

		}
		else if (state == State::SITDOWN)
		{
			if (action == Action::LEFTMOVE)
			{
				headPos.x -= 5;
			}
			else
			{
				headPos.x += 5;
			}

			headPos.y += 15;

			frontArmPos.y += 5;

			frontArmFrame.x = 9;
			backArmFrame.x = 13;

			bodyFrame.x = 3;
			bodyFrame.y = 0;

			frontArmFrame.y = 0;
			backArmFrame.y = 0;
		}
	}

}

void Player::DoAnimation()
{
	frameCount += TimerManager::GetSingleton()->GetDeltaTime();

	if (state == State::IDLE)
	{
		if (action == Action::LEFTMOVE ||
			action == Action::RIGHTMOVE)
		{
			if (frameCount > 0.0625)
			{
				// ������ �����Ӱ���
				if (b_frontArmMove)
				{
					if (frontArmFrame.x == frontArmMaxFrame.x)
					{
						--frontArmFrame.x;
						b_frontArmMove = false;
					}
					else
					{
						++frontArmFrame.x;
					}
				}
				else
				{
					if (frontArmFrame.x == 9)
					{
						++frontArmFrame.x;
						b_frontArmMove = true;
					}
					else
					{
						--frontArmFrame.x;
					}

				}
				// �޼� ������ ����
				if (b_backArmMove)
				{
					if (backArmFrame.x == backArmMaxFrame.x)
					{
						--backArmFrame.x;
						b_backArmMove = false;
					}
					else
					{
						++backArmFrame.x;
					}
				}
				else
				{
					if (backArmFrame.x == 11)
					{
						++backArmFrame.x;
						b_backArmMove = true;
					}
					else
					{
						--backArmFrame.x;
					}
				}
				// ��,�� ������ ����
				if (bodyFrame.x == bodyMaxFrame.x)
				{
					bodyFrame.x = 0;
				}
				else
				{
					++bodyFrame.x;
				}

				frameCount = 0.0f;
			}
		}
		else
		{
			frameCount = 0.0f;
		}
	}
	else if (state == State::JUMP)
	{
		if (frameCount > 0.25)
		{
			// ������ �����Ӱ���
			if (b_frontArmMove)
			{
				if (frontArmFrame.x == 9)
				{
					++frontArmFrame.x;
					b_frontArmMove = false;
				}
				else
				{
					--frontArmFrame.x;
				}
			}
			else
			{
				if (frontArmFrame.x == 11)
				{
					--frontArmFrame.x;
					b_frontArmMove = true;
				}
				else
				{
					++frontArmFrame.x;
				}
			}
			bodyFrame.x = 1;

			frameCount = 0.0f;
		}

	}
	else if (state == State::Fall)
	{
		if (frameCount > 0.25)
		{
			// ������ �����Ӱ���
			if (frontArmFrame.x < 13)
			{
				++frontArmFrame.x;
			}

			frameCount = 0.0f;
		}
	}
	else if (state == State::SITDOWN)
	{
		if (frameCount > 0.5)
		{
			if (false == sitDownCamera)
			{
				renderPos.y -= 200;
				CameraManager::GetSingleton()->SetPosY(+200);
				sitDownCamera = true;
			}

			frameCount = 0.0f;
		}
	}

	if (invisibleTime > 0)
	{
		invisibleTime -= TimerManager::GetSingleton()->GetDeltaTime();
		invisibleCount += TimerManager::GetSingleton()->GetDeltaTime();
		if (invisibleTime > 1)
		{
			if (invisibleCount > 0.15625)
			{
				b_invisible == true ? b_invisible = false : b_invisible = true;
				invisibleCount = 0.0f;
			}
		}
		else
		{
			if (invisibleCount > 0.078125)
			{
				b_invisible == true ? b_invisible = false : b_invisible = true;
				invisibleCount = 0.0f;
			}
		}
	}
	else
	{
		b_invisible = false;
		invisibleCount = 0.0f;
	}
}

bool Player::CheckCollision(SubjectTag subject, RECT shape)
{
	RECT tempRect;
	bool temp = false;

	if (IntersectRect(&tempRect, &shape, &this->shape))
	{
		if (tempRect.left >= shape.left &&
			tempRect.right <= shape.right &&
			(((shape.top + shape.bottom) / 2) + shape.top) / 2 > tempRect.bottom)
		{
			temp = true;
		}
		else
		{
			temp = false;
		}

		switch (subject)
		{
		case SubjectTag::IDLE:
			break;
		case SubjectTag::MONSTER:
			if (temp == false)
			{
				ToBeHit();
			}
			break;
		case SubjectTag::ITEM:
			break;
		case SubjectTag::PLATFORM:
			if (temp)
			{
				return true;
			}
			else
			{
				b_platform = false;
				return false;
			}
			break;
		case SubjectTag::TRAP:
			break;
		case SubjectTag::Ammo:
			ToBeHit();
			break;
		}
		return true;
	}

	return false;

}

void Player::ToStepOn()
{
	ChangeState(State::JUMP);
	jumpPower = 50;
}

void Player::ToBeHit()
{
	if (invisibleTime <= 0)
	{
		// ����, hp ó�����ֱ�
		ChangeState(State::HIT);
		invisibleTime = 2.0f;
		b_invisible = true;
	}
}

bool Player::FindImage()
{
	backArm = ImageManager::GetSingleton()->FindImage("image/player/unarmed/arm_back.bmp");
	if (backArm == nullptr)
	{
		return false;
	}
	frontArm = ImageManager::GetSingleton()->FindImage("image/player/unarmed/arm_front.bmp");
	if (frontArm == nullptr)
	{
		return false;
	}
	body = ImageManager::GetSingleton()->FindImage("image/player/unarmed/body.bmp");
	if (body == nullptr)
	{
		return false;
	}
	head = ImageManager::GetSingleton()->FindImage("image/player/unarmed/head_1.bmp");
	if (head == nullptr)
	{
		return false;
	}
	R_body = ImageManager::GetSingleton()->FindImage("image/player/unarmed/R_body.bmp");
	if (R_body == nullptr)
	{
		return false;
	}
	R_backArm = ImageManager::GetSingleton()->FindImage("image/player/unarmed/R_arm_back.bmp");
	if (R_backArm == nullptr)
	{
		return false;
	}
	R_frontArm = ImageManager::GetSingleton()->FindImage("image/player/unarmed/R_arm_front.bmp");
	if (R_frontArm == nullptr)
	{
		return false;
	}
	R_head = ImageManager::GetSingleton()->FindImage("image/player/unarmed/R_head_1.bmp");
	if (R_head == nullptr)
	{
		return false;
	}
	/*armor = ImageManager::GetSingleton()->FindImage("image/player/gold/body.bmp");
	if (armor == nullptr)
	{
		return false;
	}
	shoes = ImageManager::GetSingleton()->FindImage("image/player/gold/foot.bmp");
	if (shoes == nullptr)
	{
		return false;
	}
	R_armor = ImageManager::GetSingleton()->FindImage("image/player/gold/R_body.bmp");
	if (R_armor == nullptr)
	{
		return false;
	}
	R_shoes = ImageManager::GetSingleton()->FindImage("image/player/gold/R_foot.bmp");
	if (R_shoes == nullptr)
	{
		return false;
	}*/


	// �����
	DBbackArm = ImageManager::GetSingleton()->FindImage("image/player/unarmed/arm_back.bmp");
	if (DBbackArm == nullptr)
	{
		return false;
	}
	DBfrontArm = ImageManager::GetSingleton()->FindImage("image/player/unarmed/arm_front.bmp");
	if (DBfrontArm == nullptr)
	{
		return false;
	}
	DBbody = ImageManager::GetSingleton()->FindImage("image/player/unarmed/body.bmp");
	if (DBbody == nullptr)
	{
		return false;
	}
	DBhead0 = ImageManager::GetSingleton()->FindImage("image/player/unarmed/head_0.bmp");
	if (DBhead0 == nullptr)
	{
		return false;
	}
	DBhead1 = ImageManager::GetSingleton()->FindImage("image/player/unarmed/head_1.bmp");
	if (DBhead1 == nullptr)
	{
		return false;
	}
	DBhead2 = ImageManager::GetSingleton()->FindImage("image/player/unarmed/head_2.bmp");
	if (DBhead2 == nullptr)
	{
		return false;
	}
	DBhead3 = ImageManager::GetSingleton()->FindImage("image/player/unarmed/head_3.bmp");
	if (DBhead3 == nullptr)
	{
		return false;
	}
	DBgoldBody = ImageManager::GetSingleton()->FindImage("image/player/gold/body.bmp");
	if (DBgoldBody == nullptr)
	{
		return false;
	}
	DBgoldFoot = ImageManager::GetSingleton()->FindImage("image/player/gold/foot.bmp");
	if (DBgoldFoot == nullptr)
	{
		return false;
	}

	return true;
}

bool Player::GetItem(ItemType itemType, ItemGrade itemGrade, WeaponType weaponType)
{
	string tempitemName = "image/player/";
	string tempR_itemName = "image/player/";

	switch (itemType)
	{
	case ItemType::IDLE:
		break;
	case ItemType::HELMET:
		if (b_equipHelmet == false)
		{
			b_equipHelmet = true;
			helmetGrade = itemGrade;
			switch (itemGrade)
			{
			case ItemGrade::IDLE:
				break;
			case ItemGrade::BASIC:
				break;
			case ItemGrade::GOLD:
				tempitemName += "Ȳ��.bmp";
				break;
			case ItemGrade::SILVER:
				break;
			}
			helmet = ImageManager::GetSingleton()->FindImage(tempitemName.c_str());
			if (helmet == nullptr)
			{
				return false;
			}
			return true;
		}
		else
		{
			//�κ�
		}
		break;
	case ItemType::ARMOR:
		if (b_equipArmor == false)
		{
			b_equipArmor = true;
			armorGrade = itemGrade;
			switch (itemGrade)
			{
			case ItemGrade::IDLE:
				break;
			case ItemGrade::BASIC:
				break;
			case ItemGrade::GOLD:
				tempitemName += "gold/body.bmp";
				tempR_itemName += "gold/R_body.bmp";
				break;
			case ItemGrade::SILVER:
				break;
			}
			armor = ImageManager::GetSingleton()->FindImage(tempitemName.c_str());
			if (armor == nullptr)
			{
				return false;
			}
			R_armor = ImageManager::GetSingleton()->FindImage(tempR_itemName.c_str());
			if (R_armor == nullptr)
			{
				return false;
			}
			return true;
		}
		else
		{
			//�κ�
		}

		break;
	case ItemType::WEAPON:
		tempitemName = "image/item/";
		// �� �տ� �������� �������
		if (b_equipBackWeapon && b_equipFrontWeapon)
		{
			//�κ��丮��
		}
		else
		{

			switch (weaponType)
			{
			case WeaponType::SWORD:
				switch (itemGrade)
				{
				case ItemGrade::BASIC:
					break;
				case ItemGrade::GOLD:
					break;
				case ItemGrade::SILVER:
					break;
				}
				break;
			case WeaponType::STAFF:
				switch (itemGrade)
				{
				case ItemGrade::BASIC:
					break;
				case ItemGrade::GOLD:
					break;
				case ItemGrade::SILVER:
					break;
				}
				break;
			case WeaponType::LANCE:
				switch (itemGrade)
				{
				case ItemGrade::BASIC:
					break;
				case ItemGrade::GOLD:
					tempitemName += "��巣��_SP.bmp";
					break;
				case ItemGrade::SILVER:
					break;
				}
				break;
			}

			// back ���� ��������� ���� ���� 
			if (b_equipBackWeapon == false)
			{
				b_equipBackWeapon = true;
				backWeaponGrade = itemGrade;
				backWeaponType = weaponType;
				backWeapon = ImageManager::GetSingleton()->FindImage(tempitemName.c_str());
				if (backWeapon == nullptr)
				{
					return false;
				}
				return true;
			}
			else
			{
				b_equipFrontWeapon = true;
				frontWeaponGrade = itemGrade;
				frontWeaponType = weaponType;
				frontWeapon = ImageManager::GetSingleton()->FindImage(tempitemName.c_str());
				if (frontWeapon == nullptr)
				{
					return false;
				}
				return true;
			}
			break;
		}
		break;
	case ItemType::SHOES:
		if (b_equipShoes == false)
		{
			b_equipShoes = true;
			shoesGrade = itemGrade;
			switch (itemGrade)
			{
			case ItemGrade::IDLE:
				break;
			case ItemGrade::BASIC:
				break;
			case ItemGrade::GOLD:
				tempitemName += "gold/foot.bmp";
				tempR_itemName += "gold/R_foot.bmp";
				break;
			case ItemGrade::SILVER:
				break;
			}
			shoes = ImageManager::GetSingleton()->FindImage(tempitemName.c_str());
			if (shoes == nullptr)
			{
				return false;
			}
			R_shoes = ImageManager::GetSingleton()->FindImage(tempR_itemName.c_str());
			if (R_shoes == nullptr)
			{
				return false;
			}
			return true;
			break;
		}
		else
		{
			//�κ�
		}

		break;
	}
	return false;
}
//
//bool Player::ChangeItem(ItemType itemType, ItemGrade itemGrade, WeaponType weaponType, Image* equip)
//{
//	string itemName = "image/item/";
//
//	switch (itemType)
//	{
//	case ItemType::HELMET:
//		switch (itemGrade)
//		{
//		case ItemGrade::IDLE:
//			break;
//		case ItemGrade::BASIC:
//			break;
//		case ItemGrade::GOLD:
//			itemName += "Ȳ��.bmp";
//			return true;
//			break;
//		case ItemGrade::SILVER:
//			break;
//		}
//		break; 
//	case ItemType::ARMOR:
//		switch (itemGrade)
//		{
//		case ItemGrade::IDLE:
//			break;
//		case ItemGrade::BASIC:
//			break;
//		case ItemGrade::GOLD:
//			itemName += "Ȳ��.bmp";
//			return true;
//			break;
//		case ItemGrade::SILVER:
//			break;
//		}
//		break;
//	case ItemType::WEAPON:
//		switch (weaponType)
//		{
//		case WeaponType::SWORD:
//			switch (itemGrade)
//			{
//			case ItemGrade::BASIC:
//				break;
//			case ItemGrade::GOLD:
//				break;
//			case ItemGrade::SILVER:
//				break;
//			}
//			break;
//		case WeaponType::STAFF:
//			switch (itemGrade)
//			{
//			case ItemGrade::BASIC:
//				break;
//			case ItemGrade::GOLD:
//				break;
//			case ItemGrade::SILVER:
//				break;
//			}
//			break;
//		case WeaponType::LANCE:
//			switch (itemGrade)
//			{
//			case ItemGrade::BASIC:
//				break;
//			case ItemGrade::GOLD:
//				itemName += "��巣��_SP.bmp";
//				break;
//			case ItemGrade::SILVER:
//				break;
//			}
//			break;
//		}
//		break;
//	case ItemType::SHOES:
//		switch (itemGrade)
//		{
//		case ItemGrade::IDLE:
//			break;
//		case ItemGrade::BASIC:
//			break;
//		case ItemGrade::GOLD:
//			itemName += "Ȳ��.bmp";
//			break;
//		case ItemGrade::SILVER:
//			break;
//		}
//		break;
//	}
//
//	equip = ImageManager::GetSingleton()->FindImage(itemName.c_str());
//	if (equip == nullptr)
//	{
//		return false;
//	}
//
//	return true;
//}

void Player::PosUpdate()
{
	pos.x = renderPos.x + CameraManager::GetSingleton()->GetPos().x;
	pos.y = renderPos.y + CameraManager::GetSingleton()->GetPos().y;

	// ���� �ڼ��� �ƴҶ�
	if (false == (state == State::SITDOWN))
	{
		frontArmPos.x = (int)renderPos.x - 5;
		frontArmPos.y = (int)renderPos.y - 1;
		backArmPos.x = (int)renderPos.x + 3;
		backArmPos.y = (int)renderPos.y;
		headPos.x = (int)renderPos.x + 1;
		headPos.y = (int)renderPos.y - 18;
		bodyPos.x = (int)renderPos.x;
		bodyPos.y = (int)renderPos.y;

		shape.left = (int)pos.x - (bodySize.x / 2);
		shape.top = (int)pos.y - (bodySize.y / 2);
		shape.right = (int)pos.x + (bodySize.x / 2);
		shape.bottom = (int)pos.y + (bodySize.y / 2);



		if (sitDownCamera)
		{
			renderPos.y += 200;
			CameraManager::GetSingleton()->SetPosY(-200);
			sitDownCamera = false;
		}
	}
	// ���� �ڼ��϶�
	else
	{
		frontArmPos.x = (int)renderPos.x - 4;
		frontArmPos.y = (int)renderPos.y + 9;
		backArmPos.x = (int)renderPos.x + 4;
		backArmPos.y = (int)renderPos.y + 9;
		headPos.x = (int)renderPos.x;
		headPos.y = (int)renderPos.y - 5;
		bodyPos.x = (int)renderPos.x;
		bodyPos.y = (int)renderPos.y;

	}


}
