#include "SpiritsMonster.h"
#include "ImagePaths.h"
#include "FontChina.h"
#include "EffectsCommen.h"
#include "MakeNumbers.h"
SpiritsMonster::SpiritsMonster(MainRoledata roledata, int zOrder, int yinzihigth)
{
	//先初始化部分数据

	monster = SpiritsMonster::create(roledata.spiritUrl->getCString());
	if (monster == NULL)
	{
		log("图层路径有误，请检查路径");
		return;
	}
	//设置怪物初始位置坐标（该坐标取决于当前画层）
	monster->setPosition(roledata.nowpoint);
	//怪物动画设置
	playdonghua = SpiritsMonster::updateNowAnt(roledata, 0);
	monster->runAction(playdonghua);


	/**开始添加各部件**/
	//添加名称
	CCLabelTTF* label = CCLabelTTF::create(roledata.spiritname->getCString(), "微软雅黑", 12);
	label->setColor(Color3B::WHITE);
	//label->setDirty(true);
	label->setPosition(ccp(monster->getContentSize().width / 2, monster->getContentSize().height + 20));

	CCLabelTTF* labelback = CCLabelTTF::create(roledata.spiritname->getCString(), "微软雅黑", 12);
	labelback->setColor(Color3B::WHITE);
//	labelback->setDirty(true);
	labelback->setPosition(ccp(label->getContentSize().width / 2 + 1, label->getContentSize().height / 2 - 1));
	label->addChild(labelback, -1, 1002);

	//添加怪物头上血条
	bloodline = CCSprite::create(MONST_BLOOD_LINE);
	bloodline->setPosition(ccp(monster->getContentSize().width / 2, monster->getContentSize().height + 5));

	CCSprite* bloodlinehong = CCSprite::create(MONST_BLOOD_LINE_HONE);
	bloodlinehong->setScale(0.9f);
	bloodlinehong->setPosition(ccp(bloodline->getContentSize().width / 2 - (0.1f*bloodline->getContentSize().width / 2), bloodline->getContentSize().height / 2));
	bloodline->addChild(bloodlinehong, 1, 1);

	//添加怪物脚下阴影
	yinzi = CCSprite::create(YINZI);
	if (yinzi == NULL)
	{
		log("图层路径有误，请检查路径");
		return;
	}
	yinzi->setPosition(ccp(monster->getContentSize().width / 2, yinzihigth));

	//NPC资源
	
	EffectsCommen* selectflag = new EffectsCommen(ccp(monster->getContentSize().width / 2, -2), npc_select_flag1, 2, 20, 0, 2);
	selectflag->effects_main->setVisible(false);
	monster->addChild(yinzi, -1, 110);
	monster->addChild(label, 2, 111);
	monster->addChild(bloodline, 3, 113);
	monster->addChild(selectflag->effects_main, 4, 114);
}

/*
怪物伤害数字动画特效
*/
void SpiritsMonster::showattcknumber(int attcknum, CCSprite* monster)
{
	if (attcknum > 0)
	{
		//解析数值转化为2中格式字符串string和CCString；
		char char_attckmun[100] = { 0 };
		sprintf(char_attckmun, "%d", attcknum, char_attckmun);
		//这个主要用途拿来作为字符和int之间的相互转换
		CCString* numberstr = CCString::create(char_attckmun);
		//组合伤害数值
		MakeNumbers* nowattcknumber = new MakeNumbers(attcknum);
		//设置在怪物头上一半距离弹出伤害
		nowattcknumber->numbers->setPosition(ccp(monster->getContentSize().width / 2, monster->getContentSize().height*1.5f));
		//设置动画赛贝尔曲线
		ccBezierConfig bezier;
		bezier.controlPoint_1 = CCPointMake(50, monster->getContentSize().height*2.0f);
		bezier.controlPoint_2 = CCPointMake(monster->getContentSize().width / 2, monster->getContentSize().height);
		CCActionInterval* bezier_act = CCBezierTo::create(2.5f, bezier);
		//设置动画弹出放大和缩小
		CCActionInterval* scale_act = CCScaleTo::create(2.0f, 1.5f);
		CCActionInterval* scale_actby = CCScaleBy::create(1.0f, 2.0f);
		//设置动画淡出淡入（开始显示，最后隐藏）
		CCActionInterval* fade_actby = CCFadeIn::create(2.0f);
		CCActionInterval* fade_actby2 = CCFadeOut::create(2.0f);
		//最后执行移除回调函数，不消耗内存，用完就释放
		CCFiniteTimeAction *actbackfun = CCCallFuncO::create(monster, callfuncO_selector(SpiritsMonster::ShowNumberCallBack_setvisible), monster);
		nowattcknumber->numbers->runAction(CCSequence::create(scale_actby, scale_actby->reverse(), NULL));
		nowattcknumber->numbers->runAction(fade_actby2);
		for (int i = 0; i < numberstr->length(); i++)
		{
			CCActionInterval* fade_actby_back = fade_actby->reverse();
			nowattcknumber->numbers->getChildByTag(10 + i)->runAction(fade_actby_back);
		}
		nowattcknumber->numbers->runAction(CCSequence::create(bezier_act, actbackfun, NULL));
		//添加到怪物Body中
		monster->addChild(nowattcknumber->numbers, 10, 12);
	}
}

