//#include "stdafx.h"
#include "Inventory.h"
#include "Image.h"
#include "Player.h"

HRESULT Inventory::Init(Player* player)
{
	inventoryUi = ImageManager::GetSingleton()->FindImage("image/etc/inventory.bmp");
	if (inventoryUi == nullptr)
	{
		return E_FAIL;
	}
	ItemBox = ImageManager::GetSingleton()->FindImage("image/etc/itemBox.bmp");
	if (ItemBox == nullptr)
	{
		return E_FAIL;
	}
	olis = ImageManager::GetSingleton()->FindImage("image/etc/oilsBox.bmp");
	if (olis == nullptr)
	{
		return E_FAIL;
	}
	itemsText = ImageManager::GetSingleton()->FindImage("image/etc/item.bmp");
	if (itemsText == nullptr)
	{
		return E_FAIL;
	}
	closeText = ImageManager::GetSingleton()->FindImage("image/etc/close.bmp");
	if (closeText == nullptr)
	{
		return E_FAIL;
	}
	oilsText = ImageManager::GetSingleton()->FindImage("image/etc/oils.bmp");
	if (oilsText == nullptr)
	{
		return E_FAIL;
	}
	backText = ImageManager::GetSingleton()->FindImage("image/etc/back.bmp");
	if (backText == nullptr)
	{
		return E_FAIL;
	}
	selectBox = ImageManager::GetSingleton()->FindImage("image/etc/select.bmp");
	if (selectBox == nullptr)
	{
		return E_FAIL;
	}
	seletItem = ImageManager::GetSingleton()->FindImage("image/etc/SELET.bmp");
	if (seletItem == nullptr)
	{
		return E_FAIL;
	}
	equipText = ImageManager::GetSingleton()->FindImage("image/etc/equip.bmp");
	if (equipText == nullptr)
	{
		return E_FAIL;
	}
	dropText = ImageManager::GetSingleton()->FindImage("image/etc/drop.bmp");
	if (dropText == nullptr)
	{
		return E_FAIL;
	}
	backHText = ImageManager::GetSingleton()->FindImage("image/etc/backH.bmp");
	if (backHText == nullptr)
	{
		return E_FAIL;
	}
	frontHText = ImageManager::GetSingleton()->FindImage("image/etc/frontH.bmp");
	if (frontHText == nullptr)
	{
		return E_FAIL;
	}

	this->player = player;

	vecItems.reserve(itemMaximum);
	vecOils.reserve(oilsMaximum);
	vecItemInfos.reserve(itemMaximum);
	vecOilsInfos.reserve(oilsMaximum);
	return S_OK;
}

