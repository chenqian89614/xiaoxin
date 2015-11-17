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
	//设置下传触摸
	listenerTouch->setSwallowTouches(true);
	//开始触摸时回调onTouchBegan方法
	listenerTouch->onTouchBegan = CC_CALLBACK_2(SpriteManager::myOnTouchBegan, this);
	//触摸移动时回调onTouchMoved方法
	listenerTouch->onTouchMoved = CC_CALLBACK_2(SpriteManager::myOnTouchMoved, this);
	//触摸结束时回调onTouchEnded方法
	listenerTouch->onTouchEnded = CC_CALLBACK_2(SpriteManager::myOnTouchEnded, this);
	//终止触摸时回调onTouchCancelled方法
	listenerTouch->onTouchCancelled = CC_CALLBACK_2(SpriteManager::myOnTouchCancelled, this);

	layer->addChild(batchNode,BatchNodeZOrder);
}

void SpriteManager::SpPause()//游戏右上角的图片
{
	Rect recta(776,28,801-776,53-28);//暂停  的图片
	allSp[0] = createSprite(NULL, recta, batchNode, 1.0f, 1.0f, 960, 540, 60, 60, PauseBGZOrder-1);
	AddEventListenerSprite(allSp[0]);
}
void SpriteManager::AddEventListenerSprite(Sprite* sp)
{
	//添加到监听器
	Director *director = Director::getInstance();
	(director->getEventDispatcher())->addEventListenerWithSceneGraphPriority(listenerTouch->clone(), sp);
	listenerTouch->retain();
}
bool SpriteManager::Judge(Sprite* sp, Point location)
{
	//获取精灵的大小
	Size size = sp->getContentSize();
	//创建一个矩形对象，其大小与精灵相同
	Rect rect(0, 0, size.width, size.height);
	//判断触摸点是否在目标的范围内
	if( rect.containsPoint(location) )
	{
		//一旦进来，则说明，当前触摸点  在某个精灵范围内
		if(isTouchBegin == true)
		{
			return true;
		}
		MusicManager::playPauseMenuEffect();
		if(sp == allSp[0])//若是暂停图片，调用相应代码
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
				MusicManager::playMenuLayerMusic();//播放音乐
			}
			if(layer->getTag() == INDEX_GRAMLAYER)
			{
				((GameLayer*)(layer))->gsm->goLevelLayer();//跳转到LevelLayer里
			}
			else if(layer->getTag() == INDEX_FLYLAYER)
			{
				((FlyLayer*)(layer))->gsm->goLevelLayer();//跳转到LevelLayer里
			}
			return true;
		}
		else if(layer->getTag() == INDEX_GRAMLAYER && ((GameLayer*)(layer))->pc->PauseJudgeSp(sp))//比较节点标签  并 进行精灵判断
		{
			return true;
		}
		else if(layer->getTag() == INDEX_LEVELLAYER && ((LevelLayer*)(layer))->llh->JudgeSp(sp))//比较节点标签  并 进行精灵判断
		{
			return true;
		}
		else if(layer->getTag() == INDEX_MENULAYER && ((MenuLayer*)(layer))->mlh->JudgeSp(sp))//比较节点标签  并 进行精灵判断
		{
			return true;
		}
		else if(layer->getTag() == INDEX_FLYLAYER && ((FlyLayer*)(layer))->pc->PauseJudgeSp(sp))//比较节点标签  并 进行精灵判断
		{
			return true;
		}
		else if(layer->getTag() == INDEX_CHOICECUBELAYER && ((ChoiceCubeLayer*)(layer))->cclh->JudgeSp(sp))//比较节点标签  并 进行精灵判断
		{
			return true;
		}
		else if(layer->getTag() == INDEX_MUSICLAYER && ((MusicLayer*)(layer))->mlh->JudgeSp(sp))//比较节点标签  并 进行精灵判断
		{
			return true;
		}
	}
	return false;
}

//创建精灵的方法
Sprite* SpriteManager::createSprite(std::string* id, Rect recta, SpriteBatchNode* batchNode, float anchorX, float anchorY, float locationX, float locationY, float width, float height, int ZOrder)
{
	Sprite* sp = Sprite::createWithTexture(batchNode->getTexture(),recta);
	Size size=sp->getContentSize();//获取精灵的尺寸
	float scaleX=width/size.width;	//计算出精灵X方向缩放比
	float scaleY=height/size.height;//计算出精灵Y方向缩放比
	sp->setScaleX(scaleX);//设置精灵X方向缩放比
	sp->setScaleY(scaleY);//设置精灵Y方向缩放比
	sp->setAnchorPoint(Point(anchorX,anchorY));//设置锚点
	sp->setPosition(Point(locationX,locationY));//设置精灵的位置
	sp->setUserData(id);
	batchNode->addChild(sp,ZOrder);
	return sp;
}
//开始触控事件的处理方法
bool SpriteManager::myOnTouchBegan(Touch *touch, Event *event)
{
	isTouchBegin = true;

	//获取的当前触摸的对象，并转化为精灵类型
	Sprite* targetSp = static_cast<Sprite*>(event->getCurrentTarget());
	//获取当前坐标
	Point location = targetSp->convertToNodeSpace(touch->getLocation());

	return Judge(targetSp, location);
}
//触控移动事件的处理方法
void SpriteManager::myOnTouchMoved(Touch *touch, Event *event)
{
	isTouchBegin = false;
	isTouchMove = true;
}
//触控结束事件的处理方法
void SpriteManager::myOnTouchEnded(Touch *touch, Event *event)
{
	isTouchMove = false;
	//获取的当前触摸的对象，并转化为精灵类型
	Sprite* targetSp = static_cast<Sprite*>(event->getCurrentTarget());
	//获取当前坐标
	Point location = targetSp->convertToNodeSpace(touch->getLocation());
	Judge(targetSp, location);
}
//触控终止事件的处理方法
void SpriteManager::myOnTouchCancelled(Touch *touch, Event *event){myOnTouchEnded(touch,event);}

