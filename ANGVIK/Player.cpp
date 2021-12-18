#include "Player.h"
#include "Image.h"
#include "TrapManager.h"
#include "MonsterManager.h"

// 캐릭터 이동
// 팔 자연스럽게 해주기
// 갑옷 신발 위치 조정
// 캐릭터 랙트 세분화 해주기(몸통 머리 발)
// 렉트 세분화 후 발 부분으로 픽셀충돌다시

// 캐릭터가 왼쪽을볼떄는 랜더 순서 바꿔주기 ( 왼팔이 먼저보이게) 및 이미지 가로회전  -- O

// 카메라가 한쪽의 끝에 있을때 예외조건해주기	-- O 
// -> 델타타임으로 캐릭터를 이동시키면 소수점이 달라져서 동기화 방법찾기

// 델타타임 고정시키기....

// 보정으로 y축이 감소되면 카메라가 화면끝에있어도 올라감 -- O

#define JumpPower 90.0f

#define StartPosX 120.0f
#define StartPosY 325.0f
#define StartPointX 300.0f
#define StartPointY 350.0f

// 테스트용 매개변수
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

	// 점프상태가 아닐경우
	if (false == (state == State::JUMP))
	{
		// 내리막길(이동+낙하) 일경우 스테이트를 계속 바꿔주면서 애니메이션이 굉장히 부자연스러워짐. 고쳐야함
		// 테스트용 트랩 충돌체크 최적화 하기
		if (MapColliderManager::GetSingleton()->IsFalling(pos, shape, moveSpeed, bodySize)
			&& b_platform == false)
		{
			ChangeState(State::Fall);

			// 카메라 예외조건
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
			// 앉은 자세가 아닐경우에만 기본자세
			if (false == (state == State::SITDOWN))
			{
				ChangeState(State::IDLE);
			}
		}
	}
	// 점프 상태
	else
	{
		// 점프중 충돌검사
		if (MapColliderManager::GetSingleton()->Jump(pos, shape, moveSpeed, bodySize))
		{
			// 카메라 예외조건
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

	// 애니메이션프레임 
	DoAnimation();
	// 포스값 업데이트
	PosUpdate();

	//플레이어 이동 
	if (false == (state == State::SITDOWN))
	{
		if (Input::GetButton(VK_LEFT))
		{
			// 카메라 예외조건
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
			// 상태 변경
			ChangeAction(Action::LEFTMOVE);
			dir = direction::LEFT;
		}
		if (Input::GetButton(VK_RIGHT))
		{
			// 오른쪽 끝 예외처리 해야함
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

			// 상태 변경
			ChangeAction(Action::RIGHTMOVE);
			dir = direction::RIGHT;
		}
		if (Input::GetButton(VK_UP))
		{
			// 점프중이거나 낙하상태가 아닐 경우
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

	// 시점 부드럽게 + 캐릭터 랜더 좀더 수정
	if (Input::GetButton(VK_DOWN))
	{
		// 점프중이거나 낙하상태가 아닐경우
		if (false == (state == State::JUMP) &&
			false == (state == State::Fall))
		{
			ChangeState(State::SITDOWN);
		}
	}

	// 액션중이 아닐때 기본자세 이후에 좀더 디테일 수정
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


	//디버그용 인체실험
#ifdef _DEBUG
	// 디버깅용
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
			// 디버그용 캐릭터 랙트표시
	if (Input::GetButtonDown(VK_NUMPAD9))
	{
		DBrect == false ? DBrect = true : DBrect = false;
	}

}

void Player::Render(HDC hdc)
{
	if (invisibleTime > 0 && b_invisible)
	{
		// 피격시 무적상태 ->그려주지 않는다.
	}
	else
	{
		// 반대쪽을 보고있으므로 back, front 가 반대
		if (dir == direction::LEFT)
		{
			if (b_equipBackWeapon)
			{
				backWeapon->Render(hdc, (int)frontArmPos.x - 10, (int)frontArmPos.y -10, backWeaponFrame.x, backWeaponFrame.y);
			}
			
			R_backArm->Render(hdc, (int)frontArmPos.x, (int)frontArmPos.y, backArmFrame.x, backArmFrame.y);	// 왼팔

			R_body->Render(hdc, (int)bodyPos.x, (int)bodyPos.y, bodyFrame.x, bodyFrame.y);			// 몸
			if (b_equipArmor)
			{
				R_armor->Render(hdc, (int)bodyPos.x, (int)bodyPos.y, bodyFrame.x, bodyFrame.y);
			}
			if (b_equipShoes)
			{
				R_shoes->Render(hdc, (int)bodyPos.x, (int)bodyPos.y, bodyFrame.x, bodyFrame.y);
			}

			R_head->Render(hdc, (int)headPos.x, (int)headPos.y);								// 머리
			if (b_equipHelmet)
			{

			}
			if (b_equipFrontWeapon)
			{
				frontWeapon->Render(hdc, (int)frontArmPos.x, (int)frontArmPos.y, frontWeaponFrame.x, frontWeaponFrame.y);
			}
			R_frontArm->Render(hdc, (int)backArmPos.x, (int)backArmPos.y, frontArmFrame.x, frontArmFrame.y);// 오른팔
			
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

	//--디버그--
	if (DBrect)
	{
		Rectangle(hdc, shape.left - (int)CameraManager::GetSingleton()->GetPos().x,
			shape.top - (int)CameraManager::GetSingleton()->GetPos().y,
			shape.right - (int)CameraManager::GetSingleton()->GetPos().x,
			shape.bottom - (int)CameraManager::GetSingleton()->GetPos().y);

		Rectangle(hdc, 320, 90, 340, 115);	// 몸통 렉트
		Rectangle(hdc, 325, 115, 335, 125);	// 신발 렉트

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
		// 새로운 액션일경우 애니메이션들 기본상태로 변경
		this->action = action;


		frameCount = 0.0f;
		// 점프중일때는 무브동작 X
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
				// 오른손 프레임관리
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
				// 왼손 프레임 관리
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
				// 몸,발 프레임 관리
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
			// 오른손 프레임관리
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
			// 오른손 프레임관리
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
		// 갑옷, hp 처리해주기
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


	// 디버깅
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
				tempitemName += "황투.bmp";
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
			//인벤
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
			//인벤
		}

		break;
	case ItemType::WEAPON:
		tempitemName = "image/item/";
		// 두 손에 아이템이 있을경우
		if (b_equipBackWeapon && b_equipFrontWeapon)
		{
			//인벤토리로
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
					tempitemName += "골드랜스_SP.bmp";
					break;
				case ItemGrade::SILVER:
					break;
				}
				break;
			}

			// back 손이 비어있으면 먼저 장착 
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
			//인벤
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
//			itemName += "황투.bmp";
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
//			itemName += "황갑.bmp";
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
//				itemName += "골드랜스_SP.bmp";
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
//			itemName += "황신.bmp";
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

	// 앉은 자세가 아닐때
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
	// 앉은 자세일때
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
