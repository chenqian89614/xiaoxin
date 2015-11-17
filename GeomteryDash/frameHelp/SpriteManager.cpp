#include "SpriteManager.h"
#include "MusicManager.h"
#include "../hellocpp/GameLayer.h"
#include "../hellocpp/FlyLayer.h"
#include "../hellocpp/LevelLayer.h"
#include "../hellocpp/MenuLayer.h"
#include "../hellocpp/Constant.h"
#include "../hellocpp/ChoiceCubeLayer.h"
#include "../hellocpp/MusicLayer.h"

SpriteManager::SpriteManager(Layer* layerIn)
{
	this->layer = layerIn;

	batchNode = SpriteBatchNode::create("pic/GJ_GameSheet.png",800);
	batchNode->setAnchorPoint(Point(0, 0));
	batchNode->setPosition(Point(0,0));

	listenerTouch = EventListenerTouchOneByOne::create();
	//�����´�����
	listenerTouch->setSwallowTouches(true);
	//��ʼ����ʱ�ص�onTouchBegan����
	listenerTouch->onTouchBegan = CC_CALLBACK_2(SpriteManager::myOnTouchBegan, this);
	//�����ƶ�ʱ�ص�onTouchMoved����
	listenerTouch->onTouchMoved = CC_CALLBACK_2(SpriteManager::myOnTouchMoved, this);
	//��������ʱ�ص�onTouchEnded����
	listenerTouch->onTouchEnded = CC_CALLBACK_2(SpriteManager::myOnTouchEnded, this);
	//��ֹ����ʱ�ص�onTouchCancelled����
	listenerTouch->onTouchCancelled = CC_CALLBACK_2(SpriteManager::myOnTouchCancelled, this);

	layer->addChild(batchNode,BatchNodeZOrder);
}

void SpriteManager::SpPause()//��Ϸ���Ͻǵ�ͼƬ
{
	Rect recta(776,28,801-776,53-28);//��ͣ  ��ͼƬ
	allSp[0] = createSprite(NULL, recta, batchNode, 1.0f, 1.0f, 960, 540, 60, 60, PauseBGZOrder-1);
	AddEventListenerSprite(allSp[0]);
}
void SpriteManager::AddEventListenerSprite(Sprite* sp)
{
	//��ӵ�������
	Director *director = Director::getInstance();
	(director->getEventDispatcher())->addEventListenerWithSceneGraphPriority(listenerTouch->clone(), sp);
	listenerTouch->retain();
}
bool SpriteManager::Judge(Sprite* sp, Point location)
{
	//��ȡ����Ĵ�С
	Size size = sp->getContentSize();
	//����һ�����ζ������С�뾫����ͬ
	Rect rect(0, 0, size.width, size.height);
	//�жϴ������Ƿ���Ŀ��ķ�Χ��
	if( rect.containsPoint(location) )
	{
		//һ����������˵������ǰ������  ��ĳ�����鷶Χ��
		if(isTouchBegin == true)
		{
			return true;
		}
		MusicManager::playPauseMenuEffect();
		if(sp == allSp[0])//������ͣͼƬ��������Ӧ����
		{
			if(((GameLayer*)(layer))->pc->statePause == false)
			{
				((GameLayer*)(layer))->pc->PauseStart();
			}
			return true;
		}
		else if(sp == allSp[23])
		{
			Director *director = Director::getInstance();
			director->resume();
			if(MusicManager::onSound == true)
			{
				MusicManager::playMenuLayerMusic();//��������
			}
			if(layer->getTag() == INDEX_GRAMLAYER)
			{
				((GameLayer*)(layer))->gsm->goLevelLayer();//��ת��LevelLayer��
			}
			else if(layer->getTag() == INDEX_FLYLAYER)
			{
				((FlyLayer*)(layer))->gsm->goLevelLayer();//��ת��LevelLayer��
			}
			return true;
		}
		else if(layer->getTag() == INDEX_GRAMLAYER && ((GameLayer*)(layer))->pc->PauseJudgeSp(sp))//�ȽϽڵ��ǩ  �� ���о����ж�
		{
			return true;
		}
		else if(layer->getTag() == INDEX_LEVELLAYER && ((LevelLayer*)(layer))->llh->JudgeSp(sp))//�ȽϽڵ��ǩ  �� ���о����ж�
		{
			return true;
		}
		else if(layer->getTag() == INDEX_MENULAYER && ((MenuLayer*)(layer))->mlh->JudgeSp(sp))//�ȽϽڵ��ǩ  �� ���о����ж�
		{
			return true;
		}
		else if(layer->getTag() == INDEX_FLYLAYER && ((FlyLayer*)(layer))->pc->PauseJudgeSp(sp))//�ȽϽڵ��ǩ  �� ���о����ж�
		{
			return true;
		}
		else if(layer->getTag() == INDEX_CHOICECUBELAYER && ((ChoiceCubeLayer*)(layer))->cclh->JudgeSp(sp))//�ȽϽڵ��ǩ  �� ���о����ж�
		{
			return true;
		}
		else if(layer->getTag() == INDEX_MUSICLAYER && ((MusicLayer*)(layer))->mlh->JudgeSp(sp))//�ȽϽڵ��ǩ  �� ���о����ж�
		{
			return true;
		}
	}
	return false;
}

