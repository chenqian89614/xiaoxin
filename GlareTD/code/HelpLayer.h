#ifndef  _HelpLayer_H_
#define  _HelpLayer_H_
#include "cocos2d.h"
#include "GameSceneManager.h"

using namespace cocos2d;
//�Զ���Ĳ�����
class HelpLayer : public cocos2d::Layer
{
public:
	GameSceneManager *man;
	Menu* pMenu;
	Sprite* helpSprite;
	Sprite* help[9];
	//����
	int currPicIndex=0;
	//��ʼ���ķ���
    virtual bool init();
    void initIntroPic();
    void menuCallBack0(Object* pSende);
    void menuCallBack1(Object* pSende);
    void menuCallBack2(Object* pSende);

    //CCPlatformMacros.h�ļ��ж����һ���꣬����ָ�����͵Ķ���
    //��������Ӧ�ĳ�ʼ�����ͷŹ���
    CREATE_FUNC(HelpLayer);
};

#endif
