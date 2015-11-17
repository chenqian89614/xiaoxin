#include "AppDelegate.h"
#include "GameSceneManager.h"
#include "SimpleAudioEngine.h"
#include "MainLayer.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate() 
{

}

//初始化方法
bool AppDelegate::applicationDidFinishLaunching()
{
    //获取导演
    auto director = Director::getInstance();
    //获取绘制用GLView
    auto glview = director->getOpenGLView();
    //若不存在glview则重新创建
    if(!glview)
    {
         glview = GLView::create("Test Cpp");
    }
    //设置绘制用GLView
    director->setOpenGLView(glview);
    //设置目标分辨率,别的分辨率的屏幕将自动上下或左右留白进行多分辨率自适应
    glview->setDesignResolutionSize(540,960, kResolutionShowAll);
	//设置为显示FPS等信息
    director->setDisplayStats(false);
    //系统模拟时间间隔
    director->setAnimationInterval(1.0 / 60);
    //创建欢迎场景
    auto scene = new GameSceneManager();
    scene->createMainScene();
    //跌换到欢迎场景显示
    director->runWithScene(scene->mainScene);
    //加载音乐
    initSound();

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
    //进入前台播放声音
    if(MainLayer::musicFlag)
    {
    	CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    }
}
void AppDelegate::initSound(){							//加载音乐的方法
	CocosDenshion::SimpleAudioEngine::getInstance()->	//加载背景音乐
							preloadBackgroundMusic("sounds/playscene.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->	//加载小鸟跳跃音效
							preloadEffect("sounds/sfx_wing.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->	//加载得分音效
							preloadEffect("sounds/sfx_point.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->	//加载碰撞音效
							preloadEffect("sounds/sfx_hit.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->	//加载死亡下落音效
							preloadEffect("sounds/sfx_die.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->	//加载夹水果音效
							preloadEffect("sounds/eat.wav");
}

