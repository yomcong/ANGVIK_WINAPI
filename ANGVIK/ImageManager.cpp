#include "ImageManager.h"
#include "Image.h"

void ImageManager::Init()
{
	// æ∆¿Ã≈€ 
	/*AddImage("Image/Item/Item1.bmp", 32, 32, true, RGB(255, 0, 255));
	AddImage("Image/Item/Item2.bmp", 32, 32, true, RGB(255, 0, 255));
	AddImage("Image/Item/Item3.bmp", 32, 32, true, RGB(255, 0, 255));
	AddImage("Image/Item/Item4.bmp", 32, 32, true, RGB(255, 0, 255));
	AddImage("Image/Item/Item5.bmp", 32, 32, true, RGB(255, 0, 255));
	AddImage("Image/Item/Item6.bmp", 32, 32, true, RGB(255, 0, 255));
	AddImage("Image/Item/Item7.bmp", 32, 32, true, RGB(255, 0, 255));*/

	// ≈∏¿Ã∆≤ æ¿
	AddImage("image/etc/πË∞Ê.bmp", 960, 540);								//≈∏¿Ã∆≤ æ¿
	AddImage("image/etc/∏ﬁ¥∫πŸ.bmp", 960, 36);								//≈∏¿Ã∆≤ ∏ﬁ¥∫ πŸ
	AddImage("image/etc/start.bmp", 64, 14, true, RGB(0, 0, 0));		//≈∏¿Ã∆≤ ∏ﬁ¥∫ start text
	AddImage("image/etc/options.bmp", 79, 18, true, RGB(0, 0, 0));	//≈∏¿Ã∆≤ ∏ﬁ¥∫ option text
	AddImage("image/etc/exit.bmp", 47, 14, true, RGB(255, 255, 255));		//≈∏¿Ã∆≤ ∏ﬁ¥∫ exit text
	//AddImage("image/etc/º±≈√.bmp", 1363, 34, 8, 1, true, RGB(255, 255, 255));//	º±≈√√¢ ø°¥œ∏≈¿Ãº«
	AddImage("image/etc/º±≈√2.bmp", 1384, 34, 8, 1, true, RGB(0, 0, 0));// º±≈√√¢ ø°¥œ∏≈¿Ãº«
	AddImage("image/etc/∑Œ∞Ì.bmp", 330, 78, true, RGB(255, 255, 255));//≈∏¿Ã∆≤ ∏ﬁ¥∫ ANGVIK ∑Œ∞Ì

	// Ω∫≈◊¿Ã¡ˆ 
	AddImage("image/Stage/Stage1-Background.bmp", 6709, 1290, true, RGB(255, 255, 255)); // Ω∫≈◊¿Ã¡ˆ1 πÈ±◊∂ÛøÓµÂ
	AddImage("image/Stage/Stage1-Background2.bmp", 6709, 1290); // Ω∫≈◊¿Ã¡ˆ1 πÈ±◊∂ÛøÓµÂ(πË∞Ê)

	// «»ºø ∏ 
	AddImage("image/Stage/Stage1-test.bmp", 6709, 1290, true, RGB(255, 0, 255)); // Ω∫≈◊¿Ã¡ˆ1 πÈ±◊∂ÛøÓµÂ(«»ºøver)

	// «√∑π¿ÃæÓ
	AddImage("image/player/unarmed/arm_back.bmp", 640, 120, 16, 3, true, RGB(255, 255, 255));		// øﬁ∆»
	AddImage("image/player/unarmed/arm_front.bmp", 640, 120, 16, 3, true, RGB(255, 255, 255));		// ø¿∏•∆»
	AddImage("image/player/unarmed/body.bmp", 480, 100, 12, 2, true, RGB(255, 255, 255));			// ∏ˆ≈Î

	AddImage("image/player/unarmed/R_arm_back.bmp", 640, 120, 16, 3, true, RGB(255, 255, 255));		// øﬁ∆»(Reverse)
	AddImage("image/player/unarmed/R_arm_front.bmp", 640, 120, 16, 3, true, RGB(255, 255, 255));	// ø¿∏•∆»(Reverse)
	AddImage("image/player/unarmed/R_body.bmp", 480, 100, 12, 2, true, RGB(255, 255, 255));			// ∏ˆ≈Î(Reverse)
	AddImage("image/player/unarmed/R_body_walk.bmp", 480, 50, 12, 1, true, RGB(255, 255, 255));		// ∂Ÿ±‚(Reverse)
	AddImage("image/player/unarmed/R_head_1.bmp", 40, 40, true, RGB(255, 255, 255));	// ∏”∏Æ 2(Reverse)

	AddImage("image/player/unarmed/head_0.bmp", 40, 40, true, RGB(255, 255, 255));	// ∏”∏Æ 1
	AddImage("image/player/unarmed/head_1.bmp", 40, 40, true, RGB(255, 255, 255));	// ∏”∏Æ 2
	AddImage("image/player/unarmed/head_2.bmp", 40, 40, true, RGB(255, 255, 255));	// ∏”∏Æ 3 
	AddImage("image/player/unarmed/head_3.bmp", 40, 40, true, RGB(255, 255, 255));	// ∏”∏Æ 4

	AddImage("image/player/gold/body.bmp", 480, 100, 12, 2, true, RGB(255, 255, 255));	// »≤±› ∞©ø 
	AddImage("image/player/gold/foot.bmp", 480, 100, 12, 2, true, RGB(255, 255, 255));	// »≤±› Ω≈πﬂ

	// ¿Œ∫•≈‰∏Æ

	// æ∆¿Ã≈€
	AddImage("image/item/∞ÒµÂƒÆ.bmp", 88, 20, true, RGB(255, 255, 255));	// »≤±› ∞©ø 
	AddImage("image/item/∞ÒµÂ∑£Ω∫.bmp", 96, 18, true, RGB(255, 255, 255));	// »≤±› ∞©ø 
	AddImage("image/item/»≤≈ı.bmp", 28, 15, true, RGB(255, 255, 255));	// »≤±› ∞©ø 
	AddImage("image/item/»≤∞©.bmp", 24, 28, true, RGB(255, 255, 255));	// »≤±› ∞©ø 
	AddImage("image/item/»≤Ω≈.bmp", 10, 11, true, RGB(255, 255, 255));	// »≤±› ∞©ø 
	
	// ∏ÛΩ∫≈Õ
	// µ•Ω∫ ¿Ã∆Â∆Æ
	AddImage("image/effect.bmp", 600, 100, 6, 1, true, RGB(255, 255, 255));	// µ•Ω∫ ¿Ã∆Â∆Æ
	
	// --ƒ·--
	AddImage("image/monster/kong_atk_8f.bmp", 272, 40, 8, 1, true, RGB(255, 255, 255));	// ∞¯∞›∏º« 
	AddImage("image/monster/kong_idle_6f.bmp", 192, 54, 6, 1, true, RGB(255, 255, 255));// ±‚∫ª¿⁄ºº
	AddImage("image/monster/R_kong_atk_8f.bmp", 272, 40, 8, 1, true, RGB(255, 255, 255));	// ∞¯∞›∏º«(Reverse)
	AddImage("image/monster/R_kong_idle_6f.bmp", 192, 54, 6, 1, true, RGB(255, 255, 255));// ±‚∫ª¿⁄ºº(Reverse)
	// --ƒ· √—æÀ--
	AddImage("image/monster/kongtan.bmp", 168, 18, 6, 1, true, RGB(255, 255, 255));		// √—æÀ ø¿∏•πÊ«‚
	AddImage("image/monster/kongtan22.bmp", 168, 18, 6, 1, true, RGB(255, 255, 255));	// √—æÀ øﬁ¬ πÊ«‚
	AddImage("image/monster/∏¥Ÿ««_√—æÀ.bmp", 196, 43, 7, 1, true, RGB(255, 255, 255));	// √—æÀ ¿Ã∆Â∆Æ
	AddImage("image/monster/R_∏¥Ÿ««_√—æÀ.bmp", 196, 43, 7, 1, true, RGB(255, 255, 255));// √—æÀ ¿Ã∆Â∆Æ(Reverse)

	// ∏˘≈∞
	AddImage("image/monster/ø¯º˛¿Ã.bmp", 416, 46, 8, 1, true, RGB(255, 255, 255));	// ∏˘≈∞
	AddImage("image/monster/R_ø¯º˛¿Ã.bmp", 416, 46, 8, 1, true, RGB(255, 255, 255));	// ∏˘≈∞(Reverse)

	// ø£∆Æ
	AddImage("image/monster/Ent_move_6f.bmp", 468, 86, 6, 1, true, RGB(255, 255, 255));	// ø£∆Æ
	AddImage("image/monster/R_Ent_move_6f.bmp", 468, 86, 6, 1, true, RGB(255, 255, 255));// ø£∆Æ(Reverse)
	AddImage("image/monster/Ent_atk_6f.bmp", 444, 82, 6, 1, true, RGB(255, 255, 255));	// ø£∆Æ ∞¯∞›
	AddImage("image/monster/R_Ent_atk_6f.bmp", 444, 82, 6, 1, true, RGB(255, 255, 255));// ø£∆Æ ∞¯∞›(Reverse)
	// ø£∆Æ ≥™πµ¿Ÿ
	AddImage("image/monster/leaf1.bmp", 15, 15, true, RGB(255, 255, 255));	// ≥™πµ¿Ÿ 1
	AddImage("image/monster/leaf2.bmp", 15, 15, true, RGB(255, 255, 255));	// ≥™πµ¿Ÿ 2
	AddImage("image/monster/leaf3.bmp", 15, 15, true, RGB(255, 255, 255));	// ≥™πµ¿Ÿ 3
	AddImage("image/monster/leaf4.bmp", 15, 15, true, RGB(255, 255, 255));	// ≥™πµ¿Ÿ 4
	AddImage("image/monster/R_leaf1.bmp", 15, 15, true, RGB(255, 255, 255));// ≥™πµ¿Ÿ 1(Reverse)
	AddImage("image/monster/R_leaf2.bmp", 15, 15, true, RGB(255, 255, 255));// ≥™πµ¿Ÿ 2(Reverse)
	AddImage("image/monster/R_leaf3.bmp", 15, 15, true, RGB(255, 255, 255));// ≥™πµ¿Ÿ 3(Reverse)
	AddImage("image/monster/R_leaf4.bmp", 15, 15, true, RGB(255, 255, 255));// ≥™πµ¿Ÿ 4(Reverse)

	// «√∑ß∆˚
	AddImage("image/Stage/treetrap.bmp", 53, 90, 1, 6, true, RGB(0, 0, 0));	// «√∑ß∆˚
	AddImage("image/Stage/R_treetrap.bmp", 53, 90, 1, 6, true, RGB(255, 255, 255));	// «√∑ß∆˚(Reverse)

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
//	// √ﬂ∞°«œ∑¡¥¬ ¿ÃπÃ¡ˆ∏¶ ¿⁄∑·±∏¡∂ø°º≠ √£¥¬¥Ÿ.
//
//	// ¿÷¿∏∏È ¡æ∑·.
//
//	// æ¯¿∏∏È √ﬂ∞°«—¥Ÿ.
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

	SAFE_RELEASE(it->second);	// Image*	// Image µø¿˚«“¥Á «ÿ¡¶
	mapImages.erase(it);		// ∏ ø°º≠ ≥ÎµÂ ªË¡¶
}