void Inventory::Update()
{
	if (b_inventoryOpen)
	{
		if (Input::GetButtonDown(VK_UP))
		{
			if (selectedNum > 0)
			{
				--selectedNum;;
			}
		}
		if (Input::GetButtonDown(VK_DOWN))
		{
			if (inventoryType == InventoryType::MAIN)
			{
				if (selectedNum < 2)
				{
					++selectedNum;
				}
			}
			else if (inventoryType == InventoryType::ITEMBOX)
			{
				if (selectedNum < itemMaximum)
				{
					++selectedNum;
				}
			}
			else if (inventoryType == InventoryType::OILSBOX)
			{
				if (selectedNum < oilsMaximum)
				{
					++selectedNum;
				}
			}
			else if (inventoryType == InventoryType::SELECTITEM)
			{
				if (selectedNum < 3)
				{
					++selectedNum;
				}
			}
			else if (inventoryType == InventoryType::SELECTOILS)
			{
				if (selectedNum < 2)
				{
					++selectedNum;
				}
			}
		}
		if (Input::GetButtonDown('S'))
		{
			if (inventoryType == InventoryType::MAIN)
			{
				if (selectedNum == 0)
				{
					inventoryType = InventoryType::ITEMBOX;
					selectedNum = 0;
				}
				else if (selectedNum == 1)
				{
					inventoryType = InventoryType::OILSBOX;
					selectedNum = 0;
				}
				else
				{
					player->SetInventoryClose(false);
					b_inventoryOpen = false;
				}
			}
			else if (inventoryType == InventoryType::ITEMBOX)
			{
				if (selectedNum == itemMaximum)
				{
					inventoryType = InventoryType::MAIN;
					selectedNum = 0;
				}
				else
				{
					if (selectedNum < vecItems.size())
					{
						inventoryType = InventoryType::SELECTITEM;
						selectItemType = SelectItem::EQUIPMENT;
						selectedItemNum = selectedNum;
						selectedNum = 0;
					}
				}
			}
			else if (inventoryType == InventoryType::OILSBOX)
			{
				if (selectedNum == oilsMaximum)
				{
					inventoryType = InventoryType::MAIN;
					selectedNum = 0;
				}
				else
				{
					if (selectedNum < vecOils.size())
					{
						inventoryType = InventoryType::SELECTOILS;
						selectItemType = SelectItem::OILS;
						selectedItemNum = selectedNum;
						selectedNum = 0;
					}
				}
			}
			else if (inventoryType == InventoryType::SELECTITEM)
			{
				if (selectedNum == 3)
				{
					inventoryType = InventoryType::ITEMBOX;
					selectedNum = 0;
				}
				else if (selectedNum == 0 ||
					selectedNum == 1)
				{
					vecItems[selectedItemNum] = nullptr;
					vecItems.erase(vecItems.begin() + selectedItemNum);
					// ���� ������ ���� �Ѱ��ֱ�
					player->EquipItem(vecItemInfos[selectedItemNum].itemType,
						vecItemInfos[selectedItemNum].itemgrade,
						vecItemInfos[selectedItemNum].weaponType, true, selectedNum);
					// �̹��� nullptr
					// ���Ϳ��� �ش� ������ ����
					vecItemInfos.erase(vecItemInfos.begin() + selectedItemNum);
					// ���� ȭ������ 
					inventoryType = InventoryType::ITEMBOX;
					selectedNum = 0;
				}
				else if (selectedNum == 2)
				{
					// ������ ���
				}
			}
			else if (inventoryType == InventoryType::SELECTOILS)
			{
				if (selectedNum == 2)
				{
					inventoryType = InventoryType::OILSBOX;
					selectedNum = 0;
				}
				else if (selectedNum == 0)
				{
					// ��æƮ
				}
				else if (selectedNum == 1)
				{
					// ������ ���
				}
			}
		}
		if (Input::GetButtonDown(VK_ESCAPE))
		{
			b_inventoryOpen = false;
			player->SetInventoryClose(false);
		}
	}
	PosUpdate();

}

void Inventory::Render(HDC hdc)
{
	if (inventoryType == InventoryType::MAIN)
	{
		inventoryUi->Render(hdc, (int)pos.x, (int)pos.y);
		selectBox->Render(hdc, selectBoxPos.x, selectBoxPos.y);
		itemsText->Render(hdc, itemTextPos.x, itemTextPos.y);
		oilsText->Render(hdc, oilsTextPos.x, oilsTextPos.y);
		closeText->Render(hdc, closeTextPos.x, closeTextPos.y);
	}
	else if (inventoryType == InventoryType::ITEMBOX)
	{
		ItemBox->Render(hdc, (int)pos.x, (int)pos.y);
		selectBox->Render(hdc, selectBoxPos.x, selectBoxPos.y);
		for (int i = 0; i < vecItems.size(); ++i)
		{
			vecItems[i]->Render(hdc, (int)itemPos.x, (int)itemPos.y + (35 * i));
		}
		backText->Render(hdc, backTextPos.x, backTextPos.y);
	}
	else if (inventoryType == InventoryType::OILSBOX)
	{
		olis->Render(hdc, (int)pos.x, (int)pos.y);
		selectBox->Render(hdc, selectBoxPos.x, selectBoxPos.y);
		for (int i = 0; i < vecOils.size(); ++i)
		{
			vecOils[i]->Render(hdc, (int)oilsPos.x, (int)oilsPos.y + (35 * i));
		}
		backText->Render(hdc, backTextPos.x, backTextPos.y);
	}
	else if (inventoryType == InventoryType::SELECTITEM)
	{
		seletItem->Render(hdc, (int)pos.x, (int)pos.y);
		if (selectItemType == SelectItem::EQUIPMENT)
		{
			vecItems[selectedItemNum]->Render(hdc, (int)itemPos.x, (int)itemPos.y);
		}
		else
		{
			vecOils[selectedItemNum]->Render(hdc, (int)itemPos.x, (int)itemPos.y);
		}
		selectBox->Render(hdc, selectBoxPos.x, selectBoxPos.y);
		backHText->Render(hdc, backHTextPos.x, backHTextPos.y);
		frontHText->Render(hdc, frontHTextPos.x, frontHTextPos.y);
		dropText->Render(hdc, dropTextPos.x, dropTextPos.y);
		backText->Render(hdc, backTextPos.x, backTextPos.y);
	}
	else if (inventoryType == InventoryType::SELECTOILS)
	{
		seletItem->Render(hdc, (int)pos.x, (int)pos.y);
		if (selectItemType == SelectItem::EQUIPMENT)
		{
			vecItems[selectedItemNum]->Render(hdc, (int)itemPos.x, (int)itemPos.y);
		}
		else
		{
			vecOils[selectedItemNum]->Render(hdc, (int)itemPos.x, (int)itemPos.y);
		}
		selectBox->Render(hdc, selectBoxPos.x, selectBoxPos.y);
		equipText->Render(hdc, equipTextPos.x, equipTextPos.y);
		dropText->Render(hdc, dropTextPos.x, dropTextPos.y);
		backText->Render(hdc, backTextPos.x, backTextPos.y);
	}


}

