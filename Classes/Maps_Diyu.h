#pragma once
#include "cocos2d.h"
#include "FDPixelSprite.h"
#include "SpiritsPlayer.h"

USING_NS_CC;

class Maps_Diyu :public cocos2d::CCSprite
{
public:
	Maps_Diyu(CCLayer* layer, CCString mapsurl, CCString mapsurl_1, int zOrder, CCPoint cp);
	~Maps_Diyu(void);
	CCSprite* nowmap;
	CCSprite* nowmap_zhezhao;
	//基本数据
	float lastmove_x, lastmove_y;
	bool moveMapto(CCPoint cp, FDPixelSprite* mainmap_Touch);
	bool touch_select(CCPoint cp);
	CCActionInterval* act_moveto_maps;
	CCActionInterval* act_moveto_maps_touch;
	CCActionInterval* act_moveto_maps_zhezhao;


	void makemonster(int makenum, int monsteridtags, CCPoint randomrange, MainRoledata monster_model, int yinzihigth, CCPoint fristpoint);

	void makemonsterAttack(float times);
	void attact_todo(int monsternum, int monsteridtags, MainRoledata monster_model, int reatR, int attck_reatR, CCPoint playerpoint, CCPoint randomrange, CCPoint fristpoint);
	void moveoverCallBack(CCObject* monster_model);
	//CCAnimation* getNowAnt(MainRoledata roledata);
	//CCAnimate* updateNowAnt(MainRoledata roledata);
	//void moveTomap_dir(CCPoint newpoint,CCSprite* monsters,MainRoledata roledata);
	//根据点击坐标获得人物的朝向
	//Commen_Direction getNowPointDir(CCPoint newpoint,CCSprite* monsters,bool dirflag);

	void makeroleAttack(float times);


private:
	SpiritsPlayer* role_main;
	CCAnimate* playdonghua;
	CCPoint nowattckpoint;
};