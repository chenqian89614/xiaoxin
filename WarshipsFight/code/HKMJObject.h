#ifndef _HKMJObject_H_
#define _HKMJObject_H_
#include "cocos2d.h"

using namespace cocos2d;
class HKMJObject
{
public :
	HKMJObject(int x,int y);
	Sprite* hkmjSprite ;
	int lifeValue = 20;
	//����־
	bool qhFlag = false;
	//��������
	int x;
	int y;
	//��������ȴʱ��
	int coolTime0 = 0;
	int coolTime1 = 0;
	int coolTime2 = 0;
	int coolTime3 = 0;
	int coolTime4 = 0;
	//�򿪱�ɱ���˵���־
	bool openMenu = false;
	//��ɱ������ȴ
	int coolTimeBSJ = 100;
	int coolTimePlane = 100;
};
#endif
