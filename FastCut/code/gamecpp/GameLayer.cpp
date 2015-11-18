#include "GameLayer.h"
#include "../bnGeolibHelper/CalUtil.h"
#include "SimpleAudioEngine.h"
#include "../bnBox2DHelp/JointHelp.h"
#include "ChoiceLayer.h"
#include "AppConstant.h"
using namespace std;
using namespace cocos2d;

int GameLayer::escCount=0;
//实现GameLayer类中的init方法，初始化布景
bool GameLayer::init()
{
	//调用父类的初始化
    if ( !Layer::init() )
    {
        return false;
    }
    
    //获取可见区域尺寸
    visibleSize = Director::getInstance()->getVisibleSize();
    //获取可见区域原点坐标
    origin = Director::getInstance()->getVisibleOrigin();

    //创建暂停菜单项
    auto zantingItem = MenuItemImage::create
    (
    		pic_PATH+"zanting_a.png",	//平时的图片
    		pic_PATH+"zanting_b.png",	//选中时的图片
		   CC_CALLBACK_1(GameLayer::menuZantingCallback, this) //点击时执行的回调方法
	);
    //设置暂停菜单项的位置
    zantingItem->setPosition
	(
		Point
		(
			origin.x + zantingItem->getContentSize().width/2 + 55,	//X坐标
            origin.y + zantingItem->getContentSize().height/2 + 170	//Y坐标
        )
    );

	//创建菜单对象
    menu = Menu::create(zantingItem, NULL);
    menu->setScale(1.2);//设置菜单对象的缩放比
    //设置菜单位置
    menu->setPosition(Point::ZERO);
    //将菜单添加到布景中
    this->addChild(menu, 1);

    return true;
}

//void GameLayer::recordTime()
//{
//	//开启定时回调，记录游戏所用时间*************************************
//	auto director = Director::getInstance();
//	auto sched = director->getScheduler();
//	sched->scheduleSelector(SEL_SCHEDULE(&GameLayer::gameTimeUpdate),this,1,false);
//	//***********************************************
//}

//开始触控事件的处理方法
bool GameLayer::onMyTouchBegan(Touch *touch, Event *event)
{
	if(touchID!=-1&&touchID!=touch->getID())
	{
		return true;
	}

	lxs=touch->getLocation().x;
	lys=touch->getLocation().y;
	touchS=touch->getLocation();//获取触控点的位置

	lineSp = Sprite::create(pic_PATH+"line.png");
	lineSp->setPosition(-540,-960);
	this->addChild(lineSp,2);
	touchID=touch->getID();//获取当前触摸id

	return true;
}

//触控移动事件的处理方法
void GameLayer::onMyTouchMoved(Touch *touch, Event *event)
{
	if(touchID!=touch->getID())
	{
		return;
	}
	touchE=touch->getLocation();//获取触控点的位置

	int nums = bpoCurrMain->pointData.size();//点数
	float* temp = new float[nums*2];
	int itemp=0;
	std::vector<Point>::iterator iter=bpoCurrMain->pointData.begin();
	for(;iter!=bpoCurrMain->pointData.end();iter++)
	{
		temp[itemp]=(*iter).x;
		itemp++;
		temp[itemp]=(*iter).y;
		itemp++;
	}

	IsNotCut* inc = new IsNotCut(lxs,lys,touchE.x,touchE.y,temp,itemp);

	if(isWin==false&&isZanting==false)
	{
		addLine(touchS, touchE,lineSp);


	}

	t = Point(touch->getLocation().x,touch->getLocation().y);//当前触摸位置坐标
	//更新刚体状态
	//遍历
	std::map<std::string,PhyObject*>::iterator iter1=pomCircle.begin();
	for(;iter1!=pomCircle.end();iter1++)
	{
		PhyObject* po=iter1->second;

		Point position(po->body->GetPosition().x*pixToMeter+visibleSize.width/2,po->body->GetPosition().y*pixToMeter+visibleSize.height/2);
		float length = t.getDistance(position);//当前触摸的位置与球的位置之间的距离
		float lengthPointLine=lengthPointToLine(po->body->GetPosition().x*pixToMeter+visibleSize.width/2,po->body->GetPosition().y*pixToMeter+visibleSize.height/2,lxs,lys,touch->getLocation().x,touch->getLocation().y);//球刚体到切割线之间的距离
		if((length <=mfcd->radius&&isWin==false&&anmiPlayEnd==false&&isZanting==false)||(lengthPointLine<=mfcd->radius&&cutLine==true&&isZanting==false&&isWin==false))//po->body->sp->getContentSize().height/2
		{
			restartGame();//重新开始本关卡游戏
			return;
		}
	}
	if(mfcd->levelNum==3)
	{
		round3SparkAnmi();//第3关播放火花动画
	}else if(mfcd->levelNum==4)
	{
		round4SparkAnmi();//第4关播放火花动画
	}else if(mfcd->levelNum==5)
	{
		round5SparkAnmi();//第5关播放火花动画
	}else if(mfcd->levelNum==6)
	{
		round6SparkAnmi();//第6关播放火花动画
	}
}

//触控结束事件的处理方法
void GameLayer::onMyTouchEnded(Touch *touch, Event *event)
{
	if(touchID!=touch->getID())
	{
		return;
	}
	touchID=-1;
//	if(lxs!=touch->getLocation().x&&lys!=touch->getLocation().y)
//	{
		//终点坐标
		lxe=touch->getLocation().x;
		lye=touch->getLocation().y;

		int nums = bpoCurrMain->pointData.size();//点数
		float* temp = new float[nums*2];
		int itemp=0;
		std::vector<Point>::iterator iter=bpoCurrMain->pointData.begin();
		for(;iter!=bpoCurrMain->pointData.end();iter++)
		{
			temp[itemp]=(*iter).x;
			itemp++;
			temp[itemp]=(*iter).y;
			itemp++;
		}

		IsNotCut* inc = new IsNotCut(lxs,lys,lxe,lye,temp,itemp);
		if(!IsNotCut::canCut||isWin==true||isCutFe==true||isZanting==true)//不符合切的要求、已经胜利、切到保护边、处于暂停状态
		{
			isDelete=false;//刚体边不能删除
			lineSp->runAction(RemoveSelf::create(true));
			return;
		}

		trueCut(lxs,lys,lxe,lye,inc);//打补丁后的正确切割的方法

		if(isBlink==true)
		{
			if(!ChoiceLayer::isSound)
			{
				wl->pauseSound();//停止播放音效
			}else
			{
				playNotCutSound();//播放未切割音效
			}
			lineSp->runAction(Sequence::create(
					Blink::create(0.5f, 2),
					RemoveSelf::create(true),
					NULL
					));
			isBlink=false;
		}else{
			lineSp->runAction(RemoveSelf::create(true));
		}

		//获取剩下的面积
		areaCurr=(float)(bpoCurrMain->cp->GetAreaSigned());
		if(areaCurr<0)
		{
			areaCurr=-areaCurr;
		}
		if(mfcd->levelNum==5||mfcd->levelNum==6)
		{
			popBuff();//关于铁buff弹出和消失的方法
		}

		//计算百分比
		pers=areaCurr*100/areaInit;
		std::string s = StringUtils::format("%d%%", pers);
		labelLast->setString(s);
		if(mfcd->levelNum==1)
		{
			winArea=ROUND_1AREA;
		}else if(mfcd->levelNum==2)
		{
			winArea=ROUND_2AREA;
		}else if(mfcd->levelNum==3)
		{
			winArea=ROUND_3AREA;
		}else if(mfcd->levelNum==4)
		{
			winArea=ROUND_4AREA;
		}else if(mfcd->levelNum==5)
		{
			winArea=ROUND_5AREA;
		}else if(mfcd->levelNum==6)
		{
			winArea=ROUND_6AREA;
		}
		if(pers<=winArea)
		{
			isWin=true;
			if(!ChoiceLayer::isSound)
			{
				wl->pauseSound();//停止播放音效
			}else
			{
				playsuccMusic();//播放过关音效
			}
			phyZanTing=true;

			popWinBoard();//弹出胜利木板的方法
			recordMessage();//过关记录牌显示信息
		}
//	}
}

