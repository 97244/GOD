#include "SpiritsMonster.h"
#include "ImagePaths.h"
#include "FontChina.h"
#include "EffectsCommen.h"
#include "MakeNumbers.h"
SpiritsMonster::SpiritsMonster(MainRoledata roledata, int zOrder, int yinzihigth)
{
	//�ȳ�ʼ����������

	monster = SpiritsMonster::create(roledata.spiritUrl->getCString());
	if (monster == NULL)
	{
		log("ͼ��·����������·��");
		return;
	}
	//���ù����ʼλ�����꣨������ȡ���ڵ�ǰ���㣩
	monster->setPosition(roledata.nowpoint);
	//���ﶯ������
	playdonghua = SpiritsMonster::updateNowAnt(roledata, 0);
	monster->runAction(playdonghua);


	/**��ʼ��Ӹ�����**/
	//�������
	CCLabelTTF* label = CCLabelTTF::create(roledata.spiritname->getCString(), "΢���ź�", 12);
	label->setColor(Color3B::WHITE);
	//label->setDirty(true);
	label->setPosition(ccp(monster->getContentSize().width / 2, monster->getContentSize().height + 20));

	CCLabelTTF* labelback = CCLabelTTF::create(roledata.spiritname->getCString(), "΢���ź�", 12);
	labelback->setColor(Color3B::WHITE);
//	labelback->setDirty(true);
	labelback->setPosition(ccp(label->getContentSize().width / 2 + 1, label->getContentSize().height / 2 - 1));
	label->addChild(labelback, -1, 1002);

	//��ӹ���ͷ��Ѫ��
	bloodline = CCSprite::create(MONST_BLOOD_LINE);
	bloodline->setPosition(ccp(monster->getContentSize().width / 2, monster->getContentSize().height + 5));

	CCSprite* bloodlinehong = CCSprite::create(MONST_BLOOD_LINE_HONE);
	bloodlinehong->setScale(0.9f);
	bloodlinehong->setPosition(ccp(bloodline->getContentSize().width / 2 - (0.1f*bloodline->getContentSize().width / 2), bloodline->getContentSize().height / 2));
	bloodline->addChild(bloodlinehong, 1, 1);

	//��ӹ��������Ӱ
	yinzi = CCSprite::create(YINZI);
	if (yinzi == NULL)
	{
		log("ͼ��·����������·��");
		return;
	}
	yinzi->setPosition(ccp(monster->getContentSize().width / 2, yinzihigth));

	//NPC��Դ
	
	EffectsCommen* selectflag = new EffectsCommen(ccp(monster->getContentSize().width / 2, -2), npc_select_flag1, 2, 20, 0, 2);
	selectflag->effects_main->setVisible(false);
	monster->addChild(yinzi, -1, 110);
	monster->addChild(label, 2, 111);
	monster->addChild(bloodline, 3, 113);
	monster->addChild(selectflag->effects_main, 4, 114);
}

/*
�����˺����ֶ�����Ч
*/
void SpiritsMonster::showattcknumber(int attcknum, CCSprite* monster)
{
	if (attcknum > 0)
	{
		//������ֵת��Ϊ2�и�ʽ�ַ���string��CCString��
		char char_attckmun[100] = { 0 };
		sprintf(char_attckmun, "%d", attcknum, char_attckmun);
		//�����Ҫ��;������Ϊ�ַ���int֮����໥ת��
		CCString* numberstr = CCString::create(char_attckmun);
		//����˺���ֵ
		MakeNumbers* nowattcknumber = new MakeNumbers(attcknum);
		//�����ڹ���ͷ��һ����뵯���˺�
		nowattcknumber->numbers->setPosition(ccp(monster->getContentSize().width / 2, monster->getContentSize().height*1.5f));
		//���ö�������������
		ccBezierConfig bezier;
		bezier.controlPoint_1 = CCPointMake(50, monster->getContentSize().height*2.0f);
		bezier.controlPoint_2 = CCPointMake(monster->getContentSize().width / 2, monster->getContentSize().height);
		CCActionInterval* bezier_act = CCBezierTo::create(2.5f, bezier);
		//���ö��������Ŵ����С
		CCActionInterval* scale_act = CCScaleTo::create(2.0f, 1.5f);
		CCActionInterval* scale_actby = CCScaleBy::create(1.0f, 2.0f);
		//���ö����������루��ʼ��ʾ��������أ�
		CCActionInterval* fade_actby = CCFadeIn::create(2.0f);
		CCActionInterval* fade_actby2 = CCFadeOut::create(2.0f);
		//���ִ���Ƴ��ص��������������ڴ棬������ͷ�
		CCFiniteTimeAction *actbackfun = CCCallFuncO::create(monster, callfuncO_selector(SpiritsMonster::ShowNumberCallBack_setvisible), monster);
		nowattcknumber->numbers->runAction(CCSequence::create(scale_actby, scale_actby->reverse(), NULL));
		nowattcknumber->numbers->runAction(fade_actby2);
		for (int i = 0; i < numberstr->length(); i++)
		{
			CCActionInterval* fade_actby_back = fade_actby->reverse();
			nowattcknumber->numbers->getChildByTag(10 + i)->runAction(fade_actby_back);
		}
		nowattcknumber->numbers->runAction(CCSequence::create(bezier_act, actbackfun, NULL));
		//��ӵ�����Body��
		monster->addChild(nowattcknumber->numbers, 10, 12);
	}
}

