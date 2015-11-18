#include "Weapon.h"
//#include "AppMacros.h"
//#include <string.h>
//#include <string>
#include "cocos2d.h"
#include "GameSceneManager.h"

using namespace cocos2d;

//���캯��
Weapon::Weapon(){}

//�����ĸ��������˵�����ʱ���õĴ�������
Weapon* Weapon::create(const char* pic,int id)//��ڲ���������id
{
	//����һ������������
	Weapon* temp = new Weapon();
	//��ʼ����װ������ʱ��ҵ�����
	int sValue[4]={15,25,30,50};
	//���ַ������ĳ�ʼ������Χ
	int confinesTable[4]={100,100,100,80};
	//���ַ�������ʼ�����ӵ�������
	float updatetimeTable[4]={1.2,1.2,1.2,1.2};
	//���ַ������ĳ�ʼ�˺�ֵ
	int hurtTable[4]={10,15,20,25};
	//��ʼ���������������
	temp->initWithFile(pic);
	//�Զ��ͷ�
	temp->autorelease();
	//�õ���ǰ��������id
	temp->id = id;
	//��ʼ���������ļ���Ϊ1
	temp->level = 1;
	//����id���ð�װ��������ʱ��Ҫ�Ľ��
	temp->value = sValue[id-1];
	//����id���ø������������ӵ�������
	temp->updatetime=updatetimeTable[id-1];
	//�����ӵ��ı�־λ
	temp->fire=true;
	//����id���ø��������ĳ�ʼ�˺�
	temp->hurt=hurtTable[id-1];
	//����id���ø��������ĳ�ʼ������Χ
	temp->confines=confinesTable[id-1];
	//����һ����ʾѡ�з�����ʱ��ʾЧ���ľ������
	Sprite* scope= Sprite::create("ring.png");
	//���øþ������ĳߴ�
	float scale=(float)confinesTable[id-1]/(scope->getContentSize().width/2);
	scope->setScale(scale);
	//����λ��
	scope->setPosition(Point(24,24));
	//���ö�����ӵ�������
	temp->addChild(scope,4,1);
	//���øþ�������ʼΪ���ɼ�
	scope->setVisible(false);
	//���������������ı�־λΪfalse
	temp->updateMark=false;

	return temp;
}

//����һ��������ʱ���õķ�������ڲ���Ϊ������id
Weapon* Weapon::create(int id)
{
	//����һ���������������
	Weapon* temp = new Weapon();
	//����һ�����һ�����������ַ�������
	std::string picTable[4] = {"white_1.png","green_1.png","red_1.png","blue_1.png"};
	//��ʼ����װ������ʱ��ҵ�����
	int sValue[4]={15,25,30,50};
	//���ַ�������1��������2��ʱ�Ľ������
	int uValue[4]={15,20,30,40};
	//���ַ������ĳ�ʼ������Χ
	int confinesTable[4]={100,100,100,80};
	//���ַ�������ʼ�����ӵ�������
	float updatetimeTable[4]={1.2,1.2,1.2,1.2};
	//���ַ������ĳ�ʼ�˺�ֵ
	int hurtTable[4]={10,15,20,25};
	//��ʼ���������������
	temp->initWithFile(picTable[id-1].c_str());
	//�Զ��ͷ�
	temp->autorelease();
	//�õ���ǰ��������id
	temp->id = id;
	//��ʼ���������ļ���Ϊ1
	temp->level = 1;
	//����id���ð�װ��������ʱ��Ҫ�Ľ��
	temp->value = sValue[id-1];
	//����������ʱ�õ��Ľ��
	temp->sellValue = temp->value/2;
	//����id���ø���������1������2��ʱ��Ҫ�Ľ��
	temp->upValue = uValue[id-1];
	//����id���ø������������ӵ�������
	temp->updatetime=updatetimeTable[id-1];
	//�����ӵ��ı�־λ
	temp->fire=true;
	//����id���ø��������ĳ�ʼ�˺�
	temp->hurt=hurtTable[id-1];
	//����id���ø��������ĳ�ʼ������Χ
	temp->confines=confinesTable[id-1];
	//����һ����ʾѡ�з�����ʱ��ʾЧ���ľ������
	Sprite* scope= Sprite::create("ring.png");
	//���ݵ�ǰ�������Ĺ�����Χ�����ø�Ч������ĳߴ�
	float scale=(float)confinesTable[id-1]/(scope->getContentSize().width/2);
	scope->setScale(scale);
	//���øþ�������λ��
	scope->setPosition(Point(24,24));
	//���þ��������ӵ�������
	temp->addChild(scope,4,1);
	//���øþ�������ʼΪ���ɼ�
	scope->setVisible(false);
	//���������������ı�־λΪfalse
	temp->updateMark=false;

	return temp;
}