//暂停菜单回调方法
void GameLayer::menuZantingCallback(Object* pSender)
{
	if(isZanting==false&&isWin==false)//当前不是暂停状态且未过关***********************
	{
		if(ChoiceLayer::isSound)//声音开*********************************
		{
			wl->playClickSound();
		}
		//创建一个精灵对象，包含toumingBg.png图片
		toumingBgSp=Sprite::create(pic_PATH+"toumingBg.png");
		//设置精灵对象的位置
		toumingBgSp->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
		//将精灵添加到背景中
		this->addChild(toumingBgSp, 2);
		zantingSp = Sprite::create(pic_PATH+"suspend_bg.png");//创建暂停后弹出的精灵
		zantingSp->setScale(0.6);//设置精灵缩放比
		zantingSp->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y+20));//设置精灵位置
		this->addChild(zantingSp,3);//将精灵添加到背景精灵中

		auto guanQiaItem = MenuItemImage::create
		(
				pic_PATH+"guanQia_a.png",	//平时的图片
				pic_PATH+"guanQia_b.png",	//选中时的图片
			   CC_CALLBACK_1(GameLayer::guanQia, this) //点击时执行的回调方法
		);
		//设置关卡菜单项的位置
		guanQiaItem->setPosition
		(
			Point
			(
				origin.x + 120,//X坐标
				origin.y + 210	//Y坐标
			)
		);

		//创建关卡菜单对象
		auto menuGuanQia = Menu::create(guanQiaItem, NULL);
		menuGuanQia->setScale(1.2f);
		//设置菜单位置
		menuGuanQia->setPosition(Point::ZERO);
		//将菜单添加到布景中
		zantingSp->addChild(menuGuanQia, 2);

		auto chongWanItem = MenuItemImage::create//创建重来菜单
		(
				pic_PATH+"chongWan_a.png",	//平时的图片
				pic_PATH+"chongWan_b.png",	//选中时的图片
			   CC_CALLBACK_1(GameLayer::chongWan, this) //点击时执行的回调方法
		);
		//设置重来菜单项的位置
		chongWanItem->setPosition
		(
			Point
			(
				origin.x + 225,//X坐标
				origin.y + 210	//Y坐标
			)
		);

		//创建重来菜单对象
		auto menuchongWan = Menu::create(chongWanItem, NULL);
		menuchongWan->setScale(1.2f);
		//设置菜单位置
		menuchongWan->setPosition(Point::ZERO);
		//将菜单添加到布景中
		zantingSp->addChild(menuchongWan, 2);

		auto jixuItem = MenuItemImage::create
		(
				pic_PATH+"resume_a.png",	//平时的图片
				pic_PATH+"resume_b.png",	//选中时的图片
			   CC_CALLBACK_1(GameLayer::jiXu, this) //点击时执行的回调方法
		);
		//设置继续菜单项的位置
		jixuItem->setPosition
		(
			Point
			(
				origin.x + 330,//X坐标
				origin.y + 210	//Y坐标
			)
		);

		//创建继续菜单对象
		auto menuJiXu = Menu::create(jixuItem, NULL);
		menuJiXu->setScale(1.2f);
		//设置菜单位置
		menuJiXu->setPosition(Point::ZERO);
		//将菜单添加到布景中
		zantingSp->addChild(menuJiXu, 2);
		zantingSp->runAction(Spawn::create(//创建一个同步执行动作对象并将其执行
					ScaleBy::create(0.6f,1.67,2),//创建一个缩放动作对象
					RotateBy::create(0.6f,-360),//创建一个旋转动作对象
					//RotateTo::create(0.5f,180),
								NULL));
		isZanTingEnble=false;//暂停菜单不可用

	}else{
		isZanting=false;
		phyZanTing=false;
		isZanTingEnble=true;//暂停菜单可用
	}
	if((isZanting==true&&phyZanTing==true&&isZanTingEnble==false)||isWin==true)//暂停状态或者胜利过关*******************************************
	{
		menu->setEnabled(false);//暂停菜单不可用
	}else{
		menu->setEnabled(true);//暂停菜单可用
	}
	isZanting=true;
	phyZanTing=true;

}
//进行物理模拟
void GameLayer::step()
{
	//时间步进
	float32 timeStep = 2.0f / 60.0f;
	//速度迭代次数
	int32 velocityIterations = 6;
	//位置迭代次数
	int32 positionIterations = 2;
	//执行物理模拟
	world->Step(timeStep,velocityIterations,positionIterations);
}

void GameLayer::update(float delta)
{
//	recordTime();//记录时间的方法
	if(isZanting==true)
	{
		time=time;
	}else if(isZanting==false)
	{
		time++;
	}

	if(phyZanTing==true)
	{
		return;
	}

	if(isDelete)
	{
		if(!ChoiceLayer::isSound)
		{
			wl->pauseSound();//停止播放音效
		}else
		{
			playcutSound();//播放切割音效
		}

		deleteEdge();
		++cutNum;//切割次数增加

		int nums = bpoCurrMain->pointData.size();//点数
		float* temp = new float[nums*2];
		int itemp=0;
		std::vector<Point>::iterator iter=bpoCurrMain->pointData.begin();
		for(;iter!=bpoCurrMain->pointData.end();iter++)
		{
			temp[itemp]=(*iter).x;
			itemp++;
			temp[itemp]=(*iter).y;
			itemp++;
		}
		createEdge(temp, nums*2);

		isDelete = false;
	}

	//进行物理模拟
	step();
	//更新刚体状态
	std::map<std::string,PhyObject*>::iterator iter;
	//遍历
	for(iter=pom.begin();iter!=pom.end();iter++)
	{
		PhyObject* po=iter->second;
		po->refresh();
	}
}

