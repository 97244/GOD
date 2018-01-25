#pragma once
#include "cocos2d.h"
#include "MapsBase.h"
#include "FDPixelSprite.h"
#include "TipsForStory.h"
USING_NS_CC;

class GameMain :public Layer {
public:
	virtual bool init();
	static Scene*createScene();
	CREATE_FUNC(GameMain);
private:
	MapsBase* mainmap;
	FDPixelSprite* mainmap_Touch;
	float map_x, map_y;
	//���¶Ի���
	TipsForStory* storyTips_part1;
	TipsForStory* storyTips_part2;
	//���������NPC�б�
	Array* npclist;
public:
	virtual void GoToCcene(Ref *pSender);
	//����¼�����
	void nextCallback(Ref *pSender);
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	void storyplaydataflag(float times);
};