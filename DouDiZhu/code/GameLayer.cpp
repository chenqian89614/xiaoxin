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
	//���ø���ĳ�ʼ��
    if ( !Layer::init() )
    {
        return false;
    }
    //���� addSprite����
    addSprite();
    //���� addLabel����
    addLabel();
    //��Ӷ�ʱ�ص�
    addUpdate();
    //��Ӳ˵���
    addMenuItem();
    //�����Ƶ���Ϣ���Ƴ���������
    playGameBtn();
    //��ʼ����
    initPuKe();
    //Ԥ������Ч������
    preloadMuiscOrEffect();
    
	//touch listen
	//����һ�����㴥������
	auto listener = EventListenerTouchOneByOne::create();
	//�����´�����
	listener->setSwallowTouches(true);
	//��ʼ����ʱ�ص�onTouchBegan����
	listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
	//��ӵ�������
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
    //��ʼ��
    tempCardVector0 = new std::vector<Sprite*>();
    tempCardVector1 = new std::vector<Sprite*>();
    tempCardVector2 = new std::vector<Sprite*>();
    vecPuKe = new std::vector<Sprite*>();
    
    return true;
}
//��Ӳ˵���
void GameLayer::addMenuItem()
{
    //exit
    MenuItemImage *exitItem = MenuItemImage::create
    (
     PIC_PATH+string("game_exit.png"),
     PIC_PATH+string("game_exit.png"),
     CC_CALLBACK_1(GameLayer::menuExitCallback, this)
     );
    //���ùرղ˵����λ��
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
    //���ò˵����λ��
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
    //���ò˵����λ��
    readyItem->setPosition(Point(480,240));
    readyMenu = Menu::create(readyItem, NULL);
    readyMenu->setPosition(Point::ZERO);
    this->addChild(readyMenu,BTN_LEVEL);
    
    //�е�������������ť
	MenuItemImage *orderItem = MenuItemImage::create
	(
     PIC_PATH+string("message_jiao.png"),
     PIC_PATH+string("message_jiao.png"),
     CC_CALLBACK_1(GameLayer::menuOrderCallback, this)
     );
	//���ò˵����λ��
	orderItem->setPosition(Point(540,220));
	orderMenu = Menu::create(orderItem, NULL);
	orderMenu->setPosition(Point::ZERO);
	this->addChild(orderMenu,BTN_LEVEL);
	orderMenu->setVisible(false);
	//����
	MenuItemImage *noOrderItem = MenuItemImage::create
	(
     PIC_PATH+string("message_bu.png"),
     PIC_PATH+string("message_bu.png"),
     CC_CALLBACK_1(GameLayer::menuNoOrderCallback, this)
     );
	//���ò˵����λ��
	noOrderItem->setPosition(Point(380,220));
	noOrderMenu = Menu::create(noOrderItem, NULL);
	noOrderMenu->setPosition(Point::ZERO);
	this->addChild(noOrderMenu,BTN_LEVEL);
	noOrderMenu->setVisible(false);
    
	//������
	MenuItemImage *qdzItem = MenuItemImage::create
	(
     PIC_PATH+string("message_qiang.png"),
     PIC_PATH+string("message_qiang.png"),
     CC_CALLBACK_1(GameLayer::menuQiangCallback, this)
     );
	//���ùرղ˵����λ��
	qdzItem->setPosition(Point(540,220));
	qdzMenu = Menu::create(qdzItem, NULL);
	qdzMenu->setPosition(Point::ZERO);
	this->addChild(qdzMenu,BTN_LEVEL);
	qdzMenu->setVisible(false);
	//����
	MenuItemImage *bqItem = MenuItemImage::create
	(
     PIC_PATH+string("message_buQiang.png"),
     PIC_PATH+string("message_buQiang.png"),
     CC_CALLBACK_1(GameLayer::menuNoQiangCallback, this)
     );
	//���ò˵����λ��
	bqItem->setPosition(Point(380,220));
	bqMenu = Menu::create(bqItem, NULL);
	bqMenu->setPosition(Point::ZERO);
	this->addChild(bqMenu,BTN_LEVEL);
	bqMenu->setVisible(false);
}
//������ʱ�ص�����
void GameLayer::addUpdate()
{
	//����������Ϣ�ķ���
	schedule(schedule_selector(GameLayer::updateDrawOther), 0.1f);
    
	//���Լ�����
	schedule(schedule_selector(GameLayer::updatePuke), 0.1f);
	//��ȡϵͳʱ��
	schedule(schedule_selector(GameLayer::getSystemTime), 1.0f);
	//���ų�����Ч
	schedule(schedule_selector(GameLayer::updatePlayEffect), 0.2f);
}

