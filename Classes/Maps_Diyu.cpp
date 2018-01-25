#include "Maps_Diyu.h"
#include "FontChina.h"
#include "SpiritsMonster.h"
#include "SkillEffects.h"
#include "GetNPCData.h"
extern bool touch_skill0_flag;
extern bool nowselects = false;
extern int nowselecttag = -1;
extern GetNPCData* basedatas;


Maps_Diyu::Maps_Diyu(CCLayer* layer, CCString mapsurl, CCString mapsurl_1, int zOrder, CCPoint cp)
{
	//���Ǽ���
	basedatas = new GetNPCData();
	basedatas->GetNPCchapter1();
	basedatas->GetMonsterchapter1();
	nowattckpoint = ccp(0, 0);
	act_moveto_maps = NULL;
	act_moveto_maps_zhezhao = NULL;
	lastmove_x = 0;
	lastmove_y = 0;
	float map_x, map_y;

	float center_x, center_y;

	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	nowmap = Maps_Diyu::create(mapsurl.getCString());
	nowmap_zhezhao = Maps_Diyu::create(mapsurl_1.getCString());
	center_x = size.width / 2;
	center_y = size.height / 2;

	map_y = nowmap->getAnchorPointInPoints().y + origin.y;
	map_x = nowmap->getAnchorPointInPoints().x;

	if (cp.getLength() > 0)
	{
		nowmap->setPosition(cp);
		nowmap_zhezhao->setPosition(cp);
	}
	else
	{
		nowmap->setPosition(ccp(map_x, map_y));
		nowmap_zhezhao->setPosition(ccp(map_x, map_y));
	}

	//�����ͼ�Ͼ���λ�õ�ԭ������
	float map_fornpc_x, map_fornpc_y;
	map_fornpc_x = nowmap->getContentSize().width / 2;
	map_fornpc_y = nowmap->getContentSize().height / 2;


	basedatas->role_player.nowpoint = CCPointMake(map_fornpc_x + 428, map_fornpc_y + 480);
	role_main = new SpiritsPlayer(basedatas->role_player, 1, false);
	role_main->npc->retain();

	//����NPC
	basedatas->role_mengpo.nowpoint = CCPointMake(map_fornpc_x + 158, map_fornpc_y + 510);
	SpiritsPlayer* role_mengpo = new SpiritsPlayer(basedatas->role_mengpo, 1, true);
	nowmap->addChild(role_mengpo->npc, 2);

	////���ع���
	makemonster(5, 100, ccp(50, 50), basedatas->monster_xixuebianfu, -15, ccp(-520, 450));
	makemonster(3, 105, ccp(100, 10), basedatas->monster_kongjumo, -5, ccp(-220, 480));
	//makemonster(1,110,ccp(100,100),basedatas->monster_qitiandasheng,6,ccp(120,480));

	//�������й�������AI������
	nowmap->schedule(schedule_selector(Maps_Diyu::makemonsterAttack), (3.0f));
	//������Ҳ���������
	nowmap->schedule(schedule_selector(Maps_Diyu::makeroleAttack));

	//-------------------------------------------------------
	nowmap->addChild(role_main->npc, 2, 999);
	layer->addChild(nowmap_zhezhao, zOrder + 1);
	layer->addChild(nowmap, zOrder);
}

void Maps_Diyu::makemonsterAttack(float times)
{
	CCPoint playerpoint = this->getChildByTag(999)->getPosition();
	CCArray* allCCrct = new CCArray();
	basedatas = new GetNPCData();
	basedatas->GetMonsterchapter1();
	attact_todo(5, 100, basedatas->monster_xixuebianfu, 250, 50, playerpoint, ccp(50, 50), ccp(-520, 450));
	attact_todo(3, 105, basedatas->monster_kongjumo, 450, 300, playerpoint, ccp(100, 10), ccp(-220, 480));
	//attact_todo(1,110,basedatas->monster_qitiandasheng,450,200,playerpoint,ccp(100,100),ccp(120,480));
}

