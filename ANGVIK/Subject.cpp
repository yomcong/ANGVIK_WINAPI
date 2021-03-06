//#include "stdafx.h"
#include "Config.h"
#include "Subject.h"
#include "Observer.h"
#include "GameEntity.h"

void Subject::AddObserver(Observer* obs)
{
	vector<Observer*>::iterator iter = find(vecObservers.begin(), vecObservers.end(), obs);

	if (iter == vecObservers.end())
	{
		vecObservers.push_back(obs);
	}
}

void Subject::RemoveObserver(Observer* obs)
{
	vector<Observer*>::iterator iter = find(vecObservers.begin(), vecObservers.end(), obs);

	if (false == (iter == vecObservers.end()))
	{
		vecObservers.erase(iter);
	}

}

void Subject::Notify(Subject* subject, SubjectTag subjectTag, EventTag eventTag, MonsterType monsterType)
{
	for (int i = 0; i < vecObservers.size(); ++i)
	{
		vecObservers[i]->OnNotify(subject, monsterType, subjectTag, eventTag);
	}
}
