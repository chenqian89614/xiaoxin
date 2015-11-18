#ifndef __WelcomeLayer_H__
#define __WelcomeLayer_H__

#include "cocos2d.h"
#include "GameSceneManager.h"

using namespace cocos2d;

//�Զ���Ĳ�����
class WelcomeLayer : public cocos2d::Layer
{
public:
	GameSceneManager* gsm;
	static bool playBgM;//���������Ƿ񲥷Ź�

	//��ʼ���ķ���
	virtual bool init();
	//ѡ��˵��ص�����
    void menuChoiceCallback(Object* pSender);
    void menuStartCallback(Object* pSender);//��ʼ�˵��ص�����
	void menuHelpCallback(Object* pSender);//�����˵��ص�����
	void preloadBgMusic();//���ر��� ����
	void playBgMusic();//���ű�������
	void pauseBgMusic();//��ͣ���ű�������
	void resumeBgMusic();//�������ű�������

	void preloadSwitchSound();//�����л�����Ч
	void playSwitchSound();//�����л�����Ч
	void preloadClickSound();//���ص������Ч
	void playClickSound();//����વ������Ч
	void pauseSound();//��ͣ������Ч
	void resumeSound();//����������Ч
	void onExit(Object* pSender);//�˳��˵��Ļص�����
    ~WelcomeLayer();
    //Cocos2d-x�ж����һ���꣬����ָ�����͵Ķ���
    //��������Ӧ�ĳ�ʼ�����ͷŹ���
    CREATE_FUNC(WelcomeLayer);
};

#endif
