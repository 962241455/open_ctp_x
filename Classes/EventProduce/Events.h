#pragma once

#include "../ctp/ThostFtdcMdApi.h"
#include "../ctp/ThostFtdcUserApiStruct.h"
#include "../ctp/ThostFtdcTraderApi.h"
#include "../ctp/ThostFtdcUserApiDataType.h"

enum enmEvent
{
	EVENT_BEGIN = 0,

	EVENT_CFG_UNKNOW,
	/*test*/
	EVENT_CFG_TEST_1,
	EVENT_CFG_TEST_2,
	EVENT_CFG_TEST_3,
	EVENT_CFG_TEST_4,
	EVENT_CFG_TEST_5,

	/*common*/
	EVENT_CFG_LOAD_ERR,
	EVENT_CFG_LOAD_ERR_FORMAT,
	EVENT_CFG_LOAD_ERR_NODE,

	EVENT_SO_LOAD_ERR,

	/*ctp 事件*/
	EVENT_CTP_CREATE_ERR,		
	EVENT_CTP_EXIST,		//已经创建
	EVENT_CTP_CONNECTED,
	EVENT_CTP_DISCONNECTED,

	EVENT_CTP_ERR,
	EVENT_CTP_QUOTE_DATA,

	EVENT_END,
};

class IEvent
{
public:
	IEvent() :m_id(EVENT_BEGIN){}
	IEvent(enmEvent id)
		:m_id(id){}
	~IEvent(){}
public:
	enmEvent m_id;
};

/************************************************************************/
/*	Event实例                                                           */
/************************************************************************/

class EventSo :public IEvent
{
public:
	EventSo(enmEvent id)
	{
		m_id = id;
		errCode[0] = 0;
	}
public:
	char errCode[128];
};


class EventCfgPath :public IEvent
{
public:
	EventCfgPath(enmEvent id)
	{
		m_id = id;
		errCode[0] = 0;
	}
public:
	char errCode[128];
};


class EventCTPErr:public IEvent
{
public:
	EventCTPErr(enmEvent id)
	{
		m_id = id;
		errCode[0] = 0;
	}
public:
	char errCode[128];
};

class EventQuoteData :public IEvent
{
public:
	EventQuoteData(enmEvent id)
	{
		m_id = id;
		memset(&data, 0, sizeof(data));
	}
	CThostFtdcDepthMarketDataField data;
};