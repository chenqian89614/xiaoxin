#ifndef _Entity_H_
#define _Entity_H_

#include "cocos2d.h"
#include "DemoControllerListener.h"
#include "DemoController.h"

USING_NS_CC;

class Entity : public Node,public DemoControllerListener {

public:
	/*�󶨾������*/
	void bindSprite(Sprite* sprite);

	/*��ȡ�������*/
	Sprite* getSprite();

	/*���ÿ�����*/
	 void setController(DemoController* DemoController);

	/*ʵ��SimpleMoveListener�ӿڵķ���*/
	virtual void setTagPosition(int x, int y);
	virtual Point getTagPosition();

protected:
	Sprite* m_sprite;
	DemoController* m_DemoController;

};



#endif
