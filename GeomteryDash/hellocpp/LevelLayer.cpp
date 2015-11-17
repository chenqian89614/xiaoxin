#include "LevelLayer.h"
#include "../frameHelp/SpriteManager.h"
#include "Constant.h"

bool LevelLayer::init()
{
	//���ø���ĳ�ʼ��
    if (!Layer::init())
    {
        return false;
    }

    this->setTag(INDEX_LEVELLAYER);//���ýڵ�ı�ǩ

    visibleSize = Director::getInstance()->getVisibleSize();//��ȡ�ɼ�����ߴ�
	origin = Director::getInstance()->getVisibleOrigin();//��ȡ�ɼ�����ԭ������

	sh = new SpriteManager(this);//���������
	llh = new LevelLayerHelp(this);//������
	llh->initCreateSprite();//��ʼ�� ��������

	indexLevel = 1;

	return true;
}

