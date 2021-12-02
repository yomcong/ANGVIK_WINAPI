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
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_NUMPAD6))
	{
		pixelPos.x += 5;
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_NUMPAD4))
	{
		if (pixelPos.x > 0)
			pixelPos.x -= 5;
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_NUMPAD2))
	{
		pixelPos.y += 5;
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_NUMPAD8))
	{
		if (pixelPos.y > 0)
			pixelPos.y -= 5;
	}
}

float MapColliderManager::autoMove(float x, float y, RECT shape, float moveSpeed)
{
	float tempPosY = y + moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();


	for (int i = 0; i < 10; i++)
	{
		color = GetPixel(pixelMap->GetMemDC(),
			(int)x + (int)pixelPos.x, shape.bottom + i + (int)pixelPos.y);

		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);


		if (false == (r == 255 && g == 0 && b == 255))
		{
			return y;
		}
		else
		{
			return tempPosY;
		}
	}

}

POINTFLOAT MapColliderManager::Move(POINTFLOAT pos, RECT shape, float moveSpeed, int dir, int bodySize)
{
	int height = 0;

	for (int i = 1; i < bodySize; ++i)
	{
		// laft = -1, right = +1
		if (dir > 0)
		{
			color = GetPixel(pixelMap->GetMemDC(),
				shape.right + 1 + (int)pixelPos.x, shape.bottom - i + (int)pixelPos.y);
		}
		else
		{
			color = GetPixel(pixelMap->GetMemDC(),
				shape.left - 1 + (int)pixelPos.x, shape.bottom - i + (int)pixelPos.y);
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
				return pos;
			}
		}

	}

	pos.x += (moveSpeed * TimerManager::GetSingleton()->GetDeltaTime()) * dir;
	pos.y -= height;
	return pos;
}

bool MapColliderManager::checkCollision(RECT shape)
{
	// 포문으로 검사하는방법 생각하기

	/*for (int i = 0; i < 4; i++)
	{
		//0 = laft, top , 1 = left, bottom, 2 = right, top, 3= right, bottom

		color = GetPixel(pixelMap->GetMemDC(),
			shape.left, shape.bottom);

		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);


		if (false == (r == 255 && g == 0 && b == 255))
		{
			return false;
		}
		else
		{
			return true;
		}
	}*/
	color = GetPixel(pixelMap->GetMemDC(),
		shape.left, shape.top);

	r = GetRValue(color);
	g = GetGValue(color);
	b = GetBValue(color);

	if (false == (r == 255 && g == 0 && b == 255))
	{
		return true;
	}

	color = GetPixel(pixelMap->GetMemDC(),
		shape.left, shape.bottom);
	r = GetRValue(color);
	g = GetGValue(color);
	b = GetBValue(color);

	if (false == (r == 255 && g == 0 && b == 255))
	{
		return true;
	}

	color = GetPixel(pixelMap->GetMemDC(),
		shape.right, shape.bottom);
	r = GetRValue(color);
	g = GetGValue(color);
	b = GetBValue(color);

	if (false == (r == 255 && g == 0 && b == 255))
	{
		return true;
	}

	color = GetPixel(pixelMap->GetMemDC(),
		shape.right, shape.bottom);
	r = GetRValue(color);
	g = GetGValue(color);
	b = GetBValue(color);

	if (false == (r == 255 && g == 0 && b == 255))
	{
		return true;
	}

	return false;
}
