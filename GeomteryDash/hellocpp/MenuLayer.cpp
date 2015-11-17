#include "MenuLayer.h"
#include "../frameHelp/SpriteManager.h"
#include "../frameHelp/MusicManager.h"
#include "Constant.h"

bool MenuLayer::init()
{
	//���ø���ĳ�ʼ��
    if (!Layer::init())
    {
        return false;
    }

    this->setTag(INDEX_MENULAYER);//���ýڵ�ı�ǩ

    visibleSize = Director::getInstance()->getVisibleSize();//��ȡ�ɼ�����ߴ�
	origin = Director::getInstance()->getVisibleOrigin();//��ȡ�ɼ�����ԭ������

	sh = new SpriteManager(this);//���������
	mlh = new MenuLayerHelp(this);//MenuLayer�İ�����
	mlh->initCreateSprite();//��ʼ�� ��������

	return true;
}

