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

//��ʼ������
bool AppDelegate::applicationDidFinishLaunching()
{
    //��ȡ����
    auto director = Director::getInstance();
    //��ȡ������GLView
    auto glview = director->getOpenGLView();
    //��������glview�����´���
    if(!glview)
    {
         glview = GLView::create("Test Cpp");
    }
    //���û�����GLView
    director->setOpenGLView(glview);
    //����Ŀ��ֱ���,��ķֱ��ʵ���Ļ���Զ����»��������׽��ж�ֱ�������Ӧ
    glview->setDesignResolutionSize(540,960, kResolutionShowAll);
	//����Ϊ��ʾFPS����Ϣ
    director->setDisplayStats(false);
    //ϵͳģ��ʱ����
    director->setAnimationInterval(1.0 / 60);
    //������ӭ����
    auto scene = new GameSceneManager();
    scene->createMainScene();
    //��������ӭ������ʾ
    director->runWithScene(scene->mainScene);
    //��������
    initSound();

    return true;
}

//����������̨ʱ���ô˷���
void AppDelegate::applicationDidEnterBackground()
{
	//ֹͣ����
    Director::getInstance()->stopAnimation();
    //����������Ļ�Ҫ��������һ����ͣ��������
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

//���������ǰ̨ʱ����
void AppDelegate::applicationWillEnterForeground()
{
	//��ʼ����
    Director::getInstance()->startAnimation();
    //����ǰ̨��������
    if(MainLayer::musicFlag)
    {
    	CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    }
}
void AppDelegate::initSound(){							//�������ֵķ���
	CocosDenshion::SimpleAudioEngine::getInstance()->	//���ر�������
							preloadBackgroundMusic("sounds/playscene.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->	//����С����Ծ��Ч
							preloadEffect("sounds/sfx_wing.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->	//���ص÷���Ч
							preloadEffect("sounds/sfx_point.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->	//������ײ��Ч
							preloadEffect("sounds/sfx_hit.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->	//��������������Ч
							preloadEffect("sounds/sfx_die.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->	//���ؼ�ˮ����Ч
							preloadEffect("sounds/eat.wav");
}

