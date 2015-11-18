#include "HelpLayer.h"
#include "SimpleAudioEngine.h"
#include "WelcomeLayer.h"
#include "ChoiceLayer.h"
#include "AppConstant.h"//������
using namespace std;
using namespace cocos2d;
HelpLayer::~HelpLayer()
{

}

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

	auto backItem = MenuItemImage::create
	(
			pic_PATH+"back.png",
			pic_PATH+"back.png",
			CC_CALLBACK_0(HelpLayer::onBack, this)//���ʱִ�еĻص�����
	);
	backItem->setPosition(
			Point(
				origin.x - backItem->getContentSize().width/2+520,	//X����
				origin.y -backItem->getContentSize().height/2+940		//Y����
			)
			);
	//�����˵�����
	auto backMenu = Menu::create(backItem, NULL);
	//���ò˵�λ��
	backMenu->setPosition(Point::ZERO);
	//���˵���ӵ�������
	this->addChild(backMenu, 1);
	 //����һ��������󣬰���bg.pngͼƬ
	bgSprite = Sprite::create(pic_PATH+"bg.jpg");
	//���þ�������λ��
	bgSprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	//��������ӵ�������
	this->addChild(bgSprite, 0);

	for(int i=0;i<3;i++)
	{
		spIntro[i] = Sprite::create(helpPic_PATH+StringUtils::format("dibanHelp%d.png",i));//������ʾ����
		spIntro[i]->setAnchorPoint(Point(0,0));//������ʾ����ê��
		spIntro[i]->setPosition(0+i*350,0);//������ʾ����λ��
		TBGPoint[i] = spIntro[i]->getPosition();//��ȡ��ʾ����λ��
	}

	Point pp[4];//����һ����������飬�����������
	pp[0] = Point(0, 0);//�����������ֵ
	pp[1] = Point(350, 0);//�����������ֵ
	pp[2] = Point(350, 622);//�����������ֵ
	pp[3] = Point(0, 622);//�����������ֵ
	Color4F green(0, 1, 0, 0);//����������ɫ
	Color4F red(1, 0, 0, 0);//����α߿���ɫ
	//����������DrawNode
	DrawNode* shape = DrawNode::create();
	shape->drawPolygon(pp ,4, green, 1,red);//���ƶ����
	//�������ýڵ�
	ClippingNode* clipper=ClippingNode::create();
	//���ü���ģ��
	clipper->setStencil(shape);
	//���ñ����ýڵ�
	for(int j=0; j<3; j++)
	{
		clipper->addChild(spIntro[j],1);//����ʾ������ӵ����ýڵ���
	}
	clipper->setPosition(Point(90,200));//���ü��ýڵ�λ��
	//�������ýڵ���õ�����
	this->addChild(clipper, 0);

	for(int i=0;i<3;i++)
	{
		if(i == 0)
		{
			bSprite[i] = Sprite::create(helpPic_PATH+"white.png");//�����׵㾫��
		}else
		{
			bSprite[i] = Sprite::create(helpPic_PATH+"black.png");//�����ڵ㾫��
		}
		bSprite[i]->setPosition(Point(230+i*30,135));//���úڰ׵㾫��λ��
		this->addChild(bSprite[i],4);//���ڰ׵㾫����ӵ�������
	}
	//����һ�����㴥������
	EventListenerTouchOneByOne* listenerTouch = EventListenerTouchOneByOne::create();
	//�����´�����
	listenerTouch->setSwallowTouches(true);
	//��ʼ����ʱ�ص�onTouchBegan����
	listenerTouch->onTouchBegan = CC_CALLBACK_2(HelpLayer::onMyTouchBegan, this);
	//��ʼ����ʱ�ص�onTouchMoved����
	listenerTouch->onTouchMoved = CC_CALLBACK_2(HelpLayer::onMyTouchMoved, this);
	//��������ʱ�ص�onTouchEnded����
	listenerTouch->onTouchEnded = CC_CALLBACK_2(HelpLayer::onMyTouchEnded, this);
	//��ӵ�������
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTouch, spIntro[0]);
	for(int i=0;i<3;i++)
	{
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTouch->clone(), spIntro[i]);
	}

	return true;
}

bool HelpLayer::onMyTouchBegan(Touch *touch, Event *event)
{
	auto target = static_cast<Sprite*>(	event->getCurrentTarget());//��ȡ��ǰ�������󣬲�ת��Ϊ��������
	currPoint = touch->getLocation();//��ǰ������λ��
	Point location = target->convertToNodeSpace(currPoint);//��ȡ��ǰ����
	auto size = target->getContentSize();			//��ȡ����Ĵ�С
	auto rect = Rect(0, 0, size.width, size.height);//����һ�����ζ������С�뾫����ͬ
	if( rect.containsPoint(location)){	//�жϴ������Ƿ���Ŀ��ķ�Χ��
		return true;
	}else{
		return false;
	}
}

void HelpLayer::onMyTouchMoved(Touch *touch, Event *event)
{
	for(int i=0;i<3;i++)
	{
		spIntro[i]->setPosition(
				TBGPoint[i].x+(touch->getLocation().x-currPoint.x),
				TBGPoint[i].y
		);
	}
}

void HelpLayer::onMyTouchEnded(Touch *touch, Event *event)
{
	auto target = static_cast<Sprite*>(				//��ȡ�ĵ�ǰ�����Ķ��󣬲�ת��Ϊ��������
									event->getCurrentTarget());
	Point location = target->convertToNodeSpace(touch->getLocation());//��ȡ��ǰ����
	for(int i=0;i<3;i++)
	{
		TBGPoint[i] = spIntro[i]->getPosition();
	}

	float jlMin = MAX_INT;

	for(int i=0;i<3;i++)
	{
		if(fabs(TBGPoint[i].x)<jlMin)
		{
			jlMin = fabs(TBGPoint[i].x);

			currIntroIndex = i;
		}
	}


	int tempNum = currIntroIndex;
	for(int i=0;i<2;i++)
	{
		if(tempNum == 3)
		{
			tempNum = 0;
		}
		spIntro[tempNum]->setPosition(
						0+i*350,
						spIntro[tempNum]->getPosition().y
				);
		tempNum ++;
	}

	tempNum =currIntroIndex;
	for(int i=0;i<2;i++)
	{
		if(tempNum == -1)
		{
			tempNum = 2;
		}
		spIntro[tempNum]->setPosition(
						0-i*350,
						spIntro[tempNum]->getPosition().y
				);
		tempNum --;
	}

	for(int i=0;i<3;i++)
	{
		TBGPoint[i] = spIntro[i]->getPosition();
	}
	setBWPosition();
}

void HelpLayer::setBWPosition()
{
	int tempNUM  = 1;
	for(int i=0;i<3;i++)
	{
		if(i == currIntroIndex)
		{
			bSprite[0]->setPosition(Point(230+i*30,135));
		}else
		{
			bSprite[tempNUM ]->setPosition(Point(230+i*30,135));
			tempNUM  ++;
		}
	}
}

void HelpLayer::onBack()
{
	if(ChoiceLayer::isSound)
	{
		wl->playSwitchSound();//�����л���Ч
	}
	gsm->goWelcomeScene();
}
