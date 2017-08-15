#include "FACTPWrapper.h"
#include "../EventProduce/EventProduce.h"

#define FA_QUOTE_FLOW_FOLDER	FileUtils::getInstance()->getWritablePath().c_str()

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void *_CTPHandle  = 0;
#endif

FACTPWrapper::FACTPWrapper()
:m_svr(SVR_DX)
, m_pQuote(0)
, m_pQuoteAPI(0)
{
	m_pQuote = new FAQuote();	
}


FACTPWrapper::~FACTPWrapper()
{
}

void FACTPWrapper::ReleaseQuote()
{
	if (m_pQuoteAPI)
	{
		m_pQuoteAPI->Release();
	}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	dlclose(_CTPHandle);
#endif
}

void FACTPWrapper::CreateQuote()
{
	if (false == CTP_CFG->Load())
	{
		return;
	}

	if (false == CTP_CFG->LoadIns())
	{
		return;
	}
	
	if (m_pQuoteAPI)
	{
		IEvent * pEvent = new IEvent(EVENT_CTP_EXIST);
		EVENT_PRODUCE->FireEvent(pEvent);
		return;
	}


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	
	m_pQuoteAPI = CThostFtdcMdApi::CreateFtdcMdApi(FA_QUOTE_FLOW_FOLDER);

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

	_CTPHandle = dlopen(CTP_QUOTE_SO, RTLD_LAZY);
	if (!_CTPHandle)
	{
		EventSo * pEvent = new EventSo(EVENT_SO_LOAD_ERR);
		sprintf(pEvent->errCode,"-1-%s",dlerror());
		EVENT_PRODUCE->FireEvent(pEvent);
		//exit(0);
		return;
	}

	CTP_CREATE_0 CreateFtdcMdApi = (CTP_CREATE_0)dlsym(_CTPHandle, _CreateFtdcMdApi_4);
	if (!CreateFtdcMdApi)
	{
		EventSo * pEvent = new EventSo(EVENT_SO_LOAD_ERR);
		sprintf(pEvent->errCode,"-2-%s",dlerror());
		EVENT_PRODUCE->FireEvent(pEvent);
		//exit(0);
		return;
	}

	m_pQuoteAPI = CreateFtdcMdApi(FA_QUOTE_FLOW_FOLDER, false, false);	//必须可写目录

#else
	IEvent * pEvent = new IEvent(EVENT_CFG_UNKNOW);
	EVENT_PRODUCE->FireEvent(pEvent);
	return;
#endif

	if (!m_pQuoteAPI)
	{
		IEvent * pEvent = new IEvent(EVENT_CTP_CREATE_ERR);
		EVENT_PRODUCE->FireEvent(pEvent);
		return;
	}

	m_pQuoteAPI->RegisterSpi(m_pQuote);
	m_pQuoteAPI->RegisterFront(GetQuoteFront(m_svr));
	m_pQuoteAPI->Init();
	//m_pQuoteAPI->Join();
	//退出释放
	//dlclose(_CTPHandle);
}

char * FACTPWrapper::GetQuoteFront(enmServer svr)
{
	char * address = CTP_CFG->GetSvr(svr)->szQuote;
	//FAFILE->Log(address);
	return address;
}

void FACTPWrapper::Sub(const char *szIns)
{
	if (strlen(szIns) < 1)
	{
		return;
	}

	char *Ins[1];
	Ins[0] = new char[33];
	sprintf(Ins[0],"%s",szIns);
	m_pQuoteAPI->SubscribeMarketData(Ins, 1);
	SAFE_DEL(Ins[0]);
}

void FACTPWrapper::Sub(char **szIns, int nCount)
{
	m_pQuoteAPI->SubscribeMarketData(szIns, nCount);
}