void GameLayer::deleteEdge()
{
	std::vector<std::string> listForDel;
	std::map<std::string,PhyObject*>::iterator iter;
	//遍历
	for(iter=pom.begin();iter!=pom.end();iter++)
	{
		PhyObject* po=iter->second;
		if(po->poId->at(0)=='E')
		{
			listForDel.push_back(*po->poId);
		}
	}
	std::vector<std::string>::iterator il;
	for(il=listForDel.begin();il!=listForDel.end();il++)
	{
		PhyObject* po=pom[*il];								//拿到物体类对象指针
		world->DestroyBody(po->body);						//在物理世界中删除刚体
		pom.erase(*il);										//删掉物理类对象的指针
		this->removeChild(po->dSp);							//在布景里删除精灵
		delete po;											//删除物体类对象指针
	}
	listForDel.clear();//列表清空
}

void GameLayer::createEdge(float* coorData, int lengthCoorData)
{
	int j=0;
	int indexID=-1;//边索引

	for(int i=0;i<lengthCoorData/2;i++)
	{
		if(j==lengthCoorData-2)
		{
			if(coorData[j] == coorData[0] && coorData[j+1] == coorData[1])
			{
				j=j+2;
				continue;
			}
			else
			{
				data=new float[4]{coorData[j]-visibleSize.width/2,coorData[j+1]-visibleSize.height/2,coorData[0]-visibleSize.width/2,coorData[1]-visibleSize.height/2};
			}
		}
		else
		{
			if(coorData[j] == coorData[j+2] && coorData[j+1] == coorData[j+3])
			{
				j=j+2;
				continue;
			}
			else
			{
				data=new float[4]{coorData[j]-visibleSize.width/2,coorData[j+1]-visibleSize.height/2,coorData[j+2]-visibleSize.width/2,coorData[j+3]-visibleSize.height/2};
			}
		}
		ids=new std::string(StringUtils::format("E%d", ++indexID));//设置边刚体的id
		po = new EdgePhyObject(ids,true,this,world,pic_PATH+"violetCube.png",data,0,0,0);//创建线性物体类对象
		pom[*ids]=po;
		j=j+2;
	}
}

void GameLayer::preloadAllSound()
{
	//加载游戏胜利音效
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
		(sound_PATH+"gamesucc.mp3").c_str()
	);
	//加载游戏失败音效
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
		(sound_PATH+"gamefail.mp3").c_str()
	);
	//加载切割木板音效
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
		(sound_PATH+"cut.mp3").c_str()
	);
	//加载未切割木板音效
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
		(sound_PATH+"wave.mp3").c_str()
	);
	//加载切到金属边缘音效
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
		(sound_PATH+"peng.mp3").c_str()
	);
}
void GameLayer::playsuccMusic()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect((sound_PATH+"gamesucc.mp3").c_str());
}
void GameLayer::playfailMusic()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect((sound_PATH+"gamefail.mp3").c_str());
}
void GameLayer::playcutSound()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect((sound_PATH+"cut.mp3").c_str());
}
void GameLayer::playNotCutSound()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect((sound_PATH+"wave.mp3").c_str());
}
void GameLayer::playcutFeSound()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect((sound_PATH+"peng.mp3").c_str());
}
void GameLayer::trueCut(float lxs,float lys,float lxe,float lye,IsNotCut* inc)
{

	//更新刚体状态
	circlePoint.clear();
	//遍历球
	std::map<std::string,PhyObject*>::iterator iter1=pomCircle.begin();//声明迭代器
	for(;iter1!=pomCircle.end();iter1++)
	{
		PhyObject* po=iter1->second;
		//获取球的位置，并将其放在 circlePoint中
		circlePoint.push_back(Point(po->body->GetPosition().x*pixToMeter+visibleSize.width/2,po->body->GetPosition().y*pixToMeter+visibleSize.height/2));
	}

	//计算出两个切割用区域
	std::vector<C2DPolygon> qfy=CalUtil::calParts(lxs,lys,lxe,lye);

	//获取两个切割区域
	WDHelp* wdh1 = new WDHelp(qfy.at(0),bpoCurrMain);
	WDHelp* wdh2 = new WDHelp(qfy.at(1),bpoCurrMain);

	//保证wdh2是 多边形多的那边           wdh1是 多边形少的那边
	if(wdh1->numsAllCP!=1&&wdh2->numsAllCP==1)
	{
		WDHelp* temp = wdh1;
		wdh1 = wdh2;
		wdh2 = temp;
	}
	if(wdh1->numsAllCP==1&&wdh2->numsAllCP==1)//若切割的两部分都分别只是一个多边形
	{
		C2DPolygon cpTemp1(wdh1->pointCopy, false);//获取第一个多边形
		C2DPolygon cpTemp2(wdh2->pointCopy, false);//获取第二个多边形
		bool isContain1 = false;//标志位，为true表示第一个多边形中有球
		bool isContain2 = false;//标志位，为true表示第二个多边形中有球
		std::vector<Point>::iterator iterCP=circlePoint.begin();
		for(;iterCP!=circlePoint.end();iterCP++)//遍历球的位置
		{
			C2DPoint cpBall((*iterCP).x,(*iterCP).y);//获取球的位置
			if(cpTemp1.Contains(cpBall))//若第一个多边形中有球
			{
				isContain1 = true;
			}
			if(cpTemp2.Contains(cpBall))//若第二个多边形中有球
			{
				isContain2 = true;
			}
		}
		if(isContain1 == true && isContain2 == true)//若两个多边形都有球
		{
			isBlink=true;
			return;
		}
//		if(isContain1 == false && isContain2 == false)
//			return;
		if(isContain1 == true && isContain2 == false)//若第一个多边形中有球，第二个多边形中没有球
		{
			isBlink=false;
			bpoCurrMain->sp->setVisible(false);
			std::string  pics= pic_PATH+StringUtils::format("s_0%d.png", mfcd->levelNum);//图片的路径
			BNPolyObject* bpoTemp = new BNPolyObject(pics,&cpTemp2,this);//设置临时变量 bpoTemp
			bpoTemp->clipper->runAction(
					Sequence::create(
							MoveBy::create(3,Point(-1000*((1%2==0)?1:-1),-1000*((1%2==1)?1:-1))),
							RemoveSelf::create(true),
							NULL
			));
			BNPolyObject* bpoTemp1=new BNPolyObject(pics,&cpTemp1,this);//设置临时变量 bpoTemp1
			bpoCurrMain=bpoTemp1;//将bpoTemp1赋值为全局的 bpoCurrMain
			addCutLight();//添加切割刀光效果
		}
		if(isContain1 == false && isContain2 == true)//若第二个多边形中有球，第一个多边形中没有球
		{
			isBlink=false;
			bpoCurrMain->sp->setVisible(false);
			std::string  pics= pic_PATH+StringUtils::format("s_0%d.png", mfcd->levelNum);//图片的路径
			BNPolyObject* bpoTemp = new BNPolyObject(pics,&cpTemp1,this);//设置临时变量 bpoTemp
//			bpoTemp->clipper->runAction(MoveBy::create(3,Point(-1000*((1%2==0)?1:-1),-1000*((1%2==1)?1:-1))));
			bpoTemp->clipper->runAction(
					Sequence::create(
							MoveBy::create(3,Point(-1000*((1%2==0)?1:-1),-1000*((1%2==1)?1:-1))),
							RemoveSelf::create(true),
							NULL
			));
			BNPolyObject* bpoTemp1=new BNPolyObject(pics,&cpTemp2,this);//设置临时变量 bpoTemp1
			bpoCurrMain=bpoTemp1;//将bpoTemp1赋值为全局的 bpoCurrMain
			addCutLight();//添加切割刀光效果

		}
	}
	else
	{
		wdh2->Separate(inc, wdh1->pointCopy);
		C2DPolygon retainCP(wdh2->pointCopy,  false);//获取第二个多边形

		bool retainCPContain = false;
		std::vector<Point>::iterator iterCP=circlePoint.begin();
		for(;iterCP!=circlePoint.end();iterCP++)//遍历球的位置
		{
			C2DPoint cpBall((*iterCP).x,(*iterCP).y);//获取球的位置
			std::vector<C2DPolygon>::iterator iterFC  = (wdh2->flyCP).begin();
			for(; iterFC !=  (wdh2->flyCP).end(); iterFC++)//遍历wdh2中flyCP的Vector
			{
				if((*iterFC).Contains(cpBall))//判断球是否在多边形中
				{
					retainCPContain = true;
					break;
				}
			}
		}

		if(retainCPContain == false)//若wdh2中没有球
		{
			bpoCurrMain->sp->setVisible(false);//将精灵设为不可见
			std::vector<C2DPolygon>::iterator iter = (wdh2->flyCP).begin();
			for(; iter !=  (wdh2->flyCP).end(); iter++)//遍历wdh2中flyCP的Vector
			{
				std::string  pics= pic_PATH+StringUtils::format("s_0%d.png",mfcd-> levelNum);//图片的路径
				BNPolyObject* bpoTempF = new BNPolyObject(pics,&(*iter),this);//设置临时变量 bpoTemp
//				bpoTempF->clipper->runAction(MoveBy::create(3,Point(-1000*((1%2==0)?1:-1),-1000*((1%2==1)?1:-1))));
				bpoTempF->clipper->runAction(
						Sequence::create(
								MoveBy::create(3,Point(-1000*((1%2==0)?1:-1),-1000*((1%2==1)?1:-1))),
								RemoveSelf::create(true),
								NULL
				));
				addCutLight();//添加切割刀光效果

			}
			//若有球部分只有一块，可以干，就剩下这一块了
//				BNPolyObject* bpoTemp1=new BNPolyObject(pic_PATH+"s_01.png",&retainCP,this);
//				bpoCurrMain=bpoTemp1;
			std::string  pics= pic_PATH+StringUtils::format("s_0%d.png", mfcd->levelNum);//图片的路径
			bpoCurrMain=new BNPolyObject(pics,&retainCP,this);//给全局的 bpoCurrMain赋值
		}
	}

	isDelete=true;
}

