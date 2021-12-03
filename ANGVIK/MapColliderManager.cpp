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

bool MapColliderManager::autoMove(POINTFLOAT pos, RECT shape, float moveSpeed, int bodySize)
{
	//float tempPosY = y + moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();


	for (int i = 0; i < bodySize / 2; i++)
	{
		color = GetPixel(pixelMap->GetMemDC(),
			shape.left + i + bodySize / 4, shape.bottom + 1)/*+ (int)pixelPos.y)*/;

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

POINTFLOAT MapColliderManager::Move(POINTFLOAT pos, RECT shape, float moveSpeed, int dir, int bodySize)
{
	int height = 0;

	for (int i = 1; i < bodySize; ++i)
	{
		// laft = -1, right = +1
		if (dir > 0)
		{
			color = GetPixel(pixelMap->GetMemDC(),
				shape.right + 1 /*+ (int)pixelPos.x*/, shape.bottom - i /*+ (int)pixelPos.y)*/);
		}
		else
		{
			color = GetPixel(pixelMap->GetMemDC(),
				shape.left - 1 /*+ (int)pixelPos.x*/, shape.bottom - i /*+ (int)pixelPos.y)*/);
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

bool MapColliderManager::checkCollision(RECT shape, int dir, int bodySize)
{
	// 포문으로 검사하는방법 생각하기
	// 렉트 사각형 범위
	// 또는 움직이는 방향 레프트 또는 라이트 ,바텀 에서부터 탑
	if (dir > 0)
	{
		for (int i = 0; i < bodySize; i++)
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
		for (int i = 0; i < bodySize; i++)
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
	for (int i = 0; i < bodySize; i++)
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
	/*color = GetPixel(pixelMap->GetMemDC(),
		shape.left - CameraManager::GetSingleton()->GetPos().x, shape.top - CameraManager::GetSingleton()->GetPos().y);

	r = GetRValue(color);
	g = GetGValue(color);
	b = GetBValue(color);

	if (false == (r == 255 && g == 0 && b == 255))
	{
		return true;
	}

	color = GetPixel(pixelMap->GetMemDC(),
		shape.left - CameraManager::GetSingleton()->GetPos().x, shape.bottom - CameraManager::GetSingleton()->GetPos().y);
	r = GetRValue(color);
	g = GetGValue(color);
	b = GetBValue(color);

	if (false == (r == 255 && g == 0 && b == 255))
	{
		return true;
	}

	color = GetPixel(pixelMap->GetMemDC(),
		shape.right - CameraManager::GetSingleton()->GetPos().x, shape.bottom - CameraManager::GetSingleton()->GetPos().y);
	r = GetRValue(color);
	g = GetGValue(color);
	b = GetBValue(color);

	if (false == (r == 255 && g == 0 && b == 255))
	{
		return true;
	}

	color = GetPixel(pixelMap->GetMemDC(),
		shape.right - CameraManager::GetSingleton()->GetPos().x, shape.bottom - CameraManager::GetSingleton()->GetPos().y);
	r = GetRValue(color);
	g = GetGValue(color);
	b = GetBValue(color);

	if (false == (r == 255 && g == 0 && b == 255))
	{
		return true;
	}

	return false;*/
}
