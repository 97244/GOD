#pragma once
#include "cocos2d.h"
USING_NS_CC;
class SelectRole : public Layer
{
public:
	SelectRole(void);
	~SelectRole(void);
	virtual bool init();
	static Scene*createScene();
	CREATE_FUNC(SelectRole);
public:
	Rect rect(Sprite* tack);
	bool isTouchInside_nan(Point thisPos, Sprite* tack);
	bool isTouchInside_nv(Point thisPos, Sprite* tack);
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);

};