void Inventory::Release()
{
}

void Inventory::PosUpdate()
{
	if (inventoryType == InventoryType::MAIN)
	{
		selectBoxPos.y = (int)this->pos.y - 20 + (35 * selectedNum);
	}
	else if (inventoryType == InventoryType::ITEMBOX)
	{
		selectBoxPos.y = (int)this->pos.y - 57 + (35 * selectedNum);
		backTextPos.y = (int)this->pos.y + 82;

	}
	else if (inventoryType == InventoryType::OILSBOX)
	{
		selectBoxPos.y = (int)this->pos.y - 42 + (35 * selectedNum);
		backTextPos.y = (int)this->pos.y + 62;
	}
	else if (inventoryType == InventoryType::SELECTITEM)
	{
		selectBoxPos.y = (int)this->pos.y - 30 + (30 * selectedNum);
		backTextPos.y = (int)this->pos.y + 62;
		dropTextPos.x = (int)pos.x;
		dropTextPos.y = (int)pos.y + 30;
		backHTextPos.x = (int)pos.x;
		backHTextPos.y = (int)pos.y - 30;
		frontHTextPos.x = (int)pos.x;
		frontHTextPos.y = (int)pos.y;
	}
	else if (inventoryType == InventoryType::SELECTOILS)
	{
		selectBoxPos.y = (int)this->pos.y - 20 + (35 * selectedNum);
		backTextPos.y = (int)this->pos.y + 50;
		dropTextPos.x = (int)pos.x;
		dropTextPos.y = (int)pos.y + 18;
	}
	itemPos.x = (int)pos.x;
	itemPos.y = (int)pos.y - 56;
	oilsPos.x = (int)pos.x;
	oilsPos.y = (int)pos.y - 42;
	equipTextPos.x = (int)pos.x;
	equipTextPos.y = (int)pos.y - 20;


}

void Inventory::InventoryOpen(POINTFLOAT pos)
{
	this->pos.x = pos.x + 100;
	this->pos.y = pos.y - 100;

	itemTextPos.x = (int)this->pos.x;
	itemTextPos.y = (int)this->pos.y - 20;

	oilsTextPos.x = (int)this->pos.x;
	oilsTextPos.y = (int)this->pos.y + 15;

	closeTextPos.x = (int)this->pos.x;
	closeTextPos.y = (int)this->pos.y + 50;

	selectBoxPos.x = (int)this->pos.x;
	selectBoxPos.y = (int)this->pos.y - 20;

	inventoryType = InventoryType::MAIN;

	backTextPos.x = (int)this->pos.x;
	backTextPos.y = (int)this->pos.y;

	selectedNum = 0;

}

