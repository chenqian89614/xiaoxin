#ifndef __WelcomeLayer_H__
#define __WelcomeLayer_H__

#include "cocos2d.h"
#include "GameSceneManager.h"

using namespace cocos2d;

//自定义的布景类
class WelcomeLayer : public cocos2d::Layer
{
public:
	GameSceneManager* gsm;
	static bool playBgM;//背景音乐是否播放过

	//初始化的方法
	virtual bool init();
	//选项菜单回调方法
    void menuChoiceCallback(Object* pSender);
    void menuStartCallback(Object* pSender);//开始菜单回调方法
	void menuHelpCallback(Object* pSender);//帮助菜单回调方法
	void preloadBgMusic();//加载背景 音乐
	void playBgMusic();//播放背景音乐
	void pauseBgMusic();//暂停播放背景音乐
	void resumeBgMusic();//继续播放背景音乐

	void preloadSwitchSound();//加载切换的音效
	void playSwitchSound();//播放切换的音效
	void preloadClickSound();//加载点击的音效
	void playClickSound();//播放嗒点击的音效
	void pauseSound();//暂停播放音效
	void resumeSound();//继续播放音效
	void onExit(Object* pSender);//退出菜单的回调方法
    ~WelcomeLayer();
    //Cocos2d-x中定义的一个宏，创建指定类型的对象
    //并做好相应的初始化与释放工作
    CREATE_FUNC(WelcomeLayer);
};

#endif
