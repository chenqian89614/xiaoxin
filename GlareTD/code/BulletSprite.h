#ifndef  _BulletSprite_H_
#define  _BulletSprite_H_

#include "cocos2d.h"
#include "Monsters.h"

//自定义的精灵类
class BulletSprite : public cocos2d::Sprite
{
public:
	//构造函数
    BulletSprite();
	//子弹的编号，有三种1，2，3
	int id;
	//子弹的伤害值
	int hurt;
	//目标野怪
	int target;
	//子弹的角度
	float angle;
    //创建子弹的方法(参数为图片和子弹的id)
    static BulletSprite* create(const char* pic,int id);
    //创建子弹对象(参数为图片伤害值和目标野怪)
    static BulletSprite* create(const char* pic,int hurt,int target);
    //怪物减血方法
    void updata(int bulletId);

    //做好相应的初始化与释放工作
    CREATE_FUNC(BulletSprite);
};

#endif