void SpiritsMonster::ShowNumberCallBack_setvisible(CCObject* obj)
{
	CCSprite* monster = (CCSprite*)obj;
	//移除伤害数值
	monster->removeChildByTag(12);
}


CCAnimate* SpiritsMonster::updateNowAnt(MainRoledata roledata, int RepeatNum)
{

	//NPC动画
	CCAnimation* donghua = SpiritsMonster::getNowAnt(roledata);
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
	CCAnimate* playdonghua = CCAnimate::create(donghua);

	return playdonghua;
}

///*************
//* 根据点击坐标获得人物的朝向
//*************/
Commen_Direction SpiritsMonster::getNowPointDir(CCPoint newpoint, CCSprite* monsters, bool dirflag)
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
		//左上
		thisdir = left_up;
	}
	else if (move_x >= 0 && move_y >= 0)
	{
		//左下
		thisdir = left_down;
	}
	else if (move_x <= -0 && move_y <= -0)
	{
		//右上
		thisdir = rigth_up;
	}
	else if (move_x <= -0 && move_y >= 0)
	{
		//右下
		thisdir = rigth_down;
	}
	else
	{
		//右下
		thisdir = rigth_down;
	}
	return thisdir;
}

///*************
//* 改变移动方向
//*************/
void SpiritsMonster::moveTomap_dir(CCPoint newpoint, CCSprite* monsters, MainRoledata roledata)
{
	Commen_Direction move_dir = SpiritsMonster::getNowPointDir(newpoint, monsters, true);
	roledata.dir = move_dir;
	roledata.acttodo = run;
	monsters->stopAllActions();
	CCAnimate* playdonghua = SpiritsMonster::updateNowAnt(roledata, 0);
	monsters->runAction(playdonghua);
	//更改当前动作的其他部件位移
	char linshiimgurl[100] = { 0 };
	sprintf(linshiimgurl, "%s00000.png", roledata.spiritUrl_pao->getCString(), linshiimgurl);
	CCSprite* linshis = SpiritsMonster::create(linshiimgurl);
	monsters->getChildByTag(111)->setPosition(ccp(linshis->getContentSize().width / 2, linshis->getContentSize().height + 20));
	monsters->getChildByTag(110)->setPosition(ccp(linshis->getContentSize().width / 2, 0));
	monsters->getChildByTag(113)->setPosition(ccp(linshis->getContentSize().width / 2, linshis->getContentSize().height + 5));
	monsters->getChildByTag(114)->setPosition(ccp(linshis->getContentSize().width / 2, -2));
}

///*************
//* 改变攻击主角时的动作
//*************/
void SpiritsMonster::attackTomainRole_dir(CCPoint newpoint, CCSprite* monsters, MainRoledata roledata)
{
	Commen_Direction move_dir = SpiritsMonster::getNowPointDir(newpoint, monsters, true);
	roledata.dir = move_dir;
	roledata.acttodo = attack;
	CCAnimate* donghua_attck = SpiritsMonster::updateNowAnt(roledata, 1);//攻击动作只执行一次
	roledata.dir = move_dir;
	roledata.acttodo = stand;
	CCAnimate* donghua_stand = SpiritsMonster::updateNowAnt(roledata, 0);//恢复站立
	monsters->stopAllActions();
	monsters->runAction(CCSequence::create(donghua_attck, donghua_stand, NULL));

	//更改当前动作的其他部件位移
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
	//获取精灵区域大小
	return CCRectMake(monster->getPositionX() - monster->getContentSize().width  * monster->getAnchorPoint().x, monster->getPositionY() - monster->getContentSize().height* monster->getAnchorPoint().y, monster->getContentSize().width, monster->getContentSize().height);

}

bool SpiritsMonster::isTouchInside(CCPoint thisPos, CCSprite* monster)
{
	CCPoint localPos = thisPos;
	CCRect rc = rect(monster);
	bool isTouched = rc.containsPoint(localPos);
	if (isTouched == true) {
		//log(FontChina::G2U("选择标识该怪物"));
	}
	else
	{
		//log(FontChina::G2U("2222222222222222222！"));

	}
	return isTouched;
}



/*********************
* 八方向人物动作合成器
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
