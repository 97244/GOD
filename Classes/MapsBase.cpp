#include "MapsBase.h"
#include "ImagePaths.h"
extern int storyplayflag;
extern int storyplayflag_caozuo;

MapsBase::MapsBase(CCLayer* layer, CCString mapsurl, int zOrder, CCPoint cp)
{
	act_moveto_maps = NULL;
	float map_x, map_y;
	lastmove_x = 0;
	lastmove_y = 0;
	movetime = 0;

	float center_x, center_y;

	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	nowmap = MapsBase::create(mapsurl.getCString());
	center_x = size.width / 2;
	center_y = size.height / 2;

	map_y = nowmap->getAnchorPointInPoints().y + origin.y;
	map_x = nowmap->getAnchorPointInPoints().x;

	if (cp.getLength() > 0)
	{
		nowmap->setPosition(cp);
	}
	else
	{
		nowmap->setPosition(ccp(map_x, map_y));
	}

	//计算地图上绝对位置的原点坐标
	float map_fornpc_x, map_fornpc_y;
	map_fornpc_x = nowmap->getContentSize().width / 2;
	map_fornpc_y = nowmap->getContentSize().height / 2;

	//故事NPC
	GetNPCData npcdata = GetNPCData();
	npcdata.GetNPCchapter1();
	npcdata.role_taiyizhengren.nowpoint = CCPointMake(map_fornpc_x - 100, map_fornpc_y + 100);
	npc_taiyizhengren = new SpiritsPlayer(npcdata.role_taiyizhengren, 1, false);
	npcdata.role_taishanglaojun.nowpoint = CCPointMake(map_fornpc_x + 70, map_fornpc_y + 100);
	npc_taishanglaojun = new SpiritsPlayer(npcdata.role_taishanglaojun, 1, false);
	npcdata.role_chijiaodaxian.nowpoint = CCPointMake(map_fornpc_x - 100, map_fornpc_y + 30);
	npc_chijiaodaxian = new SpiritsPlayer(npcdata.role_chijiaodaxian, 1, false);
	npcdata.role_qingxuzhenjun.nowpoint = CCPointMake(map_fornpc_x + 70, map_fornpc_y + 30);
	npc_qingxunzhenjun = new SpiritsPlayer(npcdata.role_qingxuzhenjun, 1, false);

	log("%s\n", effpath_shentan1);
	eff1 = new EffectsCommen(ccp(map_fornpc_x - 12, map_fornpc_y + 100), effpath_shentan1, 1.5f, 13, 0, 6);
	eff2 = new EffectsCommen(ccp(map_fornpc_x - 12, map_fornpc_y + 89), effpath_shentan2, 2.5f, 15, 0, 5);
	eff_yun1 = new EffectsCommen(ccp(map_fornpc_x - 190, map_fornpc_y + 129), effpath_huanjing1, 6.5f, 58, 0, 5);
	eff_yun2 = new EffectsCommen(ccp(map_fornpc_x + 190, map_fornpc_y + 129), effpath_huanjing1, 11.5f, 35, 0, 5);
	eff_yun3 = new EffectsCommen(ccp(map_fornpc_x + 220, map_fornpc_y - 49), effpath_huanjing1, 8.5f, 30, 0, 5);
	eff_yun4 = new EffectsCommen(ccp(map_fornpc_x - 50, map_fornpc_y - 79), effpath_huanjing1, 9.5f, 38, 0, 5);


	//添加所有主角，人物，事件，故事
	nowmap->addChild(npc_taiyizhengren->npc, 1, 11);
	nowmap->addChild(npc_taishanglaojun->npc, 1, 12);
	nowmap->addChild(npc_chijiaodaxian->npc, 1, 13);
	nowmap->addChild(npc_qingxunzhenjun->npc, 1, 14);

	nowmap->addChild(eff1->effects_main, 1);
	nowmap->addChild(eff2->effects_main, 1);
	nowmap->addChild(eff_yun1->effects_main, 1);
	nowmap->addChild(eff_yun2->effects_main, 1);
	nowmap->addChild(eff_yun3->effects_main, 1);
	nowmap->addChild(eff_yun4->effects_main, 1);

	//启动定时器监听事件
	nowmap->schedule(schedule_selector(MapsBase::playerstroy_part1_show), 1.0f);

	layer->addChild(nowmap, zOrder);
	nowmap->retain();

}


