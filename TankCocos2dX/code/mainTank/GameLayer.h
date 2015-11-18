#ifndef _GameLayer_H_
#define _GameLayer_H_

#include "cocos2d.h"
#include "TankSceneManager.h"

USING_NS_CC;

class GameLayer : public Layer
{
public:
	//场景管理器
	TankSceneManager *tsm;
	//红色坦克
	Sprite *redTank;
	Sprite *redTankGun;
	//绿色坦克
	Sprite *greenTank;
	Sprite *greenTankGun;

	int bossTag=0;
	int bossX=0;
	int bossY=0;
	int bossNumber=0;

	//定时回调更新界面
	void update();
	void updateTank();
	void updateBoss();
	void updateMap();
	void updateBullet();
	//根据数据执行操作
	void setExplosion();//爆炸
	void setMainBullet();//玩家坦克子弹
	void setMainMissile();//玩家坦克导弹
	void setOtherBullet();//敌方坦克子弹
	void setMapTree();//树
	void setAward();//奖励
	void setMapData();//其他物体
	void setMapTank();//敌方坦克
	void setBossBullet();//boss
	void setNewBoss();//boss参数
	void setClear();//清空boss
	//坦克移动
	void moveTank(int redX, int redY, float redAngle, int greenX, int greenY, float greenAngle);
	void rotateGun(float redAngle, float greenAngle);
	//初始化方法
	virtual bool init();
	//初始化坦克
	void initTank();
	//初始化物体图片
	void initBatchNode();
	void initOneBatchNode(const char *path,int layer, int tag);

	CREATE_FUNC(GameLayer);
};
#endif
