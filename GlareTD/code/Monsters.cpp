#include "Monsters.h"
#include "cocos2d.h"
#include "GameSceneManager.h"

using namespace cocos2d;

//构造函数
Monsters::Monsters(){}

//初始时创建怪对象的方法(参数为怪的id，及路径)
Monsters* Monsters::create(int id,vector <Point > selfWay)//入口参数怪物的id
{
	//几种野怪的图片路径
	std::string picTable[6] = {"square.png","triangle.png","circle.png",
									"id_4.png","id_5.png","id_6.png"
	};
	//创建一个野怪对象
	Monsters* temp = new Monsters();
	//初始化野怪精灵对象
	temp->initWithFile(picTable[id-1].c_str());
	//自动释放
	temp->autorelease();
	//获取当前野怪的id
	temp->id = id;
	//根据id设置野怪的血量
	temp->blood =100*id;
	//根据id设置怪的最大血量值
	temp->maxBlood=100*id;
	//初始化路径
	temp->way=0;
	//野怪拿到属于自己的路径
	temp->selfWay = selfWay;
	//创建一个表示野怪血条的精灵对象
	Sprite* blood = Sprite::create("blood.png");
	//设置其锚点
	blood->setAnchorPoint(Point(0.5,0));
	//起始设置为不可见
	blood->setVisible(false);
	//设置位置
	blood->setPosition(Point(0,0));
	//设置血条的长度
	blood->setScaleY(1);
	//将血条精灵对象添加到布景中
	temp->addChild(blood,6,1);

	return temp;
}
//创建怪对象
Monsters* Monsters::create(int id,int blood,int way,int maxBlood,vector <Point > selfWay)//入口参数怪物的id
{
	std::string picTable[6] = {"square.png","triangle.png","circle.png",
									"id_4.png","id_5.png","id_6.png"
	};
	//创建一个野怪精灵对象
	Monsters* temp = new Monsters();
	//初始化对象
	temp->initWithFile(picTable[id-1].c_str());
	//自动释放
	temp->autorelease();
	//拿到当前怪的id
	temp->id = id;
	//拿到当前怪的血量
	temp->blood = blood;
	//拿到当前怪的最大血量
	temp->maxBlood=maxBlood;
	//拿到当前的路径
	temp->way=way;
	//拿到存放路径的数组
	temp->selfWay = selfWay;
	//创建一个表示血量的精灵对象
	Sprite* blood1 = Sprite::create("blood.png");
	//设置锚点
	blood1->setAnchorPoint(Point(0.5,0));
	//设置为不可见
	blood1->setVisible(false);
	//设置位置
	blood1->setPosition(Point(0,0));
	//设置血条的长度
	blood1->setScaleY(1);
	//添加到布景中
	temp->addChild(blood1,6,1);

	return temp;
}

//怪物减血的方法
void Monsters::cutBlood(int hurt)//入口参数子弹的id
{
	//被击中后当前血量值等于原血量值减去子弹的伤害值
	this->blood-=hurt;
	//将血条设置为可见
	(this->getChildByTag(1))->setVisible(true);
	//剩余血量值等于当前血量值比上最大血量值
	float scaleY = (float)blood/maxBlood;
	//设置血量值
	(this->getChildByTag(1))->setScaleY(scaleY);
	//顺序执行怪血条可见与不可见的效果，延迟为0.5秒
	(this->getChildByTag(1))->runAction(
			Sequence::create(
								DelayTime::create(0.5),
								CallFuncN::create(CC_CALLBACK_0(Monsters::setVisibleFalse,this)),
								NULL
								)

	);
	//创建血条精灵对象
	Sprite* blood = Sprite::create("blood.png");
	//设置锚点
	blood->setAnchorPoint(Point(0.5,0));
	//初始将血条设置为不可见
	blood->setVisible(false);
	//设置血条的位置
	blood->setPosition(Point(0,0));
	//设置血条的长度
	blood->setScaleY(scaleY);
	//顺序执行删除表示血条精灵
	blood->runAction(
			Sequence::create(
								DelayTime::create(0.5),
								CallFuncN::create(CC_CALLBACK_1(Monsters::removeSprite,this)),
								NULL
								)
	);
}

//设置怪头顶的血条为是否可见的方法
void Monsters::setVisibleFalse()
{
	((Sprite*)(this->getChildByTag(1)))->setVisible(false);
}

//第二种野怪运动过程中转弯时要调用的方法
void Monsters::refresh(float angle)
{
	//怪中心到左上角点向量
	Point vector;
	//怪的属性
	Point orgin;
	//怪精灵的宽
	orgin.x=this->getContentSize().width/2;
	//怪精灵的高
	orgin.y=this->getContentSize().height/2;
	vector.x=-orgin.x;
	vector.y=-orgin.y;
	//求向量的长度
	float length=ccpLength(vector);
	//获取此向量的角度
	float angleOrgin=ccpToAngle(vector);
	//矫正血条的角度，保证怪旋转的时候血条不旋转
	Point dirction=ccpForAngle(-angle+angleOrgin);
	//计算血条相对屏幕的位置
	Point position=ccpAdd(orgin,ccpMult(dirction,length));
	//设置血条的位置
	((Sprite*)(this->getChildByTag(1)))->setPosition(position);
	//设置血条的角度
	((Sprite*)(this->getChildByTag(1)))->setRotation(angle*180/3.1415925);
}

//删除血条精灵对象的方法
void Monsters::removeSprite(Node*node)
{
	this->removeChild(node,true);
}
