#include "GetNPCData.h"
#include "FontChina.h"
CCString* player;
CCString* player_zhan;
CCString* player_pao;
CCString* player_attack;


CCString* npcpath_taiyizhenren;
CCString* npcpath_taiyizhenren_zhan;

CCString* npcpath_taishanglaojun;
CCString* npcpath_taishanglaojun_zhan;

CCString* npcpath_chijiaodaxian;
CCString* npcpath_chijiaodaxian_zhan;

CCString* npcpath_qingxuzhenjun;
CCString* npcpath_qingxuzhenjun_zhan;

CCString* npcpath_mengpo;
CCString* npcpath_mengpo_zhan;

//************************************怪物列表*******************************************//

CCString* monsterpath_xixuebianfu;
CCString* monsterpath_xixuebianfu_zhan;

CCString* monsterpath_kongjumo;
CCString* monsterpath_kongjumo_zhan;
CCString* monsterpath_kongjumo_pao;
CCString* monsterpath_kongjumo_attck;

CCString* monsterpath_qitiandasheng;
CCString* monsterpath_qitiandasheng_zhan;
CCString* monsterpath_qitiandasheng_pao;
CCString* monsterpath_qitiandasheng_attck;

GetNPCData::GetNPCData()
{

	npcpath_taiyizhenren = CCString::create("/npc/xianren/1952-ca3334ff-00000.png");
	npcpath_taiyizhenren_zhan = CCString::create("/npc/xianren/1952-ca3334ff-");

	npcpath_taishanglaojun = CCString::create("/npc/taishanglaojun/0533-3599d5c3-00000.png");
	npcpath_taishanglaojun_zhan = CCString::create("/npc/taishanglaojun/0533-3599d5c3-");

	npcpath_chijiaodaxian = CCString::create("/npc/chijiaodaxian/0329-2073f650-00000.png");
	npcpath_chijiaodaxian_zhan = CCString::create("/npc/chijiaodaxian/0329-2073f650-");

	npcpath_qingxuzhenjun = CCString::create("/npc/qingxuzhenjun/0352-22406e66-00000.png");
	npcpath_qingxuzhenjun_zhan = CCString::create("/npc/qingxuzhenjun/0352-22406e66-");

	npcpath_mengpo = CCString::create("/npc/mengpo/1118-70357245-00000.png");
	npcpath_mengpo_zhan = CCString::create("/npc/mengpo/1118-70357245-");

	/******************************************怪物列表*********************************************/

	monsterpath_xixuebianfu = CCString::create("/monster/xixuebianfu/0968-60b2e461-00000.png");
	monsterpath_xixuebianfu_zhan = CCString::create("/monster/xixuebianfu/0968-60b2e461-");

	monsterpath_kongjumo = CCString::create("/monster/kongjumo/zhan/2010-d117595b-00000.png");
	monsterpath_kongjumo_zhan = CCString::create("/monster/kongjumo/zhan/2010-d117595b-");
	monsterpath_kongjumo_pao = CCString::create("/monster/kongjumo/pao/1004-6579bfb5-");
	monsterpath_kongjumo_attck = CCString::create("/monster/kongjumo/attck/1881-c1b24bac-");

	monsterpath_qitiandasheng = CCString::create("/monster/wukong/zhan/0192-14692807-00000.png");
	monsterpath_qitiandasheng_zhan = CCString::create("/monster/wukong/zhan/0192-14692807-");
	monsterpath_qitiandasheng_pao = CCString::create("/monster/wukong/pao/0448-2c4d8ec8-");
	monsterpath_qitiandasheng_attck = CCString::create("/monster/wukong/attck/1067-6c1336ec-");

	/******************************************主角列表*********************************************/

	player = CCString::create("/zhujiao_nv2/zhan/2145-dfb3d729-00000.png");
	player_zhan = CCString::create("/zhujiao_nv2/zhan/2145-dfb3d729-");
	player_pao = CCString::create("/zhujiao_nv2/pao/2262-edbc3127-");
	player_attack = CCString::create("/zhujiao_nv2/attck/0290-1d7090b8-");


	//屌炸天的小明
	role_player.spiritname = CCString::create(FontChina::G2U("紫秀青衣"));
	role_player.spiritUrl = player;
	role_player.spiritUrl_zhan = player_zhan;
	role_player.maxcut_zhan = 6;
	role_player.spiritUrl_pao = player_pao;
	role_player.maxcut_pao = 7;
	role_player.spiritUrl_attack = player_attack;
	role_player.maxcut_attack = 18;
	role_player.dir = left_down;
	role_player.acttodo = stand;
	role_player.actiontime = 2.5f;


}


GetNPCData::~GetNPCData(void)
{
}

