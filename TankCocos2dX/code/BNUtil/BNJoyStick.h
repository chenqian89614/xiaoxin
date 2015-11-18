#ifndef _BNJoyStick_H_
#define _BNJoyStick_H_

#include "cocos2d.h"
using namespace cocos2d;

class BNJoyStick : public Sprite
{
  public:
	//���캯��
	BNJoyStick(void);
	//��������
    virtual ~BNJoyStick(void);

    //����ҡ���ƶ��¼���ʱ��
    int yhCount=0;

    //���ر�־λ
    bool touchFlag=false;

    //����ҡ�˾���
    Sprite* centerPoint;
    //�����̰뾶
    float rRange;
    //ҡ���ƶ��ĺ�����
    float vx;
    //ҡ���ƶ���������
    float vy;

    //��ȡ��������
    Rect getRect();
    //�жϴ�����λ�õķ���
    bool containsTouchLocation(Touch* touch);
    //��������ҡ��λ�ü���ȡ�뾶
    void calCenter();
    //����ҡ������������ͼ�����귽��
    void calCenterPosition(float tx,float ty);

    //ÿ�ξ������ʱ���ص�
    virtual void onEnter();
    //ÿ�ξ����˳�ʱ���ص�
    virtual void onExit();
    //��ʼ�����¼��Ĵ�����
    bool onTouchBegan(Touch* touch, Event* event);
    //�����ƶ��¼��Ĵ�����
	void onTouchMoved(Touch* touch, Event* event);
	//���ؽ����¼��Ĵ�����
	void onTouchEnded(Touch* touch, Event* event);

	//������Ϸҡ�˷���
    static BNJoyStick* create(const std::string& basefilename,const std::string& centerfilename);
};


#endif
