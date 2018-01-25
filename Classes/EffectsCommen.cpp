#include "EffectsCommen.h"
#include "ImagePaths.h"
#include "FontChina.h"
EffectsCommen::EffectsCommen(Point basepoint, char* imgurl, float actiontime, float maxnum, int showtype, int zOrder)
{
	if (imgurl == NULL)
	{
		log(FontChina::G2U("imgur1 路径为空"));
		return;
	}
	act_moveto = NULL;
	char indeximg[100] = { 0 };
	sprintf(indeximg, "%s00000.png", PUBLICTOUMING);
	effects_main = EffectsCommen::create(indeximg);
	effects_main->setPosition(basepoint);
	if (effects_main == NULL)
	{
		log(FontChina::G2U("图层路径有误，请检查路径"));
		return;
	}

	auto thisdonghua = Animation::create();
	auto thisdonghua_return = Animation::create();

	for (int i = 0; i <= maxnum; i++)
	{
		char donghuaurl[100] = { 0 };
		sprintf(donghuaurl, "%s00%03d.png", imgurl, i);
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
		auto playdonghua = Animate::create(thisdonghua);
		actall = Sequence::create(playdonghua, NULL);
	}
	else if (showtype == 1)
	{
		//只播放一次
		thisdonghua->setLoops(1);
		auto playdonghua = Animate::create(thisdonghua);
		actall = Sequence::create(playdonghua, NULL);
	}
	else if (showtype == 2)
	{
		//循环一次之后消失
		thisdonghua->setLoops(1);
		auto actbackfun = CallFunc::create(this, callfunc_selector(EffectsCommen::moveoverCallBack_setvisible));
		auto playdonghua = Animate::create(thisdonghua);
		actall = Sequence::create(playdonghua, actbackfun, NULL);
	}
	else if (showtype == 3)
	{
		//循环一次之后消失
		thisdonghua->setLoops(2);
		auto actbackfun = CallFunc::create(this, callfunc_selector(EffectsCommen::moveoverCallBack_setvisible));
		auto playdonghua = Animate::create(thisdonghua);
		actall = Sequence::create(playdonghua, actbackfun, NULL);
	}

	effects_main->runAction(actall);
}


EffectsCommen::~EffectsCommen(void)
{

}


void EffectsCommen::moveoverCallBack_setvisible(void)
{
	//播放完成隐藏
	effects_main->setVisible(false);
}


EffectsCommen::EffectsCommen(char* imgurl0, String* imgurl, int num1, String* imgurl2, int num2, String* imgurl3, int num3, Point newpoint)
{
	if (imgurl0 == NULL)
	{
		log(FontChina::G2U("imgur10 路径为空"));
		return;
	}
	act_moveto = NULL;
	char indeximg[100] = { 0 };
	sprintf(indeximg, "%s00000.png", PUBLICTOUMING);
	effects_main = EffectsCommen::create(indeximg);
	effects_main->setPosition(newpoint);
	if (effects_main == NULL)
	{
		log("图层路径有误，请检查路径");
		return;
	}

	auto thisdonghua = Animation::create();

	for (int i = 0; i <= num1; i++)
	{
		char donghuaurl2[100] = { 0 };
		sprintf(donghuaurl2, "%s00%03d.png", imgurl->getCString(), i);
		thisdonghua->addSpriteFrameWithFileName(donghuaurl2);
	}
	thisdonghua->setDelayPerUnit(3.0f / 18.0f);//执行默认时间
	thisdonghua->setRestoreOriginalFrame(true);
	auto playdonghua = Animate::create(thisdonghua);
	thisdonghua->setLoops(1);

	auto thisdonghua2 = Animation::create();

	for (int i = 0; i <= num2; i++)
	{
		char donghuaurl[100] = { 0 };
		sprintf(donghuaurl, "%s00%03d.png", imgurl2->getCString(), i);
		thisdonghua2->addSpriteFrameWithFileName(donghuaurl);
	}
	thisdonghua2->setDelayPerUnit(2.0f / 18.0f);//执行默认时间
	thisdonghua2->setRestoreOriginalFrame(true);
	auto playdonghua2 = Animate::create(thisdonghua2);
	thisdonghua2->setLoops(1);

	auto thisdonghua3 = Animation::create();

	for (int i = 0; i <= num3; i++)
	{
		char donghuaurl[100] = { 0 };
		sprintf(donghuaurl, "%s00%03d.png", imgurl3->getCString(), i);
		thisdonghua3->addSpriteFrameWithFileName(donghuaurl);
	}
	thisdonghua3->setDelayPerUnit(2.5f / 18.0f);//执行默认时间
	thisdonghua3->setRestoreOriginalFrame(true);
	thisdonghua3->setLoops(1);
	auto playdonghua3 = Animate::create(thisdonghua3);
	auto actbackfun = CallFunc::create(this, callfunc_selector(EffectsCommen::moveoverCallBack_setvisible));
	actall = Sequence::create(playdonghua, playdonghua2, playdonghua3, actbackfun, NULL);
	actall->retain();
	effects_main->runAction(actall);

}
