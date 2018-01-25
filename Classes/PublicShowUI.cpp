#include "PublicShowUI.h"


PublicShowUI::PublicShowUI(void)
{
	//³õÊ¼»¯
	act_moveto_label = NULL;
	act_moveto_labelback = NULL;

}


PublicShowUI::~PublicShowUI(void)
{
}

void PublicShowUI::setGameText(Layer* layer, String* str, Point cp, int size)
{
	label = Label::create(str->getCString(), "Î¢ÈíÑÅºÚ", size);
	label->setColor(Color3B::WHITE);
	//label->setDirty(true);
	label->setPosition(ccp(cp.x, cp.y));
	layer->addChild(label, 4);
	labelback = Label::create(str->getCString(), "Î¢ÈíÑÅºÚ", size);
	labelback->setColor(Color3B::BLACK);
	//labelback->setDirty(true);
	labelback->setPosition(ccp(cp.x + 1, cp.y - 1));
	layer->addChild(labelback, 3);
}
void PublicShowUI::setGameTalkAbout(Layer* layer, Point cp, int size, Array *stringArray, int zindex)
{
	p_ui_talkabout = new Array();
	p_ui_talkabout_back = new Array();
	if (stringArray->count() > 0)
	{
		int j = stringArray->count() - 1;
		for (int i = 0; i < stringArray->count(); i++)
		{

			String* strthis = (String *)stringArray->objectAtIndex(i);
			CCLabelTTF* newlabels = CCLabelTTF::create(strthis->getCString(), "Î¢ÈíÑÅºÚ", size);
			newlabels->setColor(Color3B::WHITE);
			//newlabels->setDirty(true);
			newlabels->setPosition(ccp(cp.x, cp.y + j * 20));
			p_ui_talkabout->addObject(newlabels);
			CCLabelTTF* newlabels2 = CCLabelTTF::create(strthis->getCString(), "Î¢ÈíÑÅºÚ", size);
			newlabels2->setColor(Color3B::BLACK);
			//newlabels2->setDirty(true);
			newlabels2->setPosition(ccp(cp.x + 1, cp.y + 1 + j * 20));
			p_ui_talkabout_back->addObject(newlabels2);
			j--;

		}
	}

	if (p_ui_talkabout->count() > 0)
	{
		for (int i = 0; i < p_ui_talkabout->count(); i++)
		{
			layer->addChild((CCLabelTTF *)p_ui_talkabout->objectAtIndex(i), zindex + 1);
			layer->addChild((CCLabelTTF *)p_ui_talkabout_back->objectAtIndex(i), zindex);

		}
	}
}

void PublicShowUI::updataGameText(Point cp)
{
	label->setPosition(ccp(cp.x, cp.y));
	labelback->setPosition(ccp(cp.x + 1, cp.y - 1));
}



void PublicShowUI::moveGameText(bool endflag, int uestime, Point newpoint)
{
	log("______wwwwwwwwwwwwwwwwwwwwww_______");


	label->stopAction(act_moveto_label);
	labelback->stopAction(act_moveto_labelback);

	act_moveto_label = MoveTo::create(uestime, newpoint);
	act_moveto_label->retain();
	act_moveto_labelback = MoveTo::create(uestime, ccp(newpoint.x + 1, newpoint.y - 1));
	act_moveto_labelback->retain();
	label->runAction(act_moveto_label);
	labelback->runAction(act_moveto_labelback);
	log("______++++++++++++++++++++++_______");
}
