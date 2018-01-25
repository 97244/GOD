#pragma once
#include "cocos2d.h"
#include "Commen_ActionToDo.h"
#include "Commen_Direction.h"
USING_NS_CC;

class MainRoledata
{
public:

	//人物的TAG
	int tags;
	//人物姓名
	String* spiritname;
	//人物初始坐标
	Point nowpoint;
	//人物默认像素图
	String* spiritUrl;
	//人物站立像素图路径
	String* spiritUrl_zhan;
	//人物跑动像素图路径
	String* spiritUrl_pao;
	//人物攻击像素图路径
	String* spiritUrl_attack;
	//人物施法像素图路径/增加人物BUF
	String* spiritUrl_magic;
	//人物站立最大帧
	int maxcut_zhan;
	//人物跑动最大帧
	int maxcut_pao;
	//人物战斗最大帧
	int maxcut_attack;
	//人物施法最大帧
	int maxcut_magic;
	//人物当前动作
	Commen_ActionToDo acttodo;
	//人物当前朝向
	Commen_Direction dir;
	//动画时间
	float actiontime;

};