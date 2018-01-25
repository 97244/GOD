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

	//ִ�е������
	CCFiniteTimeAction *actall;

	//�����ƶ���ɵĻص�
	void moveoverCallBack_setvisible(void);
	void todoaction(float tims);
};