void GameLayer::guanQia(Object* pSender)
{
	if(!ChoiceLayer::isSound)
	{
		wl->pauseSound();//停止播放音效
	}else
	{
		wl->playClickSound();//播放点击的音效
	}
	gsm->goLevelScene();//去选关场景
}

void GameLayer::chongWan(Object* pSender)
{
	if(!ChoiceLayer::isSound)
	{
		wl->pauseSound();
	}else
	{
		wl->playClickSound();//播放点击的音效
	}
	if(mfcd->levelNum==1)
	{
		gsm->reStart();
	}else if(mfcd->levelNum==2)
	{
		gsm->reStart2();
	}else if(mfcd->levelNum==3)
	{
		gsm->reStart3();
	}else if(mfcd->levelNum==4)
	{
		gsm->reStart4();
	}else if(mfcd->levelNum==5)
	{
		gsm->reStart5();
	}else if(mfcd->levelNum==6)
	{
		gsm->reStart6();
	}
}

void GameLayer::xiaYiGuan(Object* pSender)
{
	if(ChoiceLayer::isSound)
	{
		wl->playClickSound();//播放点击的音效
	}
	if(mfcd->levelNum==1)
	{
		gsm->goRound2Scene();
	}else if(mfcd->levelNum==2)
	{
		gsm->goRound3Scene();
	}else if(mfcd->levelNum==3)
	{
		gsm->goRound4Scene();
	}else if(mfcd->levelNum==4)
	{
		gsm->goRound5Scene();
	}else if(mfcd->levelNum==5)
	{
		gsm->goRound6Scene();
	}
}

void GameLayer::initAnmi()
{
	SpriteFrameCache* sfc=SpriteFrameCache::getInstance();//获取缓冲精灵帧的实例
	sfc->addSpriteFramesWithFile(pic_PATH+"spark.plist",pic_PATH+"spark.png");//将精灵帧文件以及对应的图片添加到内存中

	//动画12幅图片的名称
	std::string sa[12]=
	{
		"spark_1.png","spark_2.png",
		"spark_3.png","spark_4.png",
		"spark_5.png","spark_6.png",
		"spark_7.png","spark_8.png",
		"spark_9.png","spark_10.png",
		"spark_11.png","spark_12.png",
	};

	Vector<SpriteFrame*> animFrames;//创建存放动画帧的列表对象
	for(int i=0;i<12;i++)
	{
		animFrames.pushBack(sfc->getSpriteFrameByName(sa[i]));//将这一段动画中的一个帧存放到向量中
	}


	//创建动画对象，从帧向量产生动画，间隔为0.03秒
	Animation *anmi=Animation::createWithSpriteFrames(animFrames, 0.03f);
	//创建动画动作对象
	anmiAc=Animate::create(anmi);

	//因为暂时不用，保持引用，防止被自动释放
	anmiAc->retain();
}