void Maps_Diyu::makeroleAttack(float times)
{
	if (touch_skill0_flag == true)
	{
		//��ȥѰ��������Χ�ĵ��ˣ�ѡ�������һ��ΪĿ�ꣻ
		CCPoint playerpoint = this->getChildByTag(999)->getPosition();
		int attck_reatR = 200;
		int nowtag = -1;
		CCPointArray* attck_pointlist = CCPointArray::create(0);
		for (int i = 0; i < 15; i++)
		{
			CCRect* attck_rect = new Rect(this->getChildByTag(999)->getPosition().x - attck_reatR / 2, this->getChildByTag(999)->getPosition().y - attck_reatR / 2, attck_reatR, attck_reatR);
			if (this->getChildByTag(100 + i) != NULL)
			{
				if (attck_rect->containsPoint(this->getChildByTag(100 + i)->getPosition()) == true)
				{
					//log(FontChina::G2U("�����ǹ�����Χ"));
					attck_pointlist->addControlPoint(this->getChildByTag(100 + i)->getPosition());
					nowtag = 100 + i;
					break;
				}
			}
		}
		if (nowselects == true)
		{
			//����Ĭ�Ϲ���
			CCPoint attck_point = this->getChildByTag(nowselecttag)->getPosition();
			basedatas = new GetNPCData();
			basedatas->GetNPCchapter1();
			basedatas->role_player.acttodo = attack;
			basedatas->role_player.actiontime = 0.5f;
			SpiritsPlayer::attckTomap_dir(ccp(attck_point.x, attck_point.y), (CCSprite*)this->getChildByTag(999), basedatas->role_player);
			SkillEffects* role_skill = new SkillEffects(ccp((int)attck_point.x, (int)attck_point.y), basedatas->role_player, (0.2f + CCRANDOM_0_1()), 12, 3, 0);

			this->addChild(role_skill->effects_main, 1000, 50);
			role_skill->release();
			SpiritsMonster::showattcknumber(899, (CCSprite*)this->getChildByTag(nowselecttag));
		}
		else
		{
			if (attck_pointlist->count() > 0)
			{
				//����Ĭ�Ϲ���
				CCPoint attck_point = attck_pointlist->getControlPointAtIndex(0);
				//�ü����Ƿ����ƶ�һ�����룬�ٽ��й���������ֱ���ͷ�ħ������
				basedatas = new GetNPCData();
				basedatas->GetNPCchapter1();
				basedatas->role_player.acttodo = attack;
				basedatas->role_player.actiontime = 0.5f;
				SpiritsPlayer::attckTomap_dir(ccp(attck_point.x, attck_point.y), (CCSprite*)this->getChildByTag(999), basedatas->role_player);
				SkillEffects* role_skill = new SkillEffects(ccp((int)attck_point.x, (int)attck_point.y), basedatas->role_player, (0.2f + CCRANDOM_0_1()), 12, 3, 0);

				this->addChild(role_skill->effects_main, 1000, 50);
				role_skill->release();
				SpiritsMonster::showattcknumber(899, (CCSprite*)this->getChildByTag(nowtag));
			}
		}
		touch_skill0_flag = false;
	}

}

bool Maps_Diyu::touch_select(CCPoint cp)
{
	bool selecttrue = false;
	nowselects = false;
	for (int i = 100; i < 115; i++)
	{
		if (nowmap->getChildByTag(i) != NULL)
		{
			if (SpiritsMonster::isTouchInside(nowmap->convertToNodeSpace(cp), (CCSprite*)nowmap->getChildByTag(i)) == true && selecttrue == false)
			{
				nowmap->getChildByTag(i)->getChildByTag(114)->setVisible(true);
				selecttrue = true;
				nowselects = true;
				nowselecttag = i;
			}
			else
			{
				nowmap->getChildByTag(i)->getChildByTag(114)->setVisible(false);
			}
		}
	}
	return selecttrue;
}

