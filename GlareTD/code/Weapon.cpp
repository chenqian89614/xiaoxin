#include "Weapon.h"
//#include "AppMacros.h"
//#include <string.h>
//#include <string>
#include "cocos2d.h"
#include "GameSceneManager.h"

using namespace cocos2d;

//构造函数
Weapon::Weapon(){}

//创建四个防御塔菜单精灵时调用的创建方法
Weapon* Weapon::create(const char* pic,int id)//入口参数武器的id
{
	//创建一个防御塔对象
	Weapon* temp = new Weapon();
	//初始化安装防御塔时金币的消耗
	int sValue[4]={15,25,30,50};
	//四种防御塔的初始攻击范围
	int confinesTable[4]={100,100,100,80};
	//四种防御塔初始发射子弹的速率
	float updatetimeTable[4]={1.2,1.2,1.2,1.2};
	//四种防御塔的初始伤害值
	int hurtTable[4]={10,15,20,25};
	//初始化防御塔精灵对象
	temp->initWithFile(pic);
	//自动释放
	temp->autorelease();
	//拿到当前防御塔的id
	temp->id = id;
	//初始化防御塔的级别为1
	temp->level = 1;
	//根据id设置安装各防御塔时需要的金币
	temp->value = sValue[id-1];
	//根据id设置各防御塔发射子弹的速率
	temp->updatetime=updatetimeTable[id-1];
	//发射子弹的标志位
	temp->fire=true;
	//根据id设置各防御塔的初始伤害
	temp->hurt=hurtTable[id-1];
	//根据id设置各防御塔的初始攻击范围
	temp->confines=confinesTable[id-1];
	//创建一个表示选中防御塔时显示效果的精灵对象
	Sprite* scope= Sprite::create("ring.png");
	//设置该精灵对象的尺寸
	float scale=(float)confinesTable[id-1]/(scope->getContentSize().width/2);
	scope->setScale(scale);
	//设置位置
	scope->setPosition(Point(24,24));
	//将该对象添加到布景中
	temp->addChild(scope,4,1);
	//设置该精灵对象初始为不可见
	scope->setVisible(false);
	//设置升级防御塔的标志位为false
	temp->updateMark=false;

	return temp;
}

//创建一级防御塔时调用的方法，入口参数为武器的id
Weapon* Weapon::create(int id)
{
	//创建一个防御塔精灵对象
	Weapon* temp = new Weapon();
	//定义一个存放一级防御塔的字符串数组
	std::string picTable[4] = {"white_1.png","green_1.png","red_1.png","blue_1.png"};
	//初始化安装防御塔时金币的消耗
	int sValue[4]={15,25,30,50};
	//四种防御塔从1级升级到2级时的金币消耗
	int uValue[4]={15,20,30,40};
	//四种防御塔的初始攻击范围
	int confinesTable[4]={100,100,100,80};
	//四种防御塔初始发射子弹的速率
	float updatetimeTable[4]={1.2,1.2,1.2,1.2};
	//四种防御塔的初始伤害值
	int hurtTable[4]={10,15,20,25};
	//初始化防御塔精灵对象
	temp->initWithFile(picTable[id-1].c_str());
	//自动释放
	temp->autorelease();
	//拿到当前防御塔的id
	temp->id = id;
	//初始化防御塔的级别为1
	temp->level = 1;
	//根据id设置安装各防御塔时需要的金币
	temp->value = sValue[id-1];
	//卖掉防御塔时得到的金币
	temp->sellValue = temp->value/2;
	//根据id设置各防御塔由1级升到2级时需要的金币
	temp->upValue = uValue[id-1];
	//根据id设置各防御塔发射子弹的速率
	temp->updatetime=updatetimeTable[id-1];
	//发射子弹的标志位
	temp->fire=true;
	//根据id设置各防御塔的初始伤害
	temp->hurt=hurtTable[id-1];
	//根据id设置各防御塔的初始攻击范围
	temp->confines=confinesTable[id-1];
	//创建一个表示选中防御塔时显示效果的精灵对象
	Sprite* scope= Sprite::create("ring.png");
	//根据当前防御塔的攻击范围来设置该效果精灵的尺寸
	float scale=(float)confinesTable[id-1]/(scope->getContentSize().width/2);
	scope->setScale(scale);
	//设置该精灵对象的位置
	scope->setPosition(Point(24,24));
	//将该精灵对象添加到布景中
	temp->addChild(scope,4,1);
	//设置该精灵对象初始为不可见
	scope->setVisible(false);
	//设置升级防御塔的标志位为false
	temp->updateMark=false;

	return temp;
}

