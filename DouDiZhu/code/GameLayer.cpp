#include "GameLayer.h"
#include "AppMacros.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "math.h"
#include "PuKe.h"
#include "BNSocketUtil.h"
#include "Constant.h"
#include <string>
#include <stdio.h>
using namespace cocos2d;
using namespace ui;
using namespace std;



bool GameLayer::init()
{
	//调用父类的初始化
    if ( !Layer::init() )
    {
        return false;
    }
    //调用 addSprite方法
    addSprite();
    //调用 addLabel方法
    addLabel();
    //添加定时回调
    addUpdate();
    //添加菜单项
    addMenuItem();
    //将出牌等信息绘制出来并隐藏
    playGameBtn();
    //初始化牌
    initPuKe();
    //预加载音效和音乐
    preloadMuiscOrEffect();
    
	//touch listen
	//创建一个单点触摸监听
	auto listener = EventListenerTouchOneByOne::create();
	//设置下传触摸
	listener->setSwallowTouches(true);
	//开始触摸时回调onTouchBegan方法
	listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
	//添加到监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
    
    if(Constant::musicFlag)
    {
        if(random()>1)
        {
        	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic
        	(
             (SOUND_PATH+string("MusicEx_Normal.ogg")).c_str(),
             true
             );
        }else{
        	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic
        	(
             (SOUND_PATH+string("MusicEx_Normal2.ogg")).c_str(),
             true
             );
        }
    }
    //初始化
    tempCardVector0 = new std::vector<Sprite*>();
    tempCardVector1 = new std::vector<Sprite*>();
    tempCardVector2 = new std::vector<Sprite*>();
    vecPuKe = new std::vector<Sprite*>();
    
    return true;
}
//添加菜单项
void GameLayer::addMenuItem()
{
    //exit
    MenuItemImage *exitItem = MenuItemImage::create
    (
     PIC_PATH+string("game_exit.png"),
     PIC_PATH+string("game_exit.png"),
     CC_CALLBACK_1(GameLayer::menuExitCallback, this)
     );
    //设置关闭菜单项的位置
    exitItem->setPosition(Point(230,490));
    Menu *exitMenu = Menu::create(exitItem, NULL);
    exitMenu->setPosition(Point::ZERO);
    this->addChild(exitMenu,BTN_LEVEL);
    //setting
    MenuItemImage *setItem = MenuItemImage::create
    (
     PIC_PATH+string("game_setting.png"),
     PIC_PATH+string("game_setting.png"),
     CC_CALLBACK_1(GameLayer::menuSetCallback, this)
     );
    //设置菜单项的位置
    setItem->setPosition(Point(320,490));
    Menu *setMenu = Menu::create(setItem, NULL);
    setMenu->setPosition(Point::ZERO);
    this->addChild(setMenu,BTN_LEVEL);
    
    //ready
    MenuItemImage *readyItem = MenuItemImage::create
    (
     PIC_PATH+string("big_green_btn.png"),
     PIC_PATH+string("big_green_btn_down.png"),
     CC_CALLBACK_1(GameLayer::menuReadyCallback, this)
     );
    //设置菜单项的位置
    readyItem->setPosition(Point(480,240));
    readyMenu = Menu::create(readyItem, NULL);
    readyMenu->setPosition(Point::ZERO);
    this->addChild(readyMenu,BTN_LEVEL);
    
    //叫地主，抢地主按钮
	MenuItemImage *orderItem = MenuItemImage::create
	(
     PIC_PATH+string("message_jiao.png"),
     PIC_PATH+string("message_jiao.png"),
     CC_CALLBACK_1(GameLayer::menuOrderCallback, this)
     );
	//设置菜单项的位置
	orderItem->setPosition(Point(540,220));
	orderMenu = Menu::create(orderItem, NULL);
	orderMenu->setPosition(Point::ZERO);
	this->addChild(orderMenu,BTN_LEVEL);
	orderMenu->setVisible(false);
	//不叫
	MenuItemImage *noOrderItem = MenuItemImage::create
	(
     PIC_PATH+string("message_bu.png"),
     PIC_PATH+string("message_bu.png"),
     CC_CALLBACK_1(GameLayer::menuNoOrderCallback, this)
     );
	//设置菜单项的位置
	noOrderItem->setPosition(Point(380,220));
	noOrderMenu = Menu::create(noOrderItem, NULL);
	noOrderMenu->setPosition(Point::ZERO);
	this->addChild(noOrderMenu,BTN_LEVEL);
	noOrderMenu->setVisible(false);
    
	//抢地主
	MenuItemImage *qdzItem = MenuItemImage::create
	(
     PIC_PATH+string("message_qiang.png"),
     PIC_PATH+string("message_qiang.png"),
     CC_CALLBACK_1(GameLayer::menuQiangCallback, this)
     );
	//设置关闭菜单项的位置
	qdzItem->setPosition(Point(540,220));
	qdzMenu = Menu::create(qdzItem, NULL);
	qdzMenu->setPosition(Point::ZERO);
	this->addChild(qdzMenu,BTN_LEVEL);
	qdzMenu->setVisible(false);
	//不抢
	MenuItemImage *bqItem = MenuItemImage::create
	(
     PIC_PATH+string("message_buQiang.png"),
     PIC_PATH+string("message_buQiang.png"),
     CC_CALLBACK_1(GameLayer::menuNoQiangCallback, this)
     );
	//设置菜单项的位置
	bqItem->setPosition(Point(380,220));
	bqMenu = Menu::create(bqItem, NULL);
	bqMenu->setPosition(Point::ZERO);
	this->addChild(bqMenu,BTN_LEVEL);
	bqMenu->setVisible(false);
}
//开启定时回调工作
void GameLayer::addUpdate()
{
	//开启绘制信息的方法
	schedule(schedule_selector(GameLayer::updateDrawOther), 0.1f);
    
	//画自己的牌
	schedule(schedule_selector(GameLayer::updatePuke), 0.1f);
	//获取系统时间
	schedule(schedule_selector(GameLayer::getSystemTime), 1.0f);
	//播放出牌音效
	schedule(schedule_selector(GameLayer::updatePlayEffect), 0.2f);
}

