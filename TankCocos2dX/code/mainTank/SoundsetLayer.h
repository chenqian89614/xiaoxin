#ifndef _SoundsetLayer_H_
#define _SoundsetLayer_H_

#include "cocos2d.h"
#include "TankSceneManager.h"

USING_NS_CC;

class SoundsetLayer : public Layer
{
public:
	//����������
	TankSceneManager *tsm;
	//��ʼ������
	virtual bool init();
	//��ʼ���˵�
	void initMenu();
	//�˵�����
	MenuItemImage *musicItem;
	MenuItemImage *effectItem;
	//�˵���ť����
	void musicChange();
	void musicRefresh();
	void effectChange();
	void effectRefresh();
	//��ת���˵�����
	void toMenuLayer();

	CREATE_FUNC(SoundsetLayer);
};
#endif
