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

#define TILEMAPTOOL_SIZE_X	800
#define TILEMAPTOOL_SIZE_Y	600
#define PIXELMAP_SIZE_X	1000
#define PIXELMAP_SIZE_Y	800

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

enum class MoveDir { Left = 2, Right = 6, Up = 0, Down = 4 };
enum class TankType { Player, Normal, Speed, Rapid, Defensive };

#include "TimerManager.h"
#include "ImageManager.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "GameManager.h"
#include "MapColliderManager.h"

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern POINT g_ptMouse;

//Ÿ�� ����
#define TILE_SIZE	16
#define TILE_COUNT_X	26
#define TILE_COUNT_Y	26
#define SAMPLE_TILE_COUNT_X 8
#define SAMPLE_TILE_COUNT_Y	2
#define STAGE_SIZE_X (WIN_SIZE_X / 2 - 8 * TILE_COUNT_X - 16)
#define STAGE_SIZE_Y (WIN_SIZE_Y / 2 - 8 * TILE_COUNT_Y)

#define RANDOM(min, max) (rand() % ((max) - (min) + 1) + (min))
#define CORRECTION_POS_MIN 8
#define CORRECTION_POS_MAX 8

enum class Terrain { Earth, Wall, Water, Grass, BreakableWall, End };

enum class TileType { Ground, Wall, Water, Iced, Grass, Brick, Nexus };
typedef struct tagSampleTile
{
	RECT rc;
	int frameX, frameY;
} SAMPLE_TILE_INFO;

typedef struct tagTile
{
	TileType tileType;
	RECT rc;				
	//image
	// sample tile�� ���̵� (������ X, ������ Y)
	int frameX, frameY;

	RECT collider;		// bullet Hit Collider
	RECT bodyCollider;	// Body Collider

	int leftHit;
	int rightHit;
	int topHit;
	int bottomHit;

} TILE_INFO;