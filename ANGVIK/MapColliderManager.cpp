//#include "stdafx.h"
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

bool MapColliderManager::IsFalling(POINTFLOAT _pos, RECT _shape, float _moveSpeed, POINT _bodySize, SubjectTag _subTag)
{
	//float tempPosY = y + moveSpeed * Timer::GetDeltaTime();
	
	if (_subTag == SubjectTag::PLAYER)
	{
		for (int i = (int)(_bodySize.x * 0.2); i <= (int)(_bodySize.x * 0.8); i++)
		{
			color = GetPixel(pixelMap->GetMemDC(),
				_shape.left + i, _shape.bottom + 1);

			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);


			if (false == (r == 255 && g == 0 && b == 255))
			{
				return false;
			}
		}

	}
	else
	{
		for (int i = 0; i <= _bodySize.x; i++)
		{
			color = GetPixel(pixelMap->GetMemDC(),
				_shape.left + i, _shape.bottom + 1);

			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);


			if (false == (r == 255 && g == 0 && b == 255))
			{
				return false;
			}
		}
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

	pos.x = (moveSpeed * Timer::GetDeltaTime()) * dir;
	pos.y = -height;
	return pos;
}

bool MapColliderManager::Jump(POINTFLOAT pos, RECT shape, float moveSpeed,  POINT bodySize)
{
	for (int i = (int)(bodySize.x*0.2); i < (int)(bodySize.x*0.8); i++)
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

bool MapColliderManager::checkCollision(SubjectTag _subTag, RECT shape, int dir, POINT bodySize)
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
				ParticleManager::GetSingleton()->CallParticle(_subTag, { (float)shape.right, (float)shape.bottom - i });
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
				ParticleManager::GetSingleton()->CallParticle(_subTag, { (float)shape.left, (float)shape.bottom - i });
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
			ParticleManager::GetSingleton()->CallParticle(_subTag, { (float)shape.left+i, (float)shape.bottom});
			return true;
		}
	}
	for (int i = 0; i < bodySize.x; i++)
	{
		color = GetPixel(pixelMap->GetMemDC(),
			shape.left + i, shape.top);

		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);


		if (false == (r == 255 && g == 0 && b == 255))
		{
			ParticleManager::GetSingleton()->CallParticle(_subTag, { (float)shape.left + i, (float)shape.top });
			return true;
		}
	}

	return false;
}

