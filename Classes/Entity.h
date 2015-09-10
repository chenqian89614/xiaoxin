#ifndef _Entity_H_
#define _Entity_H_

#include "cocos2d.h"
#include "DemoControllerListener.h"
#include "DemoController.h"

USING_NS_CC;

class Entity : public Node,public DemoControllerListener {

public:
	/*绑定精灵对象*/
	void bindSprite(Sprite* sprite);

	/*获取精灵对象*/
	Sprite* getSprite();

	/*设置控制器*/
	 void setController(DemoController* DemoController);

	/*实现SimpleMoveListener接口的方法*/
	virtual void setTagPosition(int x, int y);
	virtual Point getTagPosition();

protected:
	Sprite* m_sprite;
	DemoController* m_DemoController;

};



#endif
