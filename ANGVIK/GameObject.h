#pragma once

// ������ ������� ������ ���� �⺻���� ������ �Ǵ� Ŭ����
// �ʱ�ȭ (�޸� �Ҵ�), 1ȸ�� ����
// ������Ʈ, ���������� �����Ӹ��� ����
// ���, ���������� �����Ӹ��� ����
// �޸� ����, 1ȸ�� ����

/*
	��� : �ߺ��Ǵ� �ڵ带 ���� �� �ִ�.
	�߻�ȭ : ���Ǽ��迡 �ִ� ��ü�� ���Ӱ�ü�� �ʿ��� �����͸� �߷��� ��.

	Ŭ���� �߻�ȭ : Ŭ���� �� ����Ǵ� ������� �߷��� ��.
*/

#include "GameEntity.h"

class Image;
class GameObject : public GameEntity
{
protected:
	POINTFLOAT pos = {};
	RECT shape = {};
	float moveSpeed = 0.0f;
	//int bodySize = 0;

	Image* img = nullptr;

public:
	inline void SetPos(POINTFLOAT pos) { this->pos = pos; }
	inline void SetMoveSpeed(float speed) { this->moveSpeed = speed; }

	inline const POINTFLOAT GetPos() { return this->pos; }
	inline const RECT GetShape() { return this->shape; }


	//inline int GetBodySize() { return this->bodySize; }
	//inline const RECT* GetShapeAddress() { return &this->shape; }

	GameObject() = default;
	virtual ~GameObject() = default;
};

