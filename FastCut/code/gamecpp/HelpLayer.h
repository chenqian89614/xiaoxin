#ifndef __HelpLayer_H__
#define __HelpLayer_H__

#include "cocos2d.h"
#include "GameSceneManager.h"
#include "WelcomeLayer.h"

using namespace cocos2d;

//�Զ���Ĳ�����
class HelpLayer : public cocos2d::Layer
{
public:
	GameSceneManager* gsm;
	Sprite* bgSprite;//ָ�򱳾������ָ��
	Sprite* (spIntro) [3];//��ʾ����
	Point TBGPoint [3];//��ʾ����λ��
	Sprite* (bSprite) [3];//�ڰ׵㾫��
	int currIntroIndex = 0;//��ǰ��ʾ������
	Point currPoint;//��ǰ������λ��
	WelcomeLayer* wl;//��ӭ�����ָ��
	//��ʼ���ķ���
	virtual bool init();
	//��ʼ�����¼��Ĵ�����
	bool onMyTouchBegan(Touch *touch, Event *event);
	//�����ƶ��¼��Ĵ�����
	void onMyTouchMoved(Touch *touch, Event *event);
	//���ؽ����¼��Ĵ�����
	void onMyTouchEnded(Touch *touch, Event *event);

	void setBWPosition();//���úڵ�׵�λ��

	void onBack();//���ز˵��Ļص�����
	~HelpLayer();
	//Cocos2d-x�ж����һ���꣬����ָ�����͵Ķ���
	//��������Ӧ�ĳ�ʼ�����ͷŹ���
	CREATE_FUNC(HelpLayer);
};
#endif
