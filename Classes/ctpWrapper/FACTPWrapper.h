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
	//��̬����so�ӿ� nm -D libthostmduserapi.so | grep Create
#define CTP_QUOTE_SO		("/data/data/com.openctp.fa/lib/libthostmduserapi.so")
#define CTP_TRADE_SO		("/data/data/com.openctp.fa/lib/libthosttraderapi.so")

#define _CreateFtdcMdApi_4	("_ZN15CThostFtdcMdApi15CreateFtdcMdApiEPKcbb")


//�ӿڶ���
typedef CThostFtdcMdApi* (*CTP_CREATE_0)(const char *, const bool, const bool);
typedef CThostFtdcMdApi* (*CTP_CREATE_1)(const char *, const bool);
typedef CThostFtdcMdApi* (*CTP_CREATE_2)(const char *);
typedef CThostFtdcMdApi* (*CTP_CREATE_3)();

#endif


#define CFG_STR_LEN	33

enum enmServer
{
	SVR_DX = 0,			//����
	SVR_LT = 1,			//��ͨ
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
	///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
	virtual void OnFrontConnected();

	///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
	///@param nReason ����ԭ��
	///        0x1001 �����ʧ��
	///        0x1002 ����дʧ��
	///        0x2001 ����������ʱ
	///        0x2002 ��������ʧ��
	///        0x2003 �յ�������
	virtual void OnFrontDisconnected(int nReason);

	///������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
	///@param nTimeLapse �����ϴν��ձ��ĵ�ʱ��
	virtual void OnHeartBeatWarning(int nTimeLapse){};


	///��¼������Ӧ
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�ǳ�������Ӧ
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///����Ӧ��
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��������Ӧ��
	virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///ȡ����������Ӧ��
	virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///����ѯ��Ӧ��
	virtual void OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///ȡ������ѯ��Ӧ��
	virtual void OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�������֪ͨ
	virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) {};

	///ѯ��֪ͨ
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
	//��������ӿ�
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