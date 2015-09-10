#ifndef _DemoController_H_
#define _DemoController_H_

#include "cocos2d.h"
#include "DemoControllerListener.h"

;USING_NS_CC;

class DemoController : public Node {

public:
	/*…Ë÷√º‡Ã˝∂‘œÛ*/
	void setDemoControllerListener(DemoControllerListener* DemoControllerListener);

protected:
	DemoControllerListener* m_democontrollerlistener;
};

#endif
