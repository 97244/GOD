#pragma once
#include "cocos2d.h"  
#include <vector>
USING_NS_CC;

class PublicShowUI
{
public:
	PublicShowUI(void);
	~PublicShowUI(void);

	Label* label;
	Label* labelback;
	Array* p_ui_talkabout;
	Array* p_ui_talkabout_back;
	/** °×µ×ºÚ±ß **/
	void setGameText(Layer* layer, String* str, Point cp, int size);

	/** ¶Ô»°ÄÚÈÝ **/
	void setGameTalkAbout(Layer* layer, Point cp, int size, Array *stringArray, int zindex);

	void updataGameText(Point cp);
	void moveGameText(bool endflag, int uestime, Point newpoint);
	//void movetGameTalkAbout(CCLayer* layer,bool endflag,int uestime,CCPoint newpoint);

private:
	ActionInterval* act_moveto_label;
	ActionInterval* act_moveto_labelback;
};