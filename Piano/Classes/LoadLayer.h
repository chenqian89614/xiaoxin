#ifndef __LoadLayerController__
#define __LoadLayerController__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "extensions/cocos-ext.h"
#include "GameSceneManager.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace std;
using namespace ui;

class LoadLayer : public cocos2d::Layer
{
public:
	int currentNum;
	int instrumentNum;
	ControlPotentiometer* potentiometer;
	Label* label;
	Scheduler* schedRound;
	LoadingBar* load;
	GameSceneManager* sceneManager;
	static vector<Sprite3D*> instrument3D;
public:
	//初始化的方法
	virtual bool init();

	void update(float dt);

	void loadingPic();
	void loadingCallBack(Ref* r);
	void loading3D(int number);

	//Cocos2d-x中定义的一个宏，创建指定类型的对象
	//并做好相应的初始化与释放工作
	CREATE_FUNC(LoadLayer);
};

#endif
