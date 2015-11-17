#ifndef _GameLayer_H_
#define _GameLayer_H_

#include "GameSceneManager.h"
#include "cocos2d.h"
#include <vector>
#include "../objectHelp/Barrier.h"
#include "../objectHelp/JumpCube.h"
#include "../frameHelp/SpriteManager.h"
#include "../frameHelp/PauseCode.h"
#include "GDData.h"

using namespace cocos2d;


class GameLayer : public cocos2d::Layer
{
public:

	GameSceneManager *gsm;
	Director* director;
	Size visibleSize;
	Point origin;

	SpriteManager* sh;//���������  ָ��
	PauseCode* pc;//��ͣ����ָ��
	GDData* gdData;

	bool isUpdateAll = true;//�Ƿ����UpdateAll�����Ļص�

	int indexGK;

	JumpCube* jc;
	std::string* ids;
	Barrier* tb;
	Barrier* zh;
	std::vector<Barrier*>::iterator iter;

	std::map<std::string,Sprite*> spMap;

	std::vector<Barrier*> barrierVector;//���ϰ����vector

	int timeCountCollision = 0;//��ײʱ�������
	int timeCount = 0;




	bool isTouch=false;

    virtual bool init();//��ʼ���ķ���


	//��ʼ�����¼��Ĵ�����
	bool myOnTouchBegan(Touch *touch, Event *event);
	//�����ƶ��¼��Ĵ�����
	void myOnTouchMoved(Touch *touch, Event *event);
	//���ؽ����¼��Ĵ�����ew
	void myOnTouchEnded(Touch *touch, Event *event);
	//������ֹ�¼��Ĵ�����
	void myOnTouchCancelled(Touch *touch, Event *event);

	void updateAll();//�������еķ���
	void deleteBarrier();//ɾ�� ����Ļ�� �ϰ���  �ķ���
	void collisionDetection();//��ײ��ⷽ��
	void initObjectOrSprite();//��ʼ�� ���� ��  ��������  ��  ��Ծ�ķ���
	void refleshJumpCube();
	void updateBarrier();

    //Cocos2d-x�ж����һ���꣬����ָ�����͵Ķ���
    //��������Ӧ�ĳ�ʼ�����ͷŹ���
    CREATE_FUNC(GameLayer);
};

#endif
