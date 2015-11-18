#ifndef  _TankSceneManager_H_
#define  _TankSceneManager_H_

#include "cocos2d.h"

USING_NS_CC;

class TankSceneManager
{
public:
	//������������ķ���
	static Scene* WelcomeCreate();
	//��ת���˵�����
	void toMenuLayer();
	//��ת���������ý���
	void toSoundsetLayer();
	//��ת����Ϸ��������
	void toHelpLayer();
	//��ת����Ϸ����
	void toGameLayer();
	//��ת��ѡ�����
	void toSelectLayer();
	//���ز˵�
	static void backMenuLayer();
	//���ɱ�������
	static Sprite* getGround();
};
#endif
