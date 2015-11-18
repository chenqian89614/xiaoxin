#ifndef __HelpLayer_H__
#define __HelpLayer_H__

#include "cocos2d.h"
#include "WelcomeLayer.h"

using namespace cocos2d;

//�Զ���Ĳ�����
class HelpLayer : public cocos2d::Layer
{
public:
	//����Scene
	cocos2d::Scene* scene;
	PokerSceneManager* psm;
	Sprite* bgSprite;//ָ�򱳾������ָ��
	Sprite* (spIntro) [5];//��ʾ����
	Point TBGPoint [5];//��ʾ����λ��
	Sprite* (bSprite) [5];//�ڰ׵㾫��
	int currIntroIndex=0;
	Point currPoint;
	//��ʼ���ķ���
	virtual bool init();

	//��ʼ�����¼��Ĵ�����
	bool onMyTouchBegan(Touch *touch, Event *event);
	//�����ƶ��¼��Ĵ�����
	void onMyTouchMoved(Touch *touch, Event *event);
	//���ؽ����¼��Ĵ�����
	void onMyTouchEnded(Touch *touch, Event *event);

	void setBWPosition();//���úڵ�׵�λ��

	void goBack();//���ز˵��Ļص�����
	~HelpLayer();


	//Cocos2d-x�ж����һ���꣬����ָ�����͵Ķ���
	//��������Ӧ�ĳ�ʼ�����ͷŹ���
	CREATE_FUNC(HelpLayer);
};
#endif
