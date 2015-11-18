#include "GameSceneManager.h"
#include "WelcomeLayer.h"
#include "ChoiceLayer.h"
#include "LevelLayer.h"
#include "SetLayer.h"
#include "HelpLayer.h"
#include "GameLayer.h"

//USING_NS_CC;
using namespace cocos2d;

//ʵ��TransSceneManager���е�createScene����
void GameSceneManager::createScene()
{
    //����һ����������
	welcomeScene = Scene::create();

    //����һ����ӭ��������
	WelcomeLayer *wlayer = WelcomeLayer::create();

	welcomeScene->addChild(wlayer);
    //���ù�����
	wlayer->gsm=this;
}

void GameSceneManager::gogameScene()//ȥ��Ϸ�����ķ���
{
	Director::getInstance()->setDepthTest(true);
	//������������
	gameScene = Scene::create();
	//����һ����������
	GameLayer *glayer = GameLayer::create();
	glayer->initLevel(1);//����Ϊ  ���صĹ���
	//���ù�����
	glayer->gsm=this;
	//�򳡾���Ӳ���
	gameScene->addChild(glayer);

	//˳ʱ����Ч
	auto ss = TransitionProgressRadialCW::create(0.5, gameScene);
	Director::getInstance()->replaceScene(ss);

}

void GameSceneManager::goRound2Scene()
{
	Director::getInstance()->setDepthTest(true);
	//������������
	gameScene = Scene::create();
	//����һ����������
	GameLayer *glayer = GameLayer::create();
	glayer->initLevel(2);//����Ϊ  ���صĹ���
	//���ù�����
	glayer->gsm=this;
	//�򳡾���Ӳ���
	gameScene->addChild(glayer);

	//˳ʱ����Ч
	auto ss = TransitionProgressRadialCW::create(0.5, gameScene);
	Director::getInstance()->replaceScene(ss);
}

void GameSceneManager::goRound3Scene()
{
	Director::getInstance()->setDepthTest(true);
	//������������
	gameScene = Scene::create();
	//����һ����������
	GameLayer *glayer = GameLayer::create();
	glayer->initLevel(3);//����Ϊ  ���صĹ���
	//���ù�����
	glayer->gsm=this;
	//�򳡾���Ӳ���
	gameScene->addChild(glayer);

	//˳ʱ����Ч
	auto ss = TransitionProgressRadialCW::create(0.5, gameScene);
	Director::getInstance()->replaceScene(ss);
}

void GameSceneManager::goRound4Scene()
{
	Director::getInstance()->setDepthTest(true);
	//������������
	gameScene = Scene::create();
	//����һ����������
	GameLayer *glayer = GameLayer::create();
	glayer->initLevel(4);//����Ϊ  ���صĹ���
	//���ù�����
	glayer->gsm=this;
	//�򳡾���Ӳ���
	gameScene->addChild(glayer);

	//˳ʱ����Ч
	auto ss = TransitionProgressRadialCW::create(0.5, gameScene);
	Director::getInstance()->replaceScene(ss);
}

void GameSceneManager::goRound5Scene()
{
	Director::getInstance()->setDepthTest(true);
	//������������
	gameScene = Scene::create();
	//����һ����������
	GameLayer *glayer = GameLayer::create();
	glayer->initLevel(5);//����Ϊ  ���صĹ���
	//���ù�����
	glayer->gsm=this;
	//�򳡾���Ӳ���
	gameScene->addChild(glayer);

	//˳ʱ����Ч
	auto ss = TransitionProgressRadialCW::create(0.5, gameScene);
	Director::getInstance()->replaceScene(ss);
}

void GameSceneManager::goRound6Scene()
{
	Director::getInstance()->setDepthTest(true);
	//������������
	gameScene = Scene::create();
	//����һ����������
	GameLayer *glayer = GameLayer::create();
	glayer->initLevel(6);//����Ϊ  ���صĹ���
	//���ù�����
	glayer->gsm=this;
	//�򳡾���Ӳ���
	gameScene->addChild(glayer);

	//˳ʱ����Ч
	auto ss = TransitionProgressRadialCW::create(0.5, gameScene);
	Director::getInstance()->replaceScene(ss);
}

