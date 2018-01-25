#pragma once
#include "cocos2d.h"
USING_NS_CC;
#include "GameMain.h"
#include "LoginScenes.h"
#include "SelectRole.h"
#include "Scene_Diyu.h"
class SceneManager :public Ref
{
public:
	enum EnumSceneType
	{
		en_LoginScene = 1,
		en_SelectRole,
		en_GameMainScene,
		en_Game_DiyuScene,
		en_GameWinScene,
		en_GameOverScene,
	};

	static SceneManager*getInstance();

	virtual bool init();
	void changeScene(EnumSceneType enSceneType);
private:
	static SceneManager* m_SceneManager;
};

