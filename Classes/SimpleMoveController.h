#ifndef _SimpleMoveController_H_
#define _SimpleMoveController_H_

#include "cocos2d.h"
#include "DemoController.h"

class SimpleMoveController : public DemoController {

public:
	CREATE_FUNC(SimpleMoveController);
	virtual bool init();
	virtual void update(float dt);

	/*设置移动速度*/
	void setiSpeed(int iSpeed);

private:
	int m_iSpeed;
};

#endif
