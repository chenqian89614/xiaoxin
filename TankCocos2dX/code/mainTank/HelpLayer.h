#ifndef _HelpLayer_H_
#define _HelpLayer_H_

#include "cocos2d.h"
#include "TankSceneManager.h"

USING_NS_CC;

class HelpLayer : public Layer
{
public:
	//����������
	TankSceneManager *tsm;
	//��ʼ������
	virtual bool init();
	//��ʼ����ʾ
	void initView();
	//��ʼ��ͼƬ
	void initSprite();
	//����ͼƬ
	Sprite** helpPic;
	Sprite* helpPoint;

	int offset=480;
	int saveX=0;

	//��ʼ�����¼��Ĵ�����
	bool onMyTouchBegan(Touch* touch, Event* event);
	//�����ƶ��¼��Ĵ�����
	void onMyTouchMoved(Touch* touch, Event* event);
	//���ؽ����¼��Ĵ�����
	void onMyTouchEnded(Touch* touch, Event* event);

	//��ת���˵�����
	void toMenuLayer();

	CREATE_FUNC(HelpLayer);
};
#endif
