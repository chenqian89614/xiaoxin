#include "LevelLayerHelp.h"
#include "MusicManager.h"
#include "../hellocpp/LevelLayer.h"
#include "../hellocpp/GameLayer.h"
#include "../hellocpp/FlyLayer.h"
#include "SpriteManager.h"
#include "../hellocpp/Constant.h"
#include "ParticleSystemHelp.h"

LevelLayerHelp::LevelLayerHelp(Layer* layerIn)
{
	this->layer = layerIn;
	sh = ((LevelLayer*)(layer))->sh;
}

void LevelLayerHelp::initCreateSprite()
{
	ParticleSystemHelp* psh = new ParticleSystemHelp();
	psh->createSnow();
	((LevelLayer*)(layer))->addChild(psh->psq3, 10);

	//上侧 的图片
	sh->createSprite(NULL, Rect(0,391,389-0,424-391), sh->batchNode, 0.5f, 1.0f, WIDTH/2, HEIGHT, 560, 52, GoBackZOrder);

	//左上角 的返回键按钮
	sh->allSp[7] = sh->createSprite(NULL, Rect(871,154,910-871,186-154), sh->batchNode, 0.5f, 0.5f, 45, 540-37, 63, 55, GoBackZOrder);
	sh->allSp[7]->setRotation(-90.0f);
	sh->AddEventListenerSprite(sh->allSp[7]);

	//左下角 的图片
	sh->createSprite(NULL, Rect(825,386,897-825,457-386), sh->batchNode, 0.0f, 0.0f, 0, 0, 120, 120, GoBackZOrder);

	//关卡选择  图片
	sh->createSprite(NULL, Rect(6,600,246-6,657-600), sh->batchNode, 0.5f, 0.5f, WIDTH/2, HEIGHT/4*3+25, 270, 70, GoBackZOrder);

	//右下角 的图片
	Sprite* sp = sh->createSprite(NULL, Rect(825,386,897-825,457-386), sh->batchNode, 0.0f, 0.0f, WIDTH-120, 0, 120, 120, GoBackZOrder);
	sp->setFlippedX(true);

	//左侧 的按钮
	sh->allSp[8] = sh->createSprite(NULL, Rect(949, 65,1009-949,93-65), sh->batchNode, 0.5f, 1.0f, 64, HEIGHT/2, 325-233, 942-894, GoBackZOrder);
	sh->allSp[8]->setRotation(90.0f);
	sh->allSp[8]->setFlippedX(true);
	sh->AddEventListenerSprite(sh->allSp[8]);

	//右侧 的按钮
	sh->allSp[9] = sh->createSprite(NULL, Rect(949, 65,1009-949,93-65), sh->batchNode, 0.5f, 1.0f, 894, HEIGHT/2, 325-233, 942-894, GoBackZOrder);
	sh->allSp[9]->setRotation(-90.0f);
	sh->AddEventListenerSprite(sh->allSp[9]);

	//创建地面和背景
	sh->allSp[12] = sh->createSprite(NULL, Rect(129,685,243-129,802-685), sh->batchNode, 0.5f, 1.0f, WIDTH/8, 85, WIDTH/4, 85, GroundZOrder-1);//创建矩形
	sh->allSp[12]->setColor(Color3B(0,91,186));
	sh->allSp[13] = sh->createSprite(NULL, Rect(129,685,243-129,802-685), sh->batchNode, 0.5f, 1.0f, WIDTH/8*3, 85, WIDTH/4, 85, GroundZOrder-1);//创建矩形
	sh->allSp[13]->setColor(Color3B(0,91,186));
	sh->allSp[16] = sh->createSprite(NULL, Rect(129,685,243-129,802-685), sh->batchNode, 0.5f, 1.0f, WIDTH/8*5, 85, WIDTH/4, 85, GroundZOrder-1);//创建矩形
	sh->allSp[16]->setColor(Color3B(0,91,186));
	sh->allSp[21] = sh->createSprite(NULL, Rect(129,685,243-129,802-685), sh->batchNode, 0.5f, 1.0f, WIDTH/8*7, 85, WIDTH/4, 85, GroundZOrder-1);//创建矩形
	sh->allSp[21]->setColor(Color3B(0,91,186));
	sh->allSp[20] = sh->createStaticSprite(NULL, "pic/game_bg_01_001-hd.png", 0.0f, 0.0f, 0, 0, WIDTH, HEIGHT);//创建背景精灵
	sh->allSp[20]->setColor(Color3B(0,80,163));
	layer->addChild(sh->allSp[20],GroundZOrder-2);

	//关卡图片圆角矩形背景
	sh->allSp[10] = sh->createSprite(new std::string("1"), Rect(649, 508,1004-649,637-508), sh->batchNode, 0.5f, 0.5f, WIDTH/2, HEIGHT/2, 575, 200, GoBackZOrder-1);
	sh->AddEventListenerSprite(sh->allSp[10]);
	//“关”字
	sh->allSp[11] = sh->createSprite(NULL, Rect(738, 696, 974-738, 751-696), sh->batchNode, 0.5f, 0.5f, WIDTH/2, HEIGHT/2, 380, 75, GoBackZOrder-1);
	sh->AddEventListenerSprite(sh->allSp[11]);
	//脸 图片
	sh->allSp[18] = sh->createSprite(NULL, Rect(499,205,530-499,237-205), sh->batchNode, 0.5f, 0.5f, WIDTH/2-575/2+575/8, HEIGHT/2, 66, 66, GoBackZOrder-1);
	sh->AddEventListenerSprite(sh->allSp[18]);
	((LevelLayer*)(layer))->indexLevel = 1;
}
void LevelLayerHelp::changeLevel(int levelNum, int direction)//direction:0----向右移动    1---向左移动
{
	int sign = 1;
	if(direction == 1)
	{
		sign = 1;
	}
	else if(direction == 0)
	{
		sign = -1;
	}

	if(levelNum == 1)
	{
		//关卡图片背景
		sh->allSp[14] = sh->createSprite(new std::string("1"), Rect(649, 508,1004-649,637-508), sh->batchNode, 0.5f, 0.5f, sign*WIDTH+WIDTH/2, HEIGHT/2, 575, 200, GoBackZOrder-1);
		sh->AddEventListenerSprite(sh->allSp[14]);
		//“关”字
		sh->allSp[15] = sh->createSprite(NULL, Rect(738, 696, 974-738, 751-696), sh->batchNode, 0.5f, 0.5f, sign*WIDTH+WIDTH/2, HEIGHT/2, 380, 75, GoBackZOrder-1);
		sh->AddEventListenerSprite(sh->allSp[15]);
		//脸 图片
		sh->allSp[19] = sh->createSprite(NULL, Rect(499,205,530-499,237-205), sh->batchNode, 0.5f, 0.5f, sign*WIDTH+WIDTH/2-575/2+575/8, HEIGHT/2, 66, 66, GoBackZOrder-1);
		sh->AddEventListenerSprite(sh->allSp[19]);

		sh->allSp[12]->setColor(Color3B(0,91,186));
		sh->allSp[13]->setColor(Color3B(0,91,186));
		sh->allSp[16]->setColor(Color3B(0,91,186));
		sh->allSp[21]->setColor(Color3B(0,91,186));
		sh->allSp[20]->setColor(Color3B(0,80,163));
	}
	else if(levelNum == 2)
	{
		//关卡图片背景
		sh->allSp[14] = sh->createSprite(new std::string("2"), Rect(649, 508,1004-649,637-508), sh->batchNode, 0.5f, 0.5f, sign*WIDTH+WIDTH/2, HEIGHT/2, 575, 200, GoBackZOrder-1);
		sh->AddEventListenerSprite(sh->allSp[14]);
		//“关”字
		sh->allSp[15] = sh->createSprite(NULL, Rect(740, 753, 974-740, 807-753), sh->batchNode, 0.5f, 0.5f, sign*WIDTH+WIDTH/2, HEIGHT/2, 380, 75, GoBackZOrder-1);
		sh->AddEventListenerSprite(sh->allSp[15]);
		//脸 图片
		sh->allSp[19] = sh->createSprite(NULL, Rect(0,88,30,118-88), sh->batchNode, 0.5f, 0.5f, sign*WIDTH+WIDTH/2-575/2+575/8, HEIGHT/2, 66, 66, GoBackZOrder-1);
		sh->AddEventListenerSprite(sh->allSp[19]);

		sh->allSp[12]->setColor(Color3B(180,88,0));
		sh->allSp[13]->setColor(Color3B(180,88,0));
		sh->allSp[16]->setColor(Color3B(180,88,0));
		sh->allSp[21]->setColor(Color3B(180,88,0));
		sh->allSp[20]->setColor(Color3B(149,73,0));
	}
	else if(levelNum == 3)
	{
		//关卡图片背景
		sh->allSp[14] = sh->createSprite(new std::string("3"), Rect(649, 508,1004-649,637-508), sh->batchNode, 0.5f, 0.5f, sign*WIDTH+WIDTH/2, HEIGHT/2, 575, 200, GoBackZOrder-1);
		sh->AddEventListenerSprite(sh->allSp[14]);
		//“关”字
		sh->allSp[15] = sh->createSprite(NULL, Rect(368, 496, 605-368, 555-496), sh->batchNode, 0.5f, 0.5f, sign*WIDTH+WIDTH/2+4, HEIGHT/2, 373, 75, GoBackZOrder-1);
		sh->AddEventListenerSprite(sh->allSp[15]);
		//脸 图片
		sh->allSp[19] = sh->createSprite(NULL, Rect(30,88,60-30,118-88), sh->batchNode, 0.5f, 0.5f, sign*WIDTH+WIDTH/2-575/2+575/8, HEIGHT/2, 66, 66, GoBackZOrder-1);
		sh->AddEventListenerSprite(sh->allSp[19]);

		sh->allSp[12]->setColor(Color3B(219,0,0));
		sh->allSp[13]->setColor(Color3B(219,0,0));
		sh->allSp[16]->setColor(Color3B(219,0,0));
		sh->allSp[21]->setColor(Color3B(219,0,0));
		sh->allSp[20]->setColor(Color3B(152,0,0));
	}
}

