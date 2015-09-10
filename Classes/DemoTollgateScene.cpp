#include "cocos2d.h"
#include "DemoTollgateScene.h"
#include "player.h"
#include "SimpleMoveController.h"
#include "GameMusic.h"
#include "ui\UIWidget.h"
#include "cocostudio/CocoStudio.h" 
#include "ui\UIButton.h"
#include "ui\UIHelper.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;


Scene* DemoTollgateScene::createScene() {
	auto scene = Scene::create();
	auto layer = DemoTollgateScene::create();
	scene->addChild(layer);
	return scene;
}


bool DemoTollgateScene::init() {
	if (!Layer::init()) {
		return false;
	}

	/*�������*/
	GameMusic* BGmusicGame = GameMusic::getInstance();
	BGmusicGame->playmusic();

    /*����Tiled��ͼ����ӵ�������*/
	TMXTiledMap* map = TMXTiledMap::create("WorldI32X32.tmx");
    this->addChild(map);

	/*��������*/
	addPlayer(map);

	/*����cocos�����İ�ťUI*/
	loadUI();

	return true;
}

void DemoTollgateScene::addPlayer(TMXTiledMap* map) {
	
	/*��ȡ��Ļ�ߴ�*/
	Size visibleSize = Director::getInstance()->getVisibleSize();

	/*��������*/
	Sprite* playerSprite = Sprite::create("Hforward.png");

	/*������󶨵���Ҷ�����*/
	Player* mPlayer = Player::create();
	m_Player = mPlayer;
	m_Player->bindSprite(playerSprite);
	m_Player->run();
	
	/*ʹ��ͼ���������ƶ�*/
	m_Player->setTiledMap(map);

	/*�����������*/

	m_Player->setPosition(Point(256,480));

	/*�������ӵ���ͼ*/
	map->addChild(m_Player,10);

	/*��������ԽӼ��ƶ���ʹС�¿�ʼ����*/
	SimpleMoveController* simplemovecontroller = SimpleMoveController::create();

	/*�����ƶ��ٶ�*/
	simplemovecontroller->setiSpeed(2);

	/*�����ƶ���������ӵ�������*/
	this->addChild(simplemovecontroller);

	/*��������������������*/
	mPlayer->setController(simplemovecontroller);
}

void DemoTollgateScene::loadUI() {
	//����UI
	auto UI = CSLoader::createNode("DemoTollgateSceneUI.csb");
	this->addChild(UI,15);

	//��ȡ��ť�ؼ�����
	auto slowBtn = dynamic_cast<Button*>(UI->getChildByName("slowBtn"));
	auto accelerateBtn = dynamic_cast<Button*>(UI->getChildByName("accelerateBtn"));
	auto skillBtn = dynamic_cast<Button*>(UI->getChildByName("skillBtn"));
	auto jumpBtn = dynamic_cast<Button*>(UI->getChildByName("jumpBtn"));


	//��Ӱ�ť��������
	slowBtn->addTouchEventListener(this, toucheventselector(DemoTollgateScene::onslowClick));
	accelerateBtn->addTouchEventListener(this, toucheventselector(DemoTollgateScene::onaccelerateClick));
	skillBtn->addTouchEventListener(this, toucheventselector(DemoTollgateScene::onskillClick));
	jumpBtn->addTouchEventListener(this, toucheventselector(DemoTollgateScene::onjumpClick));

}

void DemoTollgateScene::onjumpClick(Ref* object, TouchEventType type) {
	switch (type) {
	case TouchEventType::TOUCH_EVENT_ENDED:
		m_Player->jump();
		break;
	}
}

void DemoTollgateScene::onslowClick(Ref* object, TouchEventType type) {

}

void DemoTollgateScene::onaccelerateClick(Ref* object, TouchEventType type) {

}

void DemoTollgateScene::onskillClick(Ref* object, TouchEventType type) {

}