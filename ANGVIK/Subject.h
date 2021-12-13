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

	//int GetObserverCount() { return mVecObserver.size(); }

	//void Notify(GameEntity* obj, SubjectTag subjectTag, EventTag eventTag);
	void Notify(Subject* subject, MonsterType monsterType, SubjectTag subjectTag, EventTag eventTag);

};

