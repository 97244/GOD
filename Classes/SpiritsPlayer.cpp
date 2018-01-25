#include "SpiritsPlayer.h"
#include "FontChina.h"
#include "ImagePaths.h"
#include "GetNPCData.h"

SpiritsPlayer::SpiritsPlayer(MainRoledata roledata, int zOrder, bool zhujiaoflag)
{

	//�ȳ�ʼ����������
	thisroledata = roledata;
	act_moveto_zi = NULL;
	act_moveto_npc = NULL;
	act_moveto_yinzi = NULL;
	actall = NULL;
	thiszhujiao_flag = zhujiaoflag;
	p_ui_name = new PublicShowUI();
	flag = 0;

	npc = SpiritsPlayer::create(roledata.spiritUrl->getCString());
	if (npc == NULL)
	{
		log("ͼ��·����������·��");
		return;
	}
	//����NPC��ʼλ�����꣨������ȡ���ڵ�ǰ���㣩
	npc->setPosition(roledata.nowpoint);
	//NPC��������
	playdonghua = SpiritsPlayer::updateNowAnt(roledata);
	npc->runAction(playdonghua);

	/**��ʼ��ӽ�ɫ������**/
	//��ӽ�ɫ����
	CCLabelTTF* label = CCLabelTTF::create(roledata.spiritname->getCString(), "΢���ź�", 12);
	label->setColor(Color3B::WHITE);
	//label->setDirty(true);
	label->setPosition(ccp(npc->getContentSize().width / 2, npc->getContentSize().height + 6));

	CCLabelTTF* labelback = CCLabelTTF::create(roledata.spiritname->getCString(), "΢���ź�", 12);
	labelback->setColor(Color3B::BLACK);
	//labelback->setDirty(true);
	labelback->setPosition(ccp(npc->getContentSize().width / 2 + 1, npc->getContentSize().height + 6 - 1));

	//���NPC���������Ӱ
	yinzi = CCSprite::create(YINZI);
	if (yinzi == NULL)
	{
		log("ͼ��·����������·��");
		return;
	}
	if (zhujiaoflag == true)
	{
		yinzi->setPosition(ccp(npc->getContentSize().width / 2, 12));
	}
	else
	{
		yinzi->setPosition(ccp(npc->getContentSize().width / 2, 5));
	}

	//MakeNumbers* makenumber = new  MakeNumbers(149);
	//
	//npc->addChild(makenumber->numbers,9,113);

	npc->addChild(yinzi, -1, 110);
	npc->addChild(label, 2, 111);
	npc->addChild(labelback, 1, 112);

}


cocos2d::CCRect SpiritsPlayer::rect()
{
	//��ȡ���������С
	return Rect(npc->getPositionX() - npc->getContentSize().width  * npc->getAnchorPoint().x, npc->getPositionY() - npc->getContentSize().height* npc->getAnchorPoint().y, npc->getContentSize().width, npc->getContentSize().height);

}

bool SpiritsPlayer::isTouchInside(Point thisPos)
{
	Point localPos = thisPos;
	Rect rc = rect();
	bool isTouched = rc.containsPoint(localPos);
	if (isTouched == true) {
		log(FontChina::G2U("1111111111111111111��"));

	}
	else
	{
		log(FontChina::G2U("2222222222222222222��"));

	}
	return isTouched;
}



void SpiritsPlayer::Spirits_talkabout_hid()
{
	log(FontChina::G2U("************������*****************"));
}


Animate* SpiritsPlayer::updateNowAnt(MainRoledata roledata)
{
	//NPC����
	Animation* donghua = SpiritsPlayer::getNowAnt(roledata);
	if (roledata.actiontime > 0)
	{
		donghua->setDelayPerUnit(roledata.actiontime / roledata.maxcut_zhan);
	}
	else
	{
		donghua->setDelayPerUnit(2.0f / 15.0f);//ִ��Ĭ��ʱ��
	}
	donghua->setRestoreOriginalFrame(true);
	donghua->setLoops(-1);
	Animate* playdonghua = Animate::create(donghua);

	return playdonghua;
}

Animate* SpiritsPlayer::updateNowAnt_change(MainRoledata roledata, int RepeatNum)
{
	//NPC����
	Animation* donghua = SpiritsPlayer::getNowAnt(roledata);
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
	Animate* playdonghua = Animate::create(donghua);

	return playdonghua;
}

/*************
* ����λ���ƶ�
*************/
void SpiritsPlayer::moveTomap_move(int uestime, Point newpoint, bool npcflag)
{
	if (npcflag == true)
	{
		actbackfun = CallFunc::create(this, callfunc_selector(SpiritsPlayer::moveoverCallBackforNpc));
	}
	else
	{
		actbackfun = CallFunc::create(this, callfunc_selector(SpiritsPlayer::moveoverCallBack));
	}
	movemethod(uestime, newpoint);
}

void SpiritsPlayer::movemethod(int uestime, Point newpoint)
{
	npc->stopAction(actall);
	act_moveto_npc = MoveTo::create(uestime, ccp(newpoint.x, newpoint.y + 20));
	actall = Sequence::create(act_moveto_npc, actbackfun, NULL);
	npc->runAction(actall);
}


