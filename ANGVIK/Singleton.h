// Singleton.h

// �̱��� ���� : ���α׷����� �ϳ��� �����ϴ� ��ü�� �ʿ��� �� ���Ǵ� ����
// ���� ) Ű �Ŵ��� (�����ϴ� ��ü), �� �Ŵ���, �÷��̾� ������...

#pragma once

//goto

template <typename T>
/*static*/ class Singleton
{
public:
	virtual ~Singleton() = default;

public:
	static T* GetSingleton()
	{
		static T instance;

		return &instance;
	}
protected:
	Singleton() {}		// ������, �Ҹ��ڸ� ���� ȣ������ ���ϰ� �ҰŴ�.
};