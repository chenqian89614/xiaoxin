#ifndef _SpriteManager_H_
#define _SpriteManager_H_

#include "cocos2d.h"
#include "../hellocpp/Constant.h"
#include "extensions/cocos-ext.h"
#include "../objectHelp/Barrier.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class SpriteManager
{
public:
	SpriteBatchNode* batchNode;
	Layer* layer;
	//����һ�����㴥������
	EventListenerTouchOneByOne* listenerTouch;
	Sprite* allSp[24];
	Scale9Sprite* allSs[1];
	Barrier* tb[5];
	bool isTouchBegin = false;
	bool isTouchMove = false;


public :
	SpriteManager(Layer* layerIn);
	void SpPause();//��ͣ����
	void AddEventListenerSprite(Sprite* sp);
	bool Judge(Sprite* sp, Point location);
	//�������鷽��
	static Sprite* createSprite(std::string* id, Rect recta, SpriteBatchNode* batchNode, float anchorX, float anchorY, float locationX, float locationY, float width, float height, int ZOrder);
	Sprite* createStaticSprite(std::string* id, std::string pic, float anchorX, float anchorY, float locationX, float locationY, float width, float height);
	//��ʼ�����¼��Ĵ�����
	bool myOnTouchBegan(Touch *touch, Event *event);
	//�����ƶ��¼��Ĵ�����
	void myOnTouchMoved(Touch *touch, Event *event);
	//���ؽ����¼��Ĵ�����
	void myOnTouchEnded(Touch *touch, Event *event);
	//������ֹ�¼��Ĵ�����
	void myOnTouchCancelled(Touch *touch, Event *event);
	void backgroundRoll();//������������
	Scale9Sprite* createScale9Sprite(std::string pic, Rect recta1, Rect recta2,float anchorX, float anchorY, float locationX, float locationY, float width, float height, int ZOrder);
	void createSiJiao();//�������ܵ�ͼƬ
	void createGround();//����������沢�����Զ������ƶ�
	void win();
};

#endif
