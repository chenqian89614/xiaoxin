#include "GameLayer.h"
#include "AppMacros.h"
#include "Constant.h"
#include "BNSocketUtil.h"

USING_NS_CC;

bool GameLayer::init()
{
	//调用父类的初始化
	if(!Layer::init())
	{
		return false;
	}
	//添加背景
	this->addChild(TankSceneManager::getGround(),0);
	initTank();
	initBatchNode();

	//设置定时回调指定方法干活
	auto director = Director::getInstance();
	auto sched = director->getScheduler();
	//定时回调update的方法
	sched->schedule(SEL_SCHEDULE(&GameLayer::update), this, 0.01, false);
	sched->schedule(SEL_SCHEDULE(&GameLayer::updateBoss), this, 0.01, false);
	sched->schedule(SEL_SCHEDULE(&GameLayer::updateMap), this, 0.01, false);
	sched->schedule(SEL_SCHEDULE(&GameLayer::updateBullet), this, 0.01, false);
	sched->schedule(SEL_SCHEDULE(&GameLayer::updateTank), this, 0.01, false);

	return true;
}

void GameLayer::updateTank()
{
	if(BNSocketUtil::tankFlag==1)//移动坦克位置
	{
		BNSocketUtil::tankFlag = 2;
		moveTank(Constant::redX, Constant::redY, Constant::redTankAngle,
				Constant::greenX, Constant::greenY, Constant::greenTankAngle);
		rotateGun(Constant::redGunAngle, Constant::greenGunAngle);
		BNSocketUtil::tankFlag = 0;
	}
}

void GameLayer::updateBullet()
{
	if(BNSocketUtil::mainBulletFlag==1)//玩家坦克子弹
	{
		BNSocketUtil::mainBulletFlag=2;
		setMainBullet();
		BNSocketUtil::mainBulletFlag=0;
	}
	if(BNSocketUtil::mainMissileFlag==1)//玩家坦克导弹
	{
		BNSocketUtil::mainMissileFlag=2;
		setMainMissile();
		BNSocketUtil::mainMissileFlag=0;
	}
}

void GameLayer::updateMap()
{
	if(BNSocketUtil::mapDataFlag==1)//其他物体
	{
		BNSocketUtil::mapDataFlag=2;
		setMapData();
		BNSocketUtil::mapDataFlag=0;
	}
	if(BNSocketUtil::mapTreeFlag==1)//树
	{
		BNSocketUtil::mapTreeFlag=2;
		setMapTree();
		BNSocketUtil::mapTreeFlag=0;
	}
	if(BNSocketUtil::mapTankFlag==1)//敌方坦克
	{
		BNSocketUtil::mapTankFlag=2;
		setMapTank();
		BNSocketUtil::mapTankFlag=0;
	}
	if(BNSocketUtil::explosionFlag==1)//爆炸效果
	{
		BNSocketUtil::explosionFlag=2;
		setExplosion();
		BNSocketUtil::explosionFlag=0;
	}
}

void GameLayer::updateBoss()
{
	if(BNSocketUtil::bossNewFlag==1)//创建boss
	{
		BNSocketUtil::bossNewFlag=2;
		setNewBoss();
		BNSocketUtil::bossNewFlag=0;
	}
	if(BNSocketUtil::bossFlag==1)//boss
	{
		BNSocketUtil::bossFlag=2;
		Sprite *boss=(Sprite*)(this->getChildByTag(100));
		boss->setPosition(Point(Constant::bossX, HEIGHT-Constant::bossY));
		boss->setTextureRect(Rect(bossX*((bossNumber/40)%2),bossY*((bossNumber/40)/3),bossX,bossY));
		bossNumber=(bossNumber+1)%240;
		BNSocketUtil::bossFlag=0;
	}
	if(BNSocketUtil::bossBulletFlag==1)//boss子弹
	{
		BNSocketUtil::bossBulletFlag=2;
		setBossBullet();
		BNSocketUtil::bossBulletFlag=0;
	}
	if(BNSocketUtil::clearFlag==1)//删除boss
	{
		BNSocketUtil::clearFlag=2;
		setClear();
		BNSocketUtil::clearFlag=0;
	}
}

