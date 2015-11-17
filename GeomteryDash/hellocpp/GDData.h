#ifndef _Data_H_
#define _Data_H_

#include "../objectHelp/Barrier.h"
#include "cocos2d.h"

using namespace cocos2d;

class GDData
{
public :
	GDData(Layer* layerIn);
	void createData();
	void createData3();
	void createFlyData();
	void createEightTriangle1(Layer* layer2);
	void createEightTriangle2(Layer* layer2);

public :
	std::string* ids;
	Barrier* tb;
	Layer* layer;
};

#endif
