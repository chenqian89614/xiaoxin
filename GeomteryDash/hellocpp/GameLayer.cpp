#include "GameLayer.h"
#include "../frameHelp/ParticleSystemHelp.h"
#include "../frameHelp/MusicManager.h"
#include "Constant.h"

bool GameLayer::init()
{
	//调用父类的初始化
    if (!Layer::init())
    {
        return false;
    }

    this->setTag(INDEX_GRAMLAYER);//设置节点的标签

    visibleSize = Director::getInstance()->getVisibleSize();//获取可见区域尺寸
	origin = Director::getInstance()->getVisibleOrigin();//获取可见区域原点坐标

	new ParticleSystemHelp();
	//精灵帮助类
	sh = new SpriteManager(this);
	sh->SpPause();//添加 暂停图片精灵
	sh->backgroundRoll();

	pc = new PauseCode(this);

	initObjectOrSprite();//初始化   背景 、  地面物体  和  跳跃的方块

	//关卡数据
	gdData = new GDData(this);
	if(indexGK == 1)
	{
		gdData->createData();
	}
	else if(indexGK == 3)
	{
		gdData->createData3();
	}

	//设置定时回调指定方法干活
	Director* director = Director::getInstance();
	auto sched = director->getScheduler();

	sched->scheduleSelector(SEL_SCHEDULE(&GameLayer::updateAll), this, INTERVAL, false);//不断回调

	return true;
}

void GameLayer::updateAll()
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
	timeCount++;
	if(isUpdateAll == false)
	{
		timeCountCollision++;
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
		if(timeCountCollision * INTERVAL >= 0.2)//碰撞后，有0.2s的停留时间
		{
			timeCountCollision = 0;
			gsm->goGameLayer(indexGK);
		}
		return;
	}
	if(indexGK == 1)
	{
		gdData->createData();
	}
	else if(indexGK == 3)
	{
		gdData->createData3();
	}
//	CCLOG("%d",timeCount);

	if(jc->isJump == true && jc->isDown == false)
	{
		jc->Jump();
	}
	if(jc->isJump == false && jc->isDown == true)
	{
		jc->Down();
	}
	if(jc->isJump == false && jc->isDown == false)
	{
		refleshJumpCube();//更新  跳跃方块  的状态
	}
	//实现 手指一直点着屏幕   跳跃方块  一直跳跃的功能
	if( isTouch == true )//判断是否触摸
	{
		if(jc->isDown == false && jc->isJump == false)//跳跃方块  既不处于 跳跃状态  又不处于  下落状态
		{
			jc->isJump = true;
		}
	}

	collisionDetection();
	updateBarrier();//更新 障碍物的方法
	deleteBarrier();
}

void GameLayer::updateBarrier()
{
	if(barrierVector.empty())
		return;
	bool flagUpdateBarrier = false;
	iter=barrierVector.begin();
	for(;iter!=barrierVector.end();iter++)
	{
		(*iter)->reflesh();
		if(((std::string*)((*iter)->st))->at(0) == 'd')
		{
			if((*iter)->sp->getPosition().x+(*iter)->lengthX/2 <= 0)
			{
				float x = zh->sp->getPosition().x + visibleSize.width/4;
				float y = zh->sp->getPosition().y;
				ids = new std::string("dm5");//矩形地面id
				zh=new RectBarrier(ids,this,Rect(129,685,243-129,802-685), x, y, visibleSize.width/4, visibleSize.height*0.25, GroundZOrder);//创建矩形
				zh->sp->setColor(Color3B(125,7,216));
				flagUpdateBarrier = true;
				zh->reflesh();
			}
		}
	}
	if(flagUpdateBarrier == true)
		barrierVector.push_back(zh);
}
void GameLayer::collisionDetection()
{
	if(barrierVector.empty())
		return;
	iter=barrierVector.begin();
	for(;iter!=barrierVector.end();iter++)
	{
		float min = jc->sp->getPosition().x-jc->lengthX/2;//跳跃方块的左边儿
		float max = jc->sp->getPosition().x+jc->lengthX/2;//跳跃方块的右边儿
		float target1 = (*iter)->sp->getPosition().x - (*iter)->lengthX/2;//障碍物的左边
		float target2 = (*iter)->sp->getPosition().x + (*iter)->lengthX/2;//障碍物的右边
		if(min<=target2&&target1<=max)
		{
			if((*iter)->collision(jc))//碰撞检测
			{
				isUpdateAll = false;
			}
		}
	}
}
//当跳跃方块  处于   isJump==false  和   isDown==false  的状态时    调用该方法
void GameLayer::refleshJumpCube()
{
	if(barrierVector.empty())
		return;
	float maxH = 0;
	for(std::vector<Barrier*>::iterator iter=barrierVector.begin();iter!=barrierVector.end();iter++)
	{
		float center = jc->sp->getPosition().x;//跳跃方块的中心
		float target1 = (*iter)->sp->getPosition().x - (*iter)->lengthX/2;//障碍物的左边
		float target2 = (*iter)->sp->getPosition().x + (*iter)->lengthX/2;//障碍物的右边

		if(target1<=center&&center<=target2)//跳跃方块的中心 大于等于  障碍物的左边  && 跳跃方块的中心 小于等于  障碍物的右边
		{
			if((*iter)->sp->getPosition().y + (*iter)->lengthY/2 + jc->lengthY/2 > maxH)
			{
				maxH = (*iter)->sp->getPosition().y + (*iter)->lengthY/2 + jc->lengthY/2;
			}
		}
	}
	jc->reflesh(maxH);//跳跃方块 的  更新方法
}

