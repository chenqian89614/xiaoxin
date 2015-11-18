#ifndef  _AchieveLayer_H_
#define  _AchieveLayer_H_

#include "cocos2d.h"
#include "GameSceneManager.h"
#include "AppMacros.h"
#include <String>

using namespace cocos2d;
using namespace std;

//�Զ���Ĳ�����
class AchieveLayer : public cocos2d::Layer
{
public:
	string glareScore[3];
	Label* labels;
	//������������
	Sprite *backSprite;
    //Manager ���������
    GameSceneManager *man;
    Menu* pMenu;
	//��ʼ���ķ���
    virtual bool init();
    void readScore();
    void saveScore(int);
    void menuCallBack(Object* pSende);

    //CCPlatformMacros.h�ļ��ж����һ���꣬����ָ�����͵Ķ���
    //��������Ӧ�ĳ�ʼ�����ͷŹ���
    CREATE_FUNC(AchieveLayer);
};

#endif
