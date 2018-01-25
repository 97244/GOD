#pragma once
#include "cocos2d.h"
USING_NS_CC;

class FDPixelSprite : public Sprite {
public:
	FDPixelSprite();
	virtual ~FDPixelSprite();

	void onEnter();
	void onExit();
	void setimg(String Url);

	FDPixelSprite* create(String Url);
	Image* img;
	EventListenerTouchOneByOne* m_listener;
	Rect atlasRect();
	bool isContainTouchLocation(Touch *pTouch);

	bool onTouchBegan(/*String thismapurl,*/ Touch *pTouch, Event *pEvent);


	//CC_SYNTHESIZE(const char*, m_pName, Name);
};