void GameLayer::update()
{
	if(BNSocketUtil::awardFlag==1)//奖励
	{
		BNSocketUtil::awardFlag=2;
		setAward();
		BNSocketUtil::awardFlag=0;
	}
	if(BNSocketUtil::otherBulletFlag==1)//敌方坦克子弹
	{
		BNSocketUtil::otherBulletFlag=2;
		setOtherBullet();
		BNSocketUtil::otherBulletFlag=0;
	}
}

void GameLayer::setNewBoss()
{
	Sprite *boss;
	if(Constant::bossNum==1)
	{
		bossX=294;
		bossY=284;
		boss=Sprite::create(PIC_PATH+std::string("boss1.png"),Rect(0,0,bossX,bossY));
		bossTag=TAG_BOSS_FIRST;
	}else
	{
		bossX=321;
		bossY=289;
		boss=Sprite::create(PIC_PATH+std::string("boss2.png"),Rect(0,0,bossX,bossY));
		bossTag=TAG_BOSS_SECOND;
	}

	this->addChild(boss,LAYER_BOSS,100);
}

void GameLayer::setClear()
{
	this->removeChildByTag(100,true);
	SpriteBatchNode *tempSBN=(SpriteBatchNode*)(this->getChildByTag(bossTag));
	tempSBN->removeAllChildrenWithCleanup(true);
}

void GameLayer::setBossBullet()
{
	std::vector<float>::iterator iter = (Constant::bossBullet).begin();
	SpriteBatchNode *tempSBN=(SpriteBatchNode*)(this->getChildByTag(bossTag));
	int i=0;
	int count=tempSBN->getChildrenCount();
	for(;iter!=(Constant::bossBullet).end();iter++)
	{
		if(i<count)//如果i小于子节点数，说明还有精灵未用，不必新建。
		{
			Sprite *sprite=(Sprite*)(tempSBN->getChildByTag(i));
			sprite->setPosition(Point(*(++iter),HEIGHT-*(++iter)));
			sprite->setRotation(*(++iter));
		}else
		{
			Sprite *sprite2=Sprite::createWithTexture(tempSBN->getTexture());//创建新精灵
			sprite2->setPosition(Point(*(++iter),HEIGHT-*(++iter)));
			sprite2->setRotation(*(++iter));
			tempSBN->addChild(sprite2,i,i);
		}
		i++;
	}
	while(i<count)
	{
		tempSBN->removeChildByTag(i,true);
		i++;
	}
}

