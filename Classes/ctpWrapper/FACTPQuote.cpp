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

void FAQuote::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	EventCTPErr * pEvent = new EventCTPErr(EVENT_CTP_ERR);
	EVENT_PRODUCE->FireEvent(pEvent);
}

void FAQuote::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (pRspInfo && pRspInfo->ErrorID == 0)
	{

	}
}

void FAQuote::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	EventQuoteData * pEvent = new EventQuoteData(EVENT_CTP_QUOTE_DATA);
	EVENT_PRODUCE->FireEvent(pEvent);
}