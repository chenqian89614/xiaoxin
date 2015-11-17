#include "MusicManager.h"

bool MusicManager::onSound = true;
bool MusicManager::onEffect = true;
bool MusicManager::noPlaySound = false;

void MusicManager::loadMusic()
{
	onEffect = UserDefault::getInstance()->getBoolForKey("5",true);
	onSound = UserDefault::getInstance()->getBoolForKey("6",true);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(
							"sound/BackOnTrack.mp3"					//¼ÓÔØ±³¾°ÒôÀÖ
						);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(
							"sound/menuLoop.mp3"					//¼ÓÔØ±³¾°ÒôÀÖ
						);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(
							"sound/CantLetGo.mp3"					//¼ÓÔØ±³¾°ÒôÀÖ
						);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(				//¼ÓÔØÒôÐ§
				"sound/explode_11.ogg"
			);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(				//¼ÓÔØÒôÐ§
				"sound/playSound_01.ogg"
			);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(				//¼ÓÔØÒôÐ§
				"sound/quitSound_01.ogg"
			);
}

void MusicManager::resumeBackgroundMusic()//¼ÌÐø±³¾°ÒôÀÖ
{
	onSound = true;
	UserDefault::getInstance()->setBoolForKey("6", onSound);
	UserDefault::getInstance()->flush();
	//¼ÌÐø±³¾°ÒôÀÖ
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	return;
}
void MusicManager::pauseBackgroundMusic()//ÔÝÍ£±³¾°ÒôÀÖ
{
	onSound = false;
	UserDefault::getInstance()->setBoolForKey("6", onSound);
	UserDefault::getInstance()->flush();
	//ÔÝÍ£±³¾°ÒôÀÖ
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	return;
}

void MusicManager::playExplosionEffect()//ÒôÐ§
{
	if(onEffect == false)
	{
		return;
	}
	//ÔÝÍ£±³¾°ÒôÀÖ
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/explode_11.ogg");	//²¥·ÅÒôÐ§
	return;
}
void MusicManager::playFlyLayerEffect()//½øÈë¹Ø¿¨Ê±µÄÒôÐ§
{
	if(onEffect == false)
	{
		return;
	}
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/playSound_01.ogg");	//²¥·ÅÒôÐ§
	return;
}
void MusicManager::playPauseMenuEffect()//ÔÝÍ£²Ëµ¥ÖÐµã»÷²Ëµ¥Ê±µÄÒôÐ§
{
	if(onEffect == false)
	{
		return;
	}
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/quitSound_01.ogg");	//²¥·ÅÒôÐ§
	return;
}
void MusicManager::playMenuLayerMusic()//²Ëµ¥±³¾°ÒôÀÖ
{
	if(onSound == false)
	{
		return;
	}
	//²¥·Å±³¾°ÒôÀÖ
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
	//²¥·Å±³¾°ÒôÀÖ
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic
	(
		"sound/BackOnTrack.mp3",
		true
	);
	return;

}
void MusicManager::playFlyLayerMusic()//FlyLayerµÄ±³¾°ÒôÀÖ
{
	if(onSound == false)
	{
		return;
	}
	//²¥·Å±³¾°ÒôÀÖ
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic
	(
		"sound/CantLetGo.mp3",
		true
	);
	return;
}