void SpiritsMonster::ShowNumberCallBack_setvisible(CCObject* obj)
{
	CCSprite* monster = (CCSprite*)obj;
	//�Ƴ��˺���ֵ
	monster->removeChildByTag(12);
}


CCAnimate* SpiritsMonster::updateNowAnt(MainRoledata roledata, int RepeatNum)
{

	//NPC����
	CCAnimation* donghua = SpiritsMonster::getNowAnt(roledata);
	if (roledata.actiontime > 0)
	{
		donghua->setDelayPerUnit(roledata.actiontime / roledata.maxcut_zhan);
	}
	else
	{
		donghua->setDelayPerUnit(2.0f / 15.0f);//ִ��Ĭ��ʱ��
	}
	donghua->setRestoreOriginalFrame(true);
	if (RepeatNum > 0)
	{
		donghua->setLoops(RepeatNum);
	}
	else
	{
		donghua->setLoops(-1);
	}
	CCAnimate* playdonghua = CCAnimate::create(donghua);

	return playdonghua;
}

///*************
//* ���ݵ������������ĳ���
//*************/
Commen_Direction SpiritsMonster::getNowPointDir(CCPoint newpoint, CCSprite* monsters, bool dirflag)
{
	Commen_Direction thisdir = rigth_down; //Ĭ��Ϊ����
										   //�����ƶ�����
	float center_x, center_y, npc_x, npc_y;
	int move_x, move_y;
	//����NPC����״̬
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	center_x = size.width / 2;
	center_y = size.height / 2;
	npc_x = monsters->getPositionX();
	npc_y = monsters->getPositionY();

	if (dirflag == true)
	{
		move_x = (int)(npc_x - newpoint.x);
		move_y = (int)(npc_y - newpoint.y);
	}
	else
	{
		move_x = (int)(newpoint.x - npc_x);
		move_y = (int)(newpoint.y - npc_y);
	}
	if (move_x >= 0 && move_y <= -0)
	{
		//����
		thisdir = left_up;
	}
	else if (move_x >= 0 && move_y >= 0)
	{
		//����
		thisdir = left_down;
	}
	else if (move_x <= -0 && move_y <= -0)
	{
		//����
		thisdir = rigth_up;
	}
	else if (move_x <= -0 && move_y >= 0)
	{
		//����
		thisdir = rigth_down;
	}
	else
	{
		//����
		thisdir = rigth_down;
	}
	return thisdir;
}

///*************
//* �ı��ƶ�����
//*************/
void SpiritsMonster::moveTomap_dir(CCPoint newpoint, CCSprite* monsters, MainRoledata roledata)
{
	Commen_Direction move_dir = SpiritsMonster::getNowPointDir(newpoint, monsters, true);
	roledata.dir = move_dir;
	roledata.acttodo = run;
	monsters->stopAllActions();
	CCAnimate* playdonghua = SpiritsMonster::updateNowAnt(roledata, 0);
	monsters->runAction(playdonghua);
	//���ĵ�ǰ��������������λ��
	char linshiimgurl[100] = { 0 };
	sprintf(linshiimgurl, "%s00000.png", roledata.spiritUrl_pao->getCString(), linshiimgurl);
	CCSprite* linshis = SpiritsMonster::create(linshiimgurl);
	monsters->getChildByTag(111)->setPosition(ccp(linshis->getContentSize().width / 2, linshis->getContentSize().height + 20));
	monsters->getChildByTag(110)->setPosition(ccp(linshis->getContentSize().width / 2, 0));
	monsters->getChildByTag(113)->setPosition(ccp(linshis->getContentSize().width / 2, linshis->getContentSize().height + 5));
	monsters->getChildByTag(114)->setPosition(ccp(linshis->getContentSize().width / 2, -2));
}

