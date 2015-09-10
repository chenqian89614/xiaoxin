#include "GameMusic.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"

USING_NS_CC;

GameMusic* GameMusic::_instance = nullptr;
GameMusic* GameMusic::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new GameMusic();

	}

	return _instance;
}

void GameMusic::prepare()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Arround World-World.mp3");
}


void GameMusic::playmusic()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Arround World-World.mp3", true);
}

GameMusic::~GameMusic()
{
	if (_instance != nullptr)
	{
		delete _instance;
		_instance = nullptr;
	}
}