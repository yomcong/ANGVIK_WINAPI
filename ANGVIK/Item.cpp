#include "Item.h"
#include "Image.h"
#include "ItemManager.h"

HRESULT Item::Init()
{
	//string itemName = "Image/Item/Item";
	//itemName += to_string(type+1); // ����
	//itemName += ".bmp";

	//itemImage = ImageManager::GetSingleton()->FindImage(itemName.c_str()); // sprintf()�� ������ �� �� ������� �ʾ����� ����.
	//if (itemImage == nullptr)
	//{
	//	return E_FAIL;
	//}

	this->itemManager = itemManager;

	return S_OK;
}

void Item::Update()
{
	if (useItem)
	{
		elapsedcount++;
		if (elapsedcount >= 30)
		{
			//GetItemManager()->UseItem();
			elapsedcount = 0;
		}
	}
}

void Item::Render(HDC hdc)
{
}

void Item::Release()
{
}

void Item::UseItem()
{

}

void HelmetItem::UseItem()
{
}

void ClockItem::UseItem()
{
}

void ShovelItem::UseItem()
{
}

void StarItem::UseItem()
{
}

void GrenadeItem::UseItem()
{
}

void TankLifeItem::UseItem()
{
}
