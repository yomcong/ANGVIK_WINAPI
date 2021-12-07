#pragma once

class GameEntity;
class Observer
{
public:
	virtual ~Observer() = default;
	virtual void OnNotify(GameEntity* obj, SubjectTag subjectTag, EventTag eventTag) = 0;
};
