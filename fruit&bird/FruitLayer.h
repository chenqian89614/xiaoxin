#ifndef __FruitLayer_H__
#define __FruitLayer_H__

#include "cocos2d.h"
#include "GameSceneManager.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace std;
using namespace cocos2d::extension;
using namespace ui;

class FruitLayer : public Layer
{
public:
	int count;
	int boss;
	bool stopFlag;
	bool bossFlag;
	bool gameFlag;
	bool readyFlag;
	bool overFlag;
	bool actionFlag;
	int height1;
	int height2;
	NodeGrid* effectNode;
	Sprite* bossSprite;
	//Ѫ��
	Slider* slider;
	LabelAtlas* pLabelAtlas;
	Sprite* overRank;
	MenuItemImage* relayItem;
	MenuItemImage* menuItem;
	Sprite* pauseBack;
	//������ͣ��ť����
	Sprite* pause;
	//
	Sprite* ready;
	//������������
	Sprite* background;
	//�������澫��
	Sprite* floor;
	//�������Ӿ���
	Sprite* columnUnder1;
	Sprite* columnOn1;
	Sprite* columnUnder2;
	Sprite* columnOn2;
	//��������ָ��
	GameSceneManager* sceneManager;
	//�洢ˮ������
	vector<Sprite*>* fruit;
public:
	//��ʼ�������ķ���
	virtual bool init();
	//��ʼ��Ϸ
	void startGame();
	//�������������
	int random();
	//��ʼ������
	void initColumn1();
	void initColumn2();
	//��Ϸ����
	void gameOver();
	//��Ϸʧ��
	void replay();
	void check();
	void moveObject();
	//������Ч
	void wingSound();
	void eatSound();
	//���ı�־λ
	void setFlag();
	//��ʱ�ص�����
	void update_fruit(float delta);
	void update_boss(float delta);
	void update_column(float delta);
	void menuCallback0(Ref* pSender);
	void menuCallback1(Ref* pSender);
	void menuCallback2(Ref* pSender);
	void menuCallback3(Ref* pSender);
	void menuCallback4(Ref* pSender);
	//��ѡ��ص�����
	void selectedEvent0(Ref* pSender,CheckBox::EventType type);
	void selectedEvent1(Ref* pSender,CheckBox::EventType type);
	//��ʼ���㴥���¼��Ĵ�����
	bool onTouchBegan(Touch* touch, Event* event);
	bool onTouchPause(Touch* touch, Event* event);
	CREATE_FUNC(FruitLayer);
};

#endif
