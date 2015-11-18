#include "GameSceneManager.h"
#include "WelcomeLayer.h"
#include "ChoiceLayer.h"
#include "LevelLayer.h"
#include "SetLayer.h"
#include "HelpLayer.h"
#include "GameLayer.h"

//USING_NS_CC;
using namespace cocos2d;

//实现TransSceneManager类中的createScene方法
void GameSceneManager::createScene()
{
    //创建一个场景对象
	welcomeScene = Scene::create();

    //创建一个欢迎布景对象
	WelcomeLayer *wlayer = WelcomeLayer::create();

	welcomeScene->addChild(wlayer);
    //设置管理者
	wlayer->gsm=this;
}

void GameSceneManager::gogameScene()//去游戏场景的方法
{
	Director::getInstance()->setDepthTest(true);
	//创建场景对象
	gameScene = Scene::create();
	//创建一个布景对象
	GameLayer *glayer = GameLayer::create();
	glayer->initLevel(1);//参数为  本关的关数
	//设置管理者
	glayer->gsm=this;
	//向场景添加布景
	gameScene->addChild(glayer);

	//顺时针特效
	auto ss = TransitionProgressRadialCW::create(0.5, gameScene);
	Director::getInstance()->replaceScene(ss);

}

void GameSceneManager::goRound2Scene()
{
	Director::getInstance()->setDepthTest(true);
	//创建场景对象
	gameScene = Scene::create();
	//创建一个布景对象
	GameLayer *glayer = GameLayer::create();
	glayer->initLevel(2);//参数为  本关的关数
	//设置管理者
	glayer->gsm=this;
	//向场景添加布景
	gameScene->addChild(glayer);

	//顺时针特效
	auto ss = TransitionProgressRadialCW::create(0.5, gameScene);
	Director::getInstance()->replaceScene(ss);
}

void GameSceneManager::goRound3Scene()
{
	Director::getInstance()->setDepthTest(true);
	//创建场景对象
	gameScene = Scene::create();
	//创建一个布景对象
	GameLayer *glayer = GameLayer::create();
	glayer->initLevel(3);//参数为  本关的关数
	//设置管理者
	glayer->gsm=this;
	//向场景添加布景
	gameScene->addChild(glayer);

	//顺时针特效
	auto ss = TransitionProgressRadialCW::create(0.5, gameScene);
	Director::getInstance()->replaceScene(ss);
}

void GameSceneManager::goRound4Scene()
{
	Director::getInstance()->setDepthTest(true);
	//创建场景对象
	gameScene = Scene::create();
	//创建一个布景对象
	GameLayer *glayer = GameLayer::create();
	glayer->initLevel(4);//参数为  本关的关数
	//设置管理者
	glayer->gsm=this;
	//向场景添加布景
	gameScene->addChild(glayer);

	//顺时针特效
	auto ss = TransitionProgressRadialCW::create(0.5, gameScene);
	Director::getInstance()->replaceScene(ss);
}

void GameSceneManager::goRound5Scene()
{
	Director::getInstance()->setDepthTest(true);
	//创建场景对象
	gameScene = Scene::create();
	//创建一个布景对象
	GameLayer *glayer = GameLayer::create();
	glayer->initLevel(5);//参数为  本关的关数
	//设置管理者
	glayer->gsm=this;
	//向场景添加布景
	gameScene->addChild(glayer);

	//顺时针特效
	auto ss = TransitionProgressRadialCW::create(0.5, gameScene);
	Director::getInstance()->replaceScene(ss);
}

void GameSceneManager::goRound6Scene()
{
	Director::getInstance()->setDepthTest(true);
	//创建场景对象
	gameScene = Scene::create();
	//创建一个布景对象
	GameLayer *glayer = GameLayer::create();
	glayer->initLevel(6);//参数为  本关的关数
	//设置管理者
	glayer->gsm=this;
	//向场景添加布景
	gameScene->addChild(glayer);

	//顺时针特效
	auto ss = TransitionProgressRadialCW::create(0.5, gameScene);
	Director::getInstance()->replaceScene(ss);
}

