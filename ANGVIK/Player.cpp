//#include "stdafx.h"
#include "Player.h"
#include "Image.h"
#include "TrapManager.h"
#include "MonsterManager.h"
#include "Inventory.h"
#include "AmmoManager.h"

#define JumpPower 85.0f
#define gravityAcceleration 98
 
#define StartPosX 120.0f
#define StartPosY 325.0f
#define StartPointX 300.0f
#define StartPointY 350.0f

// 테스트용 매개변수
HRESULT Player::Init(AmmoManager* _ammoManager)
{
	if (false == FindImage())
	{
		return E_FAIL;
	}

	pos.x = StartPosX;
	pos.y = StartPosY;

	renderPos = pos;

	moveSpeed = 200.0f;

	bodySize.x = 20;
	bodySize.y = 50;

	shape.left = (int)pos.x - bodySize.x / 2;
	shape.top = (int)pos.y - bodySize.y / 2;
	shape.right = (int)pos.x + bodySize.x / 2;
	shape.bottom = (int)pos.y + bodySize.y / 2;

	playerInventory = new Inventory;
	playerInventory->Init(this);

	ammoManager = _ammoManager;

	return S_OK;
}

void Player::Update()
{
	// 점프상태가 아닐경우
	if (state != State::JUMP)
	{
		// 내리막길(이동+낙하) 일경우 스테이트를 계속 바꿔주면서 애니메이션이 굉장히 부자연스러워짐. 고쳐야함
		// 중력속도 추가해주기? 
		if (MapColliderManager::GetSingleton()->IsFalling(pos, shape, moveSpeed, bodySize, subTag)
			&& b_platform == false)
		{
			gAccele += gAccele * Timer::GetDeltaTime();

			if (gAccele >= 100)
			{
				ChangeState(State::Fall);
			}
			
			// 카메라 예외조건
			if (renderPos.y < StartPointY)
			{
				renderPos.y += (moveSpeed+ gAccele)* Timer::GetDeltaTime();
			}
			else
			{
				CameraManager::GetSingleton()->SetPosY((moveSpeed+ gAccele) * Timer::GetDeltaTime());
			}
		}
		else
		{
			// 앉은 자세가 아닐경우에만 기본자세
			if (state != State::SITDOWN)
			{
				ChangeState(State::IDLE);
				gAccele = gravityAcceleration;
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
			if (CameraManager::GetSingleton()->GetPos().y <= 50)
			{
				renderPos.y -= (moveSpeed + 30) * Timer::GetDeltaTime();
			}
			else
			{
				CameraManager::GetSingleton()->SetPosY(-(moveSpeed+ 30) *Timer::GetDeltaTime());
			}


			if (jumpingPower <= 0)
			{
				ChangeState(State::Fall);
			}
			else
			{
				jumpingPower -= (moveSpeed ) * Timer::GetDeltaTime();
			}
		}
		else
		{
			jumpingPower = 0;
			ChangeState(State::Fall);
		}
	}


	// 인벤토리를 열었을땐 행동 x
	if (b_inventoryOpen == false)
	{
		// 앉아있지 않을 때 플레이어 이동 
		if (state != State::SITDOWN && b_inventoryOpen == false)
		{
			if (Input::GetButton(VK_LEFT))
			{
				// 상태 변경
				ChangeAction(Action::LEFTMOVE);
				dir = direction::LEFT;

				// 카메라 예외조건(화면끝에 있을 때)
				if (renderPos.x > StartPointX ||CameraManager::GetSingleton()->GetPos().x <= 0)
				{
					renderPos.x += MapColliderManager::GetSingleton()->
						Move(pos, shape, moveSpeed, (int)dir, bodySize).x;
					renderPos.y += MapColliderManager::GetSingleton()->
						Move(pos, shape, moveSpeed, (int)dir, bodySize).y;
				}
				else
				{
					POINTFLOAT tempPos = MapColliderManager::GetSingleton()->
						Move(pos, shape, moveSpeed, (int)dir, bodySize);
					CameraManager::GetSingleton()->SetPosX(tempPos.x);
					renderPos.y += tempPos.y;
				}
			}
			if (Input::GetButton(VK_RIGHT))
			{
				// 상태 변경
				ChangeAction(Action::RIGHTMOVE);
				dir = direction::RIGHT;

				// 카메라 예외조건(화면끝에 있을 때)
				if (renderPos.x < StartPointX || CameraManager::GetSingleton()->GetPos().x >= 5700)
				{
					renderPos.x += MapColliderManager::GetSingleton()->
						Move(pos, shape, moveSpeed, (int)dir, bodySize).x;
					renderPos.y += MapColliderManager::GetSingleton()->
						Move(pos, shape, moveSpeed, (int)dir, bodySize).y;
				}
				else
				{
					POINTFLOAT tempPos = MapColliderManager::GetSingleton()->
						Move(pos, shape, moveSpeed, (int)dir, bodySize);

					CameraManager::GetSingleton()->SetPosX(tempPos.x);
					renderPos.y += tempPos.y;
				}
				
			}
			if (Input::GetButtonDown('S'))
			{
				// 점프중이거나 낙하상태가 아닐 경우
				if (false == (state == State::JUMP) &&
					false == (state == State::Fall))
				{
					ChangeState(State::JUMP);
					jumpingPower = JumpPower;
				}
			}
			if (Input::GetButton(VK_DOWN))
			{
				// 점프중이거나 낙하상태가 아닐경우
				if (state != State::JUMP &&
					state != State::Fall)
				{
					CollisionManager::GetSingleton()->CheckItem(shape);
					ChangeState(State::SITDOWN);
				}
			}
			if (Input::GetButtonDown(VK_SPACE))
			{
				// 점프, 낙하, 앉아있는 상태가 아닐 때
				if (state != State::Fall &&
					state != State::JUMP &&
					state != State::SITDOWN)
				{
					b_inventoryOpen = true;
					playerInventory->SetInventoryOpen(true);
					playerInventory->InventoryOpen(renderPos);

				}

			}
			// 공격중이 아닐때 공격
			if (b_frontAttack == false && b_backAttack == false)
			{
				if (Input::GetButtonDown('A'))
				{
					ChangeAction(Action::FRONTATTACK);
				}

				if (Input::GetButtonDown('D'))
				{
					ChangeAction(Action::BACKATTACK);
				}
			}
		}
		else
		{
			// 앉은키를 계속 누르고 잇는지 확인
			if (!Input::GetButton(VK_DOWN))
			{
				ChangeState(State::IDLE);
			}
		}
	}


	// 액션중이 아닐때 기본자세 이후에 좀더 디테일 수정
	if (!Input::GetButton(VK_LEFT) &&
		!Input::GetButton(VK_RIGHT) &&
		state != State::SITDOWN &&
		state != State::Fall &&
		state != State::JUMP &&
		state != State::ATTACK)
	{
		ChangeState(State::IDLE);
		ChangeAction(Action::IDLE);

		frontArmFrame.x = 10;
		backArmFrame.x = 13;
		bodyFrame.x = 0;
		bodyFrame.y = 0;
		frontArmFrame.y = 0;
		backArmFrame.y = 0;
	}


	// 애니메이션프레임 
	PlayAnimation();
	// 포스값 업데이트
	PosUpdate();

	playerInventory->Update();

	CollisionManager::GetSingleton()->CheckCollision(subTag, shape);




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
		DBrect = !DBrect;
		switch (state)
		{
		case State::IDLE:
			switch (action)
			{
			case Action::IDLE:
				cout << "기본, 기본" << "\n";
				break;
			case Action::LEFTMOVE:
				cout << "기본, 왼쪽" << "\n";
				break;
			case Action::RIGHTMOVE:
				cout << "기본, 오른" << "\n";
				break;
			case Action::BACKATTACK:
				cout << "기본, 약공" << "\n";
				break;
			case Action::FRONTATTACK:
				cout << "기본, 강공" << "\n";
				break;
			}
			break;
		case State::JUMP:
			switch (action)
			{
			case Action::IDLE:
				cout << "점프, 기본" << "\n";
				break;
			case Action::LEFTMOVE:
				cout << "점프, 왼쪽" << "\n";
				break;
			case Action::RIGHTMOVE:
				cout << "점프, 오른" << "\n";
				break;
			case Action::BACKATTACK:
				cout << "점프, 약공" << "\n";
				break;
			case Action::FRONTATTACK:
				cout << "점프, 강공" << "\n";
				break;
			}
			break;
		case State::Fall:
			switch (action)
			{
			case Action::IDLE:
				cout << "낙하, 기본" << "\n";
				break;
			case Action::LEFTMOVE:
				cout << "낙하, 왼쪽" << "\n";
				break;
			case Action::RIGHTMOVE:
				cout << "낙하, 오른" << "\n";
				break;
			case Action::BACKATTACK:
				cout << "낙하, 약공" << "\n";
				break;
			case Action::FRONTATTACK:
				cout << "낙하, 강공" << "\n";
				break;
			}
			break;
		case State::SITDOWN:
			switch (action)
			{
			case Action::IDLE:
				cout << "앉음, 기본" << "\n";
				break;
			case Action::LEFTMOVE:
				cout << "앉음, 왼쪽" << "\n";
				break;
			case Action::RIGHTMOVE:
				cout << "앉음, 오른" << "\n";
				break;
			case Action::BACKATTACK:
				cout << "앉음, 약공" << "\n";
				break;
			case Action::FRONTATTACK:
				cout << "앉음, 강공" << "\n";
				break;
			}
			break;
		case State::HIT:
			switch (action)
			{
			case Action::IDLE:
				cout << "맞음, 기본" << "\n";
				break;
			case Action::LEFTMOVE:
				cout << "맞음, 왼쪽" << "\n";
				break;
			case Action::RIGHTMOVE:
				cout << "맞음, 오른" << "\n";
				break;
			case Action::BACKATTACK:
				cout << "맞음, 약공" << "\n";
				break;
			case Action::FRONTATTACK:
				cout << "맞음, 강공" << "\n";
				break;
			}
			break;
		case State::ATTACK:
			switch (action)
			{
			case Action::IDLE:
				cout << "공격, 기본" << "\n";
				break;
			case Action::LEFTMOVE:
				cout << "공격, 왼쪽" << "\n";
				break;
			case Action::RIGHTMOVE:
				cout << "공격, 오른" << "\n";
				break;
			case Action::BACKATTACK:
				cout << "공격, 약공" << "\n";
				break;
			case Action::FRONTATTACK:
				cout << "공격, 강공" << "\n";
				break;
			}
			break;
		}

		cout << bodyFrame.x << ", " << bodyFrame.y << "\n";
		cout << backArmFrame.x << ", " << backArmFrame.y << "\n";
		cout << frontArmFrame.x << ", " << frontArmFrame.y << "\n";
		cout << backWeaponFrame.x << ", " << frontWeaponFrame.x << "\n";
	}
	if (Input::GetButtonDown(VK_NUMPAD3))
	{
		cout << pos.x << ", " << pos.y << "\n";
		cout << renderPos.x << ", " << renderPos.y << "\n";
		cout << shape.left << ", " << shape.top << ", " << shape.right << ", " << shape.bottom << "\n";
	}
	if (Input::GetButtonDown(VK_NUMPAD1))
	{
		cout << CameraManager::GetSingleton()->GetPos().x << ", " << CameraManager::GetSingleton()->GetPos().y << "\n";
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
			if (b_backAttack)
			{
				if (b_equipBackWeapon)
				{
					R_backWeapon->Render(hdc, (int)backWeaponPos.x, (int)backWeaponPos.y, backWeaponFrame.x, backWeaponFrame.y);	//무기
				}

				R_backArm->Render(hdc, (int)frontArmPos.x, (int)frontArmPos.y, backAttackArmFrame.x, backAttackArmFrame.y);			//왼팔
			}
			else
			{
				if (b_equipBackWeapon)
				{
					R_backWeapon->Render(hdc, (int)backWeaponPos.x, (int)backWeaponPos.y, backWeaponFrame.x, backWeaponFrame.y);	//무기
				}

				R_backArm->Render(hdc, (int)frontArmPos.x, (int)frontArmPos.y, backArmFrame.x, backArmFrame.y);						//왼팔
			}

			R_body->Render(hdc, (int)bodyPos.x, (int)bodyPos.y, bodyFrame.x, bodyFrame.y);			// 몸
			if (b_equipArmor)
			{
				R_armor->Render(hdc, (int)bodyPos.x, (int)bodyPos.y, bodyFrame.x, bodyFrame.y);		// 갑옷
			}
			if (b_equipShoes)
			{
				R_shoes->Render(hdc, (int)bodyPos.x, (int)bodyPos.y, bodyFrame.x, bodyFrame.y);		// 신발
			}

			R_head->Render(hdc, (int)headPos.x, (int)headPos.y);									// 머리
			if (b_equipHelmet)
			{
				//헬멧
			}

			if (b_frontAttack)
			{
				if (b_equipFrontWeapon)
				{
					R_frontWeapon->Render(hdc, (int)frontWeaponPos.x, (int)frontWeaponPos.y, frontWeaponFrame.x, frontWeaponFrame.y);//오른 무기
				}
				R_frontArm->Render(hdc, (int)backArmPos.x, (int)backArmPos.y, frontAttackArmFrame.x, frontAttackArmFrame.y);		//오른팔
			}
			else
			{
				if (b_equipFrontWeapon)
				{
					R_frontWeapon->Render(hdc, (int)frontWeaponPos.x, (int)frontWeaponPos.y, frontWeaponFrame.x, frontWeaponFrame.y);//오른 무기
				}
				R_frontArm->Render(hdc, (int)backArmPos.x, (int)backArmPos.y, frontArmFrame.x, frontArmFrame.y);					// 오른팔
			}
		}
		else
		{
			if (b_backAttack)
			{
				if (b_equipBackWeapon)
				{
					backWeapon->Render(hdc, (int)backWeaponPos.x, (int)backWeaponPos.y, backWeaponFrame.x, backWeaponFrame.y);
				}
				backArm->Render(hdc, (int)backArmPos.x, (int)backArmPos.y, backAttackArmFrame.x, backAttackArmFrame.y);
			}
			else
			{
				if (b_equipBackWeapon)
				{
					backWeapon->Render(hdc, (int)backWeaponPos.x, (int)backWeaponPos.y, backWeaponFrame.x, backWeaponFrame.y);
				}
				backArm->Render(hdc, (int)backArmPos.x, (int)backArmPos.y, backArmFrame.x, backArmFrame.y);
			}
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

			if (b_frontAttack)
			{
				if (b_equipFrontWeapon)
				{
					frontWeapon->Render(hdc, (int)frontWeaponPos.x, (int)frontWeaponPos.y, frontWeaponFrame.x, frontWeaponFrame.y);
				}
				frontArm->Render(hdc, (int)frontArmPos.x, (int)frontArmPos.y, frontAttackArmFrame.x, frontAttackArmFrame.y);
			}
			else
			{
				if (b_equipFrontWeapon)
				{
					frontWeapon->Render(hdc, (int)frontWeaponPos.x, (int)frontWeaponPos.y, frontWeaponFrame.x, frontWeaponFrame.y);
				}
				frontArm->Render(hdc, (int)frontArmPos.x, (int)frontArmPos.y, frontArmFrame.x, frontArmFrame.y);

			}
		}
	}

	if (b_inventoryOpen)
	{
		playerInventory->Render(hdc);
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
		if (b_backAttack || b_frontAttack)
		{
			Rectangle(hdc, DBattackShape.left - (int)CameraManager::GetSingleton()->GetPos().x,
				DBattackShape.top - (int)CameraManager::GetSingleton()->GetPos().y,
				DBattackShape.right - (int)CameraManager::GetSingleton()->GetPos().x,
				DBattackShape.bottom - (int)CameraManager::GetSingleton()->GetPos().y);
		}
	}

}