void GameLayer::updatePuke(float dt)		//�����˿���
{
	int lastId=(Constant::whoFlag==0)?2:Constant::whoFlag-1;
	if(lastId==Constant::playerId&&Constant::drawCards)				//�����ϼ���
	{
        Constant::drawCards=false;
        if(!vecPuKe->empty())
        {
            vecPuKe->clear();
        }
        //��ʣ����ƴ��vector��
        for(int k=0;k<Constant::pukeRemainNumber;k++)
        {
            vecPuKe->push_back(puke[Constant::PUKEARRAY[k]]->pukeSprite);
        }
        //��ʣ���ƽ�������
        if(!vecPuKe->empty())
        {
            std::vector<Sprite* >::iterator tempLastPuKe;
            
            int lastSize = vecPuKe->size()/2;
            int lastLiftX =  490-lastSize*40;//���ڴ�����������Զ����
            int lastMid=0;
            for(tempLastPuKe=vecPuKe->begin();tempLastPuKe!=vecPuKe->end();++tempLastPuKe)
            {
                (*tempLastPuKe)->setPosition(Point(lastLiftX+40*lastMid++,85));
            }
        }
	}
	if(Constant::drawTiShi)						//��ʾ
	{
		Constant::drawTiShi=false;
		Constant::upCardsCount=0;
		int lastSize = Constant::playerCardsCount/2;
		int lastLiftX =  490-lastSize*40;//���ڴ�����������Զ����
		for(int j=0;j<Constant::playerCardsCount;j++)
		{
			if(Constant::upCards[Constant::PUKEARRAY[j]]==1)
			{
				//��ȡ�˿˵�λ��LL
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
	if(Constant::whoFlag==Constant::playerId&&Constant::drawAlreadyCard)		//������Ȩʱ�����Ƶĸ�����Ϊ��ʱ��������ѳ��б�	����ʾ�κζ���
	{
		buchu[0]->setVisible(false);
		for(int k=0;k<Constant::playerLength;k++)
		{
			this->removeChild(player[k]->pukeSprite);
		}
		Constant::playerLength=0;
		Constant::playerCardDraw=true;
	}
	if(Constant::whoFlag!=Constant::playerId&&Constant::drawAlreadyCard)									//��û����Ȩʱ
	{
		if(Constant::playerLength==0&&Constant::landlordCount>6)//����ѳ��б�Ϊ��ʱ��û�е�ǰ��Ȩʱ����ʾ����
		{
			buchu[0]->setVisible(true);
		}
        
		if(Constant::playerLength!=0&&Constant::playerCardDraw)			//���ѳ��б�Ϊ��ʱ�ҵ�ǰû����Ȩ�� ��ʾ�ѳ�����
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
                player[k]->pukeSprite->setScale(0.9);//�Ŵ�
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
    
	if(Constant::whoFlag!=Constant::lastPlayerId&&Constant::drawAlreadyCard)									//��û����Ȩʱ
	{
		if(Constant::lastPlayerLength==0&&Constant::landlordCount>6)//����ѳ��б�Ϊ��ʱ��û�е�ǰ��Ȩʱ����ʾ����
		{
			buchu[2]->setVisible(true);
		}
        
		if(Constant::lastPlayerLength!=0&&Constant::lastPlayerCardDraw)			//���ѳ��б�Ϊ��ʱ�ҵ�ǰû����Ȩ�� ��ʾ�ѳ�����
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
                last[k]->pukeSprite->setScale(0.9);//�Ŵ�
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
    
	if(Constant::whoFlag!=Constant::nextPlayerId&&Constant::drawAlreadyCard)									//��û����Ȩʱ
	{
		if(Constant::nextPlayerLength==0&&Constant::landlordCount>6)//����ѳ��б�Ϊ��ʱ��û�е�ǰ��Ȩʱ����ʾ����
		{
			buchu[1]->setVisible(true);
		}
        
		if(Constant::nextPlayerLength!=0&&Constant::nextPlayerCardDraw)			//���ѳ��б�Ϊ��ʱ�ҵ�ǰû����Ȩ�� ��ʾ�ѳ�����
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
                next[k]->pukeSprite->setScale(0.9);//�Ŵ�
                next[k]->pukeSprite->retain();
                
                this->addChild(next[k]->pukeSprite,k);
			}
			Constant::nextPlayerCardDraw=false;
		}
	}
	Constant::drawAlreadyCard=false;				//���ѳ�����
    
	if(Constant::drawVictory)						//����
	{
        
		Constant::drawVictory=false;
		int spriteVictory=-1;						//ʤ�� 0��������1����Ӯ��2ũ�񸺣�3ũ��Ӯ
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
//���LabelAtlas��������ʾ���������������ͷ����
void GameLayer::addLabel()
{
	//��ǰ����
    bLabelAtlas = LabelAtlas::create("15",(PIC_PATH+string("poker_number.png")),25,32,'0');//����һ��LabelAtlas����
	bLabelAtlas->setAnchorPoint(Point(1,0));//����LabelAtlas����ê��
    bLabelAtlas->setPosition(Point(690,475));
	this->addChild(bLabelAtlas,PROP_LEVEL);			//��LabelAtlas������ӵ�������
	//===========��ͷʣ������===========
	lastLabelAtlas = LabelAtlas::create("0",(PIC_PATH+string("poker_number.png")),25,32,'0');//����һ��LabelAtlas����
	lastLabelAtlas->setPosition(Point(41,360));
	this->addChild(lastLabelAtlas,PROP_LEVEL+1);			//��LabelAtlas������ӵ�������
	//
	nextLabelAtlas = LabelAtlas::create("0",(PIC_PATH+string("poker_number.png")),25,32,'0');//����һ��LabelAtlas����
	nextLabelAtlas->setPosition(Point(871,360));
	this->addChild(nextLabelAtlas,PROP_LEVEL+1);			//��LabelAtlas������ӵ�������
}
//��Ӿ���
void GameLayer::addSprite()
{
	//����һ��������󣬰���background.pngͼƬ
	Sprite  *background = Sprite::create(PIC_PATH+string("background.png"));
	background->setPosition(Point(480,270));
	//��������ӵ�������
	this->addChild(background, BACKGROUD_LEVEL);
	//������ͼ���Լ��߿�
	for(int i=0;i<3;i++)
	{
		unKnow[i] = Sprite::create(PIC_PATH+string("logo_unknown.png"));
		actKnow[i] = Sprite::create(PIC_PATH+string("logo_active.png"));//����ʱ����Ȩ
		deKnow[i] = Sprite::create(PIC_PATH+string("logo_deactive.png"));//ƽ����־��
		dizhuHeadImage[i]=Sprite::create(PIC_PATH+string("logo_dizhu.png"));//����ͷ��ũ��ͷ��
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
	//������
	for(int i=0;i<5;i++)
	{
		poke[i] = Sprite::create(PIC_PATH+string("poke_back_header.png"));
		if(i<3)//0,1,2����ʣ�������Ƶı���ͼ
		{
			poke[i]->setPosition(Point(400+i*75,490));
			poke[i]->setScale(0.8);
			this->addChild(poke[i],PROP_LEVEL);
		}else{//��һ�������һ��ҵı���ͼ
			poke[i]->setPosition(Point(60+(i-3)*830,380));
			poke[i]->setScale(1.1);
            
			this->addChild(poke[i], PROP_LEVEL);
		}
        
	}
	//ok���ƣ�׼����־
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
    
	//��������
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
	//����ͼ��
	Sprite *logo_bei = Sprite::create(PIC_PATH+string("game_bei.png"));
	logo_bei->setPosition(Point(735,490));
	this->addChild(logo_bei, PROP_LEVEL);
	//*2�������ڽе���������������ʾ
	bei2 = Sprite::create(PIC_PATH+string("cha2.png"));
	bei2->setPosition(Point(480,310));
	this->addChild(bei2, PROP_LEVEL);
	bei2->setVisible(false);
    
	//==================�������������ĸ�����
	for(int i=0;i<5;i++)
	{
		if(i!=4)
		{
			//0����
			playerSprite[i] = Sprite::create((PIC_PATH+StringUtils::format("message%d.png",i)).c_str());
			playerSprite[i]->setPosition(Point(480,200));
			this->addChild(playerSprite[i],PROP_LEVEL);
			//1����
			nextPlayerSprite[i] = Sprite::create((PIC_PATH+StringUtils::format("message%d.png",i)).c_str());
			nextPlayerSprite[i]->setPosition(Point(765,380));
			this->addChild(nextPlayerSprite[i],PROP_LEVEL);
			//2����  ת��Ϊstring���Ͳ�ת�����ֽ�������
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
    
    //��ʾ������Ϣ�ı�ǩ
	timeLabel=LabelTTF::create("","Arial",28);
    //���ñ�ǩ�������ɫ
	timeLabel->setFontFillColor(Color3B::WHITE);
	timeLabel->setPosition(Vec2(900,290));
    this->addChild(timeLabel,30);
    
    //��ը����
    wangSprite=Sprite::create();
	wangSprite->setPosition(Point(0,0));
	this->addChild(wangSprite,100);
    
	wangDropSprite=Sprite::create(ANIM_PATH+string("bomb_f.png"));
	wangDropSprite->setPosition(Point(480,600));
	this->addChild(wangDropSprite,PROP_LEVEL);
	wangDropSprite->setScale(1.5);
	wangDropSprite->setVisible(false);
    
	//ը��
	zhaSprite=Sprite::create();
	zhaSprite->setPosition(Point(0,0));
	this->addChild(zhaSprite,100);
    
	zhaDropSprite=Sprite::create(ANIM_PATH+string("bomb1.png"));
	zhaDropSprite->setPosition(Point(480,600));
	this->addChild(zhaDropSprite,PROP_LEVEL);
	zhaDropSprite->setScale(1.5);
	zhaDropSprite->setVisible(false);
    
	//�ɻ�
	planeSprite = Sprite::create(PIC_PATH+string("plane.png"));
	planeSprite->setPosition(Point(1000,300));
	this->addChild(planeSprite,PROP_LEVEL);
	planeSprite->setVisible(false);
}

//��ʱ�ص�-����������ҵ���Ϣ
void GameLayer::updateDrawOther(float dt)
{
	//û����ҽ��룬��ǰ���Ϊ��һ��
	if(Constant::playerCount==1&&Constant::drawLogo)
	{
		unKnow[0]->setVisible(true);
		deKnow[0]->setVisible(true);
	}
	else if(Constant::playerCount==2&&Constant::drawLogo)
	{
		if(Constant::playerId==0)
		{
			//��һ��ͼ��
			unKnow[1]->setVisible(true);
			deKnow[1]->setVisible(true);
			//��ǰ���ͼ��
			unKnow[0]->setVisible(true);
			deKnow[0]->setVisible(true);
		}
		else if(Constant::playerId==1)
		{
			//��һ��ͼ��
			unKnow[2]->setVisible(true);
			deKnow[2]->setVisible(true);
			//��ǰ���ͼ��
			unKnow[0]->setVisible(true);
			deKnow[0]->setVisible(true);
		}
	}
	else if(Constant::playerCount==3&&Constant::drawLogo)
	{
		//��һ��ͼ��
        deKnow[1]->setVisible(true);
		unKnow[1]->setVisible(true);
		//��һ��ͼ��
        deKnow[2]->setVisible(true);
		unKnow[2]->setVisible(true);
		//��ǰ���ͼ��
        deKnow[0]->setVisible(true);
		unKnow[0]->setVisible(true);
		Constant::drawLogo=false;
	}
	//��������OK���ж��Ƿ������׼��
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
	//��ok������Ϊ���ɼ�
	if(Constant::readyFlag)
	{
		Constant::readyFlag=false;
		Constant::readyNum=0;
		for(int i=0;i<3;i++)
		{
			ready[i]->setVisible(false);
		}
	}
	//��������,����Ȩ����Ҳ�����ʾ�е���
	if(Constant::menuItem)
	{
		Constant::menuItem=false;
		if(Constant::whoFlag==Constant::playerId)
		{
			if(Constant::landlordCount<5)
			{
				//�жϳ��νл��Ƿǳ��Σ���������Ϊ�е����Ͳ��У�����Ϊ�������Ͳ���
				if(Constant::landlordCount==1)//�е���
				{
					addOrderOrNo();
				}
				else if(Constant::landlordCount!=1)//������
				{
					addQiangOrNo();
				}
			}
			else if(Constant::landlordCount==5&&Constant::whoFlag==Constant::playerId)//��ʼ��Ϸ���һ�ֳ���
			{
				resetSprite->setVisible(true);//��ɫ��ѡ
				chuSprite->setVisible(true);//��ɫ����
				tiShiMenu->setVisible(true);
			}
			else if(Constant::landlordCount>5&&Constant::whoFlag==Constant::playerId)
			{
				resetSprite->setVisible(true);//��ɫ��ѡ
				chuSprite->setVisible(true);//��ɫ����
				buChuMenu->setVisible(true);
			}
		}
	}
    if(Constant::drawAct)
    {
        //����һ���������
        for(int i=0;i<3;i++)
        {
            actKnow[Constant::oldGoldFlag]->setVisible(false);
        }
        //����ǰ�����Ϊ��һ�����
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
        //��ʾ��ǰ����Ȩ��ҵĽ��
        actKnow[Constant::oldGoldFlag]->setVisible(true);
    }

	//���Ƴ��Ʋ˵�������յ�0�����ܳ���ʱ�������ط�����Ƴ��˵���
	if(Constant::isDrawChuPai&&Constant::whoFlag==Constant::playerId)
	{
		Constant::isDrawChuPai=false;
		if(Constant::isCanChuPai==1&&Constant::upCardsCount!=0)	//����
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
        
		if(Constant::isBuChu==0||(Constant::lastPlayerLength==0&&Constant::nextPlayerLength==0))			//������ť
		{
			buChuMenu->setVisible(false);
		}else{
			buChuMenu->setVisible(true);
		}
	}
	if(Constant::isDrawReset)
	{
		Constant::isDrawReset=false;
		if(Constant::upCardsCount!=0)		//��ѡ��ť
		{
			resetMenu->setVisible(true);
			resetSprite->setVisible(false);
		}else{
			resetMenu->setVisible(false);
			resetSprite->setVisible(true);
		}
		tiShiMenu->setVisible(true);
	}
	//������Ҳ����Ƴ��Ʋ˵���
	if(Constant::whoFlag!=Constant::playerId)
	{
		chuMenu->setVisible(false);
		resetMenu->setVisible(false);
		buChuMenu->setVisible(false);
		tiShiMenu->setVisible(false);
		chuSprite->setVisible(false);
		resetSprite->setVisible(false);
	}
	//����������Ѿ�������
	if(Constant::pukeFlag)
	{
		Constant::pukeFlag=false;
		schedule(schedule_selector(GameLayer::updatePuke), 0.1f);
		//���ö�ʱ�ص�ָ�������ɻ�
		auto director = Director::getInstance();
		auto sched = director->getScheduler();
        
		//��ʱ�ص�update_puke  17�Σ����Ϊ0.2�룬�ӳ�0
		sched->schedule(SEL_SCHEDULE(&GameLayer::update_puke),this,0.13,16,0.1,false);
	}
	//���������Ѿ���������,���ұ���Ϊ����
	if(Constant::whoIsLandlord==Constant::playerId&&Constant::landlordHadPuke)
	{
		//����ɾ��֮ǰ��17���ƣ��Լ�������
		for(int j=0;j<17;j++)
		{
			this->removeChild(puke[Constant::PUKEARRAY[j]]->pukeSprite);
			this->removeChild(mask[Constant::PUKEARRAY[j]]);
		}
        
		/*
		 * ���»��Ƶ���20����
		 * �������¸����鸳ֵ
		 * ��ʼ����
		 */
		for(int i=0;i<20;i++)
		{
			Constant::PUKEARRAY[i]=Constant::tempPUKE[i];
            
			//�����˿˱�����
			mask[Constant::PUKEARRAY[i]] = Sprite::create(PIC_PATH+string("poke_gb_mask.png"));
			mask[Constant::PUKEARRAY[i]]->setPosition(90+iCount*40,85);
			this->addChild(mask[Constant::PUKEARRAY[i]],i+1);
			mask[Constant::PUKEARRAY[i]]->setVisible(false);
			//�˿�
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
	//���Ʊ�����
	if(Constant::landlordHadPuke)
	{
		Constant::landlordHadPuke=false;
		//���ñ���ͼ���ɼ�,ɾ��
		for(int j=0;j<3;j++)
		{
			this->removeChild(poke[j]);
		}
		//������ת��ʼ
		createRotate();
	}
	//���Ʊ���
	if(Constant::beiNum!=Constant::oldBeiNum&&Constant::beiNum!=15)
	{
		Constant::oldBeiNum=Constant::beiNum;
        
		//ת��Ϊstring����
		string beiStr =StringUtils::toString(Constant::beiNum);
		//��ʾ��ǰ����
		bLabelAtlas->setString(beiStr);
		bLabelAtlas->setString(beiStr);
		//���ñ���*2
		setBeiMove();
		if(Constant::effectFlag)
		{
			//������Ч
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
			(
             (SOUND_PATH+string("Special_Multiply.mp3")).c_str()
             );
		}
	}
	//�������������������е��������������Ƿ�ɼ�,
	if(Constant::landlordListNum==3)
	{
		Constant::landlordListNum=0;
		for(int i=0;i<3;i++)
		{
			//���Ƚ�ԭ��������
			playerSprite[i]->setVisible(false);
			nextPlayerSprite[i]->setVisible(false);
			lastPlayerSprite[i]->setVisible(false);
            
			//����֮�����»�
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
	//ɾ��������������
	if(Constant::clearLandlordState)
	{
		Constant::clearLandlordState=false;
		//�յ�20��֮����ɾ��
		for(int j=0;j<5;j++)
		{
			this->removeChild(playerSprite[j]);
			this->removeChild(nextPlayerSprite[j]);
			this->removeChild(lastPlayerSprite[j]);
		}
	}
	//�����������
	if(Constant::drawCardsFlag==1)
	{
		Constant::drawCardsFlag =0;
		//ת��Ϊstring����
		string nextPukeStr =StringUtils::toString(Constant::nextPlayerCardsCount);
		//��ʾ�������˿���Ŀ
		nextLabelAtlas->setString(nextPukeStr);
		//2
		string lastPukeStr =StringUtils::toString(Constant::lastPlayerCardsCount);
		//��ʾ�������˿���Ŀ
		lastLabelAtlas->setString(lastPukeStr);
	}
	//ɾ���е�����������menu
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
//��ʱ�ص��������Ƶ����Ͳ��ų��Ƶ���Ч
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
                 (SOUND_PATH+StringUtils::format("Man_buyao%d.mp3",i)).c_str()//ת��Ϊstring���Ͳ�ת�����ֽ�������
                 );
                break;
		}
	}
}
//�ɻ�
void GameLayer::setPlaneMess()
{
	planeSprite->setVisible(false);
	planeSprite->setPosition(Point(1000,300));
}
//��ը ��֡����
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
//����ը��
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
//��ʱ�ص�������
void GameLayer::update_puke()
{
	if(iCount==17)
	{
		iCount=0;
		Constant::pukeNumber=0;
		Constant::pukeFlag=false;
		this->unschedule(SEL_SCHEDULE(&GameLayer::update_puke));
	}
	//==========��ʾ�˿�����=======
	Constant::pukeNumber++;
	//ת��Ϊstring����
	string pukeStr =StringUtils::toString(Constant::pukeNumber);
	//��ʾ����������ҵ��˿���Ŀ
	lastLabelAtlas->setString(pukeStr);
	nextLabelAtlas->setString(pukeStr);
    
	//ÿ��һ���Ʋ���һ����Ч
	if(Constant::effectFlag)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
		(
         (SOUND_PATH+string("SpecSelectCard.ogg")).c_str()
         );
	}
	//�����˿˱�����
	mask[Constant::PUKEARRAY[iCount]] = Sprite::create(PIC_PATH+string("poke_gb_mask.png"));
	mask[Constant::PUKEARRAY[iCount]]->setPosition(170+iCount*40,80);
	this->addChild(mask[Constant::PUKEARRAY[iCount]],iCount+1);
	mask[Constant::PUKEARRAY[iCount]]->setVisible(false);
	//�˿�
	(puke[Constant::PUKEARRAY[iCount]]->pukeSprite)->setPosition(Point(170+iCount*40,85));
	this->addChild(puke[Constant::PUKEARRAY[iCount]]->pukeSprite,iCount);
	iCount++;
}
void GameLayer::updateRotate(float ft)
{
	angle=(angle+1);
	if(angle>=180)//ÿ������180������
	{
		angle=angle-180;
		//ֹͣ��ǰ��ʱ�ص�����
		this->unschedule(SEL_SCHEDULE(&GameLayer::updateRotate));
		firstCard->setFlippedX(false);
		secondCard->setFlippedX(false);
		thirdCard->setFlippedX(false);
	}
    
	//���������=======��1��==========
	float firstDisX=(PKPKD_HALF-PKPKD_HALF*cos(angle*PI/180.0f));	//x����ƫ����
	float firstDisZ=(PKPKD_HALF*sin(angle*PI/180.0f));				//z����ƫ����
    
	firstCard->setPositionX(firstX+0.2*firstDisX);
	firstCard->setPositionZ(firstDisZ);
	firstCard->setRotation3D(Vec3(0,angle,0));
	if(angle==92)
	{
		firstCard->setTexture(fm);
		firstCard->setTextureRect(Rect(firstCol*72,firstRow*108,72,108));
		firstCard->setFlippedX(true);
	}
    
	//���������=======��2��
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
    
	//���������=======��3��
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
//����������
void GameLayer::createRotate()
{
	//��һ��
	firstCol=8-Constant::lastPukeId[0]%9;//��
	firstRow=Constant::lastPukeId[0]/9;	//��
	//�ڶ���
	secondCol=8-Constant::lastPukeId[1]%9;	//��
	secondRow=Constant::lastPukeId[1]/9;	//��
	//��3��
	thirdCol=8-Constant::lastPukeId[2]%9;	//��
	thirdRow=Constant::lastPukeId[2]/9;	//��
    //����������ͼ
    pfm=Director::getInstance()->getTextureCache()->addImage(PIC_PATH+string("poke_back_header.png"));
    pzm=Director::getInstance()->getTextureCache()->addImage(PIC_PATH+string("puke_whole.png"));
    //��ǰ������ͼ
    zm = pfm;
    fm = pzm;
    
    //������ת�õ��˿��ƾ���
    //=========��1��
    firstCard = Sprite::createWithTexture(zm);
    firstX = 400.0;//�м���������м�λ����ת�������м�x���겻��
    //���þ����λ��
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
	//��������ӵ�������
    this->addChild(firstCard,PROP_LEVEL);
    
    firstCard->setFlippedX(true);//����ˮƽ��ת
    //===========��2��
    secondCard = Sprite::createWithTexture(zm);
    secondX = 475.0;//�м���������м�λ����ת�������м�x���겻��
    //���þ����λ��
    secondCard->setPosition
	(
     Point
     (
      secondX,
      490
      )
     );
    secondCard->setScale(0.8);
	//��������ӵ�������
    this->addChild(secondCard,PROP_LEVEL);
    secondCard->setFlippedX(true);//����ˮƽ��ת
    
    //=============��3��
    thirdCard = Sprite::createWithTexture(zm);
    thirdX = 550.0;//�м���������м�λ����ת�������м�x���겻��
    //���þ����λ��
    thirdCard->setPosition
	(
     Point
     (
      thirdX,
      490
      )
     );
	//��������ӵ�������PROP_LEVEL
    this->addChild(thirdCard,PROP_LEVEL);
    thirdCard->setScale(0.8);
    thirdCard->setFlippedX(true);//����ˮƽ��ת
	//���ö�ʱ�ص�ָ�������ɻ�
	schedule(schedule_selector(GameLayer::updateRotate), 0.015f);
}
//�жϱ�����Ϸ���ֵĲ��������Լ���������Ч
int GameLayer::random()
{
	int number = rand()%4;
	return number;
}
//����������Ч
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
    
	//�е��������Ч
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
		//������Ч
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
		(
         (SOUND_PATH+StringUtils::format("Man_buyao%d.mp3",i)).c_str()//ת��Ϊstring���Ͳ�ת�����ֽ�������
         );
		if(i!=0)//��������Ч
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
			(
             (SOUND_PATH+StringUtils::format("Man_Rob%d.mp3",i)).c_str()//ת��Ϊstring���Ͳ�ת�����ֽ�������
             );
		}
	}
	//��������Ч
	for(int i=1;i<16;i++)
	{
		//��������Ч
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
		(
         (SOUND_PATH+StringUtils::format("Man_%d.mp3",i)).c_str()//ת��Ϊstring���Ͳ�ת�����ֽ�������
         );
		if(i<14)
		{
			//��������Ч
			CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
			(
             (SOUND_PATH+StringUtils::format("Man_dui%d.mp3",i)).c_str()//ת��Ϊstring���Ͳ�ת�����ֽ�������
             );
			//��������Ч
			CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
			(
             (SOUND_PATH+StringUtils::format("Man_tuple%d.mp3",i)).c_str()//ת��Ϊstring���Ͳ�ת�����ֽ�������
             );
		}
	}
	//�ɻ���Ч
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
     (SOUND_PATH+string("Man_feiji.mp3")).c_str()
     );
	//������Ч
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
     (SOUND_PATH+string("Man_liandui.mp3")).c_str()
     );
	//����һ��Ч
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
     (SOUND_PATH+string("Man_sandaiyi.mp3")).c_str()
     );
	//����һ����Ч
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
     (SOUND_PATH+string("Man_sandaiyidui.mp3")).c_str()
     );
	//˳����ЧMan_sidaier
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
     (SOUND_PATH+string("Man_shunzi.mp3")).c_str()
     );
	//�Ĵ�����Ч
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
     (SOUND_PATH+string("Man_sidaier.mp3")).c_str()
     );
	//�Ĵ�������Ч
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
     (SOUND_PATH+string("Man_sidailiangdui.mp3")).c_str()
     );
	//��ը��Ч
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
	//������Ч
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
     (SOUND_PATH+string("Special_Multiply.mp3")).c_str()
     );
	//������Ч
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
     (SOUND_PATH+string("Special_give.mp3")).c_str()
     );
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
     (SOUND_PATH+string("Special_plane.mp3")).c_str()
     );
}
//���Ų��С��С�������������
void GameLayer::playOrderOrRob()
{
	if(Constant::soundType==0)//����
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
		(
         (SOUND_PATH+string("Man_NoOrder.mp3")).c_str()
         );
	}
	else if(Constant::soundType==1)//�е���
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
		(
         (SOUND_PATH+string("Man_Order.mp3")).c_str()
         );
	}
	else if(Constant::soundType==2)//����
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
		(
         (SOUND_PATH+string("Man_NoRob.mp3")).c_str()
         );
	}
	else if(Constant::soundType==3)//������
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
		(
         (SOUND_PATH+StringUtils::format("Man_Rob%d.mp3",(Constant::landlordCount-2))).c_str()//ת��Ϊstring���Ͳ�ת�����ֽ�������
         );
	}
}
//������Ϸ��ʼ�󣬳��ƵȰ�ť
void GameLayer::playGameBtn()
{
	//���ƻ�ɫ����
	chuSprite = Sprite::create(PIC_PATH+string("play_btn_disable.png"));
	chuSprite->setPosition(Point(800,220));
	this->addChild(chuSprite,PROP_LEVEL);
	chuSprite->setVisible(false);
	//��ѡ
	resetSprite = Sprite::create(PIC_PATH+string("reset_btn_disable.png"));
	resetSprite->setPosition(Point(480,220));
	this->addChild(resetSprite,PROP_LEVEL);
	resetSprite->setVisible(false);
	//==========�˵���
	//����
	MenuItemImage *buChuItem = MenuItemImage::create
	(
     PIC_PATH+string("no_red_btn.png"),
     PIC_PATH+string("no_red_btn_down.png"),
     CC_CALLBACK_1(GameLayer::menuBuChuCallback, this)
     );
	//���ò˵����λ��
	buChuItem->setPosition(Point(320,220));
	buChuMenu = Menu::create(buChuItem, NULL);
	buChuMenu->setPosition(Point::ZERO);
	this->addChild(buChuMenu,BTN_LEVEL);
	buChuMenu->setVisible(false);
	//��ѡ
	MenuItemImage *resetItem = MenuItemImage::create
	(
     PIC_PATH+string("reset_blue_btn.png"),
     PIC_PATH+string("reset_blue_btn_down.png"),
     CC_CALLBACK_1(GameLayer::menuResetCallback, this)
     );
	//���ò˵����λ��
	resetItem->setPosition(Point(480,220));
	resetMenu = Menu::create(resetItem, NULL);
	resetMenu->setPosition(Point::ZERO);
	this->addChild(resetMenu,BTN_LEVEL);
	resetMenu->setVisible(false);
	//����
	MenuItemImage *chuItem = MenuItemImage::create
	(
     PIC_PATH+string("play_green_btn.png"),
     PIC_PATH+string("play_green_btn_down.png"),
     CC_CALLBACK_1(GameLayer::menuPlayCallback, this)
     );
	//���ò˵����λ��
	chuItem->setPosition(Point(800,220));
	chuMenu = Menu::create(chuItem, NULL);
	chuMenu->setPosition(Point::ZERO);
	this->addChild(chuMenu,BTN_LEVEL);
	chuMenu->setVisible(false);
	//��ʾ
	MenuItemImage *tiShiItem = MenuItemImage::create
	(
     PIC_PATH+string("tishi_blue_btn.png"),
     PIC_PATH+string("tishi_blue_btn_down.png"),
     CC_CALLBACK_1(GameLayer::menuTishi, this)
     );
	//���ò˵����λ��
	tiShiItem->setPosition(Point(640,220));
	tiShiMenu = Menu::create(tiShiItem, NULL);
	tiShiMenu->setPosition(Point::ZERO);
	this->addChild(tiShiMenu,BTN_LEVEL);
	tiShiMenu->setVisible(false);
}
//��ӽе����Ͳ��е���
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
//����������Ͳ�������
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
	//��ʼ׼���������������׼����Ϣ
	if(BNSocketUtil::connectFlag)
	{
		//�������ʹ���0����ʾ����Ϊ��������ʾ�Ѿ�׼��
		BNSocketUtil::sendInt(0);
	}
	//����׼����ť���ɼ�
	readyMenu->setVisible(false);
}
//setting����
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
        
		checkCreate = true;		//��ѡ���Ѿ�����
		set = true;				//����ѡ���Ѿ���
		first = false;			//��һ���Ѿ���ɴ���
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
			//���ùرղ˵����λ��
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
			//���ò˵����λ��
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