/********************************************
ע�ͣ�
makenum ����������
monsteridtags ������ʼ��ǩ
randomrange ���ù�Ȧ��С��ֻ������������
monster_model ��������
yinzihigth Ӱ�ӵľ���
fristpoint �����ʼ�趨�Ĺ�Ȧ��
*********************************************/
void Maps_Diyu::makemonster(int makenum, int monsteridtags, CCPoint randomrange, MainRoledata monster_model, int yinzihigth, CCPoint fristpoint)
{
	for (int i = 0; i < makenum; i++)
	{
		int add_x = (int)(CCRANDOM_MINUS1_1()*randomrange.x);
		int add_y = (int)(CCRANDOM_MINUS1_1()*randomrange.y);
		monster_model.tags = monsteridtags + i;
		monster_model.nowpoint = CCPointMake(nowmap->getContentSize().width / 2 + fristpoint.x + add_x, nowmap->getContentSize().height / 2 + fristpoint.y + add_y);
		SpiritsMonster* newmonster = new SpiritsMonster(monster_model, 1, yinzihigth);
		nowmap->addChild(newmonster->monster, 1, monsteridtags + i);
	}
}

/********************************************
ע�ͣ�
monsternum ����������
monsteridtags ������ʼ��ǩ
monster_model ��������
reatR �������ӽǵķ�Χֵ��ͨ��200���ң�
attck_reatR ����ɹ�����Χֵ��Զ�ֺ̹�������
playerpoint ��������
randomrange ����Ĭ������ƶ���Χ
fristpoint �����ʼ�趨�Ĺ�Ȧ��
*********************************************/
void Maps_Diyu::attact_todo(int monsternum, int monsteridtags, MainRoledata monster_model, int reatR, int attck_reatR, CCPoint playerpoint, CCPoint randomrange, CCPoint fristpoint)
{
	for (int i = 0; i < monsternum; i++)
	{
		CCRect* attck_rect = new Rect(this->getChildByTag(monsteridtags + i)->getPosition().x - attck_reatR / 2, this->getChildByTag(monsteridtags + i)->getPosition().y - attck_reatR / 2, attck_reatR, attck_reatR);
		if (attck_rect->containsPoint(playerpoint) == true)
		{
			//ִ�й��﹥������
			log(FontChina::G2U("�������ɹ�����Χ"));
			//����ʱ�ı䷽��
			SpiritsMonster::attackTomainRole_dir(ccp((int)playerpoint.x, (int)playerpoint.y), (CCSprite*)(this->getChildByTag(monsteridtags + i)), monster_model);
			//�ͷż��ܶ���
			int add_x = (int)(CCRANDOM_MINUS1_1() * 8);
			int add_y = (int)(CCRANDOM_MINUS1_1() * 8);
			SkillEffects* skill = new SkillEffects(ccp((int)playerpoint.x + add_x, (int)playerpoint.y + add_y), monster_model, (0.2f + CCRANDOM_0_1()), 8, 3, 1000);
			this->addChild(skill->effects_main, 1000, 50);
		}
		else
		{
			CCRect* track_rect = new Rect(this->getChildByTag(monsteridtags + i)->getPosition().x - reatR / 2, this->getChildByTag(monsteridtags + i)->getPosition().y - reatR / 2, reatR, reatR);
			if (track_rect->containsPoint(playerpoint) == true)
			{
				//ִ���ƶ�����ͣ׷ɱ����
				log(FontChina::G2U("�����������Ұ����"));
				//��ֹ�������ǣ�����һ�����룡��ҪΪ�˺ÿ��ʹ�������Ч����
				int add_x = (int)(CCRANDOM_MINUS1_1() * 25);
				int add_y = (int)(CCRANDOM_MINUS1_1() * 25);
				//�ƶ�ʱ�ı䷽��
				SpiritsMonster::moveTomap_dir(ccp((int)playerpoint.x, (int)playerpoint.y), (CCSprite*)(this->getChildByTag(monsteridtags + i)), monster_model);
				CCArray* callbackArray = CCArray::create();
				int nowtags = monsteridtags + i;
				char strs[64];
				sprintf(strs, "%d", nowtags);
				CCString* ccnowtags = CCString::create(strs);
				callbackArray->addObject(ccnowtags);
				callbackArray->addObject(monster_model.spiritname);
				char dir_x[64];
				sprintf(dir_x, "%d", (int)this->getChildByTag(nowtags)->getPositionX());
				char dir_y[64];
				sprintf(dir_y, "%d", (int)this->getChildByTag(nowtags)->getPositionY());
				CCString* d_x = CCString::create(dir_x);
				CCString* d_y = CCString::create(dir_y);
				callbackArray->addObject(d_x);
				callbackArray->addObject(d_y);
				CCFiniteTimeAction *actbackfun = CCCallFuncO::create(this, callfuncO_selector(Maps_Diyu::moveoverCallBack), callbackArray);
				CCActionInterval* act_movexixue = CCMoveTo::create(3 + CCRANDOM_MINUS1_1(), ccp((int)playerpoint.x + add_x, (int)playerpoint.y + add_y));
				this->getChildByTag(nowtags)->runAction(CCSequence::create(act_movexixue, actbackfun, NULL));
			}
			else
			{
				//������ʱ�����������Χ�ƶ�
				int stopandrun = (int)(CCRANDOM_MINUS1_1() * 10);
				if (stopandrun >= 1)
				{
					//������
					int add_x = (int)(CCRANDOM_MINUS1_1()*randomrange.x);
					int add_y = (int)(CCRANDOM_MINUS1_1()*randomrange.y);
					CCPoint move_dir = ccp(this->getContentSize().width / 2 + fristpoint.x + add_x, this->getContentSize().height / 2 + fristpoint.y + add_y);

					SpiritsMonster::moveTomap_dir(ccp((int)move_dir.x, (int)move_dir.y), (CCSprite*)(this->getChildByTag(monsteridtags + i)), monster_model);
					CCArray* callbackArray = CCArray::create();
					int nowtags = monsteridtags + i;
					char strs[64];
					sprintf(strs, "%d", nowtags);
					CCString* ccnowtags = CCString::create(strs);
					callbackArray->addObject(ccnowtags);
					callbackArray->addObject(monster_model.spiritname);
					char dir_x[64];
					sprintf(dir_x, "%d", (int)this->getChildByTag(nowtags)->getPositionX());
					char dir_y[64];
					sprintf(dir_y, "%d", (int)this->getChildByTag(nowtags)->getPositionY());
					CCString* d_x = CCString::create(dir_x);
					CCString* d_y = CCString::create(dir_y);
					callbackArray->addObject(d_x);
					callbackArray->addObject(d_y);
					CCFiniteTimeAction *actbackfun = CCCallFuncO::create(this, callfuncO_selector(Maps_Diyu::moveoverCallBack), callbackArray);
					CCActionInterval* act_movexixue = CCMoveTo::create(3 + CCRANDOM_MINUS1_1(), ccp(move_dir.x, move_dir.y));
					this->getChildByTag(nowtags)->runAction(CCSequence::create(act_movexixue, actbackfun, NULL));

				}
			}
		}
	}
}

