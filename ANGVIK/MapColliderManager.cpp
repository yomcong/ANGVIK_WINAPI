#include "MapColliderManager.h"
#include "Image.h"

HRESULT MapColliderManager::Init()
{												
	pixelMap = ImageManager::GetSingleton()->FindImage("image/Stage/Stage1-test.bmp");
	if (pixelMap == nullptr)
	{
		return E_FAIL;
	}

	

	return S_OK;
}

void MapColliderManager::Update()
{

}

bool MapColliderManager::IsFalling(POINTFLOAT pos, RECT shape, float moveSpeed, POINT bodySize)
{
	//float tempPosY = y + moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();


	for (int i = (int)(bodySize.x * 0.2); i <= (int)(bodySize.x * 0.7); i++)
	{
		color = GetPixel(pixelMap->GetMemDC(),
			shape.left + i, shape.bottom + 1);

		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);


		if (false == (r == 255 && g == 0 && b == 255))
		{
			return false;
		}
		//cout << (y + (moveSpeed * TimerManager::GetSingleton()->GetDeltaTime())) << "\n";
		//cout << pos.y << "\n";
	}
	return true;

}

POINTFLOAT MapColliderManager::Move(POINTFLOAT pos, RECT shape, float moveSpeed, int dir, POINT bodySize)
{
	float height = 0.0f;

	for (int i = 0; i <= bodySize.y; ++i)
	{
		// laft = -1,0  right = +1
		if (dir > 0)
		{
			color = GetPixel(pixelMap->GetMemDC(),
				shape.right + 1, shape.bottom - i);
		}
		else
		{
			color = GetPixel(pixelMap->GetMemDC(),
				shape.left - 1, shape.bottom - i);
		}

		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);

		// 낮은 높이는 이동 가능
		if (i < 10)
		{
			if (false == (r == 255 && g == 0 && b == 255))
			{
				height = max(height, i);
			}
		}
		else
		{
			if (false == (r == 255 && g == 0 && b == 255))
			{
				pos.x = 0;
				pos.y = 0;
				return pos;
			}
		}

	}

	pos.x = (moveSpeed * TimerManager::GetSingleton()->GetDeltaTime()) * dir;
	pos.y = -height;
	return pos;
}

bool MapColliderManager::Jump(POINTFLOAT pos, RECT shape, float moveSpeed,  POINT bodySize)
{
	for (int i = 0; i <= (int)(bodySize.x*2); i++)
	{
		color = GetPixel(pixelMap->GetMemDC(),
			shape.left + i, shape.top - 1);

		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);


		if (false == (r == 255 && g == 0 && b == 255))
		{
			return false;
		}
	}

	return true;
}

bool MapColliderManager::checkCollision(RECT shape, int dir, POINT bodySize)
{
	if (dir > 0)
	{
		for (int i = 0; i < bodySize.y; i++)
		{
			color = GetPixel(pixelMap->GetMemDC(),
				shape.right, shape.bottom - i);

			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);


			if (false == (r == 255 && g == 0 && b == 255))
			{
				return true;
			}
		}
	}
	else
	{
		for (int i = 0; i < bodySize.y; i++)
		{
			color = GetPixel(pixelMap->GetMemDC(),
				shape.left, shape.bottom - i);

			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);


			if (false == (r == 255 && g == 0 && b == 255))
			{
				return true;
			}
		}

	}
	for (int i = 0; i < bodySize.x; i++)
	{
		color = GetPixel(pixelMap->GetMemDC(),
			shape.left + i, shape.bottom);

		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);


		if (false == (r == 255 && g == 0 && b == 255))
		{
			return true;
		}
	}

	return false;
}

//bool MapColliderManager::AutoMove(POINTFLOAT pos, RECT shape, float moveSpeed,int dir, POINT bodySize)
//{
//	for (int i = 0; i < (bodySize.x / 2); i++)
//	{
//		color = GetPixel(pixelMap->GetMemDC(),
//			shape.left + i + bodySize.x / 4, shape.bottom + 1)/*+ (int)pixelPos.y)*/;
//
//		r = GetRValue(color);
//		g = GetGValue(color);
//		b = GetBValue(color);
//
//
//		if (false == (r == 255 && g == 0 && b == 255))
//		{
//			return false;
//		}
//		//cout << (y + (moveSpeed * TimerManager::GetSingleton()->GetDeltaTime())) << "\n";
//		//cout << pos.y << "\n";
//	}
//
//	return true;
//
//}
