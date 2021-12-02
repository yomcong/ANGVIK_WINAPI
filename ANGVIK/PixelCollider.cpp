#include "PixelCollider.h"
#include "Image.h"


HRESULT PixelCollider::Init()
{
	pixelMap = ImageManager::GetSingleton()->FindImage("image/Stage/Stage1-test.bmp");
	if (pixelMap == nullptr)
	{
		return E_FAIL;
	}


	return S_OK;
}

void PixelCollider::Update()
{

}

void PixelCollider::Render(HDC hdc)
{

}

void PixelCollider::Release()
{

}

float PixelCollider::autoMove(float x, float y, RECT shape)
{
	float tempPosY = y + 100 * TimerManager::GetSingleton()->GetDeltaTime();

	for (int i = 0; i < 10; i++)
	{
		color = GetPixel(pixelMap->GetMemDC(),
			x, shape.bottom + i);


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
			break;
		}
	}
}

POINTFLOAT PixelCollider::Move(POINTFLOAT pos, RECT shape, float moveSpeed, int dir)
{
	for (int i = 0; i < 10; ++i)
	{
		i *= dir;	// laft = -1, right = +1
		color = GetPixel(pixelMap->GetMemDC(),
			shape.left + i, shape.bottom);

		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);

		if (r == 255 && g == 0 && b == 255)
		{
			cout << "pos : " << shape.left - i << ", ";
			cout << "r, g, b, " << r << ", " << g << ", " << b << "\n";
			pos.x -= moveSpeed;
			break;
		}

		return POINTFLOAT();
	}
}
