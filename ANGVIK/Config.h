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

enum class SubjectTag { IDLE, PLAYER, ENEMY, ITEM, TRAP };
enum class EventTag { IDLE, ADD, COLLISION, RELEASE, };
enum class direction { LEFT = -1, RIGHT = 1};

// 창 시작위치
#define WIN_START_POS_X	200
#define WIN_START_POS_Y	100

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
#include "CameraManager.h"
#include "InputManager.h"

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern POINT g_ptMouse;

#define RANDOM(minNum, maxNum) (rand() % (maxNum - minNum+1)) + minNum

/*

config 헤더 서브젝트별로 정리하면 오류남 (이미지매니저 오류)

--옵저버 구현 해야함..--

생각중인 구조

옵저버패턴 , 오브젝트 매니저 ,충돌 매니저 구현

맵에 존재하는 객체들한테 옵저버 장착(?)후

윈도우영역에 벗어난 객체들은 랜더링을 해주지않는다.(업데이트는 해줘야할듯 또는 일부만 ex) ammo )

그리고 충돌체크 역시 하지않는다.

해당 객체가 윈도우 영역에 들어오게되면 

1. 옵저버가 해당오브젝트 매니저 한테 알림을 줘서 랜더를 시작한다.

2. 옵저버가 충돌 매니저한테 해당객체가 윈도우 영역에 들어왔으니 충돌체크를 시작해라.

충돌매니저는 윈도우영역에 존재하는 객체들끼리만 충돌비교를 한다.

해당 객체가 윈도우 영역에 벗어나면 다시 알림을 줘서 위 상황을 반복한다.



충돌 매니저는

윈도우 영역에 존재하는 객체들의 타입, 렉트정보를 가지고있다

A라는 객체가 충돌체크 함수를 호출하면 

충돌매니저가 가지고잇는 객체들의 렉트( == 윈도우영역에 존재하는)들과

렉트충돌 비교를 해서 특정 객체(B)와 충돌하게 될경우

충돌체크 함수를 호출한 A 타입과 충돌한 B타입에 타입을 비교해서 처리한다.

ex 플레이어 rect.bottom -> 몬스터 kong rect.top 과 충돌 -> 플레이어가 콩을 밟아서 죽였다.

ex 플레이어 rect.bottom -> 트랩 rect.top 과 충돌 -> 플레이어가 함정을 밟앗다.

ex 플레이어 무기 rect ->  몬스터 rect가 충돌 -> 무기를 휘둘러서 몬스터가 맞앗다.

ex 몬스터 monkey rect ->  플레이어 rect 충돌 -> 몬스터랑 플레이어가 부딪혀서 플레이어가 데미지를 입엇다.

단 B(객체)를 특정 할수있어야함.
*/