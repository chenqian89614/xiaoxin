#ifndef _DemoTollgateScene_H_
#define _DemoTollgateScene_H_

#include "cocos2d.h"
#include "GameMusic.h"
#include "player.h"
#include "ui\UIWidget.h"

;USING_NS_CC;
using namespace ui;

class DemoTollgateScene : public Layer {

public:
	static Scene* createScene();
	CREATE_FUNC(DemoTollgateScene);
	virtual bool init();

	void addPlayer(TMXTiledMap* map);

private:
	void loadUI();                   //加载cocos制作按钮UI
	void onslowClick(Ref* object, TouchEventType type);            //按钮控件触发函数
	void onaccelerateClick(Ref* object, TouchEventType type);
	void onskillClick(Ref* object, TouchEventType type);
	void onjumpClick(Ref* object, TouchEventType type);
	
	GameMusic* BGmusicGame;
	
	Player* m_Player;

};


#endif


