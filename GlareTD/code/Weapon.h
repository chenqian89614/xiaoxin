#ifndef  _Weapon_H_
#define  _Weapon_H_
#include "cocos2d.h"

using namespace cocos2d;

//�Զ���ľ�����
class Weapon : public cocos2d::Sprite
{
public:
	//���캯��
    Weapon();
	//��������id�� 1��2��3��4�����̺�����
	int id;
	//�����ļ���1��2��3��4
	int level;
	//�����ӵ�������
	int updatetime;
	//�������Ĺ�����Χ
	int confines;
	//���������˺�ֵ
	int hurt;
	//�������ĽǶ�
	float angle;
	//��װ��������Ҫ�Ľ����
	int value;
	//������������Ҫ�Ľ����
	int upValue;
	//�����������õ��Ľ����
	int sellValue;
	//�����ӵ��ı�־λ
	bool fire;
	//���·������ı�־λ
	bool updateMark;
    //�����������ļ�������
    static Weapon* create(int id,int level,float angle);
    static Weapon* create(int id);
    static Weapon* create(const char* pic,int id);
    //�����������ķ���
    void updateData();
    //����������ǰ��׼������
    void update();
    //�����ӵ��ķ���
    void fireing();
    //���÷����ӵ��ķ���
    void setFire();
    Point pointColRow;
    ProgressTimer *left;

    //ϵͳ�����һ���꣬������Ӧ�ĳ�ʼ�����ͷŹ���
    CREATE_FUNC(Weapon);
};

#endif