void MapsBase::playerstroy_part1_show(float times)
{
	if (storyplayflag == 1)
	{

		//第一章特效集

		CCString* effpath_shownpc = CCString::create("/effects/part1/shownpc/show_npc1_");
		CCString* effpath_shownpc2 = CCString::create("/effects/part1/shownpc2/show_npc2_");
		CCString* effpath_shownpc3 = CCString::create("/effects/part1/shownpc3/show_npc3_");


		float center_x, center_y;

		center_x = this->getContentSize().width / 2;
		center_y = this->getContentSize().height / 2;


		EffectsCommen* eff_yun4 = new EffectsCommen(PUBLICTOUMING, effpath_shownpc3, 19, effpath_shownpc2, 33, effpath_shownpc, 14, ccp(center_x + 120, center_y + 90));

		GetNPCData* basedatas = new GetNPCData();
		basedatas->GetNPCchapter1();
		basedatas->role_player.nowpoint = ccp(center_x + 120, center_y + 90);
		SpiritsPlayer* role_main = new  SpiritsPlayer(basedatas->role_player, 5, true);

		CCActionInterval* showjiandan_npc = CCFadeIn::create(15.0f);
		CCFiniteTimeAction *actall = CCSequence::create(showjiandan_npc, NULL);
		role_main->yinzi->runAction(actall);
		role_main->npc->runAction(actall);

		this->addChild(role_main->npc, 3);
		this->addChild(eff_yun4->effects_main, 2);

		this->schedule(schedule_selector(MapsBase::playerstroy_part1_show2), 10.0f);
		storyplayflag = -1;
	}
	else if (storyplayflag == 2)
	{
		storyplayflag_caozuo = 2;
	}
}

void MapsBase::playerstroy_part1_show2(float times)
{
	storyplayflag_caozuo = 1;
	this->unschedule(schedule_selector(MapsBase::playerstroy_part1_show2));
}


MapsBase::~MapsBase()
{

}

bool MapsBase::moveMapto(CCPoint cp, FDPixelSprite* mainmap_Touch)
{

	//npc_taiyizhengren->isTouchInside(cp);

	float center_x, center_y, move_x, move_y, map_x, map_y, to_c_x, to_c_y;

	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	center_x = size.width / 2;
	center_y = size.height / 2;
	move_x = center_x - cp.x;
	move_y = center_y - cp.y;
	map_x = nowmap->getPositionX();
	map_y = nowmap->getPositionY();
	to_c_x = nowmap->getContentSize().width / 2;
	to_c_y = nowmap->getContentSize().height / 2 + origin.y;
	map_x = map_x + move_x;
	map_y = map_y + move_y - origin.y;

	//计算移动时间
	float a1, b1;
	a1 = fabs(move_x) / size.width;
	b1 = fabs(move_y) / size.height;
	float movetime = ((a1 + b1) * 8);
	if (movetime <= 1)
	{
		movetime = 1;
	}

	if (map_x >= to_c_x)
	{
		map_x = to_c_x;
	}
	else if (map_x <= -((nowmap->getContentSize().width / 2) - size.width))
	{
		map_x = -((nowmap->getContentSize().width / 2) - size.width);
	}
	if (map_y >= to_c_y)
	{
		map_y = to_c_y;
	}
	else if (map_y <= -((nowmap->getContentSize().height / 2) - size.height))
	{
		map_y = -((nowmap->getContentSize().height / 2) - size.height);
	}

	//经典中的经典//
	//主角移动
	//CCPoint role_move_pc = nowmap->convertToNodeSpace(ccp(cp.x,cp.y));
	//role_main->moveTomap_dir(role_move_pc);	
	//role_main->moveTomap_move(movetime,role_move_pc,false);
	//地图移动
	if (map_x != lastmove_x&&map_y != lastmove_y)
	{
		//nowmap->stopAction(act_moveto_maps);
		//mainmap_Touch->stopAllActions();
		//act_moveto_maps = CCMoveTo::create(movetime,ccp((int)map_x,(int)map_y));
		//act_moveto_maps_touch = CCMoveTo::create(movetime,ccp((int)map_x,(int)map_y));
		//nowmap->runAction(act_moveto_maps);
		//mainmap_Touch->runAction(act_moveto_maps_touch);
		return true;
	}
	else
	{
		return false;
	}

}
