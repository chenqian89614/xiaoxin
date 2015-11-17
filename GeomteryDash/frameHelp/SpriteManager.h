#ifndef _SpriteManager_H_
#define _SpriteManager_H_

#include "cocos2d.h"
#include "../hellocpp/Constant.h"
#include "extensions/cocos-ext.h"
#include "../objectHelp/Barrier.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class SpriteManager
{
public:
	SpriteBatchNode* batchNode;
	Layer* layer;
	//创建一个单点触摸监听
	EventListenerTouchOneByOne* listenerTouch;
	Sprite* allSp[24];
	Scale9Sprite* allSs[1];
	Barrier* tb[5];
	bool isTouchBegin = false;
	bool isTouchMove = false;


public :
	SpriteManager(Layer* layerIn);
	void SpPause();//暂停精灵
	void AddEventListenerSprite(Sprite* sp);
	bool Judge(Sprite* sp, Point location);
	//创建精灵方法
	static Sprite* createSprite(std::string* id, Rect recta, SpriteBatchNode* batchNode, float anchorX, float anchorY, float locationX, float locationY, float width, float height, int ZOrder);
	Sprite* createStaticSprite(std::string* id, std::string pic, float anchorX, float anchorY, float locationX, float locationY, float width, float height);
	//开始触控事件的处理方法
	bool myOnTouchBegan(Touch *touch, Event *event);
	//触控移动事件的处理方法
	void myOnTouchMoved(Touch *touch, Event *event);
	//触控结束事件的处理方法
	void myOnTouchEnded(Touch *touch, Event *event);
	//触控终止事件的处理方法
	void myOnTouchCancelled(Touch *touch, Event *event);
	void backgroundRoll();//背景滚动方法
	Scale9Sprite* createScale9Sprite(std::string pic, Rect recta1, Rect recta2,float anchorX, float anchorY, float locationX, float locationY, float width, float height, int ZOrder);
	void createSiJiao();//创建四周的图片
	void createGround();//创建五个地面并让其自动向左移动
	void win();
};

#endif