void GameLayer::setMapTank()
{
	std::vector<int>::iterator iter = (Constant::mapTank).begin();
	int i=0;
	int iTank1=0;
	int iTank2=0;
	int iTank3=0;
	int iTank4=0;
	int iMark=0;
	int count=0;
	int countTank1=this->getChildByTag(TAG_TANK_1)->getChildrenCount();
	int countTank2=this->getChildByTag(TAG_TANK_2)->getChildrenCount();
	int countTank3=this->getChildByTag(TAG_TANK_3)->getChildrenCount();
	int countTank4=this->getChildByTag(TAG_TANK_4)->getChildrenCount();
	int countMark=this->getChildByTag(TAG_MARK)->getChildrenCount();
	SpriteBatchNode *tempSBN;
	SpriteBatchNode *tempSBNGun;
	for(;iter!=(Constant::mapTank).end();iter++)
	{
		int number=Constant::THING_TAG[*iter];
		if(number==6) //判断坦克编号
		{
			tempSBN=(SpriteBatchNode*)(this->getChildByTag(TAG_TANK_1));
			tempSBNGun=(SpriteBatchNode*)(this->getChildByTag(TAG_TANK_GUN1));
			i=iTank1;
			iTank1++;
			count=countTank1;
		}
		else if(number==7)
		{
			tempSBN=(SpriteBatchNode*)(this->getChildByTag(TAG_TANK_2));
			tempSBNGun=(SpriteBatchNode*)(this->getChildByTag(TAG_TANK_GUN2));
			i=iTank2;
			iTank2++;
			count=countTank2;
		}else if(number==8)
		{
			tempSBN=(SpriteBatchNode*)(this->getChildByTag(TAG_TANK_3));
			tempSBNGun=(SpriteBatchNode*)(this->getChildByTag(TAG_TANK_GUN3));
			i=iTank3;
			iTank3++;
			count=countTank3;
		}else if(number==9)
		{
			tempSBN=(SpriteBatchNode*)(this->getChildByTag(TAG_TANK_4));
			tempSBNGun=(SpriteBatchNode*)(this->getChildByTag(TAG_TANK_GUN4));
			i=iTank4;
			iTank4++;
			count=countTank4;
		}else
		{
			tempSBN=(SpriteBatchNode*)(this->getChildByTag(TAG_MARK));
			int xx=*(++iter);
			int yy=HEIGHT-*(++iter);
			++iter;
			if(iMark<countMark)//如果i小于子节点数，说明还有精灵未用，不必新建。
			{
				Sprite *sprite=(Sprite*)(tempSBN->getChildByTag(iMark));
				sprite->setPosition(Point(xx,yy));
			}else//创建新精灵
			{
				Sprite *sprite2=Sprite::createWithTexture(tempSBN->getTexture());//创建新精灵
				sprite2->setPosition(Point(xx,yy));
				tempSBN->addChild(sprite2,iMark,iMark);
			}
			iMark++;
			continue;
		}
		int x=*(++iter);
		int y=HEIGHT-*(++iter);
		int angle=*(++iter);
		int gunState=Constant::otherGunState;
		if(i<count)//如果i小于子节点数，说明还有精灵未用，不必新建。
		{
			Sprite *sprite=(Sprite*)(tempSBN->getChildByTag(i));
			sprite->setPosition(Point(x,y));
			Sprite *spriteGun=(Sprite*)(tempSBNGun->getChildByTag(i));
			spriteGun->setPosition(Point(x,y));
			spriteGun->setTextureRect(Rect(33*gunState,0,33,68));
			spriteGun->setRotation(angle);
		}else//创建新精灵
		{
			Sprite *sprite2=Sprite::createWithTexture(tempSBN->getTexture());//创建新精灵
			sprite2->setPosition(Point(x,y));
			Sprite *sprite2Gun=Sprite::createWithTexture(tempSBNGun->getTexture(),Rect(33*gunState,0,33,68));//创建新精灵
			sprite2Gun->setAnchorPoint(Point(0.53, 0.3));
			sprite2Gun->setPosition(Point(x,y));
			sprite2Gun->setRotation(angle);
			tempSBN->addChild(sprite2,i,i);
			tempSBNGun->addChild(sprite2Gun,i,i);
		}
	}
	while(iTank1<countTank1)
	{
		this->getChildByTag(TAG_TANK_1)->removeChildByTag(iTank1,true);
		this->getChildByTag(TAG_TANK_GUN1)->removeChildByTag(iTank1,true);
		iTank1++;
	}
	while(iTank2<countTank2)
	{
		this->getChildByTag(TAG_TANK_2)->removeChildByTag(iTank2,true);
		this->getChildByTag(TAG_TANK_GUN2)->removeChildByTag(iTank2,true);
		iTank2++;
	}
	while(iTank3<countTank3)
	{
		this->getChildByTag(TAG_TANK_3)->removeChildByTag(iTank3,true);
		this->getChildByTag(TAG_TANK_GUN3)->removeChildByTag(iTank3,true);
		iTank3++;
	}
	while(iTank4<countTank4)
	{
		this->getChildByTag(TAG_TANK_4)->removeChildByTag(iTank4,true);
		this->getChildByTag(TAG_TANK_GUN4)->removeChildByTag(iTank4,true);
		iTank4++;
	}
	while(iMark<countMark)
	{
		this->getChildByTag(TAG_MARK)->removeChildByTag(iMark,true);
		iMark++;
	}
}

