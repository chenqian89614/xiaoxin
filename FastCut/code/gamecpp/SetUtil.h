#ifndef __SetUtil_H__
#define __SetUtil_H__

#include "cocos2d.h"
#include "AppConstant.h"
using namespace std;

static int bgIdx=0;
static int mark1Idx=0;
static int mark2Idx=0;
static Sprite* bgSprite;
static Sprite* round1Marksprite;
static Sprite* round2Marksprite;
static Sprite* createBgSp(int setIdx)//创建背景精灵的方法
{
	switch(setIdx)
	{
	case 0:
		return bgSprite=Sprite::create(levelSetPic_PATH+"set1-2.png");//创建背景精灵对象

	case 1:
		return bgSprite=Sprite::create(levelSetPic_PATH+"set2-2.png");//创建背景精灵对象

	case 2:
		return bgSprite=Sprite::create(levelSetPic_PATH+"set3-2.png");//创建背景精灵对象

	default: break;
	}
	return NULL;
}

static Sprite* createRound1MarkSp(int setIdx)//创建关卡标记精灵的方法
{
	switch(setIdx)
	{
	case 0:
		return round1Marksprite=Sprite::create(levelSetPic_PATH+"s_01_a.png");

	case 1:
		return round1Marksprite=Sprite::create(levelSetPic_PATH+"s_03_a.png");

	case 2:
		return round1Marksprite=Sprite::create(levelSetPic_PATH+"s_05_a.png");


	default: break;
	}
	return NULL;
}

static Sprite* createRound2MarkSp(int setIdx)//创建关卡标记精灵的方法
{
	switch(setIdx)
	{
	case 0:
		return round2Marksprite=Sprite::create(levelSetPic_PATH+"s_02_a.png");

	case 1:
		return round2Marksprite=Sprite::create(levelSetPic_PATH+"s_04_a.png");

	case 2:
		return round2Marksprite=Sprite::create(levelSetPic_PATH+"s_06_a.png");

	default: break;
	}
	return NULL;
}

#endif
