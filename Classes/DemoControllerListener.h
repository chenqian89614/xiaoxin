#ifndef _DemoControllerListener_H_
#define _DemoControllerListener_H_

#include "cocos2d.h"

;USING_NS_CC;

class DemoControllerListener{

public:
	/*设置目标坐标*/
	virtual void setTagPosition(int x,int y) = 0;

	/*获取目标坐标*/
	virtual Point getTagPosition() = 0;
}



#endif