void GameLayer::setMapData()
{
	std::vector<int>::iterator iter = (Constant::mapData).begin();
	int i=0;
	int iMarkS=0;
	int iMarkL=0;
	int iBarrier=0;
	int iTower=0;
	int count=0;
	int countMarkS=this->getChildByTag(TAG_MARK_SMALL)->getChildrenCount();
	int countMarkL=this->getChildByTag(TAG_MARK_LARGE)->getChildrenCount();
	int countBarrier=this->getChildByTag(TAG_BARRIER)->getChildrenCount();
	int countTower=this->getChildByTag(TAG_TOWER)->getChildrenCount();
	SpriteBatchNode *tempSBN;
	for(;iter!=(Constant::mapData).end();iter++)
	{
		int number=Constant::THING_TAG[*iter];;
		if(number==2) //判断奖励编号
		{
			tempSBN=(SpriteBatchNode*)(this->getChildByTag(TAG_MARK_SMALL));
			i=iMarkS;
			iMarkS++;
			count=countMarkS;
		}
		else if(number==3)
		{
			tempSBN=(SpriteBatchNode*)(this->getChildByTag(TAG_MARK_LARGE));
			i=iMarkL;
			iMarkL++;
			count=countMarkL;
		}else if(number==4)
		{
			tempSBN=(SpriteBatchNode*)(this->getChildByTag(TAG_BARRIER));
			i=iBarrier;
			iBarrier++;
			count=countBarrier;
		}else if(number==5)
		{
			tempSBN=(SpriteBatchNode*)(this->getChildByTag(TAG_TOWER));
			i=iTower;
			iTower++;
			count=countTower;
		}
		if(i<count)//如果i小于子节点数，说明还有精灵未用，不必新建。
		{
			Sprite *sprite=(Sprite*)(tempSBN->getChildByTag(i));
			sprite->setPosition(Point(*(++iter),HEIGHT-*(++iter)));
		}else
		{
			Sprite *sprite2=Sprite::createWithTexture(tempSBN->getTexture());//创建新精灵
			sprite2->setPosition(Point(*(++iter),HEIGHT-*(++iter)));
			tempSBN->addChild(sprite2,i,i);
		}
	}
	while(iMarkS<countMarkS)
	{
		this->getChildByTag(TAG_MARK_SMALL)->removeChildByTag(iMarkS,true);
		iMarkS++;
	}
	while(iMarkL<countMarkL)
	{
		this->getChildByTag(TAG_MARK_LARGE)->removeChildByTag(iMarkL,true);
		iMarkL++;
	}
	while(iBarrier<countBarrier)
	{
		this->getChildByTag(TAG_BARRIER)->removeChildByTag(iBarrier,true);
		iBarrier++;
	}
	while(iTower<countTower)
	{
		this->getChildByTag(TAG_TOWER)->removeChildByTag(iTower,true);
		iTower++;
	}
}

