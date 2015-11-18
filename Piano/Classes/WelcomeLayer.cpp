#include "WelcomeLayer.h"
#include "AppMacros.h"

using namespace cocos2d;
using namespace std;

//实现MTLayer类中的init方法，初始化布景
bool WelcomeLayer::init()
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
	Sprite* logo = Sprite::create(pic_RESOURE_PATH + "logo.png");
	logo->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
	logo->setOpacity(0);
	this->addChild(logo, 1);

	logo->runAction(
			Sequence::create(
					FadeIn::create(1),
					CallFunc::create(CC_CALLBACK_0(WelcomeLayer::musicLoad, this)),
					FadeOut::create(1),
					CallFunc::create(CC_CALLBACK_0(WelcomeLayer::goToLoad, this)),
					NULL
	));

	return true;
}
void WelcomeLayer::musicLoad()
{
	string number;
	for(int i = 0; i<38; i++)
	{
		if(i<10)
		{
			number  = "0" + StringUtils::format("%d", i);
		}else
		{
			number = StringUtils::format("%d", i);
		}
		string route = music_RESOURE_PATH + "piano" + number + ".mp3";
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(route.c_str());
	}
}

void WelcomeLayer::goToLoad()
{
	sceneManager->goToLoadScene();
}

