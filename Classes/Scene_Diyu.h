#pragma once
#include "cocos2d.h"
#include "Maps_Diyu.h"
#include "BaseUI.h"
#include "FDPixelSprite.h"
USING_NS_CC;
class Scene_Diyu : public CCLayer
{
public:
	Scene_Diyu(void);
	~Scene_Diyu(void);
	
	static Scene*createScene();
	virtual bool init();
	CREATE_FUNC(Scene_Diyu);
	
	Maps_Diyu* mainmap;
	FDPixelSprite* mainmap_Touch;
	BaseUI* baseui;

	void nextCallback(CCObject* pSender);
	virtual bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

};