bool Inventory::GetItem(ItemType itemType, ItemGrade itemGrade, WeaponType weaponType)
{
	string itemName = "image/item/";
	ItemInfo tempInfo = {};
	if (itemType == ItemType::OLIS)
	{
		if (vecOils.size() == oilsMaximum)
		{
			// ������ ����ϱ�
			return false;
		}
	}
	else
	{
		if (vecItems.size() == itemMaximum)
		{
			// ������ ����ϱ�
			return false;
		}
	}
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
			itemName += "Ȳ��.bmp";
			tempInfo.itemgrade = ItemGrade::GOLD;
			tempInfo.itemType = ItemType::HELMET;
			vecItemInfos.push_back(tempInfo);
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
			itemName += "Ȳ��.bmp";
			tempInfo.itemgrade = ItemGrade::GOLD;
			tempInfo.itemType = ItemType::ARMOR;
			vecItemInfos.push_back(tempInfo);
			break;
		case ItemGrade::SILVER:
			break;
		}
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
				itemName += "���Į.bmp";
				tempInfo.itemgrade = ItemGrade::GOLD;
				tempInfo.itemType = ItemType::WEAPON;
				tempInfo.weaponType = WeaponType::SWORD;
				vecItemInfos.push_back(tempInfo);
				break;
			case ItemGrade::SILVER:
				itemName += "���Į.bmp";
				tempInfo.itemgrade = ItemGrade::SILVER;
				tempInfo.itemType = ItemType::WEAPON;
				tempInfo.weaponType = WeaponType::SWORD;
				vecItemInfos.push_back(tempInfo);
				break;
			}
			break;
		case WeaponType::BOOMERANG:
			switch (itemGrade)
			{
			case ItemGrade::IDLE:
				break;
			case ItemGrade::BASIC:
				break;
			case ItemGrade::GOLD:
				itemName += "���θ޶�.bmp";
				tempInfo.itemgrade = ItemGrade::GOLD;
				tempInfo.itemType = ItemType::WEAPON;
				tempInfo.weaponType = WeaponType::BOOMERANG;
				vecItemInfos.push_back(tempInfo);
				break;
			case ItemGrade::SILVER:
				itemName += "����θ޶�.bmp";
				tempInfo.itemgrade = ItemGrade::SILVER;
				tempInfo.itemType = ItemType::WEAPON;
				tempInfo.weaponType = WeaponType::BOOMERANG;
				vecItemInfos.push_back(tempInfo);
				break;
			}
			break;
		case WeaponType::LANCE:
			switch (itemGrade)
			{
			case ItemGrade::IDLE:
				break;
			case ItemGrade::BASIC:
				break;
			case ItemGrade::GOLD:
				itemName += "��巣��.bmp";
				tempInfo.itemgrade = ItemGrade::GOLD;
				tempInfo.itemType = ItemType::WEAPON;
				tempInfo.weaponType = WeaponType::LANCE;
				vecItemInfos.push_back(tempInfo);
				break;
			case ItemGrade::SILVER:
				itemName += "�������.bmp";
				tempInfo.itemgrade = ItemGrade::GOLD;
				tempInfo.itemType = ItemType::WEAPON;
				tempInfo.weaponType = WeaponType::LANCE;
				vecItemInfos.push_back(tempInfo);
				break;
			}
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
			itemName += "Ȳ��.bmp";
			tempInfo.itemgrade = ItemGrade::GOLD;
			tempInfo.itemType = ItemType::SHOES;
			vecItemInfos.push_back(tempInfo);
			break;
		case ItemGrade::SILVER:
			break;
		default:
			break;
		}
		break;
	case ItemType::OLIS:
		switch (itemGrade)
		{
		case ItemGrade::IDLE:
			break;
		case ItemGrade::BASIC:
			break;
		case ItemGrade::GOLD:
			itemName += "������.bmp";
			tempInfo.itemgrade = ItemGrade::GOLD;
			tempInfo.itemType = ItemType::OLIS;
			vecOilsInfos.push_back(tempInfo);
			break;
		case ItemGrade::SILVER:
			break;
		default:
			break;
		}
		break;
	}
	Image* tempImage = ImageManager::GetSingleton()->FindImage(itemName.c_str());


	if (itemType == ItemType::OLIS)
	{
		if ((vecOils.size() == oilsMaximum) == false)
		{
			vecOils.push_back(tempImage);
		}
	}
	else
	{
		if ((vecItems.size() == itemMaximum) == false)
		{
			vecItems.push_back(tempImage);
		}
	}


	return false;
}
