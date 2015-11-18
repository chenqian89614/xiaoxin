#include "PokerSceneManager.h"
#include "WelcomeLayer.h"
#include "GameLayer.h"
#include "AppMacros.h"
#include "Constant.h"
#include "AboutLayer.h"
#include "HelpLayer.h"
#include <string>
#include "SimpleAudioEngine.h"

//USING_NS_CC;
using namespace cocos2d;

void PokerSceneManager::createScene()
{
	firstScene = Scene::create();
	WelcomeLayer* layer = WelcomeLayer::create();
	layer->psm = this;
	firstScene->addChild(layer);
}
void PokerSceneManager::goWelcome()
{
	if(Constant::effectFlag)
	{
		playEffect();
	}
	Director::getInstance()->setDepthTest(true);
	welScene = Scene::create();
	WelcomeLayer* layer = WelcomeLayer::create();
	layer->psm = this;
	welScene->addChild(layer);
	//ÏòÓÒ
	auto ss = TransitionMoveInR::create(0.5, welScene);
	//Ìæ»»³¡¾°
	Director::getInstance()->replaceScene(ss);
}
void PokerSceneManager::goGame()
{
	if(Constant::effectFlag)
	{
		playEffect();
	}
	Director::getInstance()->setDepthTest(true);
	gameScene = Scene::create();
	GameLayer* layer = GameLayer::create();
	layer->psm = this;
	gameScene->addChild(layer);
	//ÏòÓÒ
	auto ss = TransitionMoveInL::create(0.5, gameScene);
	//Ìæ»»³¡¾°
	Director::getInstance()->replaceScene(ss);
}
void PokerSceneManager::goAbout()
{
	if(Constant::effectFlag)
	{
		playEffect();
	}
	Director::getInstance()->setDepthTest(true);
	aboutScene = Scene::create();
	AboutLayer* layer = AboutLayer::create();
	layer->psm = this;
	aboutScene->addChild(layer);
	//ÏòÓÒ
	auto ss = TransitionMoveInL::create(0.2, aboutScene);
	//Ìæ»»³¡¾°
	Director::getInstance()->replaceScene(ss);
}

void PokerSceneManager::goHelp()
{
	if(Constant::effectFlag)
	{
		playEffect();
	}
	Director::getInstance()->setDepthTest(true);
	helpScene=Scene::create();
	HelpLayer* layer=HelpLayer::create();
	layer->psm=this;
	helpScene->addChild(layer);

	auto ss=TransitionMoveInL::create(0.2,helpScene);

	Director::getInstance()->replaceScene(ss);
}
void PokerSceneManager::playEffect()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.9);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
		(SOUND_PATH+std::string("cancel.mp3")).c_str()
	);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
	(
		(SOUND_PATH+std::string("cancel.mp3")).c_str()
	);
}

