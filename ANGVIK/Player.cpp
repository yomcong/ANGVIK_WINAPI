#include "Player.h"
#include "Image.h"

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


HRESULT Player::Init()
{
	FindImage();

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
	// �������°� �ƴҰ��
	if (false == (state == State::JUMP))
	{
		// ���ϻ��� Ȯ��
		if (MapColliderManager::GetSingleton()->AutoFall(pos, shape, moveSpeed, bodySize))
		{
			state = State::Fall;

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
			ChangeState(State::IDLE);
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
			// ī�޶�Ŵ����� ���� ���ϰ��
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
			playerDir = direction::LEFT;
		}
		if (Input::GetButton(VK_RIGHT))
		{
			// ī�޶�Ŵ��� �߽��� �ƴҰ�� ĳ���͸� �̵�
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
			playerDir = direction::RIGHT;

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
			ChangeState(State::IDLE);
		}
	}

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
	if (KeyManager::GetSingleton()->IsOnceKeyDown('Y'))
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
			--DBbodyPos.y;
#endif
	// ����׿� ĳ���� ��Ʈǥ��
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_NUMPAD9))
	{
		cout << CameraManager::GetSingleton()->GetPos().y << "\n";
		DBrect == false ? DBrect = true : DBrect = false;
	}

}

void Player::Render(HDC hdc)
{
	if (playerDir == direction::LEFT)
	{
		R_backArm->Render(hdc, (int)armPos.x, (int)armPos.y, backArmFrame.x, backArmFrame.y);	// ����
		R_body->Render(hdc, (int)bodyPos.x, (int)bodyPos.y, bodyFrame.x, bodyFrame.y);			// ��
		R_head->Render(hdc, (int)headPos.x, (int)headPos.y);								// �Ӹ�
		R_frontArm->Render(hdc, (int)armPos.x, (int)armPos.y, frontArmFrame.x, frontArmFrame.y);// ������
	}
	else
	{
		backArm->Render(hdc, (int)armPos.x, (int)armPos.y, backArmFrame.x, backArmFrame.y);
		body->Render(hdc, (int)bodyPos.x, (int)bodyPos.y, bodyFrame.x, bodyFrame.y);
		head->Render(hdc, (int)headPos.x, (int)headPos.y);
		frontArm->Render(hdc, (int)armPos.x, (int)armPos.y, frontArmFrame.x, frontArmFrame.y);
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
		if ((action == Action::RIGHTMOVE || action == Action::LEFTMOVE) && false == (state == State::JUMP))
		{
			b_frontArmMove = true;
			b_backArmMove = true;
			frontArmFrame.x = frontArmStartFrame.x;
			backArmFrame.x = backArmStartFrame.x;
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
			frontArmFrame.x = frontArmStartFrame.x;
			backArmFrame.x = backArmStartFrame.x;
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

			armPos.y += 5;

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
					if (frontArmFrame.x == frontArmStartFrame.x)
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
					if (backArmFrame.x == backArmStartFrame.x)
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
				cout << CameraManager::GetSingleton()->GetPos().y << "\n";
				sitDownCamera = true;
			}

			frameCount = 0.0f;
		}
	}



}

HRESULT Player::FindImage()
{
	backArm = ImageManager::GetSingleton()->FindImage("image/player/unarmed/arm_back.bmp");
	if (backArm == nullptr)
	{
		return E_FAIL;
	}
	frontArm = ImageManager::GetSingleton()->FindImage("image/player/unarmed/arm_front.bmp");
	if (frontArm == nullptr)
	{
		return E_FAIL;
	}
	body = ImageManager::GetSingleton()->FindImage("image/player/unarmed/body.bmp");
	if (body == nullptr)
	{
		return E_FAIL;
	}
	head = ImageManager::GetSingleton()->FindImage("image/player/unarmed/head_1.bmp");
	if (head == nullptr)
	{
		return E_FAIL;
	}
	R_body = ImageManager::GetSingleton()->FindImage("image/player/unarmed/R_body.bmp");
	if (R_body == nullptr)
	{
		return E_FAIL;
	}
	R_backArm = ImageManager::GetSingleton()->FindImage("image/player/unarmed/R_arm_back.bmp");
	if (R_backArm == nullptr)
	{
		return E_FAIL;
	}
	R_frontArm = ImageManager::GetSingleton()->FindImage("image/player/unarmed/R_arm_front.bmp");
	if (R_frontArm == nullptr)
	{
		return E_FAIL;
	}
	R_head = ImageManager::GetSingleton()->FindImage("image/player/unarmed/R_head_1.bmp");
	if (R_head == nullptr)
	{
		return E_FAIL;
	}


	// �����
	DBbackArm = ImageManager::GetSingleton()->FindImage("image/player/unarmed/arm_back.bmp");
	if (DBbackArm == nullptr)
	{
		return E_FAIL;
	}
	DBfrontArm = ImageManager::GetSingleton()->FindImage("image/player/unarmed/arm_front.bmp");
	if (DBfrontArm == nullptr)
	{
		return E_FAIL;
	}
	DBbody = ImageManager::GetSingleton()->FindImage("image/player/unarmed/body.bmp");
	if (DBbody == nullptr)
	{
		return E_FAIL;
	}
	DBhead0 = ImageManager::GetSingleton()->FindImage("image/player/unarmed/head_0.bmp");
	if (DBhead0 == nullptr)
	{
		return E_FAIL;
	}
	DBhead1 = ImageManager::GetSingleton()->FindImage("image/player/unarmed/head_1.bmp");
	if (DBhead1 == nullptr)
	{
		return E_FAIL;
	}
	DBhead2 = ImageManager::GetSingleton()->FindImage("image/player/unarmed/head_2.bmp");
	if (DBhead2 == nullptr)
	{
		return E_FAIL;
	}
	DBhead3 = ImageManager::GetSingleton()->FindImage("image/player/unarmed/head_3.bmp");
	if (DBhead3 == nullptr)
	{
		return E_FAIL;
	}
	DBgoldBody = ImageManager::GetSingleton()->FindImage("image/player/gold/body.bmp");
	if (DBgoldBody == nullptr)
	{
		return E_FAIL;
	}
	DBgoldFoot = ImageManager::GetSingleton()->FindImage("image/player/gold/foot.bmp");
	if (DBgoldFoot == nullptr)
	{
		return E_FAIL;
	}

	return S_OK;
}

void Player::PosUpdate()
{
	pos.x = renderPos.x + CameraManager::GetSingleton()->GetPos().x;
	pos.y = renderPos.y + CameraManager::GetSingleton()->GetPos().y;


	if (false == (state == State::SITDOWN))
	{
		armPos.x = (int)renderPos.x;
		armPos.y = (int)renderPos.y;
		headPos.x = (int)renderPos.x + 2;
		headPos.y = (int)renderPos.y - 20;
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
	else
	{
		armPos.x = (int)renderPos.x;
		armPos.y = (int)renderPos.y + 5;
		headPos.x = (int)renderPos.x;
		headPos.y = (int)renderPos.y - 5;
		bodyPos.x = (int)renderPos.x;
		bodyPos.y = (int)renderPos.y;

	}


}
