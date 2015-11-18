#ifndef  _Monsters_H_
#define  _Monsters_H_
#include "cocos2d.h"
#include <vector>

using namespace cocos2d;
using namespace std;
//�Զ���ľ�����
class Monsters : public cocos2d::Sprite
{
public:
	//����ĵ�ǰѪ��
	int blood;
	//����ı�ţ������ֹ��� 1��2��3
	int id;
	//�����ߵĵڼ���·��
	int way;
	//���·��������
	vector <Point > selfWay;
	//���Ѫ��
	int maxBlood;
	//���캯��
    Monsters();
    //����Ұ�ֵķ���
    static Monsters* create(int id,vector <Point > selfWay);
    //����Ұ�ֵķ���
    static Monsters* create(int id,int blood,int way,int maxBlood,vector <Point > selfWay);
    //�����Ѫ�ķ���
    void cutBlood(int);//��ڲ����ӵ���id
    //���ù�ͷ����Ѫ��Ϊ�Ƿ�ɼ��ķ���
    void setVisibleFalse();
    //�����ڶ���Ұ���˶�������ת��ʱҪ���õķ���
    void refresh(float angle);
    //ɾ���������ķ���
    void removeSprite(Node* node);

    //��������Ӧ�ĳ�ʼ�����ͷŹ���
    CREATE_FUNC(Monsters);
};

#endif
