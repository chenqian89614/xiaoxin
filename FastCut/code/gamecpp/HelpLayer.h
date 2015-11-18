#ifndef __HelpLayer_H__
#define __HelpLayer_H__

#include "cocos2d.h"
#include "GameSceneManager.h"
#include "WelcomeLayer.h"

using namespace cocos2d;

//自定义的布景类
class HelpLayer : public cocos2d::Layer
{
public:
	GameSceneManager* gsm;
	Sprite* bgSprite;//指向背景精灵的指针
	Sprite* (spIntro) [3];//显示精灵
	Point TBGPoint [3];//显示精灵位置
	Sprite* (bSprite) [3];//黑白点精灵
	int currIntroIndex = 0;//当前显示的索引
	Point currPoint;//当前触摸点位置
	WelcomeLayer* wl;//欢迎界面的指针
	//初始化的方法
	virtual bool init();
	//开始触控事件的处理方法
	bool onMyTouchBegan(Touch *touch, Event *event);
	//触控移动事件的处理方法
	void onMyTouchMoved(Touch *touch, Event *event);
	//触控结束事件的处理方法
	void onMyTouchEnded(Touch *touch, Event *event);

	void setBWPosition();//设置黑点白点位置

	void onBack();//返回菜单的回调方法
	~HelpLayer();
	//Cocos2d-x中定义的一个宏，创建指定类型的对象
	//并做好相应的初始化与释放工作
	CREATE_FUNC(HelpLayer);
};
#endif
