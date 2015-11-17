#ifndef __MusicLayer_H__
#define __MusicLayer_H__

#include "cocos2d.h"
#include "GameSceneManager.h"
#include "../frameHelp/MusicLayerHelp.h"
#include "../frameHelp/SpriteManager.h"

using namespace cocos2d;

class MusicLayer : public cocos2d::Layer
{
public :
	GameSceneManager *gsm;
	Size visibleSize;
	Point origin;
	Director* director;
	SpriteManager* sh;//���������  ָ��
	MusicLayerHelp* mlh;//MusicLayer������ָ��

	virtual bool init();//��ʼ���ķ���

	//Cocos2d-x�ж����һ���꣬����ָ�����͵Ķ���
	//��������Ӧ�ĳ�ʼ�����ͷŹ���
	CREATE_FUNC(MusicLayer);
};

#endif
