#pragma once
#include "cocos2d.h"
#include "Commen_ActionToDo.h"
#include "Commen_Direction.h"
USING_NS_CC;

class MainRoledata
{
public:

	//�����TAG
	int tags;
	//��������
	String* spiritname;
	//�����ʼ����
	Point nowpoint;
	//����Ĭ������ͼ
	String* spiritUrl;
	//����վ������ͼ·��
	String* spiritUrl_zhan;
	//�����ܶ�����ͼ·��
	String* spiritUrl_pao;
	//���﹥������ͼ·��
	String* spiritUrl_attack;
	//����ʩ������ͼ·��/��������BUF
	String* spiritUrl_magic;
	//����վ�����֡
	int maxcut_zhan;
	//�����ܶ����֡
	int maxcut_pao;
	//����ս�����֡
	int maxcut_attack;
	//����ʩ�����֡
	int maxcut_magic;
	//���ﵱǰ����
	Commen_ActionToDo acttodo;
	//���ﵱǰ����
	Commen_Direction dir;
	//����ʱ��
	float actiontime;

};