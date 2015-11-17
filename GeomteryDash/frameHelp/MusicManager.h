#ifndef _MusicManager_H_
#define _MusicManager_H_

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

class MusicManager
{
public :
	static bool onSound;
	static bool onEffect;
	static bool noPlaySound;
	static void loadMusic();//加载背景音乐

	static void resumeBackgroundMusic();//继续背景音乐
	static void pauseBackgroundMusic();//暂停背景音乐


	static void playExplosionEffect();//爆炸时的音效
	static void playFlyLayerEffect();//进入关卡时的音效
	static void playPauseMenuEffect();//暂停菜单中点击菜单时的音效

	static void playGameLayerMusic();//gameLayer的背景音乐
	static void playFlyLayerMusic();//FlyLayer的背景音乐
	static void playMenuLayerMusic();//菜单背景音乐

};

#endif
