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
	//��ʼ���ķ���
	virtual bool init();

	void update(float dt);

	void loadingPic();
	void loadingCallBack(Ref* r);
	void loading3D(int number);

	//Cocos2d-x�ж����һ���꣬����ָ�����͵Ķ���
	//��������Ӧ�ĳ�ʼ�����ͷŹ���
	CREATE_FUNC(LoadLayer);
};

#endif
