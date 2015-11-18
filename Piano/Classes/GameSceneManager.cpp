#include "GameSceneManager.h"
#include "LoadLayer.h"
#include "WelcomeLayer.h"
#include "PianoLayer.h"

using namespace cocos2d;

//实现GameSceneManager类中的createScene方法
void GameSceneManager::createScene()
{
	//创建一个场景对象
	logoScene = Scene::create();
	//创建一个欢迎布景对象
	WelcomeLayer* layer = WelcomeLayer::create();
	layer->sceneManager = this;
	//将欢迎布景添加到场景中
	logoScene->addChild(layer);
}

void GameSceneManager::goToGameScene()
{
	Director::getInstance()->setDepthTest(true);
	gameScene = Scene::create();
	PianoLayer* layer = PianoLayer::create();
	gameScene->addChild(layer);
	layer->sceneManager = this;
	//切换场景
	Director::getInstance()->replaceScene(gameScene);
}

void GameSceneManager::goToLoadScene()
{
	Director::getInstance()->setDepthTest(true);
	loadScene = Scene::create();
	LoadLayer* layer = LoadLayer::create();
	loadScene->addChild(layer);
	layer->sceneManager = this;
	//切换场景
	Director::getInstance()->replaceScene(loadScene);
}
