#pragma once
#include "cocos2d.h"  
#include "MainRoledata.h"

USING_NS_CC;



class GetNPCData
{
public:
	GetNPCData();
	~GetNPCData(void);
	void GetNPCchapter1();
	void GetMonsterchapter1();

	//玩家主角
	MainRoledata role_player;

	/**
	第一章人物列表
	**/
	//太上老君
	MainRoledata role_taishanglaojun;
	//太乙真人
	MainRoledata role_taiyizhengren;
	//赤脚大仙
	MainRoledata role_chijiaodaxian;
	//清虚真君
	MainRoledata role_qingxuzhenjun;
	//孟婆
	MainRoledata role_mengpo;

	/***************
	**怪物列表
	***************/
	//吸血蝙蝠
	MainRoledata monster_xixuebianfu;
	//恐惧魔
	MainRoledata monster_kongjumo;
	//齐天大圣
	MainRoledata monster_qitiandasheng;
};

