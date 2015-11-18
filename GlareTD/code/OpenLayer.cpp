#include "OpenLayer.h"
#include "GameSceneManager.h"
#include "cocos2d.h"

#define pic_PRE_PATH_OpenLayer string("")

using namespace cocos2d;

//ʵ��OpenLayer���е�init��������ʼ������
bool OpenLayer::init()
{
    //���ø���ĳ�ʼ��
    if(!Layer::init())
    {
        return false;
    }

    //��ȡ�ɼ�����ߴ�
    Size visibleSize = Director::sharedDirector()->getVisibleSize();
    //��ȡ�ɼ�����ԭ������
    Point origin = Director::sharedDirector()->getVisibleOrigin();
 

    //����һ��������󣬳䵱���ؽ���ľ���
	Sprite *bn = Sprite::create(pic_PRE_PATH_OpenLayer+string("open.png"));
	//���þ�������λ��
	bn->setPosition(Point(380,240));
	//��͸��������Ϊ0
	bn->setOpacity(0);
	//��������ӵ�������
	this->addChild(bn,BACKGROUND_LEVEL_CGQ);
	ActionInterval *act=FadeIn::create(2.6f);
	ActionInterval *act2=act->reverse();
	bn->runAction(Sequence::create(
	act,
	act2,
	CallFunc::create(CC_CALLBACK_0(OpenLayer::playGameCallback,this)),
	NULL
	)
	);
    return true;
}

//ʵ��OpenLayer���е���һ���˵��Ļص�����
void OpenLayer::playGameCallback()
{
	  man->toBeginLayer();
}
