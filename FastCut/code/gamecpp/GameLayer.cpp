#include "GameLayer.h"
#include "../bnGeolibHelper/CalUtil.h"
#include "SimpleAudioEngine.h"
#include "../bnBox2DHelp/JointHelp.h"
#include "ChoiceLayer.h"
#include "AppConstant.h"
using namespace std;
using namespace cocos2d;

int GameLayer::escCount=0;
//ʵ��GameLayer���е�init��������ʼ������
bool GameLayer::init()
{
	//���ø���ĳ�ʼ��
    if ( !Layer::init() )
    {
        return false;
    }
    
    //��ȡ�ɼ�����ߴ�
    visibleSize = Director::getInstance()->getVisibleSize();
    //��ȡ�ɼ�����ԭ������
    origin = Director::getInstance()->getVisibleOrigin();

    //������ͣ�˵���
    auto zantingItem = MenuItemImage::create
    (
    		pic_PATH+"zanting_a.png",	//ƽʱ��ͼƬ
    		pic_PATH+"zanting_b.png",	//ѡ��ʱ��ͼƬ
		   CC_CALLBACK_1(GameLayer::menuZantingCallback, this) //���ʱִ�еĻص�����
	);
    //������ͣ�˵����λ��
    zantingItem->setPosition
	(
		Point
		(
			origin.x + zantingItem->getContentSize().width/2 + 55,	//X����
            origin.y + zantingItem->getContentSize().height/2 + 170	//Y����
        )
    );

	//�����˵�����
    menu = Menu::create(zantingItem, NULL);
    menu->setScale(1.2);//���ò˵���������ű�
    //���ò˵�λ��
    menu->setPosition(Point::ZERO);
    //���˵���ӵ�������
    this->addChild(menu, 1);

    return true;
}

//void GameLayer::recordTime()
//{
//	//������ʱ�ص�����¼��Ϸ����ʱ��*************************************
//	auto director = Director::getInstance();
//	auto sched = director->getScheduler();
//	sched->scheduleSelector(SEL_SCHEDULE(&GameLayer::gameTimeUpdate),this,1,false);
//	//***********************************************
//}

//��ʼ�����¼��Ĵ�����
bool GameLayer::onMyTouchBegan(Touch *touch, Event *event)
{
	if(touchID!=-1&&touchID!=touch->getID())
	{
		return true;
	}

	lxs=touch->getLocation().x;
	lys=touch->getLocation().y;
	touchS=touch->getLocation();//��ȡ���ص��λ��

	lineSp = Sprite::create(pic_PATH+"line.png");
	lineSp->setPosition(-540,-960);
	this->addChild(lineSp,2);
	touchID=touch->getID();//��ȡ��ǰ����id

	return true;
}

//�����ƶ��¼��Ĵ�����
void GameLayer::onMyTouchMoved(Touch *touch, Event *event)
{
	if(touchID!=touch->getID())
	{
		return;
	}
	touchE=touch->getLocation();//��ȡ���ص��λ��

	int nums = bpoCurrMain->pointData.size();//����
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

	t = Point(touch->getLocation().x,touch->getLocation().y);//��ǰ����λ������
	//���¸���״̬
	//����
	std::map<std::string,PhyObject*>::iterator iter1=pomCircle.begin();
	for(;iter1!=pomCircle.end();iter1++)
	{
		PhyObject* po=iter1->second;

		Point position(po->body->GetPosition().x*pixToMeter+visibleSize.width/2,po->body->GetPosition().y*pixToMeter+visibleSize.height/2);
		float length = t.getDistance(position);//��ǰ������λ�������λ��֮��ľ���
		float lengthPointLine=lengthPointToLine(po->body->GetPosition().x*pixToMeter+visibleSize.width/2,po->body->GetPosition().y*pixToMeter+visibleSize.height/2,lxs,lys,touch->getLocation().x,touch->getLocation().y);//����嵽�и���֮��ľ���
		if((length <=mfcd->radius&&isWin==false&&anmiPlayEnd==false&&isZanting==false)||(lengthPointLine<=mfcd->radius&&cutLine==true&&isZanting==false&&isWin==false))//po->body->sp->getContentSize().height/2
		{
			restartGame();//���¿�ʼ���ؿ���Ϸ
			return;
		}
	}
	if(mfcd->levelNum==3)
	{
		round3SparkAnmi();//��3�ز��Ż𻨶���
	}else if(mfcd->levelNum==4)
	{
		round4SparkAnmi();//��4�ز��Ż𻨶���
	}else if(mfcd->levelNum==5)
	{
		round5SparkAnmi();//��5�ز��Ż𻨶���
	}else if(mfcd->levelNum==6)
	{
		round6SparkAnmi();//��6�ز��Ż𻨶���
	}
}

//���ؽ����¼��Ĵ�����
void GameLayer::onMyTouchEnded(Touch *touch, Event *event)
{
	if(touchID!=touch->getID())
	{
		return;
	}
	touchID=-1;
//	if(lxs!=touch->getLocation().x&&lys!=touch->getLocation().y)
//	{
		//�յ�����
		lxe=touch->getLocation().x;
		lye=touch->getLocation().y;

		int nums = bpoCurrMain->pointData.size();//����
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
		if(!IsNotCut::canCut||isWin==true||isCutFe==true||isZanting==true)//�������е�Ҫ���Ѿ�ʤ�����е������ߡ�������ͣ״̬
		{
			isDelete=false;//����߲���ɾ��
			lineSp->runAction(RemoveSelf::create(true));
			return;
		}

		trueCut(lxs,lys,lxe,lye,inc);//�򲹶������ȷ�и�ķ���

		if(isBlink==true)
		{
			if(!ChoiceLayer::isSound)
			{
				wl->pauseSound();//ֹͣ������Ч
			}else
			{
				playNotCutSound();//����δ�и���Ч
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

		//��ȡʣ�µ����
		areaCurr=(float)(bpoCurrMain->cp->GetAreaSigned());
		if(areaCurr<0)
		{
			areaCurr=-areaCurr;
		}
		if(mfcd->levelNum==5||mfcd->levelNum==6)
		{
			popBuff();//������buff��������ʧ�ķ���
		}

		//����ٷֱ�
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
				wl->pauseSound();//ֹͣ������Ч
			}else
			{
				playsuccMusic();//���Ź�����Ч
			}
			phyZanTing=true;

			popWinBoard();//����ʤ��ľ��ķ���
			recordMessage();//���ؼ�¼����ʾ��Ϣ
		}
//	}
}

