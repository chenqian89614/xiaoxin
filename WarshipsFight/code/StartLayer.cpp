#include "StartLayer.h"
#include "Weapon.h"
#include "Constant.h"
#include "ChooseLevelLayer.h"

using namespace cocos2d;

//ʵ��StartLayer���е�init��������ʼ������
bool StartLayer::init()
{
	//���ø���ĳ�ʼ��
    if ( !Layer::init() )
    {
        return false;
    }
    //��ȡ�ɼ�����ߴ�
    Size visibleSize = Director::getInstance()->getVisibleSize();
    //��ȡ�ɼ�����ԭ������
    Point origin = Director::getInstance()->getVisibleOrigin();

    //3D�ɻ��Ĵ���
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

	//��������Ĵ���
    Sprite* StartBgSp = Sprite::create("startBg.png");
    StartBgSp->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
    this->addChild(StartBgSp,0);

    //����Ĵ���
    Sprite* StartTitleSp = Sprite::create("main_title.png");
	StartTitleSp->setPosition(Point(visibleSize.width/2,visibleSize.height/3*2));
	this->addChild(StartTitleSp,2);

	//��ʼ���˵���
	initMenuItem();

	//��ת���Ĵ���
	for(int i = 0 ;i<10;i++)
	{
		Sprite* xzTiaoSp = Sprite::create("xzTiao.png");
		xzTiaoSp->setAnchorPoint(Point(1,0.5));
		xzTiaoSp->setRotation(i*36);
		xzTiaoSp->setPosition(Point(visibleSize.width/2,visibleSize.height/3*2));
		this->addChild(xzTiaoSp,1);
		xzTiaoSp->runAction(RepeatForever::create(RotateBy::create(2,180)));
	}

	//��ȡ�Ƿ��ǵ�һ�ν�����Ϸ�ı�־��0�����ǣ�1������
	int k = UserDefault::getInstance()->getIntegerForKey(Constant::ISFIRSTENTER.c_str());
	if(k == 0)
	{
		firstEnter();
	}
	//��ȡ�����������õı�־
	int bgsyint = UserDefault::getInstance()->getIntegerForKey(Constant::BGSY.c_str());
	if(bgsyint == 0)
	{
		ChooseLevelLayer::bacMusicFlag = true;
	}else
	{
		ChooseLevelLayer::bacMusicFlag = false;
	}
	//��ȡ��Ч���������õı�־
	int yssyint = UserDefault::getInstance()->getIntegerForKey(Constant::YSSY.c_str());
	if(yssyint == 0)
	{
		ChooseLevelLayer::froMusicFlag = true;
	}else
	{
		ChooseLevelLayer::froMusicFlag = false;
	}
	//��ʼ������
	initSound();
	//���ű�������
	if(ChooseLevelLayer::bacMusicFlag == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()//���ű�������
					->playBackgroundMusic("sound_bgm_title.mp3",true);
	}
	//����һ�����㴥������
	EventListenerTouchOneByOne* listenerTouch = EventListenerTouchOneByOne::create();
	//�����´�����
	listenerTouch->setSwallowTouches(false);
	//��ʼ����ʱ�ص�onTouchBegan����
	listenerTouch->onTouchBegan = CC_CALLBACK_2(StartLayer::onTouchBegan, this);
	//��ʼ����ʱ�ص�onTouchMoved����
	listenerTouch->onTouchMoved = CC_CALLBACK_2(StartLayer::onTouchMoved, this);
	//��������ʱ�ص�onTouchEnded����
	listenerTouch->onTouchEnded = CC_CALLBACK_2(StartLayer::onTouchEnded, this);
	//��ӵ�������
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTouch,this);

	//��ȡ����ʵ�������ûص�
	auto director = Director::getInstance();
	Scheduler* sched = director->getScheduler();
	sched->scheduleSelector(SEL_SCHEDULE(&StartLayer::ball3DRotateUpdate),this,0.1,false);

	//��������ϵͳ
	ParticleSystemQuad* psq = ParticleSystemQuad::create("huoyan.plist");//���ļ��м�������ϵͳ
	psq->setPositionType(ParticleSystem::PositionType::RELATIVE);
	psq->retain();								//��������
	psq->setBlendAdditive(true);				//���û�Ϸ�ʽΪ����
	psq->setScale(0.4);
	psq->setPosition(Point(480,270));
	this->addChild(psq, 3);		//�򲼾����еľ����������ϵͳ

    return true;
}
void StartLayer::initMenuItem()
{
	//��ȡ�ɼ�����ߴ�
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//��ȡ�ɼ�����ԭ������
	Point origin = Director::getInstance()->getVisibleOrigin();

	//��ʼ�˵���
	startItem = MenuItemImage::create(
			"startButton.png",
			"startButton.png",
			CC_CALLBACK_0(StartLayer::selBTCallback, this)
	);
	startItem->setPosition(Point(visibleSize.width/2,visibleSize.height/3));

	//���ڲ˵���
	aboutItem = MenuItemImage::create(
			"about.png",
			"aboutp.png",
			CC_CALLBACK_0(StartLayer::aboutCallback, this)
	);
	aboutItem->setPosition(Point(100,30));
	aboutItem->setScale(1.5);

	//�����˵���
	helpItem = MenuItemImage::create(
			"help.png",
			"helpp.png",
			CC_CALLBACK_0(StartLayer::helpCallback, this)
	);
	helpItem->setPosition(Point(290,30));
	helpItem->setScale(1.5);

	//�����˵���
	MenuItemImage* closseItem = MenuItemImage::create(
			"closea.png",
			"closeap.png",
			CC_CALLBACK_0(StartLayer::gameCloseCallback, this)
	);
	closseItem->setPosition(Point(930,30));
	closseItem->setScale(1.5);

	//����һ���˵�����
	Menu* menu = Menu::create(startItem,aboutItem,helpItem,closseItem,NULL);
	//������λ��
	menu->setPosition(Point::ZERO);
	//������ӵ�������
	this->addChild(menu, 2);
}
void StartLayer::gameCloseCallback()
{
	Director::getInstance()->end();
}
//���ڲ˵���ص�����
void StartLayer::aboutCallback()
{
	if(ChooseLevelLayer::froMusicFlag == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()
							->playEffect("sound_sfx_click.mp3");
	}
	//���������˵������
	aboutItem->setEnabled(false);
	helpItem->setEnabled(false);
	startItem->setEnabled(false);
	if(bselItem != NULL)
	{
		bselItem->setEnabled(false);
	}
	//��������
	aboutTTSp = Sprite::create("taskTitle.png");
	aboutTTSp->setPosition(Point(260,500));
	this->addChild(aboutTTSp,14);

	//ʹ�е�����Ч��
	aboutTTSp->runAction(
			Sequence::create(
				ScaleTo::create(0.2,1.1),
				ScaleTo::create(0.1,1),
				NULL
			)
	);
	//����������
	Sprite* aboutBgSp = Sprite::create("aboutBg.png");
	aboutBgSp->setAnchorPoint(Point(0,1));
	aboutBgSp->setPosition(Point(0,0));
	aboutTTSp->addChild(aboutBgSp,10);

	//3D��Ĵ���
	earth3D = Sprite3D::create("earth.obj");
	earth3D->setScale(5.0f);
	earth3D->setTexture("worldmap.png");
	earth3D->setPosition(Point(325,200));
	aboutBgSp->addChild(earth3D,3);
	selAbout = true;

	//�رղ˵���Ĵ���
	MenuItemImage* closeItem = MenuItemImage::create(
			"close.png",
			"closep.png",
			CC_CALLBACK_0(StartLayer::closeMenuCallback, this)
	);
	Size size = aboutBgSp->getContentSize();
	closeItem->setPosition(Point(size.width-30,size.height-30));

	//����һ���˵�����
	Menu* menu = Menu::create(closeItem,NULL);
	//������λ��
	menu->setPosition(Point::ZERO);
	//������ӵ�������
	aboutBgSp->addChild(menu, 3);
}
//�����˵���ص�����
void StartLayer::helpCallback()
{
	if(ChooseLevelLayer::froMusicFlag == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()
							->playEffect("sound_sfx_click.mp3");
	}
	//���������˵������
	aboutItem->setEnabled(false);
	helpItem->setEnabled(false);
	startItem->setEnabled(false);
	if(bselItem != NULL)
	{
		bselItem->setEnabled(false);
	}
	this->removeChildByTag(14);
	//��������
	aboutTTSp = Sprite::create("helpTT.png");
	aboutTTSp->setPosition(Point(260,500));
	this->addChild(aboutTTSp,10);

	//ʹ�е�����Ч���Ķ���
	aboutTTSp->runAction(
			Sequence::create(
				ScaleTo::create(0.2,1.1),
				ScaleTo::create(0.1,1),
				NULL
			)
	);

	//��������������
	Sprite* helpBgSp = Sprite::create("helpBg.png");
	helpBgSp->setAnchorPoint(Point(0,1));
	helpBgSp->setPosition(Point(-3,0));
	aboutTTSp->addChild(helpBgSp,10);

	//����3Dģ��
	helpCube = Sprite3D::create("help.obj");
	helpCube->setTexture("Texture.png");
	helpCube->setPosition(Point(400,200));
	helpCube->setScale(5.5);
	helpBgSp->addChild(helpCube,10);

	//�����رղ˵���
	closeItem = MenuItemImage::create(
			"close.png",
			"closep.png",
			CC_CALLBACK_0(StartLayer::closeMenuCallback, this)
	);
	Size size = helpBgSp->getContentSize();
	closeItem->setPosition(Point(size.width-30,size.height-30));

	//����һ���˵�����
	Menu* menu = Menu::create(closeItem,NULL);
	//������λ��
	menu->setPosition(Point::ZERO);
	//������ӵ�������
	helpBgSp->addChild(menu, 3);

	//�����ڰ׵���ʾ������
	helpIndex = 0;

	//�����ڰ׵���ʾ��ǰͼƬ�����λ��
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
//�������úڰ׵�λ�õķ���
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
//�رղ˵���ص�����
void StartLayer::closeMenuCallback()
{
	if(ChooseLevelLayer::froMusicFlag == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()
							->playEffect("sound_sfx_click.mp3");
	}
	//���������˵������
	aboutItem->setEnabled(true);
	helpItem->setEnabled(true);
	startItem->setEnabled(true);
	if(bselItem != NULL)
	{
		bselItem->setEnabled(true);
	}
	//�õ�����С��ʧ
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
//��һ�ν���ʱ�ص��ķ���
void StartLayer::firstEnter()
{
	//����ʱ��������ָ
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

	//�����û�����
	//��һ�ν���ı�־
	UserDefault::getInstance()->setIntegerForKey(Constant::ISFIRSTENTER.c_str(),1);
	//�ؿ���
	UserDefault::getInstance()->setIntegerForKey(Constant::LEVELNUM.c_str(),1);
	//��ʼ��Ǯ
	UserDefault::getInstance()->setIntegerForKey(Constant::COUNTGOLD.c_str(),200);
	//ɱ����
	UserDefault::getInstance()->setIntegerForKey(Constant::SHADISHU.c_str(),0);

	//��ֻ��Ӧ�Ļ���ĵȼ�
	UserDefault::getInstance()->setIntegerForKey(Constant::SHIPZERO.c_str(),1);
	UserDefault::getInstance()->setIntegerForKey(Constant::SHIPONE.c_str(),1);
	UserDefault::getInstance()->setIntegerForKey(Constant::SHIPTWO.c_str(),1);
	UserDefault::getInstance()->setIntegerForKey(Constant::SHIPTHREE.c_str(),1);
	UserDefault::getInstance()->setIntegerForKey(Constant::SHIPFOUR.c_str(),1);

	//ʤ��������ʧ�ܴ�������ý�Ǯ����
	UserDefault::getInstance()->setIntegerForKey(Constant::WINCOUNT.c_str(),0);
	UserDefault::getInstance()->setIntegerForKey(Constant::LOSECOUNT.c_str(),0);
	UserDefault::getInstance()->setIntegerForKey(Constant::GETGOLDCOUNT.c_str(),0);

	//�ؿ���õ�����
	UserDefault::getInstance()->setIntegerForKey(Constant::LEVEL1.c_str(),0);
	UserDefault::getInstance()->setIntegerForKey(Constant::LEVEL2.c_str(),0);
	UserDefault::getInstance()->setIntegerForKey(Constant::LEVEL3.c_str(),0);
	UserDefault::getInstance()->setIntegerForKey(Constant::LEVEL4.c_str(),0);

	//����
	UserDefault::getInstance()->setIntegerForKey(Constant::BGSY.c_str(),0);
	UserDefault::getInstance()->setIntegerForKey(Constant::YSSY.c_str(),0);
}
//��ʼ�������ķ���
void StartLayer::initSound()
{
	CocosDenshion::SimpleAudioEngine::getInstance()							//������Ч
					->preloadBackgroundMusic("sound_bgm_title.mp3");

	CocosDenshion::SimpleAudioEngine::getInstance()							//��ʹ��Ч
					->preloadEffect("sound_sfx_click.mp3");
}
//���ò˵���ص��ķ���
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

	//����һ���˵�����
	Menu* menu = Menu::create(bselItem,clearItem,NULL);
	//������λ��
	menu->setPosition(Point::ZERO);
	//������ӵ�������
	this->addChild(menu, 3);

	Sprite* sdsSp = Sprite::create("sds.png");
	sdsSp->setPosition(Point(50,80));
	bselItem->addChild(sdsSp,3);

	int sdsSt = UserDefault::getInstance()->getIntegerForKey(Constant::SHADISHU.c_str());

	sdsLabel = LabelAtlas::create(				//����һ��LabelAtlas����
			StringUtils::format("%d",sdsSt),"labelatlas.png",15,19,'0');
	sdsLabel->setAnchorPoint(Point(0,0.5));
	sdsLabel->setPosition(Point(sdsSp->getPosition().x+30,sdsSp->getPosition().y));
	bselItem->addChild(sdsLabel,3);

	Sprite* djSp = Sprite::create("stara.png");
	djSp->setPosition(Point(50,50));
	bselItem->addChild(djSp,3);

	int moneySt = UserDefault::getInstance()->getIntegerForKey(Constant::COUNTGOLD.c_str());

	moneyLabel = LabelAtlas::create(				//����һ��LabelAtlas����
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

	//����һ���˵�����
	Menu* menu = Menu::create(sureItem,cancleItem,NULL);
	//������λ��
	menu->setPosition(Point::ZERO);
	//������ӵ�������
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
//���������ķ���
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
