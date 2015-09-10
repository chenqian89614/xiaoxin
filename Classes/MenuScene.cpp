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

	/*����cocos�����Ŀ�ʼ����UI*/
	loadUI();
	
	return true;
}

void MenuScene::loadUI() {
	//����UI
	auto UI = CSLoader::createNode("DemoGameMenuSceneUI.csb");
	this->addChild(UI);

	//��ȡ��ʼ��ť�ؼ�����
	auto startBtn = dynamic_cast<Button*>(UI->getChildByName("startBtn"));
	

	//��ӿ�ʼ��ť��������
	startBtn->addTouchEventListener(this, toucheventselector(MenuScene::onstartClick));

}

/*void MenuScene::onClick(Ref* object, TouchEventType type) {
	switch (type) {
	case TouchEventType::TOUCH_EVENT_ENDED:
		Node* node = (Node*)object;
		int tag = node->getTag();
		//���ݵ����ťtag��ͬ���������¼�
		if (tag == 121)
		{
			
		}
	
		break;
	}

}*/

void MenuScene::onstartClick(Ref* object, TouchEventType type){
	switch (type) {
	case TouchEventType::TOUCH_EVENT_ENDED:
		
		/*�ı䴰�ڷֱ��ʣ��ٵ���һ�ȣ�ΪëͼƬ��С����һ����*/
		auto director = Director::getInstance();
		auto glview = director->getOpenGLView();
		glview->setDesignResolutionSize(1280, 1024, ResolutionPolicy::NO_BORDER);
		auto scene = DemoTollgateScene::createScene();
		Director::getInstance()->replaceScene(scene);
		
		break;
	}
}