//创建精灵的方法
Sprite* SpriteManager::createStaticSprite(std::string* id, std::string pic, float anchorX, float anchorY, float locationX, float locationY, float width, float height)
{
	Sprite* sp = Sprite::create(pic);//创建精灵
	Size size=sp->getContentSize();//获取精灵的尺寸
	float scaleX=width/size.width;	//计算出精灵X方向缩放比
	float scaleY=height/size.height;//计算出精灵Y方向缩放比
	sp->setScaleX(scaleX);//设置精灵X方向缩放比
	sp->setScaleY(scaleY);//设置精灵Y方向缩放比
	sp->setAnchorPoint(Point(anchorX,anchorY));//设置锚点
	sp->setPosition(Point(locationX,locationY));//设置精灵的位置
	sp->setUserData(id);
	return sp;
}
void SpriteManager::backgroundRoll()//背景滚动方法
{

	//===背景===
	Sprite* bg = createStaticSprite(new std::string("bg"), "pic/game_bg_01_001-hd.png", 0.0f, 0.0f, 0, 0, WIDTH, HEIGHT);//创建背景精灵
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


	Sprite* bg1 = createStaticSprite(new std::string("bg1"), "pic/game_bg_01_001-hd.png", 0.0f, 0.0f, WIDTH, 0, WIDTH, HEIGHT);//创建背景精灵
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

	//背景 滚屏代码
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
void SpriteManager::createSiJiao()//创建四周的图片
{
	//左下角 的图片
	createSprite(NULL, Rect(825,386,897-825,457-386), batchNode, 0.0f, 0.0f, 0, 0, 120, 120, GroundZOrder+1);

	//右下角 的图片
	Sprite* sp = createSprite(NULL, Rect(825,386,897-825,457-386), batchNode, 0.0f, 0.0f, WIDTH-120, 0, 120, 120, GroundZOrder+1);
	sp->setFlippedX(true);

	//左上角 的图片
	sp = createSprite(NULL, Rect(825,386,897-825,457-386), batchNode, 0.0f, 0.0f, 0, HEIGHT-120, 120, 120, GroundZOrder+1);
	sp->setFlippedY(true);

	//右上角 的图片
	sp = createSprite(NULL, Rect(825,386,897-825,457-386), batchNode, 0.0f, 0.0f, WIDTH-120, HEIGHT-120, 120, 120, GroundZOrder+1);
	sp->setFlippedX(true);
	sp->setFlippedY(true);
}
void SpriteManager::createGround()//创建五个地面并让其自动向左移动
{
	//创建五个地面  并不停地移动
	tb[0]=new RectBarrier(NULL,layer,Rect(129,685,243-129,802-685),WIDTH/8,HEIGHT/8, WIDTH/4, HEIGHT/4, GroundZOrder);//创建矩形
	tb[0]->sp->setColor(Color3B(0,67,169));
	tb[0]->sp->runAction(
			RepeatForever::create(
					Sequence::create(
							MoveBy::create(0.5,Point(-WIDTH/4,0)),
							Place::create(Point(WIDTH/8,HEIGHT/8)),
							NULL)));

	tb[1]=new RectBarrier(NULL,layer,Rect(129,685,243-129,802-685),WIDTH/8*3,HEIGHT/8, WIDTH/4, HEIGHT/4, GroundZOrder);//创建矩形
	tb[1]->sp->setColor(Color3B(0,67,169));
	tb[1]->sp->runAction(
				RepeatForever::create(
						Sequence::create(
								MoveBy::create(0.5,Point(-WIDTH/4,0)),
								Place::create(Point(WIDTH/8*3,HEIGHT/8)),
								NULL)));

	tb[2]=new RectBarrier(NULL,layer,Rect(129,685,243-129,802-685),WIDTH/8*5,HEIGHT/8, WIDTH/4, HEIGHT/4, GroundZOrder);//创建矩形
	tb[2]->sp->setColor(Color3B(0,67,169));
	tb[2]->sp->runAction(
				RepeatForever::create(
						Sequence::create(
								MoveBy::create(0.5,Point(-WIDTH/4,0)),
								Place::create(Point(WIDTH/8*5,HEIGHT/8)),
								NULL)));

	tb[3]=new RectBarrier(NULL,layer,Rect(129,685,243-129,802-685),WIDTH/8*7,HEIGHT/8, WIDTH/4, HEIGHT/4, GroundZOrder);//创建矩形
	tb[3]->sp->setColor(Color3B(0,67,169));
	tb[3]->sp->runAction(
				RepeatForever::create(
						Sequence::create(
								MoveBy::create(0.5,Point(-WIDTH/4,0)),
								Place::create(Point(WIDTH/8*7,HEIGHT/8)),
								NULL)));

	tb[4]=new RectBarrier(NULL,layer,Rect(129,685,243-129,802-685),WIDTH/8*9,HEIGHT/8, WIDTH/4, HEIGHT/4, GroundZOrder);//创建矩形
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
	director->pause();//暂停各种运动

	createSprite(NULL, Rect(419,652,619-419,708-652), batchNode, 0.5, 0.5, WIDTH/2, HEIGHT/2, 500, 200, PauseBGZOrder+1);

	//左上角 的返回键按钮
	allSp[23] = createSprite(NULL, Rect(871,154,910-871,186-154), batchNode, 0.5f, 0.5f, 45, 540-37, 63, 55, GoBackZOrder);
	allSp[23]->setRotation(-90.0f);
	AddEventListenerSprite(allSp[23]);
}
