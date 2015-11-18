#include "BNJoyStick.h"
#include "Constant.h"
#include <cmath>

BNJoyStick::BNJoyStick(){}

BNJoyStick::~BNJoyStick(){}

//��ȡ��������
Rect BNJoyStick::getRect()
{
	//��ȡ����ͼ�ĳߴ��С
	auto s = getTexture()->getContentSize();
    return Rect(-s.width / 2, -s.height / 2, s.width, s.height);
}

//�жϴ����λ�÷���
bool BNJoyStick::containsTouchLocation(Touch* touch)
{
	//�жϴ������Ƿ��ھ���������
    return getRect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

//ÿ�ξ������ʱ���ص�
void BNJoyStick::onEnter()
{
	//���ø����onEnter����
	Sprite::onEnter();

	//����һ�����㴥�ؼ���
	auto listener = EventListenerTouchOneByOne::create();
	//�����´�����
	listener->setSwallowTouches(true);
	//��ʼ����ʱ�ص�onTouchBegan����
    listener->onTouchBegan = CC_CALLBACK_2(BNJoyStick::onTouchBegan, this);
    //�����ƶ�ʱ�ص�onTouchMoved����
    listener->onTouchMoved = CC_CALLBACK_2(BNJoyStick::onTouchMoved, this);
    //��������ʱ�ص�onTouchEnded����
    listener->onTouchEnded = CC_CALLBACK_2(BNJoyStick::onTouchEnded, this);
    //��ӵ�������
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

//ÿ�ξ����˳�ʱ���ص�
void BNJoyStick::onExit()
{
	//���ø����onExit����
	Sprite::onExit();
}

//��ʼ�����¼��Ĵ�����
bool BNJoyStick::onTouchBegan(Touch* touch, Event* event)
{
	if (Constant::state!=2) return false;
    if ( !containsTouchLocation(touch)) return false;
    touchFlag=true;
    return true;
}

//�����ƶ��¼��Ĵ�����
void BNJoyStick::onTouchMoved(Touch* touch, Event* event)
{
	//�����ƶ��¼���û���βŵ���һ�Σ��������Ϸ�ٶ�
	if(yhCount%2==0)
	{
		//��ȡ���ص��λ��
		Point tp = touch->getLocation();
		//����calCenterPosition����
		calCenterPosition(tp.x,tp.y);
		yhCount=0;
	}
	yhCount++;
}

//���ؽ����¼��Ĵ�����
void BNJoyStick::onTouchEnded(Touch* touch, Event* event)
{
	//���ñ�־λ
	touchFlag=false;
	//����calCenter����
	calCenter();
	//����ҡ�����ĺ�����
	vx=0;
	//����ҡ������������
	vy=0;
}

//����ҡ������������ͼ�����귽��
void BNJoyStick::calCenterPosition(float tx,float ty)
{
	//��ȡ����ê������Ļ�ڵ�λ��
	Point p=getPosition();
	//��ȡ����ê������
	Point a=getAnchorPoint();
	//��ȡ����ͼ�ĳߴ��С
	Size s=getTexture()->getContentSize();
	//�����������ĵĺ�����
	float centerX=p.x-a.x*s.width+s.width/2.0f;
	//�����������ĵ�������
	float centerY=p.y-a.y*s.height+s.height/2.0f;
	//���������ڴ��ص㵽���ĵĺ�����
	float dx=tx-centerX;
	//���������ڴ��ص㵽���ĵ�������
	float dy=ty-centerY;

	//��ǰ����������ԭ��ľ���
	float spanP2=dx*dx+dy*dy;
	//�жϵ�ǰ�����ľ����Ƿ񳬳���Χ
	if(spanP2>rRange*rRange)
	{
		float span=sqrt(spanP2);
		//���þ��������ڵĺ�����
		dx=dx*rRange/span;
		//���þ��������ڵ�������
		dy=dy*rRange/span;
	}
	//����ҡ���ƶ��ĺ�����
	vx=dx;
	//����ҡ���ƶ���������
	vy=dy;

	//����ҡ������ҡ������
	centerPoint->setPosition(Point(dx+s.width/2.0f,dy+s.height/2.0f));
}

//��������ҡ��λ�ü���ȡ�뾶
void BNJoyStick::calCenter()
{
	if(!centerPoint)
	{
		return;
	}
	//��ȡ����ͼ�ĳߴ��С
	Size s=getTexture()->getContentSize();
	//��ȡ����ͼ������ҡ�˵�x����
	float centerXTemp=s.width/2.0f;
	//��ȡ����ͼ������ҡ�˵�y����
	float centerYTemp=s.height/2.0f;
	//��������ҡ�˵�λ��
    centerPoint->setPosition(Point(centerXTemp,centerYTemp));
    //��ȡ����ͼ�뾶
    rRange=s.width/2.0f;
}

//����ҡ�˵Ĵ�������
BNJoyStick* BNJoyStick::create(const std::string& basefilename,const std::string& centerfilename)
{
	//����һ������ҡ�˶���
	BNJoyStick *bnjs = new BNJoyStick();
	//�жϾ����Ƿ���ڲ���ʼ��
	if (bnjs && bnjs->initWithFile(basefilename))
	{
		//�Զ��ͷ�
		bnjs->autorelease();
		//��ʼ��ҡ��x����
		bnjs->vx=0;
		//��ʼ��ҡ��y����
		bnjs->vy=0;
		//����һ���������
		bnjs->centerPoint=Sprite::create(centerfilename);
		//��������ӵ�ҡ�˲�����
		bnjs->addChild(bnjs->centerPoint, 1,0);
		//����calCenter����
		bnjs->calCenter();
		return bnjs;
	}
	CC_SAFE_DELETE(bnjs);
	return nullptr;
}

