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

// â ������ġ
#define WIN_START_POS_X	400
#define WIN_START_POS_Y	200

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

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern POINT g_ptMouse;

#define RANDOM(min, max) (rand() % ((max) - (min) + 1) + (min))

/*

�������� ��
ī�޶� ��ũ�� �����
��� �����
(ex : int ���� float ���� ��ȯ)

Ÿ��Ʋ��
�̳�Ŭ���� ���������� ���۷����� �����ε� ����
�̹��� ���ε� �Լ��� ����

�÷��̾�
POINT ���� �����(�ִϸ��̼�������, �ٵ������) 
�� �ִϸ��̼� �ƽ��������� ������ ������ ����� ������


�ؾ��Ұ� 

�κ��丮����,


*/