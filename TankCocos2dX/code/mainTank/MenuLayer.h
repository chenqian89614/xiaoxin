#ifndef _MenuLayer_H_
#define _MenuLayer_H_

#include "cocos2d.h"
#include "TankSceneManager.h"

USING_NS_CC;

class MenuLayer : public Layer
{
public:
	//����������
	TankSceneManager *tsm;
	//����scene
	Scene *scene;
	//3d����
	Sprite3D *sp3;
	int degree=0;
	//��ʼ������
	virtual bool init();
	//��ʼ���˵�
	void initMenu();
	//��ʼ��3D����
	void init3D();
	//�˵���ť����
	void gameStart();
	void gameHelp();
	void setSound();
	void gameExit();
	//��ʱ�ص�����
	void update();
	//��ת���˵�����
	void toGameLayer();
	//��ʼ�������ͼƬ
	static void initTitle(Layer *layer);

	CREATE_FUNC(MenuLayer);
};
#endif
