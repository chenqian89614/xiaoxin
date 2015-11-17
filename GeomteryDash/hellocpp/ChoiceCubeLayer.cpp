#include "ChoiceCubeLayer.h"
#include "../frameHelp/SpriteManager.h"
#include "Constant.h"

bool ChoiceCubeLayer::init()
{
	//���ø���ĳ�ʼ��
    if (!Layer::init())
    {
        return false;
    }

    this->setTag(INDEX_CHOICECUBELAYER);//���ýڵ�ı�ǩ

    visibleSize = Director::getInstance()->getVisibleSize();//��ȡ�ɼ�����ߴ�
	origin = Director::getInstance()->getVisibleOrigin();//��ȡ�ɼ�����ԭ������

	sh = new SpriteManager(this);//���������
	cclh = new ChoiceCubeLayerHelp(this);//������
	cclh->initCreateSprite();//��ʼ�� ��������
	return true;
}


