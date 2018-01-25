#pragma once
#include "cocos2d.h"
USING_NS_CC;
class BaseUI :public cocos2d::CCSprite
{
public:
	BaseUI(CCLayer* layer);
	~BaseUI(void);
	CCSprite* ui_head;
	CCSprite* ui_head_xiaoxiao;
	CCSprite* ui_exp;
	CCSprite* ui_yaogan;
	CCSprite* ui_skillbar;
	CCSprite* ui_skill_skill0;
	CCSprite* ui_skill_skill1;
	CCSprite* ui_skill_skill2;
	CCSprite* ui_skill_skill3;
	CCRect rect_skill0(void);
	void isTouchInside(CCTouch *pTouch);
};