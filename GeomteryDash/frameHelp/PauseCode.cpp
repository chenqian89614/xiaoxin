#include "PauseCode.h"
#include "MusicManager.h"
#include "../hellocpp/GameLayer.h"
#include "../hellocpp/FlyLayer.h"
#include "SpriteManager.h"
#include "../hellocpp/Constant.h"

PauseCode::PauseCode(Layer* layerIn)
{
	this->layer = layerIn;
}

void PauseCode::PauseStart()
{
	Director *director = Director::getInstance();
	director->pause();//��ͣ�����˶�
	SpriteManager* sh;
	if(layer->getTag() == INDEX_GRAMLAYER)
	{
		sh = ((GameLayer*)(layer))->sh;
	}
	else if(layer->getTag() == INDEX_FLYLAYER)
	{
		sh = ((FlyLayer*)(layer))->sh;
	}


	statePause = true;//��ͣ��־λ��Ϊtrue

	Rect recta(0,0,0,0);//��ͣ  �ı���
	sh->allSs[0] = sh->createScale9Sprite("pic/Scale9SpritePic.png", Rect(0,0,250,260), Rect(80,80,90,90), 0.5, 0.5, WIDTH/2, HEIGHT/2, WIDTH-150, HEIGHT-150, PauseBGZOrder);

	if(MusicManager::onSound == true)
	{
		recta = Rect(0,184,38,38);//��ͣ  �����ֿ���״̬   ��ͼƬ
	}
	else
	{
		recta = Rect(40,186,76-40,225-186);//��ͣ  �����ֹر�״̬   ��ͼƬ
	}
	sh->allSp[1] = sh->createSprite(NULL, recta, sh->batchNode, 0.5, 0.5, 325, 540-320, 100, 100, PauseBGZOrder+1);
	sh->AddEventListenerSprite(sh->allSp[1]);

	recta = Rect(535,408,80,80);//��ͣ  �ļ��� ͼƬ
	sh->allSp[2] = sh->createSprite(NULL, recta, sh->batchNode, 0.5, 0.5, 480, 540-320, 130, 130, PauseBGZOrder+1);
	sh->allSp[2]->setRotation(-90.0f);
	sh->AddEventListenerSprite(sh->allSp[2]);

	recta = Rect(939,325,998-939,385-325);//��ͣ  �Ĳ˵� ͼƬ
	sh->allSp[3] = sh->createSprite(NULL, recta, sh->batchNode, 0.5, 0.5, 635, 540-320, 100, 100, PauseBGZOrder+1);
	sh->allSp[3]->setRotation(-90.0f);
	sh->AddEventListenerSprite(sh->allSp[3]);

	recta = Rect(689,774,46,24);//��������ͼƬ
	sh->allSp[4] = sh->createSprite(NULL, recta, sh->batchNode, 0.5, 0.5, 325, 325, 100, 50, PauseBGZOrder+1);
	recta = Rect(635,774,46,24);//��������ͼƬ
	sh->allSp[5] = sh->createSprite(NULL, recta, sh->batchNode, 0.5, 0.5, 480, 325, 100, 50, PauseBGZOrder+1);
	recta = Rect(585,773,46,24);//�˵�����ͼƬ
	sh->allSp[6] = sh->createSprite(NULL, recta, sh->batchNode, 0.5, 0.5, 635, 325, 100, 50, PauseBGZOrder+1);
}
void PauseCode::PauseEnd()
{
	SpriteManager* sh;
	if(layer->getTag() == INDEX_GRAMLAYER)
	{
		sh = ((GameLayer*)(layer))->sh;
	}
	else if(layer->getTag() == INDEX_FLYLAYER)
	{
		sh = ((FlyLayer*)(layer))->sh;
	}
	sh->batchNode->removeChild(sh->allSp[1],true);
	sh->batchNode->removeChild(sh->allSp[2],true);
	sh->batchNode->removeChild(sh->allSp[3],true);
	sh->batchNode->removeChild(sh->allSp[4],true);
	sh->batchNode->removeChild(sh->allSp[5],true);
	sh->batchNode->removeChild(sh->allSp[6],true);
	sh->layer->removeChild(sh->allSs[0],true);
	Director *director = Director::getInstance();
	director->resume();
	statePause = false;//����ͣ��־λ��Ϊfalse
}
bool PauseCode::PauseJudgeSp(Sprite* sp)
{
	SpriteManager* sh;
	if(layer->getTag() == INDEX_GRAMLAYER)
	{
		sh = ((GameLayer*)(layer))->sh;
	}
	else if(layer->getTag() == INDEX_FLYLAYER)
	{
		sh = ((FlyLayer*)(layer))->sh;
	}
	if(sp == sh->allSp[1])//��������ͼƬ
	{
		Rect recta(40,186,76-40,225-186);//��ͣ  �����ֹر�״̬   ��ͼƬ
		if(MusicManager::onSound == true)
		{
			MusicManager::pauseBackgroundMusic();
		}
		else
		{
			recta = Rect(0,184,38,38);//��ͣ  �����ֿ���״̬   ��ͼƬ

			if(MusicManager::noPlaySound == true)
			{
				MusicManager::onSound = true;
				UserDefault::getInstance()->setBoolForKey("6", MusicManager::onSound);
				UserDefault::getInstance()->flush();
				if(layer->getTag() == INDEX_GRAMLAYER)
				{
					MusicManager::playGameLayerMusic();
				}
				else if(layer->getTag() == INDEX_FLYLAYER)
				{
					MusicManager::playFlyLayerMusic();
				}

				MusicManager::noPlaySound = false;
			}
			else
			{
				MusicManager::resumeBackgroundMusic();
			}
		}
		sh->batchNode->removeChild(sh->allSp[1],true);
		sh->allSp[1] = sh->createSprite(NULL, recta, sh->batchNode, 0.5, 0.5, 325, 540-320, 100, 100, PauseBGZOrder+1);
		sh->AddEventListenerSprite(sh->allSp[1]);
		return true;
	}
	else if(sp == sh->allSp[2])//���Ǽ���ͼƬ
	{
		PauseEnd();//������ͣ�����Ĵ���
		return true;
	}
	else if(sp == sh->allSp[3])//���ǲ˵�ͼƬ
	{
		PauseEnd();//������ͣ�����Ĵ���
		if(MusicManager::onSound == true)
		{
			MusicManager::playMenuLayerMusic();//��������
		}
		if(layer->getTag() == INDEX_GRAMLAYER)
		{
			((GameLayer*)(sh->layer))->gsm->goLevelLayer();//��ת��LevelLayer��
		}
		else if(layer->getTag() == INDEX_FLYLAYER)
		{
			((FlyLayer*)(sh->layer))->gsm->goLevelLayer();//��ת��LevelLayer��
		}
		return true;
	}
	else
		return false;
}
