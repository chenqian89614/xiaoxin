#ifndef  _BulletSprite_H_
#define  _BulletSprite_H_

#include "cocos2d.h"
#include "Monsters.h"

//�Զ���ľ�����
class BulletSprite : public cocos2d::Sprite
{
public:
	//���캯��
    BulletSprite();
	//�ӵ��ı�ţ�������1��2��3
	int id;
	//�ӵ����˺�ֵ
	int hurt;
	//Ŀ��Ұ��
	int target;
	//�ӵ��ĽǶ�
	float angle;
    //�����ӵ��ķ���(����ΪͼƬ���ӵ���id)
    static BulletSprite* create(const char* pic,int id);
    //�����ӵ�����(����ΪͼƬ�˺�ֵ��Ŀ��Ұ��)
    static BulletSprite* create(const char* pic,int hurt,int target);
    //�����Ѫ����
    void updata(int bulletId);

    //������Ӧ�ĳ�ʼ�����ͷŹ���
    CREATE_FUNC(BulletSprite);
};

#endif
