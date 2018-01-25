#pragma once
#include "cocos2d.h"
#include "MainRoledata.h"
USING_NS_CC;
class SkillEffects :public cocos2d::CCSprite
{
public:
	SkillEffects(CCPoint basepoint, MainRoledata model, float actiontime, float maxnum, int showtype, int skillnumber);

	~SkillEffects(void);
	CCSprite* effects_main;
	CCActionInterval* act_moveto;

	//执行的最后动作
	CCFiniteTimeAction *actall;

	//人物移动完成的回调
	void moveoverCallBack_setvisible(void);
	void todoaction(float tims);
};
