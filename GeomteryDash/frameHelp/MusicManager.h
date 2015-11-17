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
	static void loadMusic();//���ر�������

	static void resumeBackgroundMusic();//������������
	static void pauseBackgroundMusic();//��ͣ��������


	static void playExplosionEffect();//��ըʱ����Ч
	static void playFlyLayerEffect();//����ؿ�ʱ����Ч
	static void playPauseMenuEffect();//��ͣ�˵��е���˵�ʱ����Ч

	static void playGameLayerMusic();//gameLayer�ı�������
	static void playFlyLayerMusic();//FlyLayer�ı�������
	static void playMenuLayerMusic();//�˵���������

};

#endif
