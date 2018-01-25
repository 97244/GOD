#include "LoginScenes.h"
#include "ImagePaths.h"
#include "EffectsCommen.h"
#include "SceneManager.h"
LoginScenes::LoginScenes(void)
{

}

LoginScenes::~LoginScenes(void)
{

}

Scene* LoginScenes::createScene()
{
	auto scene = Scene::create();
	auto layer = LoginScenes::create();
	scene->addChild(layer);
	return scene;
}

bool LoginScenes::init()
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

	auto background_navbd = Sprite::create(LOGIN_BD1);
	background_navbd->setPosition(ccp(x / 2, y / 2 - 70));
	auto ui_logo = Sprite::create(LOGIN_LOGO);
	ui_logo->setPosition(ccp(x / 2, y / 2 + 50));
	
	auto cj1 = new EffectsCommen(ccp(x / 2 + 50, y / 2 + 100), EFF_CJ_1, 4.5f, 28, 0, 5);
	cj1->autorelease();
	cj1->retain();
	auto cj2 = new EffectsCommen(ccp(x / 2, y / 2), EFF_CJ_2, 5.5f, 29, 0, 5);
	cj2->autorelease();
	cj2->retain();
	auto cj3 = new EffectsCommen(ccp(x / 2 - 60, y / 2 - 70), EFF_CJ_4, 5.0f, 29, 0, 5);
	cj3->autorelease();
	cj3->retain();
	auto scale_actby = ScaleBy::create(2.0f, 3.0f);
	auto animation = Sequence::create(scale_actby, scale_actby->reverse(), NULL);
	cj1->effects_main->runAction(RepeatForever::create(animation));
	this->addChild(cj1->effects_main, 105);
	this->addChild(cj2->effects_main, 106);
	this->addChild(cj3->effects_main, 107);
	
	auto p_ui_login_start = MenuItemImage::create(
		"login_start.png",
		"login_start0.png",
		this,
		menu_selector(LoginScenes::menuStartGame));
	auto pMenu = Menu::create(p_ui_login_start, NULL);
	pMenu->setPosition(ccp(x / 2 - 40, y / 2 - 70));
	this->addChild(pMenu, 102);
	auto p_ui_login_newrole = MenuItemImage::create(
		"login_newrole.png",
		"login_newrole0.png",
		this,
		menu_selector(LoginScenes::menuCreateNewRole));
	auto pMenu2 = Menu::create(p_ui_login_newrole, NULL);
	pMenu2->setPosition(ccp(x / 2 + 40, y / 2 - 100));
	this->addChild(pMenu2, 103);

	this->addChild(background_navbd, 100);
	this->addChild(ui_logo, 101);
	this->makebd(0, 0, 99);
	this->makebd(1, 0, 98);
	this->schedule(schedule_selector(LoginScenes::movebd));
}


//新建
void LoginScenes::menuCreateNewRole(Ref *pSender)
{
	SceneManager::getInstance()->changeScene(SceneManager::en_SelectRole);
}

//开始
void LoginScenes::menuStartGame(Ref *pSender)
{
	SceneManager::getInstance()->changeScene(SceneManager::en_GameMainScene);
}

void LoginScenes::makebd(float num, int w, int tag)
{
	float x, y;
	Point origin = Director::getInstance()->getVisibleOrigin();
	Size size = Director::getInstance()->getWinSize();
	x = size.width;
	y = size.height + origin.y;

	auto background = Sprite::create(LOGIN_ALLBD);
	background->setAnchorPoint(CCPoint(0, 0.5));
	background->setPosition(Point(background->getContentSize().width*num + w, y / 2));
	this->addChild(background, tag, tag);
}

void LoginScenes::movebd(float times)
{
	float x, y;
	Point origin = Director::getInstance()->getVisibleOrigin();
	Size size = Director::getInstance()->getWinSize();
	x = size.width;
	y = size.height + origin.y;

	auto bg1 = Node::getChildByTag(99);
	auto sp1 = (Sprite*)bg1;

	auto bg2 = Node::getChildByTag(98);
	auto sp2 = (Sprite*)bg2;
	sp1->setPosition(Point(sp1->getPositionX() - 0.5, sp1->getPositionY()));
	sp2->setPosition(Point(sp2->getPositionX() - 0.5, sp2->getPositionY()));
	if (sp1->getPositionX() <= -sp1->getContentSize().width)
	{
		sp1->setPosition(Point(sp1->getContentSize().width, y / 2));
	}
	if (sp2->getPositionX() <= -sp2->getContentSize().width)
	{
		sp2->setPosition(Point(sp2->getContentSize().width, y / 2));
	}
}
