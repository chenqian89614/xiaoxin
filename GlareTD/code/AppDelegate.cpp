#include "AppDelegate.h"
#include "GameSceneManager.h"

using namespace cocos2d;

AppDelegate::AppDelegate(){}
AppDelegate::~AppDelegate(){}

//��ʼ������
bool AppDelegate::applicationDidFinishLaunching()
{
    //��ȡ����
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    //��������glview�����´���
    if(!glview)
    {
    	glview = GLView::create("Test Cpp");
    }
    //���û�����GLView
    director->setOpenGLView(glview);
    //����Ŀ��ֱ���,��ķֱ��ʵ���Ļ���Զ����»��������׽��ж�ֱ�������Ӧ
    glview->setDesignResolutionSize(800,480,ResolutionPolicy::SHOW_ALL);
	//����Ϊ��ʾFPS����Ϣ
    director->setDisplayStats(false);
    //ϵͳģ��ʱ����
    director->setAnimationInterval(1.0 / 60);
    //������ӭ����
    auto scene = GameSceneManager::createScene();
    //��������ӭ������ʾ
    director->runWithScene(scene);
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
    //����������Ļ�Ҫ��������һ�俪ʼ��������
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
