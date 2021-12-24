#pragma once
enum class SubjectTag { IDLE, PLAYER, MONSTER, ITEM, TRAP, PLATFORM, AMMO, WEAPON };
enum class EventTag { IDLE, ADD, INWINDOW, OUTWINDOW, RANGECOLLISION, RELEASE, };
enum class direction { LEFT = -1, RIGHT = 1 };

enum class MonsterType { IDLE, KONG, MONKEY, ENT };

enum class ItemType { IDLE, HELMET, ARMOR, WEAPON, SHOES, OLIS };
enum class WeaponType { IDLE, SWORD, BOOMERANG, LANCE, STAFF };
enum class ItemGrade { IDLE, BASIC, GOLD, SILVER };

struct ItemInfo
{
	ItemType itemType = ItemType::IDLE;
	ItemGrade itemgrade = ItemGrade::IDLE;
	WeaponType weaponType = WeaponType::IDLE;
};
#include <Windows.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <map>
#include <iostream>
#include <string>

using namespace std;

//#include "TimerManager.h"
#include "ImageManager.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "GameManager.h"
#include "MapColliderManager.h"
#include "CameraManager.h"
#include "InputManager.h"
#include "CollisionManager.h"
#include "ParticleManager.h"
#include "Timer.h"

#pragma comment(lib, "winmm.lib")