void GameSceneManager::reStart()//重新开始的方法
{
	Director::getInstance()->setDepthTest(true);
	//创建场景对象
	gameScene = Scene::create();
	//创建一个布景对象
	GameLayer *glayer = GameLayer::create();
	glayer->initLevel(1);//参数为  本关的关数
	//设置管理者
	glayer->gsm=this;
	//向场景添加布景
	gameScene->addChild(glayer);

	//特效
	auto ss = TransitionShrinkGrow::create(1.5f, gameScene);
	Director::getInstance()->replaceScene(ss);
}
void GameSceneManager::reStart2()
{
	Director::getInstance()->setDepthTest(true);
	//创建场景对象
	gameScene = Scene::create();
	//创建一个布景对象
	GameLayer *glayer = GameLayer::create();
	glayer->initLevel(2);//参数为  本关的关数
	//设置管理者
	glayer->gsm=this;
	//向场景添加布景
	gameScene->addChild(glayer);

	//特效
	auto ss = TransitionShrinkGrow::create(1.5f, gameScene);
	Director::getInstance()->replaceScene(ss);
}
void GameSceneManager::reStart3()
{
	Director::getInstance()->setDepthTest(true);
	//创建场景对象
	gameScene = Scene::create();
	//创建一个布景对象
	GameLayer *glayer = GameLayer::create();
	glayer->initLevel(3);//参数为  本关的关数
	//设置管理者
	glayer->gsm=this;
	//向场景添加布景
	gameScene->addChild(glayer);
	//特效
	auto ss = TransitionShrinkGrow::create(1.5f, gameScene);
	Director::getInstance()->replaceScene(ss);
}
void GameSceneManager::reStart4()
{
	Director::getInstance()->setDepthTest(true);
	//创建场景对象
	gameScene = Scene::create();
	//创建一个布景对象
	GameLayer *glayer = GameLayer::create();
	glayer->initLevel(4);//参数为  本关的关数
	//设置管理者
	glayer->gsm=this;
	//向场景添加布景
	gameScene->addChild(glayer);
	//特效
	auto ss = TransitionShrinkGrow::create(1.5f, gameScene);
	Director::getInstance()->replaceScene(ss);
}

void GameSceneManager::reStart5()
{
	Director::getInstance()->setDepthTest(true);
	//创建场景对象
	gameScene = Scene::create();
	//创建一个布景对象
	GameLayer *glayer = GameLayer::create();
	glayer->initLevel(5);//参数为  本关的关数
	//设置管理者
	glayer->gsm=this;
	//向场景添加布景
	gameScene->addChild(glayer);

	//特效
	auto ss = TransitionShrinkGrow::create(1.5f, gameScene);
	Director::getInstance()->replaceScene(ss);
}

void GameSceneManager::reStart6()
{
	Director::getInstance()->setDepthTest(true);
	//创建场景对象
	gameScene = Scene::create();
	//创建一个布景对象
	GameLayer *glayer = GameLayer::create();
	glayer->initLevel(6);//参数为  本关的关数
	//设置管理者
	glayer->gsm=this;
	//向场景添加布景
	gameScene->addChild(glayer);

	//特效
	auto ss = TransitionShrinkGrow::create(1.5f, gameScene);
	Director::getInstance()->replaceScene(ss);
}

void GameSceneManager::goChoiceScene()//去选项场景
{
	Director::getInstance()->setDepthTest(true);
	//创建场景对象
	choiceScene = Scene::create();
	//创建一个布景对象
	ChoiceLayer *clayer = ChoiceLayer::create();
	//设置管理者
	clayer->gsm=this;
	//向场景添加布景
	choiceScene->addChild(clayer);
	auto ss=TransitionFade::create(0.7f, choiceScene);
	Director::getInstance()->replaceScene(ss);
}

void GameSceneManager::goWelcomeScene()//去欢迎场景
{
	Director::getInstance()->setDepthTest(true);
	welcomeScene = Scene::create();//创建欢迎场景对象
	WelcomeLayer* wlayer = WelcomeLayer::create();
	wlayer->gsm=this;//设置管理者
	welcomeScene->addChild(wlayer);
	auto ss=TransitionFade::create(0.7f, welcomeScene);
	Director::getInstance()->replaceScene(ss);
}

void GameSceneManager::goLevelScene()
{
	Director::getInstance()->setDepthTest(true);
	//创建场景对象
	levelScene = Scene::create();
	//创建一个布景对象
	LevelLayer *llayer = LevelLayer::create();
	//设置管理者
	llayer->gsm=this;
	//向场景添加布景
	levelScene->addChild(llayer);
	Director::getInstance()->replaceScene(levelScene);
}


void GameSceneManager::goSetScene()
{
	Director::getInstance()->setDepthTest(true);
	setScene = Scene::create();//创建场景对象
	SetLayer *slayer = SetLayer::create();//创建一个布景对象
	slayer->gsm=this;//设置管理者
	setScene->addChild(slayer);//向场景添加布景
	Director::getInstance()->replaceScene(setScene);
}

void GameSceneManager::goHelpScene()//去帮助场景
{
	Director::getInstance()->setDepthTest(true);
	HelpScene = Scene::create();//创建帮助场景对象
	HelpLayer* hlayer = HelpLayer::create();
	hlayer->gsm=this;//设置管理者
	HelpScene->addChild(hlayer);

	auto ss=TransitionFade::create(0.7f, HelpScene);
	Director::getInstance()->replaceScene(ss);
}