void GameLayer::setAward()
{
	std::vector<int>::iterator iter = (Constant::award).begin();
	int i=0;
	int iP=0;
	int iH=0;
	int iC=0;
	int count=0;
	int countP=this->getChildByTag(TAG_PROPS_P)->getChildrenCount();
	int countH=this->getChildByTag(TAG_PROPS_H)->getChildrenCount();
	int countC=this->getChildByTag(TAG_PROPS_C)->getChildrenCount();
	SpriteBatchNode *tempSBN;
	for(;iter!=(Constant::award).end();iter++)
	{
		int number=*iter;
		if(number==14) //判断奖励编号
		{
			tempSBN=(SpriteBatchNode*)(this->getChildByTag(TAG_PROPS_P));
			i=iP;
			iP++;
			count=countP;
		}
		else if(number==13)
		{
			tempSBN=(SpriteBatchNode*)(this->getChildByTag(TAG_PROPS_H));
			i=iH;
			iH++;
			count=countH;
		}else if(number==12)
		{
			tempSBN=(SpriteBatchNode*)(this->getChildByTag(TAG_PROPS_C));
			i=iC;
			iC++;
			count=countC;
		}
		if(i<count)//如果i小于子节点数，说明还有精灵未用，不必新建。
		{
			Sprite *sprite=(Sprite*)(tempSBN->getChildByTag(i));
			sprite->setPosition(Point(*(++iter),HEIGHT-*(++iter)));
		}else
		{
			Sprite *sprite2=Sprite::createWithTexture(tempSBN->getTexture());//创建新精灵
			sprite2->setPosition(Point(*(++iter),HEIGHT-*(++iter)));
			tempSBN->addChild(sprite2,i,i);
		}
	}
	while(iP<countP)
	{
		this->getChildByTag(TAG_PROPS_P)->removeChildByTag(iP,true);
		iP++;
	}
	while(iH<countH)
	{
		this->getChildByTag(TAG_PROPS_H)->removeChildByTag(iH,true);
		iH++;
	}
	while(iC<countC)
	{
		this->getChildByTag(TAG_PROPS_C)->removeChildByTag(iC,true);
		iC++;
	}
}

void GameLayer::setMapTree()
{
	std::vector<int>::iterator iter = (Constant::mapTree).begin();
	int i=0;
	int iLight=0;
	int iDark=0;
	int count=0;
	int countLight=this->getChildByTag(TAG_TREE_LIGHT)->getChildrenCount();
	int countDark=this->getChildByTag(TAG_TREE_DARK)->getChildrenCount();
	SpriteBatchNode *tempSBN;
	for(;iter!=(Constant::mapTree).end();iter++)
	{
		int number=*iter;
		if(number==1)//判断子弹编号
		{
			tempSBN=(SpriteBatchNode*)(this->getChildByTag(TAG_TREE_LIGHT));
			i=iLight;
			iLight++;
			count=countLight;
		}else
		{
			tempSBN=(SpriteBatchNode*)(this->getChildByTag(TAG_TREE_DARK));
			i=iDark;
			iDark++;
			count=countDark;
		}
		if(i<count)//如果i小于子节点数，说明还有精灵未用，不必新建。
		{
			Sprite *sprite=(Sprite*)(tempSBN->getChildByTag(i));
			sprite->setPosition(Point(*(++iter),HEIGHT-*(++iter)));
		}else
		{
			Sprite *sprite2=Sprite::createWithTexture(tempSBN->getTexture());//创建新精灵
			sprite2->setPosition(Point(*(++iter),HEIGHT-*(++iter)));
			tempSBN->addChild(sprite2,i,i);
		}
	}
	while(iLight<countLight)
	{
		this->getChildByTag(TAG_TREE_LIGHT)->removeChildByTag(iLight,true);
		iLight++;
	}
	while(iDark<countDark)
	{
		this->getChildByTag(TAG_TREE_DARK)->removeChildByTag(iDark,true);
		iDark++;
	}
}

void GameLayer::setOtherBullet()
{
	std::vector<float>::iterator iter = (Constant::otherBullet).begin();
	int i=0;
	int iLarge=0;
	int iSmall=0;
	int count=0;
	int countLarge=this->getChildByTag(TAG_TANK_MISSILE)->getChildrenCount();
	int countSmall=this->getChildByTag(TAG_TANK_BULLET)->getChildrenCount();
	SpriteBatchNode *tempSBN;
	for(;iter!=(Constant::otherBullet).end();iter++)
	{
		int number=*iter;
		if(number==1)//判断子弹编号
		{
			tempSBN=(SpriteBatchNode*)(this->getChildByTag(TAG_TANK_MISSILE));
			i=iLarge;
			iLarge++;
			count=countLarge;
		}else
		{
			tempSBN=(SpriteBatchNode*)(this->getChildByTag(TAG_TANK_BULLET));
			i=iSmall;
			iSmall++;
			count=countSmall;
		}
		if(i<count)//如果i小于子节点数，说明还有精灵未用，不必新建。
		{
			Sprite *sprite=(Sprite*)(tempSBN->getChildByTag(i));
			sprite->setPosition(Point(*(++iter),HEIGHT-*(++iter)));
			sprite->setRotation(*(++iter));
		}else
		{
			Sprite *sprite2=Sprite::createWithTexture(tempSBN->getTexture());//创建新精灵
			sprite2->setPosition(Point(*(++iter),HEIGHT-*(++iter)));
			sprite2->setRotation(*(++iter));
			tempSBN->addChild(sprite2,i,i);
		}
	}
	while(iLarge<countLarge)
	{
		this->getChildByTag(TAG_TANK_MISSILE)->removeChildByTag(iLarge,true);
		iLarge++;
	}
	while(iSmall<countSmall)
	{
		this->getChildByTag(TAG_TANK_BULLET)->removeChildByTag(iSmall,true);
		iSmall++;
	}
}

