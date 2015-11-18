#ifndef _PuKe_H_
#define _PuKe_H_
#include "cocos2d.h"
using namespace cocos2d;
class PuKe{
public :
	int x;
	int y;
	int pkNum;//¾«Áé±àºÅ
	Sprite* pukeSprite;
	PuKe(Texture2D* tt2d,int pkNum,Rect r,int x,int y);
	~PuKe();
	Sprite* refresh();
};
#endif
