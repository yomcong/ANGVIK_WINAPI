#pragma once
#include "Config.h"
#include "Singleton.h"

class Image;
class ImageManager : public Singleton<ImageManager>
{
private:
	map<string, Image*>	mapImages;
	//map<string, map<int, int>>	mapTest;

	//"enemy_3_bullet"
	/*
	* �̹����� 600000���� ����ߴ�.
	* 6�� �߿� bullet.bmp�� ã�´�.
	* ã������ �����Ѵ�.
	* 
	// �ڷᱸ�� : vector ���� ũ�⸦ ���������� �ٲ� �� �ִ�.
	//					���� ����, ������ �ʿ��ϸ� �޸��Ҵ��
							���簡 �Ͼ�� �ӵ��� ������

				 map	���� ã�� �ӵ��� ���� �ڷᱸ��
						���� �ڷᱸ�� ������ �����ϴ�
	*/

public:
	virtual ~ImageManager() = default;

	void Init();
	void Release();

	/*
	HRESULT Init(const char* fileName, int width, int height,
		bool isTrans = false, COLORREF transColor = NULL); // File �������� ���� �̹���
	HRESULT Init(const char* fileName, int width, int height,
		int maxFrameX, int maxFrameY,
		bool isTrans = false, COLORREF transColor = NULL);
		
	*/

	Image* AddImage(const char* fileName, int width, int height,
		bool isTrans = false, COLORREF transColor = NULL);	// ����� �̹����� ����ϴ� ���
	
	Image* AddImage(const char* fileName, int width, int height,
		int maxFrameX, int maxFrameY,
		bool isTrans = false, COLORREF transColor = NULL);
	
	Image* FindImage(const char* fileName);	// ��ϵ� �̹��� �߿� �ʿ��� �̹����� ã�� ���
	void DeleteImage(const char* fileName);	// ����� ����� �̹����� ��� �����ϴ� ���
};

