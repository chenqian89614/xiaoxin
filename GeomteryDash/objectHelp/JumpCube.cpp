#include "JumpCube.h"
#include "../frameHelp/MusicManager.h"
#include "../hellocpp/GameLayer.h"

JumpCube::JumpCube(std::string* stTemp, Layer* layer, Rect recta, float spLocationX, float spLocationY, float spLength, int localZOrder)
{
	this->lengthX = spLength;
	this->lengthY = spLength;
	this->layer = layer;

	this->st = stTemp;//��Ծ���� id
	sp = Sprite::createWithTexture(((GameLayer*)(layer))->sh->batchNode->getTexture(),recta);//��������
	sp->setAnchorPoint(Point(0.5f,0.5f));//���þ����ê��   ��Ϊ���ĵ�
	sp->setPosition(Point(spLocationX,spLocationY));//���þ����λ��
	Size size=sp->getContentSize();//��ȡ����ĳߴ�
	float scaleX=spLength/size.width;//���������X�������ű�
	float scaleY=spLength/size.height;//���������Y�������ű�
	sp->setScaleX(scaleX);//���þ���X�������ű�
	sp->setScaleY(scaleY);//���þ���Y�������ű�
	sp->setColor(Color3B(102,204,35));
	layer->addChild(sp,localZOrder);//��������ӵ�������

	p = sp->getPosition();
	r = sp->getRotation();

	psh = new ParticleSystemHelp();
	layer->addChild(psh->psq1, BatchNodeZOrder-1);//��������Ч��ӵ�layer��
	psh->psq2->retain();
	psh->psq1->setVisible(false);
	psh->isPsq1 = false;

}
JumpCube::~JumpCube()
{
	delete st;
}
//����Ծ����  ����   isJump==false  ��   isDown==false  ��״̬ʱ    ���ø÷���
void JumpCube::reflesh(float maxH)
{
	if(maxH != this->sp->getPosition().y)//�ж����߶��Ƿ�Ϊ��ǰ�����λ��
	{
		isDown = true;//������ǣ��򷽿�������䶯��
	}
	p = sp->getPosition();//��¼���鵱ǰλ��
	r = sp->getRotation();//��¼���鵱ǰ��ת��
}
void JumpCube::Jump()
{
	if(psh->isPsq1 == true)//�жϵ�ǰ������Ч�Ƿ���ʾ
	{//����ǰ�л�����Ч��ʾ
		psh->psq1->retain();//���ֻ�������ϵͳָ��
		psh->psq1->stopSystem();//ֹͣ��������ϵͳ
		psh->isPsq1 = false;//��¼��������ϵͳ�ı�־λ��Ϊfalse
	}
	timeCount++;//ʱ���������һ
	sp->setPosition(Point(p.x, p.y + vJump * timeCount * INTERVALJC));//���÷����λ��
	sp->setRotation(r + vRotationJump * timeCount * INTERVALJC);//���÷������ת��
	if(sp->getPosition().y - p.y >= JCJH)//�ж�y�����λ�����Ƿ񳬹�����JCJH
	{
		this->isJump = false;//��������־λ��Ϊfalse
		timeCount = 0;//ʱ�����������
		p = sp->getPosition();//��¼���鵱ǰλ��
		sp->setRotation(r + 90);//���÷������ת��
		r = sp->getRotation();//��¼���鵱ǰ��ת��
	}
}
void JumpCube::Down()
{

	if(psh->isPsq1 == true)//�жϵ�ǰ������Ч�Ƿ���ʾ
	{
		psh->psq1->retain();//���ֻ�������ϵͳָ��
		psh->psq1->stopSystem();//ֹͣ��������ϵͳ
		psh->isPsq1 = false;//��¼��������ϵͳ�ı�־λ��Ϊfalse
	}

	timeCount++;//ʱ���������һ
	sp->setPosition(Point(p.x, p.y - vDown * timeCount * INTERVALJC));//���÷����λ��
	sp->setRotation(r + vRotationJump * timeCount * INTERVALJC);//���÷������ת��
}
void JumpCube::refleshAngleAndPosition(float y)
{
	if(psh->isPsq1 == false)//�жϵ�ǰ������Ч�Ƿ���ʾ
	{
		psh->psq1->setSourcePosition(Point(sp->getPosition().x - lengthX / 2, y - lengthY / 2));//���û�������ϵͳ��λ��
		psh->psq1->resetSystem();//���û�������ϵͳ
		psh->psq1->setVisible(true);//��������ϵͳ�ɼ�
		psh->isPsq1 = true;//��¼��������ϵͳ�ı�־λ��Ϊtrue
		psh->psq1->retain();//���ֻ�������ϵͳָ��
	}

	float angle = (sp->getRotation() - r);//���㵱ǰ��ת�ǵ�ƫ����
	if(0<angle)//�ж�ƫ�����Ƿ����0
	{
		sp->setRotation(r + 90);//������˳ʱ����ת90��
	}

	timeCount = 0;//ʱ�����������
	this->isDown = false;//����¼��������״̬�ı�־λ��Ϊfalse
	p = Point(sp->getPosition().x,y);//��¼���鵱ǰλ��
	r = sp->getRotation();//��¼���鵱ǰ��ת��
	this->sp->setPosition(p);//���÷��龫��λ��
}
void JumpCube::explode()
{
	psh->psq1->stopSystem();
	layer->addChild(psh->psq2,BatchNodeZOrder-1);//��ӱ�ըЧ��


	psh->psq2->setSourcePosition(Point(sp->getPosition().x-150 , sp->getPosition().y-70));
	psh->psq2->resetSystem();

	sp->setVisible(false);//���÷��龫�鲻�ɼ�

	MusicManager::playExplosionEffect();
}
