#ifndef __QuoteScene_SCENE_H__
#define __QuoteScene_SCENE_H__

#include "cocostudio\CocoStudio.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace ui;
#include "./EventProduce/EventProduce.h"

class QuoteScene : public cocos2d::Layer,public IEventListen
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(QuoteScene);

	void Option(Object* pSender,TouchEventType type);

	virtual void onEnterTransitionDidFinish();

public:
	virtual void OnEvent(IEvent*pEvent);
	void SubDefaultIns();
private:
	Node *m_csbNode;
	Button * m_pBtnExit;
	Button * m_pBtnSub;
	TextField * m_pTextFieldIns;
	ListView * m_pListView;
};

#endif // __QuoteScene_SCENE_H__