void GameLayer::setMainMissile()
{
	std::vector<float>::iterator iter = (Constant::mainMissile).begin();
	SpriteBatchNode *tempSBN=(SpriteBatchNode*)(this->getChildByTag(TAG_MAIN_MISSILE));
	int i=0;
	int count=tempSBN->getChildrenCount();
	for(;iter!=(Constant::mainMissile).end();iter++)
	{
		if(i<count)//如果i小于子节点数，说明还有精灵未用，不必新建。
		{
			Sprite *sprite=(Sprite*)(tempSBN->getChildByTag(i));
			sprite->setPosition(Point(*iter,HEIGHT-*(++iter)));
			sprite->setRotation(*(++iter));
		}else
		{
			Sprite *sprite2=Sprite::createWithTexture(tempSBN->getTexture());//创建新精灵
			sprite2->setPosition(Point(*iter,HEIGHT-*(++iter)));
			sprite2->setRotation(*(++iter));
			tempSBN->addChild(sprite2,i,i);
		}
		i++;
	}
	while(i<count)
	{
		tempSBN->removeChildByTag(i,true);
		i++;
	}
}

void GameLayer::setMainBullet()
{
	std::vector<float>::iterator iter = (Constant::mainBullet).begin();
	SpriteBatchNode *tempSBN=(SpriteBatchNode*)(this->getChildByTag(TAG_MAIN_BULLET));
	int i=0;
	int count=tempSBN->getChildrenCount();
	for(;iter!=(Constant::mainBullet).end();iter++)
	{
		if(i<count)//如果i小于子节点数，说明还有精灵未用，不必新建。
		{
			Sprite *sprite=(Sprite*)(tempSBN->getChildByTag(i));
			sprite->setPosition(Point(*iter,HEIGHT-*(++iter)));
		}else
		{
			Sprite *sprite2=Sprite::createWithTexture(tempSBN->getTexture());//创建新精灵
			sprite2->setPosition(Point(*iter,HEIGHT-*(++iter)));
			tempSBN->addChild(sprite2,i,i);
		}
		i++;
	}
	while(i<count)
	{
		tempSBN->removeChildByTag(i,true);
		i++;
	}
}

