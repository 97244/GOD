#include "BaseUI.h"
#include "ImagePaths.h"
#include "FontChina.h"
extern bool touch_skill0_flag;

BaseUI::BaseUI(CCLayer* layer)
{
	float center_x, center_y;

	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	center_x = size.width / 2;
	center_y = size.height / 2;

	ui_head = BaseUI::create(HEAD_BD);
	ui_head->setPosition(ccp(ui_head->getContentSize().width - 60, size.height - ui_head->getContentSize().height - 5));
	layer->addChild(ui_head, 1);

	ui_head_xiaoxiao = BaseUI::create(NV_HEAD_XIAOXIAO);
	ui_head_xiaoxiao->setPosition(ccp(ui_head_xiaoxiao->getContentSize().width - 12, size.height - ui_head_xiaoxiao->getContentSize().height - 9));
	layer->addChild(ui_head_xiaoxiao, 1);

	ui_exp = BaseUI::create(EXPBD);
	ui_exp->setPosition(ccp(150, ui_exp->getContentSize().height + 20));
	layer->addChild(ui_exp, 1);

	ui_skillbar = BaseUI::create(SKILL_BAR_BD);
	ui_skillbar->setPosition(ccp(size.width - ui_skillbar->getContentSize().width + 35, ui_skillbar->getContentSize().height));
	layer->addChild(ui_skillbar, 3);

	ui_yaogan = BaseUI::create(YAOGAN_BD);
	ui_yaogan->setPosition(ccp(ui_yaogan->getContentSize().width - 15, ui_yaogan->getContentSize().height + 25));
	layer->addChild(ui_yaogan, 1);


	ui_skill_skill0 = BaseUI::create(SKILL_NV_0);
	ui_skill_skill0->setPosition(ccp(size.width - ui_skill_skill0->getContentSize().width + 7, ui_skill_skill0->getContentSize().height + 22));
	layer->addChild(ui_skill_skill0, 1, 801);

}


CCRect BaseUI::rect_skill0()
{
	//获取精灵区域大小
	return CCRectMake(ui_skill_skill0->getPositionX() - ui_skill_skill0->getContentSize().width  * ui_skill_skill0->getAnchorPoint().x, ui_skill_skill0->getPositionY() - ui_skill_skill0->getContentSize().height* ui_skill_skill0->getAnchorPoint().y, ui_skill_skill0->getContentSize().width, ui_skill_skill0->getContentSize().height);

}

void BaseUI::isTouchInside(CCTouch *pTouch)
{

	CCPoint localPoint = pTouch->getLocation();
	CCRect rc = rect_skill0();
	bool isTouched = rc.containsPoint(localPoint);
	if (isTouched == true) {
		//log(FontChina::G2U("1111111111111111111！"));
		if (touch_skill0_flag != true)
		{
			touch_skill0_flag = true;
		}
	}

}


BaseUI::~BaseUI(void)
{
}