///*************
//* �ı乥������ʱ�Ķ���
//*************/
void SpiritsMonster::attackTomainRole_dir(CCPoint newpoint, CCSprite* monsters, MainRoledata roledata)
{
	Commen_Direction move_dir = SpiritsMonster::getNowPointDir(newpoint, monsters, true);
	roledata.dir = move_dir;
	roledata.acttodo = attack;
	CCAnimate* donghua_attck = SpiritsMonster::updateNowAnt(roledata, 1);//��������ִֻ��һ��
	roledata.dir = move_dir;
	roledata.acttodo = stand;
	CCAnimate* donghua_stand = SpiritsMonster::updateNowAnt(roledata, 0);//�ָ�վ��
	monsters->stopAllActions();
	monsters->runAction(CCSequence::create(donghua_attck, donghua_stand, NULL));

	//���ĵ�ǰ��������������λ��
	char linshiimgurl[100] = { 0 };
	sprintf(linshiimgurl, "%s00000.png", roledata.spiritUrl_attack->getCString(), linshiimgurl);
	CCSprite* linshis = SpiritsMonster::create(linshiimgurl);
	monsters->getChildByTag(111)->setPosition(ccp(linshis->getContentSize().width / 2, linshis->getContentSize().height + 20));
	monsters->getChildByTag(110)->setPosition(ccp(linshis->getContentSize().width / 2, 0));
	monsters->getChildByTag(113)->setPosition(ccp(linshis->getContentSize().width / 2, linshis->getContentSize().height + 5));
	monsters->getChildByTag(114)->setPosition(ccp(linshis->getContentSize().width / 2, -2));

}


CCRect SpiritsMonster::rect(CCSprite* monster)
{
	//��ȡ���������С
	return CCRectMake(monster->getPositionX() - monster->getContentSize().width  * monster->getAnchorPoint().x, monster->getPositionY() - monster->getContentSize().height* monster->getAnchorPoint().y, monster->getContentSize().width, monster->getContentSize().height);

}

bool SpiritsMonster::isTouchInside(CCPoint thisPos, CCSprite* monster)
{
	CCPoint localPos = thisPos;
	CCRect rc = rect(monster);
	bool isTouched = rc.containsPoint(localPos);
	if (isTouched == true) {
		//log(FontChina::G2U("ѡ���ʶ�ù���"));
	}
	else
	{
		//log(FontChina::G2U("2222222222222222222��"));

	}
	return isTouched;
}



