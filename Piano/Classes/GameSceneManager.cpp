#include "GameSceneManager.h"
#include "LoadLayer.h"
#include "WelcomeLayer.h"
#include "PianoLayer.h"

using namespace cocos2d;

//ʵ��GameSceneManager���е�createScene����
void GameSceneManager::createScene()
{
	//����һ����������
	logoScene = Scene::create();
	//����һ����ӭ��������
	WelcomeLayer* layer = WelcomeLayer::create();
	layer->sceneManager = this;
	//����ӭ������ӵ�������
	logoScene->addChild(layer);
}

void GameSceneManager::goToGameScene()
{
	Director::getInstance()->setDepthTest(true);
	gameScene = Scene::create();
	PianoLayer* layer = PianoLayer::create();
	gameScene->addChild(layer);
	layer->sceneManager = this;
	//�л�����
	Director::getInstance()->replaceScene(gameScene);
}

void GameSceneManager::goToLoadScene()
{
	Director::getInstance()->setDepthTest(true);
	loadScene = Scene::create();
	LoadLayer* layer = LoadLayer::create();
	loadScene->addChild(layer);
	layer->sceneManager = this;
	//�л�����
	Director::getInstance()->replaceScene(loadScene);
}