void Player::Release()
{
	SAFE_RELEASE(playerInventory);
}

void Player::ChangeAction(Action action)
{
	if (this->action == action)
	{
		if ((action == Action::RIGHTMOVE || action == Action::LEFTMOVE) && bodyFrame.y == 0)
		{
			bodyFrame.y = 1;
		}
		return;
	}
	else
	{
		// 새로운 액션일경우 애니메이션들 기본상태로 변경
		this->action = action;

		frameCount = 0.0f;

		if (action == Action::IDLE)
		{
			bodyFrame.x = 0;
			bodyFrame.y = 0;
			frontArmFrame.x = 11;
			frontArmFrame.y = 0;
			backArmFrame.x = 13;
			backArmFrame.y = 0;
		}

		// 점프중일때는 무브동작 X
		if ((action == Action::RIGHTMOVE || action == Action::LEFTMOVE))
		{
			b_frontArmMove = true;
			b_backArmMove = true;
			frontArmFrame.x = 11;
			backArmFrame.x = 13;
			bodyFrame.y = 1;
			frontArmFrame.y = 0;
			backArmFrame.y = 0;
		}

		if (action == Action::FRONTATTACK)
		{
			//if (b_equipFrontWeapon)
			//{
			if (frontWeaponType == WeaponType::BOOMERANG ||
				frontWeaponType == WeaponType::LANCE)
			{
				ammoManager->WeaponAttack(SubjectTag::WEAPON,frontWeaponGrade, frontWeaponType, { pos.x , pos.y }, (int)dir);
				b_equipFrontWeapon = false;
				frontWeaponType = WeaponType::IDLE;
				frontWeaponGrade = ItemGrade::IDLE;
			}
			b_frontAttack = true;
			attackCount = 0.0f;
			frontAttackArmFrame.x = 4;
			frontAttackArmFrame.y = 0;
			frontWeaponFrame.x = 0;
		}
		if (action == Action::BACKATTACK)
		{
			if (backWeaponType == WeaponType::BOOMERANG ||
				backWeaponType == WeaponType::LANCE)
			{
				ammoManager->WeaponAttack(SubjectTag::WEAPON, backWeaponGrade, backWeaponType, { pos.x , pos.y }, (int)dir);
				b_equipBackWeapon = false;
				backWeaponType = WeaponType::IDLE;
				backWeaponGrade = ItemGrade::IDLE;
			}
			b_backAttack = true;
			attackCount = 0.0f;
			backAttackArmFrame.x = 4;
			backAttackArmFrame.y = 0;
			backWeaponFrame.x = 0;
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
		}
		else if (state == State::JUMP)
		{
			b_frontArmMove = true;
			b_backArmMove = true;
			frontArmFrame.x = 11;
			backArmFrame.x = 13;
			bodyFrame.x = 0;
			bodyFrame.y = 0;
			frontArmFrame.y = 0;
			backArmFrame.y = 0;
		}
		else if (state == State::Fall)
		{
			frontArmFrame.x = 9;
			backArmFrame.x = 13;
			bodyFrame.x = 2;
			bodyFrame.y = 0;
			frontArmFrame.y = 0;
			backArmFrame.y = 0;
		}
		else if (state == State::HIT)
		{
			if (b_equipArmor)
			{
				b_equipArmor = false;
			}
			else if (b_equipHelmet)
			{
				b_equipHelmet = false;
			}
			else if (b_equipShoes)
			{
				b_equipShoes = false;
			}
			else
			{
				// 죽음
			}
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


void Player::PlayAnimation()
{
	frameCount += Timer::GetDeltaTime();

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
					if (frontArmFrame.x == 8)
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
					if (backArmFrame.x == 10)
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
			if (false == b_sitDownCamera)
			{
				renderPos.y -= 200;
				CameraManager::GetSingleton()->SetPosY(+200);
				b_sitDownCamera = true;
			}

			frameCount = 0.0f;
		}
	}

	attackCount += Timer::GetDeltaTime();

	if (b_frontAttack)
	{
		if (attackCount > 0.0412)
		{
			if (frontAttackArmFrame.x == 0)
			{
				frontAttackArmFrame.x = 15;
				++frontWeaponFrame.x;
			}
			else
			{
				if (frontAttackArmFrame.x == 12)
				{
					b_frontAttack = false;
					ChangeAction(Action::IDLE);
				}
				else
				{
					--frontAttackArmFrame.x;
					++frontWeaponFrame.x;
				}
			}
			attackCount = 0.0f;
		}
	}
	else
	{
		if (frontArmFrame.x > 4 &&
			frontArmFrame.x < 7)
		{
			if (frontWeaponType == WeaponType::LANCE)
			{
				frontWeaponFrame.x = 6;
			}
			else
			{
				frontWeaponFrame.x = 8;
			}
		}
		else if (frontArmFrame.x > 6 &&
			frontArmFrame.x < 9)
		{
			if (frontWeaponType == WeaponType::LANCE)
			{
				frontWeaponFrame.x = 5;
			}
			else
			{
				frontWeaponFrame.x = 7;
			}
		}
		else if (frontArmFrame.x > 8 &&
			frontArmFrame.x < 11)
		{
			if (frontWeaponType == WeaponType::LANCE)
			{
				frontWeaponFrame.x = 4;
			}
			else
			{
				frontWeaponFrame.x = 6;
			}
		}
		else if (frontArmFrame.x > 10 &&
			frontArmFrame.x < 13)
		{
			if (frontWeaponType == WeaponType::LANCE)
			{
				frontWeaponFrame.x = 3;
			}
			else
			{
				frontWeaponFrame.x = 5;
			}
		}
		else
		{
			if (frontWeaponType == WeaponType::LANCE)
			{
				frontWeaponFrame.x = 2;
			}
			else
			{
				frontWeaponFrame.x = 4;
			}
		}
	}

	if (b_backAttack)
	{
		if (attackCount > 0.0412)
		{
			if (backAttackArmFrame.x == 0)
			{
				backAttackArmFrame.x = 15;
				++backWeaponFrame.x;
			}
			else
			{
				if (backAttackArmFrame.x == 12)
				{
					b_backAttack = false;
					ChangeAction(Action::IDLE);
				}
				else
				{
					--backAttackArmFrame.x;
					++backWeaponFrame.x;
				}
			}
			attackCount = 0.0f;
		}
	}
	else
	{
		if (backArmFrame.x > 4 &&
			backArmFrame.x < 7)
		{
			if (backWeaponType == WeaponType::LANCE)
			{
				backWeaponFrame.x = 7;
			}
			else
			{
				backWeaponFrame.x = 8;
			}
		}
		else if (backArmFrame.x > 6 &&
			backArmFrame.x < 9)
		{
			if (backWeaponType == WeaponType::LANCE)
			{
				backWeaponFrame.x = 6;
			}
			else
			{
				backWeaponFrame.x = 7;
			}
		}
		else if (backArmFrame.x > 8 &&
			backArmFrame.x < 11)
		{
			if (backWeaponType == WeaponType::LANCE)
			{
				backWeaponFrame.x = 5;
			}
			else
			{
				backWeaponFrame.x = 6;
			}
		}
		else if (backArmFrame.x > 10 &&
			backArmFrame.x < 14)
		{
			if (backWeaponType == WeaponType::LANCE)
			{
				backWeaponFrame.x = 4;
			}
			else
			{
				backWeaponFrame.x = 5;
			}
		}
		else
		{
			backWeaponFrame.x = 4;
		}
	}
	Attacking();

	// 무적 시간
	if (invisibleTime > 0)
	{
		invisibleTime -= Timer::GetDeltaTime();
		invisibleCount += Timer::GetDeltaTime();
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

	// 무기 프레임, 포지션 관리
	switch (backWeaponType)
	{
	case WeaponType::SWORD:
		if (b_backAttack)
		{
			if (dir == direction::RIGHT)
			{
				if (backWeaponFrame.x < 6)
				{
					backWeaponPos.x = (int)renderPos.x - 10 + (backWeaponFrame.x * 10);
				}
				else
				{
					backWeaponPos.x = (int)renderPos.x - 10 + (backWeaponFrame.x * 10) - 15 * (backWeaponFrame.x % 6);
				}
			}
			else
			{
				if (backWeaponFrame.x < 6)
				{
					backWeaponPos.x = (int)renderPos.x + 10 - (backWeaponFrame.x * 10);
				}
				else
				{
					backWeaponPos.x = (int)renderPos.x + 10 - (backWeaponFrame.x * 10) + 15 * (backWeaponFrame.x % 6);
				}
			}

			if (backWeaponFrame.x < 6)
			{
				backWeaponPos.y = (int)renderPos.y - 55 + (backWeaponFrame.x * 8);
			}
			else
			{
				backWeaponPos.y = (int)renderPos.y - 55 + (backWeaponFrame.x * 8) + 5 * (backWeaponFrame.x % 6);
			}
		}
		else
		{
			if (dir == direction::RIGHT)
			{
				backWeaponPos.x = (int)renderPos.x + 33;
			}
			else
			{
				backWeaponPos.x = (int)renderPos.x - 30;
			}
			backWeaponPos.y = (int)renderPos.y - 37 + (backWeaponFrame.x * 5);
		}
		break;
	case WeaponType::BOOMERANG:
		if (dir == direction::RIGHT)
		{
			backWeaponPos.x = (int)renderPos.x + 27;
		}
		else
		{
			backWeaponPos.x = (int)renderPos.x - 27;
		}
		backWeaponPos.y = (int)renderPos.y - 20 + (backWeaponFrame.x * 5);
		break;
	case WeaponType::LANCE:
		if (dir == direction::RIGHT)
		{
			backWeaponPos.x = (int)renderPos.x + 27;
		}
		else
		{
			backWeaponPos.x = (int)renderPos.x - 30;
		}
		backWeaponPos.y = (int)renderPos.y - 22 + (backWeaponFrame.x * 5);
		break;
	}

	switch (frontWeaponType)
	{
	case WeaponType::SWORD:
		if (b_frontAttack)
		{
			if (dir == direction::RIGHT)
			{
				if (frontWeaponFrame.x < 6)
				{
					frontWeaponPos.x = (int)renderPos.x - 10 + (frontWeaponFrame.x * 10);
				}
				else
				{
					frontWeaponPos.x = (int)renderPos.x - 10 + (frontWeaponFrame.x * 10) - 15 * (frontWeaponFrame.x % 6);
				}
			}
			else
			{
				if (frontWeaponFrame.x < 6)
				{
					frontWeaponPos.x = (int)renderPos.x + 10 - (frontWeaponFrame.x * 10);
				}
				else
				{
					frontWeaponPos.x = (int)renderPos.x + 10 - (frontWeaponFrame.x * 10) + 15 * (frontWeaponFrame.x % 6);
				}
			}

			if (frontWeaponFrame.x < 6)
			{
				frontWeaponPos.y = (int)renderPos.y - 55 + (frontWeaponFrame.x * 8);
			}
			else
			{
				frontWeaponPos.y = (int)renderPos.y - 55 + (frontWeaponFrame.x * 8) + 5 * (frontWeaponFrame.x % 6);
			}
		}
		else
		{
			if (dir == direction::RIGHT)
			{
				frontWeaponPos.x = (int)renderPos.x + 18;
			}
			else
			{
				frontWeaponPos.x = (int)renderPos.x - 20;
			}
			frontWeaponPos.y = (int)renderPos.y - 30 + (frontWeaponFrame.x * 5);
		}
		break;
	case WeaponType::BOOMERANG:
		if (dir == direction::RIGHT)
		{
			frontWeaponPos.x = (int)renderPos.x ;
		}
		else
		{
			frontWeaponPos.x = (int)renderPos.x ;
		}
		frontWeaponPos.y = (int)renderPos.y - 13 + (frontWeaponFrame.x * 5);
		break;
	case WeaponType::LANCE:
		if (dir == direction::RIGHT)
		{
			frontWeaponPos.x = (int)renderPos.x + 7;
		}
		else
		{
			frontWeaponPos.x = (int)renderPos.x - 18;
		}
		frontWeaponPos.y = (int)renderPos.y - 15 + (frontWeaponFrame.x * 5);
		break;
	}
}

bool Player::CheckCollision(SubjectTag _subject, RECT _shape, EventTag _eventTag)
{
	RECT tempRect;
	bool temp = false;

	if (IntersectRect(&tempRect, &_shape, &this->shape))
	{
		if (tempRect.left >= _shape.left &&
			tempRect.right <= _shape.right &&
			(((_shape.top + _shape.bottom) / 2) + _shape.top) / 2 > tempRect.bottom)
		{
			temp = true;
		}
		else
		{
			temp = false;
		}

		switch (_subject)
		{
		case SubjectTag::IDLE:
			break;
		case SubjectTag::MONSTER:
			if (_eventTag == EventTag::RANGECOLLISION)
			{
				return true;
			}
			if (temp == false)
			{
				ToBeHit();
				return true;
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
		case SubjectTag::AMMO:
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
	jumpingPower = 50;
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

bool Player::EquipItem(ItemType itemType, ItemGrade itemGrade, WeaponType weaponType, bool changeItem, int dir)
{
	string tempitemName = "image/player/";
	string tempR_itemName = "image/player/";

	switch (itemType)
	{
	case ItemType::IDLE:
		break;
	case ItemType::HELMET:
		if (b_equipHelmet == false || changeItem)
		{
			if (b_equipHelmet)
			{
				playerInventory->GetItem(ItemType::HELMET, this->helmetGrade);
			}
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
			playerInventory->GetItem(itemType, itemGrade, weaponType);
		}
		break;
	case ItemType::ARMOR:
		if (b_equipArmor == false || changeItem)
		{
			if (b_equipArmor)
			{
				playerInventory->GetItem(ItemType::ARMOR, this->armorGrade);
			}
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
				tempitemName += "white/body.bmp";
				tempR_itemName += "white/R_body.bmp";
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
			playerInventory->GetItem(itemType, itemGrade, weaponType);
		}
		break;
	case ItemType::WEAPON:
		tempitemName = "image/item/";
		tempR_itemName = "image/item/";
		// 두 손에 아이템이 있을경우
		if (b_equipBackWeapon && b_equipFrontWeapon && (changeItem == false))
		{
			playerInventory->GetItem(itemType, itemGrade, weaponType);
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
					tempitemName += "골드칼_SP.bmp";
					tempR_itemName += "R_골드칼_SP.bmp";
					break;
				case ItemGrade::SILVER:
					tempitemName += "흰색칼_SP.bmp";
					tempR_itemName += "R_흰색칼_SP.bmp";
					break;
				}
				break;
			case WeaponType::BOOMERANG:
				switch (itemGrade)
				{
				case ItemGrade::BASIC:
					break;
				case ItemGrade::GOLD:
					tempitemName += "골드부메랑_SP.bmp";
					tempR_itemName += "R_골드부메랑_SP.bmp";
					break;
				case ItemGrade::SILVER:
					tempitemName += "흰색부메랑_SP.bmp";
					tempR_itemName += "R_흰색부메랑_SP.bmp";
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
					tempR_itemName += "R_골드랜스_SP.bmp";
					break;
				case ItemGrade::SILVER:
					tempitemName += "흰색랜스_SP.bmp";
					tempR_itemName += "R_흰색랜스_SP.bmp";
					break;
				}
				break;
			}

			// back 손이 비어있으면 먼저 장착 
			if ((b_equipBackWeapon == false || changeItem) && dir == 0)
			{
				if (b_equipBackWeapon)
				{
					playerInventory->GetItem(ItemType::WEAPON, backWeaponGrade, backWeaponType);
				}
				b_equipBackWeapon = true;
				backWeaponGrade = itemGrade;
				backWeaponType = weaponType;
				backWeaponFrame.x = 1;
				backWeapon = ImageManager::GetSingleton()->FindImage(tempitemName.c_str());
				if (backWeapon == nullptr)
				{
					return false;
				}
				R_backWeapon = ImageManager::GetSingleton()->FindImage(tempR_itemName.c_str());
				if (R_backWeapon == nullptr)
				{
					return false;
				}
				return true;
			}
			else
			{
				if (b_equipFrontWeapon)
				{
					playerInventory->GetItem(ItemType::WEAPON, frontWeaponGrade, frontWeaponType);
				}
				b_equipFrontWeapon = true;
				frontWeaponGrade = itemGrade;
				frontWeaponType = weaponType;
				frontWeaponFrame.x = 3;

				frontWeapon = ImageManager::GetSingleton()->FindImage(tempitemName.c_str());
				if (frontWeapon == nullptr)
				{
					return false;
				}
				R_frontWeapon = ImageManager::GetSingleton()->FindImage(tempR_itemName.c_str());
				if (R_frontWeapon == nullptr)
				{
					return false;
				}
				return true;
			}
			break;
		}
		break;
	case ItemType::SHOES:
		if (b_equipShoes == false || changeItem)
		{
			if (b_equipShoes)
			{
				playerInventory->GetItem(ItemType::SHOES, this->shoesGrade);
			}
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
				tempitemName += "white/foot.bmp";
				tempR_itemName += "white/R_foot.bmp";
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
			playerInventory->GetItem(itemType, itemGrade, weaponType);
		}

		break;
	case ItemType::OLIS:
		playerInventory->GetItem(itemType, itemGrade, weaponType);
		break;
	}
	return false;
}

void Player::AttackHit()
{
	b_backAttack = false;
	b_frontAttack = false;
}

void Player::Attacking()
{
	if (b_frontAttack)
	{
		if (frontWeaponType == WeaponType::SWORD && frontWeaponFrame.x > 1)
		{
				POINT tempBodySize = { 25, 15 };
				DBattackShape.left = frontWeaponPos.x - tempBodySize.x + (int)CameraManager::GetSingleton()->GetPos().x + 10;
				DBattackShape.top = frontWeaponPos.y - tempBodySize.y + (int)CameraManager::GetSingleton()->GetPos().y - 10;
				DBattackShape.right = frontWeaponPos.x + tempBodySize.x + (int)CameraManager::GetSingleton()->GetPos().x + 10;
				DBattackShape.bottom = frontWeaponPos.y + tempBodySize.y + (int)CameraManager::GetSingleton()->GetPos().y - 10;
				CollisionManager::GetSingleton()->CheckCollision(SubjectTag::WEAPON, DBattackShape);
				if (MapColliderManager::GetSingleton()->checkCollision(SubjectTag::WEAPON, DBattackShape, (int)dir, tempBodySize))
				{
					AttackHit();
				}
			
		}
	}
	else if (b_backAttack)
	{
		if (backWeaponType == WeaponType::SWORD && backWeaponFrame.x >1)
		{
			POINT tempBodySize = { 25, 15 };
			DBattackShape.left = backWeaponPos.x - tempBodySize.x + (int)CameraManager::GetSingleton()->GetPos().x + 10;
			DBattackShape.top = backWeaponPos.y - tempBodySize.y + (int)CameraManager::GetSingleton()->GetPos().y - 10;
			DBattackShape.right = backWeaponPos.x + tempBodySize.x + (int)CameraManager::GetSingleton()->GetPos().x + 10;
			DBattackShape.bottom = backWeaponPos.y + tempBodySize.y + (int)CameraManager::GetSingleton()->GetPos().y - 10;
			CollisionManager::GetSingleton()->CheckCollision(SubjectTag::WEAPON, DBattackShape);
			if (MapColliderManager::GetSingleton()->checkCollision(SubjectTag::WEAPON, DBattackShape, (int)dir, tempBodySize))
			{
				AttackHit();
			}
		}
	}
}


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

		shape.left = (int)pos.x - bodySize.x / 2;
		shape.top = (int)pos.y - bodySize.y / 2;
		shape.right = (int)pos.x + bodySize.x / 2;
		shape.bottom = (int)pos.y + bodySize.y / 2;

		if (b_sitDownCamera)
		{
			renderPos.y += 200;
			CameraManager::GetSingleton()->SetPosY(-200);
			b_sitDownCamera = false;
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

		shape.left = (int)pos.x - bodySize.x / 2;
		shape.top = (int)pos.y - bodySize.y / 2 + 10;
		shape.right = (int)pos.x + bodySize.x / 2;
		shape.bottom = (int)pos.y + bodySize.y / 2;
	}



}
