#ifndef __MenuLayer_H__
#define __MenuLayer_H__

#include "cocos2d.h"
#include "GameSceneManager.h"
#include "../frameHelp/MenuLayerHelp.h"
#include "../frameHelp/SpriteManager.h"

using namespace cocos2d;

class MenuLayer : public cocos2d::Layer
{
public :
	GameSceneManager *gsm;
	Size visibleSize;
	Point origin;
	Director* director;
	SpriteManager* sh;//���������  ָ��
	MenuLayerHelp* mlh;//MenuLayer������ָ��

	virtual bool init();//��ʼ���ķ���

	//Cocos2d-x�ж����һ���꣬����ָ�����͵Ķ���
	//��������Ӧ�ĳ�ʼ�����ͷŹ���
	CREATE_FUNC(MenuLayer);
};

#endif
