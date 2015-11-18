#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "Constant.h"
#include "AppMacros.h"

USING_NS_CC;

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
	glview->setDesignResolutionSize(960,540,ResolutionPolicy::SHOW_ALL);
	//����Ϊ��ʾFPS����Ϣ
	director->setDisplayStats(false);

	//ϵͳģ��ʱ����
	director->setAnimationInterval(1.0 / 60);
	//������ӭ����
	Scene *scene = TankSceneManager::WelcomeCreate();
	//��������ӭ������ʾ
	director->runWithScene(scene);

	//���ر�������
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic
	(
		(SOUND_PATH+std::string("background.mp3")).c_str()
	);
	//���سԵ���������Ч
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
		(SOUND_PATH+std::string("eatprops.wav")).c_str()
	);
	//���ر�ը��Ч
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
		(SOUND_PATH+std::string("grenada.ogg")).c_str()
	);
	//���ر�ը��Ч
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
		(SOUND_PATH+std::string("lose.mp3")).c_str()
	);
	//���ر�ը��Ч
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
		(SOUND_PATH+std::string("rocket_shoot2.ogg")).c_str()
	);
	//���ر�ը��Ч
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
		(SOUND_PATH+std::string("select.wav")).c_str()
	);

	Constant::musicFlag=UserDefault::getInstance()->getBoolForKey("music", true);
	Constant::effectFlag=UserDefault::getInstance()->getBoolForKey("effect", true);
	Constant::playMusic();

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
