#ifndef __GameSceneManager_H__
#define __GameSceneManager_H__

#include "cocos2d.h"

using namespace cocos2d;

//���ڴ�����������
class GameSceneManager
{
public:
	Scene* welcomeScene;//��ӭ���泡��ָ��
	Scene* gameScene;//��Ϸ����ָ��
	Scene* choiceScene;//ѡ���ָ��
	Scene* HelpScene;//��������ָ��
	Scene* Round2Scene;//�ڶ��س���ָ��
	Scene* Round3Scene;//�����س���ָ��
	Scene* Round4Scene;//���Ĺس���ָ��
	Scene* Round5Scene;//����س���ָ��
	Scene* Round6Scene;//�����س���ָ��
	Scene* levelScene;//ѡ�س���ָ�룻

	Scene* setScene;//ϵ�г���ָ��
//	//������������ķ���
//    static cocos2d::Scene* createScene();
	//������������ķ���
	void createScene();

    void gogameScene();//ȥ��Ϸ�����ķ���

    void reStart();//��һ�����¿�ʼ�ķ���
    void reStart2();//�ڶ������¿�ʼ�ķ���
    void reStart3();//���������¿�ʼ�ķ���
    void reStart4();//���Ĺ����¿�ʼ�ķ���
    void reStart5();//��������¿�ʼ�ķ���
    void reStart6();//���������¿�ʼ�ķ���
    void goChoiceScene();//ȥѡ����ķ���
    void goWelcomeScene();//�ػ�ӭ�����ķ���
    void goRound2Scene();//ȥ�ڶ��س���
    void goRound3Scene();//ȥ�����س���
    void goRound4Scene();//ȥ���Ĺس���
    void goRound5Scene();//ȥ����س���
    void goRound6Scene();//ȥ�����س���
    void goLevelScene();//ȥѡ�س���

    void goSetScene();//ȥϵ�г���

    void goHelpScene();//ȥ��������

};

#endif
