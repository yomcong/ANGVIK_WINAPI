#pragma once

class Subject;
class GameEntity;
class Observer
{
public:
	virtual ~Observer() = default;
	//virtual void OnNotify2(GameEntity* obj, SubjectTag subjectTag, EventTag eventTag) = 0;
	virtual void OnNotify(Subject* subject, SubjectTag subjectTag, EventTag eventTag) = 0;

};
