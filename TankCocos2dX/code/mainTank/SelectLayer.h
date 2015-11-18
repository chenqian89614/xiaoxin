#ifndef _SelectLayer_H_
#define _SelectLayer_H_

#include "cocos2d.h"
#include "TankSceneManager.h"
#include "BNSocketUtil.h"

USING_NS_CC;

class SelectLayer : public Layer
{
public:
	//场景管理器
	TankSceneManager *tsm;
	//初始化方法
	virtual bool init();
	//初始化菜单
	void initWaitMenu();
	//初始化图片
	void initTexture();
	//更改关卡精灵
	void showLevel();
	//切换菜单
	void toSelectMenu();
	//跳转到菜单界面
	void toMenuLayer();
	//跳转到游戏
	void toGameLayer();
	//发送关卡选择
	void sendLevel(int level);
	//定时回调等待服务器发送的消息
	void update();
	~SelectLayer();
	CREATE_FUNC(SelectLayer);

	SpriteFrame** levelFrame;
	Menu *menu;
	MenuItemImage *firstItem;
	MenuItemImage *secondItem;
	Sprite *waitSprite;
};
#endif
