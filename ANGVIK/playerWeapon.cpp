#include "playerWeapon.h"
#include "Image.h"
#include "ItemManager.h"

HRESULT playerWeapon::Init(SubjectTag _subTag, ItemGrade _itemGrade, WeaponType _weaponType, ItemManager* _itemManager)
{
	string itemName = "image/item/";
	string R_itemName = "image/item/";

	switch (_weaponType)
	{
	case WeaponType::IDLE:
		switch (_itemGrade)
		{
		case ItemGrade::IDLE:
			break;
		case ItemGrade::BASIC:
			break;
		case ItemGrade::GOLD:
			break;
		case ItemGrade::SILVER:
			break;
		}
		break;
	case WeaponType::SWORD:
		switch (_itemGrade)
		{
		case ItemGrade::IDLE:
			break;
		case ItemGrade::BASIC:
			break;
		case ItemGrade::GOLD:
			itemName += "°ñµåÄ®.bmp";
			R_itemName += "R_°ñµåÄ®.bmp";
			bodySize.x = 25;
			bodySize.y = 10;
			break;
		case ItemGrade::SILVER:
			break;
		}
		break;
	case WeaponType::BOOMERANG:
		switch (_itemGrade)
		{
		case ItemGrade::IDLE:
			break;
		case ItemGrade::BASIC:
			break;
		case ItemGrade::GOLD:
			itemName += "°ñµåºÎ¸Þ¶û_SP.bmp";
			R_itemName += "R_°ñµåºÎ¸Þ¶û_SP.bmp";
			bodySize.x = 30;
			bodySize.y = 30;
			break;
		case ItemGrade::SILVER:
			break;
		}
		break;
	case WeaponType::LANCE:
		switch (_itemGrade)
		{
		case ItemGrade::IDLE:
			break;
		case ItemGrade::BASIC:
			break;
		case ItemGrade::GOLD:
			itemName += "°ñµå·£½º_SP.bmp";
			R_itemName += "R_°ñµå·£½º_SP.bmp";
			bodySize.x = 70;
			bodySize.y = 15;
			break;
		case ItemGrade::SILVER:
			break;
		}
		break;
	}

	weaponImage = ImageManager::GetSingleton()->FindImage(itemName.c_str());
	if (weaponImage == nullptr)
	{
		return E_FAIL;
	}
	R_weaponImage = ImageManager::GetSingleton()->FindImage(R_itemName.c_str());
	if (R_weaponImage == nullptr)
	{
		return E_FAIL;
	}

	itemManager = _itemManager;

	subTag = _subTag;
	myGrade = _itemGrade;
	myType = _weaponType;

	moveSpeed = 400.0f;

	b_isAlive = false;

	return S_OK;
}

void playerWeapon::Update()
{
	if (b_isAlive)
	{
		if (dir == direction::RIGHT)
		{
			pos.x += moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
		}
		else
		{
			pos.x -= moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
		}
		
		if (MapColliderManager::GetSingleton()->checkCollision(subTag, shape, (int)dir, bodySize) ||
			CollisionManager::GetSingleton()->CheckCollision(subTag, shape))
		{
			b_isAlive = false;
			itemManager->CreateItem(subTag, pos, myType, myGrade);
		}

		if (renderPos.x <0 || renderPos.x >WIN_SIZE_X ||
			renderPos.y <0 || renderPos.y > WIN_SIZE_Y)
		{
			b_isAlive = false;
		}

		PosUpdate();
		PlayAnimation();

		if (Input::GetButtonDown(VK_NUMPAD9))
		{
			DBrect = !DBrect;
		}
	}
}

void playerWeapon::Render(HDC hdc)
{
	if (b_isAlive)
	{
		if (dir == direction::RIGHT)
		{
			weaponImage->Render(hdc, (int)renderPos.x, (int)renderPos.y, weaponFrame, 0);
		}
		else
		{
			R_weaponImage->Render(hdc, (int)renderPos.x, (int)renderPos.y, weaponFrame, 0);
		}

		if (DBrect)
			Rectangle(hdc, shape.left - (int)CameraManager::GetSingleton()->GetPos().x,
				shape.top - (int)CameraManager::GetSingleton()->GetPos().y,
				shape.right - (int)CameraManager::GetSingleton()->GetPos().x,
				shape.bottom - (int)CameraManager::GetSingleton()->GetPos().y);
	}
}

void playerWeapon::Release()
{
}

void playerWeapon::PlayAnimation()
{
	frameCount += TimerManager().GetSingleton()->GetDeltaTime();

	switch (myType)
	{
	case WeaponType::BOOMERANG:
		if (frameCount > 0.0125)
		{
			if (weaponFrame == 23)
			{
				weaponFrame = 0;
			}
			else
			{
				++weaponFrame;
			}
			frameCount = 0.0f;
		}
		break;
	case WeaponType::LANCE:
		weaponFrame = 6;
		break;
	case WeaponType::STAFF:
		break;
	default:
		break;
	}
}

void playerWeapon::PosUpdate()
{
	renderPos.x = pos.x - CameraManager::GetSingleton()->GetPos().x;
	renderPos.y = pos.y - CameraManager::GetSingleton()->GetPos().y;

	shape.left = (int)pos.x - bodySize.x / 2;
	shape.top = (int)pos.y - bodySize.y / 2;
	shape.right = (int)pos.x + bodySize.x / 2;
	shape.bottom = (int)pos.y + bodySize.y / 2;
}

bool playerWeapon::WeaponFire(POINTFLOAT _pos, int _dir)
{
	pos = _pos;
	renderPos = pos;

	if (_dir > 0)
	{
		dir = direction::RIGHT;
	}
	else
	{
		dir = direction::LEFT;
	}

	shape.left = (int)pos.x - bodySize.x / 2;
	shape.top = (int)pos.y - bodySize.y / 2;
	shape.right = (int)pos.x + bodySize.x / 2;
	shape.bottom = (int)pos.y + bodySize.y / 2;

	b_isAlive = true;

	weaponFrame = 0;

	PosUpdate();
	return true;
}