//��ͣ�˵��ص�����
void GameLayer::menuZantingCallback(Object* pSender)
{
	if(isZanting==false&&isWin==false)//��ǰ������ͣ״̬��δ����***********************
	{
		if(ChoiceLayer::isSound)//������*********************************
		{
			wl->playClickSound();
		}
		//����һ��������󣬰���toumingBg.pngͼƬ
		toumingBgSp=Sprite::create(pic_PATH+"toumingBg.png");
		//���þ�������λ��
		toumingBgSp->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
		//��������ӵ�������
		this->addChild(toumingBgSp, 2);
		zantingSp = Sprite::create(pic_PATH+"suspend_bg.png");//������ͣ�󵯳��ľ���
		zantingSp->setScale(0.6);//���þ������ű�
		zantingSp->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y+20));//���þ���λ��
		this->addChild(zantingSp,3);//��������ӵ�����������

		auto guanQiaItem = MenuItemImage::create
		(
				pic_PATH+"guanQia_a.png",	//ƽʱ��ͼƬ
				pic_PATH+"guanQia_b.png",	//ѡ��ʱ��ͼƬ
			   CC_CALLBACK_1(GameLayer::guanQia, this) //���ʱִ�еĻص�����
		);
		//���ùؿ��˵����λ��
		guanQiaItem->setPosition
		(
			Point
			(
				origin.x + 120,//X����
				origin.y + 210	//Y����
			)
		);

		//�����ؿ��˵�����
		auto menuGuanQia = Menu::create(guanQiaItem, NULL);
		menuGuanQia->setScale(1.2f);
		//���ò˵�λ��
		menuGuanQia->setPosition(Point::ZERO);
		//���˵���ӵ�������
		zantingSp->addChild(menuGuanQia, 2);

		auto chongWanItem = MenuItemImage::create//���������˵�
		(
				pic_PATH+"chongWan_a.png",	//ƽʱ��ͼƬ
				pic_PATH+"chongWan_b.png",	//ѡ��ʱ��ͼƬ
			   CC_CALLBACK_1(GameLayer::chongWan, this) //���ʱִ�еĻص�����
		);
		//���������˵����λ��
		chongWanItem->setPosition
		(
			Point
			(
				origin.x + 225,//X����
				origin.y + 210	//Y����
			)
		);

		//���������˵�����
		auto menuchongWan = Menu::create(chongWanItem, NULL);
		menuchongWan->setScale(1.2f);
		//���ò˵�λ��
		menuchongWan->setPosition(Point::ZERO);
		//���˵���ӵ�������
		zantingSp->addChild(menuchongWan, 2);

		auto jixuItem = MenuItemImage::create
		(
				pic_PATH+"resume_a.png",	//ƽʱ��ͼƬ
				pic_PATH+"resume_b.png",	//ѡ��ʱ��ͼƬ
			   CC_CALLBACK_1(GameLayer::jiXu, this) //���ʱִ�еĻص�����
		);
		//���ü����˵����λ��
		jixuItem->setPosition
		(
			Point
			(
				origin.x + 330,//X����
				origin.y + 210	//Y����
			)
		);

		//���������˵�����
		auto menuJiXu = Menu::create(jixuItem, NULL);
		menuJiXu->setScale(1.2f);
		//���ò˵�λ��
		menuJiXu->setPosition(Point::ZERO);
		//���˵���ӵ�������
		zantingSp->addChild(menuJiXu, 2);
		zantingSp->runAction(Spawn::create(//����һ��ͬ��ִ�ж������󲢽���ִ��
					ScaleBy::create(0.6f,1.67,2),//����һ�����Ŷ�������
					RotateBy::create(0.6f,-360),//����һ����ת��������
					//RotateTo::create(0.5f,180),
								NULL));
		isZanTingEnble=false;//��ͣ�˵�������

	}else{
		isZanting=false;
		phyZanTing=false;
		isZanTingEnble=true;//��ͣ�˵�����
	}
	if((isZanting==true&&phyZanTing==true&&isZanTingEnble==false)||isWin==true)//��ͣ״̬����ʤ������*******************************************
	{
		menu->setEnabled(false);//��ͣ�˵�������
	}else{
		menu->setEnabled(true);//��ͣ�˵�����
	}
	isZanting=true;
	phyZanTing=true;

}
//��������ģ��
void GameLayer::step()
{
	//ʱ�䲽��
	float32 timeStep = 2.0f / 60.0f;
	//�ٶȵ�������
	int32 velocityIterations = 6;
	//λ�õ�������
	int32 positionIterations = 2;
	//ִ������ģ��
	world->Step(timeStep,velocityIterations,positionIterations);
}

void GameLayer::update(float delta)
{
//	recordTime();//��¼ʱ��ķ���
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
			wl->pauseSound();//ֹͣ������Ч
		}else
		{
			playcutSound();//�����и���Ч
		}

		deleteEdge();
		++cutNum;//�и��������

		int nums = bpoCurrMain->pointData.size();//����
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

	//��������ģ��
	step();
	//���¸���״̬
	std::map<std::string,PhyObject*>::iterator iter;
	//����
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
	//����
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
		PhyObject* po=pom[*il];								//�õ����������ָ��
		world->DestroyBody(po->body);						//������������ɾ������
		pom.erase(*il);										//ɾ������������ָ��
		this->removeChild(po->dSp);							//�ڲ�����ɾ������
		delete po;											//ɾ�����������ָ��
	}
	listForDel.clear();//�б����
}

