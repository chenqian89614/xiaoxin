#ifndef _RankBirdLayer_H_
#define _RankBirdLayer_H_

#include "cocos2d.h"
#include "GameSceneManager.h"

using namespace cocos2d;

class RankBirdLayer : public Layer
{
public:
	//声明记录分数字符串
	std::string scoreBird[5];
	//声明显示分数的文本
	Label* labels;
	//场景管理指针
	GameSceneManager* sceneManager;
public:
	//初始化父类
	virtual bool init();
	//记录分数
	void save (int);
	//读取分数
	void load();
	//返回住菜单键
	void menuCallBack0(Ref* pSender);
	void menuCallBack1(Ref* pSender);
	CREATE_FUNC(RankBirdLayer);
};

#endif
