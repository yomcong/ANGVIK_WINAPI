#pragma once
#include "Config.h"
#include "GameEntity.h"

enum class FrameHeight { UP, DOWN };

enum class SeletedTitle { START, OPTION, EXIT };

class Image;
class TitleScene : public GameEntity
{
public:
	virtual ~TitleScene() = default;

	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	void ChooseTitle();
	void ResetAnimation();



private:
	Image* titleBackgruond = nullptr;
	Image* titleMenuBar = nullptr;
	Image* startText = nullptr;
	Image* optionText = nullptr;
	Image* exitText = nullptr;
	Image* seletedBox = nullptr;
	Image* angvikLogo = nullptr;

	FrameHeight frameHeight = FrameHeight::DOWN; 
	SeletedTitle seletedTitle = SeletedTitle::START;

	float boxFramecount = 0.0f;	// 셀렉박스 프레임
	float elepsedCount = 0.0f;	// 텍스트 위아래 흔들흔들

	POINTFLOAT startTextPos = {};		
	POINTFLOAT optionTextPos = {};		
	POINTFLOAT exitTextPos = {};		
	POINTFLOAT seletedBoxPos = {};		
	POINTFLOAT logoPos = {};			

	int seletedBoxFrame = 0;		// 셀렉박스 프레임관리 변수
};

