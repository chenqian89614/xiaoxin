#include "cocos2d.h"
#include "MenuScene.h"
#include "DemoTollgateScene.h"
#include "GameMusic.h"
#include "ui\UIWidget.h"
#include "cocostudio/CocoStudio.h" 
#include "ui\UIButton.h"
#include "ui\UIHelper.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;

Scene* MenuScene::createScene() {
	auto scene = Scene::create();
	auto layer = MenuScene::create();
	scene->addChild(layer);
	return scene;
}


bool MenuScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	_music = GameMusic::getInstance();
	_music->playmusic();

	/*载入cocos制作的开始界面UI*/
	loadUI();
	
	return true;
}

void MenuScene::loadUI() {
	//加载UI
	auto UI = CSLoader::createNode("DemoGameMenuSceneUI.csb");
	this->addChild(UI);

	//获取开始按钮控件对象
	auto startBtn = dynamic_cast<Button*>(UI->getChildByName("startBtn"));
	

	//添加开始按钮单击监听
	startBtn->addTouchEventListener(this, toucheventselector(MenuScene::onstartClick));

}

/*void MenuScene::onClick(Ref* object, TouchEventType type) {
	switch (type) {
	case TouchEventType::TOUCH_EVENT_ENDED:
		Node* node = (Node*)object;
		int tag = node->getTag();
		//根据点击按钮tag不同决定触发事件
		if (tag == 121)
		{
			
		}
	
		break;
	}

}*/

void MenuScene::onstartClick(Ref* object, TouchEventType type){
	switch (type) {
	case TouchEventType::TOUCH_EVENT_ENDED:
		
		/*改变窗口分辨率（操蛋的一比，为毛图片大小都不一样）*/
		auto director = Director::getInstance();
		auto glview = director->getOpenGLView();
		glview->setDesignResolutionSize(1280, 1024, ResolutionPolicy::NO_BORDER);
		auto scene = DemoTollgateScene::createScene();
		Director::getInstance()->replaceScene(scene);
		
		break;
	}
}