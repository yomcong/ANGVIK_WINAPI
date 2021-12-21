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

enum class SubjectTag { IDLE, PLAYER, MONSTER, ITEM	, TRAP, PLATFORM , AMMO, WEAPON };
enum class EventTag { IDLE, ADD, INWINDOW, OUTWINDOW, COLLISION, RELEASE, };
enum class direction { LEFT = -1, RIGHT = 1};

enum class MonsterType {IDLE, KONG, MONKEY, ENT};

enum class ItemType {IDLE, HELMET, ARMOR, WEAPON, SHOES, OLIS};
enum class WeaponType {IDLE, SWORD, BOOMERANG, LANCE, STAFF};
enum class ItemGrade {IDLE, BASIC, GOLD, SILVER};

struct ItemInfo
{
	ItemType itemType = ItemType::IDLE;
	ItemGrade itemgrade= ItemGrade::IDLE;
	WeaponType weaponType = WeaponType::IDLE;
};

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
#include "CollisionManager.h"
#include "ParticleManager.h"

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern POINT g_ptMouse;

#define RANDOM(minNum, maxNum) (rand() % (maxNum - minNum+1)) + minNum

/*

config 헤더 서브젝트별로 정리하면 오류남 (이미지매니저 오류)

생각중인 구조

옵저버패턴 , 오브젝트 매니저 ,충돌 매니저 구현

맵에 존재하는 객체들한테 옵저버 장착(?)후

윈도우영역에 벗어난 객체들은 랜더링을 해주지않는다.(업데이트는 해줘야할듯함 또는 일부만 ex) ammo )

그리고 충돌체크 역시 하지않는다.

해당 객체가 윈도우 영역에 들어오게되면 

1. 옵저버가 해당 오브젝트 매니저 한테 알림을 줘서 랜더를 시작한다.

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

/*
enemy 가 두종류

개 고양이.

class dog, class cat

enemyManager 가 있고
개 5마리, 고양이 5마리 생성.

각각의 개,고양이들은 고유의 주소값이 존재한다.

그런데 개,고양이가 공통적으로 사용하는 함수가 존재하고

enemyManager 는 그 함수가 호출됬을때

개인지 고양인지에 따라서 실행이 달라지고.
그러면 조건문을써서 고양이인지 개인지 구분, 후 
*/


/*
콜리전 매니저가
플레이어, 몬스터매니저, 트랩매니저의 주소를 알고잇는다.

플레이어가 콜리전 매니저를 통해 충돌함수를 호출해서 렉트값을 넘겨주면

콜리전 매니저가 렉트값을 받아서 다시 몬스터매니저, 트랩매니저한테 넘겨주고

몬스터매니저가 받은 렉트값과 , 몬스터들과 충돌비교를 해준다.

트랩매니저도 마찬가지.

충돌했으면 , 해당 타입과 충돌부위를 받아서 처리해준다.

플레이어 -> 몬스터

바텀 -> 탑 -> 플레이어가 몬스터를 밟앗다.

플레이어 -> 트랩

렉트 -> 렉트 플레이어가 트랩에 빠졋다.

몬스터 -> 플레이어

렉트 -> 렉트 몬스터가 플레이어와 부딪혓다.


*/

/*
경사진곳 이동할 때 애니메이션 고쳐야함. 

플랫폼 잇는 위치에 나무픽셀이 남아잇어서 플랫폼이 사라져도 올라가잇을수 잇음 < 픽셀을 지워주던지 해야함

아이템 장비교체
백핸드,프론트핸드 텍스트 추가해야함
함수는 dir로 관리 0= back, 1= front

아이템별 애니메이션 해줘야함

기본 장착은 칼, 창 만 구현되있음

콩 몬스터
범위체크 충돌매니저로 충돌체크 해주기

공격 애니메이션 추가해주기

콩 아모 이펙트 파티클매니저로 이식해주기

플레이어 옵저버 장착해주고 
트리거 활용하기.
ex) 몹 스폰, 히든맵

물 픽셀 지워주기

*/