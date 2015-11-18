#ifndef  _Weapon_H_
#define  _Weapon_H_
#include "cocos2d.h"

using namespace cocos2d;

//自定义的精灵类
class Weapon : public cocos2d::Sprite
{
public:
	//构造函数
    Weapon();
	//防御塔的id， 1，2，3，4（白绿红蓝）
	int id;
	//武器的级别，1，2，3，4
	int level;
	//发射子弹的速率
	int updatetime;
	//防御塔的攻击范围
	int confines;
	//防御塔的伤害值
	int hurt;
	//防御塔的角度
	float angle;
	//安装防御塔需要的金币数
	int value;
	//升级防御塔需要的金币数
	int upValue;
	//卖掉防御塔得到的金币数
	int sellValue;
	//发射子弹的标志位
	bool fire;
	//更新防御塔的标志位
	bool updateMark;
    //创建防御塔的几个方法
    static Weapon* create(int id,int level,float angle);
    static Weapon* create(int id);
    static Weapon* create(const char* pic,int id);
    //升级防御塔的方法
    void updateData();
    //升级防御塔前的准备方法
    void update();
    //发射子弹的方法
    void fireing();
    //设置发射子弹的方法
    void setFire();
    Point pointColRow;
    ProgressTimer *left;

    //系统定义的一个宏，做好相应的初始化与释放工作
    CREATE_FUNC(Weapon);
};

#endif
