#ifndef _ControlLayer_H_
#define _ControlLayer_H_

#include "cocos2d.h"
#include "BNJoyStick.h"
#include "TankSceneManager.h"
#include "GameLayer.h"

USING_NS_CC;

class ControlLayer : public Layer
{
public:
	//����������
	TankSceneManager *tsm;
	//��Ϸ״̬
	int state=0;
	//����ҡ�˶���
	BNJoyStick *tankStick;
	BNJoyStick *gunStick;
	//�˵�
	Menu *menu;
	//�õ���ϷLayerָ��
	GameLayer *gameLayer;
	//��������ֵ���������÷֡���ͣ�ľ���
	LabelAtlas *healthLabel;
	LabelAtlas *scoreLabel;
	void initView();

	//���GameLayerָ��
	void getGameLayer(GameLayer*);
	//��ʼ������
	virtual bool init();
	//��ʼ��ҡ��
	void initJoy();
	//��ʱ����
	void update();//���½���
	void sendKey();//����ҡ����Ϣ
	//������ͣ��Ϣ
	void sendPause();
	//��ת����ͣ����
	void toPauseLayer();
	//��ת���˵�����
	void toMenuLayer();
	//������Ϸ
	void backGameLayer();

	CREATE_FUNC(ControlLayer);
};
#endif
