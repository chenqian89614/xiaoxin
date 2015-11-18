#ifndef __ChoiceLayer_H__
#define __ChoiceLayer_H__
#include "cocos2d.h"
#include "GameSceneManager.h"
#include "WelcomeLayer.h"

using namespace cocos2d;
class ChoiceLayer : public cocos2d::Layer
{
public :
	GameSceneManager* gsm;
	Sprite* bgSprite;//背景精灵
	Sprite* dibanSprite;//底板精灵
	Sprite* music;//音乐精灵
	Sprite* sound;//声音精灵
	static bool isMusic;//是否播放音乐标志位
	static bool isSound;//是否播放音效标志位
    static int escChoiceCount;//记录按下返回键的次数

	WelcomeLayer* wl;//欢迎界面的指针
	//初始化的方法
	virtual bool init();
	bool controlMusic(Touch* touch,Event* event);//控制声音开关的方法

	void onBack();//返回菜单的回调方法
	~ChoiceLayer();
	//Cocos2d-x中定义的一个宏，创建指定类型的对象
	//并做好相应的初始化与释放工作
	CREATE_FUNC(ChoiceLayer);
};

#endif
