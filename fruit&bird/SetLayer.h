#ifndef _SetLayer_H_
#define _SetLayer_H_

#include "cocos2d.h"
#include "GameSceneManager.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace ui;

class SetLayer : public Layer
{
public:
	//��������ָ��
	GameSceneManager* sceneManager;
public:
	//��ʼ������
	virtual bool init();
	//����ס�˵���
	void menuCallBack(Ref* pSender);
	//��ѡ��
	void selectedEvent0(Ref* pSender,CheckBox::EventType type);
	void selectedEvent1(Ref* pSender,CheckBox::EventType type);
	CREATE_FUNC(SetLayer);
};

#endif