//��������ķ���
Sprite* SpriteManager::createSprite(std::string* id, Rect recta, SpriteBatchNode* batchNode, float anchorX, float anchorY, float locationX, float locationY, float width, float height, int ZOrder)
{
	Sprite* sp = Sprite::createWithTexture(batchNode->getTexture(),recta);
	Size size=sp->getContentSize();//��ȡ����ĳߴ�
	float scaleX=width/size.width;	//���������X�������ű�
	float scaleY=height/size.height;//���������Y�������ű�
	sp->setScaleX(scaleX);//���þ���X�������ű�
	sp->setScaleY(scaleY);//���þ���Y�������ű�
	sp->setAnchorPoint(Point(anchorX,anchorY));//����ê��
	sp->setPosition(Point(locationX,locationY));//���þ����λ��
	sp->setUserData(id);
	batchNode->addChild(sp,ZOrder);
	return sp;
}
//��ʼ�����¼��Ĵ�����
bool SpriteManager::myOnTouchBegan(Touch *touch, Event *event)
{
	isTouchBegin = true;

	//��ȡ�ĵ�ǰ�����Ķ��󣬲�ת��Ϊ��������
	Sprite* targetSp = static_cast<Sprite*>(event->getCurrentTarget());
	//��ȡ��ǰ����
	Point location = targetSp->convertToNodeSpace(touch->getLocation());

	return Judge(targetSp, location);
}
//�����ƶ��¼��Ĵ�����
void SpriteManager::myOnTouchMoved(Touch *touch, Event *event)
{
	isTouchBegin = false;
	isTouchMove = true;
}
//���ؽ����¼��Ĵ�����
void SpriteManager::myOnTouchEnded(Touch *touch, Event *event)
{
	isTouchMove = false;
	//��ȡ�ĵ�ǰ�����Ķ��󣬲�ת��Ϊ��������
	Sprite* targetSp = static_cast<Sprite*>(event->getCurrentTarget());
	//��ȡ��ǰ����
	Point location = targetSp->convertToNodeSpace(touch->getLocation());
	Judge(targetSp, location);
}
//������ֹ�¼��Ĵ�����
void SpriteManager::myOnTouchCancelled(Touch *touch, Event *event){myOnTouchEnded(touch,event);}

