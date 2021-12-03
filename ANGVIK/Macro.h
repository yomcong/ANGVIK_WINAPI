#pragma once


// 창 시작위치
#define WIN_START_POS_X	400
#define WIN_START_POS_Y	200

// 창 크기
#define WIN_SIZE_X	960
#define WIN_SIZE_Y	540

#define SAFE_RELEASE(p)	{ if (p) { p->Release(); delete p; p = nullptr; } }
#define SAFE_DELETE(p)	{ if (p) { delete p; p = nullptr; } }

#define RANDOM(min, max) (rand() % ((max) - (min) + 1) + (min))


#define PI 3.14159265357989
#define PI2 (3.14159265357989 * 2)

#define DEGREE_TO_RADIAN(x)		(x * PI / 180.0f)

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

