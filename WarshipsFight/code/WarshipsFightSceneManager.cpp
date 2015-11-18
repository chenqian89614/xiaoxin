#include "WarshipsFightSceneManager.h"
#include "StartLayer.h"
#include "ChooseLevelLayer.h"
#include "GameLayer.h"
#include "UpgradeLayer.h"

using namespace cocos2d;

//ʵ��WarshipsFightSceneManager���е�createScene����
void WarshipsFightSceneManager::createScene()
{
    //����һ����������
	StartScene = Scene::create();
    //����һ����ӭ��������
	StartLayer* layer = StartLayer::create();
	layer->wfsm = this;
    //����ӭ������ӵ�������
	StartScene->addChild(layer);
}
void WarshipsFightSceneManager::goStartScene()
{
	//    ������ȼ��
	Director::getInstance()->setDepthTest(false);
    //����һ����������
	StartScene = Scene::create();
    //����һ����ӭ��������
	StartLayer* layer = StartLayer::create();
	layer->wfsm = this;
    //����ӭ������ӵ�������
	StartScene->addChild(layer);
	auto ss=TransitionFade::create(0.5,StartScene);
	Director::getInstance()->replaceScene(ss);
}
void WarshipsFightSceneManager::goChooseLevelScene()
{
	//    ������ȼ��
	Director::getInstance()->setDepthTest(false);
	//����һ����������
	ChooseLevelScene = Scene::create();
	//����һ����ӭ��������
	ChooseLevelLayer* layer = ChooseLevelLayer::create();
	layer->wfsm = this;
	//����ӭ������ӵ�������
	ChooseLevelScene->addChild(layer);
	auto ss=TransitionFade::create(0.5,ChooseLevelScene);
	//�л�����Ϸ����
	Director::getInstance()->replaceScene(ss);
}
void WarshipsFightSceneManager::goGameScene()
{
	//    ������ȼ��
	Director::getInstance()->setDepthTest(false);
	//����һ����������
	GameScene = Scene::create();
	//����һ����ӭ��������
	GameLayer* layer = GameLayer::create();
	layer->wfsm = this;
	//����ӭ������ӵ�������
	GameScene->addChild(layer);
	auto ss=TransitionFade::create(0.5, GameScene);
	//    �л�����Ϸ����
	Director::getInstance()->replaceScene(ss);
}
void WarshipsFightSceneManager::goPpgradeScene()
{
	//    ������ȼ��
	Director::getInstance()->setDepthTest(false);
	//����һ����������
	upgradeScene = Scene::create();
	//����һ����ӭ��������
	UpgradeLayer* layer = UpgradeLayer::create();
	layer->wfsm = this;
	//����ӭ������ӵ�������
	upgradeScene->addChild(layer);
	auto ss=TransitionProgressHorizontal::create(0.5, upgradeScene);
	//    �л�����Ϸ����
	Director::getInstance()->replaceScene(ss);
}
