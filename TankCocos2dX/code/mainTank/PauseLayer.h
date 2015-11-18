#ifndef _PauseLayer_H_
#define _PauseLayer_H_

#include "cocos2d.h"
#include "TankSceneManager.h"

USING_NS_CC;

class PauseLayer : public Layer
{
public:
	//����������
	TankSceneManager *tsm;
	//��ʼ������
	virtual bool init();
	//�˵�
	Menu *pauseMenu;
	Menu *soundsetMenu;
	//�������ò˵���
	MenuItemImage *musicItem;
	MenuItemImage *effectItem;
	//��ת��soundset�˵�
	void toSoundset();
	void toPause();
	//��ʼ���˵�
	void initPauseMenu();
	void initSoundsetMenu();
	//�˵���ť����
	void musicChange();
	void musicRefresh();
	void effectChange();
	void effectRefresh();
	//���ز˵�
	void backMenu();
	//�˳���Ϸ
	void gameExit();
	//������Ϸ
	void sendContinue();

	CREATE_FUNC(PauseLayer);
	virtual ~PauseLayer();
};
#endif
