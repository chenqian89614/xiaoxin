#include "ChoiceLayer.h"
using namespace cocos2d;
#include "SimpleAudioEngine.h"
#include "MusicFlag.h"
#include "AppConstant.h"
using namespace std;

bool ChoiceLayer::isMusic=true;
bool ChoiceLayer::isSound=true;
int ChoiceLayer::escChoiceCount=0;
ChoiceLayer::~ChoiceLayer()
{

}

//实现类中的init方法，初始化布景
bool ChoiceLayer::init()
{
	//调用父类的初始化
    if ( !Layer::init() )
    {
        return false;
    }
    //获取可见区域尺寸
    Size visibleSize = Director::getInstance()->getVisibleSize();
    //获取可见区域原点坐标
    Point origin = Director::getInstance()->getVisibleOrigin();

    //创建一个精灵对象，包含bg.png图片
    bgSprite = Sprite::create(pic_PATH+"bg.jpg");
    //设置精灵对象的位置
    bgSprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    //将精灵添加到布景中
    this->addChild(bgSprite, 0);

    dibanSprite = Sprite::create(shezhiPic_PATH+"diban.png");//创建一个精灵对象，充当底板
    dibanSprite->setScale(1.2);
    //设置底板精灵位置
    dibanSprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(dibanSprite,0);//将底板精灵添加到布景中

    isMusic=loadMusicFlag();
	isSound=loadSoundFlag();

    //创建音乐开按钮精灵
    if(isMusic)
    {
    	music = Sprite::create(shezhiPic_PATH+"musicOn.png");
    }else
    {
    	music = Sprite::create(shezhiPic_PATH+"musicOff.png");
    }

	//设置精灵位置
    music->setPosition(Point( origin.x+200, origin.y+245));
    dibanSprite->addChild(music,0);//将音乐精灵添加到底板精灵中
    //创建声音开按钮精灵
    if(isSound)
    {
    	sound = Sprite::create(shezhiPic_PATH+"soundOn.png");
    }else
    {
    	sound = Sprite::create(shezhiPic_PATH+"soundOff.png");
    }

	//设置精灵位置
	sound->setPosition(Point( origin.x+200, origin.y+105));
	dibanSprite->addChild(sound,0);//将声音精灵添加到底板精灵中

	auto backItem = MenuItemImage::create
	(
			pic_PATH+"back.png",
			pic_PATH+"back.png",
			CC_CALLBACK_0(ChoiceLayer::onBack, this)//点击时执行的回调方法
	);
	backItem->setPosition(
			Point(
				origin.x - backItem->getContentSize().width/2+520,	//X坐标
				origin.y -backItem->getContentSize().height/2+940		//Y坐标
			)
			);
	//创建菜单对象
	auto backMenu = Menu::create(backItem, NULL);
	//设置菜单位置
	backMenu->setPosition(Point::ZERO);
	//将菜单添加到布景中
	this->addChild(backMenu, 1);

	//创建单点触摸监听
	EventListenerTouchOneByOne* listenerMusic = EventListenerTouchOneByOne::create();
	//设置下传触摸
	listenerMusic->setSwallowTouches(true);
	//开始触摸时回调controlMusic方法
	listenerMusic->onTouchBegan = CC_CALLBACK_2(ChoiceLayer::controlMusic, this);
	//添加到监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerMusic, music);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerMusic->clone(), sound);

    return true;
}

bool ChoiceLayer::controlMusic(Touch* touch,Event* event)
{
	//获取的当前触摸的对象，并转化为精灵类型
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	//获取当前坐标
	auto location = target->convertToNodeSpace(touch->getLocation());
	//获取精灵的大小
	auto size = target->getContentSize();
	//创建一个矩形对象，其大小与精灵相同
	auto rect = Rect(0, 0, size.width, size.height);
	if(rect.containsPoint(location)&&target==music)
	{
		if(isMusic)
		{
			if(isSound)
			{
				wl->playClickSound();//播放点击声音
			}
			wl->pauseBgMusic();//暂停播放背景音乐
			music->setTexture(shezhiPic_PATH+"musicOff.png");
			isMusic=false;

			UserDefault::getInstance()->setBoolForKey("bool1",false);	//存储是否开启背景音乐
			UserDefault::getInstance()->flush();								//事实写入

		}else
		{
			if(isSound)
			{
				wl->playClickSound();//播放点击声音
			}
//			wl->resumeBgMusic();//继续播放背景音乐
			wl->playBgMusic();//播放背景音乐
			music->setTexture(shezhiPic_PATH+"musicOn.png");
			isMusic=true;

			UserDefault::getInstance()->setBoolForKey("bool1",true);	//存储是否开启背景音乐
			UserDefault::getInstance()->flush();								//事实写入
		}
		return true;
	}else if(target==sound&&rect.containsPoint(location))
	{
		if(isSound)
		{
			wl->pauseSound();//暂停播放音效
			wl->playClickSound();//播放点击声音
			sound->setTexture(shezhiPic_PATH+"soundOff.png");
			isSound=false;

			UserDefault::getInstance()->setBoolForKey("bool2",false);//存储是否开启声音特效
			UserDefault::getInstance()->flush();								//事实写入

		}else
		{
			wl->resumeSound();//继续播放音效
			sound->setTexture(shezhiPic_PATH+"soundOn.png");
			isSound=true;

			UserDefault::getInstance()->setBoolForKey("bool2",true);//存储是否开启声音特效
			UserDefault::getInstance()->flush();								//事实写入
		}
		return true;
	}else{
		return false;
	}

	return true;
}

void ChoiceLayer::onBack()
{
	if(isSound)
	{
		wl->playSwitchSound();//播放切换音效
	}
	++escChoiceCount;
	gsm->goWelcomeScene();
}