void GameLayer::updatePuke(float dt)		//更新扑克牌
{
	int lastId=(Constant::whoFlag==0)?2:Constant::whoFlag-1;
	if(lastId==Constant::playerId&&Constant::drawCards)				//更新上家牌
	{
        Constant::drawCards=false;
        if(!vecPuKe->empty())
        {
            vecPuKe->clear();
        }
        //将剩余的牌存进vector中
        for(int k=0;k<Constant::pukeRemainNumber;k++)
        {
            vecPuKe->push_back(puke[Constant::PUKEARRAY[k]]->pukeSprite);
        }
        //对剩余牌进行排序
        if(!vecPuKe->empty())
        {
            std::vector<Sprite* >::iterator tempLastPuKe;
            
            int lastSize = vecPuKe->size()/2;
            int lastLiftX =  490-lastSize*40;//用于从左侧排序的最远距离
            int lastMid=0;
            for(tempLastPuKe=vecPuKe->begin();tempLastPuKe!=vecPuKe->end();++tempLastPuKe)
            {
                (*tempLastPuKe)->setPosition(Point(lastLiftX+40*lastMid++,85));
            }
        }
	}
	if(Constant::drawTiShi)						//提示
	{
		Constant::drawTiShi=false;
		Constant::upCardsCount=0;
		int lastSize = Constant::playerCardsCount/2;
		int lastLiftX =  490-lastSize*40;//用于从左侧排序的最远距离
		for(int j=0;j<Constant::playerCardsCount;j++)
		{
			if(Constant::upCards[Constant::PUKEARRAY[j]]==1)
			{
				//获取扑克的位置LL
				puke[Constant::PUKEARRAY[j]]->pukeSprite->setPosition(Point(lastLiftX+40*j,103));
				Constant::upCardsCount++;
			}else
			{
				puke[Constant::PUKEARRAY[j]]->pukeSprite->setPosition(Point(lastLiftX+40*j,85));
			}
		}
		resetMenu->setVisible(true);
		chuMenu->setVisible(true);
	}
    if(Constant::upCardsCount==0)
	{
		resetMenu->setVisible(false);
		chuMenu->setVisible(false);
	}
	if(Constant::whoFlag==Constant::playerId&&Constant::drawAlreadyCard)		//当有牌权时，出牌的个数不为空时，则清空已出列表	不显示任何东西
	{
		buchu[0]->setVisible(false);
		for(int k=0;k<Constant::playerLength;k++)
		{
			this->removeChild(player[k]->pukeSprite);
		}
		Constant::playerLength=0;
		Constant::playerCardDraw=true;
	}
	if(Constant::whoFlag!=Constant::playerId&&Constant::drawAlreadyCard)									//当没有牌权时
	{
		if(Constant::playerLength==0&&Constant::landlordCount>6)//如果已出列表为空时且没有当前牌权时，显示不出
		{
			buchu[0]->setVisible(true);
		}
        
		if(Constant::playerLength!=0&&Constant::playerCardDraw)			//当已出列表不为空时且当前没有牌权是 显示已出的牌
		{
			buchu[0]->setVisible(false);
			int length=Constant::playerLength;
			int zx=490-(length-1)/2*20;
			Texture2D* tt2d = Director::getInstance()->getTextureCache()->addImage(PIC_PATH+string("puke_whole.png"));
			for(int k=0;k<length;k++)
			{
                int col=8-Constant::playerCards[k]%9;
                int row=Constant::playerCards[k]/9;
                Rect r=Rect(72*col,108*row,72,108);
                player[k]=new PuKe(tt2d,k,r,zx+k*20,240);
                player[k]->refresh();
                player[k]->pukeSprite->setScale(0.9);//放大
                player[k]->pukeSprite->retain();
                
                this->addChild(player[k]->pukeSprite,k);
			}
			Constant::playerCardDraw=false;
		}
	}
    
	if(Constant::whoFlag==Constant::lastPlayerId&&Constant::drawAlreadyCard)
	{
		buchu[2]->setVisible(false);
		for(int k=0;k<Constant::lastPlayerLength;k++)
		{
			this->removeChild(last[k]->pukeSprite);
		}
		Constant::lastPlayerLength=0;
		Constant::lastPlayerCardDraw=true;
	}
    
	if(Constant::whoFlag!=Constant::lastPlayerId&&Constant::drawAlreadyCard)									//当没有牌权时
	{
		if(Constant::lastPlayerLength==0&&Constant::landlordCount>6)//如果已出列表为空时且没有当前牌权时，显示不出
		{
			buchu[2]->setVisible(true);
		}
        
		if(Constant::lastPlayerLength!=0&&Constant::lastPlayerCardDraw)			//当已出列表不为空时且当前没有牌权是 显示已出的牌
		{
			buchu[2]->setVisible(false);
			int length=Constant::lastPlayerLength;
			Texture2D* tt2d = Director::getInstance()->getTextureCache()->addImage(PIC_PATH+string("puke_whole.png"));
			for(int k=0;k<length;k++)
			{
                int col=8-Constant::lastPlayerCards[k]%9;
                int row=Constant::lastPlayerCards[k]/9;
                
                Rect r=Rect(72*col,108*row,72,108);
                last[k]=new PuKe(tt2d,k,r,160+k*20,380);
                last[k]->refresh();
                last[k]->pukeSprite->setScale(0.9);//放大
                last[k]->pukeSprite->retain();
                
                this->addChild(last[k]->pukeSprite,k);
			}
			Constant::lastPlayerCardDraw=false;
		}
	}
    
    
	if(Constant::whoFlag==Constant::nextPlayerId&&Constant::drawAlreadyCard)
	{
		buchu[1]->setVisible(false);
		for(int k=0;k<Constant::nextPlayerLength;k++)
		{
			this->removeChild(next[k]->pukeSprite);
		}
		Constant::nextPlayerLength=0;
		Constant::nextPlayerCardDraw=true;
	}
    
	if(Constant::whoFlag!=Constant::nextPlayerId&&Constant::drawAlreadyCard)									//当没有牌权时
	{
		if(Constant::nextPlayerLength==0&&Constant::landlordCount>6)//如果已出列表为空时且没有当前牌权时，显示不出
		{
			buchu[1]->setVisible(true);
		}
        
		if(Constant::nextPlayerLength!=0&&Constant::nextPlayerCardDraw)			//当已出列表不为空时且当前没有牌权是 显示已出的牌
		{
			buchu[1]->setVisible(false);
			int length=Constant::nextPlayerLength;
			Texture2D* tt2d = Director::getInstance()->getTextureCache()->addImage(PIC_PATH+string("puke_whole.png"));
			int zx=800-(length-1)*20;
			for(int k=0;k<length;k++)
			{
                int col=8-Constant::nextPlayerCards[k]%9;
                int row=Constant::nextPlayerCards[k]/9;
                
                Rect r=Rect(72*col,108*row,72,108);
                next[k]=new PuKe(tt2d,k,r,zx+k*20,380);
                next[k]->refresh();
                next[k]->pukeSprite->setScale(0.9);//放大
                next[k]->pukeSprite->retain();
                
                this->addChild(next[k]->pukeSprite,k);
			}
			Constant::nextPlayerCardDraw=false;
		}
	}
	Constant::drawAlreadyCard=false;				//画已出的牌
    
	if(Constant::drawVictory)						//画出
	{
        
		Constant::drawVictory=false;
		int spriteVictory=-1;						//胜利 0地主负，1地主赢，2农民负，3农民赢
		if(Constant::playerId==Constant::whoIsLandlord)
		{
			if(Constant::victory==1)
			{
				spriteVictory=1;
				CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic
				(
                 (SOUND_PATH+string("MusicEx_Win.ogg")).c_str()
                 );
			}
			else if(Constant::victory==0)
			{
				spriteVictory=0;
				CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic
				(
                 (SOUND_PATH+string("MusicEx_Lose.ogg")).c_str()
                 );
			}
		}else
		{
			if(Constant::victory==1)
			{
				spriteVictory=2;
				CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic
				(
                 (SOUND_PATH+string("MusicEx_Lose.ogg")).c_str()
                 );
			}
			else if(Constant::victory==0)
			{
				spriteVictory=3;
				CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic
				(
                 (SOUND_PATH+string("MusicEx_Win.ogg")).c_str()
                 );
			}
		}
		gameOverSprite[spriteVictory]=Sprite::create((PIC_PATH+StringUtils::format("text_%d.png",spriteVictory)).c_str());
		gameOverSprite[spriteVictory]->setPosition(Point(480,600));
		this->addChild(gameOverSprite[spriteVictory],100);
		gameOverSprite[spriteVictory]->runAction(Sequence::create(
                                                                  MoveTo::create(4.0,Point(480,300)),
                                                                  CallFuncN::create(CC_CALLBACK_1(GameLayer::gameOver,this)),
                                                                  NULL
                                                                  ));
	}
}
//添加LabelAtlas，用于显示倍数、其他玩家手头牌数
void GameLayer::addLabel()
{
	//当前倍数
    bLabelAtlas = LabelAtlas::create("15",(PIC_PATH+string("poker_number.png")),25,32,'0');//创建一个LabelAtlas对象
	bLabelAtlas->setAnchorPoint(Point(1,0));//设置LabelAtlas对象锚点
    bLabelAtlas->setPosition(Point(690,475));
	this->addChild(bLabelAtlas,PROP_LEVEL);			//将LabelAtlas对象添加到布景中
	//===========手头剩余牌数===========
	lastLabelAtlas = LabelAtlas::create("0",(PIC_PATH+string("poker_number.png")),25,32,'0');//创建一个LabelAtlas对象
	lastLabelAtlas->setPosition(Point(41,360));
	this->addChild(lastLabelAtlas,PROP_LEVEL+1);			//将LabelAtlas对象添加到布景中
	//
	nextLabelAtlas = LabelAtlas::create("0",(PIC_PATH+string("poker_number.png")),25,32,'0');//创建一个LabelAtlas对象
	nextLabelAtlas->setPosition(Point(871,360));
	this->addChild(nextLabelAtlas,PROP_LEVEL+1);			//将LabelAtlas对象添加到布景中
}
//添加精灵
void GameLayer::addSprite()
{
	//创建一个精灵对象，包含background.png图片
	Sprite  *background = Sprite::create(PIC_PATH+string("background.png"));
	background->setPosition(Point(480,270));
	//将精灵添加到布景中
	this->addChild(background, BACKGROUD_LEVEL);
	//添加玩家图标以及边框
	for(int i=0;i<3;i++)
	{
		unKnow[i] = Sprite::create(PIC_PATH+string("logo_unknown.png"));
		actKnow[i] = Sprite::create(PIC_PATH+string("logo_active.png"));//活动框此时有牌权
		deKnow[i] = Sprite::create(PIC_PATH+string("logo_deactive.png"));//平常标志框
		dizhuHeadImage[i]=Sprite::create(PIC_PATH+string("logo_dizhu.png"));//地主头像，农民头像
		nongminHeadImage[i]=Sprite::create(PIC_PATH+string("logo_nongmin.png"));
		if(i!=0)
		{
			unKnow[i]->setPosition(Point(60+830*(2-i),490));
			actKnow[i]->setPosition(Point(60+830*(2-i),490));
			deKnow[i]->setPosition(Point(60+830*(2-i),490));
			dizhuHeadImage[i]->setPosition(Point(60+830*(2-i),490));
			nongminHeadImage[i]->setPosition(Point(60+830*(2-i),490));
		}
		else
		{
			unKnow[i]->setPosition(Point(60,235));
			actKnow[i]->setPosition(Point(60,235));
			deKnow[i]->setPosition(Point(60,235));
			dizhuHeadImage[i]->setPosition(Point(60,235));
			nongminHeadImage[i]->setPosition(Point(60,235));
		}
		unKnow[i]->setVisible(false);
		actKnow[i]->setVisible(false);
		deKnow[i]->setVisible(false);
		dizhuHeadImage[i]->setVisible(false);
		nongminHeadImage[i]->setVisible(false);
		this->addChild(unKnow[i], PROP_LEVEL);
		this->addChild(actKnow[i], BTN_LEVEL+2);
		this->addChild(deKnow[i], BTN_LEVEL+1);
		this->addChild(dizhuHeadImage[i],BTN_LEVEL+1);
		this->addChild(nongminHeadImage[i],BTN_LEVEL+1);
	}
	//背景牌
	for(int i=0;i<5;i++)
	{
		poke[i] = Sprite::create(PIC_PATH+string("poke_back_header.png"));
		if(i<3)//0,1,2用于剩余三张牌的背景图
		{
			poke[i]->setPosition(Point(400+i*75,490));
			poke[i]->setScale(0.8);
			this->addChild(poke[i],PROP_LEVEL);
		}else{//上一玩家与下一玩家的背景图
			poke[i]->setPosition(Point(60+(i-3)*830,380));
			poke[i]->setScale(1.1);
            
			this->addChild(poke[i], PROP_LEVEL);
		}
        
	}
	//ok手势，准备标志
	for(int i=0;i<3;i++)
	{
		ready[i] = Sprite::create(PIC_PATH+string("ready.png"));
		if(i!=0)
		{
			ready[i]->setPosition(Point(130+690*(2-i),490));
		}
		else
		{
			ready[i]->setPosition(Point(60,155));
		}
		this->addChild(ready[i], PROP_LEVEL);
		ready[i]->setVisible(false);
	}
    
	//不出字样
	for(int i=0;i<3;i++)
	{
		buchu[i]=Sprite::create(PIC_PATH+string("buchu.png"));
		if(i==0)
		{
			buchu[i]->setPosition(Point(450,200));
		}else
		{
			buchu[i]->setPosition(Point(160+645*(2-i),380));
		}
		this->addChild(buchu[i],PROP_LEVEL);
		buchu[i]->setVisible(false);
	}
	//倍数图标
	Sprite *logo_bei = Sprite::create(PIC_PATH+string("game_bei.png"));
	logo_bei->setPosition(Point(735,490));
	this->addChild(logo_bei, PROP_LEVEL);
	//*2倍，用于叫地主和抢地主的显示
	bei2 = Sprite::create(PIC_PATH+string("cha2.png"));
	bei2->setPosition(Point(480,310));
	this->addChild(bei2, PROP_LEVEL);
	bei2->setVisible(false);
    
	//==================创建抢地主等四个字样
	for(int i=0;i<5;i++)
	{
		if(i!=4)
		{
			//0字样
			playerSprite[i] = Sprite::create((PIC_PATH+StringUtils::format("message%d.png",i)).c_str());
			playerSprite[i]->setPosition(Point(480,200));
			this->addChild(playerSprite[i],PROP_LEVEL);
			//1字样
			nextPlayerSprite[i] = Sprite::create((PIC_PATH+StringUtils::format("message%d.png",i)).c_str());
			nextPlayerSprite[i]->setPosition(Point(765,380));
			this->addChild(nextPlayerSprite[i],PROP_LEVEL);
			//2字样  转化为string类型并转化成字节型数组
			lastPlayerSprite[i] = Sprite::create((PIC_PATH+StringUtils::format("message%d.png",i)).c_str());
			lastPlayerSprite[i]->setPosition(Point(190,380));
			this->addChild(lastPlayerSprite[i],PROP_LEVEL);
		}
		else
		{
			//0
			playerSprite[i] = Sprite::create();
			this->addChild(playerSprite[i],PROP_LEVEL);
			//1
			nextPlayerSprite[i] = Sprite::create();
			this->addChild(nextPlayerSprite[i],PROP_LEVEL);
			//2
			lastPlayerSprite[i] = Sprite::create();
			this->addChild(lastPlayerSprite[i],PROP_LEVEL);
		}
		playerSprite[i]->setVisible(false);
		nextPlayerSprite[i]->setVisible(false);
		lastPlayerSprite[i]->setVisible(false);
	}
    
	Sprite *getTimeSprite = Sprite::create(PIC_PATH+string("get_time.png"));
	getTimeSprite->setPosition(Point(900,290));
	this->addChild(getTimeSprite,PROP_LEVEL);
    
    //显示接收信息的标签
	timeLabel=LabelTTF::create("","Arial",28);
    //设置标签字体的颜色
	timeLabel->setFontFillColor(Color3B::WHITE);
	timeLabel->setPosition(Vec2(900,290));
    this->addChild(timeLabel,30);
    
    //王炸精灵
    wangSprite=Sprite::create();
	wangSprite->setPosition(Point(0,0));
	this->addChild(wangSprite,100);
    
	wangDropSprite=Sprite::create(ANIM_PATH+string("bomb_f.png"));
	wangDropSprite->setPosition(Point(480,600));
	this->addChild(wangDropSprite,PROP_LEVEL);
	wangDropSprite->setScale(1.5);
	wangDropSprite->setVisible(false);
    
	//炸弹
	zhaSprite=Sprite::create();
	zhaSprite->setPosition(Point(0,0));
	this->addChild(zhaSprite,100);
    
	zhaDropSprite=Sprite::create(ANIM_PATH+string("bomb1.png"));
	zhaDropSprite->setPosition(Point(480,600));
	this->addChild(zhaDropSprite,PROP_LEVEL);
	zhaDropSprite->setScale(1.5);
	zhaDropSprite->setVisible(false);
    
	//飞机
	planeSprite = Sprite::create(PIC_PATH+string("plane.png"));
	planeSprite->setPosition(Point(1000,300));
	this->addChild(planeSprite,PROP_LEVEL);
	planeSprite->setVisible(false);
}

