#include "AppDelegate.h"
#include "CityRacingSceneManager.h"
#include "SimpleAudioEngine.h"
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
    glview->setDesignResolutionSize(540,960, ResolutionPolicy::SHOW_ALL);
	//����Ϊ��ʾFPS����Ϣ
    //director->setDisplayStats(true);
    //ϵͳģ��ʱ����
    director->setAnimationInterval(1.0 / 60);
    CityRacingSceneManager* crcm = new CityRacingSceneManager();
    //������ӭ����
    auto scene = crcm->createScene();
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
