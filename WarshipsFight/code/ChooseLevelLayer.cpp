#include "ChooseLevelLayer.h"
#include "Constant.h"
using namespace cocos2d;
int ChooseLevelLayer::levelNum = 0;
int ChooseLevelLayer::enemyBaseLife = 0;
bool ChooseLevelLayer::bacMusicFlag = true;
bool ChooseLevelLayer::froMusicFlag = true;
bool ChooseLevelLayer::init()
{
	if ( !Layer::init())
	{
		return false;
	}

	worldMapSp = Sprite::create("worldmapc.png");
	worldMapSp->setAnchorPoint(Point(0,0));
	worldMapSp->setPosition(Point(0,0));
	this->addChild(worldMapSp,0);
	worldMapPoint = worldMapSp->getPosition();

	initBoomFrame();
	int levelNum = myGetIntegerForKey(Constant::LEVELNUM);
	levelCount = levelNum;
	std::string levelString = "xsjx.png";
	if(levelNum == 1)
	{
		levelString = "nextLevel.png";
	}
	levelSp[0]= Sprite::create(levelString);
	levelSp[0]->setAnchorPoint(Point(0,0));
	levelSp[0]->setPosition(Point(320,50));
	worldMapSp->addChild(levelSp[0],1);

	for(int i = 1;i<levelNum;i++)
	{
		//ָ����··��
		std::string linePath = StringUtils::format("line%d.png",i);
		//������·
		Sprite* lineSp = Sprite::create(linePath);
		//���һ����·����
		if(i == levelNum-1)
		{
			lineSp->setVisible(false);
		}
		//����ê��
		if(i == 1)
		{
			lineSp->setAnchorPoint(Point(1,0));
		}else if(i==2)
		{
			lineSp->setAnchorPoint(Point(0,1));
		}else
		{
			lineSp->setAnchorPoint(Point(0,0));
		}
		//��ȡ��һ���ؿ���ֻ�Ĵ�С
		Size size =levelSp[i-1]->getContentSize();
		//�����һ���ؿ���ֻ��λ��
		Point position = levelSp[i-1]->getPosition();
		if(i==1)
		{
			//�������������������·ͼƬ��λ��
			lineSp->setPosition(Point(position.x+size.width/2,position.y+size.height));
		}else if(i==2)
		{
			//�������������������·ͼƬ��λ��
			lineSp->setPosition(Point(position.x+size.width,position.y+size.height/2));
		}else
		{
			//�������������������·ͼƬ��λ��
			lineSp->setPosition(Point(position.x+size.width,position.y+size.height/2));
		}

		//��ӵ���ͼ��
		worldMapSp->addChild(lineSp,1);

		//���ùؿ���ֻ·��
		std::string levelString = "xsjx.png";
		if(i == levelNum-1)
		{
			//������һ��δ��ʼ�ؿ���ֻ·��
			levelString = "nextLevel.png";
			levelSp[i] = Sprite::create(levelString);
			levelSp[i]->setAnchorPoint(Point(0,0));
			Size sizeT =lineSp->getContentSize();
			Point positionT = lineSp->getPosition();
			levelSp[i]->setPosition(Point(positionT.x,positionT.y));
			if(i == 1)
			{
				levelSp[i]->runAction(
						Sequence::create(
								MoveTo::create(2,Point(positionT.x-sizeT.width,positionT.y+sizeT.height)),
								CallFunc::create(CC_CALLBACK_0(ChooseLevelLayer::levelCallback,this)),
								NULL
						));
			}else if(i == 2)
			{
				ccBezierConfig bezier;
				bezier.controlPoint_1 = Point(194, 393);					//���ñ��������ߵĵ�һ�����Ƶ�
				bezier.controlPoint_2 = Point(596, 50);				//���ñ��������ߵĵڶ������Ƶ�
				bezier.endPosition = Point(695,401);					//���ñ��������ߵ����һ�����Ƶ�

				levelSp[i]->runAction(
						Sequence::create(
								BezierTo::create(3, bezier),	//����һ���������������󣬲�����ִ��
								CallFunc::create(CC_CALLBACK_0(ChooseLevelLayer::levelCallback,this)),
								NULL
						));
			}else
			{
				levelSp[i]->runAction(
							Sequence::create(
									MoveTo::create(2,Point(positionT.x+sizeT.width,positionT.y+sizeT.height)),
									CallFunc::create(CC_CALLBACK_0(ChooseLevelLayer::levelCallback,this)),
									NULL
							));
			}
		}else
		{
			//��ֻ��ֻ
			levelSp[i] = Sprite::create(levelString);
			//������ê��
			levelSp[i]->setAnchorPoint(Point(0,0));
			//��ȡ��һ��·�߾���Ĵ�С
			Size sizeT =lineSp->getContentSize();
			//��ȡ��һ����·�����λ��
			Point positionT = lineSp->getPosition();
			if(i==1)
			{
				//���ùؿ���ֻλ��
				levelSp[i]->setPosition(Point(positionT.x-sizeT.width,positionT.y+sizeT.height));
			}else if(i==2)
			{
				//���ùؿ���ֻλ��
				levelSp[i]->setPosition(Point(positionT.x+sizeT.width-30,positionT.y));
			}else
			{
				//���ùؿ���ֻλ��
				levelSp[i]->setPosition(Point(positionT.x+sizeT.width,positionT.y+sizeT.height));
			}

		}
		worldMapSp->addChild(levelSp[i],10);
	}
	if(levelNum == 1)
	{
		Sprite* kqzdSp = Sprite::create("kqzd.png");
		kqzdSp->setAnchorPoint(Point(0.5,0));
		kqzdSp->setPosition(Point(25,20));
		levelSp[0]->addChild(kqzdSp,4);
		kqzdSp->runAction(
				RepeatForever::create(
						Sequence::create(
								ScaleTo::create(0.5,1.2),
								ScaleTo::create(0.5,1),
								NULL
						)
				)
		);
		mapStartAnimation();
	}

	Sprite* maoDianSp= Sprite::create("maodian.png");
	Size size = levelSp[levelNum-1]->getContentSize();
	maoDianSp->setPosition(Point(size.width/2,size.height/2));
	levelSp[levelNum-1]->addChild(maoDianSp,3);
	maoDianSp->runAction(RepeatForever::create(
			Sequence::create(
					ScaleTo::create(0.5f,1.2f),
					ScaleTo::create(0.5f,1.0f),
					NULL)));

	for(int i=0;i<2;i++)
	{
		Sprite* tempSp = Sprite::create(StringUtils::format("jqs%d.png",i));
		tempSp->setAnchorPoint(Point(1,0.5));
		tempSp->setPosition(Point(480+i*144,515));
		this->addChild(tempSp,3);

		int tempCount = 0;
		if( i == 0)
		{
			tempCount = UserDefault::getInstance()->getIntegerForKey(Constant::SHADISHU.c_str());
		}else
		{
			tempCount = UserDefault::getInstance()->getIntegerForKey(Constant::COUNTGOLD.c_str());
		}

		LabelAtlas* tempLabel = LabelAtlas::create(				//����һ��LabelAtlas����
				StringUtils::format("%d",tempCount),"labelatlas.png",15,19,'0');
		if(i==0)
		{
			tempLabel->setAnchorPoint(Point(0,0.5));
			tempLabel->setPosition(Point(tempSp->getPosition().x-90,tempSp->getPosition().y));
		}else
		{
			tempLabel->setAnchorPoint(Point(1,0.5));
			tempLabel->setPosition(Point(tempSp->getPosition().x-50,tempSp->getPosition().y));
		}


		this->addChild(tempLabel,3);

	}
	initMenuItem();
	initSound();
	if(ChooseLevelLayer::bacMusicFlag == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()//���ű�������
							->playBackgroundMusic("sound_bgm_worldmap.mp3",true);
	}

	return true;
}
void ChooseLevelLayer::initLevelSpListenerTouch()
{
	auto director = Director::getInstance();
	Scheduler* sched = director->getScheduler();
	sched->scheduleSelector(SEL_SCHEDULE(&ChooseLevelLayer::shipRotationUpdate),this,0.1f,false);

	//����һ�����㴥������
	EventListenerTouchOneByOne* listenerTouch = EventListenerTouchOneByOne::create();
	//�����´�����
	listenerTouch->setSwallowTouches(true);
	//��ʼ����ʱ�ص�onTouchBegan����
	listenerTouch->onTouchBegan = CC_CALLBACK_2(ChooseLevelLayer::onTouchBegan, this);
	//��ʼ����ʱ�ص�onTouchMoved����
	listenerTouch->onTouchMoved = CC_CALLBACK_2(ChooseLevelLayer::onTouchMoved, this);
	//��������ʱ�ص�onTouchEnded����
	listenerTouch->onTouchEnded = CC_CALLBACK_2(ChooseLevelLayer::onTouchEnded, this);
	//��ӵ�������
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTouch, worldMapSp);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTouch->clone(), levelSp[0]);
	for(int i = 1;i<levelCount;i++)
	{
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTouch->clone(), levelSp[i]);
	}
}
void ChooseLevelLayer::mapStartAnimation()
{
	worldMapSp->runAction(
			Sequence::create(
					MoveBy::create(2,Point(0,-100)),
					MoveBy::create(2,Point(0,100)),
					CallFunc::create(CC_CALLBACK_0(ChooseLevelLayer::initLevelSpListenerTouch,this)),
					NULL
			));
}
void ChooseLevelLayer::levelCallback()
{
	std::string linePath = StringUtils::format("line%d.png",levelCount-1);
	Sprite* lineSp = Sprite::create(linePath);
	if(levelCount==2)
	{
		lineSp->setAnchorPoint(Point(1,0));
	}else if(levelCount==3)
	{
		lineSp->setAnchorPoint(Point(0,1));
	}else
	{
		lineSp->setAnchorPoint(Point(0,0));
	}
	lineSp->setVisible(false);
	Size size =levelSp[levelCount-1]->getContentSize();
	Point position = levelSp[levelCount-2]->getPosition();
	if(levelCount==2)
	{
		//�������������������·ͼƬ��λ��
		lineSp->setPosition(Point(position.x+size.width/2,position.y+size.height));
	}else if(levelCount==3)
	{
		//�������������������·ͼƬ��λ��
		lineSp->setPosition(Point(position.x+size.width,position.y+size.height/2));
	}else
	{
		//�������������������·ͼƬ��λ��
		lineSp->setPosition(Point(position.x+size.width,position.y+size.height/2));
	}
	lineSp->runAction(
			Sequence::create(
					FadeOut::create(0),
					Spawn::create(
							ToggleVisibility::create(),
							FadeIn::create(1),
							NULL
					),
					CallFunc::create(CC_CALLBACK_0(ChooseLevelLayer::mapStartAnimation,this)),
					NULL
			));
	worldMapSp->addChild(lineSp,1);
}
void ChooseLevelLayer::initMenuItem()
{
	//��ȡ�ɼ�����ߴ�
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//��ȡ�ɼ�����ԭ������
	Point origin = Director::getInstance()->getVisibleOrigin();

	menuItem[0] = MenuItemImage::create(
			"menuset.png",
			"menusetp.png",
			CC_CALLBACK_0(ChooseLevelLayer::szCallback, this)
	);
	menuItem[1] = MenuItemImage::create(
			"menusj.png",
			"menusjp.png",
			CC_CALLBACK_0(ChooseLevelLayer::sjCallback, this)
	);
	menuItem[2] = MenuItemImage::create(
			"menucj.png",
			"menucjp.png",
			CC_CALLBACK_0(ChooseLevelLayer::cjCallback, this)
	);

	MenuItemImage* backMenuItem =MenuItemImage::create(
				"goback.png",
				"gobackp.png",
				CC_CALLBACK_0(ChooseLevelLayer::backMenuCallback,this)
		);
	backMenuItem->setPosition(Point(30,520));

	//����һ���˵�����
	Menu* menu = Menu::create(menuItem[0],menuItem[1],menuItem[2],backMenuItem,NULL);
	//������λ��
	menu->setPosition(Point::ZERO);
	//������ӵ�������
	this->addChild(menu, 20);
	for(int i=0;i<3;i++)
	{

		Sprite* menuBgSp = Sprite::create("menuBg.png");
		std::string slabel = StringUtils::format("label%d.png",i);
		Sprite* labelSp = Sprite::create(slabel);

		if(i == 0)
		{
			menuBgSp->setPosition(Point(70,70));
			menuItem[0]->setPosition(menuBgSp->getPosition());
			Point p = menuBgSp->getPosition();
			labelSp->setPosition(Point(p.x+55,p.y-55));
		}else
		{
			menuBgSp->setPosition(Point(visibleSize.width/3*2-40+i*130,70));
			menuItem[i]->setPosition(menuBgSp->getPosition());
			Point p = menuBgSp->getPosition();
			labelSp->setPosition(Point(p.x+55,p.y-55));
		}


		this->addChild(menuBgSp,12);
		this->addChild(labelSp,13);
	}


}
void ChooseLevelLayer::bacMusicMenuCallback()
{
	if(ChooseLevelLayer::froMusicFlag == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()
									->playEffect("sound_sfx_click.mp3");
	}
	bacMusicFlag = !bacMusicFlag;
	SpriteFrame* sfN;
	SpriteFrame* sfS;
	if(bacMusicFlag == false)
	{
		sfN = SpriteFrame::create("bacMusicOffc.png",Rect(0,0,33,35));
		sfS = SpriteFrame::create("bacMusicOnc.png",Rect(0,0,33,35));
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		UserDefault::getInstance()->setIntegerForKey(Constant::BGSY.c_str(),1);
	}else
	{
		sfN = SpriteFrame::create("bacMusicOnc.png",Rect(0,0,33,35));
		sfS = SpriteFrame::create("bacMusicOffc.png",Rect(0,0,33,35));
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		UserDefault::getInstance()->setIntegerForKey(Constant::BGSY.c_str(),0);
	}
	musicItem[0]->setNormalSpriteFrame(sfN);
	musicItem[0]->setSelectedSpriteFrame(sfS);
}
void ChooseLevelLayer::froMusicMenuCallback()
{
	froMusicFlag = !froMusicFlag;
	if(ChooseLevelLayer::froMusicFlag == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()
									->playEffect("sound_sfx_click.mp3");
	}
	SpriteFrame* sfN;
	SpriteFrame* sfS;
	if(froMusicFlag == false)
	{
		sfN = SpriteFrame::create("froMusicOffc.png",Rect(0,0,39,30));
		sfS = SpriteFrame::create("froMusicOnc.png",Rect(0,0,39,30));
		UserDefault::getInstance()->setIntegerForKey(Constant::YSSY.c_str(),1);
	}else
	{
		sfN = SpriteFrame::create("froMusicOnc.png",Rect(0,0,39,30));
		sfS = SpriteFrame::create("froMusicOffc.png",Rect(0,0,39,30));
		UserDefault::getInstance()->setIntegerForKey(Constant::YSSY.c_str(),0);
	}
	musicItem[1]->setNormalSpriteFrame(sfN);
	musicItem[1]->setSelectedSpriteFrame(sfS);
}
void ChooseLevelLayer::szCallback()
{
	if(ChooseLevelLayer::froMusicFlag == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()
									->playEffect("sound_sfx_click.mp3");
	}
	if(selecItem == true)
	{
		selecItem = false;
		this->removeChildByTag(1);
		setMenuEnabled(true);
		return;
	}
	for(int i =1;i<3;i++)
	{
		menuItem[i]->setEnabled(false);
	}
	selecItem = true;
	musicItem[0] = MenuItemImage::create(
			"bacMusicOnc.png",
			"bacMusicOffc.png",
			CC_CALLBACK_0(ChooseLevelLayer::bacMusicMenuCallback, this)
	);
	Point psetMenu = menuItem[0]->getPosition();
	musicItem[0]->setPosition(Point(psetMenu.x,psetMenu.y+150));
	bacMusicFlag = !bacMusicFlag;
	bacMusicMenuCallback();

	musicItem[1] = MenuItemImage::create(
			"froMusicOnc.png",
			"froMusicOffc.png",
			CC_CALLBACK_0(ChooseLevelLayer::froMusicMenuCallback, this)
	);
	psetMenu = menuItem[0]->getPosition();
	musicItem[1]->setPosition(Point(psetMenu.x,psetMenu.y+90));

	froMusicFlag = !froMusicFlag;
	froMusicMenuCallback();

	//����һ���˵�����
	Menu* menu = Menu::create(musicItem[0],musicItem[1],NULL);
	//������λ��
	menu->setPosition(Point::ZERO);
	//������ӵ�������
	this->addChild(menu, 14,1);

}
void ChooseLevelLayer::sjCallback()
{
	if(ChooseLevelLayer::froMusicFlag == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()
									->playEffect("sound_sfx_click.mp3");
	}
	setMenuEnabled(false);
	selecItem = true;

	wfsm->goPpgradeScene();
}
void ChooseLevelLayer::cjCallback()
{
	if(ChooseLevelLayer::froMusicFlag == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()
									->playEffect("sound_sfx_click.mp3");
	}
	cjFlag = true;
	setMenuEnabled(false);
	selecItem = true;
	taskSp = Sprite::create("cjtaskTitle.png");
	taskSp->setPosition(Point(200,500));
	taskSp->setScale(0.2);
	this->addChild(taskSp,1);

	taskSp->runAction(
			Sequence::create(
				ScaleTo::create(0.2,1.1),
				ScaleTo::create(0.1,1),
				NULL
			)
	);

	Sprite* aboutBgSp = Sprite::create("cjbg.png");
	aboutBgSp->setAnchorPoint(Point(0,1));
	aboutBgSp->setPosition(Point(0,0));
	taskSp->addChild(aboutBgSp,10);

	ship3DSp = Sprite3D::create("ship3D.obj");
	ship3DSp->setTexture("shipWL.png");
	ship3DSp->setPosition(Point(330,130));
	ship3DSp->setScale(2.8f);
	aboutBgSp->addChild(ship3DSp,100);

	MenuItemImage* closeItem = MenuItemImage::create(
			"close.png",
			"closep.png",
			CC_CALLBACK_0(ChooseLevelLayer::closeMenuCallback, this)
	);
	Size size = aboutBgSp->getContentSize();
	closeItem->setPosition(Point(size.width-30,size.height-30));

	//����һ���˵�����
	Menu* menu = Menu::create(closeItem,NULL);
	//������λ��
	menu->setPosition(Point::ZERO);
	//������ӵ�������
	aboutBgSp->addChild(menu, 3);

	LabelAtlas* countLabel [4];
	std::string countString;

	int count [4];
	count[0] = UserDefault::getInstance()->getIntegerForKey(Constant::WINCOUNT.c_str());
	count[1] = UserDefault::getInstance()->getIntegerForKey(Constant::LOSECOUNT.c_str());
	count[2] = UserDefault::getInstance()->getIntegerForKey(Constant::SHADISHU.c_str());
	count[3] = UserDefault::getInstance()->getIntegerForKey(Constant::GETGOLDCOUNT.c_str());
	for(int i =0;i<4;i++)
	{
		countString = StringUtils::format("%d",count[i]);
		countLabel[i] = LabelAtlas::create(				//����һ��LabelAtlas����
				countString,"labelatlas.png",15,19,'0');
		countLabel[i]->setAnchorPoint(Point(0,0.5));
		countLabel[i]->setScale(1.5);
		switch(i)
		{
		case 0:countLabel[i]->setPosition(Point(195,285));break;
		case 1:countLabel[i]->setPosition(Point(195,220));break;
		case 2:countLabel[i]->setPosition(Point(515,285));break;
		case 3:countLabel[i]->setPosition(Point(515,220));break;
		}
		aboutBgSp->addChild(countLabel[i],13);
	}
}
void ChooseLevelLayer::setMenuEnabled(bool b)
{
	for(int i=0;i<3;i++)
	{
		menuItem[i]->setEnabled(b);
	}
}
void ChooseLevelLayer::initSound()
{
	CocosDenshion::SimpleAudioEngine::getInstance()					//������Ч
						->preloadBackgroundMusic("sound_bgm_worldmap.mp3");
}
bool ChooseLevelLayer::onTouchBegan(Touch* touch, Event* event)
{
	if(selecItem == true)
	{
		return false;
	}
	auto target = static_cast<Sprite*>(	//��ȡ��ǰ�������󣬲�ת��Ϊ��������
						event->getCurrentTarget());
	currPoint = touch->getLocation();
	Point location = target->convertToNodeSpace(touch->getLocation());//��ȡ��ǰ����
	auto size = target->getContentSize();			//��ȡ����Ĵ�С
	auto rect = Rect(0, 0, size.width, size.height);//����һ�����ζ������С�뾫����ͬ
	if( rect.containsPoint(location)){	//�жϴ������Ƿ���Ŀ��ķ�Χ��
		if(target == worldMapSp)
		{
			return true;
		}else if(target == levelSp[0])
		{
			if(ChooseLevelLayer::froMusicFlag == true)
			{
				CocosDenshion::SimpleAudioEngine::getInstance()
											->playEffect("sound_sfx_click.mp3");
			}
			levelSp[0]->runAction(ScaleTo::create(1,1.3));
			PopTaskWindow(0);
			ChooseLevelLayer::levelNum = 1;
		}else if(target == levelSp[1])
		{
			if(ChooseLevelLayer::froMusicFlag == true)
			{
				CocosDenshion::SimpleAudioEngine::getInstance()
											->playEffect("sound_sfx_click.mp3");
			}

			PopTaskWindow(1);
			ChooseLevelLayer::levelNum = 2;
		}else if(target == levelSp[2])
		{
			if(ChooseLevelLayer::froMusicFlag == true)
			{
				CocosDenshion::SimpleAudioEngine::getInstance()
											->playEffect("sound_sfx_click.mp3");
			}
			PopTaskWindow(2);
			ChooseLevelLayer::levelNum = 3;
		}else if(target == levelSp[3])
		{
			if(ChooseLevelLayer::froMusicFlag == true)
			{
				CocosDenshion::SimpleAudioEngine::getInstance()
											->playEffect("sound_sfx_click.mp3");
			}
			PopTaskWindow(3);
			ChooseLevelLayer::levelNum = 4;
		}else if(target == levelSp[4])
		{
			if(ChooseLevelLayer::froMusicFlag == true)
			{
				CocosDenshion::SimpleAudioEngine::getInstance()
											->playEffect("sound_sfx_click.mp3");
			}
			PopTaskWindow(4);
			ChooseLevelLayer::levelNum = 5;
		}
		return true;
	}else{
		return false;
	}
}
void ChooseLevelLayer::initBoomFrame()
{
	std::string sa[6]={						//�����ж���ͼƬ��·��������������
		"boom1.png","boom2.png","boom3.png",
		"boom4.png","boom5.png","boom6.png"
	};
	Vector<SpriteFrame*> animFrames;		//������Ŷ���֡���б����

	SpriteFrame *f0=SpriteFrame::create(sa[0],
						Rect(0,0,104,102));	//��ȡ�˶����е�ָ������֡
	animFrames.pushBack(f0);				//����һ�ζ����е�����֡��ŵ�������

	SpriteFrame *f1=SpriteFrame::create(sa[1],
						Rect(0,0,107,102));	//��ȡ�˶����е�ָ������֡
	animFrames.pushBack(f1);				//����һ�ζ����е�����֡��ŵ�������

	SpriteFrame *f2=SpriteFrame::create(sa[2],
						Rect(0,0,97,95));	//��ȡ�˶����е�ָ������֡
	animFrames.pushBack(f2);				//����һ�ζ����е�����֡��ŵ�������

	SpriteFrame *f3=SpriteFrame::create(sa[3],
						Rect(0,0,93,92));	//��ȡ�˶����е�ָ������֡
	animFrames.pushBack(f3);				//����һ�ζ����е�����֡��ŵ�������

	SpriteFrame *f4=SpriteFrame::create(sa[4],
						Rect(0,0,53,54));	//��ȡ�˶����е�ָ������֡
	animFrames.pushBack(f4);				//����һ�ζ����е�����֡��ŵ�������

	SpriteFrame *f5=SpriteFrame::create(sa[5],
						Rect(0,0,53,53));	//��ȡ�˶����е�ָ������֡
	animFrames.pushBack(f5);				//����һ�ζ����е�����֡��ŵ�������

	Animation *anmi=Animation::createWithSpriteFrames
			(animFrames, 0.1f);					//����ָ�򶯻������ָ��
	anmiAc[0]=Animate::create(anmi);			//����������������
	anmiAc[0]->retain();						//��Ϊ��ʱ���ã����Ա������ã���ֹ���Զ��ͷ�
}
void ChooseLevelLayer::PopTaskWindow(int levelIndex)
{
	selecItem = true;
	setMenuEnabled(false);
	 //��ȡ�ɼ�����ߴ�
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//��ȡ�ɼ�����ԭ������
	Point origin = Director::getInstance()->getVisibleOrigin();

	taskSp = Sprite::create("taskBg.png");
	taskSp->setPosition(Point(visibleSize.width/2-100,visibleSize.height/7*4));
	this->addChild(taskSp,1);

	std::string taskPath = StringUtils::format("level%d.png",levelIndex);
	Sprite* taskImageSp = Sprite::create(taskPath);
	taskImageSp->setPosition(Point(170,190));
	taskSp->addChild(taskImageSp,2);

	boomSp[0] = Sprite::create();
	int spx = rand()%140+40;
	int spy = rand()%140+40;
	boomSp[0]->setPosition(Point(spx,spy));
	taskImageSp->addChild(boomSp[0],1);
	boomSp[0]->runAction(
			RepeatForever::create(
					Sequence::create(
							CallFunc::create(CC_CALLBACK_0(ChooseLevelLayer::resetBoom0spPosition,this)),
							DelayTime::create(2),
							Spawn::create(
								FadeIn::create(0.5),
								anmiAc[0]->clone(),
								NULL
							),
							FadeOut::create(0.2),
							DelayTime::create(2),
							NULL
					)));

	//��ͼ�ϱ�ը=======================begin
	boomSp[1] = Sprite::create();
	spx = rand()%140+40;
	spy = rand()%140+40;
	boomSp[1]->setPosition(Point(spx,spy));
	taskImageSp->addChild(boomSp[1],1);
	boomSp[1]->runAction(
			RepeatForever::create(
					Sequence::create(
							CallFunc::create(CC_CALLBACK_0(ChooseLevelLayer::resetBoom1spPosition,this)),
							DelayTime::create(1),
							Spawn::create(
									FadeIn::create(0.5),
									anmiAc[0]->clone(),
									NULL
							),
							FadeOut::create(0.2),
							DelayTime::create(1),
							NULL
					)));

	boomSp[2] = Sprite::create();
	spx = rand()%140+40;
	spy = rand()%140+40;
	boomSp[2]->setPosition(Point(spx,spy));
	taskImageSp->addChild(boomSp[2],1);
	boomSp[2]->runAction(
			RepeatForever::create(
					Sequence::create(
							CallFunc::create(CC_CALLBACK_0(ChooseLevelLayer::resetBoom2spPosition,this)),
							DelayTime::create(1.5),
							Spawn::create(
									FadeIn::create(0.5),
									anmiAc[0]->clone(),
									NULL
							),
							FadeOut::create(0.2),
							DelayTime::create(1.5),
							NULL
					)));
	//��ͼ�ϱ�ը=======================end
	Sprite* taskTitleSp = Sprite::create("taskTitle.png");
	taskTitleSp->setAnchorPoint(Point(0,0));
	taskTitleSp->setPosition(Point(0,taskSp->getContentSize().height-2));
	taskSp->addChild(taskTitleSp,2);

	for(int i=0;i<2;i++)
	{
		Sprite* bgSp = Sprite::create("bgc.png");
		bgSp->setAnchorPoint(Point(0,0));
		bgSp->setPosition(Point(80+i*100,5));
		taskSp->addChild(bgSp,3);
	}

	std::string levelString ;
	switch(levelIndex)
	{
	case 0:
		levelString = "LEVEL1";
		break;
	case 1:
		levelString = "LEVEL2";
		break;
	case 2:
		levelString = "LEVEL3";
		break;
	case 3:
		levelString = "LEVEL4";
		break;
	}

	int jx = UserDefault::getInstance()->getIntegerForKey(levelString.c_str());

	int jxs = jx/10;
	int jxg = jx%10;
	Sprite* jxcySp;

	if(jxs == 1)
	{
		jxcySp = Sprite::create("jx01.png");
	}else
	{
		jxcySp = Sprite::create("jx00.png");
	}
	jxcySp->setAnchorPoint(Point(0,0));
	jxcySp->setPosition(Point(85,5));
	taskSp->addChild(jxcySp,3);

	if(jxg == 1)
	{
		jxcySp = Sprite::create("jx11.png");
	}else
	{
		jxcySp = Sprite::create("jx10.png");
	}
	jxcySp->setAnchorPoint(Point(0,0));
	jxcySp->setPosition(Point(182,5));
	taskSp->addChild(jxcySp,3);


	std::string labelPath ;
	switch(levelIndex)
	{
	case 0:	labelPath = "\u548c\u5e73\u906d\u591c\u88ad";		break;
	case 1:	labelPath = "\u51b0\u878d\u5b88\u6d77\u7586";		break;
	case 2: labelPath = "\u5730\u72f1\u4e4b\u6218";  		break;
	case 3: labelPath = "\u6218\u540e\u5929\u5802";  		break;
	}

	Label* titleLabel = Label::createWithTTF(labelPath,"FZKATJW.ttf",30);
	titleLabel->setAnchorPoint(Point(0,0.5));
	titleLabel->setPosition(Point(10,30));
	taskTitleSp->addChild(titleLabel,0);

	MenuItemImage* ksItem = MenuItemImage::create(
			"button.png",
			"buttonp.png",
			CC_CALLBACK_0(ChooseLevelLayer::ksMenuCallback, this)
	);
	ksItem->setAnchorPoint(Point(1,0));
	ksItem->setPosition(Point(taskSp->getContentSize().width-30,5));

	MenuItemImage* jbItem = MenuItemImage::create(
			"button.png",
			"buttonp.png",
			CC_CALLBACK_0(ChooseLevelLayer::jbMenuCallback, this)
	);
	jbItem->setAnchorPoint(Point(1,0));
	jbItem->setPosition(Point(taskSp->getContentSize().width-180,5));

	MenuItemImage* closeItem = MenuItemImage::create(
			"close.png",
			"closep.png",
			CC_CALLBACK_0(ChooseLevelLayer::closeMenuCallback, this)
	);
	closeItem->setAnchorPoint(Point(0.5,0.5));
	closeItem->setPosition(Point(taskSp->getContentSize().width-30,taskSp->getContentSize().height-30));

	//����һ���˵�����
	Menu* menu = Menu::create(ksItem,jbItem,closeItem,NULL);
	//������λ��
	menu->setPosition(Point::ZERO);
	//������ӵ�������
	taskSp->addChild(menu, 2);

	Point pp[4];//����һ����������飬�����������
	pp[0] = Point(0, 0);//�����������ֵ
	pp[1] = Point(293, 0);//�����������ֵ
	pp[2] = Point(293, 165);//�����������ֵ
	pp[3] = Point(0, 165);//�����������ֵ
	Color4F green(0, 1, 0, 0);//����������ɫ
	Color4F red(1, 0, 0, 0.5f);//����α߿���ɫ
	//����������DrawNode
	DrawNode* shape = DrawNode::create();
	shape->drawPolygon(pp ,4, green, 2,red);//���ƶ����
	//�������ýڵ�
	ClippingNode* clipper=ClippingNode::create();
	//���ü���ģ��
	clipper->setStencil(shape);
	//���ü��ýڵ�λ��
	clipper->setPosition(Point(315,105));
	//�������ýڵ���õ�����
	taskSp->addChild(clipper, 10);

	std::string wzbgPath = StringUtils::format("wzbg%d.png",levelIndex);
	wzbgSp = Sprite::create(wzbgPath);
	wzbgSp->setAnchorPoint(Point(0,1));
	wzbgSp->setPosition(Point(22,0));
	clipper->addChild(wzbgSp,3);
	PopTaskWdFlag = true;

	Label* ksLabel = Label::createWithTTF("\u5f00\u59cb","FZKATJW.ttf",30);
	ksLabel->setPosition(Point(85,30));
	ksItem->addChild(ksLabel,0);

	Sprite* miaSp = Sprite::create("mia.png");
	miaSp->setPosition(Point(30,30));
	ksItem->addChild(miaSp,0);

	jbLabel = Label::createWithTTF("\u7b80\u5355","FZKATJW.ttf",30);
	jbLabel->setPosition(Point(85,30));
	jbItem->addChild(jbLabel,0);

	Sprite* jxSp = Sprite::create("jxc.png");
	jxSp->setPosition(Point(30,30));
	jbItem->addChild(jxSp,0);

	taskSp->setScale(0.1);
	taskSp->runAction(ScaleTo::create(0.3,1));
}
void ChooseLevelLayer::closeMenuCallback()
{
	setMenuEnabled(true);
	selecItem = false;
	PopTaskWdFlag = false;
	cjFlag = false;
	if(ChooseLevelLayer::froMusicFlag == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()
									->playEffect("sound_sfx_click.mp3");
	}
	taskSp->runAction(
			Sequence::create(
					ScaleTo::create(0.2,0.1),
					RemoveSelf::create(true),
					NULL)
	);

}
void ChooseLevelLayer::ksMenuCallback()
{
	if(ChooseLevelLayer::froMusicFlag == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()
									->playEffect("sound_sfx_click.mp3");
	}
	wfsm->goGameScene();
}
void ChooseLevelLayer::jbMenuCallback()
{
	if(ChooseLevelLayer::froMusicFlag == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()							//��ʹ��Ч
									->playEffect("sound_sfx_star_3.mp3");
	}
	jbIndex++;
	jbIndex = jbIndex%3;
	switch(jbIndex)
	{
	case 0:jbLabel->setString("\u7b80\u5355");ChooseLevelLayer::enemyBaseLife = 100;break;
	case 1:jbLabel->setString("\u666e\u901a");ChooseLevelLayer::enemyBaseLife = 200;break;
	case 2:jbLabel->setString("\u56f0\u96be");ChooseLevelLayer::enemyBaseLife = 400;break;
	}
}
void ChooseLevelLayer::onTouchMoved(Touch* touch, Event* event)
{
	float deltaY = touch->getLocation().y-currPoint.y;
	float pointY = worldMapPoint.y+deltaY;
	if(pointY <=0&&pointY >=-100)
	{
		worldMapSp->setPosition(0,pointY);
	}
}
void ChooseLevelLayer::onTouchEnded(Touch* touch, Event* event)
{
	worldMapPoint = worldMapSp->getPosition();
}
int ChooseLevelLayer::myGetIntegerForKey (std::string key)
{
	int result = UserDefault::getInstance()->getIntegerForKey(key.c_str());
	return result;
}
void ChooseLevelLayer::backMenuCallback()
{
	if(ChooseLevelLayer::froMusicFlag == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()
							->playEffect("sound_sfx_click.mp3");
	}
	wfsm->goStartScene();
}
void ChooseLevelLayer::shipRotationUpdate()
{
	if(cjFlag == true)
	{
		ship3DSp -> setRotation3D(Vertex3F(0,ship3DSp -> getRotation3D().y+1,0));
	}
	if(PopTaskWdFlag == true)
	{
		if(wzbgSp->getPosition().y <= 520)
		{
			wzbgSp->setPosition(Point(wzbgSp->getPosition().x,wzbgSp->getPosition().y+2.5));
		}else
		{
			wzbgSp->setPosition(Point(22,0));
		}

	}
}
void ChooseLevelLayer::resetBoom0spPosition()
{
	int spx = rand()%140+40;
	int spy = rand()%140+40;
	boomSp[0]->setPosition(Point(spx,spy));
}
void ChooseLevelLayer::resetBoom1spPosition()
{
	int spx = rand()%140+40;
	int spy = rand()%140+40;
	boomSp[1]->setPosition(Point(spx,spy));
}
void ChooseLevelLayer::resetBoom2spPosition()
{
	int spx = rand()%140+40;
	int spy = rand()%140+40;
	boomSp[2]->setPosition(Point(spx,spy));
}
