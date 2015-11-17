#ifndef __ChoiceCubeLayer_H__
#define __ChoiceCubeLayer_H__

#include "cocos2d.h"
#include "GameSceneManager.h"
#include "../frameHelp/ChoiceCubeLayerHelp.h"
#include "../frameHelp/SpriteManager.h"

using namespace cocos2d;

class ChoiceCubeLayer : public cocos2d::Layer
{
public :
	GameSceneManager *gsm;
	Size visibleSize;
	Point origin;
	Director* director;
	SpriteManager* sh;//���������  ָ��
	ChoiceCubeLayerHelp* cclh;//ChoiceCubeLayer������ָ��

	virtual bool init();//��ʼ���ķ���

	//Cocos2d-x�ж����һ���꣬����ָ�����͵Ķ���
	//��������Ӧ�ĳ�ʼ�����ͷŹ���
	CREATE_FUNC(ChoiceCubeLayer);
};

#endif
