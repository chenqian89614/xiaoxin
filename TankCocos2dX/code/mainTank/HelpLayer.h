#ifndef _HelpLayer_H_
#define _HelpLayer_H_

#include "cocos2d.h"
#include "TankSceneManager.h"

USING_NS_CC;

class HelpLayer : public Layer
{
public:
	//场景管理器
	TankSceneManager *tsm;
	//初始化方法
	virtual bool init();
	//初始化显示
	void initView();
	//初始化图片
	void initSprite();
	//帮助图片
	Sprite** helpPic;
	Sprite* helpPoint;

	int offset=480;
	int saveX=0;

	//开始触控事件的处理方法
	bool onMyTouchBegan(Touch* touch, Event* event);
	//触控移动事件的处理方法
	void onMyTouchMoved(Touch* touch, Event* event);
	//触控结束事件的处理方法
	void onMyTouchEnded(Touch* touch, Event* event);

	//跳转到菜单界面
	void toMenuLayer();

	CREATE_FUNC(HelpLayer);
};
#endif
