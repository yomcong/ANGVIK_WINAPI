#pragma once
#include "Config.h"
#include "GameEntity.h"
#include "Observer.h"

class Player;
class MonsterManager;
class Image;
class TrapManager;
class ItemManager;
class AmmoManager;
class StageScene : public GameEntity, public Observer
{
public:
	virtual ~StageScene() = default;

	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	virtual void OnNotify(Subject* _subject, MonsterType _monsterType, SubjectTag _subjectTag, EventTag _eventTag) override;

private:
	Image* stageBackgruond = nullptr;
	Image* stageBackgruond2 = nullptr;
	Image* stagePixelMap = nullptr;
	Image* stageHiddenMap = nullptr;

	bool b_hiddenMapDiscovery = false;

	POINT mapPos = {};

	Player* player = nullptr;
	MonsterManager* monsterManager = nullptr;
	TrapManager* trapManager = nullptr;
	ItemManager* itemManager = nullptr;
	AmmoManager* ammoManager = nullptr;

	//����׿�
	bool debugPixelMap = false;

};

