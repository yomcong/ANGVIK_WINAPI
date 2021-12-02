#pragma once
#include <Windows.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <map>
#include <iostream>
#include <string>

using namespace std;

#pragma comment(lib, "winmm.lib")

// 창 시작위치
#define WIN_START_POS_X	400
#define WIN_START_POS_Y	200

// 창 크기
#define WIN_SIZE_X	960
#define WIN_SIZE_Y	540

#define PI 3.14159265357989
#define PI2 (3.14159265357989 * 2)

#define DEGREE_TO_RADIAN(x)		(x * PI / 180.0f)

#define SAFE_RELEASE(p)	{ if (p) { p->Release(); delete p; p = nullptr; } }
#define SAFE_DELETE(p)	{ if (p) { delete p; p = nullptr; } }

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

#include "TimerManager.h"
#include "ImageManager.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "GameManager.h"
#include "MapColliderManager.h"

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern POINT g_ptMouse;

#define RANDOM(min, max) (rand() % ((max) - (min) + 1) + (min))

/*

스테이지 씬
카메라 스크롤 만들기
경고 물어보기
(ex : int 에서 float 으로 변환)

타이틀씬
이넘클래스 증감연산자 오퍼레이터 오버로딩 질문
이미지 파인드 함수로 묶기

플레이어
POINT 변수 물어보기(애니메이션프레임, 바디사이즈) 
각 애니매이션 맥스프레임을 변수로 적을지 상수로 적을지


해야할것 

인벤토리구현,


*/