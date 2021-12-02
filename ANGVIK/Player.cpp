#include "Player.h"
#include "PixelCollider.h"
#include "Image.h"

// 픽셀충돌 관리해주기
// 픽셀충돌 2중포문 물어보기


// 캐릭터 이동 
// 팔 자연스럽게 해주기
// 갑옷 신발 위치 조정
// 캐릭터 랙트 세분화 해주기(몸통 머리 발)
// 렉트 세분화 후 발 부분으로 픽셀충돌다시

// 캐릭터가 왼쪽을볼떄는 랜더 순서 바꿔주기 ( 왼팔이 먼저보이게) 및 이미지 가로회전

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
	// 점프중이 아닐때 낙하
	if (false == (action == PlayerAction::JUMP))
	{
		pos.y = playerPixelCollision->autoMove(pos.x, pos.y, shape, moveSpeed);
	}

	//플레이어 이동
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
	{
		// 이동(픽셀충돌검사)
		pos = playerPixelCollision->Move(pos, shape, moveSpeed, -1, bodySize_Y);
		// 상태 변경
		action = PlayerAction::LEFTMOVE;

	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	{
		// 이동(픽셀충돌검사)
		pos = playerPixelCollision->Move(pos, shape, moveSpeed, 1, bodySize_Y);
		// 상태 변경
		action = PlayerAction::RIGHTMOVE;
		
		// 애니메이션 프레임
		frameCount += TimerManager::GetSingleton()->GetDeltaTime();
		if (frameCount > 0.125)
		{
			// 손 구부리기, 몸통 뛰는모션
			frontArmFrame.y = 1;
			backArmFrame.y = 1;
			bodyFrame.y = 1;

			// 오른손 프레임관리
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
			// 왼손 프레임 관리
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
			// 몸,발 프레임 관리
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

	// 액션중이 아닐때 기본자세
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


	//디버그용 인체실험
#ifdef _DEBUG
	// 디버깅용
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
	// 디버그용 캐릭터 랙트표시
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

	Rectangle(hdc, 320, 90, 340, 115);	// 몸통 렉트
	Rectangle(hdc, 325, 115, 335, 125);	// 신발 렉트

	backArm->Render(hdc, pos.x + 5, pos.y, backArmFrame.x, backArmFrame.y);	// 왼팔
	body->Render(hdc, pos.x, pos.y, bodyFrame.x, bodyFrame.y);				// 몸
	frontArm->Render(hdc, pos.x, pos.y, frontArmFrame.x, frontArmFrame.y);	// 오른팔

	if (DBplayerRect)
		Rectangle(hdc, shape.left, shape.top, shape.right, shape.bottom);

}

void Player::Release()
{

}
