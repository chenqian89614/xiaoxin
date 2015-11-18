#include "WarshipsFightSceneManager.h"
#include "StartLayer.h"
#include "ChooseLevelLayer.h"
#include "GameLayer.h"
#include "UpgradeLayer.h"

using namespace cocos2d;

//实现WarshipsFightSceneManager类中的createScene方法
void WarshipsFightSceneManager::createScene()
{
    //创建一个场景对象
	StartScene = Scene::create();
    //创建一个欢迎布景对象
	StartLayer* layer = StartLayer::create();
	layer->wfsm = this;
    //将欢迎布景添加到场景中
	StartScene->addChild(layer);
}
void WarshipsFightSceneManager::goStartScene()
{
	//    设置深度检测
	Director::getInstance()->setDepthTest(false);
    //创建一个场景对象
	StartScene = Scene::create();
    //创建一个欢迎布景对象
	StartLayer* layer = StartLayer::create();
	layer->wfsm = this;
    //将欢迎布景添加到场景中
	StartScene->addChild(layer);
	auto ss=TransitionFade::create(0.5,StartScene);
	Director::getInstance()->replaceScene(ss);
}
void WarshipsFightSceneManager::goChooseLevelScene()
{
	//    设置深度检测
	Director::getInstance()->setDepthTest(false);
	//创建一个场景对象
	ChooseLevelScene = Scene::create();
	//创建一个欢迎布景对象
	ChooseLevelLayer* layer = ChooseLevelLayer::create();
	layer->wfsm = this;
	//将欢迎布景添加到场景中
	ChooseLevelScene->addChild(layer);
	auto ss=TransitionFade::create(0.5,ChooseLevelScene);
	//切换到游戏场景
	Director::getInstance()->replaceScene(ss);
}
void WarshipsFightSceneManager::goGameScene()
{
	//    设置深度检测
	Director::getInstance()->setDepthTest(false);
	//创建一个场景对象
	GameScene = Scene::create();
	//创建一个欢迎布景对象
	GameLayer* layer = GameLayer::create();
	layer->wfsm = this;
	//将欢迎布景添加到场景中
	GameScene->addChild(layer);
	auto ss=TransitionFade::create(0.5, GameScene);
	//    切换到游戏场景
	Director::getInstance()->replaceScene(ss);
}
void WarshipsFightSceneManager::goPpgradeScene()
{
	//    设置深度检测
	Director::getInstance()->setDepthTest(false);
	//创建一个场景对象
	upgradeScene = Scene::create();
	//创建一个欢迎布景对象
	UpgradeLayer* layer = UpgradeLayer::create();
	layer->wfsm = this;
	//将欢迎布景添加到场景中
	upgradeScene->addChild(layer);
	auto ss=TransitionProgressHorizontal::create(0.5, upgradeScene);
	//    切换到游戏场景
	Director::getInstance()->replaceScene(ss);
}
