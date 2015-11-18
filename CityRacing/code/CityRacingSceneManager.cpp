#include "CityRacingSceneManager.h"
#include "StartLayer.h"
#include "ChooseCarLayer.h"
#include "GameLayer.h"
#include "ChooseLevelLayer.h"
#include "ShopLayer.h"
#include "GameOverLayer.h"
#include "PHBLayer.h"
#include "HelpLayer.h"

using namespace cocos2d;
//ʵ��CityRacingSceneManager���е�createScene����
Scene* CityRacingSceneManager::createScene()
{
    //����һ����������
    auto scene = Scene::create();
    //����һ����ӭ��������
    StartLayer* layer = StartLayer::create();
    layer->crsm=this;
    //����ӭ������ӵ�������
    scene->addChild(layer);
    //���س���
    return scene;
}
void CityRacingSceneManager::goStartLyaer()
{
    //����һ����������
	startScene = Scene::create();
    //����һ����ӭ��������
    auto layer = StartLayer::create();
    layer->crsm=this;
    //����ӭ������ӵ�������
    startScene->addChild(layer);
    //����һ���л���������Ч
    auto ss=TransitionProgressInOut::create(0.5, startScene);
    //�л�����Ϸ����
    Director::getInstance()->replaceScene(ss);
}
void CityRacingSceneManager::goChooseCarLayer()
{
	//����һ����������
	chooseCarscene = Scene::create();
	//����һ����ӭ��������
	auto layer = ChooseCarLayer::create();
	layer->crsm=this;
	//����ӭ������ӵ�������
	chooseCarscene->addChild(layer);
	//����һ���л���������Ч
	auto ss=TransitionProgressInOut::create(0.5,chooseCarscene);
	//�л�����Ϸ����
	Director::getInstance()->replaceScene(ss);
}
void CityRacingSceneManager::goGameLayer()
{
	//����һ����������
	gameScene = Scene::create();
	//����һ����ӭ��������
	auto layer = GameLayer::create();
	layer->crsm=this;
	//����ӭ������ӵ�������
	gameScene->addChild(layer);
	//����һ���л���������Ч
	auto ss=TransitionProgressInOut::create(0.5,gameScene);
	//�л�����Ϸ����
	Director::getInstance()->replaceScene(ss);
}
void CityRacingSceneManager::goMainLayer()
{
	//����һ����������
	mainScene = Scene::create();
	//����һ����ӭ��������
	auto layer = StartLayer::create();
	layer->crsm=this;
	//����ӭ������ӵ�������
	mainScene->addChild(layer);
	//����һ���л���������Ч
	auto ss=TransitionProgressInOut::create(0.5,mainScene);
	//�л�����Ϸ����
	Director::getInstance()->replaceScene(ss);
}
void CityRacingSceneManager::goChooseLevelLayer()
{
	//����һ����������
	levelScene = Scene::create();
	//����һ����ӭ��������
	auto layer = ChooseLevelLayer::create();
	layer->crsm=this;
	//����ӭ������ӵ�������
	levelScene->addChild(layer);
	//����һ���л���������Ч
	auto ss=TransitionProgressInOut::create(0.5,levelScene);
	//�л�����Ϸ����
	Director::getInstance()->replaceScene(ss);
}
void CityRacingSceneManager::goShopLayer()
{
	//����һ����������
	shopScene = Scene::create();
	//����һ����ӭ��������
	auto layer = ShopLayer::create();
	layer->crsm=this;
	//����ӭ������ӵ�������
	shopScene->addChild(layer);
	//����һ���л���������Ч
	auto ss=TransitionProgressInOut::create(0.5,shopScene);
	//�л�����Ϸ����
	Director::getInstance()->replaceScene(ss);
}
void CityRacingSceneManager::goGameOverLayer()
{
	//����һ����������
	gameOverSceen = Scene::create();
	//����һ����ӭ��������
	auto layer = GameOverLayer::create();
	layer->crsm=this;
	//����ӭ������ӵ�������
	gameOverSceen->addChild(layer);
	//����һ���л���������Ч
	auto ss=TransitionProgressInOut::create(0.5,gameOverSceen);
	//�л�����Ϸ����
	Director::getInstance()->replaceScene(ss);
}
void CityRacingSceneManager::goPHBLayer()
{
	//����һ����������
	PHBScene = Scene::create();
	//����һ����ӭ��������
	auto layer = PHBLayer::create();
	layer->crsm=this;
	//����ӭ������ӵ�������
	PHBScene->addChild(layer);
	//����һ���л���������Ч
	auto ss=TransitionProgressInOut::create(0.5,PHBScene);
	//�л�����Ϸ����
	Director::getInstance()->replaceScene(ss);
}
void CityRacingSceneManager::goHelpLayer()
{
	//����һ����������
	helpScene = Scene::create();
	//����һ����ӭ��������
	auto layer = HelpLayer::create();
	layer->crsm=this;
	//����ӭ������ӵ�������
	helpScene->addChild(layer);
	//����һ���л���������Ч
	auto ss=TransitionFade::create(0.5,helpScene);
	//�л�����Ϸ����
	Director::getInstance()->replaceScene(ss);
}
