#include "GameMain.h"
#include "PublicCommen.h"
#include "ImagePaths.h"
#include "SceneManager.h"
extern int storyplayflag_caozuo;
Scene *GameMain::createScene()
{
	auto scene = Scene::create();
	auto lyaer = GameMain::create();
	scene->addChild(lyaer);
	return scene;
}
bool GameMain::init()
{
	bool isRet = false;
	do 
	{
		CC_BREAK_IF(!Layer::init());
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Point origin = Director::getInstance()->getVisibleOrigin();

		map_y = visibleSize.height / 2;
		map_x = visibleSize.width / 2;

		mainmap = new MapsBase(this, "map_shengjie.jpg", 0, ccp(map_x, map_y - 66));
		mainmap->autorelease();
		mainmap->retain();
		mainmap_Touch = mainmap_Touch->create("map_shengjie0.png");
		mainmap_Touch->setimg("map_shengjie0.png");
		mainmap_Touch->autorelease();
		mainmap_Touch->retain();
		Size size = Director::getInstance()->getWinSize();
		mainmap_Touch->setPosition(ccp(map_x, map_y - 66));
		mainmap_Touch->setVisible(false);//是否显示点击层
		this->addChild(mainmap_Touch, 0);

		float map_fornpc_x, map_fornpc_y;
		map_fornpc_x = mainmap->nowmap->getContentSize().width / 2;
		map_fornpc_y = mainmap->nowmap->getContentSize().height / 2;
		//故事里面的NPC列表
		npclist = Array::createWithCapacity(4);
		//故事NPC
		GetNPCData npcdata = GetNPCData();
		npcdata.GetNPCchapter1();
		npcdata.role_taiyizhengren.dir = rigth_down;
		auto npc_taiyizhengren1 = new SpiritsPlayer(npcdata.role_taiyizhengren, 0, false);
		npcdata.role_taishanglaojun.dir = rigth_down;
		auto npc_taishanglaojun1 = new SpiritsPlayer(npcdata.role_taishanglaojun, 0, false);
		npcdata.role_chijiaodaxian.dir = rigth_down;
		auto npc_chijiaodaxian1 = new SpiritsPlayer(npcdata.role_chijiaodaxian, 0, false);
		npcdata.role_qingxuzhenjun.dir = rigth_down;
		auto npc_qingxunzhenjun1 = new SpiritsPlayer(npcdata.role_qingxuzhenjun, 0, false);
		npcdata.role_player.dir = rigth_down;
		auto npc_zhujiao = new SpiritsPlayer(npcdata.role_player, 0, false);
		npc_zhujiao->autorelease();
		npc_zhujiao->retain();

		npclist->addObject(npc_taiyizhengren1->npc);
		npclist->addObject(npc_taishanglaojun1->npc);
		npclist->addObject(npc_chijiaodaxian1->npc);
		npclist->addObject(npc_qingxunzhenjun1->npc);
		npclist->addObject(npc_zhujiao->npc);


		String* strpart1 = String::create("stroytxt/part1.txt");

		//读取文件
		string stroy_part1 = PublicCommen::getFileByName(strpart1->getCString());

		vector<string> talkstroynum = PublicCommen::split(stroy_part1, "\n");
		vector<string> talkstroynum_list;
		auto talkstroy_name = Array::createWithCapacity(talkstroynum.size());
		auto talkstroy_npcflag = Array::createWithCapacity(talkstroynum.size());
		auto talkstroy_about = Array::createWithCapacity(talkstroynum.size());
		auto talkstroy_todo = Array::createWithCapacity(talkstroynum.size());
		auto talkstroy_progress = Array::createWithCapacity(talkstroynum.size());
		for (int i = 0; i < talkstroynum.size(); i++)
		{
			talkstroynum_list = PublicCommen::split(talkstroynum.at(i), "@");
			talkstroy_name->addObject(String::create(talkstroynum_list.at(0)));
			talkstroy_npcflag->addObject(String::create(talkstroynum_list.at(1)));
			talkstroy_about->addObject(String::create(talkstroynum_list.at(2)));
			talkstroy_todo->addObject(String::create(talkstroynum_list.at(3)));
			talkstroy_progress->addObject(String::create(talkstroynum_list.at(4)));
		}

		//故事对话框
		storyTips_part1 = new TipsForStory(this, Vec2(map_x, map_y), String::create(STORY_TIP_BD), 2, npclist, talkstroy_name, talkstroy_npcflag, talkstroy_about, talkstroy_todo, talkstroy_progress);
		storyTips_part1->autorelease();
		storyTips_part1->retain();
		//启动定时器监听事件
		this->schedule(schedule_selector(GameMain::storyplaydataflag), 1.0f);

		auto item1 = MenuItemImage::create(JS_CHAT_BG, JS_CHAT_BG_0, this, menu_selector(GameMain::GoToCcene));
		item1->setPosition(ccp(visibleSize.width / 2 + 220, visibleSize.height / 2 + 150));
		auto menu = Menu::create(item1, NULL);
		menu->setPosition(Vec2::ZERO);
		this->addChild(menu, 0);

		//开启点击事件
		setTouchEnabled(true);

		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = CC_CALLBACK_2(GameMain::onTouchBegan, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
		isRet = true;

	} while (0);

	return true;
}

void GameMain::storyplaydataflag(float times)
{
	if (storyplayflag_caozuo == 1)
	{
		String* strpart2 = String::create("stroytxt/part2.txt");

		string url = strpart2->getCString();
		//读取文件
		string stroy_part1 = PublicCommen::getFileByName(url);

		vector<string> talkstroynum = PublicCommen::split(stroy_part1, "\n");
		vector<string> talkstroynum_list;
		auto talkstroy_name = Array::createWithCapacity(talkstroynum.size());
		auto talkstroy_npcflag = Array::createWithCapacity(talkstroynum.size());
		auto talkstroy_about = Array::createWithCapacity(talkstroynum.size());
		auto talkstroy_todo = Array::createWithCapacity(talkstroynum.size());
		auto talkstroy_progress = Array::createWithCapacity(talkstroynum.size());
		for (int i = 0; i < talkstroynum.size(); i++)
		{
			talkstroynum_list = PublicCommen::split(talkstroynum.at(i), "@");
			talkstroy_name->addObject(CCString::create(talkstroynum_list.at(0)));
			talkstroy_npcflag->addObject(CCString::create(talkstroynum_list.at(1)));
			talkstroy_about->addObject(CCString::create(talkstroynum_list.at(2)));
			talkstroy_todo->addObject(CCString::create(talkstroynum_list.at(3)));
			talkstroy_progress->addObject(CCString::create(talkstroynum_list.at(4)));
		}

		//故事对话框
		storyTips_part2 = new TipsForStory(this, Vec2(map_x, map_y), String::create(STORY_TIP_BD), 2, npclist, talkstroy_name, talkstroy_npcflag, talkstroy_about, talkstroy_todo, talkstroy_progress);
		storyTips_part2->autorelease();
		storyTips_part2->retain();
		storyplayflag_caozuo = -1;
	}
	else if (storyplayflag_caozuo == 2)
	{
		SceneManager::getInstance()->changeScene(SceneManager::en_Game_DiyuScene);
		storyplayflag_caozuo = -1;
	}
}

void GameMain::GoToCcene(Ref* pSender)
{
	SceneManager::getInstance()->changeScene(SceneManager::en_Game_DiyuScene);
}

bool GameMain::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	if (mainmap_Touch->onTouchBegan(/*"map_shengjie0.png",*/ pTouch, pEvent) == true)
	{
		mainmap->moveMapto(pTouch->getLocation(), mainmap_Touch);
	}
	return true;
}
