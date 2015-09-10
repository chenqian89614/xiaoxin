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
	void loadUI();                   //����cocos������ťUI
	void onslowClick(Ref* object, TouchEventType type);            //��ť�ؼ���������
	void onaccelerateClick(Ref* object, TouchEventType type);
	void onskillClick(Ref* object, TouchEventType type);
	void onjumpClick(Ref* object, TouchEventType type);
	
	GameMusic* BGmusicGame;
	
	Player* m_Player;

};


#endif