void GameLayer::deleteBarrier()//删除 出屏幕的 障碍物
{
	if(barrierVector.empty())//若障碍物列表 为空  则返回
		return;

	iter=barrierVector.begin();
	for(;iter!=barrierVector.end();)
	{
		if((*iter)->sp->getPosition().x+(*iter)->lengthX/2 < 0)
		{
			this->removeChild((*iter)->sp,true);
			iter = barrierVector.erase(iter);//iter = 指向iter的下一个
		}
		else{iter++;}
	}
}

//开始触控事件的处理方法
bool GameLayer::myOnTouchBegan(Touch *touch, Event *event)
{
	isTouch = true;
	return true;
}
//触控移动事件的处理方法
void GameLayer::myOnTouchMoved(Touch *touch, Event *event){}
//触控结束事件的处理方法
void GameLayer::myOnTouchEnded(Touch *touch, Event *event)
{
	isTouch = false;
}
//触控终止事件的处理方法
void GameLayer::myOnTouchCancelled(Touch *touch, Event *event){myOnTouchEnded(touch,event);}
void GameLayer::initObjectOrSprite()
{
	setTouchEnabled(true);
	auto listenerET = EventListenerTouchOneByOne::create();//创建一个触摸监听
	listenerET->setSwallowTouches(true);//设置下传触摸
	listenerET->onTouchBegan = CC_CALLBACK_2(GameLayer::myOnTouchBegan, this);//开始触摸时回调onTouchBegan方法
	listenerET->onTouchMoved = CC_CALLBACK_2(GameLayer::myOnTouchMoved, this);//触摸移动时回调onTouchMoved方法
	listenerET->onTouchEnded = CC_CALLBACK_2(GameLayer::myOnTouchEnded, this);//抬起时回调onTouchEnded方法
	listenerET->onTouchCancelled = CC_CALLBACK_2(GameLayer::myOnTouchCancelled, this);//终止触摸时回调onTouchCancelled方法


	//======地面====
	ids = new std::string("dm1");//矩形地面id
	tb=new RectBarrier(ids,this,Rect(129,685,243-129,802-685),visibleSize.width/8,visibleSize.height/8, visibleSize.width/4, visibleSize.height*0.25, GroundZOrder);//创建矩形
	tb->sp->setColor(Color3B(125,7,216));
	barrierVector.push_back(tb);

	ids = new std::string("dm2");//矩形地面id
	tb=new RectBarrier(ids,this,Rect(129,685,243-129,802-685),visibleSize.width/8*3,visibleSize.height/8, visibleSize.width/4, visibleSize.height*0.25, GroundZOrder);//创建矩形
	tb->sp->setColor(Color3B(125,7,216));
	barrierVector.push_back(tb);

	ids = new std::string("dm3");//矩形地面id
	tb=new RectBarrier(ids,this,Rect(129,685,243-129,802-685),visibleSize.width/8*5,visibleSize.height/8, visibleSize.width/4, visibleSize.height*0.25, GroundZOrder);//创建矩形
	tb->sp->setColor(Color3B(125,7,216));
	barrierVector.push_back(tb);

	ids = new std::string("dm4");//矩形地面id
	tb=new RectBarrier(ids,this,Rect(129,685,243-129,802-685),visibleSize.width/8*7,visibleSize.height/8, visibleSize.width/4, visibleSize.height*0.25, GroundZOrder);//创建矩形
	tb->sp->setColor(Color3B(125,7,216));
	barrierVector.push_back(tb);

	ids = new std::string("dm5");//矩形地面id
	zh=new RectBarrier(ids,this,Rect(129,685,243-129,802-685),visibleSize.width/8*9,visibleSize.height/8, visibleSize.width/4, visibleSize.height*0.25, GroundZOrder);//创建矩形
	zh->sp->setColor(Color3B(125,7,216));
	barrierVector.push_back(zh);

	//取数据的代码
	int p1 = UserDefault::getInstance()->getIntegerForKey("1",779);
	int p2 = UserDefault::getInstance()->getIntegerForKey("2",110);
	int p3 = UserDefault::getInstance()->getIntegerForKey("3",30);
	int p4 = UserDefault::getInstance()->getIntegerForKey("4",30);

	ids = new std::string("JC");//跳跃方块id
	jc =new JumpCube(ids, this, Rect(p1,p2,p3,p4), JCX, JCY, LENGTHJC, 3);//创建跳跃方块   SPIC[1]
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerET, jc->sp);//注册监听器

	if(MusicManager::onSound == true)
	{
		MusicManager::playGameLayerMusic();//播放背景音乐
	}
	else
	{
		MusicManager::noPlaySound = true;
	}
}
