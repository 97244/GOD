#pragma once
#include "cocos2d.h"
USING_NS_CC;
#include "MainRoledata.h"
#include "PublicShowUI.h"
class SpiritsPlayer :public Sprite
{
public:
	Sprite *npc;
	Sprite *yinzi;
	Sprite *sp_liaotianbd;

	PublicShowUI *p_ui_name;

	Array *stringArray;
	Animate* playdonghua;
	Animate* playdonghua2;
	Commen_Direction move_dir;

	bool endflag;
	bool endflag2;
	bool thiszhujiao_flag;

	void Spirits_talkabout_hid();

	SpiritsPlayer(MainRoledata roledata, int zOrder, bool zhujiaoflag);
	~SpiritsPlayer(void);

	static Animation* getNowAnt(MainRoledata roledata);
	Animate* updateNowAnt(MainRoledata roledata);
	static Animate* updateNowAnt_change(MainRoledata roledata, int RepeatNum);
	void updateNpcPoint(Point newpoint);
	void moveTomap_dir(Point newpoint);
	static void attckTomap_dir(Point newpoint, Sprite* npc, MainRoledata role_player);
	void moveTomap_move(int uestime, Point newpoint, bool npcflag);
	//人物移动完成的回调
	void moveoverCallBack(void);
	//普通NPC移动完成的回调
	void moveoverCallBackforNpc(void);
	//根据点击坐标获得人物的朝向
	Commen_Direction getNowPointDir(Point newpoint);
	static Commen_Direction getNowPointDir_change(Point newpoint, Sprite* npc);
	// 触摸点是否在精灵上
	bool isTouchInside(Point thisPos);
	//移动方式
	void movemethod(int uestime, Point newpoint);

private:
	//角色基本数据
	MainRoledata thisroledata;
	FiniteTimeAction *actall;
	ActionInterval* act_moveto_zi;
	ActionInterval* act_moveto_npc;
	ActionInterval* act_moveto_yinzi;
	ActionInterval* act_moveto_eff;
	ActionInterval* act_moveto_eff_zhujiao;
	FiniteTimeAction *actbackfun;
	int flag;

private:
	Rect rect();

};