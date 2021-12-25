//#include "stdafx.h"
#include "TestItem.h"
#include "Image.h"

HRESULT TestItem::Init(POINTFLOAT pos, ItemType itemType, ItemGrade itemGrade, WeaponType weaponType)
{
	string itemName = "image/item/";

	this->pos = pos;
	this->itemType = itemType;
	this->itemGrade = itemGrade;
	this->weaponType = weaponType;
	switch (itemType)
	{
	case ItemType::IDLE:
		break;
	case ItemType::HELMET:
		switch (itemGrade)
		{
		case ItemGrade::IDLE:
			break;
		case ItemGrade::BASIC:
			break;
		case ItemGrade::GOLD:
			itemName += "È²Åõ.bmp";
			break;
		case ItemGrade::SILVER:
			break;
		}
		break;
	case ItemType::ARMOR:
		switch (itemGrade)
		{
		case ItemGrade::IDLE:
			break;
		case ItemGrade::BASIC:
			break;
		case ItemGrade::GOLD:
			itemName += "È²°©.bmp";
			break;
		case ItemGrade::SILVER:
			itemName += "¹é°©.bmp";
			break;
		}
			bodySize.x = 10;
			bodySize.y = 10;
		break;
	case ItemType::WEAPON:
		switch (weaponType)
		{
		case WeaponType::IDLE:
			switch (itemGrade)
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
			switch (itemGrade)
			{
			case ItemGrade::IDLE:
				break;
			case ItemGrade::BASIC:
				break;
			case ItemGrade::GOLD:
				itemName += "°ñµåÄ®.bmp";
				break;
			case ItemGrade::SILVER:
				itemName += "Èò»öÄ®.bmp";
				break;
			}
			bodySize.x = 25;
			bodySize.y = 10;
			break;
		case WeaponType::BOOMERANG:
			switch (itemGrade)
			{
			case ItemGrade::IDLE:
				break;
			case ItemGrade::BASIC:
				break;
			case ItemGrade::GOLD:
				itemName += "°ñµåºÎ¸Þ¶û.bmp";
				break;
			case ItemGrade::SILVER:
				itemName += "Èò»öºÎ¸Þ¶û.bmp";
				break;
			}
			bodySize.x = 10;
			bodySize.y = 10;
			break;
		case WeaponType::LANCE:
			switch (itemGrade)
			{
			case ItemGrade::IDLE:
				break;
			case ItemGrade::BASIC:
				break;
			case ItemGrade::GOLD:
				itemName += "°ñµå·£½º.bmp";
				
				break;
			case ItemGrade::SILVER:
				itemName += "Èò»ö·£½º.bmp";
				break;
			}
			bodySize.x = 30;
			bodySize.y = 10;
			break;
		}

		break;
	case ItemType::SHOES:
		switch (itemGrade)
		{
		case ItemGrade::IDLE:
			break;
		case ItemGrade::BASIC:
			break;
		case ItemGrade::GOLD:
			itemName += "È²½Å.bmp";
			bodySize.x = 5;
			bodySize.y = 5;
			break;
		case ItemGrade::SILVER:
			itemName += "¹é½Å.bmp";
			break;
		}
		bodySize.x = 5;
		bodySize.y = 5;
		break;
	case ItemType::OLIS:
		switch (itemGrade)
		{
		case ItemGrade::IDLE:
			break;
		case ItemGrade::BASIC:
			break;
		case ItemGrade::GOLD:
			itemName += "°ñµå¿ÀÀÏ.bmp";
			bodySize.x = 5;
			bodySize.y = 5;
			break;
		case ItemGrade::SILVER:
			break;
		default:
			break;
		}
		break;
	}

	itemImage = ImageManager::GetSingleton()->FindImage(itemName.c_str());
	if (itemImage == nullptr)
	{
		return E_FAIL;
	}

	renderPos = pos;

	moveSpeed = 200;

	renderPos.x = pos.x - CameraManager::GetSingleton()->GetPos().x;
	renderPos.y = pos.y - CameraManager::GetSingleton()->GetPos().y;

	shape.left = (int)pos.x - bodySize.x;
	shape.top = (int)pos.y - bodySize.y;
	shape.right = (int)pos.x + bodySize.x;
	shape.bottom = (int)pos.y + bodySize.y;

	return S_OK;
}

void TestItem::Update()
{
	if (MapColliderManager::GetSingleton()->IsFalling(pos, shape, 100, bodySize, subTag))
	{
		pos.y += moveSpeed * Timer::GetDeltaTime();
	}

	renderPos.x = pos.x - CameraManager::GetSingleton()->GetPos().x;
	renderPos.y = pos.y - CameraManager::GetSingleton()->GetPos().y;

	shape.left = (int)pos.x - bodySize.x;
	shape.top = (int)pos.y - bodySize.y;
	shape.right = (int)pos.x + bodySize.x;
	shape.bottom = (int)pos.y + bodySize.y;

	if (Input::GetButtonDown(VK_NUMPAD9))
	{
		DBrect == false ? DBrect = true : DBrect = false;
	}
}

void TestItem::Render(HDC hdc)
{
	itemImage->Render(hdc, (int)renderPos.x, (int)renderPos.y);



	if (DBrect)
		Rectangle(hdc, shape.left - (int)CameraManager::GetSingleton()->GetPos().x,
			shape.top - (int)CameraManager::GetSingleton()->GetPos().y,
			shape.right - (int)CameraManager::GetSingleton()->GetPos().x,
			shape.bottom - (int)CameraManager::GetSingleton()->GetPos().y);
}

void TestItem::Release()
{

}