void GameLayer::createEdge(float* coorData, int lengthCoorData)
{
	int j=0;
	int indexID=-1;//������

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
		ids=new std::string(StringUtils::format("E%d", ++indexID));//���ñ߸����id
		po = new EdgePhyObject(ids,true,this,world,pic_PATH+"violetCube.png",data,0,0,0);//�����������������
		pom[*ids]=po;
		j=j+2;
	}
}

void GameLayer::preloadAllSound()
{
	//������Ϸʤ����Ч
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
		(sound_PATH+"gamesucc.mp3").c_str()
	);
	//������Ϸʧ����Ч
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
		(sound_PATH+"gamefail.mp3").c_str()
	);
	//�����и�ľ����Ч
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
		(sound_PATH+"cut.mp3").c_str()
	);
	//����δ�и�ľ����Ч
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
		(sound_PATH+"wave.mp3").c_str()
	);
	//�����е�������Ե��Ч
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

	//���¸���״̬
	circlePoint.clear();
	//������
	std::map<std::string,PhyObject*>::iterator iter1=pomCircle.begin();//����������
	for(;iter1!=pomCircle.end();iter1++)
	{
		PhyObject* po=iter1->second;
		//��ȡ���λ�ã���������� circlePoint��
		circlePoint.push_back(Point(po->body->GetPosition().x*pixToMeter+visibleSize.width/2,po->body->GetPosition().y*pixToMeter+visibleSize.height/2));
	}

	//����������и�������
	std::vector<C2DPolygon> qfy=CalUtil::calParts(lxs,lys,lxe,lye);

	//��ȡ�����и�����
	WDHelp* wdh1 = new WDHelp(qfy.at(0),bpoCurrMain);
	WDHelp* wdh2 = new WDHelp(qfy.at(1),bpoCurrMain);

	//��֤wdh2�� ����ζ���Ǳ�           wdh1�� ������ٵ��Ǳ�
	if(wdh1->numsAllCP!=1&&wdh2->numsAllCP==1)
	{
		WDHelp* temp = wdh1;
		wdh1 = wdh2;
		wdh2 = temp;
	}
	if(wdh1->numsAllCP==1&&wdh2->numsAllCP==1)//���и�������ֶ��ֱ�ֻ��һ�������
	{
		C2DPolygon cpTemp1(wdh1->pointCopy, false);//��ȡ��һ�������
		C2DPolygon cpTemp2(wdh2->pointCopy, false);//��ȡ�ڶ��������
		bool isContain1 = false;//��־λ��Ϊtrue��ʾ��һ�������������
		bool isContain2 = false;//��־λ��Ϊtrue��ʾ�ڶ��������������
		std::vector<Point>::iterator iterCP=circlePoint.begin();
		for(;iterCP!=circlePoint.end();iterCP++)//�������λ��
		{
			C2DPoint cpBall((*iterCP).x,(*iterCP).y);//��ȡ���λ��
			if(cpTemp1.Contains(cpBall))//����һ�������������
			{
				isContain1 = true;
			}
			if(cpTemp2.Contains(cpBall))//���ڶ��������������
			{
				isContain2 = true;
			}
		}
		if(isContain1 == true && isContain2 == true)//����������ζ�����
		{
			isBlink=true;
			return;
		}
//		if(isContain1 == false && isContain2 == false)
//			return;
		if(isContain1 == true && isContain2 == false)//����һ������������򣬵ڶ����������û����
		{
			isBlink=false;
			bpoCurrMain->sp->setVisible(false);
			std::string  pics= pic_PATH+StringUtils::format("s_0%d.png", mfcd->levelNum);//ͼƬ��·��
			BNPolyObject* bpoTemp = new BNPolyObject(pics,&cpTemp2,this);//������ʱ���� bpoTemp
			bpoTemp->clipper->runAction(
					Sequence::create(
							MoveBy::create(3,Point(-1000*((1%2==0)?1:-1),-1000*((1%2==1)?1:-1))),
							RemoveSelf::create(true),
							NULL
			));
			BNPolyObject* bpoTemp1=new BNPolyObject(pics,&cpTemp1,this);//������ʱ���� bpoTemp1
			bpoCurrMain=bpoTemp1;//��bpoTemp1��ֵΪȫ�ֵ� bpoCurrMain
			addCutLight();//����и��Ч��
		}
		if(isContain1 == false && isContain2 == true)//���ڶ�������������򣬵�һ���������û����
		{
			isBlink=false;
			bpoCurrMain->sp->setVisible(false);
			std::string  pics= pic_PATH+StringUtils::format("s_0%d.png", mfcd->levelNum);//ͼƬ��·��
			BNPolyObject* bpoTemp = new BNPolyObject(pics,&cpTemp1,this);//������ʱ���� bpoTemp
//			bpoTemp->clipper->runAction(MoveBy::create(3,Point(-1000*((1%2==0)?1:-1),-1000*((1%2==1)?1:-1))));
			bpoTemp->clipper->runAction(
					Sequence::create(
							MoveBy::create(3,Point(-1000*((1%2==0)?1:-1),-1000*((1%2==1)?1:-1))),
							RemoveSelf::create(true),
							NULL
			));
			BNPolyObject* bpoTemp1=new BNPolyObject(pics,&cpTemp2,this);//������ʱ���� bpoTemp1
			bpoCurrMain=bpoTemp1;//��bpoTemp1��ֵΪȫ�ֵ� bpoCurrMain
			addCutLight();//����и��Ч��

		}
	}
	else
	{
		wdh2->Separate(inc, wdh1->pointCopy);
		C2DPolygon retainCP(wdh2->pointCopy,  false);//��ȡ�ڶ��������

		bool retainCPContain = false;
		std::vector<Point>::iterator iterCP=circlePoint.begin();
		for(;iterCP!=circlePoint.end();iterCP++)//�������λ��
		{
			C2DPoint cpBall((*iterCP).x,(*iterCP).y);//��ȡ���λ��
			std::vector<C2DPolygon>::iterator iterFC  = (wdh2->flyCP).begin();
			for(; iterFC !=  (wdh2->flyCP).end(); iterFC++)//����wdh2��flyCP��Vector
			{
				if((*iterFC).Contains(cpBall))//�ж����Ƿ��ڶ������
				{
					retainCPContain = true;
					break;
				}
			}
		}

		if(retainCPContain == false)//��wdh2��û����
		{
			bpoCurrMain->sp->setVisible(false);//��������Ϊ���ɼ�
			std::vector<C2DPolygon>::iterator iter = (wdh2->flyCP).begin();
			for(; iter !=  (wdh2->flyCP).end(); iter++)//����wdh2��flyCP��Vector
			{
				std::string  pics= pic_PATH+StringUtils::format("s_0%d.png",mfcd-> levelNum);//ͼƬ��·��
				BNPolyObject* bpoTempF = new BNPolyObject(pics,&(*iter),this);//������ʱ���� bpoTemp
//				bpoTempF->clipper->runAction(MoveBy::create(3,Point(-1000*((1%2==0)?1:-1),-1000*((1%2==1)?1:-1))));
				bpoTempF->clipper->runAction(
						Sequence::create(
								MoveBy::create(3,Point(-1000*((1%2==0)?1:-1),-1000*((1%2==1)?1:-1))),
								RemoveSelf::create(true),
								NULL
				));
				addCutLight();//����и��Ч��

			}
			//�����򲿷�ֻ��һ�飬���Ըɣ���ʣ����һ����
//				BNPolyObject* bpoTemp1=new BNPolyObject(pic_PATH+"s_01.png",&retainCP,this);
//				bpoCurrMain=bpoTemp1;
			std::string  pics= pic_PATH+StringUtils::format("s_0%d.png", mfcd->levelNum);//ͼƬ��·��
			bpoCurrMain=new BNPolyObject(pics,&retainCP,this);//��ȫ�ֵ� bpoCurrMain��ֵ
		}
	}

	isDelete=true;
}

