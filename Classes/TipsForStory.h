#pragma once
#include "cocos2d.h"
#include "ImagePaths.h"
#include "EffectsCommen.h"
USING_NS_CC;

class TipsForStory :public cocos2d::CCSprite
{
public:
	int nowflag;
	bool overtodoflag;
	CCSprite* story_tip;
	CCActionInterval* act_move_storytip;

	TipsForStory(CCLayer* layer, CCPoint basepoint, CCString* imgurl, int zOrder, CCArray* npclist, CCArray* talkstroy_name, CCArray* talkstroy_npcflag, CCArray* talkstroy_about, CCArray* talkstroy_todo, CCArray* talkstroy_progress);


	~TipsForStory(void);

	void addStroys(int nowid, int zOrder);
	void totobutton(CCObject* pSender);


private:
	CCArray* this_npclist;
	CCArray* this_talkstroy_name;
	CCArray* this_talkstroy_npcflag;
	CCArray* this_talkstroy_about;
	CCArray* this_talkstroy_todo;
	CCArray* this_talkstroy_progress;

	EffectsCommen* eff_shownpc1;
	EffectsCommen* eff_shownpc;
	EffectsCommen* eff_shownpc3;

};