//ȡ��
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
//ȷ��
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
//�е���
void GameLayer::menuOrderCallback(Ref* sender)
{
	//������������не����Ͳ�����Ϊ���ɼ�
	orderMenu->setVisible(false);
	noOrderMenu->setVisible(false);
	//��������������ݱ�����
	if(BNSocketUtil::connectFlag)
	{
		//�е��������������1
		BNSocketUtil::sendInt(1);
		BNSocketUtil::sendInt(1);
	}
}
//����
void GameLayer::menuNoOrderCallback(Ref* sender)
{
	//���е����Ͳ��е�������
	orderMenu->setVisible(false);
	noOrderMenu->setVisible(false);
	if(BNSocketUtil::connectFlag)
	{
		//�е��������������1
		BNSocketUtil::sendInt(1);
		BNSocketUtil::sendInt(0);
	}
}
//�������ı�
void GameLayer::menuQiangCallback(Ref* sender)
{
	bqMenu->setVisible(false);
	qdzMenu->setVisible(false);
	if(BNSocketUtil::connectFlag)
	{
		//�е��������������1
		BNSocketUtil::sendInt(1);//��־λ
		BNSocketUtil::sendInt(1);//����
	}
}
//��������
void GameLayer::menuNoQiangCallback(Ref* sender)
{
	if(BNSocketUtil::connectFlag)
	{
		//�е��������������1
		BNSocketUtil::sendInt(1);
		//���߷�������ǰ״̬Ϊ����
        
		BNSocketUtil::sendInt(0);
	}
	bqMenu->setVisible(false);
	qdzMenu->setVisible(false);
}
void GameLayer::menuTishi(Ref* sender)			//��ʾ
{
	if(BNSocketUtil::connectFlag)
	{
		BNSocketUtil::sendInt(4);
	}
}
//2��
void GameLayer::menuChaCallback(Ref* sender)
{
	bei2->setVisible(false);
	bei2->setPosition(Point(480,310));
}
void GameLayer::menuBuChuCallback(Ref* sender)
{
	//���Ѿ����𣬵�ѡ���˲����ƣ����������������
	if(BNSocketUtil::connectFlag)
	{
		BNSocketUtil::sendInt(3);//��ʾҪ����
		BNSocketUtil::sendInt(0);//������
	}
}
//��ѡ--��̧����Ʒ���
void GameLayer::menuResetCallback(Ref* sender)
{
	for(int i=0;i<Constant::playerCardsCount;i++)
	{
		int lastSize = Constant::playerCardsCount/2;
		int lastLiftX =  490-lastSize*40;//���ڴ�����������Զ����
		//int lastMid=0;
		puke[Constant::PUKEARRAY[i]]->pukeSprite->setPosition(Point(lastLiftX+40*i,85));
		Constant::upCards[Constant::PUKEARRAY[i]]=0;
	}
	Constant::upCardsCount=0;
	Constant::isDrawReset=true;
}
//��ʼ��Ϸ����
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
	//���Ѿ�����׼�����ƣ����������������
	if(BNSocketUtil::connectFlag)
	{
		BNSocketUtil::sendInt(3);	//��ʾҪ����
		BNSocketUtil::sendInt(1);	//����
	}
	//��̧�������Ϊ0
	Constant::upCardsCount=0;
    
}
//���ñ���˳��ִ��
void GameLayer::setBeiMove()
{
	bei2->setVisible(true);
	//˳����
	bei2->runAction(
                    Sequence::create(
                                     MoveTo::create(2.0,Point(480,340)),
                                     CallFuncN::create(CC_CALLBACK_1(GameLayer::menuChaCallback, this)),
                                     NULL)
					);
}
//�з��˿���
void GameLayer::initPuKe()
{
	Texture2D* tt2d = Director::getInstance()->getTextureCache()->addImage(PIC_PATH+string("puke_whole.png"));
	//���
	int pukeSpriteCount= 0;
    
	for(int i=0;i<648;i=i+108)//��6��
	{
		for(int j=648-72;j>=0;j=j-72)//9��
		{
			Rect r = Rect(j,i,72,108);//��ȡ���
			puke[pukeSpriteCount] = new PuKe(tt2d,pukeSpriteCount,r,648-j+120,i+59);//��������
			puke[pukeSpriteCount]->refresh();//����λ��
			puke[pukeSpriteCount]->pukeSprite->setScale(1.5);//�Ŵ�
			puke[pukeSpriteCount]->pukeSprite->retain();
			pukeSpriteCount++;
		}
	}
}
//touch,ֻ�н����������������Ϻ󣬲��ܴ�����
bool GameLayer::onTouchBegan(Touch* touch, Event* event)
{
	beginX = touch->getLocation().x;
	beginY = touch->getLocation().y;
    
	if(Constant::whoFlag==Constant::playerId&&Constant::landlordCount>=5)//�ж��Ƿ��Ѿ����Ƴɹ�
	{
		//�����˿�����
		for(int k=0;k<Constant::playerCardsCount;k++)
		{
			//��ȡÿ���˿���λ��
			Point pkPoint = puke[Constant::PUKEARRAY[k]]->pukeSprite->getPosition();
			//�ж��Ƿ������˿���
			if(abs(beginX- pkPoint.x+32)<=36&&abs(beginY- pkPoint.y)<=54)
			{
				mask[Constant::PUKEARRAY[k]]->setPosition(pkPoint);
				mask[Constant::PUKEARRAY[k]]->setVisible(true);
				break;//ֻ��̧��һ����
			}
		}
	}
	return true;
}
//�����ƶ�
void GameLayer::onTouchMoved(Touch *touch, Event *event)
{
	moveX = touch->getLocation().x;
	moveY = touch->getLocation().y;
	if(Constant::whoFlag==Constant::playerId&&Constant::landlordCount>=5)//�ж��Ƿ��Ѿ����Ƴɹ�
	{
		//�����˿�����===������
		for(int k=0;k<Constant::playerCardsCount;k++)
		{
			//��ȡ�˿˵�λ��
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
//��������
void GameLayer::onTouchEnded(Touch *touch, Event *event)
{
	Point point = touch->getLocation();
	int m=0;
	if(Constant::whoFlag==Constant::playerId&&Constant::landlordCount>=5)//�ж��Ƿ��Ѿ����Ƴɹ�
	{
		//�����˿�����--�����˿�������Ӧ
		for(int k=0; k<Constant::playerCardsCount; k++)
		{
			//��ȡ�˿˵�λ��
			Point pkPoint = puke[Constant::PUKEARRAY[k]]->pukeSprite->getPosition();
			//����������
			if(k==Constant::playerCardsCount-1)
			{
				beginX-=32;
			}
			if(abs(beginX- pkPoint.x+32)<=36&&abs(beginY- pkPoint.y)<=54)//��������,+32����ƫ
			{
				if(Constant::upCards[Constant::PUKEARRAY[k]]==1)//�Ѿ�̧��
				{
					puke[Constant::PUKEARRAY[k]]->pukeSprite->setPosition(Point(pkPoint.x,pkPoint.y-18));
					Constant::upCards[Constant::PUKEARRAY[k]]=0;
					Constant::upCardsCount--;
                    
				}else{//��δ̧��
					puke[Constant::PUKEARRAY[k]]->pukeSprite->setPosition(Point(pkPoint.x,pkPoint.y+18));
					Constant::upCards[Constant::PUKEARRAY[k]]=1;
					Constant::upCardsCount++;			//�Ѿ�����
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
				break;//ֻ��̧��һ����
			}
		}
        
		//�����˿�����
		for(int k=0;k<Constant::playerCardsCount;k++)
		{
			//��ȡ�˿˵�λ��
			Point pkPoint = puke[Constant::PUKEARRAY[k]]->pukeSprite->getPosition();
            
			//�����һ���
			if(pkPoint.x<=point.x&&pkPoint.x>=beginX&&abs(pkPoint.y-beginY)<54&&abs(pkPoint.y-point.y)<81)
			{
				if(Constant::upCards[Constant::PUKEARRAY[k]]==1)
				{
					puke[Constant::PUKEARRAY[k]]->pukeSprite->setPosition(Point(pkPoint.x,pkPoint.y-18));
					Constant::upCards[Constant::PUKEARRAY[k]]=0;
					Constant::upCardsCount--;
				}else{
					puke[Constant::PUKEARRAY[k]]->pukeSprite->setPosition(Point(pkPoint.x,pkPoint.y+18));
					Constant::upCards[Constant::PUKEARRAY[k]]=1;					//���ñ�־λ ��ʾ�˿��Ѿ�̧��
					Constant::upCardsCount++;		//���̧��
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
            
			//���ҵ��󻬶�
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
			//���ø÷���������ǰ��׼������
			isChuPai();
		}else
		{
			Constant::isDrawChuPai=true;
			Constant::isDrawReset=true;
		}
        
	}
}
//�ж��Ƿ����
void GameLayer::isChuPai()
{
	//���Ѿ�����׼�����������������
	if(BNSocketUtil::connectFlag)
	{
		BNSocketUtil::sendInt(2);							//��ʾҪ���͵����Ƶ���Ŀ������
		int upCardCount=Constant::upCardsCount;
		BNSocketUtil::sendInt(upCardCount);					//��Ŀ
		for(int i=0;i<Constant::playerCardsCount;i++)
		{
			if(Constant::upCards[Constant::PUKEARRAY[i]]==1)
			{
				//��ʼ׼���������������׼����Ϣ
				//��������
				int send=Constant::PUKEARRAY[i];
				BNSocketUtil::sendInt(send);
			}
		}
	}
}
//��ȡϵͳʱ��
void GameLayer::getSystemTime(float dt)
{
    time_t t = time(0);
    char tmp[64];
    strftime( tmp, sizeof(tmp),"%H:%M",localtime(&t) );
    timeLabel->setString(tmp);
}
