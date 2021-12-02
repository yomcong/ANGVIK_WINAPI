#include "ImageManager.h"
#include "Image.h"

void ImageManager::Init()
{
	// ������ 
	AddImage("Image/Item/Item1.bmp", 32, 32, true, RGB(255, 0, 255));
	AddImage("Image/Item/Item2.bmp", 32, 32, true, RGB(255, 0, 255));
	AddImage("Image/Item/Item3.bmp", 32, 32, true, RGB(255, 0, 255));
	AddImage("Image/Item/Item4.bmp", 32, 32, true, RGB(255, 0, 255));
	AddImage("Image/Item/Item5.bmp", 32, 32, true, RGB(255, 0, 255));
	AddImage("Image/Item/Item6.bmp", 32, 32, true, RGB(255, 0, 255));
	AddImage("Image/Item/Item7.bmp", 32, 32, true, RGB(255, 0, 255));

	// Ÿ��Ʋ ��
	AddImage("image/etc/���.bmp", 960, 540);								//Ÿ��Ʋ ��
	AddImage("image/etc/�޴���.bmp", 960, 36);								//Ÿ��Ʋ �޴� ��
	AddImage("image/etc/start.bmp", 64, 14, true, RGB(255, 255, 255));		//Ÿ��Ʋ �޴� start text
	AddImage("image/etc/options.bmp", 79, 18, true, RGB(255, 255, 255));	//Ÿ��Ʋ �޴� option text
	AddImage("image/etc/exit.bmp", 47, 14, true, RGB(255, 255, 255));		//Ÿ��Ʋ �޴� exit text
	//AddImage("image/etc/����.bmp", 1363, 34, 8, 1, true, RGB(255, 255, 255));//	����â ���ϸ��̼�
	AddImage("image/etc/����2.bmp", 1384, 34, 8, 1, true, RGB(255, 255, 255));// ����â ���ϸ��̼�
	AddImage("image/etc/�ΰ�.bmp", 330, 78, true, RGB(255, 255, 255));//Ÿ��Ʋ �޴� ANGVIK �ΰ�


	// �������� 
	AddImage("image/Stage/Stage1-Background.bmp", 6709, 1290, true , RGB(255, 255, 255)); // ��������1 ��׶���
	AddImage("image/Stage/Stage1-Background2.bmp", 6709, 1290); // ��������1 ��׶���(���)

	// �ȼ� ��
	AddImage("image/Stage/Stage1-test.bmp", 6709, 1290, true , RGB(255, 0, 255)); // ��������1 ��׶���(�ȼ�ver)

	// �÷��̾�
	AddImage("image/player/unarmed/arm_back.bmp", 640, 120,16, 3, true, RGB(255, 255, 255));	// ����
	AddImage("image/player/unarmed/arm_front.bmp", 640, 120,16, 3, true, RGB(255, 255, 255));	// ������
	AddImage("image/player/unarmed/body.bmp", 480, 100, 12, 2, true, RGB(255, 255, 255));		// ����
	AddImage("image/player/unarmed/head_0.bmp", 40, 40, true, RGB(255, 255, 255));	// �Ӹ� 1
	AddImage("image/player/unarmed/head_1.bmp", 40, 40, true, RGB(255, 255, 255));	// �Ӹ� 2
	AddImage("image/player/unarmed/head_2.bmp", 40, 40, true, RGB(255, 255, 255));	// �Ӹ� 3 
	AddImage("image/player/unarmed/head_3.bmp", 40, 40, true, RGB(255, 255, 255));	// �Ӹ� 4

	AddImage("image/player/gold/body.bmp", 480, 100, 12, 2, true, RGB(255, 255, 255));	// Ȳ�� ����
	AddImage("image/player/gold/foot.bmp", 480, 100, 12, 2, true, RGB(255, 255, 255));	// Ȳ�� �Ź�


	
	//�ε� ��	
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
