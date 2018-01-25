#pragma once
#include "GetNPCData.h"
//第一章故事进度
extern int storyplayflag_caozuo = 0;
//第一章故事进度
extern int storyplayflag = 0;
extern GetNPCData* basedatas = new GetNPCData();

extern bool touch_skill0_flag = false;

extern bool nowselect = false;
class bianl
{
public:

	bianl(void)
	{
	}

	virtual ~bianl(void)
	{
	}
};