void GameLayer::setExplosion()
{
	std::vector<int>::iterator iter = (Constant::explosion).begin();
	int i=0;
	int iLarge=0;
	int iSmall=0;
	int count=0;
	int countLarge=this->getChildByTag(TAG_LARGEEXPLOSION)->getChildrenCount();
	int countSmall=this->getChildByTag(TAG_SMALLEXPLOSION)->getChildrenCount();
	SpriteBatchNode *tempSBN;
	for(;iter!=(Constant::explosion).end();iter++)
	{
		int number=*iter;
		int d;
		if(number<25)//判断爆炸是大爆炸还是小爆炸
		{
			tempSBN=(SpriteBatchNode*)(this->getChildByTag(TAG_LARGEEXPLOSION));
			d=64;
			i=iLarge;
			iLarge++;
			count=countLarge;
		}else
		{
			tempSBN=(SpriteBatchNode*)(this->getChildByTag(TAG_SMALLEXPLOSION));
			number=number-25;
			d=32;
			i=iSmall;
			iSmall++;
			count=countSmall;
		}
		if(i<count)//如果i小于子节点数，说明还有精灵未用，不必新建。
		{
			Sprite *sprite=(Sprite*)(tempSBN->getChildByTag(i));
			sprite->setTextureRect(Rect((number%5)*d,(number/5)*d,d,d));
			sprite->setPosition(Point(*(++iter),HEIGHT-*(++iter)));
		}else
		{
			Sprite *sprite2=Sprite::createWithTexture(tempSBN->getTexture());//创建新精灵
			sprite2->setTextureRect(Rect((number%5)*d,(number/5)*d,d,d));//重新设置图片剪裁框
			sprite2->setPosition(Point(*(++iter),HEIGHT-*(++iter)));
			tempSBN->addChild(sprite2,i,i);
		}
	}
	while(iLarge<countLarge)
	{
		this->getChildByTag(TAG_LARGEEXPLOSION)->removeChildByTag(iLarge,true);
		iLarge++;
	}
	while(iSmall<countSmall)
	{
		this->getChildByTag(TAG_SMALLEXPLOSION)->removeChildByTag(iSmall,true);
		iSmall++;
	}
}

void GameLayer::moveTank(int redX, int redY, float redAngle, int greenX, int greenY, float greenAngle)
{
	//移动和旋转精灵主体 红色坦克
	redTank->setPosition(Point(redX,HEIGHT-redY));
	redTankGun->setPosition(Point(redX,HEIGHT-redY));
	redTank->setRotation(redAngle);

	greenTank->setPosition(Point(greenX,HEIGHT-greenY));
	greenTankGun->setPosition(Point(greenX,HEIGHT-greenY));
	greenTank->setRotation(greenAngle);
}

void GameLayer::rotateGun(float redAngle, float greenAngle)
{
	//旋转炮筒
	redTankGun->setRotation(redAngle);
	redTankGun->setTextureRect(Rect(33*Constant::redGunState,0,33,68));
	greenTankGun->setRotation(greenAngle);
	greenTankGun->setTextureRect(Rect(33*Constant::greenGunState,0,33,68));
}

void GameLayer::initTank()
{
	//创建精灵
	redTank=Sprite::create(PIC_PATH+std::string("mainbodyr.png"));
	redTank->setScale(1.1f);
	redTank->setPosition(Point(0,0));
	this->addChild(redTank,LAYER_REDTANK);

	redTankGun=Sprite::create(PIC_PATH+std::string("maingun.png"),Rect(0,0,33,68));
	redTankGun->setScale(1.1f);
	redTankGun->setAnchorPoint(Point(0.53, 0.3));
	redTankGun->setPosition(Point(0,0));
	this->addChild(redTankGun,LAYER_REDTANKGUN);

	greenTank=Sprite::create(PIC_PATH+std::string("mainbodyg.png"));
	greenTank->setScale(1.1f);
	greenTank->setPosition(Point(0,0));
	this->addChild(greenTank,LAYER_GREENTANK);

	greenTankGun=Sprite::create(PIC_PATH+std::string("maingun.png"),Rect(0,0,33,68));
	greenTankGun->setScale(1.1f);
	greenTankGun->setAnchorPoint(Point(0.53, 0.3));
	greenTankGun->setPosition(Point(0,0));
	this->addChild(greenTankGun,LAYER_GREENTANKGUN);
}

