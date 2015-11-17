#include "FlyLayer.h"
#include "../frameHelp/ParticleSystemHelp.h"
#include "../frameHelp/MusicManager.h"
#include "Constant.h"

bool FlyLayer::init()
{
	//调用父类的初始化
    if (!Layer::init())
    {
        return false;
    }

    this->setTag(INDEX_FLYLAYER);//设置节点的标签

    visibleSize = Director::getInstance()->getVisibleSize();//获取可见区域尺寸
	origin = Director::getInstance()->getVisibleOrigin();//获取可见区域原点坐标

	setTouchEnabled(true);
	auto listenerET = EventListenerTouchOneByOne::create();//创建一个触摸监听
	listenerET->setSwallowTouches(true);//设置下传触摸
	listenerET->onTouchBegan = CC_CALLBACK_2(FlyLayer::myOnTouchBegan, this);//开始触摸时回调onTouchBegan方法
	listenerET->onTouchMoved = CC_CALLBACK_2(FlyLayer::myOnTouchMoved, this);//触摸移动时回调onTouchMoved方法
	listenerET->onTouchEnded = CC_CALLBACK_2(FlyLayer::myOnTouchEnded, this);//抬起时回调onTouchEnded方法
	listenerET->onTouchCancelled = CC_CALLBACK_2(FlyLayer::myOnTouchCancelled, this);//终止触摸时回调onTouchCancelled方法

	sh = new SpriteManager(this);
	sh->SpPause();//添加 暂停图片精灵
	sh->backgroundRoll();

	new ParticleSystemHelp();
	pc = new PauseCode(this);

	//取数据的代码
	int p1 = UserDefault::getInstance()->getIntegerForKey("1",779);
	int p2 = UserDefault::getInstance()->getIntegerForKey("2",110);
	int p3 = UserDefault::getInstance()->getIntegerForKey("3",30);
	int p4 = UserDefault::getInstance()->getIntegerForKey("4",30);

	ids = new std::string("JC");//跳跃飞行器
	fo =new FlyObject(ids, this, Rect(568,23,606-568,46-23), 32, 18, 64, 36,
					  Rect(p1,p2,p3,p4), 32, 35, 26, 26,
								 3);//创建飞行器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerET->clone(), fo->sp);//注册监听器

	//关卡数据
	gdData = new GDData(this);
	gdData->createFlyData();

	if(MusicManager::onSound == true)
	{
		MusicManager::playFlyLayerMusic();//播放背景音乐
	}
	else
	{
		MusicManager::noPlaySound = true;
	}


	//设置定时回调指定方法干活
	Director* director = Director::getInstance();
	auto sched = director->getScheduler();

	sched->scheduleSelector(SEL_SCHEDULE(&FlyLayer::updateAll), this, INTERVAL, false);//不断回调

	return true;
}

void FlyLayer::updateAll()
{
	if(timeCount == 1300)
	{
		//背景停止移动
		spMap["bg"]->stopAllActions();
		spMap["bg1"]->stopAllActions();
		//将地面静止  的代码
		iter=barrierVector.begin();
		for(;iter!=barrierVector.end();iter++)
		{
			if(((std::string*)((*iter)->st))->at(0) == 'd')
			{
				(*iter)->sp->stopAllActions();
			}
		}
		sh->win();
		return;
	}

	if(isUpdateAll == false)
	{
		timeCountCollision++;
		//背景停止移动
		spMap["bg"]->stopAllActions();
		spMap["bg1"]->stopAllActions();

		if(timeCountCollision * INTERVAL >= 0.2)//碰撞后，有0.2s的停留时间
		{
			timeCountCollision = 0;
			gsm->goFlyLayer();
		}
		return;
	}

	timeCount++;
	gdData->createFlyData();

	fo->updata();//更新飞行器的状态

	updateBarrier();//更新 障碍物的方法
	collisionDetection();
	deleteBarrier();
}

void FlyLayer::collisionDetection()
{
	if(barrierVector.empty())
		return;
	iter=barrierVector.begin();
	for(;iter!=barrierVector.end();iter++)
	{
		if((*iter)->collisionFo(fo))//碰撞检测
		{
			isUpdateAll = false;
		}
	}
}
void FlyLayer::updateBarrier()
{
	if(barrierVector.empty())
		return;
	iter=barrierVector.begin();
	for(;iter!=barrierVector.end();iter++)
	{
		(*iter)->reflesh();
	}
}
void FlyLayer::deleteBarrier()//删除 出屏幕的 障碍物
{
	if(barrierVector.empty())//若障碍物列表 为空  则返回
		return;

	iter=barrierVector.begin();
	for(;iter!=barrierVector.end();)
	{
		if((*iter)->sp->getPosition().x+(*iter)->lengthX/2 < 0)
		{
			this->removeChild((*iter)->sp,true);
			iter = barrierVector.erase(iter);//iter = 指向iter的下一个   并从barrierVector删掉iter
		}
		else{iter++;}
	}
}


//开始触控事件的处理方法
bool FlyLayer::myOnTouchBegan(Touch *touch, Event *event)
{
	isTouch = true;
	return true;
}
//触控移动事件的处理方法
void FlyLayer::myOnTouchMoved(Touch *touch, Event *event){}
//触控结束事件的处理方法
void FlyLayer::myOnTouchEnded(Touch *touch, Event *event)
{
	isTouch = false;
}
//触控终止事件的处理方法
void FlyLayer::myOnTouchCancelled(Touch *touch, Event *event){myOnTouchEnded(touch,event);}