//创建防御塔精灵对象(升级时调用的创建方法),参数分别为防御塔的id，等级，角度
Weapon* Weapon::create(int id,int level,float angle)
{
	//创建一个对象
	Weapon* temp = new Weapon();
	std::string picTable[4][3] = {{"white_2.png","white_3.png","white_4.png"},
			{"green_2.png","green_3.png","green_4.png"},
			{"red_2.png","red_3.png","red_4.png"},
			{"blue_2.png","blue_3.png","blue_4.png"}};//白，绿，红，蓝
	//四种防御塔三个不同等级下每发子弹的伤害值
	int hurtTable[4][3]={
			{20,30,60},
			{25,35,45},
			{30,40,50},
			{35,45,55}
	};
	//四种防御塔三个不同等级下的攻击范围
	int confinesTable[4][3]={
			{120,140,160},
			{100,100,100},
			{130,160,180},
			{100,110,120}
	};
	//发射子弹的速率，数值越大表示发射速度越快
	float updatetimeTable[4][3]={
			{1.5,8.0,4.0},
			{1.3,1.4,1.5},
			{1.3,1.4,1.5},
			{1.5,1.8,2.1}
	};
	//自动释放
	temp->autorelease();
	//初始化存放图片的格子
	temp->initWithFile(picTable[id-1][level-1].c_str());
	//根据当前选中的防御塔的id及等级来设置该防御塔的伤害
	temp->hurt=hurtTable[id-1][level-1];
	//根据当前选中的防御塔的id及等级来设置该防御塔的攻击范围
	temp->confines=confinesTable[id-1][level-1];
	//根据当前选中的防御塔的id及等级来设置该防御塔发射子弹的速率
	temp->updatetime=updatetimeTable[id-1][level-1];
	//设置武器的旋转角度
	temp->setRotation(angle);

	return temp;
}

//升级防御塔前的准备方法
void Weapon::update()
{
	//如果防御塔的等级为4级或者表示更新的标志位为true
	if(level==4||this->updateMark==true)
	{
		return;
	}
	//将防御塔更新的标志位设置为true
	this->updateMark=true;
	//创建一个百分比动作特效，在4秒的时间内从0到百分之百
	ProgressTo *to1 = ProgressTo::create(4, 100);
	//创建一个用于显示升级进度的精灵对象
	left = ProgressTimer::create(Sprite::create("ring2.png"));
	//设置工作模式为半径模式
	left->setType(ProgressTimer::Type::RADIAL);
	//设置旋转角度
	left->setRotation(angle-90);
	//将特效添加到布景中
	addChild(left);
	//设置位置
	left->setPosition(Point(24,24));
	left->runAction(
			Sequence::create(
					to1,
					CallFuncN::create(CC_CALLBACK_0(Weapon::updateData,this)),
					NULL));
}

//升级防御塔的方法
void Weapon::updateData()
{
	//拿到当前选中防御塔的id
	int id = this->id;
	//拿到当前选中防御塔的等级
	int level = this->level;
	//设置升级防御塔时的金币消耗
	this->upValue+=level*10;
	//设置卖掉防御塔时的金币收入
	this->sellValue+=level*5;
	//存放升级用到的各阶段的防御塔精灵对象的数组
	std::string picTable[4][3] = {{"white_2.png","white_3.png","white_4.png"},
			{"green_2.png","green_3.png","green_4.png"},
			{"red_2.png","red_3.png","red_4.png"},
			{"blue_2.png","blue_3.png","blue_4.png"}};//白，绿，红，蓝
	//初始化防御塔从2级升到4级各阶段的伤害
	int hurtTable[4][3]={
			{20,30,60},
			{25,35,45},
			{30,40,50},
			{35,45,55}
	};
	//初始化防御塔从2级升到4级各阶段的攻击范围
	int confinesTable[4][3]={
			{120,140,160},
			{100,100,100},
			{130,160,180},
			{100,110,120}
	};
	//初始化防御塔从2级升到4级各阶段发射子弹的速率
	float updatetimeTable[4][3]={
			{1.5,8.0,4.0},
			{1.3,1.4,1.5},
			{1.3,1.4,1.5},
			{1.5,1.8,2.1}
	};
	//初始化防御塔精灵对象
	this->initWithFile(picTable[id-1][level-1].c_str());
	//根据当前防御塔的id及等级设置其伤害
	this->hurt=hurtTable[id-1][level-1];
	//根据当前防御塔的id及等级设置其攻击范围
	this->confines=confinesTable[id-1][level-1];
	//根据当前防御塔的id及等级设置其发射子弹的速率
	this->updatetime=updatetimeTable[id-1][level-1];
	//创建一个用来显示攻击范围的精灵对象
	Sprite* scope=(Sprite*)this->getChildByTag(1);
	//设置其尺寸的大小
	float width=(float)scope->getContentSize().width/2;
	float scale=this->confines/width;
	scope->setScale(scale);
	//升级成功后将其等级自加
	this->level++;
	//然后将升级的标志位设置为false
	this->updateMark=false;
	//将发射子弹的标志位设置为true
	this->fire=true;
	this->removeChild(left,true);
}

//发射子弹的方法
void Weapon::fireing()
{
	//初始化当前发射子弹的标志位为false
	this->fire=false;
	//顺序执行发射子弹的动作，不同id的防御塔不可以同时发射子弹
	this->runAction(
			Sequence::create(
					//延时1秒
					DelayTime::create(1),
					CallFuncN::create(CC_CALLBACK_0(Weapon::setFire,this)),
					NULL
			)
			);
}

//设置发射子弹的方法
void Weapon::setFire()
{
	//如果当前更新防御塔的标志位为false
	if(this->updateMark==false)
	{
		//将发射子弹的标志位设为true
		this->fire=true;
	}
}
