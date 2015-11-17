#include "AppDelegate.h"
#include "SimpleAudioEngine.h"

AppDelegate::AppDelegate(){}
AppDelegate::~AppDelegate() {}
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
	glview->setDesignResolutionSize(960,540, ResolutionPolicy::SHOW_ALL);
	//����Ϊ��ʾFPS����Ϣ
    director->setDisplayStats(false);
    //ϵͳģ��ʱ����
    director->setAnimationInterval(1.0 / 60);//
    //������ӭ����
    GameSceneManager* gsm = new GameSceneManager();
    gsm->createScene(); //��������ӭ������ʾ

//    director->runWithScene(gsm->gameScene);

    return true;
}
//����������̨ʱ���ô˷���
void AppDelegate::applicationDidEnterBackground()
{
	//ֹͣ����
    Director::getInstance()->stopAnimation();
//    //����������Ļ�Ҫ��������һ����ͣ��������
//    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	//��ͣ��������
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

//���������ǰ̨ʱ����
void AppDelegate::applicationWillEnterForeground()
{
	//��ʼ����
    Director::getInstance()->startAnimation();
//    //����������Ļ�Ҫ��������һ�俪ʼ��������
//     SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	//������������
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