void GetNPCData::GetNPCchapter1()
{



	role_taiyizhengren.spiritname = CCString::create(FontChina::G2U("太乙真人"));
	role_taiyizhengren.spiritUrl = npcpath_taiyizhenren;
	role_taiyizhengren.spiritUrl_zhan = npcpath_taiyizhenren_zhan;
	role_taiyizhengren.maxcut_zhan = 9;
	role_taiyizhengren.spiritUrl_pao = NULL;
	role_taiyizhengren.maxcut_pao = 0;
	role_taiyizhengren.spiritUrl_attack = NULL;
	role_taiyizhengren.maxcut_attack = 0;
	role_taiyizhengren.dir = rigth_down;
	role_taiyizhengren.acttodo = stand;
	role_taiyizhengren.actiontime = 2.6f;

	role_taishanglaojun.spiritname = CCString::create(FontChina::G2U("太上老君"));
	role_taishanglaojun.spiritUrl = npcpath_taishanglaojun;
	role_taishanglaojun.spiritUrl_zhan = npcpath_taishanglaojun_zhan;
	role_taishanglaojun.maxcut_zhan = 8;
	role_taishanglaojun.spiritUrl_pao = NULL;
	role_taishanglaojun.maxcut_pao = 0;
	role_taishanglaojun.spiritUrl_attack = NULL;
	role_taishanglaojun.maxcut_attack = 0;
	role_taishanglaojun.dir = left_down;
	role_taishanglaojun.acttodo = stand;
	role_taishanglaojun.actiontime = 2.5f;

	role_chijiaodaxian.spiritname = CCString::create(FontChina::G2U("赤脚大仙"));
	role_chijiaodaxian.spiritUrl = npcpath_chijiaodaxian;
	role_chijiaodaxian.spiritUrl_zhan = npcpath_chijiaodaxian_zhan;
	role_chijiaodaxian.maxcut_zhan = 8;
	role_chijiaodaxian.spiritUrl_pao = NULL;
	role_chijiaodaxian.maxcut_pao = 0;
	role_chijiaodaxian.spiritUrl_attack = NULL;
	role_chijiaodaxian.maxcut_attack = 0;
	role_chijiaodaxian.dir = rigth_down;
	role_chijiaodaxian.acttodo = stand;
	role_chijiaodaxian.actiontime = 2.5f;

	role_qingxuzhenjun.spiritname = CCString::create(FontChina::G2U("玉鼎真君"));
	role_qingxuzhenjun.spiritUrl = npcpath_qingxuzhenjun;
	role_qingxuzhenjun.spiritUrl_zhan = npcpath_qingxuzhenjun_zhan;
	role_qingxuzhenjun.maxcut_zhan = 12;
	role_qingxuzhenjun.spiritUrl_pao = NULL;
	role_qingxuzhenjun.maxcut_pao = 0;
	role_qingxuzhenjun.spiritUrl_attack = NULL;
	role_qingxuzhenjun.maxcut_attack = 0;
	role_qingxuzhenjun.dir = left_down;
	role_qingxuzhenjun.acttodo = stand;
	role_qingxuzhenjun.actiontime = 3.0f;

	role_mengpo.spiritname = CCString::create(FontChina::G2U("孟婆"));
	role_mengpo.spiritUrl = npcpath_mengpo;
	role_mengpo.spiritUrl_zhan = npcpath_mengpo_zhan;
	role_mengpo.maxcut_zhan = 8;
	role_mengpo.spiritUrl_pao = NULL;
	role_mengpo.maxcut_pao = 0;
	role_mengpo.spiritUrl_attack = NULL;
	role_mengpo.maxcut_attack = 0;
	role_mengpo.dir = rigth_down;
	role_mengpo.acttodo = stand;
	role_mengpo.actiontime = 3.0f;

}



void GetNPCData::GetMonsterchapter1()
{

	monster_xixuebianfu.spiritname = CCString::create(FontChina::G2U("吸血蝙蝠"));
	monster_xixuebianfu.spiritUrl = monsterpath_xixuebianfu;
	monster_xixuebianfu.spiritUrl_zhan = monsterpath_xixuebianfu_zhan;
	monster_xixuebianfu.maxcut_zhan = 6;
	monster_xixuebianfu.spiritUrl_pao = monsterpath_xixuebianfu_zhan;
	monster_xixuebianfu.maxcut_pao = 6;
	monster_xixuebianfu.spiritUrl_attack = monsterpath_xixuebianfu_zhan;
	monster_xixuebianfu.maxcut_attack = 6;
	monster_xixuebianfu.dir = left_down;
	monster_xixuebianfu.acttodo = stand;
	monster_xixuebianfu.actiontime = 2.0f;

	monster_kongjumo.spiritname = CCString::create(FontChina::G2U("恐惧魔"));
	monster_kongjumo.spiritUrl = monsterpath_kongjumo;
	monster_kongjumo.spiritUrl_zhan = monsterpath_kongjumo_zhan;
	monster_kongjumo.maxcut_zhan = 9;
	monster_kongjumo.spiritUrl_pao = monsterpath_kongjumo_pao;
	monster_kongjumo.maxcut_pao = 8;
	monster_kongjumo.spiritUrl_attack = monsterpath_kongjumo_attck;
	monster_kongjumo.maxcut_attack = 11;
	monster_kongjumo.dir = left_down;
	monster_kongjumo.acttodo = stand;
	monster_kongjumo.actiontime = 2.0f;

	monster_qitiandasheng.spiritname = CCString::create(FontChina::G2U("子龙山人"));
	monster_qitiandasheng.spiritUrl = monsterpath_qitiandasheng;
	monster_qitiandasheng.spiritUrl_zhan = monsterpath_qitiandasheng_zhan;
	monster_qitiandasheng.maxcut_zhan = 9;
	monster_qitiandasheng.spiritUrl_pao = monsterpath_qitiandasheng_pao;
	monster_qitiandasheng.maxcut_pao = 7;
	monster_qitiandasheng.spiritUrl_attack = monsterpath_qitiandasheng_attck;
	monster_qitiandasheng.maxcut_attack = 12;
	monster_qitiandasheng.dir = left_down;
	monster_qitiandasheng.acttodo = stand;
	monster_qitiandasheng.actiontime = 2.0f;
}
