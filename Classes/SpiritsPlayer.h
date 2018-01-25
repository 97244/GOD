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
	//�����ƶ���ɵĻص�
	void moveoverCallBack(void);
	//��ͨNPC�ƶ���ɵĻص�
	void moveoverCallBackforNpc(void);
	//���ݵ������������ĳ���
	Commen_Direction getNowPointDir(Point newpoint);
	static Commen_Direction getNowPointDir_change(Point newpoint, Sprite* npc);
	// �������Ƿ��ھ�����
	bool isTouchInside(Point thisPos);
	//�ƶ���ʽ
	void movemethod(int uestime, Point newpoint);

private:
	//��ɫ��������
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