void GameSceneManager::reStart()//���¿�ʼ�ķ���
{
	Director::getInstance()->setDepthTest(true);
	//������������
	gameScene = Scene::create();
	//����һ����������
	GameLayer *glayer = GameLayer::create();
	glayer->initLevel(1);//����Ϊ  ���صĹ���
	//���ù�����
	glayer->gsm=this;
	//�򳡾���Ӳ���
	gameScene->addChild(glayer);

	//��Ч
	auto ss = TransitionShrinkGrow::create(1.5f, gameScene);
	Director::getInstance()->replaceScene(ss);
}
void GameSceneManager::reStart2()
{
	Director::getInstance()->setDepthTest(true);
	//������������
	gameScene = Scene::create();
	//����һ����������
	GameLayer *glayer = GameLayer::create();
	glayer->initLevel(2);//����Ϊ  ���صĹ���
	//���ù�����
	glayer->gsm=this;
	//�򳡾���Ӳ���
	gameScene->addChild(glayer);

	//��Ч
	auto ss = TransitionShrinkGrow::create(1.5f, gameScene);
	Director::getInstance()->replaceScene(ss);
}
void GameSceneManager::reStart3()
{
	Director::getInstance()->setDepthTest(true);
	//������������
	gameScene = Scene::create();
	//����һ����������
	GameLayer *glayer = GameLayer::create();
	glayer->initLevel(3);//����Ϊ  ���صĹ���
	//���ù�����
	glayer->gsm=this;
	//�򳡾���Ӳ���
	gameScene->addChild(glayer);
	//��Ч
	auto ss = TransitionShrinkGrow::create(1.5f, gameScene);
	Director::getInstance()->replaceScene(ss);
}
void GameSceneManager::reStart4()
{
	Director::getInstance()->setDepthTest(true);
	//������������
	gameScene = Scene::create();
	//����һ����������
	GameLayer *glayer = GameLayer::create();
	glayer->initLevel(4);//����Ϊ  ���صĹ���
	//���ù�����
	glayer->gsm=this;
	//�򳡾���Ӳ���
	gameScene->addChild(glayer);
	//��Ч
	auto ss = TransitionShrinkGrow::create(1.5f, gameScene);
	Director::getInstance()->replaceScene(ss);
}

void GameSceneManager::reStart5()
{
	Director::getInstance()->setDepthTest(true);
	//������������
	gameScene = Scene::create();
	//����һ����������
	GameLayer *glayer = GameLayer::create();
	glayer->initLevel(5);//����Ϊ  ���صĹ���
	//���ù�����
	glayer->gsm=this;
	//�򳡾���Ӳ���
	gameScene->addChild(glayer);

	//��Ч
	auto ss = TransitionShrinkGrow::create(1.5f, gameScene);
	Director::getInstance()->replaceScene(ss);
}

void GameSceneManager::reStart6()
{
	Director::getInstance()->setDepthTest(true);
	//������������
	gameScene = Scene::create();
	//����һ����������
	GameLayer *glayer = GameLayer::create();
	glayer->initLevel(6);//����Ϊ  ���صĹ���
	//���ù�����
	glayer->gsm=this;
	//�򳡾���Ӳ���
	gameScene->addChild(glayer);

	//��Ч
	auto ss = TransitionShrinkGrow::create(1.5f, gameScene);
	Director::getInstance()->replaceScene(ss);
}

void GameSceneManager::goChoiceScene()//ȥѡ���
{
	Director::getInstance()->setDepthTest(true);
	//������������
	choiceScene = Scene::create();
	//����һ����������
	ChoiceLayer *clayer = ChoiceLayer::create();
	//���ù�����
	clayer->gsm=this;
	//�򳡾���Ӳ���
	choiceScene->addChild(clayer);
	auto ss=TransitionFade::create(0.7f, choiceScene);
	Director::getInstance()->replaceScene(ss);
}

void GameSceneManager::goWelcomeScene()//ȥ��ӭ����
{
	Director::getInstance()->setDepthTest(true);
	welcomeScene = Scene::create();//������ӭ��������
	WelcomeLayer* wlayer = WelcomeLayer::create();
	wlayer->gsm=this;//���ù�����
	welcomeScene->addChild(wlayer);
	auto ss=TransitionFade::create(0.7f, welcomeScene);
	Director::getInstance()->replaceScene(ss);
}

void GameSceneManager::goLevelScene()
{
	Director::getInstance()->setDepthTest(true);
	//������������
	levelScene = Scene::create();
	//����һ����������
	LevelLayer *llayer = LevelLayer::create();
	//���ù�����
	llayer->gsm=this;
	//�򳡾���Ӳ���
	levelScene->addChild(llayer);
	Director::getInstance()->replaceScene(levelScene);
}


void GameSceneManager::goSetScene()
{
	Director::getInstance()->setDepthTest(true);
	setScene = Scene::create();//������������
	SetLayer *slayer = SetLayer::create();//����һ����������
	slayer->gsm=this;//���ù�����
	setScene->addChild(slayer);//�򳡾���Ӳ���
	Director::getInstance()->replaceScene(setScene);
}

void GameSceneManager::goHelpScene()//ȥ��������
{
	Director::getInstance()->setDepthTest(true);
	HelpScene = Scene::create();//����������������
	HelpLayer* hlayer = HelpLayer::create();
	hlayer->gsm=this;//���ù�����
	HelpScene->addChild(hlayer);

	auto ss=TransitionFade::create(0.7f, HelpScene);
	Director::getInstance()->replaceScene(ss);
}
