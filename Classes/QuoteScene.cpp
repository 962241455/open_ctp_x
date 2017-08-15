#include "QuoteScene.h"
USING_NS_CC;

#include "./ctpWrapper/FACTPWrapper.h"

using namespace cocostudio::timeline;

Scene* QuoteScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = QuoteScene::create();

    // add layer as a child to scene
    scene->addChild(layer);
	
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool QuoteScene::init()
{    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
		
	return true;
}

void QuoteScene::onEnterTransitionDidFinish()
{
	EVENT_PRODUCE->RegListen(this);

	m_csbNode = CSLoader::createNode("QuoteScene.csb");

	Layout * pLayoutTop = dynamic_cast<Layout*>(m_csbNode->getChildByName("Panel_Top"));
	m_pBtnExit = dynamic_cast<Button*>(pLayoutTop->getChildByName("Button_Exit"));
	m_pBtnExit->addTouchEventListener(this, toucheventselector(QuoteScene::Option));
	m_pBtnSub = dynamic_cast<Button*>(m_csbNode->getChildByName("Button_Sub"));
	m_pBtnSub->addTouchEventListener(this, toucheventselector(QuoteScene::Option));
	m_pTextFieldIns = dynamic_cast<TextField*>(m_csbNode->getChildByName("TextField_Ins"));
	//ListView_Quote
	m_pListView = dynamic_cast<ListView*>(m_csbNode->getChildByName("ListView_Quote"));
	//Init ListView

	addChild(m_csbNode);

	//自动订阅配置合约
	SubDefaultIns();
}

void QuoteScene::Option(Object* pSender,TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
	{
		if (pSender == m_pBtnExit)
		{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			MessageBox("you are in win32 window ,please use [x] to exit", "Alert");
			return;
#endif
			Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			exit(1);
#endif
		}
		else if (pSender == m_pBtnSub)
		{
			CTP_WRAP->Sub(m_pTextFieldIns->getString().c_str());
		}
	}
		break;
	default:
		break;
	}

}

void QuoteScene::OnEvent(IEvent*pEvent)
{
	switch (pEvent->m_id)
	{
		/* CTP */
	case EVENT_CTP_QUOTE_DATA:
	{
		EventQuoteData* pSo = (EventQuoteData*)pEvent;
		
	}
		break;
	case EVENT_CTP_ERR:
	{
		EventCTPErr* pSo = (EventCTPErr*)pEvent;
	}
		break;
	default:
		break;
	}
}

void QuoteScene::SubDefaultIns()
{
	char *ins[128] = {0};
	int count = 0;
	CTP_CFG->GetIns(ins, count);
	CTP_WRAP->Sub(ins, count);
}