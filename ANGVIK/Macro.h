#pragma once

//enum class SubjectTag { IDLE, PLAYER, MONSTER, ITEM, TRAP, PLATFORM, AMMO, WEAPON };
//enum class EventTag { IDLE, ADD, INWINDOW, OUTWINDOW, RANGECOLLISION, RELEASE, };
//enum class direction { LEFT = -1, RIGHT = 1 };
//
//enum class MonsterType { IDLE, KONG, MONKEY, ENT };
//
//enum class ItemType { IDLE, HELMET, ARMOR, WEAPON, SHOES, OLIS };
//enum class WeaponType { IDLE, SWORD, BOOMERANG, LANCE, STAFF };
//enum class ItemGrade { IDLE, BASIC, GOLD, SILVER };
//
//struct ItemInfo
//{
//	ItemType itemType = ItemType::IDLE;
//	ItemGrade itemgrade = ItemGrade::IDLE;
//	WeaponType weaponType = WeaponType::IDLE;
//};

// 창 시작위치
#define WIN_START_POS_X	400
#define WIN_START_POS_Y	200

// 창 크기
#define WIN_SIZE_X	960
#define WIN_SIZE_Y	540

#define SAFE_RELEASE(p)	{ if (p) { p->Release(); delete p; p = nullptr; } }
#define SAFE_DELETE(p)	{ if (p) { delete p; p = nullptr; } }

#define RANDOM(min, max) (rand() % ((max) - (min) + 1) + (min))

#define DEGREE_TO_RADIAN(x)		(x * PI / 180.0f)

#define PI 3.14159265357989
#define PI2 (3.14159265357989 * 2)


#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
 //Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
 //allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

