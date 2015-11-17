#include "Barrier.h"
#include "../hellocpp/GameLayer.h"
#include "../hellocpp/FlyLayer.h"
TriangleBarrier::TriangleBarrier
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
	idChar = 'T';

	sp = Sprite::createWithTexture(((GameLayer*)(layer))->sh->batchNode->getTexture(),recta);//创建精灵
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
	else if(layer->getTag() == INDEX_FLYLAYER)
	{
		((FlyLayer*)(layer))->sh->batchNode->addChild(sp,localZOrder);//将精灵添加到布景中
	}

	this->p = sp->getPosition();//记录障碍物当前位置
}

bool TriangleBarrier::collision(JumpCube* jc)
{
	Point point(jc->sp->getPosition().x-this->sp->getPosition().x,jc->sp->getPosition().y-this->sp->getPosition().y);
	float distance = point.getLength();//方块的中心点与三角形中心点 之间的距离
	float length = jc->lengthX/2+this->lengthX/2;//距离的临界距离
	if(distance<=length)//实际记录是否小于等于临界距离
	{
		jc->explode();//调用方块的爆炸方法
		return true;
	}
	else
	{
		return false;
	}
}
bool TriangleBarrier::collisionFo(FlyObject* fo)
{
	if (fo->sp->boundingBox().intersectsRect(sp->boundingBox()))//判断飞行器与障碍物是否有交集
	{
		fo->explode();//调用飞行器的爆炸方法
		return true;
	}
	else
	{
		return false;
	}
}