void GameLayer::jiXu(Object* pSender)
{
	if(ChoiceLayer::isSound)
	{
		wl->playClickSound();//播放点击的音效
	}
	zantingSp->runAction(RemoveSelf::create(true));
	toumingBgSp->runAction(RemoveSelf::create(true));
	phyZanTing=false;
	isZanting=false;
	isZanTingEnble=true;
}
void GameLayer::initLevel(int levelNum)
{
	//创建一个包含"100%/"内容的文本标签
	labelLast=Label::createWithTTF("100%", fonts_PATH+"FZKATJW.ttf", 40);
	labelLast->setTextColor(Color4B::RED);
	//设置文本标签的位置
	labelLast->setPosition
	(
		Point
		(
			origin.x + 470,
			origin.y + visibleSize.height - labelLast->getContentSize().height
		)
	);
	//将文本标签添加到布景中
	this->addChild(labelLast, 1);

	//创建一个精灵对象，充当背景
	backgroundsp = Sprite::create(pic_PATH+"bg.jpg");
	 //设置精灵对象的位置
	backgroundsp->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	//将背景精灵添加到布景中
	this->addChild(backgroundsp, 0);

	//=============================
	//初始化物理世界
	//创建重力加速度向量
	b2Vec2 gravity(0.0f, 0.0f);
	//创建物理世界
	world = new b2World(gravity);
	//允许静止物体休眠
	world->SetAllowSleeping(true);

	new MyFCData(this,levelNum);

	MyContactListener* mcl=new MyContactListener();		//创建碰撞监听器
	world->SetContactListener(mcl);


	//获取原始面积
	areaInit=(float)(bpoCurrMain->cp->GetAreaSigned());
	if(areaInit<0)
	{
		areaInit=-areaInit;
	}
	preloadAllSound();//预加载各种音效
	//定时回调
	schedule(schedule_selector(GameLayer::update), 0.01f);

	//创建一个单点触摸监听
	auto listenerTouch = EventListenerTouchOneByOne::create();
	//设置下传触摸
	listenerTouch->setSwallowTouches(true);
	//开始触摸时回调onTouchBegan方法
	listenerTouch->onTouchBegan = CC_CALLBACK_2(GameLayer::onMyTouchBegan, this);
	//触摸移动时回调onTouchMoved方法
	listenerTouch->onTouchMoved = CC_CALLBACK_2(GameLayer::onMyTouchMoved, this);
	//触摸结束时回调onTouchEnded方法
	listenerTouch->onTouchEnded = CC_CALLBACK_2(GameLayer::onMyTouchEnded, this);
	//添加到监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTouch, this);

	wl->pauseBgMusic();//暂停播放背景音乐
//	recordTime();//记录时间的方法

}
//void GameLayer::gameTimeUpdate()
//{
//	if(isZanting==true)
//	{
//		time=time;
//	}else if(isZanting==false)
//	{
//		time++;
//	}
//}

void GameLayer::recordMessage()
{
	//过关后显示的信息如切割数等begin=============================================================
	timeLabel = Label::createWithCharMap(pic_PATH+"number.png",27,50, '0');
	//设置文本标签的位置
	timeLabel->setPosition
	(
		Point
		(
			origin.x + 265,
			origin.y + 365
		)
	);
	std::string sTime = StringUtils::format("%d", time/60);//设置显示切割数标签的值
	timeLabel->setString(sTime);
	//将文本标签添加到布景中
	winBgSp->addChild(timeLabel, 1);

	cutLabel = Label::createWithCharMap(pic_PATH+"number.png",27,50, '0');//创建切割数文本标签
	//设置文本标签的位置
	cutLabel->setPosition
	(
		Point
		(
			origin.x + 265,
			origin.y + 303
		)
	);
	std::string sCutNum = StringUtils::format("%d", cutNum);//设置显示切割数标签的值
	cutLabel->setString(sCutNum);
	//将文本标签添加到布景中
	winBgSp->addChild(cutLabel, 1);

	lastLabel = Label::createWithCharMap(pic_PATH+"number.png",27,50, '0');//创建显示剩余面积文本标签
	//设置文本标签的位置
	lastLabel->setPosition
	(
		Point
		(
			origin.x + 265,
			origin.y + 233
		)
	);
	std::string sPers = StringUtils::format("%d", pers);//设置显示剩余面积标签的值
	lastLabel->setString(sPers);
	//将文本标签添加到布景中
	winBgSp->addChild(lastLabel, 1);
	//过关后显示的信息如切割数等end=============================================================

}

void GameLayer::restartGame()
{
	if(!ChoiceLayer::isSound)
	{
		wl->pauseSound();
	}else
	{
		playfailMusic();//播放失败音效
	}
	if(mfcd->levelNum==1&&isZanting==false)
	{
		gsm->reStart();
	}else if(mfcd->levelNum==2&&isZanting==false)
	{
		gsm->reStart2();
	}
	else if(mfcd->levelNum==3&&isZanting==false)
	{
		gsm->reStart3();
	}else if(mfcd->levelNum==4&&isZanting==false)
	{
		gsm->reStart4();
	}else if(mfcd->levelNum==5&&isZanting==false)
	{
		gsm->reStart5();
	}else if(mfcd->levelNum==6&&isZanting==false)
	{
		gsm->reStart6();
	}
}

