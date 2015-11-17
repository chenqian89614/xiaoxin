#ifndef _FlyLayer_H_
#define _FlyLayer_H_

#include "GameSceneManager.h"
#include "cocos2d.h"
#include <vector>
#include "../objectHelp/FlyObject.h"
#include "../objectHelp/Barrier.h"
#include "../frameHelp/SpriteManager.h"
#include "../frameHelp/PauseCode.h"
#include "GDData.h"

using namespace cocos2d;


class FlyLayer : public cocos2d::Layer
{
public:

	GameSceneManager *gsm;
	Director* director;
	Size visibleSize;
	Point origin;

//	MusicHelp* mh;//���������� ָ��
	SpriteManager* sh;//���������  ָ��
	PauseCode* pc;//��ͣ����ָ��
	GDData* gdData;
	FlyObject* fo;
	std::string* ids;

	bool isUpdateAll = true;//�Ƿ����UpdateAll�����Ļص�


	Barrier* tb;
//	Barrier* zh;
	std::vector<Barrier*>::iterator iter;
	std::vector<Barrier*> barrierVector;//���ϰ����vector

	std::map<std::string,Sprite*> spMap;



	int timeCountCollision = 0;//��ײʱ�������
	int timeCount = 0;




	bool isTouch=false;

    virtual bool init();//��ʼ���ķ���


	//��ʼ�����¼��Ĵ�����
	bool myOnTouchBegan(Touch *touch, Event *event);
	//�����ƶ��¼��Ĵ�����
	void myOnTouchMoved(Touch *touch, Event *event);
	//���ؽ����¼��Ĵ�����
	void myOnTouchEnded(Touch *touch, Event *event);
	//������ֹ�¼��Ĵ�����
	void myOnTouchCancelled(Touch *touch, Event *event);

	void updateAll();//�������еķ���
	void updateBarrier();
	void collisionDetection();
	void deleteBarrier();//ɾ�� ����Ļ�� �ϰ���  �ķ���

    //Cocos2d-x�ж����һ���꣬����ָ�����͵Ķ���
    //��������Ӧ�ĳ�ʼ�����ͷŹ���
    CREATE_FUNC(FlyLayer);
};

#endif
