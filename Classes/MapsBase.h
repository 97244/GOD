#pragma once
#include "cocos2d.h"
#include "FDPixelSprite.h"
#include "SpiritsPlayer.h"
#include "GetNPCData.h"
#include "EffectsCommen.h"
USING_NS_CC;

class MapsBase : public Sprite
{
public:
	MapsBase(Layer* layer, String mapsurl, int zOrder, Point cp);
	~MapsBase();

	CCSprite* nowmap;
	bool moveMapto(Point cp, FDPixelSprite* mainmap_Touch);
	
	//��ͼNPC�б�
	SpiritsPlayer* npc_taiyizhengren;
	SpiritsPlayer* npc_taishanglaojun;
	SpiritsPlayer* npc_chijiaodaxian;
	SpiritsPlayer* npc_qingxunzhenjun;


	void playerstroy_part1_show(float times);
	void playerstroy_part1_show2(float times);

private:
	//��������
	float lastmove_x, lastmove_y;
	CCActionInterval* act_moveto_maps;
	CCActionInterval* act_moveto_maps_touch;
	CCFiniteTimeAction *actall;
	GetNPCData* basedatas;
	SpiritsPlayer* role_main;

	//�ƶ�ʱ��
	float movetime;

	//��Ч
	EffectsCommen* eff1;//��̨��Ч
	EffectsCommen* eff2;//��̨��Ч
	EffectsCommen* eff_yun1;//����Ч��
	EffectsCommen* eff_yun2;
	EffectsCommen* eff_yun3;
	EffectsCommen* eff_yun4;

};