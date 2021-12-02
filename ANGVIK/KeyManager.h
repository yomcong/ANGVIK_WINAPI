#pragma once
#include "Config.h"
#include <vector>
#include <bitset>	// stl�ڷᱸ�� vector
#include "Singleton.h"

using namespace std;

#define KEY_MAX_COUNT	256

class KeyManager : public Singleton<KeyManager>
{
private:
	// ���� ���� �ּ�

	bitset<KEY_MAX_COUNT>	keyUp;	// Ű�� �� ���� �������� �ƴ���
	bitset<KEY_MAX_COUNT>	keyDown;// Ű�� ���� �������� �ƴ���

public:
	virtual ~KeyManager() = default;

	void Init();
	void Release();

	bool IsOnceKeyDown(int key);	// Ű�� ù��°�� ���ȴ��� �Ǵ�
	bool IsOnceKeyUp(int key);		// Ű�� ù��°�� ���ȴٰ� ���������� �Ǵ�
	bool IsStayKeyDown(int key);	// Ű�� ������ �ִ��� �Ǵ�
};

