#include "ImageManager.h"
#include "Image.h"

void ImageManager::Init()
{
	// ������ 
	/*AddImage("Image/Item/Item1.bmp", 32, 32, true, RGB(255, 0, 255));
	AddImage("Image/Item/Item2.bmp", 32, 32, true, RGB(255, 0, 255));
	AddImage("Image/Item/Item3.bmp", 32, 32, true, RGB(255, 0, 255));
	AddImage("Image/Item/Item4.bmp", 32, 32, true, RGB(255, 0, 255));
	AddImage("Image/Item/Item5.bmp", 32, 32, true, RGB(255, 0, 255));
	AddImage("Image/Item/Item6.bmp", 32, 32, true, RGB(255, 0, 255));
	AddImage("Image/Item/Item7.bmp", 32, 32, true, RGB(255, 0, 255));*/

	// Ÿ��Ʋ ��
	AddImage("image/etc/���.bmp", 960, 540);								//Ÿ��Ʋ ��
	AddImage("image/etc/�޴���.bmp", 960, 36);								//Ÿ��Ʋ �޴� ��
	AddImage("image/etc/start.bmp", 64, 14, true, RGB(0, 0, 0));		//Ÿ��Ʋ �޴� start text
	AddImage("image/etc/options.bmp", 79, 18, true, RGB(0, 0, 0));	//Ÿ��Ʋ �޴� option text
	AddImage("image/etc/exit.bmp", 47, 14, true, RGB(0, 0, 0));		//Ÿ��Ʋ �޴� exit text
	//AddImage("image/etc/����.bmp", 1363, 34, 8, 1, true, RGB(255, 255, 255));//	����â ���ϸ��̼�
	AddImage("image/etc/����2.bmp", 1384, 34, 8, 1, true, RGB(0, 0, 0));// ����â ���ϸ��̼�
	AddImage("image/etc/�ΰ�.bmp", 330, 78, true, RGB(255, 255, 255));//Ÿ��Ʋ �޴� ANGVIK �ΰ�

	// �������� 
	AddImage("image/Stage/Stage1-Background.bmp", 6709, 1290, true, RGB(255, 255, 255)); // ��������1 ��׶���
	AddImage("image/Stage/Stage1-Background2.bmp", 6709, 1290); // ��������1 ��׶���(���)
	AddImage("image/Stage/Stage1-Hidden.bmp", 6709, 1290, true, RGB(255, 255, 255)); // ��������1 ��������

	// �ȼ� ��
	AddImage("image/Stage/Stage1-test.bmp", 6709, 1290, true, RGB(255, 0, 255)); // ��������1 ��׶���(�ȼ�ver)

	// �÷��̾�
	AddImage("image/player/unarmed/arm_back.bmp", 640, 120, 16, 3, true, RGB(255, 255, 255));		// ����
	AddImage("image/player/unarmed/arm_front.bmp", 640, 120, 16, 3, true, RGB(255, 255, 255));		// ������
	AddImage("image/player/unarmed/body.bmp", 480, 100, 12, 2, true, RGB(255, 255, 255));			// ����

	AddImage("image/player/unarmed/R_arm_back.bmp", 640, 120, 16, 3, true, RGB(255, 255, 255));		// ����(Reverse)
	AddImage("image/player/unarmed/R_arm_front.bmp", 640, 120, 16, 3, true, RGB(255, 255, 255));	// ������(Reverse)
	AddImage("image/player/unarmed/R_body.bmp", 480, 100, 12, 2, true, RGB(255, 255, 255));			// ����(Reverse)
	AddImage("image/player/unarmed/R_body_walk.bmp", 480, 50, 12, 1, true, RGB(255, 255, 255));		// �ٱ�(Reverse)
	AddImage("image/player/unarmed/R_head_1.bmp", 40, 40, true, RGB(255, 255, 255));	// �Ӹ� 2(Reverse)

	AddImage("image/player/unarmed/head_0.bmp", 40, 40, true, RGB(255, 255, 255));	// �Ӹ� 1
	AddImage("image/player/unarmed/head_1.bmp", 40, 40, true, RGB(255, 255, 255));	// �Ӹ� 2
	AddImage("image/player/unarmed/head_2.bmp", 40, 40, true, RGB(255, 255, 255));	// �Ӹ� 3 
	AddImage("image/player/unarmed/head_3.bmp", 40, 40, true, RGB(255, 255, 255));	// �Ӹ� 4

	AddImage("image/player/gold/body.bmp", 480, 100, 12, 2, true, RGB(255, 255, 255));	// Ȳ�� ����
	AddImage("image/player/gold/foot.bmp", 480, 100, 12, 2, true, RGB(255, 255, 255));	// Ȳ�� �Ź�
	AddImage("image/player/gold/R_body.bmp", 480, 100, 12, 2, true, RGB(255, 255, 255));	// Ȳ�� ����(Reverse)
	AddImage("image/player/gold/R_foot.bmp", 480, 100, 12, 2, true, RGB(255, 255, 255));	// Ȳ�� �Ź�(Reverse)

	AddImage("image/item/���Į_SP.bmp", 1188, 108, 11, 1, true, RGB(255, 255, 255));			// Ȳ�� Į ��������Ʈ
	AddImage("image/item/��巣��_SP.bmp", 812, 116, 7, 1, true, RGB(255, 255, 255));		// Ȳ�� â ��������Ʈ
	AddImage("image/item/���θ޶�_SP.bmp", 1296, 54, 24, 1, true, RGB(255, 255, 255));		// Ȳ�� â ��������Ʈ

	AddImage("image/item/R_���Į_SP.bmp", 1188, 108, 11, 1, true, RGB(255, 255, 255));		// Ȳ�� Į ��������Ʈ
	AddImage("image/item/R_��巣��_SP.bmp", 812, 116, 9, 1, true, RGB(255, 255, 255));		// Ȳ�� â ��������Ʈ
	AddImage("image/item/R_���θ޶�_SP.bmp", 1296, 54, 24, 1, true, RGB(255, 255, 255));	// Ȳ�� �θ޶� ��������Ʈ

	// �κ��丮
	AddImage("image/etc/inventory.bmp", 132, 161);	// �κ��丮 ui
	AddImage("image/etc/itemBox.bmp", 131, 245);	// ������ �ڽ�
	AddImage("image/etc/oilsBox.bmp", 131, 206);	// ���� �ڽ�
	AddImage("image/etc/select.bmp", 60, 35);	// ����Ƽ�� �ڽ�
	AddImage("image/etc/SELET.bmp", 132, 186);	// ���� ������
	AddImage("image/etc/item.bmp", 46, 14, true, RGB(0, 0, 0));	// �κ��丮 text
	AddImage("image/etc/close.bmp", 58, 15, true, RGB(0, 0, 0));	// ������ text
	AddImage("image/etc/oils.bmp", 45, 15, true, RGB(0, 0, 0));	// ���� text
	AddImage("image/etc/back.bmp", 50, 15, true, RGB(0, 0, 0));	// BACK text
	AddImage("image/etc/equip.bmp", 58, 19, true, RGB(0, 0, 0));// equip text
	AddImage("image/etc/drop.bmp", 45, 18, true, RGB(0, 0, 0));	// drop text
	AddImage("image/etc/backH.bmp", 70, 18, true, RGB(0, 0, 0));// back.H text
	AddImage("image/etc/frontH.bmp", 70, 18, true, RGB(0, 0, 0));	// front.H text
	

	// ������ 
	AddImage("image/item/Ȳ��.bmp", 28, 15, true, RGB(255, 255, 255));	// Ȳ�� ����
	AddImage("image/item/Ȳ��.bmp", 24, 28, true, RGB(255, 255, 255));	// Ȳ�� ����
	AddImage("image/item/Ȳ��.bmp", 10, 11, true, RGB(255, 255, 255));	// Ȳ�� ����

	AddImage("image/item/���Į.bmp", 88, 20, true, RGB(255, 255, 255));	// Ȳ�� ����
	AddImage("image/item/��巣��.bmp", 96, 18, true, RGB(255, 255, 255));	// Ȳ�� â 
	AddImage("image/item/���θ޶�.bmp", 34, 24, true, RGB(255, 255, 255));	// Ȳ�� �θ޶�

	AddImage("image/item/������.bmp", 15, 22, true, RGB(255, 255, 255));	// Ȳ�� �θ޶�

	// ���� ����Ʈ
	AddImage("image/effect.bmp", 600, 100, 6, 1, true, RGB(255, 255, 255));		// ���� ����Ʈ
	AddImage("image/weaponEffect.bmp", 108, 21, 4, 1, true, RGB(255, 255, 255));// ���� -> �� ����Ʈ

	// ����
	// --��--
	AddImage("image/monster/kong_atk_8f.bmp", 272, 40, 8, 1, true, RGB(255, 255, 255));	// ���ݸ�� 
	AddImage("image/monster/kong_idle_6f.bmp", 192, 54, 6, 1, true, RGB(255, 255, 255));// �⺻�ڼ�
	AddImage("image/monster/R_kong_atk_8f.bmp", 272, 40, 8, 1, true, RGB(255, 255, 255));	// ���ݸ��(Reverse)
	AddImage("image/monster/R_kong_idle_6f.bmp", 192, 54, 6, 1, true, RGB(255, 255, 255));// �⺻�ڼ�(Reverse)
	// --�� �Ѿ�--
	AddImage("image/monster/kongtan.bmp", 168, 18, 6, 1, true, RGB(255, 255, 255));		// �Ѿ� ��������
	AddImage("image/monster/kongtan22.bmp", 168, 18, 6, 1, true, RGB(255, 255, 255));	// �Ѿ� ���ʹ���
	AddImage("image/monster/�����_�Ѿ�.bmp", 196, 43, 7, 1, true, RGB(255, 255, 255));	// �Ѿ� ����Ʈ
	AddImage("image/monster/R_�����_�Ѿ�.bmp", 196, 43, 7, 1, true, RGB(255, 255, 255));// �Ѿ� ����Ʈ(Reverse)

	// ��Ű
	AddImage("image/monster/������.bmp", 416, 46, 8, 1, true, RGB(255, 255, 255));	// ��Ű
	AddImage("image/monster/R_������.bmp", 416, 46, 8, 1, true, RGB(255, 255, 255));	// ��Ű(Reverse)

	// ��Ʈ
	AddImage("image/monster/Ent_move_6f.bmp", 468, 86, 6, 1, true, RGB(255, 255, 255));	// ��Ʈ
	AddImage("image/monster/R_Ent_move_6f.bmp", 468, 86, 6, 1, true, RGB(255, 255, 255));// ��Ʈ(Reverse)
	AddImage("image/monster/Ent_atk_6f.bmp", 444, 82, 6, 1, true, RGB(255, 255, 255));	// ��Ʈ ����
	AddImage("image/monster/R_Ent_atk_6f.bmp", 444, 82, 6, 1, true, RGB(255, 255, 255));// ��Ʈ ����(Reverse)
	// ��Ʈ ������
	AddImage("image/monster/leaf1.bmp", 15, 15, true, RGB(255, 255, 255));	// ������ 1
	AddImage("image/monster/leaf2.bmp", 15, 15, true, RGB(255, 255, 255));	// ������ 2
	AddImage("image/monster/leaf3.bmp", 15, 15, true, RGB(255, 255, 255));	// ������ 3
	AddImage("image/monster/leaf4.bmp", 15, 15, true, RGB(255, 255, 255));	// ������ 4
	AddImage("image/monster/R_leaf1.bmp", 15, 15, true, RGB(255, 255, 255));// ������ 1(Reverse)
	AddImage("image/monster/R_leaf2.bmp", 15, 15, true, RGB(255, 255, 255));// ������ 2(Reverse)
	AddImage("image/monster/R_leaf3.bmp", 15, 15, true, RGB(255, 255, 255));// ������ 3(Reverse)
	AddImage("image/monster/R_leaf4.bmp", 15, 15, true, RGB(255, 255, 255));// ������ 4(Reverse)

	// �÷���
	AddImage("image/Stage/treetrap.bmp", 53, 90, 1, 6, true, RGB(255, 255, 255));	// �÷���
	AddImage("image/Stage/R_treetrap.bmp", 53, 90, 1, 6, true, RGB(255, 255, 255));	// �÷���(Reverse)

}

