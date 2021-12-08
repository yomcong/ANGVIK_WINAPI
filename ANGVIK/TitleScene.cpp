#include "TitleScene.h"
#include "Image.h"

// ������Ʈ
// �Ϸ��õ� ī��Ʈ�� �ؽ�Ʈ ���Ʒ� ���Ÿ� �� �����ڽ� �ִϸ��̼� ���� ����

// ���õ� �ؽ�Ʈ ���Ʒ��� ���Ÿ��� ���
// �Ϸ���Ʈī��Ʈ�� ��ŸŸ������ ������Ű�µ�, �Ҽ������� �����Ǵٺ���, �ּ�,�ִ�ġ�� ���������� ���ڿ�������

// ���õ� �ؽ�Ʈ�� �Ķ��ڽ� �Ϸ��Ÿ��� ���
// ��ŸŸ���� �Ҽ����̶� ������ ������ �ڿ������� ����

HRESULT TitleScene::Init()
{
	titleBackgruond = ImageManager::GetSingleton()->FindImage("image/etc/���.bmp");	//Ÿ��Ʋ ��׶���
	if (titleBackgruond == nullptr)
	{
		return E_FAIL;
	}
	titleMenuBar = ImageManager::GetSingleton()->FindImage("image/etc/�޴���.bmp");	//Ÿ��Ʋ �޴� ��
	if (titleMenuBar == nullptr)
	{
		return E_FAIL;
	}
	startText = ImageManager::GetSingleton()->FindImage("image/etc/start.bmp");	//Ÿ��Ʋ start text
	if (startText == nullptr)
	{
		return E_FAIL;
	}
	optionText = ImageManager::GetSingleton()->FindImage("image/etc/options.bmp");	//Ÿ��Ʋ option text
	if (optionText == nullptr)
	{
		return E_FAIL;
	}
	exitText = ImageManager::GetSingleton()->FindImage("image/etc/exit.bmp");	//Ÿ��Ʋ exit text
	if (exitText == nullptr)
	{
		return E_FAIL;
	}
	seletedBox = ImageManager::GetSingleton()->FindImage("image/etc/����2.bmp");	// ���� �ڽ�
	if (seletedBox == nullptr)
	{
		return E_FAIL;
	}
	angvikLogo = ImageManager::GetSingleton()->FindImage("image/etc/�ΰ�.bmp");	// �Ӻ� �ΰ�
	if (angvikLogo == nullptr)
	{
		return E_FAIL;
	}
	

	// ���� �ڽ�
	seletedBoxPos.x = WIN_SIZE_X * 0.25;
	seletedBoxPos.y = WIN_SIZE_Y * 0.75;

	// ��ŸƮ �ؽ�Ʈ
	startTextPos.x = WIN_SIZE_X * 0.25f;
	startTextPos.y = WIN_SIZE_Y * 0.75f;

	// �ɼ� �ؽ�Ʈ
	optionTextPos.x = WIN_SIZE_X * 0.50f;
	optionTextPos.y = WIN_SIZE_Y * 0.75f;

	// ����Ʈ �ؽ�Ʈ
	exitTextPos.x = WIN_SIZE_X * 0.75f;
	exitTextPos.y = WIN_SIZE_Y * 0.75f;
	
	// �Ӻ� �ΰ� 
	logoPos.x = WIN_SIZE_X * 0.50f;
	logoPos.y = WIN_SIZE_Y * 0.30f;


	return S_OK;
}

void TitleScene::Update()
{
	elepsedCount += TimerManager::GetSingleton()->GetDeltaTime();
	boxFramecount += TimerManager::GetSingleton()->GetDeltaTime();

	if (Input::GetButtonDown(VK_SPACE))	// �� ��ȯ
	{
		if (seletedTitle == SeletedTitle::START)
		{
			SceneManager::GetSingleton()->ChangeScene("StageScene");
		}
		else if (seletedTitle == SeletedTitle::OPTION)
		{
			SceneManager::GetSingleton()->ChangeScene("StageScene");
		}
		else
		{
			SceneManager::GetSingleton()->ChangeScene("StageScene");
		}
	}

	if (Input::GetButtonDown(VK_LEFT))
	{
		//seletedtitle--;
		ResetAnimation();	// Ű�Է��� �������� �ִϸ��̼� ���۵� �ʱⰪ���� �ʱ�ȭ.

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
		//seletedtitle++;
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

	// ���� ���õ� ���� ���� ���� ������Ʈ
	ChooseTitle();

	// ���� �ڽ� �ִϸ��̼� ������
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

	if (boxFramecount > 1000)
		boxFramecount = 0.0f;
}

void TitleScene::Render(HDC hdc)
{
	titleBackgruond->Render(hdc);																// Ÿ��Ʋ ��׶���

	titleMenuBar->Render(hdc, WIN_SIZE_X / 2, (int)(WIN_SIZE_Y * 0.75));						// Ÿ��Ʋ �޴� ��

	seletedBox->Render(hdc, (int)seletedBoxPos.x, (int)seletedBoxPos.y, seletedBoxFrame, 0);	// ���� �ڽ�

	angvikLogo->Render(hdc, (int)logoPos.x, (int)logoPos.y);
	startText->Render(hdc, (int)startTextPos.x, (int)startTextPos.y);							// ��ŸƮ text
	optionText->Render(hdc, (int)optionTextPos.x, (int)optionTextPos.y);						// �ɼ� text
	exitText->Render(hdc, (int)exitTextPos.x, (int)exitTextPos.y);								// ����Ʈ text

}

void TitleScene::Release()
{

}

void TitleScene::ChooseTitle()
{
	// �ؽ�Ʈ ������ �ִϸ��̼� ��ġ
	float animation = TimerManager::GetSingleton()->GetDeltaTime() * 5.0f;

	// ���õ� �� �ؽ�Ʈ ������
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

	// ������ �ִϸ��̼�
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
