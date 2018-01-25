#include "SpiritsPlayer.h"
#include "FontChina.h"
#include "ImagePaths.h"
#include "GetNPCData.h"

SpiritsPlayer::SpiritsPlayer(MainRoledata roledata, int zOrder, bool zhujiaoflag)
{

	//先初始化部分数据
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
		log("图层路径有误，请检查路径");
		return;
	}
	//设置NPC初始位置坐标（该坐标取决于当前画层）
	npc->setPosition(roledata.nowpoint);
	//NPC动画设置
	playdonghua = SpiritsPlayer::updateNowAnt(roledata);
	npc->runAction(playdonghua);

	/**开始添加角色各部件**/
	//添加角色名称
	CCLabelTTF* label = CCLabelTTF::create(roledata.spiritname->getCString(), "微软雅黑", 12);
	label->setColor(Color3B::WHITE);
	//label->setDirty(true);
	label->setPosition(ccp(npc->getContentSize().width / 2, npc->getContentSize().height + 6));

	CCLabelTTF* labelback = CCLabelTTF::create(roledata.spiritname->getCString(), "微软雅黑", 12);
	labelback->setColor(Color3B::BLACK);
	//labelback->setDirty(true);
	labelback->setPosition(ccp(npc->getContentSize().width / 2 + 1, npc->getContentSize().height + 6 - 1));

	//添加NPC人物脚下阴影
	yinzi = CCSprite::create(YINZI);
	if (yinzi == NULL)
	{
		log("图层路径有误，请检查路径");
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
	//获取精灵区域大小
	return Rect(npc->getPositionX() - npc->getContentSize().width  * npc->getAnchorPoint().x, npc->getPositionY() - npc->getContentSize().height* npc->getAnchorPoint().y, npc->getContentSize().width, npc->getContentSize().height);

}

bool SpiritsPlayer::isTouchInside(Point thisPos)
{
	Point localPos = thisPos;
	Rect rc = rect();
	bool isTouched = rc.containsPoint(localPos);
	if (isTouched == true) {
		log(FontChina::G2U("1111111111111111111！"));

	}
	else
	{
		log(FontChina::G2U("2222222222222222222！"));

	}
	return isTouched;
}



void SpiritsPlayer::Spirits_talkabout_hid()
{
	log(FontChina::G2U("************调用了*****************"));
}


Animate* SpiritsPlayer::updateNowAnt(MainRoledata roledata)
{
	//NPC动画
	Animation* donghua = SpiritsPlayer::getNowAnt(roledata);
	if (roledata.actiontime > 0)
	{
		donghua->setDelayPerUnit(roledata.actiontime / roledata.maxcut_zhan);
	}
	else
	{
		donghua->setDelayPerUnit(2.0f / 15.0f);//执行默认时间
	}
	donghua->setRestoreOriginalFrame(true);
	donghua->setLoops(-1);
	Animate* playdonghua = Animate::create(donghua);

	return playdonghua;
}

Animate* SpiritsPlayer::updateNowAnt_change(MainRoledata roledata, int RepeatNum)
{
	//NPC动画
	Animation* donghua = SpiritsPlayer::getNowAnt(roledata);
	if (roledata.actiontime > 0)
	{
		donghua->setDelayPerUnit(roledata.actiontime / roledata.maxcut_zhan);
	}
	else
	{
		donghua->setDelayPerUnit(2.0f / 15.0f);//执行默认时间
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
* 主角位移移动
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
* 改变移动方向
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
	//更改当前动作的其他部件位移
	char linshiimgurl[100] = { 0 };
	sprintf(linshiimgurl, "%s00000.png", npcdata->role_player.spiritUrl_pao->getCString(), linshiimgurl);
	CCSprite* linshis = SpiritsPlayer::create(linshiimgurl);
	npc->getChildByTag(111)->setPosition(ccp(linshis->getContentSize().width / 2, linshis->getContentSize().height + 2));
	npc->getChildByTag(112)->setPosition(ccp(linshis->getContentSize().width / 2, linshis->getContentSize().height + 2));
	npc->getChildByTag(110)->setPosition(ccp(linshis->getContentSize().width / 2, 0));
}

/*************
* 改变各种类型方向
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
	//更改当前动作的其他部件位移
	char linshiimgurl[100] = { 0 };
	sprintf(linshiimgurl, "%s00000.png", role_player.spiritUrl_attack->getCString(), linshiimgurl);
	CCSprite* linshis = SpiritsPlayer::create(linshiimgurl);
	npc->getChildByTag(111)->setPosition(ccp(linshis->getContentSize().width / 2, linshis->getContentSize().height + 2));
	npc->getChildByTag(112)->setPosition(ccp(linshis->getContentSize().width / 2, linshis->getContentSize().height + 2));
	npc->getChildByTag(110)->setPosition(ccp(linshis->getContentSize().width / 2, 0));
}



/*************
* 重构改变方向
*************/
Commen_Direction SpiritsPlayer::getNowPointDir_change(Point newpoint, Sprite* npc)
{
	Commen_Direction thisdir = rigth_down; //默认为右下
										   //计算移动数据
	float center_x, center_y, npc_x, npc_y;
	int move_x, move_y;
	//更新NPC方向，状态
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
		//左上
		thisdir = left_up;
	}
	else if (move_x >= 0 && move_y >= 0)
	{
		//左下
		thisdir = left_down;
	}
	else if (move_x <= 0 && move_y <= 0)
	{
		//右上
		thisdir = rigth_up;
	}
	else if (move_x <= 0 && move_y >= 0)
	{
		//右下
		thisdir = rigth_down;
	}
	else
	{
		thisdir = rigth_down;
	}
	return thisdir;
}


/*************
* 根据点击坐标获得人物的朝向
*************/
Commen_Direction SpiritsPlayer::getNowPointDir(Point newpoint)
{
	Commen_Direction thisdir = rigth_down; //默认为右下
										   //计算移动数据
	float center_x, center_y, npc_x, npc_y;
	int move_x, move_y;
	//更新NPC方向，状态
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
		//左上
		thisdir = left_up;
	}
	else if (move_x >= 10 && move_y >= 10)
	{
		//左下
		thisdir = left_down;
	}
	else if (move_x <= -10 && move_y <= -10)
	{
		//右上
		thisdir = rigth_up;
	}
	else if (move_x <= -10 && move_y >= 10)
	{
		//右下
		thisdir = rigth_down;
	}
	else if (move_x > -10 && move_x < 10 && move_y>0)
	{
		//下
		thisdir = down;
	}
	else if (move_x > -10 && move_x < 10 && move_y < 0)
	{
		//上
		thisdir = up;
	}
	else if (move_x > 0 && move_y > -10 && move_y < 10)
	{
		//左
		thisdir = lefts;
	}
	else if (move_x<0 && move_y>-10 && move_y < 10)
	{
		//右
		thisdir = rigth;
	}
	return thisdir;
}

/*************
* 移动完成后的回调
*************/
void SpiritsPlayer::moveoverCallBack()
{
	//移动完成之后恢复站立状态
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
* 普通NPC移动完成后的回调
*************/
void SpiritsPlayer::moveoverCallBackforNpc()
{

}

/*************
* 点击瞬移至此
*************/
void SpiritsPlayer::updateNpcPoint(Point newpoint)
{
	p_ui_name->updataGameText(ccp(newpoint.x, newpoint.y + npc->getContentSize().height / 2 + 10));
	npc->setPosition(newpoint);
	yinzi->setPosition(ccp(newpoint.x, newpoint.y - npc->getContentSize().height / 2 + 5));
}


/*********************
* 八方向人物动作合成器
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

