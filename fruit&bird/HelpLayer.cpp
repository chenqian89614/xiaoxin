#include "HelpLayer.h"

using namespace cocos2d;

//ʵ��HelpLayer���е�init��������ʼ������
bool HelpLayer::init()
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
	//��������
	Sprite* background = Sprite::create("morning.png");
	//����ê��
	background->setAnchorPoint(Point(0, 0));
	//���þ�������λ��
	background->setPosition(Point(origin.x,origin.y + visibleSize.height - background->getContentSize().height));
	//��������ӵ�������
	this->addChild(background, 0);

	//�������澫��1
	Sprite* floor = Sprite::create("floor.png");
	//����ê��
	floor->setAnchorPoint(Point(0, 0));
	//���þ������λ��
	floor->setPosition(Point(origin.x, origin.y));
	this->addChild(floor);
	//���õ������
	floor->runAction(RepeatForever::create(
		Sequence::create(
				MoveTo::create(0.5, Point(-120, 0)),
				MoveTo::create(0, Point(0, 0)),
				NULL
	)));

	Sprite* back = Sprite::create("helpBack.png");
	back->setPosition(Point(visibleSize.width/2, visibleSize.height/2 - 5));
	this->addChild(back, 0);

	for(int i=0;i<4;i++)
	{
		sp[i] = Sprite::create(StringUtils::format("help%d.png",i));
		sp[i]->setPosition(180+i*360, 320);
		if(i!=0)
		{
			sp[i]->runAction(FadeOut::create(0));
		}
	}

	//���ز˵�
	MenuItemImage* menuItem = MenuItemImage::create(
		"menu.png",
		"menu_off.png",
		 CC_CALLBACK_1(HelpLayer::menuCallBack, this) //���ʱִ�еĻص�����

	);
	menuItem->setPosition(Point(270,50));
	Menu* menu = Menu::create(menuItem, NULL);
	//���ò˵�λ��
	menu->setPosition(Point::ZERO);
	this->addChild(menu,10);

	Point pp[4];
	pp[0] = Point(0, 0);
	pp[1] = Point(360, 0);
	pp[2] = Point(360, 640);
	pp[3] = Point(0, 640);
	Color4F green(0, 1, 0, 0);
	Color4F red(1, 0, 0, 0);
	//����������DrawNode
	DrawNode* shape = DrawNode::create();
	shape->drawPolygon(pp ,4, green, 1,red);
	//�������ýڵ�
	ClippingNode* clipper=ClippingNode::create();
	//���ü���ģ��
	clipper->setStencil(shape);
	//���ñ����ýڵ�
	for(int i=0; i<4; i++)
	{
		clipper->addChild(sp[i],0);
	}
	clipper->setPosition(Point(90, 160));
	//�������ýڵ���õ�����
	this->addChild(clipper, 0);

	//����һ�����㴥������
	EventListenerTouchOneByOne* listenerTouch = EventListenerTouchOneByOne::create();
	//�����´�����
	listenerTouch->setSwallowTouches(true);
	//��ʼ����ʱ�ص�onTouchBegan����
	listenerTouch->onTouchBegan = CC_CALLBACK_2(HelpLayer::onTouchBegan, this);
	//��������ʱ�ص�onTouchEnded����
	listenerTouch->onTouchEnded = CC_CALLBACK_2(HelpLayer::onTouchEnded, this);
	//��ӵ�������
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTouch, clipper);

	return true;
}
void HelpLayer::onTouchEnded(Touch* touch, Event* event)
{
	do{
		if(moveFlag)
		{
			break;
		}
		//��ȡ�ĵ�ǰ�����Ķ��󣬲�ת��Ϊ��������
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		//��ȡ��ǰ����
		auto location = target->convertToNodeSpace(touch->getLocation());
		endPoint =  location;
		if(beganPoint.x-endPoint.x>=30)
		{
			index++;
			if(index>3)
			{
				index=0;
				sp[0]->setPosition(Point(540,320));
				sp[0]->runAction(FadeOut::create(0));
			}
			sp[index]->setPosition(Point(540,320));
			moveFlag=true;
			for(int i=0;i<3;i++)
			{
				if(i == index)
				{
					sp[i]->runAction(
						Spawn::create(
						MoveBy::create(1,Point(-360,0)),
						FadeIn::create(1),
						NULL
					));
				}
				if(i == index-1)
				{
					sp[i]->runAction(
						Spawn::create(
						MoveBy::create(1,Point(-360,0)),
						FadeOut::create(1),
						NULL
					));
				}
				if(i == index + 1)
				{
					sp[i]->runAction(
						Spawn::create(
						MoveBy::create(1,Point(-360,0)),
						FadeOut::create(1),
						NULL
					));
				}
			}
			sp[3]->runAction(
					Sequence::create(
					Spawn::create(MoveBy::create(1,Point(-360,0)), FadeIn::create(1),NULL),
					CallFunc::create(CC_CALLBACK_0(HelpLayer::setmoveFlag, this)),
					NULL
			));

		}else if(endPoint.x-beganPoint.x>=30)
		{
			index--;
			if(index<0)
			{
				index = 3;
				sp[3]->setPosition(Point(-180,320));
			}
			sp[index]->setPosition(Point(-180,320));
			moveFlag=true;
			for(int i=3;i>0;i--)
			{
				if(i == index)
				{
					sp[i]->runAction(
						Spawn::create(
							MoveBy::create(1,Point(360,0)),
							FadeIn::create(1),
							NULL
						));
				}
				if(i == index + 1)
				{
					sp[i]->runAction(
						Spawn::create(
						MoveBy::create(1,Point(360,0)),
						FadeOut::create(1),
						NULL
					));
				}
				if(i == index - 1)
				{
					sp[i]->runAction(
						Spawn::create(
						MoveBy::create(1,Point(360,0)),
						FadeOut::create(1),
						NULL
					));
				}
			}
			sp[0]->runAction(
					Sequence::create(
					Spawn::create(MoveBy::create(1,Point(360,0)), FadeIn::create(1),NULL),
					CallFunc::create(CC_CALLBACK_0(HelpLayer::setmoveFlag, this)),
					NULL
			));
		}
	}while(0);
}
bool HelpLayer::onTouchBegan(Touch* touch, Event* event)
{
	if(moveFlag)
	{
		return false;
	}
	//��ȡ�ĵ�ǰ�����Ķ��󣬲�ת��Ϊ��������
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	//��ȡ��ǰ����
	auto location = target->convertToNodeSpace(touch->getLocation());
	beganPoint = location;
	return true;
}
void HelpLayer::setmoveFlag()
{
	moveFlag=false;
	if(beganPoint.x-endPoint.x>=30)
	{
		if(index+1>3)
		{
			sp[0]->setPosition(Point(540,320));
		}else
		{
			sp[index+1]->setPosition(Point(540,320));
		}
	}

	if(endPoint.x-beganPoint.x>=30)
	{
		if(index-1<0)
		{
			sp[3]->setPosition(Point(-180,320));
		}else
		{
			sp[index-1]->setPosition(Point(-180,320));
		}
	}
}
void HelpLayer::menuCallBack(Ref* pSender)
{
	sceneManager->goToMainScene();

}