/*************
* �ı��ƶ�����
*************/
void SpiritsPlayer::moveTomap_dir(Point newpoint)
{
	GetNPCData* npcdata = new GetNPCData();
	npcdata->GetNPCchapter1();
	move_dir = SpiritsPlayer::getNowPointDir(newpoint);
	npcdata->role_player.dir = move_dir;
	npcdata->role_player.acttodo = run;
	npcdata->role_player.actiontime = 0.5;
	npc->stopAllActions();
	playdonghua = SpiritsPlayer::updateNowAnt(npcdata->role_player);
	npc->runAction(playdonghua);
	//���ĵ�ǰ��������������λ��
	char linshiimgurl[100] = { 0 };
	sprintf(linshiimgurl, "%s00000.png", npcdata->role_player.spiritUrl_pao->getCString(), linshiimgurl);
	CCSprite* linshis = SpiritsPlayer::create(linshiimgurl);
	npc->getChildByTag(111)->setPosition(ccp(linshis->getContentSize().width / 2, linshis->getContentSize().height + 2));
	npc->getChildByTag(112)->setPosition(ccp(linshis->getContentSize().width / 2, linshis->getContentSize().height + 2));
	npc->getChildByTag(110)->setPosition(ccp(linshis->getContentSize().width / 2, 0));
}

/*************
* �ı�������ͷ���
*************/
void SpiritsPlayer::attckTomap_dir(Point newpoint, Sprite* npc, MainRoledata role_player)
{
	GetNPCData npcdata = GetNPCData();
	npcdata.GetNPCchapter1();
	Commen_Direction move_dir = SpiritsPlayer::getNowPointDir_change(newpoint, npc);
	role_player.dir = move_dir;
	role_player.acttodo = attack;
	CCAnimate* donghua_attck = SpiritsPlayer::updateNowAnt_change(role_player, 1);
	role_player.dir = move_dir;
	role_player.acttodo = stand;
	CCAnimate* donghua_stand = SpiritsPlayer::updateNowAnt_change(role_player, 0);
	npc->stopAllActions();
	npc->runAction(CCSequence::create(donghua_attck, donghua_stand, NULL));
	//���ĵ�ǰ��������������λ��
	char linshiimgurl[100] = { 0 };
	sprintf(linshiimgurl, "%s00000.png", role_player.spiritUrl_attack->getCString(), linshiimgurl);
	CCSprite* linshis = SpiritsPlayer::create(linshiimgurl);
	npc->getChildByTag(111)->setPosition(ccp(linshis->getContentSize().width / 2, linshis->getContentSize().height + 2));
	npc->getChildByTag(112)->setPosition(ccp(linshis->getContentSize().width / 2, linshis->getContentSize().height + 2));
	npc->getChildByTag(110)->setPosition(ccp(linshis->getContentSize().width / 2, 0));
}



/*************
* �ع��ı䷽��
*************/
Commen_Direction SpiritsPlayer::getNowPointDir_change(Point newpoint, Sprite* npc)
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
	npc_x = npc->getPositionX();
	npc_y = npc->getPositionY();

	move_x = (int)(npc_x - newpoint.x);
	move_y = (int)(npc_y - newpoint.y - 20);

	if (move_x >= 0 && move_y <= 0)
	{
		//����
		thisdir = left_up;
	}
	else if (move_x >= 0 && move_y >= 0)
	{
		//����
		thisdir = left_down;
	}
	else if (move_x <= 0 && move_y <= 0)
	{
		//����
		thisdir = rigth_up;
	}
	else if (move_x <= 0 && move_y >= 0)
	{
		//����
		thisdir = rigth_down;
	}
	else
	{
		thisdir = rigth_down;
	}
	return thisdir;
}


/*************
* ���ݵ������������ĳ���
*************/
Commen_Direction SpiritsPlayer::getNowPointDir(Point newpoint)
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
	npc_x = npc->getPositionX();
	npc_y = npc->getPositionY();

	move_x = (int)(npc_x - newpoint.x);
	move_y = (int)(npc_y - newpoint.y - 20);

	if (move_x >= 10 && move_y <= -10)
	{
		//����
		thisdir = left_up;
	}
	else if (move_x >= 10 && move_y >= 10)
	{
		//����
		thisdir = left_down;
	}
	else if (move_x <= -10 && move_y <= -10)
	{
		//����
		thisdir = rigth_up;
	}
	else if (move_x <= -10 && move_y >= 10)
	{
		//����
		thisdir = rigth_down;
	}
	else if (move_x > -10 && move_x < 10 && move_y>0)
	{
		//��
		thisdir = down;
	}
	else if (move_x > -10 && move_x < 10 && move_y < 0)
	{
		//��
		thisdir = up;
	}
	else if (move_x > 0 && move_y > -10 && move_y < 10)
	{
		//��
		thisdir = lefts;
	}
	else if (move_x<0 && move_y>-10 && move_y < 10)
	{
		//��
		thisdir = rigth;
	}
	return thisdir;
}

/*************
* �ƶ���ɺ�Ļص�
*************/
void SpiritsPlayer::moveoverCallBack()
{
	//�ƶ����֮��ָ�վ��״̬
	GetNPCData npcdata = GetNPCData();
	npcdata.GetNPCchapter1();
	npcdata.role_player.dir = move_dir;
	npcdata.role_player.acttodo = stand;
	npcdata.role_player.actiontime = 1.1f;
	npc->stopAllActions();
	playdonghua = SpiritsPlayer::updateNowAnt(npcdata.role_player);
	npc->runAction(playdonghua);
}

/*************
* ��ͨNPC�ƶ���ɺ�Ļص�
*************/
void SpiritsPlayer::moveoverCallBackforNpc()
{

}

/*************
* ���˲������
*************/
void SpiritsPlayer::updateNpcPoint(Point newpoint)
{
	p_ui_name->updataGameText(ccp(newpoint.x, newpoint.y + npc->getContentSize().height / 2 + 10));
	npc->setPosition(newpoint);
	yinzi->setPosition(ccp(newpoint.x, newpoint.y - npc->getContentSize().height / 2 + 5));
}


/*********************
* �˷������ﶯ���ϳ���
*********************/
CCAnimation* SpiritsPlayer::getNowAnt(MainRoledata roledata)
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



SpiritsPlayer::~SpiritsPlayer(void)
{
}

