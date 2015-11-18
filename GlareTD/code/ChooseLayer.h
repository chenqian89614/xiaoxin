#ifndef  _ChooseLayer_H_
#define  _ChooseLayer_H_
#include "GameSceneManager.h"
#include "AppMacros.h"

#include "cocos2d.h"
using namespace cocos2d;

//�Զ���Ĳ�����
class ChooseLayer : public cocos2d::Layer
{
public:
	//�����˵�����
	Menu* pMenu;
	//������������������
	GameSceneManager *man;
	//����һ���л��ؿ��õ���ȫ�ֱ���
	static int modeLevel;
	//��ʼ���ķ���
    virtual bool init();

    //����ؿ�1-5�Ļص�����
    void oneMode(Object* pSender);
    void twoMode(Object* pSender);
    void threeMode(Object* pSender);
    void fourMode(Object* pSender);
    void fiveMode(Object* pSender);
    //���ذ�ť����ص�����
    void sixMode(Object* pSender);

    //CCPlatformMacros.h�ļ��ж����һ���꣬����ָ�����͵Ķ���
    //��������Ӧ�ĳ�ʼ�����ͷŹ���
    CREATE_FUNC(ChooseLayer);
};

#endif