void GameLayer::guanQia(Object* pSender)
{
	if(!ChoiceLayer::isSound)
	{
		wl->pauseSound();//ֹͣ������Ч
	}else
	{
		wl->playClickSound();//���ŵ������Ч
	}
	gsm->goLevelScene();//ȥѡ�س���
}

void GameLayer::chongWan(Object* pSender)
{
	if(!ChoiceLayer::isSound)
	{
		wl->pauseSound();
	}else
	{
		wl->playClickSound();//���ŵ������Ч
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
		wl->playClickSound();//���ŵ������Ч
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
	SpriteFrameCache* sfc=SpriteFrameCache::getInstance();//��ȡ���徫��֡��ʵ��
	sfc->addSpriteFramesWithFile(pic_PATH+"spark.plist",pic_PATH+"spark.png");//������֡�ļ��Լ���Ӧ��ͼƬ��ӵ��ڴ���

	//����12��ͼƬ������
	std::string sa[12]=
	{
		"spark_1.png","spark_2.png",
		"spark_3.png","spark_4.png",
		"spark_5.png","spark_6.png",
		"spark_7.png","spark_8.png",
		"spark_9.png","spark_10.png",
		"spark_11.png","spark_12.png",
	};

	Vector<SpriteFrame*> animFrames;//������Ŷ���֡���б����
	for(int i=0;i<12;i++)
	{
		animFrames.pushBack(sfc->getSpriteFrameByName(sa[i]));//����һ�ζ����е�һ��֡��ŵ�������
	}


	//�����������󣬴�֡�����������������Ϊ0.03��
	Animation *anmi=Animation::createWithSpriteFrames(animFrames, 0.03f);
	//����������������
	anmiAc=Animate::create(anmi);

	//��Ϊ��ʱ���ã��������ã���ֹ���Զ��ͷ�
	anmiAc->retain();
}

void GameLayer::jiXu(Object* pSender)
{
	if(ChoiceLayer::isSound)
	{
		wl->playClickSound();//���ŵ������Ч
	}
	zantingSp->runAction(RemoveSelf::create(true));
	toumingBgSp->runAction(RemoveSelf::create(true));
	phyZanTing=false;
	isZanting=false;
	isZanTingEnble=true;
}
void GameLayer::initLevel(int levelNum)
{
	//����һ������"100%/"���ݵ��ı���ǩ
	labelLast=Label::createWithTTF("100%", fonts_PATH+"FZKATJW.ttf", 40);
	labelLast->setTextColor(Color4B::RED);
	//�����ı���ǩ��λ��
	labelLast->setPosition
	(
		Point
		(
			origin.x + 470,
			origin.y + visibleSize.height - labelLast->getContentSize().height
		)
	);
	//���ı���ǩ��ӵ�������
	this->addChild(labelLast, 1);

	//����һ��������󣬳䵱����
	backgroundsp = Sprite::create(pic_PATH+"bg.jpg");
	 //���þ�������λ��
	backgroundsp->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	//������������ӵ�������
	this->addChild(backgroundsp, 0);

	//=============================
	//��ʼ����������
	//�����������ٶ�����
	b2Vec2 gravity(0.0f, 0.0f);
	//������������
	world = new b2World(gravity);
	//����ֹ��������
	world->SetAllowSleeping(true);

	new MyFCData(this,levelNum);

	MyContactListener* mcl=new MyContactListener();		//������ײ������
	world->SetContactListener(mcl);


	//��ȡԭʼ���
	areaInit=(float)(bpoCurrMain->cp->GetAreaSigned());
	if(areaInit<0)
	{
		areaInit=-areaInit;
	}
	preloadAllSound();//Ԥ���ظ�����Ч
	//��ʱ�ص�
	schedule(schedule_selector(GameLayer::update), 0.01f);

	//����һ�����㴥������
	auto listenerTouch = EventListenerTouchOneByOne::create();
	//�����´�����
	listenerTouch->setSwallowTouches(true);
	//��ʼ����ʱ�ص�onTouchBegan����
	listenerTouch->onTouchBegan = CC_CALLBACK_2(GameLayer::onMyTouchBegan, this);
	//�����ƶ�ʱ�ص�onTouchMoved����
	listenerTouch->onTouchMoved = CC_CALLBACK_2(GameLayer::onMyTouchMoved, this);
	//��������ʱ�ص�onTouchEnded����
	listenerTouch->onTouchEnded = CC_CALLBACK_2(GameLayer::onMyTouchEnded, this);
	//��ӵ�������
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTouch, this);

	wl->pauseBgMusic();//��ͣ���ű�������
//	recordTime();//��¼ʱ��ķ���

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
	//���غ���ʾ����Ϣ���и�����begin=============================================================
	timeLabel = Label::createWithCharMap(pic_PATH+"number.png",27,50, '0');
	//�����ı���ǩ��λ��
	timeLabel->setPosition
	(
		Point
		(
			origin.x + 265,
			origin.y + 365
		)
	);
	std::string sTime = StringUtils::format("%d", time/60);//������ʾ�и�����ǩ��ֵ
	timeLabel->setString(sTime);
	//���ı���ǩ��ӵ�������
	winBgSp->addChild(timeLabel, 1);

	cutLabel = Label::createWithCharMap(pic_PATH+"number.png",27,50, '0');//�����и����ı���ǩ
	//�����ı���ǩ��λ��
	cutLabel->setPosition
	(
		Point
		(
			origin.x + 265,
			origin.y + 303
		)
	);
	std::string sCutNum = StringUtils::format("%d", cutNum);//������ʾ�и�����ǩ��ֵ
	cutLabel->setString(sCutNum);
	//���ı���ǩ��ӵ�������
	winBgSp->addChild(cutLabel, 1);

	lastLabel = Label::createWithCharMap(pic_PATH+"number.png",27,50, '0');//������ʾʣ������ı���ǩ
	//�����ı���ǩ��λ��
	lastLabel->setPosition
	(
		Point
		(
			origin.x + 265,
			origin.y + 233
		)
	);
	std::string sPers = StringUtils::format("%d", pers);//������ʾʣ�������ǩ��ֵ
	lastLabel->setString(sPers);
	//���ı���ǩ��ӵ�������
	winBgSp->addChild(lastLabel, 1);
	//���غ���ʾ����Ϣ���и�����end=============================================================

}

