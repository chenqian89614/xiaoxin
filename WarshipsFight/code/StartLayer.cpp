#include "StartLayer.h"
#include "Weapon.h"
#include "Constant.h"
#include "ChooseLevelLayer.h"

using namespace cocos2d;

//实现StartLayer类中的init方法，初始化布景
bool StartLayer::init()
{
	//调用父类的初始化
    if ( !Layer::init() )
    {
        return false;
    }
    //获取可见区域尺寸
    Size visibleSize = Director::getInstance()->getVisibleSize();
    //获取可见区域原点坐标
    Point origin = Director::getInstance()->getVisibleOrigin();

    //3D飞机的创建
    palne3D = Sprite3D::create("zdj3D.obj");
    palne3D->setTexture("HE162R.jpg");
    palne3D->setPosition(Point(220,400));
    palne3D->setScale(0.015f);
    palne3D->setRotation3D(Vertex3F(30,45,0));
   	this->addChild(palne3D,10);

    plane3D = Sprite3D::create("plane.obj");
    plane3D->setTexture("F111tail.jpg");
    plane3D->setPosition(Point(800,400));
    plane3D->setScale(0.05f);
    plane3D->setRotation3D(Vertex3F(30,-45,0));
	this->addChild(plane3D,10);

	//背景精灵的创建
    Sprite* StartBgSp = Sprite::create("startBg.png");
    StartBgSp->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
    this->addChild(StartBgSp,0);

    //标题的创建
    Sprite* StartTitleSp = Sprite::create("main_title.png");
	StartTitleSp->setPosition(Point(visibleSize.width/2,visibleSize.height/3*2));
	this->addChild(StartTitleSp,2);

	//初始化菜单项
	initMenuItem();

	//旋转条的创建
	for(int i = 0 ;i<10;i++)
	{
		Sprite* xzTiaoSp = Sprite::create("xzTiao.png");
		xzTiaoSp->setAnchorPoint(Point(1,0.5));
		xzTiaoSp->setRotation(i*36);
		xzTiaoSp->setPosition(Point(visibleSize.width/2,visibleSize.height/3*2));
		this->addChild(xzTiaoSp,1);
		xzTiaoSp->runAction(RepeatForever::create(RotateBy::create(2,180)));
	}

	//获取是否是第一次进入游戏的标志，0代表是，1代表不是
	int k = UserDefault::getInstance()->getIntegerForKey(Constant::ISFIRSTENTER.c_str());
	if(k == 0)
	{
		firstEnter();
	}
	//获取背景声音设置的标志
	int bgsyint = UserDefault::getInstance()->getIntegerForKey(Constant::BGSY.c_str());
	if(bgsyint == 0)
	{
		ChooseLevelLayer::bacMusicFlag = true;
	}else
	{
		ChooseLevelLayer::bacMusicFlag = false;
	}
	//获取音效声音的设置的标志
	int yssyint = UserDefault::getInstance()->getIntegerForKey(Constant::YSSY.c_str());
	if(yssyint == 0)
	{
		ChooseLevelLayer::froMusicFlag = true;
	}else
	{
		ChooseLevelLayer::froMusicFlag = false;
	}
	//初始化声音
	initSound();
	//播放背景声音
	if(ChooseLevelLayer::bacMusicFlag == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()//播放背景音乐
					->playBackgroundMusic("sound_bgm_title.mp3",true);
	}
	//创建一个单点触摸监听
	EventListenerTouchOneByOne* listenerTouch = EventListenerTouchOneByOne::create();
	//设置下传触摸
	listenerTouch->setSwallowTouches(false);
	//开始触摸时回调onTouchBegan方法
	listenerTouch->onTouchBegan = CC_CALLBACK_2(StartLayer::onTouchBegan, this);
	//开始触摸时回调onTouchMoved方法
	listenerTouch->onTouchMoved = CC_CALLBACK_2(StartLayer::onTouchMoved, this);
	//触摸结束时回调onTouchEnded方法
	listenerTouch->onTouchEnded = CC_CALLBACK_2(StartLayer::onTouchEnded, this);
	//添加到监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTouch,this);

	//获取导演实例来设置回调
	auto director = Director::getInstance();
	Scheduler* sched = director->getScheduler();
	sched->scheduleSelector(SEL_SCHEDULE(&StartLayer::ball3DRotateUpdate),this,0.1,false);

	//火焰粒子系统
	ParticleSystemQuad* psq = ParticleSystemQuad::create("huoyan.plist");//从文件中加载粒子系统
	psq->setPositionType(ParticleSystem::PositionType::RELATIVE);
	psq->retain();								//保持引用
	psq->setBlendAdditive(true);				//设置混合方式为增加
	psq->setScale(0.4);
	psq->setPosition(Point(480,270));
	this->addChild(psq, 3);		//向布景层中的精灵添加粒子系统

    return true;
}
void StartLayer::initMenuItem()
{
	//获取可见区域尺寸
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//获取可见区域原点坐标
	Point origin = Director::getInstance()->getVisibleOrigin();

	//开始菜单项
	startItem = MenuItemImage::create(
			"startButton.png",
			"startButton.png",
			CC_CALLBACK_0(StartLayer::selBTCallback, this)
	);
	startItem->setPosition(Point(visibleSize.width/2,visibleSize.height/3));

	//关于菜单项
	aboutItem = MenuItemImage::create(
			"about.png",
			"aboutp.png",
			CC_CALLBACK_0(StartLayer::aboutCallback, this)
	);
	aboutItem->setPosition(Point(100,30));
	aboutItem->setScale(1.5);

	//帮助菜单项
	helpItem = MenuItemImage::create(
			"help.png",
			"helpp.png",
			CC_CALLBACK_0(StartLayer::helpCallback, this)
	);
	helpItem->setPosition(Point(290,30));
	helpItem->setScale(1.5);

	//帮助菜单项
	MenuItemImage* closseItem = MenuItemImage::create(
			"closea.png",
			"closeap.png",
			CC_CALLBACK_0(StartLayer::gameCloseCallback, this)
	);
	closseItem->setPosition(Point(930,30));
	closseItem->setScale(1.5);

	//创建一个菜单对象
	Menu* menu = Menu::create(startItem,aboutItem,helpItem,closseItem,NULL);
	//设置其位置
	menu->setPosition(Point::ZERO);
	//将其添加到布景中
	this->addChild(menu, 2);
}
void StartLayer::gameCloseCallback()
{
	Director::getInstance()->end();
}
//关于菜单项回调方法
void StartLayer::aboutCallback()
{
	if(ChooseLevelLayer::froMusicFlag == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()
							->playEffect("sound_sfx_click.mp3");
	}
	//设置其他菜单项不可用
	aboutItem->setEnabled(false);
	helpItem->setEnabled(false);
	startItem->setEnabled(false);
	if(bselItem != NULL)
	{
		bselItem->setEnabled(false);
	}
	//创建标题
	aboutTTSp = Sprite::create("taskTitle.png");
	aboutTTSp->setPosition(Point(260,500));
	this->addChild(aboutTTSp,14);

	//使有弹出的效果
	aboutTTSp->runAction(
			Sequence::create(
				ScaleTo::create(0.2,1.1),
				ScaleTo::create(0.1,1),
				NULL
			)
	);
	//关于主背景
	Sprite* aboutBgSp = Sprite::create("aboutBg.png");
	aboutBgSp->setAnchorPoint(Point(0,1));
	aboutBgSp->setPosition(Point(0,0));
	aboutTTSp->addChild(aboutBgSp,10);

	//3D球的创建
	earth3D = Sprite3D::create("earth.obj");
	earth3D->setScale(5.0f);
	earth3D->setTexture("worldmap.png");
	earth3D->setPosition(Point(325,200));
	aboutBgSp->addChild(earth3D,3);
	selAbout = true;

	//关闭菜单项的创建
	MenuItemImage* closeItem = MenuItemImage::create(
			"close.png",
			"closep.png",
			CC_CALLBACK_0(StartLayer::closeMenuCallback, this)
	);
	Size size = aboutBgSp->getContentSize();
	closeItem->setPosition(Point(size.width-30,size.height-30));

	//创建一个菜单对象
	Menu* menu = Menu::create(closeItem,NULL);
	//设置其位置
	menu->setPosition(Point::ZERO);
	//将其添加到布景中
	aboutBgSp->addChild(menu, 3);
}
//帮助菜单项回调方法
void StartLayer::helpCallback()
{
	if(ChooseLevelLayer::froMusicFlag == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()
							->playEffect("sound_sfx_click.mp3");
	}
	//设置其他菜单项不可用
	aboutItem->setEnabled(false);
	helpItem->setEnabled(false);
	startItem->setEnabled(false);
	if(bselItem != NULL)
	{
		bselItem->setEnabled(false);
	}
	this->removeChildByTag(14);
	//创建标题
	aboutTTSp = Sprite::create("helpTT.png");
	aboutTTSp->setPosition(Point(260,500));
	this->addChild(aboutTTSp,10);

	//使有弹出的效果的动作
	aboutTTSp->runAction(
			Sequence::create(
				ScaleTo::create(0.2,1.1),
				ScaleTo::create(0.1,1),
				NULL
			)
	);

	//创建帮助主背景
	Sprite* helpBgSp = Sprite::create("helpBg.png");
	helpBgSp->setAnchorPoint(Point(0,1));
	helpBgSp->setPosition(Point(-3,0));
	aboutTTSp->addChild(helpBgSp,10);

	//创建3D模型
	helpCube = Sprite3D::create("help.obj");
	helpCube->setTexture("Texture.png");
	helpCube->setPosition(Point(400,200));
	helpCube->setScale(5.5);
	helpBgSp->addChild(helpCube,10);

	//创建关闭菜单项
	closeItem = MenuItemImage::create(
			"close.png",
			"closep.png",
			CC_CALLBACK_0(StartLayer::closeMenuCallback, this)
	);
	Size size = helpBgSp->getContentSize();
	closeItem->setPosition(Point(size.width-30,size.height-30));

	//创建一个菜单对象
	Menu* menu = Menu::create(closeItem,NULL);
	//设置其位置
	menu->setPosition(Point::ZERO);
	//将其添加到布景中
	helpBgSp->addChild(menu, 3);

	//帮助黑白点显示的索引
	helpIndex = 0;

	//创建黑白点显示当前图片浏览的位置
	for(int i=0;i<6;i++)
	{
		if(i == 0)
		{
			bwSp[i] = Sprite::create("blank.png");
		}else
		{
			bwSp[i] = Sprite::create("white.png");
		}
		bwSp[i]->setPosition(Point(50,350-i*50));
		helpBgSp->addChild(bwSp[i],3);
	}
	helpFlag = true;
}
//重新设置黑白点位置的方法
void StartLayer::setBWPosition()
{
	int tempNUm = 1;
	for(int i=0;i<6;i++)
	{
		if(i == helpIndex)
		{
			bwSp[0]->setPosition(Point(50,350-i*50));
		}else
		{
			bwSp[tempNUm]->setPosition(Point(50,350-i*50));
			tempNUm ++;
		}

	}
}
//关闭菜单项回调方法
void StartLayer::closeMenuCallback()
{
	if(ChooseLevelLayer::froMusicFlag == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()
							->playEffect("sound_sfx_click.mp3");
	}
	//设置其他菜单项可用
	aboutItem->setEnabled(true);
	helpItem->setEnabled(true);
	startItem->setEnabled(true);
	if(bselItem != NULL)
	{
		bselItem->setEnabled(true);
	}
	//让弹窗变小消失
	aboutTTSp->runAction(
				Sequence::create(
						ScaleTo::create(0.2,0.1),
						RemoveSelf::create(true),
						NULL
				)
	);
	helpFlag = false;
	selAbout = false;
}
//第一次进入时回调的方法
void StartLayer::firstEnter()
{
	//进入时帮助的手指
	if(UserDefault::getInstance()->getIntegerForKey(Constant::ISFIRSTENTER.c_str()) == 0)
	{
		Sprite* tsSp = Sprite::create("finger.png");
		tsSp->setAnchorPoint(Point(1,0));
		tsSp->setPosition(Point(210,30));
		this->addChild(tsSp,5,10);
		tsSp->runAction(
				RepeatForever::create(
						Sequence::create(
							ScaleTo::create(0.5,1.2),
							ScaleTo::create(0.5,1),
						NULL
						)
				)
		);
	}

	//设置用户数据
	//第一次进入的标志
	UserDefault::getInstance()->setIntegerForKey(Constant::ISFIRSTENTER.c_str(),1);
	//关卡数
	UserDefault::getInstance()->setIntegerForKey(Constant::LEVELNUM.c_str(),1);
	//初始金钱
	UserDefault::getInstance()->setIntegerForKey(Constant::COUNTGOLD.c_str(),200);
	//杀敌数
	UserDefault::getInstance()->setIntegerForKey(Constant::SHADISHU.c_str(),0);

	//船只对应的火箭的等级
	UserDefault::getInstance()->setIntegerForKey(Constant::SHIPZERO.c_str(),1);
	UserDefault::getInstance()->setIntegerForKey(Constant::SHIPONE.c_str(),1);
	UserDefault::getInstance()->setIntegerForKey(Constant::SHIPTWO.c_str(),1);
	UserDefault::getInstance()->setIntegerForKey(Constant::SHIPTHREE.c_str(),1);
	UserDefault::getInstance()->setIntegerForKey(Constant::SHIPFOUR.c_str(),1);

	//胜利次数，失败次数，获得金钱总数
	UserDefault::getInstance()->setIntegerForKey(Constant::WINCOUNT.c_str(),0);
	UserDefault::getInstance()->setIntegerForKey(Constant::LOSECOUNT.c_str(),0);
	UserDefault::getInstance()->setIntegerForKey(Constant::GETGOLDCOUNT.c_str(),0);

	//关卡获得的荣誉
	UserDefault::getInstance()->setIntegerForKey(Constant::LEVEL1.c_str(),0);
	UserDefault::getInstance()->setIntegerForKey(Constant::LEVEL2.c_str(),0);
	UserDefault::getInstance()->setIntegerForKey(Constant::LEVEL3.c_str(),0);
	UserDefault::getInstance()->setIntegerForKey(Constant::LEVEL4.c_str(),0);

	//声音
	UserDefault::getInstance()->setIntegerForKey(Constant::BGSY.c_str(),0);
	UserDefault::getInstance()->setIntegerForKey(Constant::YSSY.c_str(),0);
}
//初始化声音的方法
void StartLayer::initSound()
{
	CocosDenshion::SimpleAudioEngine::getInstance()							//背景音效
					->preloadBackgroundMusic("sound_bgm_title.mp3");

	CocosDenshion::SimpleAudioEngine::getInstance()							//即使音效
					->preloadEffect("sound_sfx_click.mp3");
}
//设置菜单项回调的方法
void StartLayer::selBTCallback()
{
	if(ChooseLevelLayer::froMusicFlag == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()
							->playEffect("sound_sfx_click.mp3");
	}
	startItem->setVisible(false);
	bselItem = MenuItemImage::create(
			"startButtonSel.png",
			"startButtonSelp.png",
			CC_CALLBACK_0(StartLayer::startCallback, this)
	);
	bselItem->setPosition(Point(480,180));

	MenuItemImage* clearItem = MenuItemImage::create(
			"clear.png",
			"clearp.png",
			CC_CALLBACK_0(StartLayer::clearCallback, this)
	);
	clearItem->setPosition(Point(597-40,244-40));

	//创建一个菜单对象
	Menu* menu = Menu::create(bselItem,clearItem,NULL);
	//设置其位置
	menu->setPosition(Point::ZERO);
	//将其添加到布景中
	this->addChild(menu, 3);

	Sprite* sdsSp = Sprite::create("sds.png");
	sdsSp->setPosition(Point(50,80));
	bselItem->addChild(sdsSp,3);

	int sdsSt = UserDefault::getInstance()->getIntegerForKey(Constant::SHADISHU.c_str());

	sdsLabel = LabelAtlas::create(				//创建一个LabelAtlas对象
			StringUtils::format("%d",sdsSt),"labelatlas.png",15,19,'0');
	sdsLabel->setAnchorPoint(Point(0,0.5));
	sdsLabel->setPosition(Point(sdsSp->getPosition().x+30,sdsSp->getPosition().y));
	bselItem->addChild(sdsLabel,3);

	Sprite* djSp = Sprite::create("stara.png");
	djSp->setPosition(Point(50,50));
	bselItem->addChild(djSp,3);

	int moneySt = UserDefault::getInstance()->getIntegerForKey(Constant::COUNTGOLD.c_str());

	moneyLabel = LabelAtlas::create(				//创建一个LabelAtlas对象
			StringUtils::format("%d",moneySt),"labelatlas.png",15,19,'0');
	moneyLabel->setAnchorPoint(Point(0,0.5));
	moneyLabel->setPosition(Point(djSp->getPosition().x+30,djSp->getPosition().y));
	bselItem->addChild(moneyLabel,3);
}
void StartLayer::clearCallback()
{
	if(ChooseLevelLayer::froMusicFlag == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()
							->playEffect("sound_sfx_click.mp3");
	}
	aboutItem->setEnabled(false);
	helpItem->setEnabled(false);
	czcdSp = Sprite::create("czcdTT.png");
	czcdSp->setPosition(Point(480,400));
	this->addChild(czcdSp,3);

	Sprite* bbSp = Sprite::create("bb.png");
	bbSp->setAnchorPoint(Point(0,1));
	bbSp->setPosition(Point(0,0));
	czcdSp->addChild(bbSp,3);

	MenuItemImage* sureItem = MenuItemImage::create(
			"sure.png",
			"surep.png",
			CC_CALLBACK_0(StartLayer::sureCallback, this)
	);
	sureItem->setPosition(Point(80,100));

	MenuItemImage* cancleItem = MenuItemImage::create(
			"cancle.png",
			"canclep.png",
			CC_CALLBACK_0(StartLayer::cancleCallback, this)
	);
	cancleItem->setPosition(Point(230,100));

	//创建一个菜单对象
	Menu* menu = Menu::create(sureItem,cancleItem,NULL);
	//设置其位置
	menu->setPosition(Point::ZERO);
	//将其添加到布景中
	bbSp->addChild(menu, 3);
}
void StartLayer::sureCallback()
{
	if(ChooseLevelLayer::froMusicFlag == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()
							->playEffect("sound_sfx_click.mp3");
	}
	firstEnter();
	moneyLabel->setString("200");
	sdsLabel->setString("0");
	this->removeChild(czcdSp,true);
	aboutItem->setEnabled(true);
	helpItem->setEnabled(true);
	startItem->setEnabled(true);
}
void StartLayer::cancleCallback()
{
	if(ChooseLevelLayer::froMusicFlag == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()
							->playEffect("sound_sfx_click.mp3");
	}
	this->removeChild(czcdSp,true);
	aboutItem->setEnabled(true);
	helpItem->setEnabled(true);
}
void StartLayer::startCallback()
{
	if(ChooseLevelLayer::froMusicFlag == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()
							->playEffect("sound_sfx_click.mp3");
	}
	wfsm->goChooseLevelScene();
}
//触摸监听的方法
bool StartLayer::onTouchBegan(Touch* touch, Event* event)
{
	if(helpFlag == false)
	{
		return false;
	}
	currPoint = touch->getLocation();
	if(touch->getLocation().x>250&&touch->getLocation().x<840
						&&touch->getLocation().y>80&&touch->getLocation().y<470)
	{
		return true;
	}else
	{
		return false;
	}
}
void StartLayer::onTouchMoved(Touch* touch, Event* event)
{
	if(showPNG == true)
	{
		return ;
	}
	deltaAngleY = (int)(touch->getLocation().y-currPoint.y)%360;

	helpCube->setRotation3D(Vertex3F(helpCubeLastAngle-deltaAngleY,0,0));
}
void StartLayer::onTouchEnded(Touch* touch, Event* event)
{
	helpCubeLastAngle = (int)helpCube->getRotation3D().x % 330;
	if(helpCubeLastAngle < 0&&helpCubeLastAngle>-30)
	{
		helpCubeLastAngle = fabs(helpCubeLastAngle);
	}else if(helpCubeLastAngle < 0)
	{
		helpCubeLastAngle = helpCubeLastAngle + 330;
	}
	helpIndex = (helpCubeLastAngle+29) / 60;
	helpCubeLastAngle = helpIndex * 60;
	helpCube->setRotation3D(Vertex3F(helpCubeLastAngle,0,0));

	if(helpIndex < 0)
	{
		helpIndex = 6 + helpIndex;
	}
	setBWPosition();
	if(fabs(deltaAngleY)<5&&showPNG == false)
	{
		spHelp = Sprite::create(StringUtils::format("help%d.png",helpIndex));
		spHelp->setPosition(Point(535,270));
		this->addChild(spHelp,10);
		spHelp->runAction(
				Sequence::create(
						Spawn::create(
								ScaleTo::create(0.2,1/0.6),
								MoveTo::create(0.2,Point(480,270))
						,NULL
						),
				ScaleTo::create(0.1,1/0.625)
				,NULL));
		showPNG = true;
		closeItem->setEnabled(false);
	}else if(fabs(deltaAngleY)<5&&showPNG == true)
	{
		spHelp->runAction(
						Sequence::create(
								ScaleTo::create(0.1,1/0.600),
								Spawn::create(
										ScaleTo::create(0.2,1),
										MoveTo::create(0.2,Point(535,270))
								,NULL
								),
						RemoveSelf::create(true)
						,NULL));
		showPNG = false;
		closeItem->setEnabled(true);
	}
}
void StartLayer::ball3DRotateUpdate()
{
	if(upFlag == false)
	{
		deltaDis =deltaDis -2;
		deltaAngle = deltaAngle+0.5;
	}else if(upFlag == true)
	{
		deltaDis =deltaDis +2;
		deltaAngle = deltaAngle-0.5;
	}
	if(deltaDis>=24||deltaDis<=1)
	{
		upFlag = !upFlag;
	}
	plane3D->setPosition(Point(800,400+deltaDis%25));
	plane3D->setRotation3D(Vertex3F(30 + deltaAngle,-45,0));
	palne3D->setPosition(Point(220,400+deltaDis%25));
	palne3D->setRotation3D(Vertex3F(30+ deltaAngle,45 ,0));
	if(selAbout == true)
	{
		int ry = (int)(earth3D->getRotation3D().y-1)%360;
		earth3D->setRotation3D(Vertex3F(0,ry,0 ));
	}
}
