#include "TitleScene.h"
#include "Image.h"

HRESULT TitleScene::Init()
{
	titleBackgruond = ImageManager::GetSingleton()->FindImage("image/etc/배경.bmp");	//타이틀 백그라운드
	if (titleBackgruond == nullptr)
	{
		return E_FAIL;
	}
	titleMenuBar = ImageManager::GetSingleton()->FindImage("image/etc/메뉴바.bmp");	//타이틀 메뉴 바
	if (titleMenuBar == nullptr)
	{
		return E_FAIL;
	}
	startText = ImageManager::GetSingleton()->FindImage("image/etc/start.bmp");	//타이틀 start text
	if (startText == nullptr)
	{
		return E_FAIL;
	}
	optionText = ImageManager::GetSingleton()->FindImage("image/etc/options.bmp");	//타이틀 option text
	if (optionText == nullptr)
	{
		return E_FAIL;
	}
	exitText = ImageManager::GetSingleton()->FindImage("image/etc/exit.bmp");	//타이틀 exit text
	if (exitText == nullptr)
	{
		return E_FAIL;
	}
	seletedBox = ImageManager::GetSingleton()->FindImage("image/etc/선택2.bmp");	// 선택 박스
	if (seletedBox == nullptr)
	{
		return E_FAIL;
	}
	angvikLogo = ImageManager::GetSingleton()->FindImage("image/etc/로고.bmp");	// 앙빅 로고
	if (angvikLogo == nullptr)
	{
		return E_FAIL;
	}

	// 셀렉 박스
	seletedBoxPos.x = WIN_SIZE_X * 0.25;
	seletedBoxPos.y = WIN_SIZE_Y * 0.75;

	// 스타트 텍스트
	startTextPos.x = WIN_SIZE_X * 0.25f;
	startTextPos.y = WIN_SIZE_Y * 0.75f;

	// 옵션 텍스트
	optionTextPos.x = WIN_SIZE_X * 0.50f;
	optionTextPos.y = WIN_SIZE_Y * 0.75f;

	// 엑시트 텍스트
	exitTextPos.x = WIN_SIZE_X * 0.75f;
	exitTextPos.y = WIN_SIZE_Y * 0.75f;
	
	// 앙빅 로고 
	logoPos.x = WIN_SIZE_X * 0.50f;
	logoPos.y = WIN_SIZE_Y * 0.30f;


	return S_OK;
}

void TitleScene::Update()
{
	elepsedCount += Timer::GetDeltaTime();
	boxFramecount += Timer::GetDeltaTime();

	if (Input::GetButtonDown(VK_SPACE))	// 씬 전환
	{
		// 게임시작
		if (seletedTitle == SeletedTitle::START)
		{
			SceneManager::GetSingleton()->ChangeScene("StageScene");
		}
		// 옵션
		else if (seletedTitle == SeletedTitle::OPTION)
		{
			SceneManager::GetSingleton()->ChangeScene("StageScene");
		}
		// 종료
		else
		{
			SceneManager::GetSingleton()->ChangeScene("StageScene");
		}
	}

	if (Input::GetButtonDown(VK_LEFT))
	{
		ResetAnimation();	// 키입력이 들어왓을때 애니메이션 동작들 초기값으로 초기화.

		if (seletedTitle == SeletedTitle::START)
		{
			seletedTitle = SeletedTitle::EXIT;
		}
		else if (seletedTitle == SeletedTitle::OPTION)
		{
			seletedTitle = SeletedTitle::START;
		}
		else
		{
			seletedTitle = SeletedTitle::OPTION;
		}
	}
	if (Input::GetButtonDown(VK_RIGHT))
	{
		ResetAnimation();

		if (seletedTitle == SeletedTitle::START)
		{
			seletedTitle = SeletedTitle::OPTION;
		}
		else if (seletedTitle == SeletedTitle::OPTION)
		{
			seletedTitle = SeletedTitle::EXIT;
		}
		else
		{
			seletedTitle = SeletedTitle::START;
		}
	}

	// 현재 선택된 씬에 따른 랜더 업데이트
	ChooseTitle();

	// 셀렉 박스 애니메이션 프레임
	if (boxFramecount > 0.125)
	{
		if (seletedBoxFrame == 7)
		{
			seletedBoxFrame = 0;
		}
		else
		{
			++seletedBoxFrame;
		}
		boxFramecount = 0;
	}

}

void TitleScene::Render(HDC hdc)
{
	titleBackgruond->Render(hdc);																// 타이틀 백그라운드

	titleMenuBar->Render(hdc, WIN_SIZE_X / 2, (int)(WIN_SIZE_Y * 0.75));						// 타이틀 메뉴 바

	seletedBox->Render(hdc, (int)seletedBoxPos.x, (int)seletedBoxPos.y, seletedBoxFrame, 0);	// 셀렉 박스

	angvikLogo->Render(hdc, (int)logoPos.x, (int)logoPos.y);
	startText->Render(hdc, (int)startTextPos.x, (int)startTextPos.y);							// 스타트 text
	optionText->Render(hdc, (int)optionTextPos.x, (int)optionTextPos.y);						// 옵션 text
	exitText->Render(hdc, (int)exitTextPos.x, (int)exitTextPos.y);
}

void TitleScene::Release()
{

}

void TitleScene::ChooseTitle()
{
	// 텍스트 흔들흔들 애니메이션 수치
	float animation = Timer::GetDeltaTime() * 5.0f;

	// 선택된 씬 텍스트 흔들흔들
	switch (seletedTitle)
	{
	case SeletedTitle::START:
		seletedBoxPos.x = WIN_SIZE_X * 0.25f;

		if (frameHeight == FrameHeight::DOWN)
		{
			startTextPos.y += animation;
		}
		else
		{
			startTextPos.y -= animation;
		}

		break;
	case SeletedTitle::OPTION:
		seletedBoxPos.x = WIN_SIZE_X * 0.50f;

		if (frameHeight == FrameHeight::DOWN)
		{
			optionTextPos.y += animation;
		}
		else
		{
			optionTextPos.y -= animation;
		}

		break;
	case SeletedTitle::EXIT:
		seletedBoxPos.x = WIN_SIZE_X * 0.75f;

		if (frameHeight == FrameHeight::DOWN)
		{
			exitTextPos.y += animation;
		}
		else
		{
			exitTextPos.y -= animation;
		}

		break;

	}

	// 흔들흔들 애니메이션
	if (((int)elepsedCount)%2 < 1)
	{
		frameHeight = FrameHeight::UP;
	}
	else
	{
		frameHeight = FrameHeight::DOWN;
	}
}

void TitleScene::ResetAnimation()
{
	startTextPos.y = WIN_SIZE_Y * 0.75f;
	optionTextPos.y = WIN_SIZE_Y * 0.75f;
	exitTextPos.y = WIN_SIZE_Y * 0.75f;
	seletedBoxFrame = 0;
}
