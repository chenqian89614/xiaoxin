#include "BulletSprite.h"
#include "cocos2d.h"
#include "GameSceneManager.h"

using namespace cocos2d;

//构造函数
BulletSprite::BulletSprite(){}

//创建子弹的方法
BulletSprite* BulletSprite::create(const char* pic,int id)
{
	//声明一个指向子弹的指针temp
	BulletSprite* temp = new BulletSprite();
	//初始化子弹精灵对象
	temp->initWithFile(pic);
	//自动释放
	temp->autorelease();
	//拿到子弹的id
	temp->id = id;
	//设置初始的角度
	temp->angle=0;

	return temp;
}

//创建子弹的方法
BulletSprite* BulletSprite::create(const char* pic,int hurt,int target)
{
	//声明指向子弹的指针
	BulletSprite* temp = new BulletSprite();
	//初始化子弹精灵对象
	temp->initWithFile(pic);
	//自动释放
	temp->autorelease();
	//拿到子弹的伤害值
	temp->hurt = hurt;
	//拿到当前的目标野怪
	temp->target = target;
	//设置发射子弹的角度
	temp->angle=0;

	return temp;
}