bool LevelLayerHelp::JudgeSp(Sprite* sp)
{
	if(sp == sh->allSp[7])//所按精灵 若是返回键
	{
		((LevelLayer*)(layer))->gsm->goMenuLayer();
		return true;
	}
	else if(sp == sh->allSp[8])//所按精灵 若是左侧按钮
	{
		int index = ((LevelLayer*)(layer))->indexLevel;
		index--;
		if(index == 0)
		{
			index = 3;
		}
		changeLevel(index, 0);
		moveEffet(0);
		((LevelLayer*)(layer))->indexLevel = index;
		return true;
	}
	else if(sp == sh->allSp[9])//所按精灵 若是右侧按钮
	{
		int index = ((LevelLayer*)(layer))->indexLevel;
		index++;
		if(index == 4)
		{
			index = 1;
		}
		changeLevel(index, 1);
		moveEffet(1);
		((LevelLayer*)(layer))->indexLevel = index;
		return true;
	}
	else if(sp == sh->allSp[10] ||  sp == sh->allSp[11] || sp == sh->allSp[18])//所按精灵 若是关卡背景
	{
		MusicManager::playFlyLayerEffect();
		std::string* spS=(std::string*)sh->allSp[10]->getUserData();
		char spC = spS->at(0);
		if(spC == '1')
		{
			((GameLayer*)(layer))->gsm->goGameLayer(1);
		}
		else if(spC == '2')
		{
			((FlyLayer*)(layer))->gsm->goFlyLayer();
		}
		else if(spC == '3')
		{
			((GameLayer*)(layer))->gsm->goGameLayer(3);
		}
		return true;
	}
	else
		return false;
}
void LevelLayerHelp::moveEffet(int direction)//0----向右移动    1---向左移动
{
	int sign = -1;
	if(direction == 1)
	{
		sign = -1;
	}
	else if(direction == 0)
	{
		sign = 1;
	}
	sh->allSp[10]->runAction(Sequence::create(
								MoveBy::create(0.5,Point(sign*WIDTH,0)),
								RemoveSelf::create(true),
								NULL));
	sh->allSp[11]->runAction(Sequence::create(
									MoveBy::create(0.5,Point(sign*WIDTH,0)),
									RemoveSelf::create(true),
									NULL));
	sh->allSp[18]->runAction(Sequence::create(
										MoveBy::create(0.5,Point(sign*WIDTH,0)),
										RemoveSelf::create(true),
										NULL));
	sh->allSp[14]->runAction(MoveBy::create(0.5,Point(sign*WIDTH,0)));
	sh->allSp[15]->runAction(MoveBy::create(0.5,Point(sign*WIDTH,0)));
	sh->allSp[19]->runAction(MoveBy::create(0.5,Point(sign*WIDTH,0)));
	sh->allSp[10] = sh->allSp[14];
	sh->allSp[11] = sh->allSp[15];
	sh->allSp[18] = sh->allSp[19];
}
