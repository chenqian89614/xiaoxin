#ifndef _MenuScene_H_
#define _MenuScene_H_

#include "cocos2d.h"
#include "GameMusic.h"
#include "ui\UIWidget.h"

USING_NS_CC;
using namespace ui;

class MenuScene : public Layer{

public:
	static Scene* createScene();
	CREATE_FUNC(MenuScene);
	virtual bool init();

private:
	void loadUI();                                       //����cocos�����Ŀ�ʼ����UI
	//void onClick(Ref* object, TouchEventType type);     //���������ܺ�������tag�жϴ����¼�
	void onstartClick(Ref* object, TouchEventType type);     //��ʼ������������

private:
	GameMusic* _music;
	
}



#endif
