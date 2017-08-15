#pragma once

#include "cocos2d.h"
#include "../ctp/ThostFtdcMdApi.h"
#include "../ctp/ThostFtdcUserApiStruct.h"
#include "../ctp/ThostFtdcTraderApi.h"
#include "../ctp/ThostFtdcUserApiDataType.h"
#include "single.h"
#include <vector>
using namespace std;

USING_NS_CC;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#if defined x64
#pragma comment(lib,"../../proj.win32/ctp_win64/thostmduserapi.lib")
#pragma comment(lib,"../../proj.win32/ctp_win64/thosttraderapi.lib")
#else
#pragma comment(lib,"../../proj.win32/ctp_win32/thostmduserapi.lib")
#pragma comment(lib,"../../proj.win32/ctp_win32/thosttraderapi.lib")
#endif
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <dlfcn.h>
	//动态加载so接口 nm -D libthostmduserapi.so | grep Create
#define CTP_QUOTE_SO		("/data/data/com.openctp.fa/lib/libthostmduserapi.so")
#define CTP_TRADE_SO		("/data/data/com.openctp.fa/lib/libthosttraderapi.so")

#define _CreateFtdcMdApi_4	("_ZN15CThostFtdcMdApi15CreateFtdcMdApiEPKcbb")


//接口定义
typedef CThostFtdcMdApi* (*CTP_CREATE_0)(const char *, const bool, const bool);
typedef CThostFtdcMdApi* (*CTP_CREATE_1)(const char *, const bool);
typedef CThostFtdcMdApi* (*CTP_CREATE_2)(const char *);
typedef CThostFtdcMdApi* (*CTP_CREATE_3)();

#endif


#define CFG_STR_LEN	33

enum enmServer
{
	SVR_DX = 0,			//电信
	SVR_LT = 1,			//联通
	SVR_MAX,
};

class FACfg
{
public:
	struct tagServer
	{
		char szQuote[CFG_STR_LEN];
		char szTrade[CFG_STR_LEN];
		char szBrokerID[CFG_STR_LEN];
		char szAccount[CFG_STR_LEN];
		char szPwd[CFG_STR_LEN];
	};

	struct tagIns
	{
		char szIns[CFG_STR_LEN];
	};
	
public:
	FACfg(){ memset(m_stSvrs, 0, sizeof(m_stSvrs)); m_vIns.clear(); }
	bool Load();
	bool LoadIns();
	tagServer * GetSvr(enmServer svr) { return &m_stSvrs[svr]; }
	void GetIns(char *szIns[],int &nCount);
private:
	tagServer m_stSvrs[SVR_MAX];
	vector<tagIns> m_vIns;

};
#define CTP_CFG singleton_t<FACfg>::instance()	

class FAFile
{
public:
	std::string GetWirtePath();
	std::string GetResPath(char *fileName);
	std::string GetResStrBuf(char *fileName);
	std::string GetResStrBuf(char *fileName, int offset);
public:
	void Log(const char *szLog);
};
#define FAFILE singleton_t<FAFile>::instance()	

class FAQuote :public CThostFtdcMdSpi
{
public:
	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	virtual void OnFrontConnected();

	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	///@param nReason 错误原因
	///        0x1001 网络读失败
	///        0x1002 网络写失败
	///        0x2001 接收心跳超时
	///        0x2002 发送心跳失败
	///        0x2003 收到错误报文
	virtual void OnFrontDisconnected(int nReason);

	///心跳超时警告。当长时间未收到报文时，该方法被调用。
	///@param nTimeLapse 距离上次接收报文的时间
	virtual void OnHeartBeatWarning(int nTimeLapse){};


	///登录请求响应
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///登出请求响应
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///错误应答
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///订阅行情应答
	virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///取消订阅行情应答
	virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///订阅询价应答
	virtual void OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///取消订阅询价应答
	virtual void OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///深度行情通知
	virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) {};

	///询价通知
	virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp) {};
};


class FACTPWrapper
{
public:
	FACTPWrapper();
	~FACTPWrapper();

	/*
	Quote
	*/
public:
	//创建行情接口
	void CreateQuote();
	void ReleaseQuote();

	char * GetQuoteFront(enmServer svr);

	void Sub(const char *szIns);
	void Sub(char **szIns,int nCount);

	/*
	Trade
	*/
public:
	//Trade
	void CreateTrade(){}


private:
	FAQuote * m_pQuote;
	enmServer	m_svr;
	CThostFtdcMdApi * m_pQuoteAPI;
};


#define CTP_WRAP singleton_t<FACTPWrapper>::instance()	