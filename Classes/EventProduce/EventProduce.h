#pragma once
#include "Events.h"
#include "../single.h"
#include <vector>
using namespace std;

#define SAFE_DEL(x) {if(x){delete x;x=0;}}

typedef vector<IEvent*> vE;
typedef vE::iterator vEIter;

class IEventListen
{
public:
	virtual void OnEvent(IEvent*pEvent) = 0;
};

typedef vector<IEventListen*> vEL;
typedef vEL::iterator vELIter;

class CEventProduce
{
public:
	CEventProduce(){}
	~CEventProduce(){}

public:
	void RegListen(IEventListen * pListen){ m_vel.push_back(pListen); }
	void UnRegListen(IEventListen * pListen){
		for (vELIter it = m_vel.begin(); it != m_vel.end();++it)
		{
			if (*it == pListen)
			{
				m_vel.erase(it);
				return;
			}
		}
	}

public:
	void FireEvent(IEvent*pEvent){		
		for (vELIter it = m_vel.begin(); it != m_vel.end(); ++it)
		{
			(*it)->OnEvent(pEvent);
		}
		SAFE_DEL(pEvent);
	}


private:
	vEL m_vel;
};

#define EVENT_PRODUCE singleton_t<CEventProduce>::instance()