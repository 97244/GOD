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
	//����ͼƬ����
	void makebd(float num, int w, int tag);
	void movebd(float times);
	void nextCallback(Ref *pSender);
	
public:
	//��ʼ
	void menuStartGame(Ref *pSender);
	//�½�
	void menuCreateNewRole(Ref *pSender);
};
