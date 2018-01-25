#include "SkillEffects.h"
//#include "../SkillPath.h"
#include "FontChina.h"

SkillEffects::SkillEffects(CCPoint basepoint, MainRoledata model, float actiontime, float maxnum, int showtype, int skillnumber)
{

	CCString* publictouming1 = CCString::create("/effects/part1/shentan1/0049-ecd97d89-");
	//吸血蝙蝠普通攻击
	CCString* skill_xixue = CCString::create("/skills/xixue/skill_xixue_");
	CCString* skill_kongjumo = CCString::create("/skills/kongjumo/skill_kongjimo_");
	CCString* skill_ziqidonglai = CCString::create("/role_skill/ziqidonglai/ziqidonglai_");


	act_moveto = NULL;
	char indeximg[100] = { 0 };
	sprintf(indeximg, "%s00000.png", publictouming1->getCString());
	effects_main = SkillEffects::create(indeximg);
	effects_main->setPosition(basepoint);
	if (effects_main == NULL)
	{
		log("图层路径有误，请检查路径");
		return;
	}

	CCAnimation* thisdonghua = CCAnimation::create();
	CCAnimation* thisdonghua_return = CCAnimation::create();
	CCString* imgurls = CCString::create("");
	if (model.spiritname->isEqual(CCString::create(FontChina::G2U("恐惧魔"))) == true)
	{
		maxnum = 13;
		imgurls = skill_kongjumo;
	}
	else if (model.spiritname->isEqual(CCString::create(FontChina::G2U("吸血蝙蝠"))) == true)
	{
		maxnum = 8;
		imgurls = skill_xixue;
	}
	else if (model.spiritname->isEqual(CCString::create(FontChina::G2U("紫秀青衣"))) == true)
	{
		maxnum = 12;
		if (skillnumber == 0)
		{
			imgurls = skill_ziqidonglai;
		}
	}
	else
	{
		imgurls = skill_ziqidonglai;
	}
	for (int i = 0; i <= maxnum; i++)
	{
		char donghuaurl[100] = { 0 };
		sprintf(donghuaurl, "%s00%03d.png", imgurls->getCString(), i);
		thisdonghua->addSpriteFrameWithFileName(donghuaurl);
	}

	if (actiontime > 0)
	{
		thisdonghua->setDelayPerUnit(actiontime / maxnum);
	}
	else
	{
		thisdonghua->setDelayPerUnit(2.0f / 15.0f);//执行默认时间
	}
	thisdonghua->setRestoreOriginalFrame(true);

	//特效显示方式
	if (showtype == 0)
	{
		//无限循环
		thisdonghua->setLoops(-1);
		CCAnimate* playdonghua = CCAnimate::create(thisdonghua);
		actall = CCSequence::create(playdonghua, NULL);
	}
	else if (showtype == 1)
	{
		//只播放一次
		thisdonghua->setLoops(1);
		CCAnimate* playdonghua = CCAnimate::create(thisdonghua);
		actall = CCSequence::create(playdonghua, NULL);
	}
	else if (showtype == 2)
	{
		//循环一次之后消失
		thisdonghua->setLoops(1);
		CCDelayTime *waiting = CCDelayTime::create(0.5f);
		CCFiniteTimeAction *actbackfun = CCCallFunc::create(this, callfunc_selector(SkillEffects::moveoverCallBack_setvisible));
		CCAnimate* playdonghua = CCAnimate::create(thisdonghua);
		actall = CCSequence::create(waiting, playdonghua, actbackfun, NULL);
	}
	else if (showtype == 3)
	{
		//循环一次之后消失
		thisdonghua->setLoops(1);
		CCDelayTime *waiting = CCDelayTime::create(0.5f);
		CCFiniteTimeAction *actbackfun = CCCallFunc::create(this, callfunc_selector(SkillEffects::moveoverCallBack_setvisible));
		CCAnimate* playdonghua = CCAnimate::create(thisdonghua);
		actall = CCSequence::create(waiting, playdonghua, actbackfun, NULL);
	}

	effects_main->runAction(actall);

}



void SkillEffects::moveoverCallBack_setvisible(void)
{
	//播放完成隐藏
	effects_main->setVisible(false);
}

SkillEffects::~SkillEffects(void)
{
}
