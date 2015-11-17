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
	MusicManager::loadMusic();//���ر�������

	//����һ����������
	Scene* gameScene = Scene::create();
	//����һ����ӭ��������
	MenuLayer* layer =  MenuLayer::create();
	layer->gsm = this;
	//����ӭ������ӵ�������
	gameScene->addChild(layer);

	if(MusicManager::onSound == true)
	{
		MusicManager::playMenuLayerMusic();//��������
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
	//������Ϸ����
	Scene* MenuScene = Scene::create();

	MenuLayer* layer =  MenuLayer::create();
	layer->gsm = this;
	MenuScene->addChild(layer);

	//�滻����
	Director::getInstance()->replaceScene(MenuScene);//ss
}
void GameSceneManager::goLevelLayer()
{
	Director::getInstance()->setDepthTest(true);
	//������Ϸ����
	Scene* LevelScene = Scene::create();

	LevelLayer* layer =  LevelLayer::create();
	layer->gsm = this;
	LevelScene->addChild(layer);

	//�滻����
	Director::getInstance()->replaceScene(LevelScene);//ss
}
void GameSceneManager::goGameLayer(int index)
{
	Director::getInstance()->setDepthTest(true);
	//������Ϸ����
	Scene* GramScene = Scene::create();

	GameLayer* layer =  GameLayer::create();
	layer->gsm = this;
	layer->indexGK = index;
	GramScene->addChild(layer);

	//�滻����
	Director::getInstance()->replaceScene(GramScene);//ss
}

void GameSceneManager::goFlyLayer()
{
	Director::getInstance()->setDepthTest(true);
	//������Ϸ����
	Scene* sceceTemp = Scene::create();

	FlyLayer* layer = FlyLayer::create();
	layer->gsm = this;
	sceceTemp->addChild(layer);

	//�滻����
	Director::getInstance()->replaceScene(sceceTemp);//ss
}
void GameSceneManager::goMusicLayer()
{
	Director::getInstance()->setDepthTest(true);
	//������Ϸ����
	Scene* sceceTemp = Scene::create();

	MusicLayer* layer = MusicLayer::create();
	layer->gsm = this;
	sceceTemp->addChild(layer);

	//�滻����
	Director::getInstance()->replaceScene(sceceTemp);//ss
}
void GameSceneManager::goChoiceCubeLayer()
{
	Director::getInstance()->setDepthTest(true);
	//������Ϸ����
	Scene* sceceTemp = Scene::create();

	ChoiceCubeLayer* layer = ChoiceCubeLayer::create();
	layer->gsm = this;
	sceceTemp->addChild(layer);

	//�滻����
	Director::getInstance()->replaceScene(sceceTemp);//ss
}