void GameLayer::addCutLight()
{
	if((lye>=lys&&lxe>=lxs)||(lye<=lys&&lxe<=lxs))//正向切(/////)的时候
	{
		angle=atan(fabs(lxe-lxs)/fabs(lye-lys))*Rad_to_deg;
	}else if((lye>=lys&&lxe<=lxs)||(lye<=lys&&lxe>=lxs))//反向切(\\\\\)的时候
	{
		angle=-atan(fabs(lxe-lxs)/fabs(lye-lys))*Rad_to_deg;
	}
	Point l(lxe-lxs,lye-lys);//
	l.getLength();//触摸起点到终点的长度
	float scaleLight=l.getLength()/Light_Length;//刀光的缩放比

	lightSp=Sprite::create(pic_PATH+"light.png");
//			lightSp->setAnchorPoint(Point(0,0));
	lightSp->setPosition(Point((lxs+lxe)/2,(lys+lye)/2));
	lightSp->setRotation(angle);
	lightSp->setScale(scaleLight);
	this->addChild(lightSp,2);
	lightSp->runAction(Sequence::create(
			DelayTime::create(0.1f),
			RemoveSelf::create(true),
			NULL
			));
}
void GameLayer::popWinBoard()
{
	if(mfcd->levelNum==6)
	{
		//创建一个精灵对象，包含toumingBg.png图片
		toumingBgSp=Sprite::create(pic_PATH+"toumingBg.png");
		//设置精灵对象的位置
		toumingBgSp->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
		//将精灵添加到背景中
		backgroundsp->addChild(toumingBgSp, 1);
		winBgSp = Sprite::create(pic_PATH+"bg.png");//创建胜利后弹出结果的精灵
		winBgSp->setScaleX(1.1);
		winBgSp->setScaleY(1.2);//设置缩放比
		winBgSp->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y+20));//设置精灵位置
		this->addChild(winBgSp,2);//将精灵添加到背景精灵中

		auto guanQiaItem = MenuItemImage::create
		(
				pic_PATH+"guanQia_a.png",	//平时的图片
				pic_PATH+"guanQia_b.png",	//选中时的图片
			   CC_CALLBACK_1(GameLayer::guanQia, this) //点击时执行的回调方法
		);
		//设置关卡菜单项的位置
		guanQiaItem->setPosition
		(
			Point
			(
				origin.x + 95,//X坐标
				origin.y + 120	//Y坐标
			)
		);

		//创建关卡菜单对象
		auto menuGuanQia = Menu::create(guanQiaItem, NULL);
		//设置菜单位置
		menuGuanQia->setPosition(Point::ZERO);
		//将菜单添加到布景中
		winBgSp->addChild(menuGuanQia, 2);

		auto chongWanItem = MenuItemImage::create
		(
				pic_PATH+"chongWan_a.png",	//平时的图片
				pic_PATH+"chongWan_b.png",	//选中时的图片
			   CC_CALLBACK_1(GameLayer::chongWan, this) //点击时执行的回调方法
		);
		//设置重来菜单项的位置
		chongWanItem->setPosition
		(
			Point
			(
				origin.x + 345,//X坐标
				origin.y + 120	//Y坐标
			)
		);

		//创建重来菜单对象
		auto menuchongWan = Menu::create(chongWanItem, NULL);
		//设置菜单位置
		menuchongWan->setPosition(Point::ZERO);
		//将菜单添加到布景中
		winBgSp->addChild(menuchongWan, 2);
	}else
	{
		//创建一个精灵对象，包含toumingBg.png图片
		toumingBgSp=Sprite::create(pic_PATH+"toumingBg.png");
		//设置精灵对象的位置
		toumingBgSp->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
		//将精灵添加到背景中
		backgroundsp->addChild(toumingBgSp, 1);
		winBgSp = Sprite::create(pic_PATH+"bg.png");//创建胜利后弹出结果的精灵
		winBgSp->setScaleX(1.1);
		winBgSp->setScaleY(1.2);//设置缩放比
		winBgSp->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y+20));//设置精灵位置
		this->addChild(winBgSp,2);//将精灵添加到背景精灵中

		auto guanQiaItem = MenuItemImage::create
		(
				pic_PATH+"guanQia_a.png",	//平时的图片
				pic_PATH+"guanQia_b.png",	//选中时的图片
			   CC_CALLBACK_1(GameLayer::guanQia, this) //点击时执行的回调方法
		);
		//设置关卡菜单项的位置
		guanQiaItem->setPosition
		(
			Point
			(
				origin.x + 95,//X坐标
				origin.y + 120	//Y坐标
			)
		);

		//创建关卡菜单对象
		auto menuGuanQia = Menu::create(guanQiaItem, NULL);
		//设置菜单位置
		menuGuanQia->setPosition(Point::ZERO);
		//将菜单添加到布景中
		winBgSp->addChild(menuGuanQia, 2);

		auto chongWanItem = MenuItemImage::create
		(
				pic_PATH+"chongWan_a.png",	//平时的图片
				pic_PATH+"chongWan_b.png",	//选中时的图片
			   CC_CALLBACK_1(GameLayer::chongWan, this) //点击时执行的回调方法
		);
		//设置重来菜单项的位置
		chongWanItem->setPosition
		(
			Point
			(
				origin.x + 220,//X坐标
				origin.y + 120	//Y坐标
			)
		);

		//创建重来菜单对象
		auto menuchongWan = Menu::create(chongWanItem, NULL);
		//设置菜单位置
		menuchongWan->setPosition(Point::ZERO);
		//将菜单添加到布景中
		winBgSp->addChild(menuchongWan, 2);

		auto xiaYiGuanItem = MenuItemImage::create
		(
				pic_PATH+"xiaYiGuan_a.png",	//平时的图片
				pic_PATH+"xiaYiGuan_b.png",	//选中时的图片
			   CC_CALLBACK_1(GameLayer::xiaYiGuan, this) //点击时执行的回调方法
		);
		//设置下一关菜单项的位置
		xiaYiGuanItem->setPosition
		(
			Point
			(
				origin.x + 345,//X坐标
				origin.y + 120	//Y坐标
			)
		);
		//创建下一关菜单对象
		auto menuXiaYiGuan = Menu::create(xiaYiGuanItem, NULL);
		//设置菜单位置
		menuXiaYiGuan->setPosition(Point::ZERO);
		//将菜单添加到布景中
		winBgSp->addChild(menuXiaYiGuan, 2);
	}
}
void GameLayer::popBuff()
{
	if(tempArea>areaCurr&&isBuff==true)
	{
		buffCutSp->runAction(Sequence::create(//创建一个连续执行动作对象
				Spawn::create(//创建一个同步执行动作对象并将其执行
						ScaleBy::create(1.0f,2.0f),
						MoveTo::create(0.5f,Point(450,700)),
						MoveTo::create(0.5f,Point(540,750)),
						NULL),
				RemoveSelf::create(true),
				NULL));
		isBuff=false;
	}
	if(cutNum==1)
	{
		tempArea=areaInit;
	}
	if((tempArea-areaCurr)/areaInit>=0.2)//一次切割面积不少于20%时奖励一个buff
	{
		buffCutSp = Sprite::create(pic_PATH+"tiebuff.png");
//				buffCutSp->setPosition(270,480);
		buffCutSp->setPosition(Point((lxs+lxe)/2,(lys+lye)/2));//设置铁buff初始位置
		buffCutSp->runAction(Spawn::create(//创建一个同步执行动作对象并将其执行
					ScaleBy::create(2.0f,0.5f),//创建一个缩放动作对象
					MoveTo::create(2.0f,Point(500,750)),//创建一个移动动作对象
								NULL));
		this->addChild(buffCutSp,2);
		isBuff=true;
	}else{
		isBuff=false;
	}
	tempArea=areaCurr;
}

