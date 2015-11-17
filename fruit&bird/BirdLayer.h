#ifndef __BirdLayer_H__
#define __BirdLayer_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "GameSceneManager.h"

using namespace cocos2d;
using namespace std;
using namespace cocos2d::extension;
using namespace ui;

class BirdLayer : public Layer
{
public:
	int columnNumber;
	//��ͣ��־λ
	bool stopFlag;
	bool runFlag = false;
	//��¼����
	int count = 0;
	//���������ӱ�־λ
	bool columnFlag1;
	bool columnFlag2;
	//��Ϸ��ʼ��־λ
	bool gameFlag;
	//��Ϸ׼����־λ
	bool readyFlag;
	//��Ϸ������־λ
	bool overFlag;
	//��������
	NodeGrid* effectNode;
	LabelAtlas* pLabelAtlas;
	Sprite* overRank;
	MenuItemImage* replayItem;
	MenuItemImage* menuItem;
	Sprite* pause;
	//������������
	Sprite *background;
	//�������澫��
	Sprite *floor;
	//�������Ӿ���
	Scale9Sprite* columnUnder1;
	Scale9Sprite* columnOn1;
	Scale9Sprite* columnUnder2;
	Scale9Sprite* columnOn2;
	//����С����
	Sprite* bird;
	//����ready����
	Sprite* ready;
	Sprite* pauseBack;
	//������������
	Animate* animAc;
	//��������ָ��
	GameSceneManager* sceneManager;
public:
	//��ʼ�������ķ���
	virtual bool init();
	//��ʼ��С��
	void initBird();
	//��ʼ��Ϸ
	void startGame();
	//��Ϸ����
	void gameOver();
	//С���˶�
	void birdRun();
	//��������
	void wingSound();
	void pointSound();
	void hitSound();
	void dieSound();
	//��������
	void update_column(float delta);
	//����С������ײ
	void update_bird(float delta);
	//��Ϸ���������˶�
	void moveObject();
	//��ʼ����
	void initColumn1();
	void initColumn2();
	//���������
	int random();
	//�˵�
	void menuCallbackItem0(Ref* pSender);
	void menuCallbackItem1(Ref* pSender);
	void menuCallbackItem2(Ref* pSender);
	void menuCallbackItem3(Ref* pSender);
	void menuCallbackItem4(Ref* pSender);
	//��ѡ��ص�����
	void selectedEvent0(Ref* pSender,CheckBox::EventType type);
	void selectedEvent1(Ref* pSender,CheckBox::EventType type);
	//�������
	void replay();
	//��ʼ���㴥���¼��Ĵ�����
	bool onTouchBegan(Touch* touch, Event* event);
	bool onTouchPause(Touch* touch, Event* event);
	void setRunFlag1();
	void setRunFlag2();

    //Cocos2d-x�ж����һ���꣬����ָ�����͵Ķ���
    //��������Ӧ�ĳ�ʼ�����ͷŹ���
    CREATE_FUNC(BirdLayer);
};

#endif
