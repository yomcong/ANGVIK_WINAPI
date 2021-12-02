//#include "PixelCollider.h"
//#include "Image.h"
//
//
//HRESULT PixelCollider::Init()
//{
//	pixelMap = ImageManager::GetSingleton()->FindImage("image/Stage/Stage1-test.bmp");
//	if (pixelMap == nullptr)
//	{
//		return E_FAIL;
//	}
//
//
//	return S_OK;
//
//
//}
//
//void PixelCollider::Update()
//{
//	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_NUMPAD6))
//	{
//		pixelPos.x += 5;
//	}
//	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_NUMPAD4))
//	{
//		if(pixelPos.x >0)
//			pixelPos.x -= 5;
//	}
//	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_NUMPAD2))
//	{
//		pixelPos.y += 5;
//	}
//	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_NUMPAD8))
//	{
//		if (pixelPos.y > 0)
//			pixelPos.y -= 5;
//	}	
//}
//
//void PixelCollider::Render(HDC hdc)
//{
//
//}
//
//void PixelCollider::Release()
//{
//
//}
//
//// 낙하
//float PixelCollider::autoMove(float x, float y, RECT shape, float moveSpeed)
//{
//	float tempPosY = y + moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
//
//	
//	for (int i = 0; i < 10; i++)
//	{
//		color = GetPixel(pixelMap->GetMemDC(),
//			x+ pixelPos.x, shape.bottom + i + pixelPos.y);
//
//		r = GetRValue(color);
//		g = GetGValue(color);
//		b = GetBValue(color);
//
//
//		if (false == (r == 255 && g == 0 && b == 255))
//		{
//			return y;
//		}
//		else
//		{
//			return tempPosY;
//			break;
//		}
//	}
//}
//
////이동
//POINTFLOAT PixelCollider::Move(POINTFLOAT pos, RECT shape, float moveSpeed, int dir, int bodySize)
//{
//	int height = 0;
//
//	for (int i = 1; i < bodySize; ++i)
//	{
//		// laft = -1, right = +1
//		if (dir > 0)
//		{
//			color = GetPixel(pixelMap->GetMemDC(),
//				shape.right + 1 + pixelPos.x, shape.bottom - i + pixelPos.y);
//		}
//		else
//		{
//			color = GetPixel(pixelMap->GetMemDC(),
//				shape.left - 1 + pixelPos.x, shape.bottom - i + pixelPos.y);
//		}
//
//		r = GetRValue(color);
//		g = GetGValue(color);
//		b = GetBValue(color);
//
//		// 낮은 높이는 이동 가능
//		if (i < 7)
//		{
//			if (false == (r == 255 && g == 0 && b == 255))
//			{
//				height = max(height, i);
//			}
//		}
//		else
//		{
//			if (false == (r == 255 && g == 0 && b == 255))
//			{
//				return pos;
//			}
//		}
//
//	}
//
//	pos.x += (moveSpeed * TimerManager::GetSingleton()->GetDeltaTime()) * dir;
//	pos.y -= height;
//	return pos;
//}
