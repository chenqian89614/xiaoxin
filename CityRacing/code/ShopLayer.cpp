#include "cocos2d.h"
#include "ShopLayer.h"
#include "Constant.h"
#include "StartLayer.h"

using namespace cocos2d;

bool ShopLayer::init()
{
	//���ø���ĳ�ʼ��
	if (!Layer::init())
	{
		return false;
	}
	selectIndex = 0;

	if(StartLayer::soundFlag == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(	//��������
						"background.mp3",
						true
						);
	}


	bgSpriteO = Sprite::create("scene1.jpg");
	bgSpriteO->setPosition(270,480);
	this->addChild(bgSpriteO,0);

	bgSpriteT = Sprite::create("scene1.jpg");
	bgSpriteT->setPosition(270,-480);
	this->addChild(bgSpriteT,0);

	Sprite* bg = Sprite::create("MenuBg.png");
	bg->setPosition(Point(270,480));
	this->addChild(bg,1);

	for(int i=0;i<2;i++)
	{
		itemSprite[i] = Sprite::create("ShopBottom.png");
		itemSprite[i]->setPosition(Point(195+i*150,650));
		this->addChild(itemSprite[i],2);

		Sprite* sp = Sprite::create(StringUtils::format("item%d.png",i+1));
		sp->setPosition(Point(195+i*150,670));
		this->addChild(sp,3);
	}
	for(int i=2;i<5;i++)
	{
		itemSprite[i] = Sprite::create("ShopBottom.png");
		itemSprite[i]->setPosition(Point(120+(i-2)*150,470));
		this->addChild(itemSprite[i],2);

		Sprite* sp = Sprite::create(StringUtils::format("item%d.png",i+1));
		sp->setPosition(Point(120+(i-2)*150,490));
		this->addChild(sp,3);
	}

	LabelAtlas* cbBuyNo2 = LabelAtlas::create(						//����һ��LabelAtlas����
			"4","upNum.png",20,23,'0');
	cbBuyNo2->setPosition(								//����LabelAtlas����λ��
						Point(220,600));
	this->addChild(cbBuyNo2,4);							//��LabelAtlas������ӵ�������

	LabelAtlas* cbBuyRct = LabelAtlas::create(						//����һ��LabelAtlas����
			"2","upNum.png",20,23,'0');
	cbBuyRct->setPosition(								//����LabelAtlas����λ��
						Point(370,600));
	this->addChild(cbBuyRct,4);							//��LabelAtlas������ӵ�������

	selSprite = Sprite::create("Selected.png");
	selSprite->setPosition(itemSprite[0]->getPosition());
	this->addChild(selSprite,4);

	Sprite* introSprite= Sprite::create("Introduction.png");
	introSprite->setPosition(Point(270,270));
	this->addChild(introSprite,3);

	//������һ���˵���
	MenuItemImage* BTItem = MenuItemImage::create(
			   "Button.png",						//ƽʱ��ͼƬ
			   "ButtonPressed.png",				//ѡ��ʱ��ͼƬ
			   CC_CALLBACK_0(ShopLayer::buyItem, this) 	//���ʱִ�еĻص�����
		);
	//������һ���˵����λ��
	BTItem->setPosition(Point(270,100));

	//������һ���˵���
	MenuItemImage* backMenu = MenuItemImage::create(
			   "goback.png",	//ƽʱ��ͼƬ
			   "gobackp.png",	//ѡ��ʱ��ͼƬ
			   CC_CALLBACK_0(ShopLayer::backMenuCallback, this) //���ʱִ�еĻص�����
		);
	//������һ���˵����λ��
	backMenu->setPosition(Point(40,920));


	//�����˵�����
	auto menu = Menu::create(BTItem,backMenu,NULL);
	//���ò˵�λ��
	menu->setPosition(Point::ZERO);
	//���˵���ӵ�������
	this->addChild(menu, 1);

	Sprite* enter = Sprite::create("Buy.png");
	enter->setPosition(270,100);
	this->addChild(enter,2,9);


	//���ö�ʱ�ص�ָ�������ɻ�
	auto director = Director::getInstance();
	auto sched = director->getScheduler();
	//����������ʱ�ص�
	sched->scheduleSelector(SEL_SCHEDULE(&ShopLayer::bgUpdate),this,0.005,false);

	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(ShopLayer::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,itemSprite[0]);
	for(int i=1;i<5;i++)
	{
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(),itemSprite[i]);
	}

	initItemFuncIntro();

	return true;
}
void ShopLayer::backMenuCallback()
{
	if(StartLayer::gameMode == 3)
	{
		crsm->goStartLyaer();
	}else if(StartLayer::gameMode == 4)
	{
		crsm->goGameOverLayer();
	}
}
void ShopLayer::buyItem()
{
	do{
		int goldSum = UserDefault::getInstance()->getIntegerForKey(Constant::userGold.c_str());
		int restGoldSum = goldSum - (int)atof(itemPriceString[selectIndex].c_str());
		if(restGoldSum < 0 )
		{
			break ;
		}
		std::string userString ;
		if(selectIndex == 4)
		{
			int index = rand()%4;
			selectIndex = index;
		}
		switch(selectIndex)
		{
		case 0:
			userString = "userNo2tCount";
			break;
		case 1:
			userString = "userRocketCount";
			break;
		case 2:
			userString = "userWDCount";
			break;
		case 3:
			userString = "userDoubleGold";
			break;
		}
		selSprite->setPosition(itemSprite[selectIndex]->getPosition());
		int countTemp = UserDefault::getInstance()->getIntegerForKey(userString.c_str());
		int itemCount = 1;
		if(selectIndex == 0)
		{
			itemCount = 4;
		}else if(selectIndex == 1)
		{
			itemCount = 2;
		}

		UserDefault::getInstance()->setIntegerForKey(
				Constant::userGold.c_str(),restGoldSum);
		userGoldCount->setString(StringUtils::format("%d",restGoldSum));
		UserDefault::getInstance()->setIntegerForKey(
								userString.c_str(),countTemp+itemCount);

		itemFuncIntro();
	}while(0);
}
bool ShopLayer::onTouchBegan(Touch* touch, Event* event)
{
	//��ȡ�ĵ�ǰ�����Ķ��󣬲�ת��Ϊ��������
	spriteTouch = static_cast<Sprite*>(event->getCurrentTarget());
	spriteTouch->retain();
	//��ȡ��ǰ����
	auto location = spriteTouch->convertToNodeSpace(touch->getLocation());
	//��ȡ����Ĵ�С
	auto size = spriteTouch->getContentSize();
	//����һ�����ζ������С�뾫����ͬ
	auto rect = Rect(0, 0, size.width, size.height);
	//�жϴ������Ƿ���Ŀ��ķ�Χ��
	if(rect.containsPoint(location)){
		for(int i = 0;i<5;i++)
		{
			if(spriteTouch==itemSprite[i])
			{
				selSprite->setPosition(itemSprite[i]->getPosition());
				selectIndex = i ;
				itemFuncIntro();
				break ;
			}
		}
		return true;
	}
	return false ;
}
void ShopLayer::initItemFuncIntro()
{
	Sprite* myResources = Sprite::create("myres.png");
	myResources->setPosition(Point(220,850));
	this->addChild(myResources,4);

	int count = UserDefault::getInstance()->getIntegerForKey(Constant::userNo2tCount.c_str());

	myResourcesCount = LabelAtlas::create(						//����һ��LabelAtlas����
			StringUtils::format("%d",count)
				,"upNum.png",20,23,'0');
	myResourcesCount->setPosition(								//����LabelAtlas����λ��
						Point(370,830));
	this->addChild(myResourcesCount,4);			//��LabelAtlas������ӵ�������

	itemName = Label::createWithTTF("\u52a0\u901f\u5361:","FZKATJW.ttf",30);
	itemName->setPosition(Point(190,340));
	this->addChild(itemName,4);

	itemFunc = Label::createWithTTF("\u5927\u5e45\u5ea6\u63d0\u5347\u8f66\u884c\u9a76\u901f\u5ea6","FZKATJW.ttf",30);
	itemFunc->setPosition(Point(270,270));
	this->addChild(itemFunc,4);

	itemPrice = LabelAtlas::create(						//����һ��LabelAtlas����
			"300","upNum.png",20,23,'0');
	itemPrice->setPosition(								//����LabelAtlas����λ��
						Point(300,326));
	this->addChild(itemPrice,4);			//��LabelAtlas������ӵ�������

	int buyOrNot = UserDefault::getInstance()->getIntegerForKey(Constant::userGold.c_str());

	userGoldCount = LabelAtlas::create(						//����һ��LabelAtlas����
			StringUtils::format("%d",buyOrNot)
				,"upNum.png",20,23,'0');
	userGoldCount->setPosition(								//����LabelAtlas����λ��
						Point(300,196));
	this->addChild(userGoldCount,4);			//��LabelAtlas������ӵ�������

	itemNameString[0]  ="\u52a0\u901f\u5361";
	itemNameString[1]  ="\u706b\u7bad\u7b52";
	itemNameString[2]  ="\u4fdd\u62a4\u5957";
	itemNameString[3]  ="\u53cc\u500d\u91d1\u5e01";
	itemNameString[4]  ="\u968f\u673a\u62bd\u5956";

	itemFuncString[0] = "\u5927\u5e45\u5ea6\u63d0\u5347\u8f66\u901f";
	itemFuncString[1] ="\u53ef\u7528\u6765\u6d88\u706d\u6321\u9053\u7684\u8f66";
	itemFuncString[2] ="\u4f7f\u81ea\u5df1\u7684\u8f66\u53d8\u4e3a\u65e0\u654c\u72b6\u6001";
	itemFuncString[3] ="\u5728\u6e38\u620f\u4e2d\u83b7\u5f97\u53cc\u500d\u91d1\u5e01";
	itemFuncString[4] ="\u968f\u673a\u62bd\u53d6\u9053\u5177";

	itemPriceString[0] = "300";
	itemPriceString[1] = "240";
	itemPriceString[2] = "2000";
	itemPriceString[3] = "2500";
	itemPriceString[4] = "500";
}
void ShopLayer::itemFuncIntro()
{
	itemName->setString(itemNameString[selectIndex]);
	itemFunc->setString(itemFuncString[selectIndex]);
	itemPrice->setString(itemPriceString[selectIndex]);
	int count = 0 ;
	switch(selectIndex)
	{
	case 0:
		count = UserDefault::getInstance()->getIntegerForKey(Constant::userNo2tCount.c_str());
		break ;
	case 1:
		count = UserDefault::getInstance()->getIntegerForKey(Constant::userRocketCount.c_str());
		break ;
	case 2:
		count = UserDefault::getInstance()->getIntegerForKey(Constant::userWDCount.c_str());
		break ;
	case 3:
		count = UserDefault::getInstance()->getIntegerForKey(Constant::userDoubleGold.c_str());
		break ;
	}
	myResourcesCount->setString(StringUtils::format("%d",count));
}
void ShopLayer::bgUpdate()
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
