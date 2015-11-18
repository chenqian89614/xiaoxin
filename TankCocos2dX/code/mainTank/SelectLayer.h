#ifndef _SelectLayer_H_
#define _SelectLayer_H_

#include "cocos2d.h"
#include "TankSceneManager.h"
#include "BNSocketUtil.h"

USING_NS_CC;

class SelectLayer : public Layer
{
public:
	//����������
	TankSceneManager *tsm;
	//��ʼ������
	virtual bool init();
	//��ʼ���˵�
	void initWaitMenu();
	//��ʼ��ͼƬ
	void initTexture();
	//���Ĺؿ�����
	void showLevel();
	//�л��˵�
	void toSelectMenu();
	//��ת���˵�����
	void toMenuLayer();
	//��ת����Ϸ
	void toGameLayer();
	//���͹ؿ�ѡ��
	void sendLevel(int level);
	//��ʱ�ص��ȴ����������͵���Ϣ
	void update();
	~SelectLayer();
	CREATE_FUNC(SelectLayer);

	SpriteFrame** levelFrame;
	Menu *menu;
	MenuItemImage *firstItem;
	MenuItemImage *secondItem;
	Sprite *waitSprite;
};
#endif
