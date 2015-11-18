#include "Monsters.h"
#include "cocos2d.h"
#include "GameSceneManager.h"

using namespace cocos2d;

//���캯��
Monsters::Monsters(){}

//��ʼʱ�����ֶ���ķ���(����Ϊ�ֵ�id����·��)
Monsters* Monsters::create(int id,vector <Point > selfWay)//��ڲ��������id
{
	//����Ұ�ֵ�ͼƬ·��
	std::string picTable[6] = {"square.png","triangle.png","circle.png",
									"id_4.png","id_5.png","id_6.png"
	};
	//����һ��Ұ�ֶ���
	Monsters* temp = new Monsters();
	//��ʼ��Ұ�־������
	temp->initWithFile(picTable[id-1].c_str());
	//�Զ��ͷ�
	temp->autorelease();
	//��ȡ��ǰҰ�ֵ�id
	temp->id = id;
	//����id����Ұ�ֵ�Ѫ��
	temp->blood =100*id;
	//����id���ùֵ����Ѫ��ֵ
	temp->maxBlood=100*id;
	//��ʼ��·��
	temp->way=0;
	//Ұ���õ������Լ���·��
	temp->selfWay = selfWay;
	//����һ����ʾҰ��Ѫ���ľ������
	Sprite* blood = Sprite::create("blood.png");
	//������ê��
	blood->setAnchorPoint(Point(0.5,0));
	//��ʼ����Ϊ���ɼ�
	blood->setVisible(false);
	//����λ��
	blood->setPosition(Point(0,0));
	//����Ѫ���ĳ���
	blood->setScaleY(1);
	//��Ѫ�����������ӵ�������
	temp->addChild(blood,6,1);

	return temp;
}
//�����ֶ���
Monsters* Monsters::create(int id,int blood,int way,int maxBlood,vector <Point > selfWay)//��ڲ��������id
{
	std::string picTable[6] = {"square.png","triangle.png","circle.png",
									"id_4.png","id_5.png","id_6.png"
	};
	//����һ��Ұ�־������
	Monsters* temp = new Monsters();
	//��ʼ������
	temp->initWithFile(picTable[id-1].c_str());
	//�Զ��ͷ�
	temp->autorelease();
	//�õ���ǰ�ֵ�id
	temp->id = id;
	//�õ���ǰ�ֵ�Ѫ��
	temp->blood = blood;
	//�õ���ǰ�ֵ����Ѫ��
	temp->maxBlood=maxBlood;
	//�õ���ǰ��·��
	temp->way=way;
	//�õ����·��������
	temp->selfWay = selfWay;
	//����һ����ʾѪ���ľ������
	Sprite* blood1 = Sprite::create("blood.png");
	//����ê��
	blood1->setAnchorPoint(Point(0.5,0));
	//����Ϊ���ɼ�
	blood1->setVisible(false);
	//����λ��
	blood1->setPosition(Point(0,0));
	//����Ѫ���ĳ���
	blood1->setScaleY(1);
	//��ӵ�������
	temp->addChild(blood1,6,1);

	return temp;
}

//�����Ѫ�ķ���
void Monsters::cutBlood(int hurt)//��ڲ����ӵ���id
{
	//�����к�ǰѪ��ֵ����ԭѪ��ֵ��ȥ�ӵ����˺�ֵ
	this->blood-=hurt;
	//��Ѫ������Ϊ�ɼ�
	(this->getChildByTag(1))->setVisible(true);
	//ʣ��Ѫ��ֵ���ڵ�ǰѪ��ֵ�������Ѫ��ֵ
	float scaleY = (float)blood/maxBlood;
	//����Ѫ��ֵ
	(this->getChildByTag(1))->setScaleY(scaleY);
	//˳��ִ�й�Ѫ���ɼ��벻�ɼ���Ч�����ӳ�Ϊ0.5��
	(this->getChildByTag(1))->runAction(
			Sequence::create(
								DelayTime::create(0.5),
								CallFuncN::create(CC_CALLBACK_0(Monsters::setVisibleFalse,this)),
								NULL
								)

	);
	//����Ѫ���������
	Sprite* blood = Sprite::create("blood.png");
	//����ê��
	blood->setAnchorPoint(Point(0.5,0));
	//��ʼ��Ѫ������Ϊ���ɼ�
	blood->setVisible(false);
	//����Ѫ����λ��
	blood->setPosition(Point(0,0));
	//����Ѫ���ĳ���
	blood->setScaleY(scaleY);
	//˳��ִ��ɾ����ʾѪ������
	blood->runAction(
			Sequence::create(
								DelayTime::create(0.5),
								CallFuncN::create(CC_CALLBACK_1(Monsters::removeSprite,this)),
								NULL
								)
	);
}

//���ù�ͷ����Ѫ��Ϊ�Ƿ�ɼ��ķ���
void Monsters::setVisibleFalse()
{
	((Sprite*)(this->getChildByTag(1)))->setVisible(false);
}

//�ڶ���Ұ���˶�������ת��ʱҪ���õķ���
void Monsters::refresh(float angle)
{
	//�����ĵ����Ͻǵ�����
	Point vector;
	//�ֵ�����
	Point orgin;
	//�־���Ŀ�
	orgin.x=this->getContentSize().width/2;
	//�־���ĸ�
	orgin.y=this->getContentSize().height/2;
	vector.x=-orgin.x;
	vector.y=-orgin.y;
	//�������ĳ���
	float length=ccpLength(vector);
	//��ȡ�������ĽǶ�
	float angleOrgin=ccpToAngle(vector);
	//����Ѫ���ĽǶȣ���֤����ת��ʱ��Ѫ������ת
	Point dirction=ccpForAngle(-angle+angleOrgin);
	//����Ѫ�������Ļ��λ��
	Point position=ccpAdd(orgin,ccpMult(dirction,length));
	//����Ѫ����λ��
	((Sprite*)(this->getChildByTag(1)))->setPosition(position);
	//����Ѫ���ĽǶ�
	((Sprite*)(this->getChildByTag(1)))->setRotation(angle*180/3.1415925);
}

//ɾ��Ѫ���������ķ���
void Monsters::removeSprite(Node*node)
{
	this->removeChild(node,true);
}