//定时回调-绘制其他玩家的信息
void GameLayer::updateDrawOther(float dt)
{
	//没有玩家进入，当前玩家为第一个
	if(Constant::playerCount==1&&Constant::drawLogo)
	{
		unKnow[0]->setVisible(true);
		deKnow[0]->setVisible(true);
	}
	else if(Constant::playerCount==2&&Constant::drawLogo)
	{
		if(Constant::playerId==0)
		{
			//下一家图像
			unKnow[1]->setVisible(true);
			deKnow[1]->setVisible(true);
			//当前玩家图像
			unKnow[0]->setVisible(true);
			deKnow[0]->setVisible(true);
		}
		else if(Constant::playerId==1)
		{
			//上一家图像
			unKnow[2]->setVisible(true);
			deKnow[2]->setVisible(true);
			//当前玩家图像
			unKnow[0]->setVisible(true);
			deKnow[0]->setVisible(true);
		}
	}
	else if(Constant::playerCount==3&&Constant::drawLogo)
	{
		//下一家图像
        deKnow[1]->setVisible(true);
		unKnow[1]->setVisible(true);
		//上一家图像
        deKnow[2]->setVisible(true);
		unKnow[2]->setVisible(true);
		//当前玩家图像
        deKnow[0]->setVisible(true);
		unKnow[0]->setVisible(true);
		Constant::drawLogo=false;
	}
	//绘制手势OK，判断是否有玩家准备
	if(Constant::readyNum!=0&&!Constant::readyFlag)
	{
		Constant::readyNum=0;
		if(Constant::playerReady==1)
		{
			ready[0]->setVisible(true);
		}
		if(Constant::lastPlayerReady==1)
		{
			ready[2]->setVisible(true);
		}
		if(Constant::nextPlayerReady==1)
		{
			ready[1]->setVisible(true);
		}
	}
	//将ok手势设为不可见
	if(Constant::readyFlag)
	{
		Constant::readyFlag=false;
		Constant::readyNum=0;
		for(int i=0;i<3;i++)
		{
			ready[i]->setVisible(false);
		}
	}
	//地主方框,有牌权的玩家才能显示叫地主
	if(Constant::menuItem)
	{
		Constant::menuItem=false;
		if(Constant::whoFlag==Constant::playerId)
		{
			if(Constant::landlordCount<5)
			{
				//判断初次叫还是非初次，若初次则为叫地主和不叫，否则为抢地主和不抢
				if(Constant::landlordCount==1)//叫地主
				{
					addOrderOrNo();
				}
				else if(Constant::landlordCount!=1)//抢地主
				{
					addQiangOrNo();
				}
			}
			else if(Constant::landlordCount==5&&Constant::whoFlag==Constant::playerId)//开始游戏后第一轮出牌
			{
				resetSprite->setVisible(true);//灰色重选
				chuSprite->setVisible(true);//灰色出牌
				tiShiMenu->setVisible(true);
			}
			else if(Constant::landlordCount>5&&Constant::whoFlag==Constant::playerId)
			{
				resetSprite->setVisible(true);//灰色重选
				chuSprite->setVisible(true);//灰色出牌
				buChuMenu->setVisible(true);
			}
		}
	}
    if(Constant::drawAct)
    {
        //将上一个金框隐藏
        for(int i=0;i<3;i++)
        {
            actKnow[Constant::oldGoldFlag]->setVisible(false);
        }
        //将当前金框设为上一个金框
        int landlord;
        if(Constant::whoFlag==Constant::playerId)
        {
            landlord=0;
        }else if(Constant::whoFlag==Constant::lastPlayerId)
        {
            landlord=2;
        }else if(Constant::whoFlag==Constant::nextPlayerId)
        {
            landlord=1;
        }
        Constant::oldGoldFlag =landlord;
        //显示当前有牌权玩家的金框
        actKnow[Constant::oldGoldFlag]->setVisible(true);
    }

	//绘制出牌菜单项，当接收到0即不能出牌时则将其隐藏否则绘制出菜单项
	if(Constant::isDrawChuPai&&Constant::whoFlag==Constant::playerId)
	{
		Constant::isDrawChuPai=false;
		if(Constant::isCanChuPai==1&&Constant::upCardsCount!=0)	//出牌
		{
			chuMenu->setVisible(true);
			chuSprite->setVisible(false);
			Constant::isCanChuPai=-1;
		}
		else if(Constant::isCanChuPai==0||Constant::upCardsCount==0)
		{
			chuMenu->setVisible(false);
			chuSprite->setVisible(true);
		}
        
		if(Constant::isBuChu==0||(Constant::lastPlayerLength==0&&Constant::nextPlayerLength==0))			//不出按钮
		{
			buChuMenu->setVisible(false);
		}else{
			buChuMenu->setVisible(true);
		}
	}
	if(Constant::isDrawReset)
	{
		Constant::isDrawReset=false;
		if(Constant::upCardsCount!=0)		//重选按钮
		{
			resetMenu->setVisible(true);
			resetSprite->setVisible(false);
		}else{
			resetMenu->setVisible(false);
			resetSprite->setVisible(true);
		}
		tiShiMenu->setVisible(true);
	}
	//其他玩家不绘制出牌菜单项
	if(Constant::whoFlag!=Constant::playerId)
	{
		chuMenu->setVisible(false);
		resetMenu->setVisible(false);
		buChuMenu->setVisible(false);
		tiShiMenu->setVisible(false);
		chuSprite->setVisible(false);
		resetSprite->setVisible(false);
	}
	//如果服务器已经发完牌
	if(Constant::pukeFlag)
	{
		Constant::pukeFlag=false;
		schedule(schedule_selector(GameLayer::updatePuke), 0.1f);
		//设置定时回调指定方法干活
		auto director = Director::getInstance();
		auto sched = director->getScheduler();
        
		//定时回调update_puke  17次，间隔为0.2秒，延迟0
		sched->schedule(SEL_SCHEDULE(&GameLayer::update_puke),this,0.13,16,0.1,false);
	}
	//如果到最后，已经产生地主,并且本机为地主
	if(Constant::whoIsLandlord==Constant::playerId&&Constant::landlordHadPuke)
	{
		//首先删掉之前的17张牌，以及背景牌
		for(int j=0;j<17;j++)
		{
			this->removeChild(puke[Constant::PUKEARRAY[j]]->pukeSprite);
			this->removeChild(mask[Constant::PUKEARRAY[j]]);
		}
        
		/*
		 * 重新绘制地主20张牌
		 * 首先重新给数组赋值
		 * 开始绘制
		 */
		for(int i=0;i<20;i++)
		{
			Constant::PUKEARRAY[i]=Constant::tempPUKE[i];
            
			//设置扑克背景框
			mask[Constant::PUKEARRAY[i]] = Sprite::create(PIC_PATH+string("poke_gb_mask.png"));
			mask[Constant::PUKEARRAY[i]]->setPosition(90+iCount*40,85);
			this->addChild(mask[Constant::PUKEARRAY[i]],i+1);
			mask[Constant::PUKEARRAY[i]]->setVisible(false);
			//扑克
			(puke[Constant::PUKEARRAY[i]]->pukeSprite)->setPosition(Point(90+i*40,85));
			this->addChild(puke[Constant::PUKEARRAY[i]]->pukeSprite,i);
		}
		if(Constant::effectFlag)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
			(
             (SOUND_PATH+string("Special_Multiply.mp3")).c_str()
             );
		}
	}
	//绘制背景牌
	if(Constant::landlordHadPuke)
	{
		Constant::landlordHadPuke=false;
		//设置背景图不可见,删除
		for(int j=0;j<3;j++)
		{
			this->removeChild(poke[j]);
		}
		//创建旋转开始
		createRotate();
	}
	//绘制倍数
	if(Constant::beiNum!=Constant::oldBeiNum&&Constant::beiNum!=15)
	{
		Constant::oldBeiNum=Constant::beiNum;
        
		//转化为string类型
		string beiStr =StringUtils::toString(Constant::beiNum);
		//显示当前倍数
		bLabelAtlas->setString(beiStr);
		bLabelAtlas->setString(beiStr);
		//设置倍数*2
		setBeiMove();
		if(Constant::effectFlag)
		{
			//倍数音效
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
			(
             (SOUND_PATH+string("Special_Multiply.mp3")).c_str()
             );
		}
	}
	//绘制抢地主、不抢、叫地主、不叫字样是否可见,
	if(Constant::landlordListNum==3)
	{
		Constant::landlordListNum=0;
		for(int i=0;i<3;i++)
		{
			//首先将原来的隐藏
			playerSprite[i]->setVisible(false);
			nextPlayerSprite[i]->setVisible(false);
			lastPlayerSprite[i]->setVisible(false);
            
			//隐藏之后重新画
			if(Constant::playerId==i)
			{
				playerSprite[Constant::landlordList[i]]->setVisible(true);
			}
			else if(Constant::nextPlayerId==i)
			{
				nextPlayerSprite[Constant::landlordList[i]]->setVisible(true);
			}
			else if(Constant::lastPlayerId==i)
			{
				lastPlayerSprite[Constant::landlordList[i]]->setVisible(true);
			}
            
			if(Constant::effectFlag)
			{
				if(Constant::whoFlag==0)
				{
					Constant::soundType = Constant::landlordList[2];
				}
				else if(Constant::whoFlag==1)
				{
					Constant::soundType = Constant::landlordList[0];
				}
				else if(Constant::whoFlag==2)
				{
					Constant::soundType = Constant::landlordList[1];
				}
				playOrderOrRob();
			}
		}
	}
	//删除抢地主等字样
	if(Constant::clearLandlordState)
	{
		Constant::clearLandlordState=false;
		//收到20张之后则删除
		for(int j=0;j<5;j++)
		{
			this->removeChild(playerSprite[j]);
			this->removeChild(nextPlayerSprite[j]);
			this->removeChild(lastPlayerSprite[j]);
		}
	}
	//绘制玩家手牌
	if(Constant::drawCardsFlag==1)
	{
		Constant::drawCardsFlag =0;
		//转化为string类型
		string nextPukeStr =StringUtils::toString(Constant::nextPlayerCardsCount);
		//显示地主的扑克数目
		nextLabelAtlas->setString(nextPukeStr);
		//2
		string lastPukeStr =StringUtils::toString(Constant::lastPlayerCardsCount);
		//显示地主的扑克数目
		lastLabelAtlas->setString(lastPukeStr);
	}
	//删除叫地主，抢地主menu
	if(Constant::deleteMenu)
	{
		Constant::deleteMenu=false;
        
		this->removeChild(orderMenu);
		this->removeChild(noOrderMenu);
		this->removeChild(qdzMenu);
		this->removeChild(bqMenu);
		for(int i=0;i<3;i++)
		{
			this->removeChild(ready[i]);
			this->removeChild(unKnow[i]);
			this->removeChild(deKnow[i]);
		}
	}
	if(Constant::drawHeadImage)
	{
		Constant::drawHeadImage=false;
		if(Constant::whoFlag==Constant::playerId)
		{
			dizhuHeadImage[0]->setVisible(true);
			nongminHeadImage[1]->setVisible(true);
			nongminHeadImage[2]->setVisible(true);
		}else if(Constant::whoFlag==Constant::lastPlayerId)
		{
			dizhuHeadImage[2]->setVisible(true);
			nongminHeadImage[1]->setVisible(true);
			nongminHeadImage[0]->setVisible(true);
		}else if(Constant::whoFlag==Constant::nextPlayerId)
		{
			dizhuHeadImage[1]->setVisible(true);
			nongminHeadImage[0]->setVisible(true);
			nongminHeadImage[2]->setVisible(true);
		}
	}
}
//定时回调，根据牌的类型播放出牌的音效
void GameLayer::updatePlayEffect(float dt)
{
	if(Constant::isCanPlayEffect&&Constant::effectFlag)
	{
		Constant::isCanPlayEffect=false;
		switch(Constant::EFFECT_ROW_COL[Constant::effectRow][Constant::effectCol])
		{
			case DAN_1:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_1.mp3")).c_str()
                 );
                break;
			case DAN_2:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_2.mp3")).c_str()
                 );
                break;
			case DAN_3:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_3.mp3")).c_str()
                 );
                break;
			case DAN_4:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_4.mp3")).c_str()
                 );
                break;
			case DAN_5:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_5.mp3")).c_str()
                 );
                break;
			case DAN_6:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_6.mp3")).c_str()
                 );
                break;
			case DAN_7:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_7.mp3")).c_str()
                 );
                break;
			case DAN_8:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_8.mp3")).c_str()
                 );
                break;
			case DAN_9:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_9.mp3")).c_str()
                 );
                break;
			case DAN_10:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_10.mp3")).c_str()
                 );
                break;
			case DAN_11:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_11.mp3")).c_str()
                 );
                break;
			case DAN_12:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_12.mp3")).c_str()
                 );
                break;
			case DAN_13:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_13.mp3")).c_str()
                 );
                break;
			case DAN_14:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_14.mp3")).c_str()
                 );
                break;
			case DAN_15:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_15.mp3")).c_str()
                 );
                break;
                
			case DUI_1:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_dui1.mp3")).c_str()
                 );
                break;
			case DUI_2:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_dui2.mp3")).c_str()
                 );
                break;
			case DUI_3:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_dui3.mp3")).c_str()
                 );
                break;
			case DUI_4:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_dui4.mp3")).c_str()
                 );
                break;
			case DUI_5:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_dui5.mp3")).c_str()
                 );
                break;
			case DUI_6:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_dui6.mp3")).c_str()
                 );
                break;
			case DUI_7:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_dui7.mp3")).c_str()
                 );
                break;
			case DUI_8:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_dui8.mp3")).c_str()
                 );
                break;
			case DUI_9:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_dui9.mp3")).c_str()
                 );
                break;
			case DUI_10:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_dui10.mp3")).c_str()
                 );
                break;
			case DUI_11:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_dui11.mp3")).c_str()
                 );
                break;
			case DUI_12:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_dui12.mp3")).c_str()
                 );
                break;
			case DUI_13:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_dui13.mp3")).c_str()
                 );
                break;
                
			case SAN_1:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_tuple1.mp3")).c_str()
                 );
                break;
			case SAN_2:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_tuple2.mp3")).c_str()
                 );
                break;
			case SAN_3:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_tuple3.mp3")).c_str()
                 );
                break;
			case SAN_4:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_tuple4.mp3")).c_str()
                 );
                break;
			case SAN_5:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_tuple5.mp3")).c_str()
                 );
                break;
			case SAN_6:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_tuple6.mp3")).c_str()
                 );
                break;
			case SAN_7:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_tuple7.mp3")).c_str()
                 );
                break;
			case SAN_8:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_tuple8.mp3")).c_str()
                 );
                break;
			case SAN_9:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_tuple9.mp3")).c_str()
                 );
                break;
			case SAN_10:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_tuple10.mp3")).c_str()
                 );
                break;
			case SAN_11:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_tuple11.mp3")).c_str()
                 );
                break;
			case SAN_12:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_tuple12.mp3")).c_str()
                 );
                break;
			case SAN_13:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_tuple13.mp3")).c_str()
                 );
                break;
                
			case FEI_JI:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_feiji.mp3")).c_str()
                 );
				planeSprite->setVisible(true);
				planeSprite->runAction(
                                       Sequence::create(
                                                        MoveTo::create(3.5,Point(-50,300)),
                                                        CallFuncN::create(CC_CALLBACK_0(GameLayer::setPlaneMess,this)),
                                                        NULL
                                                        ));
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Special_plane.mp3")).c_str()
                 );
                break;
			case LIAN_DUI:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_liandui.mp3")).c_str()
                 );
                break;
			case SAN_DAI_YI:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_sandaiyi.mp3")).c_str()
                 );
                break;
			case SAN_DAI_DUI:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_sandaiyidui.mp3")).c_str()
                 );
                break;
			case SHUN_ZI:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_shunzi.mp3")).c_str()
                 );
                break;
			case SI_DAI_ER:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_sidaier.mp3")).c_str()
                 );
                break;
			case SI_DAI_DUI:
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_sidailiangdui.mp3")).c_str()
                 );
                break;
			case WANG_ZHA:
				wangDropSprite->setVisible(true);
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_wangzha.mp3")).c_str()
                 );
				wangDropSprite->runAction(
                                          Sequence::create(
                                                           MoveTo::create(2.0,Point(480,300)),
                                                           CallFuncN::create(CC_CALLBACK_0(GameLayer::initWang,this)),
                                                           NULL
                                                           ));
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Special_Bomb.mp3")).c_str()
                 );
                
                break;
			case ZHA_DAN:
				zhaDropSprite->setVisible(true);
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Man_zhadan.mp3")).c_str()
                 );
				zhaDropSprite->runAction(Sequence::create(
                                                          MoveTo::create(2.0,Point(480,300)),
                                                          CallFuncN::create(CC_CALLBACK_0(GameLayer::initZhaDan,this)),
                                                          NULL
                                                          ));
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+string("Special_Bomb.mp3")).c_str()
                 );
                break;
			case BU_YAO:
				int i = random();
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
				(
                 (SOUND_PATH+StringUtils::format("Man_buyao%d.mp3",i)).c_str()//转化为string类型并转化成字节型数组
                 );
                break;
		}
	}
}
//飞机
void GameLayer::setPlaneMess()
{
	planeSprite->setVisible(false);
	planeSprite->setPosition(Point(1000,300));
}
//王炸 换帧精灵
void GameLayer::initWang()
{
	wangDropSprite->setVisible(false);
	wangDropSprite->setPosition(Point(480,600));
	animZha=false;
	std::string sa[10]=
	{
		ANIM_PATH+string("bomb_fire0.png"),ANIM_PATH+string("bomb_fire1.png"),
		ANIM_PATH+string("bomb_fire2.png"),ANIM_PATH+string("bomb_fire3.png"),
		ANIM_PATH+string("bomb_fire4.png"),ANIM_PATH+string("bomb_fire5.png"),
		ANIM_PATH+string("bomb_fire6.png"),ANIM_PATH+string("bomb_fire7.png"),
		ANIM_PATH+string("bomb_fire8.png"),ANIM_PATH+string("bomb_fire9.png")
	};
    
	Vector<SpriteFrame*> animFrames;
	Animation *anim;
	for(int i=0;i<10;i++)
	{
		SpriteFrameWang[i]=SpriteFrame::create(sa[i],Rect(0,0,181,125),false,Point(0,0),Size(0,0));
		animFrames.pushBack(SpriteFrameWang[i]);
	}
    anim=Animation::createWithSpriteFrames(animFrames,0.4f);
    animateWang=Animate::create(anim);
    animateWang->retain();

    wangSprite->setPosition(Point(480,300));
    wangSprite->setScale(1.2);
    wangSprite->runAction(Sequence::create(
                                    animateWang,
                                        CallFuncN::create(CC_CALLBACK_0(GameLayer::removeAnimSprite, this)),
                                            NULL
                        ));
	
}
//定义炸弹
void GameLayer::initZhaDan()
{
	animZha=true;
	zhaDropSprite->setVisible(false);
	zhaDropSprite->setPosition(Point(480,600));
    
	std::string ss[8]=
	{
		ANIM_PATH+string("bomb2.png"),ANIM_PATH+string("bomb3.png"),
		ANIM_PATH+string("bomb4.png"),ANIM_PATH+string("bomb5.png"),
		ANIM_PATH+string("bomb6.png"),ANIM_PATH+string("bomb7.png"),
		ANIM_PATH+string("bomb8.png"),ANIM_PATH+string("bomb9.png")
	};
    
	Vector<SpriteFrame*> animFrames;
	Animation *anim;
	for(int i=0;i<8;i++)
	{
		SpriteFrameZha[i]=SpriteFrame::create(ss[i],Rect(0,0,95,88),false,Point(0,0),Size(0,0));
		animFrames.pushBack(SpriteFrameZha[i]);
	}
    
    anim=Animation::createWithSpriteFrames(animFrames,0.5f);
    animateZha=Animate::create(anim);
    animateZha->retain();

    zhaSprite->setPosition(Point(480,300));
    zhaSprite->setScale(0.6);
    zhaSprite->runAction(Sequence::create(
                                    animateZha,
                                            CallFuncN::create(CC_CALLBACK_0(GameLayer::removeAnimSprite, this)),
                                                NULL
                        ));
	
}
void GameLayer::removeAnimSprite()
{
	if(animZha)
	{
		this->removeChild(zhaSprite);
		animZha = false;
	}
	else
	{
		this->removeChild(wangSprite);
	}
}
//定时回调，发牌
void GameLayer::update_puke()
{
	if(iCount==17)
	{
		iCount=0;
		Constant::pukeNumber=0;
		Constant::pukeFlag=false;
		this->unschedule(SEL_SCHEDULE(&GameLayer::update_puke));
	}
	//==========显示扑克数量=======
	Constant::pukeNumber++;
	//转化为string类型
	string pukeStr =StringUtils::toString(Constant::pukeNumber);
	//显示其他两个玩家的扑克数目
	lastLabelAtlas->setString(pukeStr);
	nextLabelAtlas->setString(pukeStr);
    
	//每发一张牌播放一次音效
	if(Constant::effectFlag)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
		(
         (SOUND_PATH+string("SpecSelectCard.ogg")).c_str()
         );
	}
	//设置扑克背景框
	mask[Constant::PUKEARRAY[iCount]] = Sprite::create(PIC_PATH+string("poke_gb_mask.png"));
	mask[Constant::PUKEARRAY[iCount]]->setPosition(170+iCount*40,80);
	this->addChild(mask[Constant::PUKEARRAY[iCount]],iCount+1);
	mask[Constant::PUKEARRAY[iCount]]->setVisible(false);
	//扑克
	(puke[Constant::PUKEARRAY[iCount]]->pukeSprite)->setPosition(Point(170+iCount*40,85));
	this->addChild(puke[Constant::PUKEARRAY[iCount]]->pukeSprite,iCount);
	iCount++;
}
void GameLayer::updateRotate(float ft)
{
	angle=(angle+1);
	if(angle>=180)//每当大于180度置零
	{
		angle=angle-180;
		//停止当前定时回调方法
		this->unschedule(SEL_SCHEDULE(&GameLayer::updateRotate));
		firstCard->setFlippedX(false);
		secondCard->setFlippedX(false);
		thirdCard->setFlippedX(false);
	}
    
	//翻方块操作=======第1张==========
	float firstDisX=(PKPKD_HALF-PKPKD_HALF*cos(angle*PI/180.0f));	//x方向偏移量
	float firstDisZ=(PKPKD_HALF*sin(angle*PI/180.0f));				//z方向偏移量
    
	firstCard->setPositionX(firstX+0.2*firstDisX);
	firstCard->setPositionZ(firstDisZ);
	firstCard->setRotation3D(Vec3(0,angle,0));
	if(angle==92)
	{
		firstCard->setTexture(fm);
		firstCard->setTextureRect(Rect(firstCol*72,firstRow*108,72,108));
		firstCard->setFlippedX(true);
	}
    
	//翻方块操作=======第2张
	float secondDisX=(PKPKD_HALF-PKPKD_HALF*cos(angle*PI/180.0f));
	float secondDisZ=(PKPKD_HALF*sin(angle*PI/180.0f));
	secondCard->setPositionX(secondX+0.2*secondDisX);
	secondCard->setPositionZ(secondDisZ);
	secondCard->setRotation3D(Vec3(0,angle,0));
	if(angle==92)
	{
		secondCard->setTexture(fm);
		secondCard->setTextureRect(Rect(secondCol*72,secondRow*108,72,108));
		secondCard->setFlippedX(true);
	}
    
	//翻方块操作=======第3张
	float thirdDisX=(PKPKD_HALF-PKPKD_HALF*cos(angle*PI/180.0f));
	float thirdDisZ=(PKPKD_HALF*sin(angle*PI/180.0f));
    
	thirdCard->setPositionX(thirdX+0.2*thirdDisX);
	thirdCard->setPositionZ(thirdDisZ);
	thirdCard->setRotation3D(Vec3(0,angle,0));
	if(angle==92)
	{
		thirdCard->setTexture(fm);
		thirdCard->setTextureRect(Rect(thirdCol*72,thirdRow*108,72,108));
		thirdCard->setFlippedX(true);
	}
}
//创建三张牌
void GameLayer::createRotate()
{
	//第一张
	firstCol=8-Constant::lastPukeId[0]%9;//列
	firstRow=Constant::lastPukeId[0]/9;	//行
	//第二张
	secondCol=8-Constant::lastPukeId[1]%9;	//列
	secondRow=Constant::lastPukeId[1]/9;	//行
	//第3张
	thirdCol=8-Constant::lastPukeId[2]%9;	//列
	thirdRow=Constant::lastPukeId[2]/9;	//行
    //加载正反面图
    pfm=Director::getInstance()->getTextureCache()->addImage(PIC_PATH+string("poke_back_header.png"));
    pzm=Director::getInstance()->getTextureCache()->addImage(PIC_PATH+string("puke_whole.png"));
    //当前正反面图
    zm = pfm;
    fm = pzm;
    
    //创建翻转用的扑克牌精灵
    //=========第1张
    firstCard = Sprite::createWithTexture(zm);
    firstX = 400.0;//中间变量，沿中间位置旋转，所以中间x坐标不变
    //设置精灵的位置
    firstCard->setPosition
	(
     Point
     (
      firstX,
      490
      )
     );
    firstCard->setScale(0.8);
    firstCard->setAnchorPoint(Point(0.5,0.5));
	//将精灵添加到布景中
    this->addChild(firstCard,PROP_LEVEL);
    
    firstCard->setFlippedX(true);//设置水平旋转
    //===========第2张
    secondCard = Sprite::createWithTexture(zm);
    secondX = 475.0;//中间变量，沿中间位置旋转，所以中间x坐标不变
    //设置精灵的位置
    secondCard->setPosition
	(
     Point
     (
      secondX,
      490
      )
     );
    secondCard->setScale(0.8);
	//将精灵添加到布景中
    this->addChild(secondCard,PROP_LEVEL);
    secondCard->setFlippedX(true);//设置水平旋转
    
    //=============第3张
    thirdCard = Sprite::createWithTexture(zm);
    thirdX = 550.0;//中间变量，沿中间位置旋转，所以中间x坐标不变
    //设置精灵的位置
    thirdCard->setPosition
	(
     Point
     (
      thirdX,
      490
      )
     );
	//将精灵添加到布景中PROP_LEVEL
    this->addChild(thirdCard,PROP_LEVEL);
    thirdCard->setScale(0.8);
    thirdCard->setFlippedX(true);//设置水平旋转
	//设置定时回调指定方法干活
	schedule(schedule_selector(GameLayer::updateRotate), 0.015f);
}
//判断背景游戏音乐的播放种类以及不出的音效
int GameLayer::random()
{
	int number = rand()%4;
	return number;
}
//加载音乐音效
void GameLayer::preloadMuiscOrEffect()
{
	//preloadBackgroundMusic
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic
	(
     (SOUND_PATH+string("MusicEx_Exciting.ogg")).c_str()
     );
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic
	(
     (SOUND_PATH+string("MusicEx_Normal.ogg")).c_str()
     );
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic
	(
     (SOUND_PATH+string("MusicEx_Normal2.ogg")).c_str()
     );
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic
	(
     (SOUND_PATH+string("MusicEx_Win.ogg")).c_str()
     );
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic
	(
     (SOUND_PATH+string("MusicEx_Lose.ogg")).c_str()
     );
	//preloadEffect
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
     (SOUND_PATH+string("SpecOk.ogg")).c_str()
     );
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
     (SOUND_PATH+string("SpecSelectCard.ogg")).c_str()
     );
    
	//叫地主相关音效
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
     (SOUND_PATH+string("Man_NoOrder.mp3")).c_str()
     );
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
     (SOUND_PATH+string("Man_NoRob.mp3")).c_str()
     );
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
     (SOUND_PATH+string("Man_Order.mp3")).c_str()
     );
    
	for(int i=0;i<4;i++)
	{
		//不出音效
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
		(
         (SOUND_PATH+StringUtils::format("Man_buyao%d.mp3",i)).c_str()//转化为string类型并转化成字节型数组
         );
		if(i!=0)//抢地主音效
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
			(
             (SOUND_PATH+StringUtils::format("Man_Rob%d.mp3",i)).c_str()//转化为string类型并转化成字节型数组
             );
		}
	}
	//牌内容音效
	for(int i=1;i<16;i++)
	{
		//单张牌音效
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
		(
         (SOUND_PATH+StringUtils::format("Man_%d.mp3",i)).c_str()//转化为string类型并转化成字节型数组
         );
		if(i<14)
		{
			//对子牌音效
			CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
			(
             (SOUND_PATH+StringUtils::format("Man_dui%d.mp3",i)).c_str()//转化为string类型并转化成字节型数组
             );
			//三张牌音效
			CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
			(
             (SOUND_PATH+StringUtils::format("Man_tuple%d.mp3",i)).c_str()//转化为string类型并转化成字节型数组
             );
		}
	}
	//飞机音效
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
     (SOUND_PATH+string("Man_feiji.mp3")).c_str()
     );
	//连对音效
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
     (SOUND_PATH+string("Man_liandui.mp3")).c_str()
     );
	//三带一音效
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
     (SOUND_PATH+string("Man_sandaiyi.mp3")).c_str()
     );
	//三带一对音效
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
     (SOUND_PATH+string("Man_sandaiyidui.mp3")).c_str()
     );
	//顺子音效Man_sidaier
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
     (SOUND_PATH+string("Man_shunzi.mp3")).c_str()
     );
	//四带二音效
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
     (SOUND_PATH+string("Man_sidaier.mp3")).c_str()
     );
	//四带两对音效
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
     (SOUND_PATH+string("Man_sidailiangdui.mp3")).c_str()
     );
	//王炸音效
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
     (SOUND_PATH+string("Man_wangzha.mp3")).c_str()
     );
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
     (SOUND_PATH+string("Man_zhadan.mp3")).c_str()
     );
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
     (SOUND_PATH+string("Special_alert.mp3")).c_str()
     );
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
     (SOUND_PATH+string("Special_Bomb.mp3")).c_str()
     );
	//倍数音效
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
     (SOUND_PATH+string("Special_Multiply.mp3")).c_str()
     );
	//出牌音效
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
     (SOUND_PATH+string("Special_give.mp3")).c_str()
     );
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
     (SOUND_PATH+string("Special_plane.mp3")).c_str()
     );
}
//播放不叫、叫、抢、不抢地主
void GameLayer::playOrderOrRob()
{
	if(Constant::soundType==0)//不叫
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
		(
         (SOUND_PATH+string("Man_NoOrder.mp3")).c_str()
         );
	}
	else if(Constant::soundType==1)//叫地主
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
		(
         (SOUND_PATH+string("Man_Order.mp3")).c_str()
         );
	}
	else if(Constant::soundType==2)//不抢
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
		(
         (SOUND_PATH+string("Man_NoRob.mp3")).c_str()
         );
	}
	else if(Constant::soundType==3)//抢地主
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
		(
         (SOUND_PATH+StringUtils::format("Man_Rob%d.mp3",(Constant::landlordCount-2))).c_str()//转化为string类型并转化成字节型数组
         );
	}
}
//绘制游戏开始后，出牌等按钮
void GameLayer::playGameBtn()
{
	//出牌灰色精灵
	chuSprite = Sprite::create(PIC_PATH+string("play_btn_disable.png"));
	chuSprite->setPosition(Point(800,220));
	this->addChild(chuSprite,PROP_LEVEL);
	chuSprite->setVisible(false);
	//重选
	resetSprite = Sprite::create(PIC_PATH+string("reset_btn_disable.png"));
	resetSprite->setPosition(Point(480,220));
	this->addChild(resetSprite,PROP_LEVEL);
	resetSprite->setVisible(false);
	//==========菜单项
	//不出
	MenuItemImage *buChuItem = MenuItemImage::create
	(
     PIC_PATH+string("no_red_btn.png"),
     PIC_PATH+string("no_red_btn_down.png"),
     CC_CALLBACK_1(GameLayer::menuBuChuCallback, this)
     );
	//设置菜单项的位置
	buChuItem->setPosition(Point(320,220));
	buChuMenu = Menu::create(buChuItem, NULL);
	buChuMenu->setPosition(Point::ZERO);
	this->addChild(buChuMenu,BTN_LEVEL);
	buChuMenu->setVisible(false);
	//重选
	MenuItemImage *resetItem = MenuItemImage::create
	(
     PIC_PATH+string("reset_blue_btn.png"),
     PIC_PATH+string("reset_blue_btn_down.png"),
     CC_CALLBACK_1(GameLayer::menuResetCallback, this)
     );
	//设置菜单项的位置
	resetItem->setPosition(Point(480,220));
	resetMenu = Menu::create(resetItem, NULL);
	resetMenu->setPosition(Point::ZERO);
	this->addChild(resetMenu,BTN_LEVEL);
	resetMenu->setVisible(false);
	//出牌
	MenuItemImage *chuItem = MenuItemImage::create
	(
     PIC_PATH+string("play_green_btn.png"),
     PIC_PATH+string("play_green_btn_down.png"),
     CC_CALLBACK_1(GameLayer::menuPlayCallback, this)
     );
	//设置菜单项的位置
	chuItem->setPosition(Point(800,220));
	chuMenu = Menu::create(chuItem, NULL);
	chuMenu->setPosition(Point::ZERO);
	this->addChild(chuMenu,BTN_LEVEL);
	chuMenu->setVisible(false);
	//提示
	MenuItemImage *tiShiItem = MenuItemImage::create
	(
     PIC_PATH+string("tishi_blue_btn.png"),
     PIC_PATH+string("tishi_blue_btn_down.png"),
     CC_CALLBACK_1(GameLayer::menuTishi, this)
     );
	//设置菜单项的位置
	tiShiItem->setPosition(Point(640,220));
	tiShiMenu = Menu::create(tiShiItem, NULL);
	tiShiMenu->setPosition(Point::ZERO);
	this->addChild(tiShiMenu,BTN_LEVEL);
	tiShiMenu->setVisible(false);
}
//添加叫地主和不叫地主
void GameLayer::addOrderOrNo()
{
	orderMenu->setVisible(true);
	noOrderMenu->setVisible(true);
	if(Constant::effectFlag)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
		(
         (SOUND_PATH+string("SpecSelectCard.ogg")).c_str()
         );
	}
}
//添加抢地主和不抢地主
void GameLayer::addQiangOrNo()
{
	qdzMenu->setVisible(true);
	bqMenu->setVisible(true);
    
	if(Constant::effectFlag)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
		(
         (SOUND_PATH+string("SpecSelectCard.ogg")).c_str()
         );
	}
}
//game ready
void GameLayer::menuReadyCallback(Ref* sender)
{
	//开始准备，向服务器发送准备信息
	if(BNSocketUtil::connectFlag)
	{
		//发送类型代码0，表示数据为整数，表示已经准备
		BNSocketUtil::sendInt(0);
	}
	//设置准备按钮不可见
	readyMenu->setVisible(false);
}
//setting设置
void GameLayer::menuSetCallback(Ref* sender)
{
	if(Constant::effectFlag)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
		(
         (SOUND_PATH+string("SpecOk.ogg")).c_str()
         );
	}
	if(!checkCreate)
	{
		setBack = Sprite::create(PIC_PATH+string("set_background.png"));
		setBack->setPosition(Point(480,300));
		this->addChild(setBack, 20);
        
		//effect
		CheckBox* effectBox = CheckBox::create(
                                               PIC_PATH+string("check.png"),
                                               PIC_PATH+string("uncheck.png"),
                                               PIC_PATH+string("uncheck.png"),
                                               PIC_PATH+string("uncheck.png"),
                                               PIC_PATH+string("uncheck.png")
                                               );
		setBack->addChild(effectBox, 1);
		effectBox->setPosition(Point(335,100));
		effectBox->setSelectedState(!Constant::effectFlag);
		effectBox->addEventListener(CC_CALLBACK_2(GameLayer::menuEffectCallback, this));
        
		//backgroundMusic
		CheckBox* musicBox = CheckBox::create(
                                              PIC_PATH+string("check.png"),
                                              PIC_PATH+string("uncheck.png"),
                                              PIC_PATH+string("uncheck.png"),
                                              PIC_PATH+string("uncheck.png"),
                                              PIC_PATH+string("uncheck.png")
                                              );
		setBack->addChild(musicBox, 1);
		musicBox->setPosition(Point(335,35));
		musicBox->setSelectedState(!Constant::musicFlag);
		musicBox->addEventListener(CC_CALLBACK_2(GameLayer::menuMusicCallback, this));
        
		checkCreate = true;		//复选框已经创建
		set = true;				//设置选项已经打开
		first = false;			//第一次已经完成创建
	}
	if(set)
	{
		setBack->setVisible(true);
	}else{
		setBack->setVisible(false);
	}
	set = !set;
}
//set effect
void GameLayer::menuEffectCallback(Ref* pSender,CheckBox::EventType type)
{
	switch(type)
	{
		case CheckBox::EventType::SELECTED:
        	Constant::effectFlag = false;
			break;
		case CheckBox::EventType::UNSELECTED:
			Constant::effectFlag = true;
			break;
		default:
		    break;
	}
}
//music
void GameLayer::menuMusicCallback(Ref* pSender,CheckBox::EventType type)
{
	switch(type)
	{
		case CheckBox::EventType::SELECTED:
        	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
        	Constant::musicFlag = false;
			break;
		case CheckBox::EventType::UNSELECTED:
			CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
			Constant::musicFlag = true;
			break;
		default:
		    break;
	}
}
//exit game
void GameLayer::menuExitCallback(Ref* sender)
{
	if(Constant::effectFlag)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
		(
         (SOUND_PATH+string("SpecOk.ogg")).c_str()
         );
	}
	if(set||(first&&!set))
	{
		if(!exit)
		{
			yesOrNo = Sprite::create(PIC_PATH+string("YesOrNo.png"));
			yesOrNo->setPosition(Point(480,270));
			this->addChild(yesOrNo,CHECK_LEVEL);
            
			//ok
			MenuItemImage *okItem = MenuItemImage::create
			(
             PIC_PATH+string("blue_btn_ok.png"),
             PIC_PATH+string("blue_btn_ok.png"),
             CC_CALLBACK_1(GameLayer::menuOkCallback, this)
             );
			//设置关闭菜单项的位置
			okItem->setPosition(Point(300,50));
			Menu *okMenu = Menu::create(okItem, NULL);
			okMenu->setPosition(Point::ZERO);
			yesOrNo->addChild(okMenu,1);
            
			//cancel
			MenuItemImage *cancelItem = MenuItemImage::create
			(
             PIC_PATH+string("blue_btn_cancel.png"),
             PIC_PATH+string("blue_btn_cancel.png"),
             CC_CALLBACK_1(GameLayer::menuCancelCallback, this)
             );
			//设置菜单项的位置
			cancelItem->setPosition(Point(100,50));
			Menu *cancelMenu = Menu::create(cancelItem, NULL);
			cancelMenu->setPosition(Point::ZERO);
			yesOrNo->addChild(cancelMenu,1);
			exit=true;
		}else{
			yesOrNo->setVisible(true);
		}
        
	}else{
		setBack->setVisible(false);
		set=!set;
	}
}