/*********************
* �˷������ﶯ���ϳ���
*********************/
CCAnimation* SpiritsMonster::getNowAnt(MainRoledata roledata)
{
	CCAnimation* thisdonghua = CCAnimation::create();
	switch (roledata.dir)
	{
	case up:

		switch (roledata.acttodo)
		{
		case run:
			for (int i = 0; i <= roledata.maxcut_pao; i++)
			{
				char donghuaurl[100] = { 0 };
				sprintf(donghuaurl, "%s06%03d.png", roledata.spiritUrl_pao->getCString(), i);
				thisdonghua->addSpriteFrameWithFileName(donghuaurl);
			}
			break;
		case stand:
			for (int i = 0; i <= roledata.maxcut_zhan; i++)
			{
				char donghuaurl[100] = { 0 };
				sprintf(donghuaurl, "%s06%03d.png", roledata.spiritUrl_zhan->getCString(), i);
				thisdonghua->addSpriteFrameWithFileName(donghuaurl);
			}
			break;
		case attack:
			break;
		case death:
			break;
		case funny:
			break;
		default:
			break;
		}

		break;
	case down:
		switch (roledata.acttodo)
		{
		case run:
			for (int i = 0; i <= roledata.maxcut_pao; i++)
			{
				char donghuaurl[100] = { 0 };
				sprintf(donghuaurl, "%s04%03d.png", roledata.spiritUrl_pao->getCString(), i);
				thisdonghua->addSpriteFrameWithFileName(donghuaurl);
			}
			break;
		case stand:
			for (int i = 0; i <= roledata.maxcut_zhan; i++)
			{
				char donghuaurl[100] = { 0 };
				sprintf(donghuaurl, "%s04%03d.png", roledata.spiritUrl_zhan->getCString(), i);
				thisdonghua->addSpriteFrameWithFileName(donghuaurl);
			}
			break;
		case attack:
			break;
		case death:
			break;
		case funny:
			break;
		default:
			break;
		}
		break;
	case lefts:
		switch (roledata.acttodo)
		{
		case run:
			for (int i = 0; i <= roledata.maxcut_pao; i++)
			{
				char donghuaurl[100] = { 0 };
				sprintf(donghuaurl, "%s05%03d.png", roledata.spiritUrl_pao->getCString(), i);
				thisdonghua->addSpriteFrameWithFileName(donghuaurl);
			}
			break;
		case stand:
			for (int i = 0; i <= roledata.maxcut_zhan; i++)
			{
				char donghuaurl[100] = { 0 };
				sprintf(donghuaurl, "%s05%03d.png", roledata.spiritUrl_zhan->getCString(), i);
				thisdonghua->addSpriteFrameWithFileName(donghuaurl);
			}
			break;
		case attack:
			break;
		case death:
			break;
		case funny:
			break;
		default:
			break;
		}
		break;
	case rigth:
		switch (roledata.acttodo)
		{
		case run:
			for (int i = 0; i <= roledata.maxcut_pao; i++)
			{
				char donghuaurl[100] = { 0 };
				sprintf(donghuaurl, "%s07%03d.png", roledata.spiritUrl_pao->getCString(), i);
				thisdonghua->addSpriteFrameWithFileName(donghuaurl);
			}
			break;
		case stand:
			for (int i = 0; i <= roledata.maxcut_zhan; i++)
			{
				char donghuaurl[100] = { 0 };
				sprintf(donghuaurl, "%s07%03d.png", roledata.spiritUrl_zhan->getCString(), i);
				thisdonghua->addSpriteFrameWithFileName(donghuaurl);
			}
			break;
		case attack:
			break;
		case death:
			break;
		case funny:
			break;
		default:
			break;
		}
		break;
	case rigth_up:
		switch (roledata.acttodo)
		{
		case run:
			for (int i = 0; i <= roledata.maxcut_pao; i++)
			{
				char donghuaurl[100] = { 0 };
				sprintf(donghuaurl, "%s03%03d.png", roledata.spiritUrl_pao->getCString(), i);
				thisdonghua->addSpriteFrameWithFileName(donghuaurl);
			}
			break;
		case stand:
			for (int i = 0; i <= roledata.maxcut_zhan; i++)
			{
				char donghuaurl[100] = { 0 };
				sprintf(donghuaurl, "%s03%03d.png", roledata.spiritUrl_zhan->getCString(), i);
				thisdonghua->addSpriteFrameWithFileName(donghuaurl);
			}
			break;
		case attack:
			for (int i = 0; i <= roledata.maxcut_attack; i++)
			{
				char donghuaurl[100] = { 0 };
				sprintf(donghuaurl, "%s03%03d.png", roledata.spiritUrl_attack->getCString(), i);
				thisdonghua->addSpriteFrameWithFileName(donghuaurl);
			}
			break;
		case magicup:
			for (int i = 0; i <= roledata.maxcut_magic; i++)
			{
				char donghuaurl[100] = { 0 };
				sprintf(donghuaurl, "%s03%03d.png", roledata.spiritUrl_magic->getCString(), i);
				thisdonghua->addSpriteFrameWithFileName(donghuaurl);
			}
			break;
		case death:
			break;
		case funny:
			break;
		default:
			break;
		}
		break;
	case rigth_down:
		switch (roledata.acttodo)
		{
		case run:
			for (int i = 0; i <= roledata.maxcut_pao; i++)
			{
				char donghuaurl[1000] = { 0 };
				sprintf(donghuaurl, "%s00%03d.png", roledata.spiritUrl_pao->getCString(), i);
				thisdonghua->addSpriteFrameWithFileName(donghuaurl);
			}
			break;
		case stand:
			for (int i = 0; i <= roledata.maxcut_zhan; i++)
			{
				char donghuaurl[100] = { 0 };
				sprintf(donghuaurl, "%s00%03d.png", roledata.spiritUrl_zhan->getCString(), i);
				thisdonghua->addSpriteFrameWithFileName(donghuaurl);
			}
			break;
		case attack:
			for (int i = 0; i <= roledata.maxcut_attack; i++)
			{
				char donghuaurl[100] = { 0 };
				sprintf(donghuaurl, "%s00%03d.png", roledata.spiritUrl_attack->getCString(), i);
				thisdonghua->addSpriteFrameWithFileName(donghuaurl);
			}
			break;
		case magicup:
			for (int i = 0; i <= roledata.maxcut_magic; i++)
			{
				char donghuaurl[100] = { 0 };
				sprintf(donghuaurl, "%s00%03d.png", roledata.spiritUrl_magic->getCString(), i);
				thisdonghua->addSpriteFrameWithFileName(donghuaurl);
			}
			break;
		case death:
			break;
		case funny:
			break;
		default:
			break;
		}
		break;
	case left_down:
		switch (roledata.acttodo)
		{
		case run:
			for (int i = 0; i <= roledata.maxcut_pao; i++)
			{
				char donghuaurl[100] = { 0 };
				sprintf(donghuaurl, "%s01%03d.png", roledata.spiritUrl_pao->getCString(), i);
				thisdonghua->addSpriteFrameWithFileName(donghuaurl);
			}
			break;
		case stand:
			for (int i = 0; i <= roledata.maxcut_zhan; i++)
			{
				char donghuaurl[100] = { 0 };
				sprintf(donghuaurl, "%s01%03d.png", roledata.spiritUrl_zhan->getCString(), i);
				thisdonghua->addSpriteFrameWithFileName(donghuaurl);
			}
			break;
		case attack:
			for (int i = 0; i <= roledata.maxcut_attack; i++)
			{
				char donghuaurl[100] = { 0 };
				sprintf(donghuaurl, "%s01%03d.png", roledata.spiritUrl_attack->getCString(), i);
				thisdonghua->addSpriteFrameWithFileName(donghuaurl);
			}
			break;
		case magicup:
			for (int i = 0; i <= roledata.maxcut_magic; i++)
			{
				char donghuaurl[100] = { 0 };
				sprintf(donghuaurl, "%s01%03d.png", roledata.spiritUrl_magic->getCString(), i);
				thisdonghua->addSpriteFrameWithFileName(donghuaurl);
			}
			break;
		case death:
			break;
		case funny:
			break;
		default:
			break;
		}
		break;
	case left_up:
		switch (roledata.acttodo)
		{
		case run:
			for (int i = 0; i <= roledata.maxcut_pao; i++)
			{
				char donghuaurl[100] = { 0 };
				sprintf(donghuaurl, "%s02%03d.png", roledata.spiritUrl_pao->getCString(), i);
				thisdonghua->addSpriteFrameWithFileName(donghuaurl);
			}
			break;
		case stand:
			for (int i = 0; i <= roledata.maxcut_zhan; i++)
			{
				char donghuaurl[100] = { 0 };
				sprintf(donghuaurl, "%s02%03d.png", roledata.spiritUrl_zhan->getCString(), i);
				thisdonghua->addSpriteFrameWithFileName(donghuaurl);
			}
			break;
		case attack:
			for (int i = 0; i <= roledata.maxcut_attack; i++)
			{
				char donghuaurl[100] = { 0 };
				sprintf(donghuaurl, "%s02%03d.png", roledata.spiritUrl_attack->getCString(), i);
				thisdonghua->addSpriteFrameWithFileName(donghuaurl);
			}
			break;
		case magicup:
			for (int i = 0; i <= roledata.maxcut_magic; i++)
			{
				char donghuaurl[100] = { 0 };
				sprintf(donghuaurl, "%s02%03d.png", roledata.spiritUrl_magic->getCString(), i);
				thisdonghua->addSpriteFrameWithFileName(donghuaurl);
			}
			break;
		case death:
			break;
		case funny:
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	return thisdonghua;
}


SpiritsMonster::~SpiritsMonster(void)
{
}
