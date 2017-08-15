#include "FACTPWrapper.h"
#include "../EventProduce/EventProduce.h"


void FAQuote::OnFrontConnected()
{
	IEvent * pEvent = new IEvent(EVENT_CTP_CONNECTED);
	EVENT_PRODUCE->FireEvent(pEvent);
}

void FAQuote::OnFrontDisconnected(int nReason)
{
	IEvent * pEvent = new IEvent(EVENT_CTP_DISCONNECTED);
	EVENT_PRODUCE->FireEvent(pEvent);
}