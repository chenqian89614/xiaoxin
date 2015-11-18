#include "ChooseCarLayer.h"
#include "MyCar.h"
#include "cocos2d.h"
#include "AppMacros.h"
#include "GameLayer.h"
#include "StartLayer.h"
#include "Constant.h"

using namespace cocos2d;

//记录当前选择的车的型号
int ChooseCarLayer::currCarNum = 0;

bool ChooseCarLayer::init()
{
	//调用父类的初始化
	if (!Layer::init())
	{
	    return false;
	}
	ChooseCarLayer::currCarNum = 0;
    //获取可见区域尺寸
    Size visibleSize = Director::getInstance()->getVisibleSize();
    //获取可见区域原点坐标
    Point origin = Director::getInstance()->getVisibleOrigin();

    bgSpriteO = Sprite::create("scene1.jpg");
    bgSpriteO->setPosition(270,480);
    this->addChild(bgSpriteO,0);

    bgSpriteT = Sprite::create("scene1.jpg");
    bgSpriteT->setPosition(270,-480);
    this->addChild(bgSpriteT,0);

    Sprite* garageSprite = Sprite::create("GarageIcon.png");
    garageSprite->setPosition(270,780);
    this->addChild(garageSprite,1);

    Sprite* garage = Sprite::create("Garage.png");
    garage->setPosition(270,800);
    this->addChild(garage,1);

    for(int i=0;i<8;i++)
    {
    	garageBG[i] = Sprite::create("GarageFrame.png");
		garageBG[i]->setPosition(Point(270+i*480,480));
		this->addChild(garageBG[i],1);

		TBGPoint[i] = garageBG[i]->getPosition();

		myCar[i] = new MyCar(i+1,165.5,280);
		carSprite[i] = myCar[i]->refresh();
		garageBG[i]->addChild(carSprite[i],1);

		int buyOrNot = UserDefault::getInstance()->getIntegerForKey(Constant::uesrDefunct[i].c_str());
		if(buyOrNot == 0)
		{
			lockeSprite[i] = Sprite::create("Locked.png");
			lockeSprite[i]->setPosition(Point(165.5,280));
			garageBG[i]->addChild(lockeSprite[i],2);
		}

		int starCount = 0;
	//	for(int j=0;j<=i;j++)
	//	{
	//		Sprite* star = Sprite::create("garage/star.png");
	//		int p = 0;
	//		if(j%2==0)
	//		{
	//			p =-(starCount*30);
	//		}else if(j%2==1)
	//		{
	//			starCount++;
	//			p =(starCount*30);
	//		}
	//		star->setPosition(165.5+p,220);
	//		garageBG[i]->addChild(star,1);
	//	}
		for(int j=0;j<i+1;j++)
		{
			Sprite* dbSprite = Sprite::create("DB.png");
			dbSprite->setPosition(Point(130+j*25,100));
			garageBG[i]->addChild(dbSprite,1);
		}


		LabelAtlas* carPriceLabel = LabelAtlas::create(						//创建一个LabelAtlas对象
				StringUtils::format("%d",(i+1)*500),"upNum.png",20,23,'0');
		carPriceLabel->setAnchorPoint(Point(0,0.5));			//设置LabelAtlas对象锚点
		carPriceLabel->setPosition(								//设置LabelAtlas对象位置
							Point(150,180));
		garageBG[i]->addChild(carPriceLabel,1);			//将LabelAtlas对象添加到布景中

		int userGoldCount = UserDefault::getInstance()->getIntegerForKey(Constant::userGold.c_str());

		userGoldLabel[i] = LabelAtlas::create(						//创建一个LabelAtlas对象
				StringUtils::format("%d",userGoldCount),"upNum.png",20,23,'0');
		userGoldLabel[i]->setAnchorPoint(Point(1,0.5));			//设置LabelAtlas对象锚点
		userGoldLabel[i]->setPosition(								//设置LabelAtlas对象位置
							Point(300,25));
		garageBG[i]->addChild(userGoldLabel[i],DJZORDER);			//将LabelAtlas对象添加到布景中
    }

    //创建下一个菜单项
	MenuItemImage* BTItem = MenuItemImage::create(
			   "Button.png",	//平时的图片
			   "ButtonPressed.png",	//选中时的图片
			   CC_CALLBACK_0(ChooseCarLayer::gameEnter, this) //点击时执行的回调方法
		);
	//设置下一个菜单项的位置
	BTItem->setPosition(Point(270,150));

	//创建下一个菜单项
	MenuItemImage* backMenu = MenuItemImage::create(
			   "goback.png",	//平时的图片
			   "gobackp.png",	//选中时的图片
			   CC_CALLBACK_0(ChooseCarLayer::backMenuCallback, this) //点击时执行的回调方法
		);
	//设置下一个菜单项的位置
	backMenu->setPosition(Point(40,920));

	//创建菜单对象
	auto menu = Menu::create(BTItem,backMenu,NULL);
	//设置菜单位置
	menu->setPosition(Point::ZERO);
	//将菜单添加到布景中
	this->addChild(menu, 1);

	refreshMenuSprite();

    //设置定时回调指定方法干活
	auto director = Director::getInstance();
	auto sched = director->getScheduler();
	//背景滚屏定时回调
	sched->scheduleSelector(SEL_SCHEDULE(&ChooseCarLayer::bgUpdate),this,0.005,false);

	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(ChooseCarLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(ChooseCarLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(ChooseCarLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,garageBG[0]);
	for(int i=1;i<8;i++)
	{
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(),garageBG[i]);
	}
    return true;
}
void ChooseCarLayer::backMenuCallback()
{
	if(StartLayer::gameMode == 0)
	{
		crsm->goChooseLevelLayer();
	}else if(StartLayer::gameMode == 5)
	{
		crsm->goGameOverLayer();
	}else
	{
		crsm->goStartLyaer();
	}
}
void ChooseCarLayer::refreshMenuSprite()
{
	this->removeChildByTag(9);
	int buyOrNot = UserDefault::getInstance()->getIntegerForKey(Constant::uesrDefunct[tempCarNum].c_str());
	if(buyOrNot == 1 && (StartLayer::gameMode == 0||StartLayer::gameMode == 1))
	{
		Sprite* enter = Sprite::create("Enter.png");
		enter->setPosition(270,150);
		this->addChild(enter,2,9);
	}else if(buyOrNot == 0)
	{
		Sprite* enter = Sprite::create("Buy.png");
		enter->setPosition(270,150);
		this->addChild(enter,2,9);
	}else if(StartLayer::gameMode == 2 || StartLayer::gameMode == 5)
	{
		Sprite* enter = Sprite::create("enterMain.png");
		enter->setPosition(270,150);
		this->addChild(enter,2,9);
	}
}
bool ChooseCarLayer::onTouchBegan(Touch* touch, Event* event)
{
	auto target = static_cast<Sprite*>(	//获取当前触摸对象，并转化为精灵类型
						event->getCurrentTarget());
	currPoint = touch->getLocation();
	Point location = target->convertToNodeSpace(touch->getLocation());//获取当前坐标
	auto size = target->getContentSize();			//获取精灵的大小
	auto rect = Rect(0, 0, size.width, size.height);//创建一个矩形对象，其大小与精灵相同
	if( rect.containsPoint(location)){	//判断触摸点是否在目标的范围内
		return true;
	}else{
		return false;
	}
}
void ChooseCarLayer::onTouchMoved(Touch* touch, Event* event)
{
	for(int i=0;i<8;i++)
	{
		garageBG[i]->setPosition(
				TBGPoint[i].x+(touch->getLocation().x-currPoint.x),
				TBGPoint[i].y
		);
	}
}
void ChooseCarLayer::onTouchEnded(Touch* touch, Event* event)
{
	auto target = static_cast<Sprite*>(				//获取的当前触摸的对象，并转化为精灵类型
								event->getCurrentTarget());
	Point location = target->convertToNodeSpace(touch->getLocation());//获取当前坐标
    for(int i=0;i<8;i++)
	{
		TBGPoint[i] = garageBG[i]->getPosition();
	}
    float jlMin = MAX_INT;
    int shortNum = 0;
    for(int i=0;i<8;i++)
    {
    	if(fabs(270-TBGPoint[i].x)<jlMin)
    	{
    		jlMin = fabs(TBGPoint[i].x-270);
    		shortNum = i;
    		tempCarNum = i;
    	}
    }
    for(int i=shortNum;i<8;i++)
    {
    	garageBG[i]->setPosition(
    			270+(i-shortNum)*480,
    			garageBG[i]->getPosition().y
    	);
    }
    for(int i=shortNum;i>=0;i--)
    {
    	garageBG[i]->setPosition(
    	    			270-(shortNum-i)*480,
    	    			garageBG[i]->getPosition().y
    	    	);
    }
    for(int i=0;i<8;i++)
	{
		TBGPoint[i] = garageBG[i]->getPosition();
	}
    int buyOrNot = UserDefault::getInstance()->getIntegerForKey(Constant::uesrDefunct[shortNum].c_str());
    if(buyOrNot == 1)
    {
    	ChooseCarLayer::currCarNum = shortNum;
    }

    refreshMenuSprite();
}
void ChooseCarLayer::gameEnter()
{
	do{
		int buyOrNot = UserDefault::getInstance()->getIntegerForKey(Constant::uesrDefunct[tempCarNum].c_str());
		int userGoldCount = UserDefault::getInstance()->getIntegerForKey(Constant::userGold.c_str());
		int carPrice = (ChooseCarLayer::currCarNum+1)*500;
		if(buyOrNot == 0)
		{
			if(userGoldCount >= carPrice)
			{
				garageBG[ChooseCarLayer::currCarNum]->removeChild(lockeSprite[tempCarNum],true);
				int restGold = userGoldCount - carPrice;
				//重置玩家的金钱数
				UserDefault::getInstance()->setIntegerForKey(
								Constant::userGold.c_str(),restGold);
				for(int i = 0;i <8 ;i++)
				{
					userGoldLabel[i]->setString(StringUtils::format("%d",restGold));
				}
				//标志该车已被买
				UserDefault::getInstance()->setIntegerForKey(
						Constant::uesrDefunct[tempCarNum].c_str(),1);
				ChooseCarLayer::currCarNum = tempCarNum;
				refreshMenuSprite();
			}else
			{
				break;
			}
		}else if((StartLayer::gameMode == 1||StartLayer::gameMode == 0)&&buyOrNot == 1)
		{//=========此处应该进入游戏场景
			crsm->goGameLayer();
		}else if(StartLayer::gameMode == 2)
		{
			crsm->goStartLyaer();
		}else if(StartLayer::gameMode == 5)
		{
			crsm->goGameOverLayer();
		}
	}while(0);

}
void ChooseCarLayer::bgUpdate()
{
	if(bgSpriteO->getPosition().y==1440)
	{
		bgSpriteO->setPosition(Point(270,-480));
	}else
	{
		bgSpriteO->setPosition(Point(270,bgSpriteO->getPosition().y+1));
	}

	if(bgSpriteT->getPosition().y==1440)
	{
		bgSpriteT->setPosition(Point(270,-480));
	}else
	{
		bgSpriteT->setPosition(Point(270,bgSpriteT->getPosition().y+1));
	}
}
