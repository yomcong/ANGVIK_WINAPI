#include "Player.h"
#include "PixelCollider.h"
#include "Image.h"

// �ȼ��浹 �������ֱ�
// �ȼ��浹 2������ �����


// ĳ���� �̵� 
// �� �ڿ������� ���ֱ�
// ���� �Ź� ��ġ ����
// ĳ���� ��Ʈ ����ȭ ���ֱ�(���� �Ӹ� ��)
// ��Ʈ ����ȭ �� �� �κ����� �ȼ��浹�ٽ�

// ĳ���Ͱ� ������������ ���� ���� �ٲ��ֱ� ( ������ �������̰�) �� �̹��� ����ȸ��

HRESULT Player::Init()
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

	// DB
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
	//

	pos.x = 120.0f;
	pos.y = 425.0f;

	moveSpeed = 50.0f;

	bodySize_X = 20;
	bodySize_Y = 50;

	shape.left = (int)pos.x - (bodySize_X / 2);
	shape.top = (int)pos.y - (bodySize_Y / 2);
	shape.right = (int)pos.x + (bodySize_X / 2);
	shape.bottom = (int)pos.y + (bodySize_Y / 2);

	playerPixelCollision = new PixelCollider;
	playerPixelCollision->Init();


	return S_OK;
}

void Player::Update()
{
	// �������� �ƴҶ� ����
	if (false == (action == PlayerAction::JUMP))
	{
		pos.y = playerPixelCollision->autoMove(pos.x, pos.y, shape, moveSpeed);
	}

	//�÷��̾� �̵�
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
	{
		// �̵�(�ȼ��浹�˻�)
		pos = playerPixelCollision->Move(pos, shape, moveSpeed, -1, bodySize_Y);
		// ���� ����
		action = PlayerAction::LEFTMOVE;

	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	{
		// �̵�(�ȼ��浹�˻�)
		pos = playerPixelCollision->Move(pos, shape, moveSpeed, 1, bodySize_Y);
		// ���� ����
		action = PlayerAction::RIGHTMOVE;
		
		// �ִϸ��̼� ������
		frameCount += TimerManager::GetSingleton()->GetDeltaTime();
		if (frameCount > 0.125)
		{
			// �� ���θ���, ���� �ٴ¸��
			frontArmFrame.y = 1;
			backArmFrame.y = 1;
			bodyFrame.y = 1;

			// ������ �����Ӱ���
			if (b_frontArmMove)
			{
				if (frontArmFrame.x == 15)
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
				if (backArmFrame.x == 15)
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
				if (backArmFrame.x == 9)
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
			if (bodyFrame.x == 11)
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

	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
	{
		action = PlayerAction::JUMP;
		pos.y -= moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
	{
		action = PlayerAction::SITDOWN;
		pos.y += moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
	}

	// �׼����� �ƴҶ� �⺻�ڼ�
	if (!KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT) &&
		!KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT) &&
		!KeyManager::GetSingleton()->IsStayKeyDown(VK_UP) &&
		!KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
	{
		action = PlayerAction::NORMAL;

		frontArmFrame.x = 11;
		frontArmFrame.y = 0;

		backArmFrame.x = 13;
		backArmFrame.y = 0;

		bodyFrame.y = 0;
		bodyFrame.x = 0;
	}

	shape.left = (int)pos.x - (bodySize_X / 2);
	shape.top = (int)pos.y - (bodySize_Y / 2);
	shape.right = (int)pos.x + (bodySize_X / 2);
	shape.bottom = (int)pos.y + (bodySize_Y / 2);


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
		DBplayerRect == false ? DBplayerRect = true : DBplayerRect = false;
	}

}

void Player::Render(HDC hdc)
{
	DBbackArm->Render(hdc, 100, 100, DBarmPos.x, DBarmPos.y);
	DBfrontArm->Render(hdc, 200, 100, DBarmPos.x, DBarmPos.y);
	DBbody->Render(hdc, 300, 100, DBbodyPos.x, DBbodyPos.y);
	DBhead0->Render(hdc, 450, 100);
	DBhead1->Render(hdc, 500, 100);
	DBhead2->Render(hdc, 550, 100);
	DBhead3->Render(hdc, 600, 100);

	DBgoldBody->Render(hdc, 350, 100, DBbodyPos.x, DBbodyPos.y);
	DBgoldFoot->Render(hdc, 350, 100, DBbodyPos.x, DBbodyPos.y);

	Rectangle(hdc, 320, 90, 340, 115);	// ���� ��Ʈ
	Rectangle(hdc, 325, 115, 335, 125);	// �Ź� ��Ʈ

	backArm->Render(hdc, pos.x + 5, pos.y, backArmFrame.x, backArmFrame.y);	// ����
	body->Render(hdc, pos.x, pos.y, bodyFrame.x, bodyFrame.y);				// ��
	frontArm->Render(hdc, pos.x, pos.y, frontArmFrame.x, frontArmFrame.y);	// ������

	if (DBplayerRect)
		Rectangle(hdc, shape.left, shape.top, shape.right, shape.bottom);

}

void Player::Release()
{

}
