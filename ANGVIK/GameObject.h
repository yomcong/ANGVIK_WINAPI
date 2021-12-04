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
	// ��ǥ
	POINTFLOAT pos = {};
	// ������ ��ǥ
	POINTFLOAT renderPos = {};
	// �浹üũ ��Ʈ
	RECT shape = {};
	// ��Ʈ ������
	POINT bodySize = {};
	// �̵��ӵ�
	float moveSpeed = 0.0f;

	// �ִϸ��̼� ������
	POINT framePos = {};
	// �ִϸ��̼� �����Ӱ��� ī��Ʈ
	float frameCount = 0.0f;

	// ����׿� ��Ʈ
	bool DBrect = false;
	RECT DBRenderShape = {};


public:
	inline void SetPos(POINTFLOAT pos) { this->pos = pos;/* POINTFLOAT{pos.x + CameraManager::GetSingleton()->GetPos().x, pos.y + CameraManager::GetSingleton()->GetPos().y};*/ }
	inline void SetMoveSpeed(float speed) { this->moveSpeed = speed; }

	inline const POINTFLOAT GetPos() { return this->pos; }
	inline const RECT GetShape() { return this->shape; }
	inline const int GetBodySizeX() { return this->bodySize.x; }
	inline const int GetBodySizeY() { return this->bodySize.y; }

	inline void SetDBrect(bool DBrect) { this->DBrect = DBrect; }

	inline const RECT* GetShapeAddress() { return &this->shape; }

	GameObject() = default;
	virtual ~GameObject() = default;
};

