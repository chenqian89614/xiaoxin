#ifndef _MyFCData_H_
#define _MyFCData_H_

#include "cocos2d.h"

using namespace cocos2d;

class GameLayer;
class MyFCData
{
public :

	MyFCData(GameLayer* layerIn, int levelNumIn);
	void createMyFCData1();
	void createMyFCData2();
	void createMyFCData3();
	void createMyFCData4();
	void createMyFCData5();
	void createMyFCData6();

public :
	GameLayer* layer;
	static int levelNum;//µ±Ç°¹Ø¿¨
	static int radius;//Çò°ë¾¶
};

#endif
