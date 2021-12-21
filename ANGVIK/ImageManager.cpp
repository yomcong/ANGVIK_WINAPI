#include "ImageManager.h"
#include "Image.h"

void ImageManager::Init()
{
	// 아이템 
	/*AddImage("Image/Item/Item1.bmp", 32, 32, true, RGB(255, 0, 255));
	AddImage("Image/Item/Item2.bmp", 32, 32, true, RGB(255, 0, 255));
	AddImage("Image/Item/Item3.bmp", 32, 32, true, RGB(255, 0, 255));
	AddImage("Image/Item/Item4.bmp", 32, 32, true, RGB(255, 0, 255));
	AddImage("Image/Item/Item5.bmp", 32, 32, true, RGB(255, 0, 255));
	AddImage("Image/Item/Item6.bmp", 32, 32, true, RGB(255, 0, 255));
	AddImage("Image/Item/Item7.bmp", 32, 32, true, RGB(255, 0, 255));*/

	// 타이틀 씬
	AddImage("image/etc/배경.bmp", 960, 540);								//타이틀 씬
	AddImage("image/etc/메뉴바.bmp", 960, 36);								//타이틀 메뉴 바
	AddImage("image/etc/start.bmp", 64, 14, true, RGB(0, 0, 0));		//타이틀 메뉴 start text
	AddImage("image/etc/options.bmp", 79, 18, true, RGB(0, 0, 0));	//타이틀 메뉴 option text
	AddImage("image/etc/exit.bmp", 47, 14, true, RGB(0, 0, 0));		//타이틀 메뉴 exit text
	//AddImage("image/etc/선택.bmp", 1363, 34, 8, 1, true, RGB(255, 255, 255));//	선택창 에니매이션
	AddImage("image/etc/선택2.bmp", 1384, 34, 8, 1, true, RGB(0, 0, 0));// 선택창 에니매이션
	AddImage("image/etc/로고.bmp", 330, 78, true, RGB(255, 255, 255));//타이틀 메뉴 ANGVIK 로고

	// 스테이지 
	AddImage("image/Stage/Stage1-Background.bmp", 6709, 1290, true, RGB(255, 255, 255)); // 스테이지1 백그라운드
	AddImage("image/Stage/Stage1-Background2.bmp", 6709, 1290); // 스테이지1 백그라운드(배경)
	AddImage("image/Stage/Stage1-Hidden.bmp", 6709, 1290, true, RGB(255, 255, 255)); // 스테이지1 히든지역

	// 픽셀 맵
	AddImage("image/Stage/Stage1-test.bmp", 6709, 1290, true, RGB(255, 0, 255)); // 스테이지1 백그라운드(픽셀ver)

	// 플레이어
	AddImage("image/player/unarmed/arm_back.bmp", 640, 120, 16, 3, true, RGB(255, 255, 255));		// 왼팔
	AddImage("image/player/unarmed/arm_front.bmp", 640, 120, 16, 3, true, RGB(255, 255, 255));		// 오른팔
	AddImage("image/player/unarmed/body.bmp", 480, 100, 12, 2, true, RGB(255, 255, 255));			// 몸통

	AddImage("image/player/unarmed/R_arm_back.bmp", 640, 120, 16, 3, true, RGB(255, 255, 255));		// 왼팔(Reverse)
	AddImage("image/player/unarmed/R_arm_front.bmp", 640, 120, 16, 3, true, RGB(255, 255, 255));	// 오른팔(Reverse)
	AddImage("image/player/unarmed/R_body.bmp", 480, 100, 12, 2, true, RGB(255, 255, 255));			// 몸통(Reverse)
	AddImage("image/player/unarmed/R_body_walk.bmp", 480, 50, 12, 1, true, RGB(255, 255, 255));		// 뛰기(Reverse)
	AddImage("image/player/unarmed/R_head_1.bmp", 40, 40, true, RGB(255, 255, 255));	// 머리 2(Reverse)

	AddImage("image/player/unarmed/head_0.bmp", 40, 40, true, RGB(255, 255, 255));	// 머리 1
	AddImage("image/player/unarmed/head_1.bmp", 40, 40, true, RGB(255, 255, 255));	// 머리 2
	AddImage("image/player/unarmed/head_2.bmp", 40, 40, true, RGB(255, 255, 255));	// 머리 3 
	AddImage("image/player/unarmed/head_3.bmp", 40, 40, true, RGB(255, 255, 255));	// 머리 4

	AddImage("image/player/gold/body.bmp", 480, 100, 12, 2, true, RGB(255, 255, 255));	// 황금 갑옷
	AddImage("image/player/gold/foot.bmp", 480, 100, 12, 2, true, RGB(255, 255, 255));	// 황금 신발
	AddImage("image/player/gold/R_body.bmp", 480, 100, 12, 2, true, RGB(255, 255, 255));	// 황금 갑옷(Reverse)
	AddImage("image/player/gold/R_foot.bmp", 480, 100, 12, 2, true, RGB(255, 255, 255));	// 황금 신발(Reverse)

	AddImage("image/item/골드칼_SP.bmp", 1188, 108, 11, 1, true, RGB(255, 255, 255));			// 황금 칼 스프라이트
	AddImage("image/item/골드랜스_SP.bmp", 812, 116, 7, 1, true, RGB(255, 255, 255));		// 황금 창 스프라이트
	AddImage("image/item/골드부메랑_SP.bmp", 1296, 54, 24, 1, true, RGB(255, 255, 255));		// 황금 창 스프라이트

	AddImage("image/item/R_골드칼_SP.bmp", 1188, 108, 11, 1, true, RGB(255, 255, 255));		// 황금 칼 스프라이트
	AddImage("image/item/R_골드랜스_SP.bmp", 812, 116, 9, 1, true, RGB(255, 255, 255));		// 황금 창 스프라이트
	AddImage("image/item/R_골드부메랑_SP.bmp", 1296, 54, 24, 1, true, RGB(255, 255, 255));	// 황금 부메랑 스프라이트

	// 인벤토리
	AddImage("image/etc/inventory.bmp", 132, 161);	// 인벤토리 ui
	AddImage("image/etc/itemBox.bmp", 131, 245);	// 아이템 박스
	AddImage("image/etc/oilsBox.bmp", 131, 206);	// 오일 박스
	AddImage("image/etc/select.bmp", 60, 35);	// 셀렉티드 박스
	AddImage("image/etc/SELET.bmp", 132, 186);	// 셀렉 아이템
	AddImage("image/etc/item.bmp", 46, 14, true, RGB(0, 0, 0));	// 인벤토리 text
	AddImage("image/etc/close.bmp", 58, 15, true, RGB(0, 0, 0));	// 아이템 text
	AddImage("image/etc/oils.bmp", 45, 15, true, RGB(0, 0, 0));	// 오일 text
	AddImage("image/etc/back.bmp", 50, 15, true, RGB(0, 0, 0));	// BACK text
	AddImage("image/etc/equip.bmp", 58, 19, true, RGB(0, 0, 0));// equip text
	AddImage("image/etc/drop.bmp", 45, 18, true, RGB(0, 0, 0));	// drop text
	AddImage("image/etc/backH.bmp", 70, 18, true, RGB(0, 0, 0));// back.H text
	AddImage("image/etc/frontH.bmp", 70, 18, true, RGB(0, 0, 0));	// front.H text
	

	// 아이템 
	AddImage("image/item/황투.bmp", 28, 15, true, RGB(255, 255, 255));	// 황금 갑옷
	AddImage("image/item/황갑.bmp", 24, 28, true, RGB(255, 255, 255));	// 황금 갑옷
	AddImage("image/item/황신.bmp", 10, 11, true, RGB(255, 255, 255));	// 황금 갑옷

	AddImage("image/item/골드칼.bmp", 88, 20, true, RGB(255, 255, 255));	// 황금 갑옷
	AddImage("image/item/골드랜스.bmp", 96, 18, true, RGB(255, 255, 255));	// 황금 창 
	AddImage("image/item/골드부메랑.bmp", 34, 24, true, RGB(255, 255, 255));	// 황금 부메랑

	AddImage("image/item/골드오일.bmp", 15, 22, true, RGB(255, 255, 255));	// 황금 부메랑

	// 데스 이펙트
	AddImage("image/effect.bmp", 600, 100, 6, 1, true, RGB(255, 255, 255));		// 데스 이펙트
	AddImage("image/weaponEffect.bmp", 108, 21, 4, 1, true, RGB(255, 255, 255));// 무기 -> 맵 이펙트

	// 몬스터
	// --콩--
	AddImage("image/monster/kong_atk_8f.bmp", 272, 40, 8, 1, true, RGB(255, 255, 255));	// 공격모션 
	AddImage("image/monster/kong_idle_6f.bmp", 192, 54, 6, 1, true, RGB(255, 255, 255));// 기본자세
	AddImage("image/monster/R_kong_atk_8f.bmp", 272, 40, 8, 1, true, RGB(255, 255, 255));	// 공격모션(Reverse)
	AddImage("image/monster/R_kong_idle_6f.bmp", 192, 54, 6, 1, true, RGB(255, 255, 255));// 기본자세(Reverse)
	// --콩 총알--
	AddImage("image/monster/kongtan.bmp", 168, 18, 6, 1, true, RGB(255, 255, 255));		// 총알 오른방향
	AddImage("image/monster/kongtan22.bmp", 168, 18, 6, 1, true, RGB(255, 255, 255));	// 총알 왼쪽방향
	AddImage("image/monster/모다피_총알.bmp", 196, 43, 7, 1, true, RGB(255, 255, 255));	// 총알 이펙트
	AddImage("image/monster/R_모다피_총알.bmp", 196, 43, 7, 1, true, RGB(255, 255, 255));// 총알 이펙트(Reverse)

	// 몽키
	AddImage("image/monster/원숭이.bmp", 416, 46, 8, 1, true, RGB(255, 255, 255));	// 몽키
	AddImage("image/monster/R_원숭이.bmp", 416, 46, 8, 1, true, RGB(255, 255, 255));	// 몽키(Reverse)

	// 엔트
	AddImage("image/monster/Ent_move_6f.bmp", 468, 86, 6, 1, true, RGB(255, 255, 255));	// 엔트
	AddImage("image/monster/R_Ent_move_6f.bmp", 468, 86, 6, 1, true, RGB(255, 255, 255));// 엔트(Reverse)
	AddImage("image/monster/Ent_atk_6f.bmp", 444, 82, 6, 1, true, RGB(255, 255, 255));	// 엔트 공격
	AddImage("image/monster/R_Ent_atk_6f.bmp", 444, 82, 6, 1, true, RGB(255, 255, 255));// 엔트 공격(Reverse)
	// 엔트 나뭇잎
	AddImage("image/monster/leaf1.bmp", 15, 15, true, RGB(255, 255, 255));	// 나뭇잎 1
	AddImage("image/monster/leaf2.bmp", 15, 15, true, RGB(255, 255, 255));	// 나뭇잎 2
	AddImage("image/monster/leaf3.bmp", 15, 15, true, RGB(255, 255, 255));	// 나뭇잎 3
	AddImage("image/monster/leaf4.bmp", 15, 15, true, RGB(255, 255, 255));	// 나뭇잎 4
	AddImage("image/monster/R_leaf1.bmp", 15, 15, true, RGB(255, 255, 255));// 나뭇잎 1(Reverse)
	AddImage("image/monster/R_leaf2.bmp", 15, 15, true, RGB(255, 255, 255));// 나뭇잎 2(Reverse)
	AddImage("image/monster/R_leaf3.bmp", 15, 15, true, RGB(255, 255, 255));// 나뭇잎 3(Reverse)
	AddImage("image/monster/R_leaf4.bmp", 15, 15, true, RGB(255, 255, 255));// 나뭇잎 4(Reverse)

	// 플랫폼
	AddImage("image/Stage/treetrap.bmp", 53, 90, 1, 6, true, RGB(255, 255, 255));	// 플랫폼
	AddImage("image/Stage/R_treetrap.bmp", 53, 90, 1, 6, true, RGB(255, 255, 255));	// 플랫폼(Reverse)

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
