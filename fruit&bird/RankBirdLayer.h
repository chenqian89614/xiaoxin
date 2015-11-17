#ifndef _RankBirdLayer_H_
#define _RankBirdLayer_H_

#include "cocos2d.h"
#include "GameSceneManager.h"

using namespace cocos2d;

class RankBirdLayer : public Layer
{
public:
	//������¼�����ַ���
	std::string scoreBird[5];
	//������ʾ�������ı�
	Label* labels;
	//��������ָ��
	GameSceneManager* sceneManager;
public:
	//��ʼ������
	virtual bool init();
	//��¼����
	void save (int);
	//��ȡ����
	void load();
	//����ס�˵���
	void menuCallBack0(Ref* pSender);
	void menuCallBack1(Ref* pSender);
	CREATE_FUNC(RankBirdLayer);
};

#endif
