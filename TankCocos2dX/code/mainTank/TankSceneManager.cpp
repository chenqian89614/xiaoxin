#include "TankSceneManager.h"
#include "WelcomeLayer.h"
#include "MenuLayer.h"
#include "ControlLayer.h"
#include "GameLayer.h"
#include "SoundsetLayer.h"
#include "SelectLayer.h"
#include "PauseLayer.h"
#include "HelpLayer.h"
#include "BNSocketUtil.h"
#include "AppMacros.h"

USING_NS_CC;

//ʵ��WelcomeLayerMangaer���е�createScene����
Scene* TankSceneManager::WelcomeCreate()
{
	//������������
	Scene* scene=Scene::create();
	//������������
	Layer* layer=WelcomeLayer::create();
	//����ӭ������ӵ�������
	scene->addChild(layer);

	return scene;
}

Sprite* TankSceneManager::getGround()
{
	Sprite *groundSprite=Sprite::create(PIC_PATH+std::string("gameBackground.png"));
	groundSprite->setPosition(Point(480,270));
	groundSprite->setScale(1.2f);
	return groundSprite;
}

void TankSceneManager::toMenuLayer()
{
	//������������
	Scene* scene=Scene::create();
	//������������
	Layer* layer=MenuLayer::create();
	//����ӭ������ӵ�������
	scene->addChild(layer);
	//�����л�������Ч
	TransitionFade* tf=TransitionFade::create(0.8f,scene);
	//��ȡ����
	Director *dir=Director::getInstance();
	//�л�����
	dir->replaceScene(tf);
}

void TankSceneManager::toSoundsetLayer()
{
	//������������
	Scene* scene=Scene::create();
	//������������
	Layer* layer=SoundsetLayer::create();
	//����ӭ������ӵ�������
	scene->addChild(layer);
	//�����л�������Ч
	TransitionFadeTR* ftf=TransitionFadeTR::create(0.8f,scene);
	//��ȡ����
	Director *dir=Director::getInstance();
	//�л�����
	dir->replaceScene(ftf);
}

void TankSceneManager::toHelpLayer()
{
	//������������
	Scene* scene=Scene::create();
	//������������
	Layer* layer=HelpLayer::create();
	//����ӭ������ӵ�������
	scene->addChild(layer);
	//�����л�������Ч
	TransitionFadeTR* ftf=TransitionFadeTR::create(0.8f,scene);
	//��ȡ����
	Director *dir=Director::getInstance();
	//�л�����
	dir->replaceScene(ftf);
}

void TankSceneManager::toSelectLayer()
{
	//������������
	Scene* scene=Scene::create();
	//������������
	SelectLayer *selectLayer=SelectLayer::create();
	//����ӭ������ӵ�������
	scene->addChild(selectLayer);
	//�����л�������Ч
	TransitionFadeTR* tf=TransitionFadeTR::create(0.8f,scene);
	//��ȡ����
	Director *dir=Director::getInstance();
	//�л�����
	dir->replaceScene(tf);
}

void TankSceneManager::toGameLayer()
{
	//������������
	Scene* scene=Scene::create();
	//���Ʋ����
	GameLayer *gameLayer=GameLayer::create();
	//���Ʋ����
	ControlLayer *controlLayer=ControlLayer::create();
	//��û��Ʋ������
	controlLayer->getGameLayer(gameLayer);
	//����ӭ������ӵ�������
	scene->addChild(gameLayer, 0, 0);
	scene->addChild(controlLayer, 1, 1);
	//�����л�������Ч
	TransitionFadeTR* ftf=TransitionFadeTR::create(0.8f,scene);
	//��ȡ����
	Director *dir=Director::getInstance();
	//�л�����
	dir->replaceScene(ftf);
}

void TankSceneManager::backMenuLayer()
{
	//������������
	Scene* scene=Scene::create();
	//������������
	Layer* layer=MenuLayer::create();
	//����ӭ������ӵ�������
	scene->addChild(layer);
	//�����л�������Ч
	TransitionFade* tf=TransitionFade::create(0.8f,scene);
	//��ȡ����
	Director *dir=Director::getInstance();
	//�л�����
	dir->replaceScene(tf);
}

