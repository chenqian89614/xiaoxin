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

	/*添加音乐*/
	GameMusic* BGmusicGame = GameMusic::getInstance();
	BGmusicGame->playmusic();

    /*加载Tiled地图，添加到场景中*/
	TMXTiledMap* map = TMXTiledMap::create("WorldI32X32.tmx");
    this->addChild(map);

	/*加载主角*/
	addPlayer(map);

	/*载入cocos制作的按钮UI*/
	loadUI();

	return true;
}

void DemoTollgateScene::addPlayer(TMXTiledMap* map) {
	
	/*获取屏幕尺寸*/
	Size visibleSize = Director::getInstance()->getVisibleSize();

	/*创建精灵*/
	Sprite* playerSprite = Sprite::create("Hforward.png");

	/*将精灵绑定到玩家对象上*/
	Player* mPlayer = Player::create();
	m_Player = mPlayer;
	m_Player->bindSprite(playerSprite);
	m_Player->run();
	
	/*使地图随着主角移动*/
	m_Player->setTiledMap(map);

	/*设置玩家坐标*/

	m_Player->setPosition(Point(256,480));

	/*将玩家添加到地图*/
	map->addChild(m_Player,10);

	/*将主角类对接简单移动，使小新开始奔跑*/
	SimpleMoveController* simplemovecontroller = SimpleMoveController::create();

	/*设置移动速度*/
	simplemovecontroller->setiSpeed(2);

	/*将简单移动控制器添加到场景中*/
	this->addChild(simplemovecontroller);

	/*将控制器设置在主角上*/
	mPlayer->setController(simplemovecontroller);
}

void DemoTollgateScene::loadUI() {
	//加载UI
	auto UI = CSLoader::createNode("DemoTollgateSceneUI.csb");
	this->addChild(UI,15);

	//获取按钮控件对象
	auto slowBtn = dynamic_cast<Button*>(UI->getChildByName("slowBtn"));
	auto accelerateBtn = dynamic_cast<Button*>(UI->getChildByName("accelerateBtn"));
	auto skillBtn = dynamic_cast<Button*>(UI->getChildByName("skillBtn"));
	auto jumpBtn = dynamic_cast<Button*>(UI->getChildByName("jumpBtn"));


	//添加按钮单击监听
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