//��������ķ���
Sprite* SpriteManager::createStaticSprite(std::string* id, std::string pic, float anchorX, float anchorY, float locationX, float locationY, float width, float height)
{
	Sprite* sp = Sprite::create(pic);//��������
	Size size=sp->getContentSize();//��ȡ����ĳߴ�
	float scaleX=width/size.width;	//���������X�������ű�
	float scaleY=height/size.height;//���������Y�������ű�
	sp->setScaleX(scaleX);//���þ���X�������ű�
	sp->setScaleY(scaleY);//���þ���Y�������ű�
	sp->setAnchorPoint(Point(anchorX,anchorY));//����ê��
	sp->setPosition(Point(locationX,locationY));//���þ����λ��
	sp->setUserData(id);
	return sp;
}
void SpriteManager::backgroundRoll()//������������
{

	//===����===
	Sprite* bg = createStaticSprite(new std::string("bg"), "pic/game_bg_01_001-hd.png", 0.0f, 0.0f, 0, 0, WIDTH, HEIGHT);//������������
	if(layer->getTag() == INDEX_GRAMLAYER)
	{
		((GameLayer*)(layer))->spMap["bg"]=bg;
		bg->setColor(Color3B(98,5,170));
	}
	else if(layer->getTag() == INDEX_FLYLAYER)
	{
		((FlyLayer*)(layer))->spMap["bg"]=bg;
		bg->setColor(Color3B(98,5,170));
	}
	else
	{
		bg->setColor(Color3B(0,83,208));
	}
	layer->addChild(bg,BackgroundZOrder);


	Sprite* bg1 = createStaticSprite(new std::string("bg1"), "pic/game_bg_01_001-hd.png", 0.0f, 0.0f, WIDTH, 0, WIDTH, HEIGHT);//������������
	if(layer->getTag() == INDEX_GRAMLAYER)
	{
		((GameLayer*)(layer))->spMap["bg1"]=bg1;
		bg1->setColor(Color3B(98,5,170));
	}
	else if(layer->getTag() == INDEX_FLYLAYER)
	{
		((FlyLayer*)(layer))->spMap["bg1"]=bg1;
		bg1->setColor(Color3B(98,5,170));
		Sprite* sp1 = createSprite(NULL, Rect(0,499,319,528-499), batchNode, 0.0f, 0.0f, 0, 0, WIDTH, HEIGHT_EDGE, BackgroundZOrder+1);
		Sprite* sp2 = createSprite(NULL, Rect(0,499,319,528-499), batchNode, 0.0f, 1.0f, 0, HEIGHT, WIDTH, HEIGHT_EDGE, BackgroundZOrder+1);
	}
	else
	{
		bg1->setColor(Color3B(0,83,208));
	}
	layer->addChild(bg1,BackgroundZOrder);

	//���� ��������
	auto a1 = MoveBy::create(10, Point(-WIDTH, 0));
	auto  action = RepeatForever::create(Sequence::create( Place::create(Point(0, 0)), a1, NULL));
	bg->runAction(action);
	a1 = MoveBy::create(10, Point(-WIDTH, 0));
	action = RepeatForever::create(Sequence::create( Place::create(Point(WIDTH, 0)), a1, NULL));
	bg1->runAction(action);

}
Scale9Sprite* SpriteManager::createScale9Sprite(std::string pic, Rect recta1, Rect recta2,float anchorX, float anchorY, float locationX, float locationY, float width, float height, int ZOrder)
{
//	Scale9Sprite* ss = Scale9Sprite::create();
//	ss->updateWithBatchNode(batchNode,recta1,false,recta2);
//	ss->setAnchorPoint(Point(anchorX, anchorY));
//	ss->setContentSize(Size(width, height));
//	ss->setPosition(Point(locationX, locationY));
//	layer->addChild(ss, ZOrder);

	auto ss = Scale9Sprite::create(pic, recta1, recta2);
	ss->setAnchorPoint(Point(anchorX, anchorY));
	ss->setContentSize(Size(width, height));
	ss->setPosition(Point(locationX, locationY));
	layer->addChild(ss, ZOrder);
	return ss;
}
void SpriteManager::createSiJiao()//�������ܵ�ͼƬ
{
	//���½� ��ͼƬ
	createSprite(NULL, Rect(825,386,897-825,457-386), batchNode, 0.0f, 0.0f, 0, 0, 120, 120, GroundZOrder+1);

	//���½� ��ͼƬ
	Sprite* sp = createSprite(NULL, Rect(825,386,897-825,457-386), batchNode, 0.0f, 0.0f, WIDTH-120, 0, 120, 120, GroundZOrder+1);
	sp->setFlippedX(true);

	//���Ͻ� ��ͼƬ
	sp = createSprite(NULL, Rect(825,386,897-825,457-386), batchNode, 0.0f, 0.0f, 0, HEIGHT-120, 120, 120, GroundZOrder+1);
	sp->setFlippedY(true);

	//���Ͻ� ��ͼƬ
	sp = createSprite(NULL, Rect(825,386,897-825,457-386), batchNode, 0.0f, 0.0f, WIDTH-120, HEIGHT-120, 120, 120, GroundZOrder+1);
	sp->setFlippedX(true);
	sp->setFlippedY(true);
}
void SpriteManager::createGround()//����������沢�����Զ������ƶ�
{
	//�����������  ����ͣ���ƶ�
	tb[0]=new RectBarrier(NULL,layer,Rect(129,685,243-129,802-685),WIDTH/8,HEIGHT/8, WIDTH/4, HEIGHT/4, GroundZOrder);//��������
	tb[0]->sp->setColor(Color3B(0,67,169));
	tb[0]->sp->runAction(
			RepeatForever::create(
					Sequence::create(
							MoveBy::create(0.5,Point(-WIDTH/4,0)),
							Place::create(Point(WIDTH/8,HEIGHT/8)),
							NULL)));

	tb[1]=new RectBarrier(NULL,layer,Rect(129,685,243-129,802-685),WIDTH/8*3,HEIGHT/8, WIDTH/4, HEIGHT/4, GroundZOrder);//��������
	tb[1]->sp->setColor(Color3B(0,67,169));
	tb[1]->sp->runAction(
				RepeatForever::create(
						Sequence::create(
								MoveBy::create(0.5,Point(-WIDTH/4,0)),
								Place::create(Point(WIDTH/8*3,HEIGHT/8)),
								NULL)));

	tb[2]=new RectBarrier(NULL,layer,Rect(129,685,243-129,802-685),WIDTH/8*5,HEIGHT/8, WIDTH/4, HEIGHT/4, GroundZOrder);//��������
	tb[2]->sp->setColor(Color3B(0,67,169));
	tb[2]->sp->runAction(
				RepeatForever::create(
						Sequence::create(
								MoveBy::create(0.5,Point(-WIDTH/4,0)),
								Place::create(Point(WIDTH/8*5,HEIGHT/8)),
								NULL)));

	tb[3]=new RectBarrier(NULL,layer,Rect(129,685,243-129,802-685),WIDTH/8*7,HEIGHT/8, WIDTH/4, HEIGHT/4, GroundZOrder);//��������
	tb[3]->sp->setColor(Color3B(0,67,169));
	tb[3]->sp->runAction(
				RepeatForever::create(
						Sequence::create(
								MoveBy::create(0.5,Point(-WIDTH/4,0)),
								Place::create(Point(WIDTH/8*7,HEIGHT/8)),
								NULL)));

	tb[4]=new RectBarrier(NULL,layer,Rect(129,685,243-129,802-685),WIDTH/8*9,HEIGHT/8, WIDTH/4, HEIGHT/4, GroundZOrder);//��������
	tb[4]->sp->setColor(Color3B(0,67,169));
	tb[4]->sp->runAction(
				RepeatForever::create(
						Sequence::create(
								MoveBy::create(0.5,Point(-WIDTH/4,0)),
								Place::create(Point(WIDTH/8*9,HEIGHT/8)),
								NULL)));
}
void SpriteManager::win()
{
	batchNode->removeChild(allSp[0],true);

	Director *director = Director::getInstance();
	director->pause();//��ͣ�����˶�

	createSprite(NULL, Rect(419,652,619-419,708-652), batchNode, 0.5, 0.5, WIDTH/2, HEIGHT/2, 500, 200, PauseBGZOrder+1);

	//���Ͻ� �ķ��ؼ���ť
	allSp[23] = createSprite(NULL, Rect(871,154,910-871,186-154), batchNode, 0.5f, 0.5f, 45, 540-37, 63, 55, GoBackZOrder);
	allSp[23]->setRotation(-90.0f);
	AddEventListenerSprite(allSp[23]);
}