void GameLayer::restartGame()
{
	if(!ChoiceLayer::isSound)
	{
		wl->pauseSound();
	}else
	{
		playfailMusic();//����ʧ����Ч
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
	if((lye>=lys&&lxe>=lxs)||(lye<=lys&&lxe<=lxs))//������(/////)��ʱ��
	{
		angle=atan(fabs(lxe-lxs)/fabs(lye-lys))*Rad_to_deg;
	}else if((lye>=lys&&lxe<=lxs)||(lye<=lys&&lxe>=lxs))//������(\\\\\)��ʱ��
	{
		angle=-atan(fabs(lxe-lxs)/fabs(lye-lys))*Rad_to_deg;
	}
	Point l(lxe-lxs,lye-lys);//
	l.getLength();//������㵽�յ�ĳ���
	float scaleLight=l.getLength()/Light_Length;//��������ű�

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
		//����һ��������󣬰���toumingBg.pngͼƬ
		toumingBgSp=Sprite::create(pic_PATH+"toumingBg.png");
		//���þ�������λ��
		toumingBgSp->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
		//��������ӵ�������
		backgroundsp->addChild(toumingBgSp, 1);
		winBgSp = Sprite::create(pic_PATH+"bg.png");//����ʤ���󵯳�����ľ���
		winBgSp->setScaleX(1.1);
		winBgSp->setScaleY(1.2);//�������ű�
		winBgSp->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y+20));//���þ���λ��
		this->addChild(winBgSp,2);//��������ӵ�����������

		auto guanQiaItem = MenuItemImage::create
		(
				pic_PATH+"guanQia_a.png",	//ƽʱ��ͼƬ
				pic_PATH+"guanQia_b.png",	//ѡ��ʱ��ͼƬ
			   CC_CALLBACK_1(GameLayer::guanQia, this) //���ʱִ�еĻص�����
		);
		//���ùؿ��˵����λ��
		guanQiaItem->setPosition
		(
			Point
			(
				origin.x + 95,//X����
				origin.y + 120	//Y����
			)
		);

		//�����ؿ��˵�����
		auto menuGuanQia = Menu::create(guanQiaItem, NULL);
		//���ò˵�λ��
		menuGuanQia->setPosition(Point::ZERO);
		//���˵���ӵ�������
		winBgSp->addChild(menuGuanQia, 2);

		auto chongWanItem = MenuItemImage::create
		(
				pic_PATH+"chongWan_a.png",	//ƽʱ��ͼƬ
				pic_PATH+"chongWan_b.png",	//ѡ��ʱ��ͼƬ
			   CC_CALLBACK_1(GameLayer::chongWan, this) //���ʱִ�еĻص�����
		);
		//���������˵����λ��
		chongWanItem->setPosition
		(
			Point
			(
				origin.x + 345,//X����
				origin.y + 120	//Y����
			)
		);

		//���������˵�����
		auto menuchongWan = Menu::create(chongWanItem, NULL);
		//���ò˵�λ��
		menuchongWan->setPosition(Point::ZERO);
		//���˵���ӵ�������
		winBgSp->addChild(menuchongWan, 2);
	}else
	{
		//����һ��������󣬰���toumingBg.pngͼƬ
		toumingBgSp=Sprite::create(pic_PATH+"toumingBg.png");
		//���þ�������λ��
		toumingBgSp->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
		//��������ӵ�������
		backgroundsp->addChild(toumingBgSp, 1);
		winBgSp = Sprite::create(pic_PATH+"bg.png");//����ʤ���󵯳�����ľ���
		winBgSp->setScaleX(1.1);
		winBgSp->setScaleY(1.2);//�������ű�
		winBgSp->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y+20));//���þ���λ��
		this->addChild(winBgSp,2);//��������ӵ�����������

		auto guanQiaItem = MenuItemImage::create
		(
				pic_PATH+"guanQia_a.png",	//ƽʱ��ͼƬ
				pic_PATH+"guanQia_b.png",	//ѡ��ʱ��ͼƬ
			   CC_CALLBACK_1(GameLayer::guanQia, this) //���ʱִ�еĻص�����
		);
		//���ùؿ��˵����λ��
		guanQiaItem->setPosition
		(
			Point
			(
				origin.x + 95,//X����
				origin.y + 120	//Y����
			)
		);

		//�����ؿ��˵�����
		auto menuGuanQia = Menu::create(guanQiaItem, NULL);
		//���ò˵�λ��
		menuGuanQia->setPosition(Point::ZERO);
		//���˵���ӵ�������
		winBgSp->addChild(menuGuanQia, 2);

		auto chongWanItem = MenuItemImage::create
		(
				pic_PATH+"chongWan_a.png",	//ƽʱ��ͼƬ
				pic_PATH+"chongWan_b.png",	//ѡ��ʱ��ͼƬ
			   CC_CALLBACK_1(GameLayer::chongWan, this) //���ʱִ�еĻص�����
		);
		//���������˵����λ��
		chongWanItem->setPosition
		(
			Point
			(
				origin.x + 220,//X����
				origin.y + 120	//Y����
			)
		);

		//���������˵�����
		auto menuchongWan = Menu::create(chongWanItem, NULL);
		//���ò˵�λ��
		menuchongWan->setPosition(Point::ZERO);
		//���˵���ӵ�������
		winBgSp->addChild(menuchongWan, 2);

		auto xiaYiGuanItem = MenuItemImage::create
		(
				pic_PATH+"xiaYiGuan_a.png",	//ƽʱ��ͼƬ
				pic_PATH+"xiaYiGuan_b.png",	//ѡ��ʱ��ͼƬ
			   CC_CALLBACK_1(GameLayer::xiaYiGuan, this) //���ʱִ�еĻص�����
		);
		//������һ�ز˵����λ��
		xiaYiGuanItem->setPosition
		(
			Point
			(
				origin.x + 345,//X����
				origin.y + 120	//Y����
			)
		);
		//������һ�ز˵�����
		auto menuXiaYiGuan = Menu::create(xiaYiGuanItem, NULL);
		//���ò˵�λ��
		menuXiaYiGuan->setPosition(Point::ZERO);
		//���˵���ӵ�������
		winBgSp->addChild(menuXiaYiGuan, 2);
	}
}
void GameLayer::popBuff()
{
	if(tempArea>areaCurr&&isBuff==true)
	{
		buffCutSp->runAction(Sequence::create(//����һ������ִ�ж�������
				Spawn::create(//����һ��ͬ��ִ�ж������󲢽���ִ��
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
	if((tempArea-areaCurr)/areaInit>=0.2)//һ���и����������20%ʱ����һ��buff
	{
		buffCutSp = Sprite::create(pic_PATH+"tiebuff.png");
//				buffCutSp->setPosition(270,480);
		buffCutSp->setPosition(Point((lxs+lxe)/2,(lys+lye)/2));//������buff��ʼλ��
		buffCutSp->runAction(Spawn::create(//����һ��ͬ��ִ�ж������󲢽���ִ��
					ScaleBy::create(2.0f,0.5f),//����һ�����Ŷ�������
					MoveTo::create(2.0f,Point(500,750)),//����һ���ƶ���������
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
		if(anmiPlayEnd==true)//����������Ž���
		{
			return;
		}
		if(!ChoiceLayer::isSound)
		{
			wl->pauseSound();//ֹͣ������Ч
		}else{
			playcutFeSound();//�����е���������Ч
		}
		isCutFe=true;
		sparkSp->setPosition(Point::getIntersectPoint(Point(22,575),Point(141,450),Point(lxs,lys),t));
		this->addChild(sparkSp,2);
		initAnmi();
		//��ʼ���Ŷ���
		sparkSp->runAction(Sequence::create(
				anmiAc,//���Ż𻨶���
				RemoveSelf::create(true),//�Ƴ��𻨾���
				NULL));
		lineSp->runAction(ToggleVisibility ::create());//�и�������Ϊ���ɼ�
		cutLine=false;//�и��߲��ɼ�
//		lineSp->runAction(Blink::create(0.7f, 2));
		anmiPlayEnd=true;//�������Ž���
	}else if(Point::isSegmentIntersect(Point(116,262),Point(269,350),Point(lxs,lys),t)&&bpoCurrMain->JudgeIsContian(Point(116,262),Point(269,350)))
	{
		if(anmiPlayEnd==true)
		{
			return;
		}
		if(!ChoiceLayer::isSound)
		{
			wl->pauseSound();//ֹͣ������Ч
		}else{
			playcutFeSound();//�����е���������Ч
		}
		isCutFe=true;
		sparkSp->setPosition(Point::getIntersectPoint(Point(116,262),Point(269,350),Point(lxs,lys),t));
		this->addChild(sparkSp,2);
		initAnmi();
		//��ʼ���Ŷ���
		sparkSp->runAction(Sequence::create(
				anmiAc,
				RemoveSelf::create(true),
				NULL));
		lineSp->runAction(ToggleVisibility ::create());//�и�������Ϊ���ɼ�
		cutLine=false;//�и��߲��ɼ�
		anmiPlayEnd=true;//�������Ž���
	}else if(Point::isSegmentIntersect(Point(426,262),Point(396,448),Point(lxs,lys),t)&&bpoCurrMain->JudgeIsContian(Point(396,448),Point(426,262)))
	{
		if(anmiPlayEnd==true)
		{
			return;
		}
		if(!ChoiceLayer::isSound)
		{
			wl->pauseSound();//ֹͣ������Ч
		}else{
			playcutFeSound();//�����е���������Ч
		}
		isCutFe=true;
		sparkSp->setPosition(Point::getIntersectPoint(Point(426,262),Point(396,448),Point(lxs,lys),t));
		this->addChild(sparkSp,2);
		initAnmi();
		//��ʼ���Ŷ���
		sparkSp->runAction(Sequence::create(
				anmiAc,
				RemoveSelf::create(true),
				NULL));
		lineSp->runAction(ToggleVisibility ::create());//�и�������Ϊ���ɼ�
		cutLine=false;//�и��߲��ɼ�
		anmiPlayEnd=true;//�������Ž���
	}else{
		isCutFe=false;
		anmiPlayEnd=false;
		cutLine=true;//�и��߿ɼ�
	}
}
void GameLayer::round4SparkAnmi()
{
	Sprite* sparkSp=Sprite::create();
	//�����������н��㲢�ҽ�����û�б�����
	if(Point::isSegmentIntersect(Point(272,798),Point(59,707),Point(lxs,lys),t)&&bpoCurrMain->JudgeIsContian(Point(272,798),Point(59,707)))
	{
		if(anmiPlayEnd==true)
		{
			return;
		}
		if(!ChoiceLayer::isSound)
		{
			wl->pauseSound();//ֹͣ������Ч
		}else{
			playcutFeSound();//�����е���������Ч
		}
		isCutFe=true;
		sparkSp->setPosition(Point::getIntersectPoint(Point(272,798),Point(59,707),Point(lxs,lys),t));
		this->addChild(sparkSp,2);
		initAnmi();
		//��ʼ���Ŷ���
		sparkSp->runAction(Sequence::create(
				anmiAc,
				RemoveSelf::create(true),
				NULL));
		lineSp->runAction(ToggleVisibility ::create());//�и�������Ϊ���ɼ�
		cutLine=false;//�и��߲��ɼ�
		anmiPlayEnd=true;
	}else if(Point::isSegmentIntersect(Point(59,707),Point(59,526),Point(lxs,lys),t)&&bpoCurrMain->JudgeIsContian(Point(59,707),Point(59,526)))
	{
		if(anmiPlayEnd==true)
		{
			return;
		}
		if(!ChoiceLayer::isSound)
		{
			wl->pauseSound();//ֹͣ������Ч
		}else{
			playcutFeSound();//�����е���������Ч
		}
		isCutFe=true;
		sparkSp->setPosition(Point::getIntersectPoint(Point(59,707),Point(59,526),Point(lxs,lys),t));
		this->addChild(sparkSp,2);
		initAnmi();
		//��ʼ���Ŷ���
		sparkSp->runAction(Sequence::create(
				anmiAc,
				RemoveSelf::create(true),
				NULL));
		lineSp->runAction(ToggleVisibility ::create());//�и�������Ϊ���ɼ�
		cutLine=false;//�и��߲��ɼ�
		anmiPlayEnd=true;
	}else if(Point::isSegmentIntersect(Point(375,476),Point(483,427),Point(lxs,lys),t)&&bpoCurrMain->JudgeIsContian(Point(375,476),Point(483,427)))
	{
		if(anmiPlayEnd==true)
		{
			return;
		}
		if(!ChoiceLayer::isSound)
		{
			wl->pauseSound();//ֹͣ������Ч
		}else{
			playcutFeSound();//�����е���������Ч
		}
		isCutFe=true;
		sparkSp->setPosition(Point::getIntersectPoint(Point(375,476),Point(483,427),Point(lxs,lys),t));
		this->addChild(sparkSp,2);
		initAnmi();
		//��ʼ���Ŷ���
		sparkSp->runAction(Sequence::create(
				anmiAc,
				RemoveSelf::create(true),
				NULL));
		lineSp->runAction(ToggleVisibility ::create());//�и�������Ϊ���ɼ�
		cutLine=false;//�и��߲��ɼ�
		anmiPlayEnd=true;
	}else{
		isCutFe=false;
		anmiPlayEnd=false;
		cutLine=true;//�и��߿ɼ�
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
			wl->pauseSound();//ֹͣ������Ч
		}else{
			playcutFeSound();//�����е���������Ч
		}
		isCutFe=true;
		sparkSp->setPosition(Point::getIntersectPoint(Point(271,772),Point(190,545),Point(lxs,lys),t));
		this->addChild(sparkSp,2);
		initAnmi();
		//��ʼ���Ŷ���
		sparkSp->runAction(Sequence::create(
				anmiAc,//���Ż𻨶���
				RemoveSelf::create(true),//�Ƴ��𻨾���
				NULL));
		lineSp->runAction(ToggleVisibility ::create());//�и�������Ϊ���ɼ�
		cutLine=false;//�и��߲��ɼ�
		anmiPlayEnd=true;

	}else if(isBuff==false&&Point::isSegmentIntersect(Point(144,382),Point(52,258),Point(lxs,lys),t)&&bpoCurrMain->JudgeIsContian(Point(144,382),Point(52,258)))
	{
		if(anmiPlayEnd==true)
		{
			return;
		}
		if(!ChoiceLayer::isSound)
		{
			wl->pauseSound();//ֹͣ������Ч
		}else{
			playcutFeSound();//�����е���������Ч
		}
		isCutFe=true;
		sparkSp->setPosition(Point::getIntersectPoint(Point(144,382),Point(52,258),Point(lxs,lys),t));
		this->addChild(sparkSp,2);
		initAnmi();
		//��ʼ���Ŷ���
		sparkSp->runAction(Sequence::create(
				anmiAc,
				RemoveSelf::create(true),
				NULL));
		lineSp->runAction(ToggleVisibility ::create());//�и�������Ϊ���ɼ�
		cutLine=false;//�и��߲��ɼ�
		anmiPlayEnd=true;

	}else if(isBuff==false&&Point::isSegmentIntersect(Point(494,258),Point(397,382),Point(lxs,lys),t)&&bpoCurrMain->JudgeIsContian(Point(494,258),Point(397,382)))
	{
		if(anmiPlayEnd==true)
		{
			return;
		}
		if(!ChoiceLayer::isSound)
		{
			wl->pauseSound();//ֹͣ������Ч
		}else{
			playcutFeSound();//�����е���������Ч
		}
		isCutFe=true;
		sparkSp->setPosition(Point::getIntersectPoint(Point(494,258),Point(397,382),Point(lxs,lys),t));
		this->addChild(sparkSp,2);
		initAnmi();
		//��ʼ���Ŷ���
		sparkSp->runAction(Sequence::create(
				anmiAc,
				RemoveSelf::create(true),
				NULL));
		lineSp->runAction(ToggleVisibility ::create());//�и�������Ϊ���ɼ�
		cutLine=false;//�и��߲��ɼ�
		anmiPlayEnd=true;
	}else{
		isCutFe=false;
		anmiPlayEnd=false;
		cutLine=true;//�и��߿ɼ�
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
			wl->pauseSound();//ֹͣ������Ч
		}else{
			playcutFeSound();//�����е���������Ч
		}
		isCutFe=true;
		sparkSp->setPosition(Point::getIntersectPoint(Point(146,412),Point(47,293),Point(lxs,lys),t));
		this->addChild(sparkSp,2);
		initAnmi();
		//��ʼ���Ŷ���
		sparkSp->runAction(Sequence::create(
				anmiAc,//���Ż𻨶���
				RemoveSelf::create(true),//�Ƴ��𻨾���
				NULL));
		lineSp->runAction(ToggleVisibility ::create());//�и�������Ϊ���ɼ�
		cutLine=false;//�и��߲��ɼ�
		anmiPlayEnd=true;
	}else if(isBuff==false&&Point::isSegmentIntersect(Point(47,293),Point(151,170),Point(lxs,lys),t)&&bpoCurrMain->JudgeIsContian(Point(47,293),Point(151,170)))
	{
		if(anmiPlayEnd==true)
		{
			return;
		}
		if(!ChoiceLayer::isSound)
		{
			wl->pauseSound();//ֹͣ������Ч
		}else{
			playcutFeSound();//�����е���������Ч
		}
		isCutFe=true;
		sparkSp->setPosition(Point::getIntersectPoint(Point(47,293),Point(151,170),Point(lxs,lys),t));
		this->addChild(sparkSp,2);
		initAnmi();
		//��ʼ���Ŷ���
		sparkSp->runAction(Sequence::create(
				anmiAc,
				RemoveSelf::create(true),
				NULL));
		lineSp->runAction(ToggleVisibility ::create());//�и�������Ϊ���ɼ�
		cutLine=false;//�и��߲��ɼ�
		anmiPlayEnd=true;
	}else if(isBuff==false&&Point::isSegmentIntersect(Point(400,536),Point(500,658),Point(lxs,lys),t)&&bpoCurrMain->JudgeIsContian(Point(400,536),Point(500,658)))
	{
		if(anmiPlayEnd==true)
		{
			return;
		}
		if(!ChoiceLayer::isSound)
		{
			wl->pauseSound();//ֹͣ������Ч
		}else{
			playcutFeSound();//�����е���������Ч
		}
		isCutFe=true;
		sparkSp->setPosition(Point::getIntersectPoint(Point(400,536),Point(500,658),Point(lxs,lys),t));
		this->addChild(sparkSp,2);
		initAnmi();
		//��ʼ���Ŷ���
		sparkSp->runAction(Sequence::create(
				anmiAc,
				RemoveSelf::create(true),
				NULL));
		lineSp->runAction(ToggleVisibility ::create());//�и�������Ϊ���ɼ�
		cutLine=false;//�и��߲��ɼ�
		anmiPlayEnd=true;
	}else if(isBuff==false&&Point::isSegmentIntersect(Point(500,658),Point(400,778),Point(lxs,lys),t)&&bpoCurrMain->JudgeIsContian(Point(500,658),Point(400,778)))
	{
		if(anmiPlayEnd==true)
		{
			return;
		}
		if(!ChoiceLayer::isSound)
		{
			wl->pauseSound();//ֹͣ������Ч
		}else{
			playcutFeSound();//�����е���������Ч
		}
		isCutFe=true;
		sparkSp->setPosition(Point::getIntersectPoint(Point(500,658),Point(400,778),Point(lxs,lys),t));
		this->addChild(sparkSp,2);
		initAnmi();
		//��ʼ���Ŷ���
		sparkSp->runAction(Sequence::create(
				anmiAc,
				RemoveSelf::create(true),
				NULL));
		lineSp->runAction(ToggleVisibility ::create());//�и�������Ϊ���ɼ�
		cutLine=false;//�и��߲��ɼ�
		anmiPlayEnd=true;
	}else{
		isCutFe=false;
		anmiPlayEnd=false;
		cutLine=true;//�и��߿ɼ�
	}
}
float GameLayer::lengthPointToLine(float x,float y,float xs,float ys,float xm,float ym)
{
	float lengthpointToline;

//	float x;//������x����
//	float y;//������y����
	//�������뿪ʼ��������������������봥���ƶ���������нǺ��������봥���ƶ�����������������뿪ʼ������������нǾ�Ϊ���
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
	//��ȡ����ĳߴ�
	Size size=edgeS->getContentSize();
	//���������Y�������ű�
	float scaleY=p3.getLength()/size.height;
	//���þ���Y�������ű�
	edgeS->setScaleY(scaleY);

	//���þ����λ��
	edgeS->setPosition(Point((pe.x+ps.x)/2,(pe.y+ps.y)/2));
	edgeS->setRotation(-(std::atan2((ps.x-pe.x),(pe.y-ps.y)))*180/3.1415926);

}