void ImageManager::Release()
{
	for (auto& elem : mapImages)
	{
		SAFE_RELEASE(elem.second);
	}

	mapImages.clear();
}

//void ImageManager::AddImage()
//{
//	// �߰��Ϸ��� �̹����� �ڷᱸ������ ã�´�.
//
//	// ������ ����.
//
//	// ������ �߰��Ѵ�.
//	//new Image();
//	//img->Init
//
//}

Image* ImageManager::AddImage(const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	if (FindImage(fileName))
	{
		return nullptr;
	}

	Image* img = new Image;
	if (FAILED(img->Init(fileName, width, height, isTrans, transColor)))
	{
		SAFE_RELEASE(img);
		return nullptr;
	}

	mapImages.insert(make_pair(fileName, img));

	return img;
}

Image* ImageManager::AddImage(const char* fileName, int width, int height,
	int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
	if (FindImage(fileName))
	{
		return nullptr;
	}

	Image* img = new Image;
	if (FAILED(img->Init(fileName, width, height, maxFrameX,
		maxFrameY, isTrans, transColor)))
	{
		SAFE_RELEASE(img);
		return nullptr;
	}

	mapImages.insert(make_pair(fileName, img));

	return img;
}

Image* ImageManager::FindImage(const char* fileName)
{
	map<string, Image*>::iterator it = mapImages.find(fileName);
	if (it == mapImages.end())
	{
		return nullptr;
	}

	return it->second;
}

void ImageManager::DeleteImage(const char* fileName)
{
	map<string, Image*>::iterator it = mapImages.find(fileName);
	if (it == mapImages.end())
	{
		return;
	}

	SAFE_RELEASE(it->second);	// Image*	// Image �����Ҵ� ����
	mapImages.erase(it);		// �ʿ��� ��� ����
}
