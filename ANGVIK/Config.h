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

// â ������ġ
#define WIN_START_POS_X	200
#define WIN_START_POS_Y	100

// â ũ��
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

config ��� ������Ʈ���� �����ϸ� ������ (�̹����Ŵ��� ����)

�������� ����

���������� , ������Ʈ �Ŵ��� ,�浹 �Ŵ��� ����

�ʿ� �����ϴ� ��ü������ ������ ����(?)��

�����쿵���� ��� ��ü���� �������� �������ʴ´�.(������Ʈ�� ������ҵ��� �Ǵ� �Ϻθ� ex) ammo )

�׸��� �浹üũ ���� �����ʴ´�.

�ش� ��ü�� ������ ������ �����ԵǸ� 

1. �������� �ش� ������Ʈ �Ŵ��� ���� �˸��� �༭ ������ �����Ѵ�.

2. �������� �浹 �Ŵ������� �ش簴ü�� ������ ������ �������� �浹üũ�� �����ض�.

�浹�Ŵ����� �����쿵���� �����ϴ� ��ü�鳢���� �浹�񱳸� �Ѵ�.

�ش� ��ü�� ������ ������ ����� �ٽ� �˸��� �༭ �� ��Ȳ�� �ݺ��Ѵ�.



�浹 �Ŵ�����

������ ������ �����ϴ� ��ü���� Ÿ��, ��Ʈ������ �������ִ�

A��� ��ü�� �浹üũ �Լ��� ȣ���ϸ� 

�浹�Ŵ����� �������մ� ��ü���� ��Ʈ( == �����쿵���� �����ϴ�)���

��Ʈ�浹 �񱳸� �ؼ� Ư�� ��ü(B)�� �浹�ϰ� �ɰ��

�浹üũ �Լ��� ȣ���� A Ÿ�԰� �浹�� BŸ�Կ� Ÿ���� ���ؼ� ó���Ѵ�.

ex �÷��̾� rect.bottom -> ���� kong rect.top �� �浹 -> �÷��̾ ���� ��Ƽ� �׿���.

ex �÷��̾� rect.bottom -> Ʈ�� rect.top �� �浹 -> �÷��̾ ������ ��Ѵ�.

ex �÷��̾� ���� rect ->  ���� rect�� �浹 -> ���⸦ �ֵѷ��� ���Ͱ� �¾Ѵ�.

ex ���� monkey rect ->  �÷��̾� rect �浹 -> ���Ͷ� �÷��̾ �ε����� �÷��̾ �������� �Ծ���.

�� B(��ü)�� Ư�� �Ҽ��־����.

*/

/*
enemy �� ������

�� �����.

class dog, class cat

enemyManager �� �ְ�
�� 5����, ����� 5���� ����.

������ ��,����̵��� ������ �ּҰ��� �����Ѵ�.

�׷��� ��,����̰� ���������� ����ϴ� �Լ��� �����ϰ�

enemyManager �� �� �Լ��� ȣ�������

������ ��������� ���� ������ �޶�����.
�׷��� ���ǹ����Ἥ ��������� ������ ����, �� 
*/


/*
�ݸ��� �Ŵ�����
�÷��̾�, ���͸Ŵ���, Ʈ���Ŵ����� �ּҸ� �˰��մ´�.

�÷��̾ �ݸ��� �Ŵ����� ���� �浹�Լ��� ȣ���ؼ� ��Ʈ���� �Ѱ��ָ�

�ݸ��� �Ŵ����� ��Ʈ���� �޾Ƽ� �ٽ� ���͸Ŵ���, Ʈ���Ŵ������� �Ѱ��ְ�

���͸Ŵ����� ���� ��Ʈ���� , ���͵�� �浹�񱳸� ���ش�.

Ʈ���Ŵ����� ��������.

�浹������ , �ش� Ÿ�԰� �浹������ �޾Ƽ� ó�����ش�.

�÷��̾� -> ����

���� -> ž -> �÷��̾ ���͸� ��Ѵ�.

�÷��̾� -> Ʈ��

��Ʈ -> ��Ʈ �÷��̾ Ʈ���� ������.

���� -> �÷��̾�

��Ʈ -> ��Ʈ ���Ͱ� �÷��̾�� �ε�����.


*/

/*
������� �̵��� �� �ִϸ��̼� ���ľ���. 

�÷��� �մ� ��ġ�� �����ȼ��� �����վ �÷����� ������� �ö������� ���� < �ȼ��� �����ִ��� �ؾ���

������ ���ü
���ڵ�,����Ʈ�ڵ� �ؽ�Ʈ �߰��ؾ���
�Լ��� dir�� ���� 0= back, 1= front

�����ۺ� �ִϸ��̼� �������

�⺻ ������ Į, â �� ����������

�� ����
����üũ �浹�Ŵ����� �浹üũ ���ֱ�

���� �ִϸ��̼� �߰����ֱ�

�� �Ƹ� ����Ʈ ��ƼŬ�Ŵ����� �̽����ֱ�

�÷��̾� ������ �������ְ� 
Ʈ���� Ȱ���ϱ�.
ex) �� ����, �����

�� �ȼ� �����ֱ�

*/