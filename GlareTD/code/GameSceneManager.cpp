#include "GameSceneManager.h"
#include "BeginLayer.h"
#include "HelpLayer.h"
#include "ChooseLayer.h"
#include "AchieveLayer.h"
#include "GameLayer.h"
#include "OpenLayer.h"


using namespace cocos2d;

//实现GameSceneManager类中的createScene方法
Scene* GameSceneManager::createScene()
{
    //创建一个场景对象
	Scene *scene = Scene::create();
	OpenLayer *layer = OpenLayer::create();
    //将欢迎布景添加到场景中
    scene->addChild(layer);
    //返回场景
    return scene;
}

//切换到主界面
void GameSceneManager::toBeginLayer()
{
	//获取Director（导演）
	Director* pDirector = Director::sharedDirector();
	pDirector -> setDepthTest(true);
	Scene* toGameLayerSence = Scene::create();
	BeginLayer *layer = BeginLayer::create();
	toGameLayerSence->addChild(layer);
	TransitionScene* ccts= TransitionFadeTR::create(1.0f, toGameLayerSence);
	//执行切换
	Director::sharedDirector()->replaceScene(ccts);
}

//切换到选关界面
void GameSceneManager::toChooseLayer()
{
	//获取Director（导演）
	Director* pDirector = Director::sharedDirector();
	pDirector -> setDepthTest(true);
	Scene* toGameLayerSence = Scene::create();
	ChooseLayer *layer = ChooseLayer::create();
	toGameLayerSence->addChild(layer);
	TransitionScene* ccts= TransitionFadeTR::create(1.0f, toGameLayerSence);
	//执行切换
	Director::sharedDirector()->replaceScene(ccts);
}

//切换到helplayer
void GameSceneManager::toHelpLayer()
{
	//获取Director（导演）
	Director* pDirector = Director::sharedDirector();
	pDirector -> setDepthTest(true);
	Scene* toGameLayerSence = Scene::create();
	HelpLayer *layer = HelpLayer::create();
	toGameLayerSence->addChild(layer);
	TransitionScene* ccts= TransitionFadeTR::create(1.0f, toGameLayerSence);
	//执行切换
	Director::sharedDirector()->replaceScene(ccts);
}

//切换到最高分
void GameSceneManager::toAchieveLayer()
{
	//获取Director（导演）
	Director* pDirector = Director::sharedDirector();
	pDirector -> setDepthTest(true);
	Scene* toGameLayerSence = Scene::create();
	AchieveLayer *layer = AchieveLayer::create();
	//layer->man = this;
	toGameLayerSence->addChild(layer);
	TransitionScene* ccts= TransitionFadeTR::create(1.0f, toGameLayerSence);
	//执行切换
	Director::sharedDirector()->replaceScene(ccts);
}

//切换到游戏界面
void GameSceneManager::toGameLayer()
{
	//获取Director（导演）
	Director* pDirector = Director::sharedDirector();
	pDirector -> setDepthTest(true);
	Scene* toGameLayerSence = Scene::create();
	GameLayer *layer = GameLayer::create();
	toGameLayerSence->addChild(layer);
	TransitionScene* ccts= TransitionFadeTR::create(1.0f, toGameLayerSence);
	//执行切换
	Director::sharedDirector()->replaceScene(ccts);
}
