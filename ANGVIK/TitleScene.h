#pragma once
#include "stdafx.h"
#include "Config.h"
#include "GameEntity.h"

enum class FrameHeight { UP, DOWN };

enum class SeletedTitle { START, OPTION, EXIT };

//int maxNumber = (int)SeletedTitle::EXIT;


//SeletedTitle operator++ (SeletedTitle &s, int)
//{
//	//const SeletedTitle ePrev = s;
//	//const int i = static_cast<int>(s);
//	//s = static_cast<SeletedTitle>((i + 1) % 3);
//	//return ePrev;
//
//
//	using IntType = typename underlying_type<SeletedTitle>::type;
//	s = static_cast<SeletedTitle>(static_cast<IntType>(s) + 1);
//	if (s == SeletedTitle::EXIT)
//		s = static_cast<SeletedTitle>(0);
//	return s;
//}
//
//SeletedTitle operator-- (SeletedTitle &s,int)
//{
//	using IntType = typename underlying_type<SeletedTitle>::type;
//	s = static_cast<SeletedTitle>(static_cast<IntType>(s) - 1);
//	if (s == SeletedTitle::START)
//		s = static_cast<SeletedTitle>(3);
//	return s;
//}

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

	FrameHeight frameHeight = FrameHeight::DOWN; // �ؽ�Ʈ ���Ʒ� ������
	SeletedTitle seletedTitle = SeletedTitle::START;

	float boxFramecount = 0.0f;	// �����ڽ� ������
	float elepsedCount = 0.0f;	// �ؽ�Ʈ ���Ʒ� ������

	POINTFLOAT startTextPos = {};		// ��ŸƮ �ؽ�Ʈ Y ��ġ ����
	POINTFLOAT optionTextPos = {};		// �ɼ� �ؽ�Ʈ	Y ��ġ ����
	POINTFLOAT exitTextPos = {};		// ����Ʈ �ؽ�Ʈ Y ��ġ ����
	POINTFLOAT seletedBoxPos = {};		// ���� �ڽ�		��ġ ����
	POINTFLOAT logoPos = {};			// �Ӻ� �ΰ�		��ġ ����


	int seletedBoxFrame = 0;		// �����ڽ� �����Ӱ��� ����


};

