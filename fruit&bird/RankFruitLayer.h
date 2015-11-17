#ifndef _RankFruitLayer_H_
#define _RankFruitLayer_H_

#include "cocos2d.h"
#include "GameSceneManager.h"

using namespace cocos2d;

class RankFruitLayer : public Layer
{
public:
	//������¼�����ַ���
	std::string scoreFruit[5];
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
	CREATE_FUNC(RankFruitLayer);
};

#endif
