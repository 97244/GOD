#include "Scene_Diyu.h"
#include "ImagePaths.h"

Scene*Scene_Diyu::createScene()
{
	auto scene = Scene::create();
	auto layer = Scene_Diyu::create();
	scene->addChild(layer);
	return scene;
}
Scene_Diyu::Scene_Diyu(void)
{

}


Scene_Diyu::~Scene_Diyu(void)
{
}
bool Scene_Diyu::init()
{
	if (!Layer::init())
	{
		return false;
	}
	float x, y;
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	x = size.width;
	y = size.height;
	//地图
	mainmap = new Maps_Diyu(this, "map_diyu_naihe.jpg", "map_diyu_naihe1.png", 0, ccp(x / 2 - 308, y / 2 - 486));
	mainmap_Touch = mainmap_Touch->create("map_diyu_naihe0.png");
	mainmap_Touch->setimg("map_diyu_naihe0.png");
	mainmap_Touch->setPosition(ccp(x / 2 - 308, y / 2 - 486));
	mainmap_Touch->setVisible(false);//是否显示点击层

	baseui = new BaseUI(this);

	this->addChild(mainmap_Touch, 0);
	setTouchEnabled(true);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Scene_Diyu::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}



bool Scene_Diyu::onTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	
	if (mainmap_Touch->onTouchBegan(/*"map_diyu_naihe0.png",*/ pTouch, pEvent) == true && mainmap->touch_select(pTouch->getLocation()) == false)
	{
		mainmap->moveMapto(pTouch->getLocation(), mainmap_Touch);
	}
	baseui->isTouchInside(pTouch);
	return true;
}

