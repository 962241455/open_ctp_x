#include "LoginScene.h"
USING_NS_CC;

#include "./ctpWrapper/FACTPWrapper.h"
#include "QuoteScene.h"

using namespace cocostudio::timeline;

Scene* LoginScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LoginScene::create();

    // add layer as a child to scene
    scene->addChild(layer);
	
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LoginScene::init()
{    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	
	EVENT_PRODUCE->RegListen(this);
    
	m_csbNode = CSLoader::createNode("LoginScene.csb");

	addChild(m_csbNode);
	
	Button * pBtnLogin = dynamic_cast<Button*>(m_csbNode->getChildByName("Button_Login"));
	pBtnLogin->addTouchEventListener(this, toucheventselector(LoginScene::Option));

	return true;
}

void LoginScene::Option(Object* pSender,TouchEventType type)
{
	//Text *pTxt = dynamic_cast<Text*>(m_csbNode->getChildByName("Text_CTP_STATUS_Value"));
	//pTxt->setText("btn click!");

	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		//m_pTxtCTPStatusValue->setText("ctp ctp ctp ctp ctp ctp ctp ctp ctp !");
		//pTxt->setText("ctp create ing...!");
		CTP_WRAP->CreateQuote();
		CTP_WRAP->CreateTrade();
		break;
	default:
		break;
	}

}

void LoginScene::OnEvent(IEvent*pEvent)
{
	switch (pEvent->m_id)
	{
		/* TEST */
	case EVENT_CFG_TEST_1:
	{
						   Text *pTxt = dynamic_cast<Text*>(m_csbNode->getChildByName("Text_CTP_STATUS_Value"));
						   pTxt->setText("[Test] info-1-!");

	}
		break;
	case EVENT_CFG_TEST_2:
	{
							 Text *pTxt = dynamic_cast<Text*>(m_csbNode->getChildByName("Text_CTP_STATUS_Value"));
							 pTxt->setText("[Test] info-2-!");

	}
		break;
	case EVENT_CFG_TEST_3:
	{
							 Text *pTxt = dynamic_cast<Text*>(m_csbNode->getChildByName("Text_CTP_STATUS_Value"));
							 pTxt->setText("[Test] info-3-!");

	}
		break;
	case EVENT_CFG_TEST_4:
	{
							 Text *pTxt = dynamic_cast<Text*>(m_csbNode->getChildByName("Text_CTP_STATUS_Value"));
							 pTxt->setText("[Test] info-4-!");

	}
		break;
	case EVENT_CFG_TEST_5:
	{
							 Text *pTxt = dynamic_cast<Text*>(m_csbNode->getChildByName("Text_CTP_STATUS_Value"));
							 pTxt->setText("[Test] info-5-!");

	}
		break;
		/*SO */
	case EVENT_SO_LOAD_ERR:
	{

							  EventSo * pSo = (EventSo*)pEvent;
							  Text *pTxt = dynamic_cast<Text*>(m_csbNode->getChildByName("Text_CTP_STATUS_Value"));
							  std::string sz;
							  sz.append("so err:");
							  sz.append(pSo->errCode);
							  pTxt->setText(sz.c_str());

	}
		break;

		/* CFG */
	case EVENT_CFG_LOAD_ERR:
	{
							   EventCfgPath * pSo = (EventCfgPath*)pEvent;
							   Text *pTxt = dynamic_cast<Text*>(m_csbNode->getChildByName("Text_CTP_STATUS_Value"));
							   std::string sz;
							   sz.append("cfg err:");
							   sz.append(pSo->errCode);
							   pTxt->setText(sz.c_str());

	}
		break;

		/* CTP */
	case EVENT_CTP_CREATE_ERR:
	{
								 //connected
								 Text *pTxt = dynamic_cast<Text*>(m_csbNode->getChildByName("Text_CTP_STATUS_Value"));
								 pTxt->setString("err:ctp create err!");

	}
		break;
	case EVENT_CTP_CONNECTED:
	{
								//connected
								Text *pTxt = dynamic_cast<Text*>(m_csbNode->getChildByName("Text_CTP_STATUS_Value"));
								pTxt->setString("ctp server connectded !");

								//sceneÇÐ»»
								//QuoteScene
								auto quoteScene = QuoteScene::createScene();
								Director::getInstance()->purgeCachedData();
								Director::getInstance()->pushScene(quoteScene);
	}
		break;
	case EVENT_CTP_DISCONNECTED:
	{
								   //disconnected
								   Text *pTxt = dynamic_cast<Text*>(m_csbNode->getChildByName("Text_CTP_STATUS_Value"));
								   pTxt->setText("err:ctp server disconnectded !");
	}
		break;
	case EVENT_CTP_EXIST:
	{
								//exist
								Text *pTxt = dynamic_cast<Text*>(m_csbNode->getChildByName("Text_CTP_STATUS_Value"));
								pTxt->setText("warn:ctp already exist!");
	}
		break;
	default:
		break;
	}
}