//取消
void GameLayer::menuCancelCallback(Ref* sender)
{
	if(Constant::effectFlag)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
		(
         (SOUND_PATH+string("SpecOk.ogg")).c_str()
         );
	}
	yesOrNo->setVisible(false);
}
//确定
void GameLayer::menuOkCallback(Ref* sender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	BNSocketUtil::closeConnect();
	psm->goWelcome();
}
void GameLayer::gameOver(Ref* sender)
{
	this->unscheduleAllSelectors();
	gameDataReset();
	psm->goGame();
}
void GameLayer::gameDataReset()
{
	Constant::oldGoldFlag=-1;
	Constant::playerReady=0;
	Constant::lastPlayerReady=0;
	Constant::nextPlayerReady=0;
	Constant::readyNum=0;
	Constant::pukeFlag=false;
	Constant::readyFlag=false;
	Constant::landlordHadPuke=false;
	Constant::clearLandlordState=false;
	Constant::isDrawChuPai=false;
	Constant::isDrawReset=false;
	Constant::isCanPlayEffect=false;
	Constant::whoFlag=-1;
	Constant::whoIsLandlord=-1;
	Constant::landlordCount=0;
	Constant::beiNum=15;
	Constant::oldBeiNum=15;
	Constant::landlordListNum=-1;
	Constant::soundType=-1;
	Constant::playerCardsCount=0;
	Constant::lastPlayerCardsCount=0;
	Constant::nextPlayerCardsCount=0;
	Constant::upCardsCount=0;
	Constant::isCanChuPai=0;
	Constant::drawCardsFlag=0;
	Constant::isBuChu=0;
	Constant::playerLength=0;
	Constant::lastPlayerLength=0;
	Constant::nextPlayerLength=0;
	Constant::deleteMenu=false;
	Constant::menuItem=false;
	Constant::drawTiShi=false;
	Constant::effectRow=-1;
	Constant::effectCol=-1;
	Constant::victory=-1;
	Constant::drawLogo=true;
	Constant::pukeNumber=0;
    Constant::drawAct=false;
}
//叫地主
void GameLayer::menuOrderCallback(Ref* sender)
{
	//叫完地主，将叫叫地主和不叫设为不可见
	orderMenu->setVisible(false);
	noOrderMenu->setVisible(false);
	//向服务器发送数据兵设置
	if(BNSocketUtil::connectFlag)
	{
		//叫地主向服务器发送1
		BNSocketUtil::sendInt(1);
		BNSocketUtil::sendInt(1);
	}
}
//不叫
void GameLayer::menuNoOrderCallback(Ref* sender)
{
	//将叫地主和不叫地主隐藏
	orderMenu->setVisible(false);
	noOrderMenu->setVisible(false);
	if(BNSocketUtil::connectFlag)
	{
		//叫地主向服务器发送1
		BNSocketUtil::sendInt(1);
		BNSocketUtil::sendInt(0);
	}
}
//抢地主改变
void GameLayer::menuQiangCallback(Ref* sender)
{
	bqMenu->setVisible(false);
	qdzMenu->setVisible(false);
	if(BNSocketUtil::connectFlag)
	{
		//叫地主向服务器发送1
		BNSocketUtil::sendInt(1);//标志位
		BNSocketUtil::sendInt(1);//内容
	}
}
//不抢地主
void GameLayer::menuNoQiangCallback(Ref* sender)
{
	if(BNSocketUtil::connectFlag)
	{
		//叫地主向服务器发送1
		BNSocketUtil::sendInt(1);
		//告诉服务器当前状态为不抢
        
		BNSocketUtil::sendInt(0);
	}
	bqMenu->setVisible(false);
	qdzMenu->setVisible(false);
}
void GameLayer::menuTishi(Ref* sender)			//提示
{
	if(BNSocketUtil::connectFlag)
	{
		BNSocketUtil::sendInt(4);
	}
}
//2倍
void GameLayer::menuChaCallback(Ref* sender)
{
	bei2->setVisible(false);
	bei2->setPosition(Point(480,310));
}
void GameLayer::menuBuChuCallback(Ref* sender)
{
	//牌已经点起，但选择了不出牌，向服务器发送数据
	if(BNSocketUtil::connectFlag)
	{
		BNSocketUtil::sendInt(3);//表示要出牌
		BNSocketUtil::sendInt(0);//不出牌
	}
}
//重选--将抬起的牌放下
void GameLayer::menuResetCallback(Ref* sender)
{
	for(int i=0;i<Constant::playerCardsCount;i++)
	{
		int lastSize = Constant::playerCardsCount/2;
		int lastLiftX =  490-lastSize*40;//用于从左侧排序的最远距离
		//int lastMid=0;
		puke[Constant::PUKEARRAY[i]]->pukeSprite->setPosition(Point(lastLiftX+40*i,85));
		Constant::upCards[Constant::PUKEARRAY[i]]=0;
	}
	Constant::upCardsCount=0;
	Constant::isDrawReset=true;
}
//开始游戏出牌
void GameLayer::menuPlayCallback(Ref* sender)
{
	for(int k=0;k<Constant::playerCardsCount;k++)
	{
		if(Constant::upCards[Constant::PUKEARRAY[k]]==1)
		{
			this->removeChild(puke[Constant::PUKEARRAY[k]]->pukeSprite);
			this->removeChild(mask[Constant::PUKEARRAY[k]]);
		}
	}
	//牌已经点起，准备出牌，向服务器发送数据
	if(BNSocketUtil::connectFlag)
	{
		BNSocketUtil::sendInt(3);	//表示要出牌
		BNSocketUtil::sendInt(1);	//出牌
	}
	//把抬起的牌清为0
	Constant::upCardsCount=0;
    
}
//设置倍数顺序执行
void GameLayer::setBeiMove()
{
	bei2->setVisible(true);
	//顺序动作
	bei2->runAction(
                    Sequence::create(
                                     MoveTo::create(2.0,Point(480,340)),
                                     CallFuncN::create(CC_CALLBACK_1(GameLayer::menuChaCallback, this)),
                                     NULL)
					);
}
//切分扑克牌
void GameLayer::initPuKe()
{
	Texture2D* tt2d = Director::getInstance()->getTextureCache()->addImage(PIC_PATH+string("puke_whole.png"));
	//编号
	int pukeSpriteCount= 0;
    
	for(int i=0;i<648;i=i+108)//行6行
	{
		for(int j=648-72;j>=0;j=j-72)//9列
		{
			Rect r = Rect(j,i,72,108);//截取面积
			puke[pukeSpriteCount] = new PuKe(tt2d,pukeSpriteCount,r,648-j+120,i+59);//创建对象
			puke[pukeSpriteCount]->refresh();//更新位置
			puke[pukeSpriteCount]->pukeSprite->setScale(1.5);//放大
			puke[pukeSpriteCount]->pukeSprite->retain();
			pukeSpriteCount++;
		}
	}
}
//touch,只有叫完地主和抢地主完毕后，才能触摸牌
bool GameLayer::onTouchBegan(Touch* touch, Event* event)
{
	beginX = touch->getLocation().x;
	beginY = touch->getLocation().y;
    
	if(Constant::whoFlag==Constant::playerId&&Constant::landlordCount>=5)//判断是否已经发牌成功
	{
		//遍历扑克数组
		for(int k=0;k<Constant::playerCardsCount;k++)
		{
			//获取每张扑克牌位置
			Point pkPoint = puke[Constant::PUKEARRAY[k]]->pukeSprite->getPosition();
			//判断是否点击了扑克牌
			if(abs(beginX- pkPoint.x+32)<=36&&abs(beginY- pkPoint.y)<=54)
			{
				mask[Constant::PUKEARRAY[k]]->setPosition(pkPoint);
				mask[Constant::PUKEARRAY[k]]->setVisible(true);
				break;//只能抬起一张牌
			}
		}
	}
	return true;
}
//触摸移动
void GameLayer::onTouchMoved(Touch *touch, Event *event)
{
	moveX = touch->getLocation().x;
	moveY = touch->getLocation().y;
	if(Constant::whoFlag==Constant::playerId&&Constant::landlordCount>=5)//判断是否已经发牌成功
	{
		//遍历扑克数组===从左到右
		for(int k=0;k<Constant::playerCardsCount;k++)
		{
			//获取扑克的位置
			Point pkPoint = puke[Constant::PUKEARRAY[k]]->pukeSprite->getPosition();
            
			if(pkPoint.x<=moveX&&pkPoint.x>=beginX&&abs(pkPoint.y-beginY)<54&&abs(pkPoint.y-moveY)<81)
			{
				mask[Constant::PUKEARRAY[k]]->setPosition(pkPoint);
				mask[Constant::PUKEARRAY[k]]->setVisible(true);
			}
			else if(pkPoint.x<=beginX&&pkPoint.x>=moveX&&abs(pkPoint.y-beginY)<54&&abs(pkPoint.y-moveY)<81)
			{
				mask[Constant::PUKEARRAY[k]]->setPosition(pkPoint);
				mask[Constant::PUKEARRAY[k]]->setVisible(true);
			}
		}
	}
}
//触摸结束
void GameLayer::onTouchEnded(Touch *touch, Event *event)
{
	Point point = touch->getLocation();
	int m=0;
	if(Constant::whoFlag==Constant::playerId&&Constant::landlordCount>=5)//判断是否已经发牌成功
	{
		//遍历扑克数组--单击扑克作出反应
		for(int k=0; k<Constant::playerCardsCount; k++)
		{
			//获取扑克的位置
			Point pkPoint = puke[Constant::PUKEARRAY[k]]->pukeSprite->getPosition();
			//如果点击了牌
			if(k==Constant::playerCardsCount-1)
			{
				beginX-=32;
			}
			if(abs(beginX- pkPoint.x+32)<=36&&abs(beginY- pkPoint.y)<=54)//如果点击牌,+32往又偏
			{
				if(Constant::upCards[Constant::PUKEARRAY[k]]==1)//已经抬起
				{
					puke[Constant::PUKEARRAY[k]]->pukeSprite->setPosition(Point(pkPoint.x,pkPoint.y-18));
					Constant::upCards[Constant::PUKEARRAY[k]]=0;
					Constant::upCardsCount--;
                    
				}else{//牌未抬起
					puke[Constant::PUKEARRAY[k]]->pukeSprite->setPosition(Point(pkPoint.x,pkPoint.y+18));
					Constant::upCards[Constant::PUKEARRAY[k]]=1;
					Constant::upCardsCount++;			//已经点起
				}
				mask[Constant::PUKEARRAY[k]]->setVisible(false);
                
				if(Constant::effectFlag)
				{
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
					(
                     (SOUND_PATH+string("SpecSelectCard.ogg")).c_str()
                     );
				}
				if(k==Constant::playerCardsCount-1)
				{
					beginX+=32;
				}
				break;//只能抬起一张牌
			}
		}
        
		//遍历扑克数组
		for(int k=0;k<Constant::playerCardsCount;k++)
		{
			//获取扑克的位置
			Point pkPoint = puke[Constant::PUKEARRAY[k]]->pukeSprite->getPosition();
            
			//从左到右滑动
			if(pkPoint.x<=point.x&&pkPoint.x>=beginX&&abs(pkPoint.y-beginY)<54&&abs(pkPoint.y-point.y)<81)
			{
				if(Constant::upCards[Constant::PUKEARRAY[k]]==1)
				{
					puke[Constant::PUKEARRAY[k]]->pukeSprite->setPosition(Point(pkPoint.x,pkPoint.y-18));
					Constant::upCards[Constant::PUKEARRAY[k]]=0;
					Constant::upCardsCount--;
				}else{
					puke[Constant::PUKEARRAY[k]]->pukeSprite->setPosition(Point(pkPoint.x,pkPoint.y+18));
					Constant::upCards[Constant::PUKEARRAY[k]]=1;					//设置标志位 表示扑克已经抬起
					Constant::upCardsCount++;		//点击抬起
				}
				mask[Constant::PUKEARRAY[k]]->setVisible(false);
                
				if(Constant::effectFlag&&m==0)
				{
					m++;
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
					(
                     (SOUND_PATH+string("SpecSelectCard.ogg")).c_str()
                     );
				}
			}
            
			//从右到左滑动
			else if(pkPoint.x<=beginX&&pkPoint.x>=point.x&&abs(pkPoint.y-beginY)<54&&abs(pkPoint.y-point.y)<81)
			{
				if(Constant::upCards[Constant::PUKEARRAY[k]]==1)
				{
					puke[Constant::PUKEARRAY[k]]->pukeSprite->setPosition(Point(pkPoint.x,pkPoint.y-18));
					Constant::upCards[Constant::PUKEARRAY[k]]=0;
					Constant::upCardsCount--;
                    
				}else{
					puke[Constant::PUKEARRAY[k]]->pukeSprite->setPosition(Point(pkPoint.x,pkPoint.y+18));
					Constant::upCards[Constant::PUKEARRAY[k]]=1;
					Constant::upCardsCount++;
				}
				mask[Constant::PUKEARRAY[k]]->setVisible(false);
				if(Constant::effectFlag&&m==0)
				{
					m++;
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
					(
                     (SOUND_PATH+string("SpecSelectCard.ogg")).c_str()
                     );
				}
			}
		}
        
		if(Constant::upCardsCount>0)
		{
			//调用该方法，出牌前的准备工作
			isChuPai();
		}else
		{
			Constant::isDrawChuPai=true;
			Constant::isDrawReset=true;
		}
        
	}
}
//判断是否出牌
void GameLayer::isChuPai()
{
	//牌已经点起，准备向服务器发送数据
	if(BNSocketUtil::connectFlag)
	{
		BNSocketUtil::sendInt(2);							//表示要发送点起牌的数目及内容
		int upCardCount=Constant::upCardsCount;
		BNSocketUtil::sendInt(upCardCount);					//数目
		for(int i=0;i<Constant::playerCardsCount;i++)
		{
			if(Constant::upCards[Constant::PUKEARRAY[i]]==1)
			{
				//开始准备，向服务器发送准备信息
				//发送内容
				int send=Constant::PUKEARRAY[i];
				BNSocketUtil::sendInt(send);
			}
		}
	}
}
//获取系统时间
void GameLayer::getSystemTime(float dt)
{
    time_t t = time(0);
    char tmp[64];
    strftime( tmp, sizeof(tmp),"%H:%M",localtime(&t) );
    timeLabel->setString(tmp);
}
