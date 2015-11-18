#include "GameSceneManager.h"
#include "BeginLayer.h"
#include "HelpLayer.h"
#include "ChooseLayer.h"
#include "AchieveLayer.h"
#include "GameLayer.h"
#include "OpenLayer.h"


using namespace cocos2d;

//ʵ��GameSceneManager���е�createScene����
Scene* GameSceneManager::createScene()
{
    //����һ����������
	Scene *scene = Scene::create();
	OpenLayer *layer = OpenLayer::create();
    //����ӭ������ӵ�������
    scene->addChild(layer);
    //���س���
    return scene;
}

//�л���������
void GameSceneManager::toBeginLayer()
{
	//��ȡDirector�����ݣ�
	Director* pDirector = Director::sharedDirector();
	pDirector -> setDepthTest(true);
	Scene* toGameLayerSence = Scene::create();
	BeginLayer *layer = BeginLayer::create();
	toGameLayerSence->addChild(layer);
	TransitionScene* ccts= TransitionFadeTR::create(1.0f, toGameLayerSence);
	//ִ���л�
	Director::sharedDirector()->replaceScene(ccts);
}

//�л���ѡ�ؽ���
void GameSceneManager::toChooseLayer()
{
	//��ȡDirector�����ݣ�
	Director* pDirector = Director::sharedDirector();
	pDirector -> setDepthTest(true);
	Scene* toGameLayerSence = Scene::create();
	ChooseLayer *layer = ChooseLayer::create();
	toGameLayerSence->addChild(layer);
	TransitionScene* ccts= TransitionFadeTR::create(1.0f, toGameLayerSence);
	//ִ���л�
	Director::sharedDirector()->replaceScene(ccts);
}

//�л���helplayer
void GameSceneManager::toHelpLayer()
{
	//��ȡDirector�����ݣ�
	Director* pDirector = Director::sharedDirector();
	pDirector -> setDepthTest(true);
	Scene* toGameLayerSence = Scene::create();
	HelpLayer *layer = HelpLayer::create();
	toGameLayerSence->addChild(layer);
	TransitionScene* ccts= TransitionFadeTR::create(1.0f, toGameLayerSence);
	//ִ���л�
	Director::sharedDirector()->replaceScene(ccts);
}

//�л�����߷�
void GameSceneManager::toAchieveLayer()
{
	//��ȡDirector�����ݣ�
	Director* pDirector = Director::sharedDirector();
	pDirector -> setDepthTest(true);
	Scene* toGameLayerSence = Scene::create();
	AchieveLayer *layer = AchieveLayer::create();
	//layer->man = this;
	toGameLayerSence->addChild(layer);
	TransitionScene* ccts= TransitionFadeTR::create(1.0f, toGameLayerSence);
	//ִ���л�
	Director::sharedDirector()->replaceScene(ccts);
}

//�л�����Ϸ����
void GameSceneManager::toGameLayer()
{
	//��ȡDirector�����ݣ�
	Director* pDirector = Director::sharedDirector();
	pDirector -> setDepthTest(true);
	Scene* toGameLayerSence = Scene::create();
	GameLayer *layer = GameLayer::create();
	toGameLayerSence->addChild(layer);
	TransitionScene* ccts= TransitionFadeTR::create(1.0f, toGameLayerSence);
	//ִ���л�
	Director::sharedDirector()->replaceScene(ccts);
}
