#include "cocos2d.h"
#include "UpgradeLayer.h"
#include "Constant.h"
#include "ChooseLevelLayer.h"

using namespace cocos2d;

bool UpgradeLayer::init()
{
	//调用父类的初始化
	if ( !Layer::init() )
	{
		return false;
	}
	Sprite* bacSp = Sprite::create("ship_upgrade_bg.png");
	bacSp->setPosition(Point(480,270));
	this->addChild(bacSp,1);

	Label* titleLabel = Label::createWithTTF("\u795e\u79d8\u5723\u5730","FZKATJW.ttf",30);
	titleLabel->setPosition(Point(480,527));
	this->addChild(titleLabel,2);

	Sprite* moneySp = Sprite::create("jb.png");
	moneySp->setPosition(Point(930,520));
	moneySp->setScale(0.2);
	this->addChild(moneySp,3);

	Sprite* sjjqSp = Sprite::create("sjjq.png");
	sjjqSp->setPosition(Point(470,390));
	this->addChild(sjjqSp,3);

	int rank = UserDefault::getInstance()->getIntegerForKey(selectShipst.c_str());
	std::string needMSt = StringUtils::format("%d",(rank+1)*300);

	nMoneyLabel = LabelAtlas::create(				//创建一个LabelAtlas对象
			needMSt,"labelatlas.png",15,19,'0');
	nMoneyLabel->setAnchorPoint(Point(0,0.5));
	nMoneyLabel->setPosition(Point(sjjqSp->getPosition().x+80,sjjqSp->getPosition().y));
	this->addChild(nMoneyLabel,3);

	int temp = UserDefault::getInstance()->getIntegerForKey(Constant::COUNTGOLD.c_str());
	std::string moneySt = StringUtils::format("%d",temp);
	moneyLabel = LabelAtlas::create(				//创建一个LabelAtlas对象
			moneySt,"labelatlas.png",15,19,'0');
	moneyLabel->setAnchorPoint(Point(1,0.5));
	moneyLabel->setPosition(Point(moneySp->getPosition().x-40,moneySp->getPosition().y));
	this->addChild(moneyLabel,3);

	int index = 1;
	std::string objPath = StringUtils::format("daodan%d.obj",index);
	std::string pngPath = StringUtils::format("daodan%d.png",index);

	weapon = Sprite3D::create(objPath);
	weapon->setTexture(pngPath);
	weapon->setPosition(Point(325,260));
	weapon->setRotation3D(Vertex3F(-40,79,0));
	this->addChild(weapon,3);

	Point pp[4];//创建一个坐标点数组，用于描绘多边形
	pp[0] = Point(0, 0);//设置坐标点数值
	pp[1] = Point(236, 0);//设置坐标点数值
	pp[2] = Point(236, 230);//设置坐标点数值
	pp[3] = Point(0, 230);//设置坐标点数值
	Color4F green(0, 1, 0, 0);//多边形填充颜色
	Color4F red(1, 0, 0, 0.5f);//多边形边框颜色
	//创建剪裁用DrawNode
	DrawNode* shape = DrawNode::create();
	shape->drawPolygon(pp ,4, green, 2,red);//绘制多边形
	//创建剪裁节点
	ClippingNode* clipper=ClippingNode::create();
	//设置剪裁模板
	clipper->setStencil(shape);
	//设置剪裁节点位置
	clipper->setPosition(Point(710,205));
	//将被剪裁节点放置到层中
	this->addChild(clipper, 10);

	for(int i = 0;i<2;i++)
	{
		std::string spath = StringUtils::format("ddjj%d.png",i);
		ddjjSp[i] = Sprite::create(spath);
		ddjjSp[i]->setAnchorPoint(Point(0,1));
		ddjjSp[i]->setPosition(Point(0,0));
		clipper->addChild(ddjjSp[i],3);
	}
	ddjjSp[1]->setVisible(false);

	initShipMenu();

	selectToolSp = Sprite::create("selectTool.png");
	selectToolSp->setPosition(Point(85,40));
	this->addChild(selectToolSp,10);

	toolBarSp= Sprite::create("toolBar.png");
	toolBarSp->setAnchorPoint(Point(0.324,0.64));
	toolBarSp->setPosition(Point(16,90));
	selectToolSp->addChild(toolBarSp,5);

	toolSZJSp= Sprite::create("toolSZJ.png");
	toolSZJSp->setPosition(Point(73,12));
	toolBarSp->addChild(toolSZJSp,-1);

	toolPacSp= Sprite::create("toolPackge.png");
	toolPacSp->setPosition(Point(73,12));
	toolBarSp->addChild(toolPacSp,-2);

	Sprite* toolLSDSp= Sprite::create("toolLSD.png");
	toolLSDSp->setPosition(Point(94,18));
	selectToolSp->addChild(toolLSDSp,5);

	toolGGSp= Sprite::create("toolGG0.png");
	toolGGSp->setAnchorPoint(Point(0.5,0));
	toolGGSp->setPosition(Point(94,18));
	selectToolSp->addChild(toolGGSp,4);

	toolGG1Sp= Sprite::create("toolGG1.png");
	toolGG1Sp->setAnchorPoint(Point(0.5,0));
	toolGG1Sp->setPosition(Point(5,31));
	toolGGSp->addChild(toolGG1Sp,5);

	Sprite* toolCZSp= Sprite::create("toolCZ.png");
	toolCZSp->setAnchorPoint(Point(0.5,0.7));
	toolCZSp->setPosition(Point(5,30));
	toolGG1Sp->addChild(toolCZSp,5);

	disWeaponStar("SHIPZERO");

	auto director = Director::getInstance();
	Scheduler* sched = director->getScheduler();
	sched->scheduleSelector(SEL_SCHEDULE(&UpgradeLayer::weaponStageUpdate),this,0.1f,false);

	if(ChooseLevelLayer::froMusicFlag == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()							//即使音效
								->preloadEffect("getCoin.mp3");
	}

	return true;
}
void UpgradeLayer::sjRunAction()
{
	toolBarSp->runAction(
			Sequence::create(
				RotateTo::create(0.5,45),
				CallFunc::create(CC_CALLBACK_0(UpgradeLayer::openSZJ,this)),
				CallFunc::create(CC_CALLBACK_0(UpgradeLayer::toolGGSpRunAction,this)),
				RotateTo::create(0.5,0),
				CallFunc::create(CC_CALLBACK_0(UpgradeLayer::addPacSp,this)),
				NULL
			)
	);
}
void UpgradeLayer::toolGGSpRunAction()
{
	toolGGSp->runAction(
			Sequence::create(
					RotateTo::create(0.6,-30),
					CallFunc::create(CC_CALLBACK_0(UpgradeLayer::rotateGG1,this)),
					RotateTo::create(0.6,0),
					NULL
			)
	);
}
void UpgradeLayer::rotateGG1()
{
	toolGG1Sp->runAction(
			Sequence::create(
				RotateTo::create(0.1,-20),
				RotateTo::create(0.1,0),
				NULL
			)
	);
}
void UpgradeLayer::openSZJ()
{
	toolSZJSp->runAction(
			Sequence::create(
				ScaleTo::create(0.1,1.3),
				CallFunc::create(CC_CALLBACK_0(UpgradeLayer::removePacSp,this)),
				ScaleTo::create(0.1,1),
				NULL
			)
	);
}
void UpgradeLayer::removePacSp()
{
	toolBarSp->removeChild(toolPacSp,true);
}
void UpgradeLayer::addPacSp()
{
	toolPacSp= Sprite::create("toolPackge.png");
	toolPacSp->setPosition(Point(73,12));
	toolBarSp->addChild(toolPacSp,-2);
}
void UpgradeLayer::initShipMenu()
{
	shipMenu[0] =MenuItemImage::create(
			"warShip00.png",
			"warShip00.png",
			CC_CALLBACK_0(UpgradeLayer::shipZeroCallback,this)
	);
	shipMenu[0]->setPosition(Point(85,40));

	shipMenu[1] =MenuItemImage::create(
			"warShip11.png",
			"warShip11.png",
			CC_CALLBACK_0(UpgradeLayer::shipOneCallback,this)
	);
	shipMenu[1]->setPosition(Point(205,40));

	shipMenu[2] =MenuItemImage::create(
			"warShip22.png",
			"warShip22.png",
			CC_CALLBACK_0(UpgradeLayer::shipTwoCallback,this)
	);
	shipMenu[2]->setPosition(Point(325,40));

	shipMenu[3] =MenuItemImage::create(
			"warShip33.png",
			"warShip33.png",
			CC_CALLBACK_0(UpgradeLayer::shipThreeCallback,this)
	);
	shipMenu[3]->setPosition(Point(445,40));

	shipMenu[4] =MenuItemImage::create(
			"warShip44.png",
			"warShip44.png",
			CC_CALLBACK_0(UpgradeLayer::shipFourCallback,this)
	);
	shipMenu[4]->setPosition(Point(565,40));

	MenuItemImage* leftMenuItem =MenuItemImage::create(
			"left.png",
			"leftp.png",
			CC_CALLBACK_0(UpgradeLayer::direcMenuCallback,this)
	);
	leftMenuItem->setPosition(Point(100,270));

	MenuItemImage* rightMenuItem =MenuItemImage::create(
			"right.png",
			"rightp.png",
			CC_CALLBACK_0(UpgradeLayer::direcMenuCallback,this)
	);
	rightMenuItem->setPosition(Point(550,270));

	MenuItemImage* sjMenuItem =MenuItemImage::create(
			"buttomBg.png",
			"buttomBgp.png",
			CC_CALLBACK_0(UpgradeLayer::sjwqMenuCallback,this)
	);
	sjMenuItem->setPosition(Point(820,30));


	MenuItemImage* backMenuItem =MenuItemImage::create(
			"goback.png",
			"gobackp.png",
			CC_CALLBACK_0(UpgradeLayer::backMenuCallback,this)
	);
	backMenuItem->setPosition(Point(30,520));

	Menu* menu = Menu::create(shipMenu[0],shipMenu[1],shipMenu[2],shipMenu[3],shipMenu[4],
					sjMenuItem,leftMenuItem,rightMenuItem,backMenuItem,NULL);
	//设置其位置
	menu->setPosition(Point::ZERO);
	//将其添加到布景中
	this->addChild(menu,5);
}
void UpgradeLayer::backMenuCallback()
{
	if(ChooseLevelLayer::froMusicFlag == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()
							->playEffect("sound_sfx_click.mp3");
	}
	wfsm->goChooseLevelScene();
}
void UpgradeLayer::sjwqMenuCallback()
{
	int rank = UserDefault::getInstance()->getIntegerForKey(selectShipst.c_str());
	restMoney = UserDefault::getInstance()->getIntegerForKey(Constant::COUNTGOLD.c_str());
	moneyCount = restMoney;
	restMoney = restMoney - (menuIndex+1)*(rank+1)*200;
	if(rank >= 4||restMoney<0)
	{
		moneyLabel->runAction(
				Sequence::create(
						ScaleTo::create(0.5,1.5),
						ScaleTo::create(0.5,1),
						NULL
				));
		return ;
	}
	UserDefault::getInstance()->setIntegerForKey(Constant::COUNTGOLD.c_str(),restMoney);
	UserDefault::getInstance()->setIntegerForKey(selectShipst.c_str(),rank+1);
	sjRunAction();
	disWeaponStar(selectShipst);
	tempCoinPoint=shipMenu[menuIndex]->getPosition();
	Sprite* tempCoin = Sprite::create("jb.png");
	tempCoin->setPosition(Point(930,520));
	tempCoin->setScale(0.2);
	this->addChild(tempCoin,20);
	decMoneyFlag = true;
	//金币运动到船的位置
	tempCoin->runAction(
			Sequence::create(
					Spawn::create(
							MoveTo::create(0.5,tempCoinPoint),
							Sequence::create(
									ScaleTo::create(0.2,0.3),
									CallFunc::create(CC_CALLBACK_0(UpgradeLayer::createCoin,this)),
									ScaleTo::create(0.2,0.15),
									FadeOut::create(0.1),
									CallFunc::create(CC_CALLBACK_0(UpgradeLayer::liangPlist,this)),
									NULL
							),
							NULL
					),
					RemoveSelf::create(true),
					NULL
			));
}
//创建金币
void UpgradeLayer::createCoin()
{
	if(ChooseLevelLayer::froMusicFlag == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()
								->playEffect("getCoin.mp3");
	}

	creatCoinNum++;
	if(creatCoinNum == 14)
	{
		creatCoinNum = 0;
		return ;
	}
	if(creatCoinNum == 13)
	{
		Sprite* tempCoin = Sprite::create("jb.png");
		tempCoin->setPosition(Point(930,520));
		tempCoin->setScale(0.2);
		this->addChild(tempCoin,20);
		tempCoin->runAction(
				Sequence::create(
						Spawn::create(
								MoveTo::create((float)(0.5-(float)(creatCoinNum)/15),tempCoinPoint),
								Sequence::create(
										ScaleTo::create(0.1,0.25),
										CallFunc::create(CC_CALLBACK_0(UpgradeLayer::createCoin,this)),
										Spawn::create(
												ScaleTo::create(0.1,0.4),
												FadeOut::create(0.1),
												NULL
												),
										NULL
								),
								NULL
						),
						RemoveSelf::create(true),
						NULL
				));
		return;
	}
	Sprite* tempCoin = Sprite::create("jb.png");
	tempCoin->setPosition(Point(930,520));
	tempCoin->setScale(0.2);
	this->addChild(tempCoin,20);
	tempCoin->runAction(
			Sequence::create(
					Spawn::create(
							MoveTo::create((float)(0.5-(float)(creatCoinNum)/15),tempCoinPoint),
							Sequence::create(
									ScaleTo::create(0.1,0.25),
									CallFunc::create(CC_CALLBACK_0(UpgradeLayer::createCoin,this)),
									Spawn::create(
											ScaleTo::create(0.1,0.4),
											FadeOut::create(0.1),
											NULL
											),
									NULL
							),
							NULL
					),
					RemoveSelf::create(true),
					NULL
			));
}
void UpgradeLayer::liangPlist()
{
	ParticleSystemQuad* psq = ParticleSystemQuad::create("liang.plist");//从文件中加载粒子系统
	psq->setPositionType(ParticleSystem::PositionType::RELATIVE);
	psq->retain();									//保持引用
	psq->setBlendAdditive(true);					//设置混合方式为增加
	psq->setPosition(tempCoinPoint);
	this->addChild(psq, 10);		//向布景层中的精灵添加粒子系统
}
void UpgradeLayer::disWeaponStar(std::string key)
{
	if(ChooseLevelLayer::froMusicFlag == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()							//即使音效
									->playEffect("sound_sfx_star_3.mp3");
	}
	starsRotationFlag = false;
	for(int i = 0;i<5;i++)
	{
		this->removeChildByTag(i);
	}
	int temp = UserDefault::getInstance()->getIntegerForKey(key.c_str());
	starsNum = temp;

	for(int i = 0;i<temp;i++)
	{
		stars3D[i] = Sprite3D::create("gold3D.obj");
		stars3D[i]->setTexture("glod.png");
		stars3D[i]->setScale(0.3);
		stars3D[i]->setPosition(Point(740+i*50,155));
		stars3D[i]->setRotation3D(Vertex3F(0,starsRotation,0));
		this->addChild(stars3D[i],5,i);
	}
	starsRotationFlag = true;
	if(temp == 4)
	{
		if(wqSp != NULL)
		{
			this->removeChild(wqSp,true);
		}
		//无穷金币
		nMoneyLabel->setVisible(false);
		wqSp = Sprite::create("wq.png");
		wqSp->setAnchorPoint(Point(0,0.5));
		wqSp->setPosition(nMoneyLabel->getPosition());
		this->addChild(wqSp,3);
	}else
	{
		if(wqSp != NULL)
		{
			this->removeChild(wqSp,true);
		}
		nMoneyLabel->setVisible(true);
		std::string nmSt = StringUtils::format("%d",(menuIndex+1)*(temp+1)*200);
		nMoneyLabel->setString(nmSt);
	}
}
void UpgradeLayer::direcMenuCallback()
{
	if(ChooseLevelLayer::froMusicFlag == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()
							->playEffect("sound_sfx_click.mp3");
	}
	if(daodanIndex == 0)
	{
		daodanIndex = 1;
		ddjjSp[0]->setVisible(false);
		ddjjSp[1]->setVisible(true);
		ddjjSp[1]->setPosition(Point(0,0));
	}else
	{
		daodanIndex = 0;
		ddjjSp[0]->setVisible(true);
		ddjjSp[1]->setVisible(false);
		ddjjSp[0]->setPosition(Point(0,0));
	}
	updateDaoDan(daodanIndex);
}
void UpgradeLayer::updateDaoDan(int index)
{
	this->removeChild(weapon,true);
	std::string objPath = StringUtils::format("daodan%d.obj",index);
	std::string pngPath = StringUtils::format("daodan%d.png",index);
	weapon = Sprite3D::create(objPath);
	if(index == 0 )
	{
		weapon->setScale(0.09f);
		weapon->setPosition(Point(325,260));
	}else
	{
		weapon->setScaleY(1.0f);
		weapon->setPosition(Point(325,260));
	}

	weapon->setRotation3D(Vertex3F(-40,79+deltaAngleY,0));
	rotation[0] = -40;
	rotation[1] = 79;
	rotation[2] = 0;

	weapon->setTexture(pngPath);

	this->addChild(weapon,3);
}
void UpgradeLayer::shipZeroCallback()
{
	if(menuIndex == 0)
	{
		return;
	}
	float doTime = 0.5;
	selectToolSp->runAction(
					MoveTo::create(doTime,Point(85,40))
		);
	selectShipst = "SHIPZERO";
	menuIndex =0;
	disWeaponStar(selectShipst);
}
void UpgradeLayer::shipOneCallback()
{
	if(menuIndex == 1)
	{
		return;
	}
	float doTime = 0.5;
	selectToolSp->runAction(
			MoveTo::create(doTime,Point(205,40))
		);
	selectShipst = "SHIPONE";
	menuIndex =1;
	disWeaponStar(selectShipst);
}
void UpgradeLayer::shipTwoCallback()
{
	if(menuIndex == 2)
	{
		return;
	}
	float doTime = 0.5;
	selectToolSp->runAction(
			MoveTo::create(doTime,Point(325,40))
		);
	selectShipst = "SHIPTWO";
	menuIndex =2;
	disWeaponStar(selectShipst);
}
void UpgradeLayer::shipThreeCallback()
{
	if(menuIndex == 3)
	{
		return;
	}
	float doTime = 0.5;
	selectToolSp->runAction(
			MoveTo::create(doTime,Point(445,40))
		);
	selectShipst = "SHIPTHREE";
	menuIndex =3;
	disWeaponStar(selectShipst);
}
void UpgradeLayer::shipFourCallback()
{
	if(menuIndex == 4)
	{
		return;
	}
	float doTime = 0.5;
	selectToolSp->runAction(
			MoveTo::create(doTime,Point(565,40))
		);
	selectShipst = "SHIPFOUR";
	menuIndex =4;
	disWeaponStar(selectShipst);
}

void UpgradeLayer::weaponStageUpdate()
{
	deltaAngleY = deltaAngleY + 2;
	weapon->setRotation3D(Vertex3F(-40,79+deltaAngleY,0));
	if(ddjjSp[daodanIndex]->getPosition().y<480)
	{
		ddjjSp[daodanIndex] ->setPosition(
				Point(
						ddjjSp[daodanIndex]->getPosition().x,
						ddjjSp[daodanIndex]->getPosition().y+2.5));
	}else
	{
		ddjjSp[daodanIndex]->setPosition(Point(0,0));
	}
	if(decMoneyFlag == true)
	{
		moneyCount = moneyCount-100;
		std::string moneystr = StringUtils::format("%d",moneyCount);
		moneyLabel->setString(moneystr);
		if(moneyCount <= restMoney)
		{
			decMoneyFlag = false;
		}
	}
	if(starsRotationFlag == true)
	{
		for(int i=0;i<starsNum;i++)
		{
			stars3D[i]->setRotation3D(Vertex3F(0,stars3D[i]->getRotation3D().y+2,0));
		}
		starsRotation = stars3D[0]->getRotation3D().y;
	}
}
