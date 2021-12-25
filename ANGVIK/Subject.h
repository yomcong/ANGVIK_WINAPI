#pragma once

class Observer;
class Subject
{
private:
	vector<Observer*> vecObservers;
public:
	virtual ~Subject() = default;

	void AddObserver(Observer* obs);
	void RemoveObserver(Observer* obs);

	Subject* GetSubject() { return this; }

	void Notify(Subject* subject, SubjectTag subjectTag, EventTag eventTag, MonsterType monsterType = MonsterType::IDLE);
};

