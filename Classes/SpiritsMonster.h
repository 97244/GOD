#pragma once
#include "cocos2d.h"
#include "MainRoledata.h"
USING_NS_CC;
class SpiritsMonster :public cocos2d::CCSprite
{
public:

	CCSprite* monster;
	CCSprite* yinzi;
	CCSprite* bloodline;
	CCAnimate* playdonghua;
	SpiritsMonster(MainRoledata roledata, int zOrder, int yinzihigth);
	~SpiritsMonster(void);
	static CCAnimation* getNowAnt(MainRoledata roledata);
	static CCAnimate* updateNowAnt(MainRoledata roledata, int RepeatNum);
	//���ݵ������������ĳ���
	static Commen_Direction getNowPointDir(CCPoint newpoint, CCSprite* monsters, bool dirflag);
	//���ݵ�������þ���ĳ���
	//Commen_Direction getNowPointDir(CCPoint newpoint,CCSprite* monsters);
	static void moveTomap_dir(CCPoint newpoint, CCSprite* monsters, MainRoledata roledata);
	static void attackTomainRole_dir(CCPoint newpoint, CCSprite* monsters, MainRoledata roledata);
	// �������Ƿ��ھ�����
	static bool isTouchInside(CCPoint thisPos, CCSprite* monster);
	// ��ʾ�����˺���ֵ
	static void showattcknumber(int attcknum, CCSprite* monster);
	void ShowNumberCallBack_setvisible(CCObject* obj);
private:
	static CCRect rect(CCSprite* monster);
};

