#include "ImageManager.h"
#include "Image.h"

void ImageManager::Init()
{
	// 아이템 
	AddImage("Image/Item/Item1.bmp", 32, 32, true, RGB(255, 0, 255));
	AddImage("Image/Item/Item2.bmp", 32, 32, true, RGB(255, 0, 255));
	AddImage("Image/Item/Item3.bmp", 32, 32, true, RGB(255, 0, 255));
	AddImage("Image/Item/Item4.bmp", 32, 32, true, RGB(255, 0, 255));
	AddImage("Image/Item/Item5.bmp", 32, 32, true, RGB(255, 0, 255));
	AddImage("Image/Item/Item6.bmp", 32, 32, true, RGB(255, 0, 255));
	AddImage("Image/Item/Item7.bmp", 32, 32, true, RGB(255, 0, 255));

	// 타이틀 씬
	AddImage("image/etc/배경.bmp", 960, 540);								//타이틀 씬
	AddImage("image/etc/메뉴바.bmp", 960, 36);								//타이틀 메뉴 바
	AddImage("image/etc/start.bmp", 64, 14, true, RGB(255, 255, 255));		//타이틀 메뉴 start text
	AddImage("image/etc/options.bmp", 79, 18, true, RGB(255, 255, 255));	//타이틀 메뉴 option text
	AddImage("image/etc/exit.bmp", 47, 14, true, RGB(255, 255, 255));		//타이틀 메뉴 exit text
	//AddImage("image/etc/선택.bmp", 1363, 34, 8, 1, true, RGB(255, 255, 255));//	선택창 에니매이션
	AddImage("image/etc/선택2.bmp", 1384, 34, 8, 1, true, RGB(255, 255, 255));// 선택창 에니매이션
	AddImage("image/etc/로고.bmp", 330, 78, true, RGB(255, 255, 255));//타이틀 메뉴 ANGVIK 로고


	// 스테이지 
	AddImage("image/Stage/Stage1-Background.bmp", 6709, 1290, true, RGB(255, 255, 255)); // 스테이지1 백그라운드
	AddImage("image/Stage/Stage1-Background2.bmp", 6709, 1290); // 스테이지1 백그라운드(배경)

	// 픽셀 맵
	AddImage("image/Stage/Stage1-test.bmp", 6709, 1290, true, RGB(255, 0, 255)); // 스테이지1 백그라운드(픽셀ver)

	// 플레이어
	AddImage("image/player/unarmed/arm_back.bmp", 640, 120, 16, 3, true, RGB(255, 255, 255));	// 왼팔
	AddImage("image/player/unarmed/arm_front.bmp", 640, 120, 16, 3, true, RGB(255, 255, 255));	// 오른팔
	AddImage("image/player/unarmed/body.bmp", 480, 100, 12, 2, true, RGB(255, 255, 255));		// 몸통
	AddImage("image/player/unarmed/head_0.bmp", 40, 40, true, RGB(255, 255, 255));	// 머리 1
	AddImage("image/player/unarmed/head_1.bmp", 40, 40, true, RGB(255, 255, 255));	// 머리 2
	AddImage("image/player/unarmed/head_2.bmp", 40, 40, true, RGB(255, 255, 255));	// 머리 3 
	AddImage("image/player/unarmed/head_3.bmp", 40, 40, true, RGB(255, 255, 255));	// 머리 4

	AddImage("image/player/gold/body.bmp", 480, 100, 12, 2, true, RGB(255, 255, 255));	// 황금 갑옷
	AddImage("image/player/gold/foot.bmp", 480, 100, 12, 2, true, RGB(255, 255, 255));	// 황금 신발

	// 몬스터
	// --콩--
	AddImage("image/monster/kong_atk_8f.bmp", 272, 40, 8, 1, true, RGB(255, 255, 255));	// 공격모션 
	AddImage("image/monster/kong_idle_6f.bmp", 192, 54, 6, 1, true, RGB(255, 255, 255));// 기본자세
	// --콩 총알--
	AddImage("image/monster/kongtan.bmp", 168, 18, 6, 1, true, RGB(255, 255, 255));		// 총알 오른방향
	AddImage("image/monster/kongtan22.bmp", 168, 18, 6, 1, true, RGB(255, 255, 255));	// 총알 왼쪽방향
	// 몽키
	AddImage("image/monster/원숭이.bmp", 416, 46, 8, 1, true, RGB(255, 255, 255));	// 몽키


	//로딩 씬	
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
//	// 추가하려는 이미지를 자료구조에서 찾는다.
//
//	// 있으면 종료.
//
//	// 없으면 추가한다.
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

	SAFE_RELEASE(it->second);	// Image*	// Image 동적할당 해제
	mapImages.erase(it);		// 맵에서 노드 삭제
}
