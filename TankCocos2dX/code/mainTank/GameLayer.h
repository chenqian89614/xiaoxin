#ifndef _GameLayer_H_
#define _GameLayer_H_

#include "cocos2d.h"
#include "TankSceneManager.h"

USING_NS_CC;

class GameLayer : public Layer
{
public:
	//����������
	TankSceneManager *tsm;
	//��ɫ̹��
	Sprite *redTank;
	Sprite *redTankGun;
	//��ɫ̹��
	Sprite *greenTank;
	Sprite *greenTankGun;

	int bossTag=0;
	int bossX=0;
	int bossY=0;
	int bossNumber=0;

	//��ʱ�ص����½���
	void update();
	void updateTank();
	void updateBoss();
	void updateMap();
	void updateBullet();
	//��������ִ�в���
	void setExplosion();//��ը
	void setMainBullet();//���̹���ӵ�
	void setMainMissile();//���̹�˵���
	void setOtherBullet();//�з�̹���ӵ�
	void setMapTree();//��
	void setAward();//����
	void setMapData();//��������
	void setMapTank();//�з�̹��
	void setBossBullet();//boss
	void setNewBoss();//boss����
	void setClear();//���boss
	//̹���ƶ�
	void moveTank(int redX, int redY, float redAngle, int greenX, int greenY, float greenAngle);
	void rotateGun(float redAngle, float greenAngle);
	//��ʼ������
	virtual bool init();
	//��ʼ��̹��
	void initTank();
	//��ʼ������ͼƬ
	void initBatchNode();
	void initOneBatchNode(const char *path,int layer, int tag);

	CREATE_FUNC(GameLayer);
};
#endif
