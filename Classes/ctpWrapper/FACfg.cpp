#include "FACTPWrapper.h"
#include "tinyxml2/tinyxml2.h"
#include "../EventProduce/EventProduce.h"

#define CTP_XML	("CTPServer.xml")
#define CTP_INS_XML	("InsSub.xml")

#ifndef WIN32
#define sprintf_s  snprintf
#endif

bool FACfg::Load()
{	
	if (!CCFileUtils::getInstance()->isFileExist(CTP_XML))
	{
		std::vector<std::string> searchPaths;
		searchPaths.push_back("Resource");
		searchPaths.push_back("res");
		CCFileUtils::getInstance()->setSearchPaths(searchPaths);
	}
	auto xml = new tinyxml2::XMLDocument();
	std::string buf = FAFILE->GetResStrBuf(CTP_XML);
	//FAFILE->Log(buf.c_str());
	tinyxml2::XMLError errCode = xml->Parse(buf.c_str());
	if (0 != errCode)
	{
		EventCfgPath * pEvent = new EventCfgPath(EVENT_CFG_LOAD_ERR);
		sprintf(pEvent->errCode, "path err:%d,%s", errCode, buf.c_str());
		EVENT_PRODUCE->FireEvent(pEvent);
		return false;
	}

	auto rootNode = xml->RootElement();
	if (!rootNode)
	{
		IEvent * pEvent = new IEvent(EVENT_CFG_LOAD_ERR_NODE);
		EVENT_PRODUCE->FireEvent(pEvent);

		log("[Err] ctp_cfg_xml: file load err-1-");
		return false;
	}

	auto svr = rootNode->FirstChildElement("Server");

	if (!svr)
	{
		IEvent * pEvent = new IEvent(EVENT_CFG_LOAD_ERR_NODE);
		EVENT_PRODUCE->FireEvent(pEvent);
		log("[Err] ctp_cfg_xml: file load err-2-");
		return false;
	}
	
	int index = 0;

	while (svr)
	{		
		sprintf(m_stSvrs[index].szQuote, "%s", svr->Attribute("Quote"));
		sprintf(m_stSvrs[index].szTrade, "%s", svr->Attribute("Trade"));
		sprintf(m_stSvrs[index].szBrokerID, "%s", svr->Attribute("BrokerID"));
		sprintf(m_stSvrs[index].szAccount, "%s", svr->Attribute("AccountID"));
		sprintf(m_stSvrs[index].szPwd, "%s", svr->Attribute("Password"));
		
		svr = svr->NextSiblingElement();

		index++;

		if (index >= SVR_MAX)
			break;
	}

	return true;
}

bool FACfg::LoadIns()
{
	if (!CCFileUtils::getInstance()->isFileExist(CTP_INS_XML))
	{
		std::vector<std::string> searchPaths;
		searchPaths.push_back("Resource");
		searchPaths.push_back("res");
		CCFileUtils::getInstance()->setSearchPaths(searchPaths);
	}
	auto xml = new tinyxml2::XMLDocument();
	std::string buf = FAFILE->GetResStrBuf(CTP_INS_XML);
	//FAFILE->Log(buf.c_str());
	tinyxml2::XMLError errCode = xml->Parse(buf.c_str());
	if (0 != errCode)
	{
		EventCfgPath * pEvent = new EventCfgPath(EVENT_CFG_LOAD_ERR);
		sprintf(pEvent->errCode, "path err:%d,%s", errCode, buf.c_str());
		EVENT_PRODUCE->FireEvent(pEvent);
		return false;
	}

	auto rootNode = xml->RootElement();
	if (!rootNode)
	{
		IEvent * pEvent = new IEvent(EVENT_CFG_LOAD_ERR_NODE);
		EVENT_PRODUCE->FireEvent(pEvent);

		log("[Err] ctp_cfg_xml: file load err-1-");
		return false;
	}

	auto svr = rootNode->FirstChildElement("Ins");

	if (!svr)
	{
		IEvent * pEvent = new IEvent(EVENT_CFG_LOAD_ERR_NODE);
		EVENT_PRODUCE->FireEvent(pEvent);
		log("[Err] ctp_cfg_xml: file load err-2-");
		return false;
	}

	while (svr)
	{
		tagIns ins;
		sprintf(ins.szIns, "%s", svr->Attribute("key"));
		m_vIns.push_back(ins);
		svr = svr->NextSiblingElement();
	}

	return true;
}

void FACfg::GetIns(char *szIns[], int &nCount)
{
	nCount = 0;

	for (int i = 0; i < m_vIns.size();i++)
	{
		szIns[nCount++] = m_vIns[i].szIns;
	}
}
