#include "MusicLayer.h"
#include "../frameHelp/SpriteManager.h"
#include "Constant.h"

bool MusicLayer::init()
{
	//���ø���ĳ�ʼ��
    if (!Layer::init())
    {
        return false;
    }

    this->setTag(INDEX_MUSICLAYER);//���ýڵ�ı�ǩ

    visibleSize = Director::getInstance()->getVisibleSize();//��ȡ�ɼ�����ߴ�
	origin = Director::getInstance()->getVisibleOrigin();//��ȡ�ɼ�����ԭ������

	sh = new SpriteManager(this);//���������
	mlh = new MusicLayerHelp(this);//������
	mlh->initCreateSprite();//��ʼ�� ��������

	return true;
}


