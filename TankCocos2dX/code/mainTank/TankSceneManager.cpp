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

//实现WelcomeLayerMangaer类中的createScene方法
Scene* TankSceneManager::WelcomeCreate()
{
	//创建场景对象
	Scene* scene=Scene::create();
	//创建布景对象
	Layer* layer=WelcomeLayer::create();
	//将欢迎布景添加到场景中
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
	//创建场景对象
	Scene* scene=Scene::create();
	//创建布景对象
	Layer* layer=MenuLayer::create();
	//将欢迎布景添加到场景中
	scene->addChild(layer);
	//设置切换场景特效
	TransitionFade* tf=TransitionFade::create(0.8f,scene);
	//获取导演
	Director *dir=Director::getInstance();
	//切换场景
	dir->replaceScene(tf);
}

void TankSceneManager::toSoundsetLayer()
{
	//创建场景对象
	Scene* scene=Scene::create();
	//创建布景对象
	Layer* layer=SoundsetLayer::create();
	//将欢迎布景添加到场景中
	scene->addChild(layer);
	//设置切换场景特效
	TransitionFadeTR* ftf=TransitionFadeTR::create(0.8f,scene);
	//获取导演
	Director *dir=Director::getInstance();
	//切换场景
	dir->replaceScene(ftf);
}

void TankSceneManager::toHelpLayer()
{
	//创建场景对象
	Scene* scene=Scene::create();
	//创建布景对象
	Layer* layer=HelpLayer::create();
	//将欢迎布景添加到场景中
	scene->addChild(layer);
	//设置切换场景特效
	TransitionFadeTR* ftf=TransitionFadeTR::create(0.8f,scene);
	//获取导演
	Director *dir=Director::getInstance();
	//切换场景
	dir->replaceScene(ftf);
}

void TankSceneManager::toSelectLayer()
{
	//创建场景对象
	Scene* scene=Scene::create();
	//创建布景对象
	SelectLayer *selectLayer=SelectLayer::create();
	//将欢迎布景添加到场景中
	scene->addChild(selectLayer);
	//设置切换场景特效
	TransitionFadeTR* tf=TransitionFadeTR::create(0.8f,scene);
	//获取导演
	Director *dir=Director::getInstance();
	//切换场景
	dir->replaceScene(tf);
}

void TankSceneManager::toGameLayer()
{
	//创建场景对象
	Scene* scene=Scene::create();
	//绘制层对象
	GameLayer *gameLayer=GameLayer::create();
	//控制层对象
	ControlLayer *controlLayer=ControlLayer::create();
	//获得绘制层的引用
	controlLayer->getGameLayer(gameLayer);
	//将欢迎布景添加到场景中
	scene->addChild(gameLayer, 0, 0);
	scene->addChild(controlLayer, 1, 1);
	//设置切换场景特效
	TransitionFadeTR* ftf=TransitionFadeTR::create(0.8f,scene);
	//获取导演
	Director *dir=Director::getInstance();
	//切换场景
	dir->replaceScene(ftf);
}

void TankSceneManager::backMenuLayer()
{
	//创建场景对象
	Scene* scene=Scene::create();
	//创建布景对象
	Layer* layer=MenuLayer::create();
	//将欢迎布景添加到场景中
	scene->addChild(layer);
	//设置切换场景特效
	TransitionFade* tf=TransitionFade::create(0.8f,scene);
	//获取导演
	Director *dir=Director::getInstance();
	//切换场景
	dir->replaceScene(tf);
}

