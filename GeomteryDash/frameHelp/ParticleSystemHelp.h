#ifndef _ParticleSystemHelp_H_
#define _ParticleSystemHelp_H_

#include "cocos2d.h"
#include "../hellocpp/Constant.h"

using namespace cocos2d;

class ParticleSystemHelp
{
public :
	ParticleSystemHelp(){
	}
	void createSnow()
	{
		psq3 = ParticleSnow::create();			//创建下雪粒子系统效果
		psq3->retain();										//保持引用
		psq3->setTexture( Director::getInstance()->getTextureCache()->addImage("pic/snow.png") );	//为粒子系统设置图片
		psq3->setPosition( Point(WIDTH/2, HEIGHT) );						//设置粒子系统的坐标
		psq3->setLife(3);										//设置粒子系统的生命值
		psq3->setLifeVar(1);   								//设置粒子系统的生命变化值
		psq3->setGravity(Point(0,-10));							//设置粒子系统的重力向量
		psq3->setSpeed(130);									//设置粒子系统的速度值
		psq3->setSpeedVar(30);    							//设置粒子系统的速度变化值
		psq3->setStartColor((Color4F){0.9,0.9,0.9,1});				//设置粒子系统的开始颜色值
		psq3->setStartColorVar((Color4F){0,0,0.1,1});				//设置粒子系统的开始颜色变化值
		psq3->setEmissionRate(psq3->getTotalParticles()/psq3->getLife());	//设置粒子系统的发射速率
//		this->addChild(psq3, 0);								//将粒子系统添加到精灵中
	}


public :
	ParticleSystemQuad* psq1 = ParticleSystemQuad::create("pic/GC/dragEffect.plist");//在地面滑行的时候    方块后面的特效
	bool isPsq1 = false;
	ParticleSystemQuad* psq2 = ParticleSystemQuad::create("pic/GC/explodeEffect.plist");//撞击后，  方块爆炸的特效
	ParticleSystemQuad* psq3;


};

#endif
