#ifndef _PauseCode_H_
#define _PauseCode_H_

#include "cocos2d.h"

using namespace cocos2d;

class PauseCode
{
public :
	PauseCode(Layer* layerIn);
	void PauseStart();
	void PauseEnd();
	bool PauseJudgeSp(Sprite* sp);
public :
	Layer* layer;
	bool statePause = false;
};

#endif
