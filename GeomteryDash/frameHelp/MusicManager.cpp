#include "MusicManager.h"

bool MusicManager::onSound = true;
bool MusicManager::onEffect = true;
bool MusicManager::noPlaySound = false;

void MusicManager::loadMusic()
{
	onEffect = UserDefault::getInstance()->getBoolForKey("5",true);
	onSound = UserDefault::getInstance()->getBoolForKey("6",true);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(
							"sound/BackOnTrack.mp3"					//���ر�������
						);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(
							"sound/menuLoop.mp3"					//���ر�������
						);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(
							"sound/CantLetGo.mp3"					//���ر�������
						);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(				//������Ч
				"sound/explode_11.ogg"
			);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(				//������Ч
				"sound/playSound_01.ogg"
			);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(				//������Ч
				"sound/quitSound_01.ogg"
			);
}

void MusicManager::resumeBackgroundMusic()//������������
{
	onSound = true;
	UserDefault::getInstance()->setBoolForKey("6", onSound);
	UserDefault::getInstance()->flush();
	//������������
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	return;
}
void MusicManager::pauseBackgroundMusic()//��ͣ��������
{
	onSound = false;
	UserDefault::getInstance()->setBoolForKey("6", onSound);
	UserDefault::getInstance()->flush();
	//��ͣ��������
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	return;
}

void MusicManager::playExplosionEffect()//��Ч
{
	if(onEffect == false)
	{
		return;
	}
	//��ͣ��������
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/explode_11.ogg");	//������Ч
	return;
}
void MusicManager::playFlyLayerEffect()//����ؿ�ʱ����Ч
{
	if(onEffect == false)
	{
		return;
	}
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/playSound_01.ogg");	//������Ч
	return;
}
void MusicManager::playPauseMenuEffect()//��ͣ�˵��е���˵�ʱ����Ч
{
	if(onEffect == false)
	{
		return;
	}
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/quitSound_01.ogg");	//������Ч
	return;
}
void MusicManager::playMenuLayerMusic()//�˵���������
{
	if(onSound == false)
	{
		return;
	}
	//���ű�������
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic
	(
		"sound/menuLoop.mp3",
		true
	);
	return;
}
void MusicManager::playGameLayerMusic()
{
	if(onSound == false)
	{
		return;
	}
	//���ű�������
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic
	(
		"sound/BackOnTrack.mp3",
		true
	);
	return;

}
void MusicManager::playFlyLayerMusic()//FlyLayer�ı�������
{
	if(onSound == false)
	{
		return;
	}
	//���ű�������
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic
	(
		"sound/CantLetGo.mp3",
		true
	);
	return;
}
