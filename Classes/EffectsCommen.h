#pragma once
#include "cocos2d.h"

USING_NS_CC;
class EffectsCommen :public Sprite
{
public:

	Sprite* effects_main;
	ActionInterval* act_moveto;

	EffectsCommen(Point basepoint, char* imgurl, float actiontime, float maxnum, int showtype, int zOrder);
	~EffectsCommen(void);
	EffectsCommen(char* imgurl0, String* imgurl, int num1, String* imgurl2, int num2, String* imgurl3, int num3, Point newpoint);



	//ִ�е������
	FiniteTimeAction *actall;

	//�����ƶ���ɵĻص�
	void moveoverCallBack_setvisible(void);
};