//�����������������(����ʱ���õĴ�������),�����ֱ�Ϊ��������id���ȼ����Ƕ�
Weapon* Weapon::create(int id,int level,float angle)
{
	//����һ������
	Weapon* temp = new Weapon();
	std::string picTable[4][3] = {{"white_2.png","white_3.png","white_4.png"},
			{"green_2.png","green_3.png","green_4.png"},
			{"red_2.png","red_3.png","red_4.png"},
			{"blue_2.png","blue_3.png","blue_4.png"}};//�ף��̣��죬��
	//���ַ�����������ͬ�ȼ���ÿ���ӵ����˺�ֵ
	int hurtTable[4][3]={
			{20,30,60},
			{25,35,45},
			{30,40,50},
			{35,45,55}
	};
	//���ַ�����������ͬ�ȼ��µĹ�����Χ
	int confinesTable[4][3]={
			{120,140,160},
			{100,100,100},
			{130,160,180},
			{100,110,120}
	};
	//�����ӵ������ʣ���ֵԽ���ʾ�����ٶ�Խ��
	float updatetimeTable[4][3]={
			{1.5,8.0,4.0},
			{1.3,1.4,1.5},
			{1.3,1.4,1.5},
			{1.5,1.8,2.1}
	};
	//�Զ��ͷ�
	temp->autorelease();
	//��ʼ�����ͼƬ�ĸ���
	temp->initWithFile(picTable[id-1][level-1].c_str());
	//���ݵ�ǰѡ�еķ�������id���ȼ������ø÷��������˺�
	temp->hurt=hurtTable[id-1][level-1];
	//���ݵ�ǰѡ�еķ�������id���ȼ������ø÷������Ĺ�����Χ
	temp->confines=confinesTable[id-1][level-1];
	//���ݵ�ǰѡ�еķ�������id���ȼ������ø÷����������ӵ�������
	temp->updatetime=updatetimeTable[id-1][level-1];
	//������������ת�Ƕ�
	temp->setRotation(angle);

	return temp;
}

//����������ǰ��׼������
void Weapon::update()
{
	//����������ĵȼ�Ϊ4�����߱�ʾ���µı�־λΪtrue
	if(level==4||this->updateMark==true)
	{
		return;
	}
	//�����������µı�־λ����Ϊtrue
	this->updateMark=true;
	//����һ���ٷֱȶ�����Ч����4���ʱ���ڴ�0���ٷ�֮��
	ProgressTo *to1 = ProgressTo::create(4, 100);
	//����һ��������ʾ�������ȵľ������
	left = ProgressTimer::create(Sprite::create("ring2.png"));
	//���ù���ģʽΪ�뾶ģʽ
	left->setType(ProgressTimer::Type::RADIAL);
	//������ת�Ƕ�
	left->setRotation(angle-90);
	//����Ч��ӵ�������
	addChild(left);
	//����λ��
	left->setPosition(Point(24,24));
	left->runAction(
			Sequence::create(
					to1,
					CallFuncN::create(CC_CALLBACK_0(Weapon::updateData,this)),
					NULL));
}

//�����������ķ���
void Weapon::updateData()
{
	//�õ���ǰѡ�з�������id
	int id = this->id;
	//�õ���ǰѡ�з������ĵȼ�
	int level = this->level;
	//��������������ʱ�Ľ������
	this->upValue+=level*10;
	//��������������ʱ�Ľ������
	this->sellValue+=level*5;
	//��������õ��ĸ��׶εķ�����������������
	std::string picTable[4][3] = {{"white_2.png","white_3.png","white_4.png"},
			{"green_2.png","green_3.png","green_4.png"},
			{"red_2.png","red_3.png","red_4.png"},
			{"blue_2.png","blue_3.png","blue_4.png"}};//�ף��̣��죬��
	//��ʼ����������2������4�����׶ε��˺�
	int hurtTable[4][3]={
			{20,30,60},
			{25,35,45},
			{30,40,50},
			{35,45,55}
	};
	//��ʼ����������2������4�����׶εĹ�����Χ
	int confinesTable[4][3]={
			{120,140,160},
			{100,100,100},
			{130,160,180},
			{100,110,120}
	};
	//��ʼ����������2������4�����׶η����ӵ�������
	float updatetimeTable[4][3]={
			{1.5,8.0,4.0},
			{1.3,1.4,1.5},
			{1.3,1.4,1.5},
			{1.5,1.8,2.1}
	};
	//��ʼ���������������
	this->initWithFile(picTable[id-1][level-1].c_str());
	//���ݵ�ǰ��������id���ȼ��������˺�
	this->hurt=hurtTable[id-1][level-1];
	//���ݵ�ǰ��������id���ȼ������乥����Χ
	this->confines=confinesTable[id-1][level-1];
	//���ݵ�ǰ��������id���ȼ������䷢���ӵ�������
	this->updatetime=updatetimeTable[id-1][level-1];
	//����һ��������ʾ������Χ�ľ������
	Sprite* scope=(Sprite*)this->getChildByTag(1);
	//������ߴ�Ĵ�С
	float width=(float)scope->getContentSize().width/2;
	float scale=this->confines/width;
	scope->setScale(scale);
	//�����ɹ�����ȼ��Լ�
	this->level++;
	//Ȼ�������ı�־λ����Ϊfalse
	this->updateMark=false;
	//�������ӵ��ı�־λ����Ϊtrue
	this->fire=true;
	this->removeChild(left,true);
}

//�����ӵ��ķ���
void Weapon::fireing()
{
	//��ʼ����ǰ�����ӵ��ı�־λΪfalse
	this->fire=false;
	//˳��ִ�з����ӵ��Ķ�������ͬid�ķ�����������ͬʱ�����ӵ�
	this->runAction(
			Sequence::create(
					//��ʱ1��
					DelayTime::create(1),
					CallFuncN::create(CC_CALLBACK_0(Weapon::setFire,this)),
					NULL
			)
			);
}

//���÷����ӵ��ķ���
void Weapon::setFire()
{
	//�����ǰ���·������ı�־λΪfalse
	if(this->updateMark==false)
	{
		//�������ӵ��ı�־λ��Ϊtrue
		this->fire=true;
	}
}
