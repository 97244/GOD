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

	//�������
	MainRoledata role_player;

	/**
	��һ�������б�
	**/
	//̫���Ͼ�
	MainRoledata role_taishanglaojun;
	//̫������
	MainRoledata role_taiyizhengren;
	//��Ŵ���
	MainRoledata role_chijiaodaxian;
	//�������
	MainRoledata role_qingxuzhenjun;
	//����
	MainRoledata role_mengpo;

	/***************
	**�����б�
	***************/
	//��Ѫ����
	MainRoledata monster_xixuebianfu;
	//�־�ħ
	MainRoledata monster_kongjumo;
	//�����ʥ
	MainRoledata monster_qitiandasheng;
};

