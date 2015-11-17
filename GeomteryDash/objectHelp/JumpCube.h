#ifndef _JumpCube_H_
#define _JumpCube_H_

#include "cocos2d.h"
#include "../hellocpp/Constant.h"
#include "../frameHelp/ParticleSystemHelp.h"

using namespace cocos2d;

class JumpCube
{
public:
	Sprite* sp;//����ľ���
	std::string* st;//�����id

	Point p;
	float r;
	float lengthX;//����ĳ�
	float lengthY;//����Ŀ�

	//������Ծ�ĸ����������
	float vJump = JCJH / timeJump;//(timeJump * INTERVALJC);//����ʱ���ٶ�
	float vRotationJump = 90.0f / timeJump;//(timeJump * INTERVALJC);//���������� ��ת�Ľ��ٶ�
	bool isJump=false;//�Ƿ�����Ծ״̬

	//��������ĸ����������
	float vDown = vJump * 1.0;//����ʱ���ٶ�  ������ʱ���ٶȵ�1.2��
	bool isDown = false;

	int timeCount = 0;//ʱ���¼��

	ParticleSystemHelp* psh;

	Layer* layer;

	JumpCube(std::string* stTemp, Layer* layer, Rect recta, float spLocationX, float spLocationY, float spLength, int localZOrder);
	~JumpCube();
	void reflesh(float maxH);

	void Jump();
	void Down();
	void refleshAngleAndPosition(float y);
	void explode();
};

#endif