/*************
* �ƶ���ɺ�Ļص�
*************/
void Maps_Diyu::moveoverCallBack(CCObject* monster_model)
{
	GetNPCData* basedatas = new GetNPCData();
	basedatas->GetMonsterchapter1();
	//�ƶ����֮��ָ�վ��״̬
	CCArray* modellist = (CCArray*)monster_model;
	CCString* nowtags = (CCString*)modellist->objectAtIndex(0);
	CCString* nowmonstername = (CCString*)modellist->objectAtIndex(1);
	CCString* d_x = (CCString*)modellist->objectAtIndex(2);
	CCString* d_y = (CCString*)modellist->objectAtIndex(3);
	if (nowmonstername->isEqual(CCString::create(FontChina::G2U("�־�ħ"))) == true)
	{
		basedatas->monster_kongjumo.acttodo = stand;
		basedatas->monster_kongjumo.dir = SpiritsMonster::getNowPointDir(ccp(d_x->floatValue(), d_y->floatValue()), (CCSprite*)this->getChildByTag(nowtags->intValue()), false);
		this->getChildByTag(nowtags->intValue())->stopAllActions();
		playdonghua = SpiritsMonster::updateNowAnt(basedatas->monster_kongjumo, 0);
		this->getChildByTag(nowtags->intValue())->runAction(playdonghua);
	}
	if (nowmonstername->isEqual(CCString::create(FontChina::G2U("����ɽ��"))) == true)
	{
		basedatas->monster_qitiandasheng.acttodo = stand;
		basedatas->monster_qitiandasheng.dir = SpiritsMonster::getNowPointDir(ccp(d_x->floatValue(), d_y->floatValue()), (CCSprite*)this->getChildByTag(nowtags->intValue()), false);
		this->getChildByTag(nowtags->intValue())->stopAllActions();
		playdonghua = SpiritsMonster::updateNowAnt(basedatas->monster_qitiandasheng, 0);
		this->getChildByTag(nowtags->intValue())->runAction(playdonghua);
	}

}


