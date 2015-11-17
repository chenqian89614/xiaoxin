#include "GameSceneManager.h"
#include "GameLayer.h"
#include "LevelLayer.h"
#include "MenuLayer.h"
#include "FlyLayer.h"
#include "ChoiceCubeLayer.h"
#include "MusicLayer.h"
#include "../frameHelp/MusicManager.h"


void GameSceneManager::createScene()
{
	MusicManager::loadMusic();//加载背景音乐

	//创建一个场景对象
	Scene* gameScene = Scene::create();
	//创建一个欢迎布景对象
	MenuLayer* layer =  MenuLayer::create();
	layer->gsm = this;
	//将欢迎布景添加到场景中
	gameScene->addChild(layer);

	if(MusicManager::onSound == true)
	{
		MusicManager::playMenuLayerMusic();//播放音乐
	}
	else
	{
		MusicManager::noPlaySound = true;
	}

	Director::getInstance()->runWithScene(gameScene);
}
void GameSceneManager::goMenuLayer()
{
	Director::getInstance()->setDepthTest(true);
	//创建游戏场景
	Scene* MenuScene = Scene::create();

	MenuLayer* layer =  MenuLayer::create();
	layer->gsm = this;
	MenuScene->addChild(layer);

	//替换场景
	Director::getInstance()->replaceScene(MenuScene);//ss
}
void GameSceneManager::goLevelLayer()
{
	Director::getInstance()->setDepthTest(true);
	//创建游戏场景
	Scene* LevelScene = Scene::create();

	LevelLayer* layer =  LevelLayer::create();
	layer->gsm = this;
	LevelScene->addChild(layer);

	//替换场景
	Director::getInstance()->replaceScene(LevelScene);//ss
}
void GameSceneManager::goGameLayer(int index)
{
	Director::getInstance()->setDepthTest(true);
	//创建游戏场景
	Scene* GramScene = Scene::create();

	GameLayer* layer =  GameLayer::create();
	layer->gsm = this;
	layer->indexGK = index;
	GramScene->addChild(layer);

	//替换场景
	Director::getInstance()->replaceScene(GramScene);//ss
}

void GameSceneManager::goFlyLayer()
{
	Director::getInstance()->setDepthTest(true);
	//创建游戏场景
	Scene* sceceTemp = Scene::create();

	FlyLayer* layer = FlyLayer::create();
	layer->gsm = this;
	sceceTemp->addChild(layer);

	//替换场景
	Director::getInstance()->replaceScene(sceceTemp);//ss
}
void GameSceneManager::goMusicLayer()
{
	Director::getInstance()->setDepthTest(true);
	//创建游戏场景
	Scene* sceceTemp = Scene::create();

	MusicLayer* layer = MusicLayer::create();
	layer->gsm = this;
	sceceTemp->addChild(layer);

	//替换场景
	Director::getInstance()->replaceScene(sceceTemp);//ss
}
void GameSceneManager::goChoiceCubeLayer()
{
	Director::getInstance()->setDepthTest(true);
	//创建游戏场景
	Scene* sceceTemp = Scene::create();

	ChoiceCubeLayer* layer = ChoiceCubeLayer::create();
	layer->gsm = this;
	sceceTemp->addChild(layer);

	//替换场景
	Director::getInstance()->replaceScene(sceceTemp);//ss
}
