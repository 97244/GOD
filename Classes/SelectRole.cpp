#include "SelectRole.h"
#include "ImagePaths.h"
#include "EffectsCommen.h"
#include "FontChina.h"
#include "SceneManager.h"
#define FONT_NAME                       "Thonburi"
#define FONT_SIZE                       36

SelectRole::SelectRole(void)
{

}

SelectRole::~SelectRole(void)
{

}

Scene * SelectRole::createScene()
{
	auto scene = Scene::create();
	auto layer = SelectRole::create();
	scene->addChild(layer);
	return scene;
}
bool SelectRole::init()
{
	if (!Layer::init())
	{
		return false;
	}

	float x, y;
	Point origin = Director::getInstance()->getVisibleOrigin();
	Size size = Director::getInstance()->getWinSize();
	x = size.width;
	y = size.height + origin.y;

	auto background_navbd = Sprite::create(SELECT_ROLE_BD);
	background_navbd->setPosition(ccp(x / 2, y / 2));

	auto move_l = MoveBy::create(1.5f, ccp(75, 0));
	auto move_r = MoveBy::create(1.5f, ccp(-75, 0));
	auto move_l0 = MoveBy::create(1.5f, ccp(75, 0));
	auto move_r0 = MoveBy::create(1.5f, ccp(-75, 0));
	auto fade_act1 = FadeOut::create(1.0f);
	auto fade_act2 = FadeOut::create(1.0f);
	auto rolebd_nan = Sprite::create(SELECT_ROLE_NAN);
	rolebd_nan->setPosition(ccp(x / 2 + 60, y / 2));
	rolebd_nan->runAction(move_l0);
	auto rolebd_nv = Sprite::create(SELECT_ROLE_NV);
	rolebd_nv->setPosition(ccp(x / 2 - 60, y / 2));
	rolebd_nv->runAction(move_r0);


	auto rolebd_nan0 = Sprite::create(SELECT_ROLE_NAN_0);
	rolebd_nan0->setPosition(ccp(x / 2 + 60, y / 2));
	rolebd_nan0->runAction(Sequence::create(move_l, fade_act1, NULL));

	auto rolebd_nv0 = Sprite::create(SELECT_ROLE_NV_0);
	rolebd_nv0->setPosition(ccp(x / 2 - 60, y / 2));
	rolebd_nv0->runAction(Sequence::create(move_r, fade_act2, NULL));

	auto csj1 = new EffectsCommen(ccp(x / 2, y / 2 - 50), EFF_Sll, 4, 39, 0, 5);
	csj1->autorelease();
	csj1->retain();
	auto scale_actby1 = ScaleBy::create(1.5f, 0.35f);
	auto scale_actby = ScaleBy::create(1.5f, 0.7f);
	csj1->effects_main->runAction(Sequence::create(scale_actby1, scale_actby->reverse(), NULL));


	this->addChild(csj1->effects_main, 3, 1990);
	this->addChild(background_navbd, 1, 10);
	this->addChild(rolebd_nan, 2, 11);
	this->addChild(rolebd_nv, 2, 12);
	this->addChild(rolebd_nan0, 2, 111);
	this->addChild(rolebd_nv0, 2, 122);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(SelectRole::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	setTouchEnabled(true);
	return true;

}



Rect SelectRole::rect(Sprite* tack)
{
	//获取精灵区域大小
	return Rect(tack->getPositionX() - tack->getContentSize().width  * tack->getAnchorPoint().x, tack->getPositionY() - tack->getContentSize().height* tack->getAnchorPoint().y, tack->getContentSize().width, tack->getContentSize().height);
}


bool SelectRole::isTouchInside_nan(Point thisPos, Sprite* tack)
{
	Point localPos = thisPos;
	Rect rc = rect(tack);
	bool isTouched = rc.containsPoint(localPos);
	if (isTouched == true) {
		auto fade_act = FadeIn::create(1.0f);
		this->getChildByTag(111)->runAction(fade_act);
		this->getChildByTag(111)->setVisible(true);
		this->getChildByTag(11)->setVisible(false);
		this->getChildByTag(122)->setVisible(false);
		this->getChildByTag(12)->setVisible(true);
		SceneManager::getInstance()->changeScene(SceneManager::en_GameMainScene);
	}
	else
	{
	}
	return isTouched;
}
bool SelectRole::isTouchInside_nv(Point thisPos, Sprite* tack)
{
	Point localPos = thisPos;
	Rect rc = rect(tack);
	bool isTouched = rc.containsPoint(localPos);
	if (isTouched == true) {
		auto fade_act = FadeIn::create(1.0f);
		this->getChildByTag(122)->runAction(fade_act);
		this->getChildByTag(122)->setVisible(true);
		this->getChildByTag(111)->setVisible(false);
		this->getChildByTag(12)->setVisible(false);
		this->getChildByTag(11)->setVisible(true);
		auto scene = GameMain::createScene();
		SceneManager::getInstance()->changeScene(SceneManager::en_GameMainScene);
	}
	else
	{
	}
	return isTouched;
}



bool SelectRole::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	isTouchInside_nan(pTouch->getLocation(), (Sprite*)this->getChildByTag(11));
	isTouchInside_nv(pTouch->getLocation(), (Sprite*)this->getChildByTag(12));
	return true;
}
