#ifndef __LevelLayer_H__
#define __LevelLayer_H__

#include "cocos2d.h"
#include "GameSceneManager.h"
#include "../frameHelp/LevelLayerHelp.h"
#include "../frameHelp/SpriteManager.h"

using namespace cocos2d;

class LevelLayer : public cocos2d::Layer
{
public :
	GameSceneManager *gsm;
	Size visibleSize;
	Point origin;
	Director* director;
	SpriteManager* sh;//���������  ָ��
	LevelLayerHelp* llh;//LevelLayer������ָ��

	int indexLevel;//�ؿ���������

	virtual bool init();//��ʼ���ķ���

	//Cocos2d-x�ж����һ���꣬����ָ�����͵Ķ���
	//��������Ӧ�ĳ�ʼ�����ͷŹ���
	CREATE_FUNC(LevelLayer);
};

#endif
