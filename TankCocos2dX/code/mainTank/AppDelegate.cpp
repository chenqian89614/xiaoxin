#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "Constant.h"
#include "AppMacros.h"

USING_NS_CC;

AppDelegate::AppDelegate(){}
AppDelegate::~AppDelegate(){}

//初始化方法
bool AppDelegate::applicationDidFinishLaunching()
{
	//获取导演
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	//若不存在glview则重新创建
	if(!glview)
	{
		glview = GLView::create("Test Cpp");
	}
	//设置绘制用GLView
	director->setOpenGLView(glview);
	//设置目标分辨率,别的分辨率的屏幕将自动上下或左右留白进行多分辨率自适应
	glview->setDesignResolutionSize(960,540,ResolutionPolicy::SHOW_ALL);
	//设置为显示FPS等信息
	director->setDisplayStats(false);

	//系统模拟时间间隔
	director->setAnimationInterval(1.0 / 60);
	//创建欢迎场景
	Scene *scene = TankSceneManager::WelcomeCreate();
	//跌换到欢迎场景显示
	director->runWithScene(scene);

	//加载背景音乐
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic
	(
		(SOUND_PATH+std::string("background.mp3")).c_str()
	);
	//加载吃到奖励的音效
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
		(SOUND_PATH+std::string("eatprops.wav")).c_str()
	);
	//加载爆炸音效
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
		(SOUND_PATH+std::string("grenada.ogg")).c_str()
	);
	//加载爆炸音效
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
		(SOUND_PATH+std::string("lose.mp3")).c_str()
	);
	//加载爆炸音效
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
		(SOUND_PATH+std::string("rocket_shoot2.ogg")).c_str()
	);
	//加载爆炸音效
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
		(SOUND_PATH+std::string("select.wav")).c_str()
	);

	Constant::musicFlag=UserDefault::getInstance()->getBoolForKey("music", true);
	Constant::effectFlag=UserDefault::getInstance()->getBoolForKey("effect", true);
	Constant::playMusic();

	return true;
}

//当程序进入后台时调用此方法
void AppDelegate::applicationDidEnterBackground()
{
	//停止动画
	Director::getInstance()->stopAnimation();
	//如果有声音的话要调用下面一句暂停声音播放
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

//当程序进入前台时调用
void AppDelegate::applicationWillEnterForeground()
{
	//开始动画
	Director::getInstance()->startAnimation();
	//如果有声音的话要调用下面一句开始声音播放
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
