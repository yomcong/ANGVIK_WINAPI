#pragma once

// 앞으로 만들어질 게임의 가장 기본적인 구조가 되는 클래스
// 초기화 (메모리 할당), 1회만 진행
// 업데이트, 지속적으로 프레임마다 진행
// 출력, 지속적으로 프레임마다 진행
// 메모리 해제, 1회만 진행

/*
	상속 : 중복되는 코드를 줄일 수 있다.
	추상화 : 현실세계에 있는 객체를 게임객체에 필요한 데이터만 추려낸 것.

	클래스 추상화 : 클래스 간 공통되는 내용들을 추려낸 것.
*/

#include "GameEntity.h"

class Image;
class GameObject : public GameEntity
{
protected:
	POINTFLOAT pos = {};
	RECT shape = {};
	float moveSpeed = 0.0f;
	int bodySize = 0;

	Image* img = nullptr;

public:
	inline void SetPos(POINTFLOAT pos) { this->pos = pos;/* POINTFLOAT{pos.x + CameraManager::GetSingleton()->GetPos().x, pos.y + CameraManager::GetSingleton()->GetPos().y};*/ }
	inline void SetMoveSpeed(float speed) { this->moveSpeed = speed; }

	inline const POINTFLOAT GetPos() { return this->pos; }
	inline const RECT GetShape() { return this->shape; }
	inline const int GetBodySize() { return this->bodySize; }


	inline const RECT* GetShapeAddress() { return &this->shape; }

	GameObject() = default;
	virtual ~GameObject() = default;
};

