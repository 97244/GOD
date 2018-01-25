#pragma once
#include "cocos2d.h"

USING_NS_CC;
class LoginScenes : public Layer
{
public:
	LoginScenes(void);
	~LoginScenes(void);
	static Scene*createScene();
	virtual bool init();
	CREATE_FUNC(LoginScenes);

public:
	//背景图片滚动
	void makebd(float num, int w, int tag);
	void movebd(float times);
	void nextCallback(Ref *pSender);
	
public:
	//开始
	void menuStartGame(Ref *pSender);
	//新建
	void menuCreateNewRole(Ref *pSender);
};