void GameLayer::initBatchNode()
{
	initOneBatchNode((PIC_PATH+std::string("tree1.png")).c_str(), LAYER_TREE_DARK, TAG_TREE_DARK);
	initOneBatchNode((PIC_PATH+std::string("tree2.png")).c_str(), LAYER_TREE_LIGHT, TAG_TREE_LIGHT);
	initOneBatchNode((PIC_PATH+std::string("mark1.png")).c_str(), LAYER_MARK_SMALL, TAG_MARK_SMALL);
	initOneBatchNode((PIC_PATH+std::string("mark1.png")).c_str(), LAYER_MARK, TAG_MARK);
	initOneBatchNode((PIC_PATH+std::string("mark2.png")).c_str(), LAYER_MARK_LARGE, TAG_MARK_LARGE);
	initOneBatchNode((PIC_PATH+std::string("barrier.png")).c_str(), LAYER_BARRIER, TAG_BARRIER);
	initOneBatchNode((PIC_PATH+std::string("tower.png")).c_str(), LAYER_TOWER, TAG_TOWER);
	initOneBatchNode((PIC_PATH+std::string("enemybody1.png")).c_str(), LAYER_TANK_1, TAG_TANK_1);
	initOneBatchNode((PIC_PATH+std::string("enemybody2.png")).c_str(), LAYER_TANK_2, TAG_TANK_2);
	initOneBatchNode((PIC_PATH+std::string("enemybody3.png")).c_str(), LAYER_TANK_3, TAG_TANK_3);
	initOneBatchNode((PIC_PATH+std::string("enemybody4.png")).c_str(), LAYER_TANK_4, TAG_TANK_4);
	initOneBatchNode((PIC_PATH+std::string("boss1bullet.png")).c_str(), LAYER_BOSS_FIRST, TAG_BOSS_FIRST);
	initOneBatchNode((PIC_PATH+std::string("boss2bullet.png")).c_str(), LAYER_BOSS_SECOND, TAG_BOSS_SECOND);
	initOneBatchNode((PIC_PATH+std::string("tankBullet.png")).c_str(), LAYER_MAIN_BULLET, TAG_MAIN_BULLET);
	initOneBatchNode((PIC_PATH+std::string("tankBazooka.png")).c_str(), LAYER_MAIN_MISSILE, TAG_MAIN_MISSILE);
	initOneBatchNode((PIC_PATH+std::string("enemyBullet.png")).c_str(), LAYER_TANK_BULLET, TAG_TANK_BULLET);
	initOneBatchNode((PIC_PATH+std::string("enemyBazooka.png")).c_str(), LAYER_TANK_MISSILE, TAG_TANK_MISSILE);
	initOneBatchNode((PIC_PATH+std::string("propsC.png")).c_str(), LAYER_PROPS_C, TAG_PROPS_C);
	initOneBatchNode((PIC_PATH+std::string("propsH.png")).c_str(), LAYER_PROPS_H, TAG_PROPS_H);
	initOneBatchNode((PIC_PATH+std::string("propsP.png")).c_str(), LAYER_PROPS_P, TAG_PROPS_P);
	initOneBatchNode((PIC_PATH+std::string("explosion1.png")).c_str(), LAYER_LARGEEXPLOSION, TAG_LARGEEXPLOSION);
	initOneBatchNode((PIC_PATH+std::string("explosion2.png")).c_str(), LAYER_SMALLEXPLOSION, TAG_SMALLEXPLOSION);
	initOneBatchNode((PIC_PATH+std::string("enemygun1.png")).c_str(), LAYER_TANK_GUN1, TAG_TANK_GUN1);
	initOneBatchNode((PIC_PATH+std::string("enemygun2.png")).c_str(), LAYER_TANK_GUN2, TAG_TANK_GUN2);
	initOneBatchNode((PIC_PATH+std::string("enemygun3.png")).c_str(), LAYER_TANK_GUN3, TAG_TANK_GUN3);
	initOneBatchNode((PIC_PATH+std::string("enemygun4.png")).c_str(), LAYER_TANK_GUN4, TAG_TANK_GUN4);
}
//利用地址生成BatchNode
void GameLayer::initOneBatchNode(const char *path,int layer, int tag)
{
	SpriteBatchNode *sbn = SpriteBatchNode::create(path,500);
	sbn->setAnchorPoint(Point(0, 0));
	sbn->setPosition(Point(0, 0));
	this->addChild(sbn, layer, tag);
}
