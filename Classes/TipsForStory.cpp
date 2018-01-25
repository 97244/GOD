#include "TipsForStory.h"
#include "GetNPCData.h"
#include "SpiritsPlayer.h"
#include "FontChina.h"
#include "bianl.h"//È«¾Ö±äÁ¿
extern int storyplayflag;


TipsForStory::TipsForStory(CCLayer* layer, CCPoint basepoint, CCString* imgurl, int zOrder, CCArray* npclist, CCArray* talkstroy_name, CCArray* talkstroy_npcflag, CCArray* talkstroy_about, CCArray* talkstroy_todo, CCArray* talkstroy_progress)
{

	overtodoflag = false;
	this_npclist = npclist;
	this_npclist->retain();
	this_talkstroy_name = talkstroy_name;
	this_talkstroy_name->retain();
	this_talkstroy_npcflag = talkstroy_npcflag;
	this_talkstroy_npcflag->retain();
	this_talkstroy_about = talkstroy_about;
	this_talkstroy_about->retain();
	this_talkstroy_todo = talkstroy_todo;
	this_talkstroy_todo->retain();
	this_talkstroy_progress = talkstroy_progress;
	this_talkstroy_progress->retain();


	float center_x, center_y;

	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	center_x = size.width / 2;
	center_y = size.height / 2;


	act_move_storytip = NULL;
	story_tip = TipsForStory::create(imgurl->getCString());
	story_tip->setPosition(basepoint);

	if (story_tip == NULL)
	{
		log("Í¼²ãÂ·¾¶ÓÐÎó£¬Çë¼ì²éÂ·¾¶");
		return;
	}

	int maxlist = talkstroy_about->count();
	nowflag = 0;

	if (maxlist > 0)
	{
		addStroys(nowflag, zOrder);
	}

	layer->addChild(story_tip, zOrder);
}

void TipsForStory::addStroys(int nowid, int zOrder)
{
	CCString* playnpcflag = (CCString*)this_talkstroy_npcflag->objectAtIndex(nowflag);
	CCSprite * thisnpc = (CCSprite *)(this_npclist->objectAtIndex(playnpcflag->intValue()));

	CCLabelTTF* thisnpcname_label = (CCLabelTTF*)thisnpc->getChildByTag(111);
	CCString* thisnpcname_str = CCString::create(thisnpcname_label->getString());
	thisnpc->setPosition(ccp(story_tip->getContentSize().width / 2 - 150, story_tip->getContentSize().height / 2 - 9));
	thisnpc->getChildByTag(111)->setVisible(false);
	thisnpc->getChildByTag(112)->setVisible(false);
	story_tip->addChild(thisnpc, zOrder + 1, 001);

	CCString* thisnpcname = (CCString*)this_talkstroy_name->objectAtIndex(nowflag);
	//NPCÃû³Æ
	CCLabelTTF* name_label = CCLabelTTF::create(FontChina::G2U(thisnpcname->getCString()), "Î¢ÈíÑÅºÚ", 12);
	name_label->setColor(Color3B::YELLOW);
	//name_label->setDirty(true);
	name_label->setHorizontalAlignment(kCCTextAlignmentLeft);
	name_label->setDimensions(CCSizeMake(120, 50));
	name_label->setPosition(ccp(90, 95));

	CCLabelTTF* name_label2 = CCLabelTTF::create(FontChina::G2U(thisnpcname->getCString()), "Î¢ÈíÑÅºÚ", 12);
	name_label2->setColor(Color3B::BLACK);
	//name_label2->setDirty(true);
	name_label2->setHorizontalAlignment(kCCTextAlignmentLeft);
	name_label2->setDimensions(CCSizeMake(120, 50));
	name_label2->setPosition(ccp(90 + 1, 95 - 1));
	story_tip->addChild(name_label, zOrder + 4, 128);
	story_tip->addChild(name_label2, zOrder + 3, 129);

	//Ëµ»°ÄÚÈÝ
	CCString* nowabout = (CCString*)(this_talkstroy_about->objectAtIndex(nowflag));
	CCLabelTTF* newlabels = CCLabelTTF::create(FontChina::G2U(nowabout->getCString()), "Î¢ÈíÑÅºÚ", 12);
	newlabels->setColor(Color3B::WHITE);
	//newlabels->setDirty(true);
	newlabels->setHorizontalAlignment(kCCTextAlignmentLeft);
	newlabels->setDimensions(CCSizeMake(290, 200));
	newlabels->setPosition(ccp(220, -7));

	CCLabelTTF* newlabels2 = CCLabelTTF::create(FontChina::G2U(nowabout->getCString()), "Î¢ÈíÑÅºÚ", 12);
	newlabels2->setColor(Color3B::BLACK);
	//newlabels2->setDirty(true);
	newlabels2->setHorizontalAlignment(kCCTextAlignmentLeft);
	newlabels2->setDimensions(CCSizeMake(290, 200));
	newlabels2->setPosition(ccp(220 - 1, -7 - 1));
	story_tip->addChild(newlabels, zOrder + 2, 100 + 1);
	story_tip->addChild(newlabels2, zOrder + 1, 200 + 1);

	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
		"butbd.png",
		"butbd.png",
		this,
		menu_selector(TipsForStory::totobutton));

	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition(315, 32);
	story_tip->addChild(pMenu, zOrder + 5, 300);

	CCString* thisnpctodo = (CCString*)this_talkstroy_todo->objectAtIndex(nowflag);
	//µã»÷ÊÂ¼þ
	CCLabelTTF* todo_label = CCLabelTTF::create(FontChina::G2U(thisnpctodo->getCString()), "Î¢ÈíÑÅºÚ", 10);
	todo_label->setColor(Color3B::YELLOW);
	//todo_label->setDirty(true);
	todo_label->setHorizontalAlignment(kCCTextAlignmentLeft);
	todo_label->setDimensions(CCSizeMake(120, 50));
	todo_label->setPosition(ccp(365, 15));

	CCLabelTTF* todo_label2 = CCLabelTTF::create(FontChina::G2U(thisnpctodo->getCString()), "Î¢ÈíÑÅºÚ", 10);
	todo_label2->setColor(Color3B::BLACK);
	//todo_label2->setDirty(true);
	todo_label2->setHorizontalAlignment(kCCTextAlignmentLeft);
	todo_label2->setDimensions(CCSizeMake(120, 50));
	todo_label2->setPosition(ccp(365 + 1, 15 - 1));
	story_tip->addChild(todo_label, zOrder + 6, 138);
	story_tip->addChild(todo_label2, zOrder + 5, 139);

}
void TipsForStory::totobutton(CCObject* pSender)
{
	CCString* thistodo = (CCString*)this_talkstroy_todo->objectAtIndex(nowflag);

	if (thistodo->isEqual(CCString::create("µã»÷¼ÌÐø")))
	{
		nowflag++;
		if (nowflag > 0)
		{
			story_tip->removeAllChildren();
			addStroys(nowflag, 114);
		}
	}
	else if (thistodo->isEqual(CCString::create("¶Ô»°Íê³É")))
	{
		story_tip->removeAllChildren();
		story_tip->setVisible(false);
		story_tip->retain();
		CCString* thistprogress = (CCString*)this_talkstroy_progress->objectAtIndex(nowflag);
		storyplayflag = thistprogress->intValue();
	}
}


TipsForStory::~TipsForStory(void)
{

}