/*************************
����˵��:
CCPoint cp  �������������
mainmap_Touch ����������Ҫȥ��ʱ�ı����ƶ�
**************************/
bool Maps_Diyu::moveMapto(CCPoint cp, FDPixelSprite* mainmap_Touch)
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

	//�����ƶ�ʱ�䣬��ߴ�ҿ��԰����Ż�һ��
	//���ھ�����ƶ�ʱ����һЩ����
	float a1, b1;
	a1 = fabs(move_x) / size.width;
	b1 = fabs(move_y) / size.height;
	float movetime = ((a1 + b1) * 8);
	if (movetime <= 1)
	{
		movetime = 1;
	}

	//�����Ǿ�������Ҫ�Ǵ��������ͼ�Ž���֮��
	//��ֹ��ʾ���򳬳���ͼ�ĳ����ƶ����߽�Ͳ����ƶ��ˣ�
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

	//�����еľ���//
	//�����ƶ�
	CCPoint role_move_pc = nowmap->convertToNodeSpace(ccp(cp.x, cp.y));//�˴���Ҫͨ����ͼ���ӽǰ������ƶ�������ת��һ�¡�
	role_main->moveTomap_dir(role_move_pc);
	role_main->moveTomap_move(movetime, role_move_pc, false);
	//��ͼ�ƶ�
	if (map_x != lastmove_x&&map_y != lastmove_y)
	{
		nowmap->stopAction(act_moveto_maps);
		nowmap_zhezhao->stopAction(act_moveto_maps_zhezhao);
		mainmap_Touch->stopAllActions();
		act_moveto_maps = CCMoveTo::create(movetime, ccp((int)map_x, (int)map_y));
		act_moveto_maps_touch = CCMoveTo::create(movetime, ccp((int)map_x, (int)map_y));
		act_moveto_maps_zhezhao = CCMoveTo::create(movetime, ccp((int)map_x, (int)map_y));
		nowmap->runAction(act_moveto_maps);
		nowmap_zhezhao->runAction(act_moveto_maps_zhezhao);
		mainmap_Touch->runAction(act_moveto_maps_touch);
		return true;
	}
	else
	{
		return false;
	}

}



Maps_Diyu::~Maps_Diyu(void)
{
}
