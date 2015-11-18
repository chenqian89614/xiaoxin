#ifndef _DialogLayer_h
#define _DialogLayer_h

#include "cocos2d.h"
#include "GameSceneManager.h"
#include "GameLayer.h"

using namespace std;
using namespace cocos2d;

class DialogLayer: public LayerColor
{
public:
	//�������ű�־λ
	static bool isMusic;
	//����Ч����־λ
	static bool isParticle;
    //���˵�����
	Menu *m_pMenu;
    //��ť�Ƿ񱻵���ı�־λ
    bool m_bTouchedMenu;
    //�������1-2�ľ������
    Sprite* x_1;
    Sprite* x_2;
    //��ű�־
    bool xx_1;
    bool xx_2;
    //��������������������
    GameSceneManager *man;

public:
	//��ʼ���ķ���
    virtual bool init();
    //��ʼ��
    void initDialog();
    //�������˵�����ķ���
    void homeSence(Object* pSender);
    //����Ч���˵���ť�Ļص�����
    void parused();
    //�����˵���ť�Ļص�����
    void sounded();
    //������Ϸ��ť�ĵ����ص�����
    void menuCallbackContinueGame(Object *pSender);

    CREATE_FUNC(DialogLayer);
};

#endif
