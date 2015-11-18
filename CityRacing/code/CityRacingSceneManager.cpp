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
//实现CityRacingSceneManager类中的createScene方法
Scene* CityRacingSceneManager::createScene()
{
    //创建一个场景对象
    auto scene = Scene::create();
    //创建一个欢迎布景对象
    StartLayer* layer = StartLayer::create();
    layer->crsm=this;
    //将欢迎布景添加到场景中
    scene->addChild(layer);
    //返回场景
    return scene;
}
void CityRacingSceneManager::goStartLyaer()
{
    //创建一个场景对象
	startScene = Scene::create();
    //创建一个欢迎布景对象
    auto layer = StartLayer::create();
    layer->crsm=this;
    //将欢迎布景添加到场景中
    startScene->addChild(layer);
    //创建一个切换场景到特效
    auto ss=TransitionProgressInOut::create(0.5, startScene);
    //切换到游戏场景
    Director::getInstance()->replaceScene(ss);
}
void CityRacingSceneManager::goChooseCarLayer()
{
	//创建一个场景对象
	chooseCarscene = Scene::create();
	//创建一个欢迎布景对象
	auto layer = ChooseCarLayer::create();
	layer->crsm=this;
	//将欢迎布景添加到场景中
	chooseCarscene->addChild(layer);
	//创建一个切换场景到特效
	auto ss=TransitionProgressInOut::create(0.5,chooseCarscene);
	//切换到游戏场景
	Director::getInstance()->replaceScene(ss);
}
void CityRacingSceneManager::goGameLayer()
{
	//创建一个场景对象
	gameScene = Scene::create();
	//创建一个欢迎布景对象
	auto layer = GameLayer::create();
	layer->crsm=this;
	//将欢迎布景添加到场景中
	gameScene->addChild(layer);
	//创建一个切换场景到特效
	auto ss=TransitionProgressInOut::create(0.5,gameScene);
	//切换到游戏场景
	Director::getInstance()->replaceScene(ss);
}
void CityRacingSceneManager::goMainLayer()
{
	//创建一个场景对象
	mainScene = Scene::create();
	//创建一个欢迎布景对象
	auto layer = StartLayer::create();
	layer->crsm=this;
	//将欢迎布景添加到场景中
	mainScene->addChild(layer);
	//创建一个切换场景到特效
	auto ss=TransitionProgressInOut::create(0.5,mainScene);
	//切换到游戏场景
	Director::getInstance()->replaceScene(ss);
}
void CityRacingSceneManager::goChooseLevelLayer()
{
	//创建一个场景对象
	levelScene = Scene::create();
	//创建一个欢迎布景对象
	auto layer = ChooseLevelLayer::create();
	layer->crsm=this;
	//将欢迎布景添加到场景中
	levelScene->addChild(layer);
	//创建一个切换场景到特效
	auto ss=TransitionProgressInOut::create(0.5,levelScene);
	//切换到游戏场景
	Director::getInstance()->replaceScene(ss);
}
void CityRacingSceneManager::goShopLayer()
{
	//创建一个场景对象
	shopScene = Scene::create();
	//创建一个欢迎布景对象
	auto layer = ShopLayer::create();
	layer->crsm=this;
	//将欢迎布景添加到场景中
	shopScene->addChild(layer);
	//创建一个切换场景到特效
	auto ss=TransitionProgressInOut::create(0.5,shopScene);
	//切换到游戏场景
	Director::getInstance()->replaceScene(ss);
}
void CityRacingSceneManager::goGameOverLayer()
{
	//创建一个场景对象
	gameOverSceen = Scene::create();
	//创建一个欢迎布景对象
	auto layer = GameOverLayer::create();
	layer->crsm=this;
	//将欢迎布景添加到场景中
	gameOverSceen->addChild(layer);
	//创建一个切换场景到特效
	auto ss=TransitionProgressInOut::create(0.5,gameOverSceen);
	//切换到游戏场景
	Director::getInstance()->replaceScene(ss);
}
void CityRacingSceneManager::goPHBLayer()
{
	//创建一个场景对象
	PHBScene = Scene::create();
	//创建一个欢迎布景对象
	auto layer = PHBLayer::create();
	layer->crsm=this;
	//将欢迎布景添加到场景中
	PHBScene->addChild(layer);
	//创建一个切换场景到特效
	auto ss=TransitionProgressInOut::create(0.5,PHBScene);
	//切换到游戏场景
	Director::getInstance()->replaceScene(ss);
}
void CityRacingSceneManager::goHelpLayer()
{
	//创建一个场景对象
	helpScene = Scene::create();
	//创建一个欢迎布景对象
	auto layer = HelpLayer::create();
	layer->crsm=this;
	//将欢迎布景添加到场景中
	helpScene->addChild(layer);
	//创建一个切换场景到特效
	auto ss=TransitionFade::create(0.5,helpScene);
	//切换到游戏场景
	Director::getInstance()->replaceScene(ss);
}