void GameLayer::round3SparkAnmi()
{
	Sprite* sparkSp=Sprite::create();
	if(Point::isSegmentIntersect(Point(22,575),Point(141,450),Point(lxs,lys),t)&&bpoCurrMain->JudgeIsContian(Point(22,575),Point(141,450)))
	{
		if(anmiPlayEnd==true)//如果动画播放结束
		{
			return;
		}
		if(!ChoiceLayer::isSound)
		{
			wl->pauseSound();//停止播放音效
		}else{
			playcutFeSound();//播放切到金属的音效
		}
		isCutFe=true;
		sparkSp->setPosition(Point::getIntersectPoint(Point(22,575),Point(141,450),Point(lxs,lys),t));
		this->addChild(sparkSp,2);
		initAnmi();
		//开始播放动画
		sparkSp->runAction(Sequence::create(
				anmiAc,//播放火花动画
				RemoveSelf::create(true),//移除火花精灵
				NULL));
		lineSp->runAction(ToggleVisibility ::create());//切割线设置为不可见
		cutLine=false;//切割线不可见
//		lineSp->runAction(Blink::create(0.7f, 2));
		anmiPlayEnd=true;//动画播放结束
	}else if(Point::isSegmentIntersect(Point(116,262),Point(269,350),Point(lxs,lys),t)&&bpoCurrMain->JudgeIsContian(Point(116,262),Point(269,350)))
	{
		if(anmiPlayEnd==true)
		{
			return;
		}
		if(!ChoiceLayer::isSound)
		{
			wl->pauseSound();//停止播放音效
		}else{
			playcutFeSound();//播放切到金属的音效
		}
		isCutFe=true;
		sparkSp->setPosition(Point::getIntersectPoint(Point(116,262),Point(269,350),Point(lxs,lys),t));
		this->addChild(sparkSp,2);
		initAnmi();
		//开始播放动画
		sparkSp->runAction(Sequence::create(
				anmiAc,
				RemoveSelf::create(true),
				NULL));
		lineSp->runAction(ToggleVisibility ::create());//切割线设置为不可见
		cutLine=false;//切割线不可见
		anmiPlayEnd=true;//动画播放结束
	}else if(Point::isSegmentIntersect(Point(426,262),Point(396,448),Point(lxs,lys),t)&&bpoCurrMain->JudgeIsContian(Point(396,448),Point(426,262)))
	{
		if(anmiPlayEnd==true)
		{
			return;
		}
		if(!ChoiceLayer::isSound)
		{
			wl->pauseSound();//停止播放音效
		}else{
			playcutFeSound();//播放切到金属的音效
		}
		isCutFe=true;
		sparkSp->setPosition(Point::getIntersectPoint(Point(426,262),Point(396,448),Point(lxs,lys),t));
		this->addChild(sparkSp,2);
		initAnmi();
		//开始播放动画
		sparkSp->runAction(Sequence::create(
				anmiAc,
				RemoveSelf::create(true),
				NULL));
		lineSp->runAction(ToggleVisibility ::create());//切割线设置为不可见
		cutLine=false;//切割线不可见
		anmiPlayEnd=true;//动画播放结束
	}else{
		isCutFe=false;
		anmiPlayEnd=false;
		cutLine=true;//切割线可见
	}
}
void GameLayer::round4SparkAnmi()
{
	Sprite* sparkSp=Sprite::create();
	//如果与金属边有交点并且金属边没有被切走
	if(Point::isSegmentIntersect(Point(272,798),Point(59,707),Point(lxs,lys),t)&&bpoCurrMain->JudgeIsContian(Point(272,798),Point(59,707)))
	{
		if(anmiPlayEnd==true)
		{
			return;
		}
		if(!ChoiceLayer::isSound)
		{
			wl->pauseSound();//停止播放音效
		}else{
			playcutFeSound();//播放切到金属的音效
		}
		isCutFe=true;
		sparkSp->setPosition(Point::getIntersectPoint(Point(272,798),Point(59,707),Point(lxs,lys),t));
		this->addChild(sparkSp,2);
		initAnmi();
		//开始播放动画
		sparkSp->runAction(Sequence::create(
				anmiAc,
				RemoveSelf::create(true),
				NULL));
		lineSp->runAction(ToggleVisibility ::create());//切割线设置为不可见
		cutLine=false;//切割线不可见
		anmiPlayEnd=true;
	}else if(Point::isSegmentIntersect(Point(59,707),Point(59,526),Point(lxs,lys),t)&&bpoCurrMain->JudgeIsContian(Point(59,707),Point(59,526)))
	{
		if(anmiPlayEnd==true)
		{
			return;
		}
		if(!ChoiceLayer::isSound)
		{
			wl->pauseSound();//停止播放音效
		}else{
			playcutFeSound();//播放切到金属的音效
		}
		isCutFe=true;
		sparkSp->setPosition(Point::getIntersectPoint(Point(59,707),Point(59,526),Point(lxs,lys),t));
		this->addChild(sparkSp,2);
		initAnmi();
		//开始播放动画
		sparkSp->runAction(Sequence::create(
				anmiAc,
				RemoveSelf::create(true),
				NULL));
		lineSp->runAction(ToggleVisibility ::create());//切割线设置为不可见
		cutLine=false;//切割线不可见
		anmiPlayEnd=true;
	}else if(Point::isSegmentIntersect(Point(375,476),Point(483,427),Point(lxs,lys),t)&&bpoCurrMain->JudgeIsContian(Point(375,476),Point(483,427)))
	{
		if(anmiPlayEnd==true)
		{
			return;
		}
		if(!ChoiceLayer::isSound)
		{
			wl->pauseSound();//停止播放音效
		}else{
			playcutFeSound();//播放切到金属的音效
		}
		isCutFe=true;
		sparkSp->setPosition(Point::getIntersectPoint(Point(375,476),Point(483,427),Point(lxs,lys),t));
		this->addChild(sparkSp,2);
		initAnmi();
		//开始播放动画
		sparkSp->runAction(Sequence::create(
				anmiAc,
				RemoveSelf::create(true),
				NULL));
		lineSp->runAction(ToggleVisibility ::create());//切割线设置为不可见
		cutLine=false;//切割线不可见
		anmiPlayEnd=true;
	}else{
		isCutFe=false;
		anmiPlayEnd=false;
		cutLine=true;//切割线可见
	}
}
void GameLayer::round5SparkAnmi()
{
	Sprite* sparkSp=Sprite::create();
	if(isBuff==false&&Point::isSegmentIntersect(Point(271,772),Point(190,545),Point(lxs,lys),t)&&bpoCurrMain->JudgeIsContian(Point(271,772),Point(190,545)))
	{
		if(anmiPlayEnd==true)
		{
			return;
		}
		if(!ChoiceLayer::isSound)
		{
			wl->pauseSound();//停止播放音效
		}else{
			playcutFeSound();//播放切到金属的音效
		}
		isCutFe=true;
		sparkSp->setPosition(Point::getIntersectPoint(Point(271,772),Point(190,545),Point(lxs,lys),t));
		this->addChild(sparkSp,2);
		initAnmi();
		//开始播放动画
		sparkSp->runAction(Sequence::create(
				anmiAc,//播放火花动画
				RemoveSelf::create(true),//移除火花精灵
				NULL));
		lineSp->runAction(ToggleVisibility ::create());//切割线设置为不可见
		cutLine=false;//切割线不可见
		anmiPlayEnd=true;

	}else if(isBuff==false&&Point::isSegmentIntersect(Point(144,382),Point(52,258),Point(lxs,lys),t)&&bpoCurrMain->JudgeIsContian(Point(144,382),Point(52,258)))
	{
		if(anmiPlayEnd==true)
		{
			return;
		}
		if(!ChoiceLayer::isSound)
		{
			wl->pauseSound();//停止播放音效
		}else{
			playcutFeSound();//播放切到金属的音效
		}
		isCutFe=true;
		sparkSp->setPosition(Point::getIntersectPoint(Point(144,382),Point(52,258),Point(lxs,lys),t));
		this->addChild(sparkSp,2);
		initAnmi();
		//开始播放动画
		sparkSp->runAction(Sequence::create(
				anmiAc,
				RemoveSelf::create(true),
				NULL));
		lineSp->runAction(ToggleVisibility ::create());//切割线设置为不可见
		cutLine=false;//切割线不可见
		anmiPlayEnd=true;

	}else if(isBuff==false&&Point::isSegmentIntersect(Point(494,258),Point(397,382),Point(lxs,lys),t)&&bpoCurrMain->JudgeIsContian(Point(494,258),Point(397,382)))
	{
		if(anmiPlayEnd==true)
		{
			return;
		}
		if(!ChoiceLayer::isSound)
		{
			wl->pauseSound();//停止播放音效
		}else{
			playcutFeSound();//播放切到金属的音效
		}
		isCutFe=true;
		sparkSp->setPosition(Point::getIntersectPoint(Point(494,258),Point(397,382),Point(lxs,lys),t));
		this->addChild(sparkSp,2);
		initAnmi();
		//开始播放动画
		sparkSp->runAction(Sequence::create(
				anmiAc,
				RemoveSelf::create(true),
				NULL));
		lineSp->runAction(ToggleVisibility ::create());//切割线设置为不可见
		cutLine=false;//切割线不可见
		anmiPlayEnd=true;
	}else{
		isCutFe=false;
		anmiPlayEnd=false;
		cutLine=true;//切割线可见
	}
}
void GameLayer::round6SparkAnmi()
{
	Sprite* sparkSp=Sprite::create();
	if(isBuff==false&&Point::isSegmentIntersect(Point(146,412),Point(47,293),Point(lxs,lys),t)&&bpoCurrMain->JudgeIsContian(Point(146,412),Point(47,293)))
	{
		if(anmiPlayEnd==true)
		{
			return;
		}
		if(!ChoiceLayer::isSound)
		{
			wl->pauseSound();//停止播放音效
		}else{
			playcutFeSound();//播放切到金属的音效
		}
		isCutFe=true;
		sparkSp->setPosition(Point::getIntersectPoint(Point(146,412),Point(47,293),Point(lxs,lys),t));
		this->addChild(sparkSp,2);
		initAnmi();
		//开始播放动画
		sparkSp->runAction(Sequence::create(
				anmiAc,//播放火花动画
				RemoveSelf::create(true),//移除火花精灵
				NULL));
		lineSp->runAction(ToggleVisibility ::create());//切割线设置为不可见
		cutLine=false;//切割线不可见
		anmiPlayEnd=true;
	}else if(isBuff==false&&Point::isSegmentIntersect(Point(47,293),Point(151,170),Point(lxs,lys),t)&&bpoCurrMain->JudgeIsContian(Point(47,293),Point(151,170)))
	{
		if(anmiPlayEnd==true)
		{
			return;
		}
		if(!ChoiceLayer::isSound)
		{
			wl->pauseSound();//停止播放音效
		}else{
			playcutFeSound();//播放切到金属的音效
		}
		isCutFe=true;
		sparkSp->setPosition(Point::getIntersectPoint(Point(47,293),Point(151,170),Point(lxs,lys),t));
		this->addChild(sparkSp,2);
		initAnmi();
		//开始播放动画
		sparkSp->runAction(Sequence::create(
				anmiAc,
				RemoveSelf::create(true),
				NULL));
		lineSp->runAction(ToggleVisibility ::create());//切割线设置为不可见
		cutLine=false;//切割线不可见
		anmiPlayEnd=true;
	}else if(isBuff==false&&Point::isSegmentIntersect(Point(400,536),Point(500,658),Point(lxs,lys),t)&&bpoCurrMain->JudgeIsContian(Point(400,536),Point(500,658)))
	{
		if(anmiPlayEnd==true)
		{
			return;
		}
		if(!ChoiceLayer::isSound)
		{
			wl->pauseSound();//停止播放音效
		}else{
			playcutFeSound();//播放切到金属的音效
		}
		isCutFe=true;
		sparkSp->setPosition(Point::getIntersectPoint(Point(400,536),Point(500,658),Point(lxs,lys),t));
		this->addChild(sparkSp,2);
		initAnmi();
		//开始播放动画
		sparkSp->runAction(Sequence::create(
				anmiAc,
				RemoveSelf::create(true),
				NULL));
		lineSp->runAction(ToggleVisibility ::create());//切割线设置为不可见
		cutLine=false;//切割线不可见
		anmiPlayEnd=true;
	}else if(isBuff==false&&Point::isSegmentIntersect(Point(500,658),Point(400,778),Point(lxs,lys),t)&&bpoCurrMain->JudgeIsContian(Point(500,658),Point(400,778)))
	{
		if(anmiPlayEnd==true)
		{
			return;
		}
		if(!ChoiceLayer::isSound)
		{
			wl->pauseSound();//停止播放音效
		}else{
			playcutFeSound();//播放切到金属的音效
		}
		isCutFe=true;
		sparkSp->setPosition(Point::getIntersectPoint(Point(500,658),Point(400,778),Point(lxs,lys),t));
		this->addChild(sparkSp,2);
		initAnmi();
		//开始播放动画
		sparkSp->runAction(Sequence::create(
				anmiAc,
				RemoveSelf::create(true),
				NULL));
		lineSp->runAction(ToggleVisibility ::create());//切割线设置为不可见
		cutLine=false;//切割线不可见
		anmiPlayEnd=true;
	}else{
		isCutFe=false;
		anmiPlayEnd=false;
		cutLine=true;//切割线可见
	}
}
float GameLayer::lengthPointToLine(float x,float y,float xs,float ys,float xm,float ym)
{
	float lengthpointToline;

//	float x;//球中心x坐标
//	float y;//球中心y坐标
	//球中心与开始触摸点的向量与球中心与触摸移动点的向量夹角和球中心与触摸移动点的向量与球中心与开始触摸点的向量夹角均为锐角
	if(((y-ys)*(ym-ys)+(x-xs)*(xm-xs)>0)&&((y-ym)*(ys-ym)+(x-xm)*(xs-xm)>0))
	{
		lengthpointToline=fabs(x*(ym-ys)-y*(xm-xs)-xs*(ym-ys)+ys*(xm-xs))/sqrt((ym-ys)*(ym-ys)+(xm-xs)*(xm-xs));

	}else{
		float length1=(x-xs)*(x-xs)+(y-ys)*(y-ys);
		float length2=(x-xm)*(x-xm)+(y-ym)*(y-ym);
		if(length1<=length2)
		{
			lengthpointToline=sqrt(length1);
		}else{
			lengthpointToline=sqrt(length2);
		}
	}

	return lengthpointToline;

}
void GameLayer::addLine(Point ps, Point pe,Sprite* edgeS)
{
	Point p3=ps-pe;
	//获取精灵的尺寸
	Size size=edgeS->getContentSize();
	//计算出精灵Y方向缩放比
	float scaleY=p3.getLength()/size.height;
	//设置精灵Y方向缩放比
	edgeS->setScaleY(scaleY);

	//设置精灵的位置
	edgeS->setPosition(Point((pe.x+ps.x)/2,(pe.y+ps.y)/2));
	edgeS->setRotation(-(std::atan2((ps.x-pe.x),(pe.y-ps.y)))*180/3.1415926);

}
