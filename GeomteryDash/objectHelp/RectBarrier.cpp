#include "Barrier.h"
#include "../hellocpp/GameLayer.h"
#include "../hellocpp/MenuLayer.h"
#include "../hellocpp/FlyLayer.h"
#include "../hellocpp/ChoiceCubeLayer.h"
#include "../hellocpp/MusicLayer.h"


RectBarrier::RectBarrier
(
		std::string* stTemp,
		Layer* layer,
		Rect recta,
		float spLocationX,
		float spLocationY,
		float spLengthX,
		float spLengthY,
		int localZOrder
):Barrier(stTemp, layer, recta, spLocationX, spLocationY, spLengthX, spLengthY, localZOrder)
{
	idChar = 'R';//设置矩形障碍物id
	sp = Sprite::createWithTexture(((GameLayer*)(layer))->sh->batchNode->getTexture(),recta);//创建精灵对象
//	sp = Sprite::create(pic);//创建精灵
	sp->setAnchorPoint(Point(0.5f,0.5f));//设置精灵的锚点   设为中心点
	sp->setPosition(Point(spLocationX,spLocationY));//设置精灵的位置
	Size size=sp->getContentSize();//获取精灵的尺寸
	float scaleX=spLengthX/size.width;//计算出精灵X方向缩放比
	float scaleY=spLengthY/size.height;//计算出精灵Y方向缩放比
	sp->setScaleX(scaleX);//设置精灵X方向缩放比
	sp->setScaleY(scaleY);//设置精灵Y方向缩放比
//	layer->addChild(sp,localZOrder);//将精灵添加到布景中
	if(layer->getTag() == INDEX_GRAMLAYER)
	{
		((GameLayer*)(layer))->sh->batchNode->addChild(sp,localZOrder);//将精灵添加到布景中
	}
	else if(layer->getTag() == INDEX_MENULAYER)
	{
		((MenuLayer*)(layer))->sh->batchNode->addChild(sp,localZOrder);//将精灵添加到布景中
	}
	else if(layer->getTag() == INDEX_FLYLAYER)
	{
		((FlyLayer*)(layer))->sh->batchNode->addChild(sp,localZOrder);//将精灵添加到布景中
	}
	else if(layer->getTag() == INDEX_CHOICECUBELAYER)
	{
		((ChoiceCubeLayer*)(layer))->sh->batchNode->addChild(sp,localZOrder);//将精灵添加到布景中
	}
	else if(layer->getTag() == INDEX_MUSICLAYER)
	{
		((MusicLayer*)(layer))->sh->batchNode->addChild(sp,localZOrder);//将精灵添加到布景中
	}


	this->p = sp->getPosition();//记录障碍物当前位置
}
//跳跃方块的左边儿  小于等于   障碍物的右边  并且   跳跃方块的右边儿  大于等于   障碍物的左边    时   进行碰撞检测
bool RectBarrier::collision(JumpCube* jc)
{
	float jcBottom = jc->sp->getPosition().y - jc->lengthY/2;//跳跃方块的下边儿
	float rbTop = this->sp->getPosition().y + this->lengthY/2;//障碍物的上边儿

	float jcZ = jc->sp->getPosition().x-jc->lengthX/2;//跳跃方块的左边
	float jcY = jc->sp->getPosition().x+jc->lengthX/2;//跳跃方块的右边
	float rbZ = this->sp->getPosition().x - this->lengthX/2;//障碍物的左边儿
	float rbY = this->sp->getPosition().x + this->lengthX/2;//障碍物的左边儿

	if(jc->sp->getPosition().x<rbZ && jcY>=rbZ)//跳跃方块的中点x坐标  小于 障碍物的左边 && 跳跃方块的右边  大于等于   障碍物的左边儿
	{
		if(jcBottom<rbTop)//跳跃方块的下边儿  小于 障碍物的上边儿
		{
			jc->explode();//调用方块的爆炸方法
			return true;
		}
		else//跳跃方块的下边儿  大于等于  障碍物的上边儿
		{
			if(jcBottom <= rbTop)//跳跃方块的下边儿  小于等于  障碍物的上边儿
			{
				jc->refleshAngleAndPosition(rbTop + jc->lengthY/2);//调用更新方块姿态的方法
			}
			return false;
		}
	}
	else//跳跃方块的中点x坐标  大于   障碍物的左边    并且此时的jcBottom已经大于等于rbTop了
	{
		if(jcBottom <= rbTop)//跳跃方块的下边儿  小于等于  障碍物的上边儿
		{
			jc->refleshAngleAndPosition(rbTop + jc->lengthY/2);//调用更新方块姿态的方法
		}
		return false;
	}
}
bool RectBarrier::collisionFo(FlyObject* fo)
{
	float rbTop = this->sp->getPosition().y + this->lengthY/2;//障碍物的上边儿
	float rbBottom = this->sp->getPosition().y - this->lengthY/2;//障碍物的下边儿
	float rbZ = this->sp->getPosition().x - this->lengthX/2;//障碍物的左边儿
	float rbY = this->sp->getPosition().x + this->lengthX/2;//障碍物的右边儿

	if(fo->maxX>=rbZ && fo->minY>=rbTop && fo->minX<=rbY)//飞行器的右边 大于 障碍物的左边   飞行器的下边大于等于障碍物的上边  飞行器的左边小于等于障碍物的右边
	{
		if(rbTop>fo->heightDown)//障碍物的上边儿大于飞行器的飞行下限
		{
			fo->heightDown = rbTop;//设置飞行器的飞行下限
		}
		return false;
	}
	if(fo->maxX>=rbZ && fo->maxY<=rbBottom && fo->minX<=rbY)//飞行器的右边 大于 障碍物的左边   飞行器的上边小于等于障碍物的下边  飞行器的左边小于等于障碍物的右边
	{
		if(rbBottom<fo->heightUp)//障碍物的下边儿小于飞行器的飞行上限
		{
			fo->heightUp = rbBottom;//设置飞行器的飞行上限
		}
		return false;
	}
	if(fo->minX>rbY)//飞行器的左边大于障碍物的右边
	{
		if(rbTop == fo->heightDown)//障碍物的上边儿 等于 飞行器的飞行下限
		{
			fo->heightDown = HEIGHT_EDGE;//设置飞行器的飞行下限
		}
		if(rbBottom == fo->heightUp)//障碍物的下边儿 等于 飞行器的飞行上限
		{
			fo->heightUp = HEIGHT - HEIGHT_EDGE;//设置飞行器的飞行上限
		}
		return false;
	}
	if(fo->minX<rbZ && fo->maxX>rbZ)//飞行器的右边 小于 障碍物的左边   飞行器的左边 大于 障碍物的右边
	{
		if(fo->maxY<rbBottom || fo->minY>rbTop)//飞行器的上边  小于 障碍物的下边     或者      飞行器的下边  大于 障碍物的上边
		{
			return false;
		}

		if (fo->sp->boundingBox().intersectsRect(sp->boundingBox()))//判断飞行器和障碍物之后是否存在交集//判断飞行器所在的包围盒与障碍物所在的包围盒是否有交集
		{
			fo->explode();//调用飞行器的爆炸方法
			return true;
		}
		else
		{
			return false;
		}
	}
}
