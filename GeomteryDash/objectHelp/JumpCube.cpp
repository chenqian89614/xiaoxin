#include "JumpCube.h"
#include "../frameHelp/MusicManager.h"
#include "../hellocpp/GameLayer.h"

JumpCube::JumpCube(std::string* stTemp, Layer* layer, Rect recta, float spLocationX, float spLocationY, float spLength, int localZOrder)
{
	this->lengthX = spLength;
	this->lengthY = spLength;
	this->layer = layer;

	this->st = stTemp;//跳跃方块 id
	sp = Sprite::createWithTexture(((GameLayer*)(layer))->sh->batchNode->getTexture(),recta);//创建精灵
	sp->setAnchorPoint(Point(0.5f,0.5f));//设置精灵的锚点   设为中心点
	sp->setPosition(Point(spLocationX,spLocationY));//设置精灵的位置
	Size size=sp->getContentSize();//获取精灵的尺寸
	float scaleX=spLength/size.width;//计算出精灵X方向缩放比
	float scaleY=spLength/size.height;//计算出精灵Y方向缩放比
	sp->setScaleX(scaleX);//设置精灵X方向缩放比
	sp->setScaleY(scaleY);//设置精灵Y方向缩放比
	sp->setColor(Color3B(102,204,35));
	layer->addChild(sp,localZOrder);//将精灵添加到布景中

	p = sp->getPosition();
	r = sp->getRotation();

	psh = new ParticleSystemHelp();
	layer->addChild(psh->psq1, BatchNodeZOrder-1);//将滑翔特效添加到layer里
	psh->psq2->retain();
	psh->psq1->setVisible(false);
	psh->isPsq1 = false;

}
JumpCube::~JumpCube()
{
	delete st;
}
//当跳跃方块  处于   isJump==false  和   isDown==false  的状态时    调用该方法
void JumpCube::reflesh(float maxH)
{
	if(maxH != this->sp->getPosition().y)//判断最大高度是否为当前方块的位置
	{
		isDown = true;//如果不是，则方块进行下落动作
	}
	p = sp->getPosition();//记录方块当前位置
	r = sp->getRotation();//记录方块当前旋转角
}
void JumpCube::Jump()
{
	if(psh->isPsq1 == true)//判断当前滑翔特效是否显示
	{//若当前有滑翔特效显示
		psh->psq1->retain();//保持滑翔粒子系统指针
		psh->psq1->stopSystem();//停止滑翔粒子系统
		psh->isPsq1 = false;//记录滑翔粒子系统的标志位设为false
	}
	timeCount++;//时间计数器加一
	sp->setPosition(Point(p.x, p.y + vJump * timeCount * INTERVALJC));//设置方块的位置
	sp->setRotation(r + vRotationJump * timeCount * INTERVALJC);//设置方块的旋转角
	if(sp->getPosition().y - p.y >= JCJH)//判断y方向的位移量是否超过常数JCJH
	{
		this->isJump = false;//将上升标志位设为false
		timeCount = 0;//时间计数器置零
		p = sp->getPosition();//记录方块当前位置
		sp->setRotation(r + 90);//设置方块的旋转角
		r = sp->getRotation();//记录方块当前旋转角
	}
}
void JumpCube::Down()
{

	if(psh->isPsq1 == true)//判断当前滑翔特效是否显示
	{
		psh->psq1->retain();//保持滑翔粒子系统指针
		psh->psq1->stopSystem();//停止滑翔粒子系统
		psh->isPsq1 = false;//记录滑翔粒子系统的标志位设为false
	}

	timeCount++;//时间计数器加一
	sp->setPosition(Point(p.x, p.y - vDown * timeCount * INTERVALJC));//设置方块的位置
	sp->setRotation(r + vRotationJump * timeCount * INTERVALJC);//设置方块的旋转角
}
void JumpCube::refleshAngleAndPosition(float y)
{
	if(psh->isPsq1 == false)//判断当前滑翔特效是否显示
	{
		psh->psq1->setSourcePosition(Point(sp->getPosition().x - lengthX / 2, y - lengthY / 2));//设置滑翔粒子系统的位置
		psh->psq1->resetSystem();//重置滑翔粒子系统
		psh->psq1->setVisible(true);//设置粒子系统可见
		psh->isPsq1 = true;//记录滑翔粒子系统的标志位设为true
		psh->psq1->retain();//保持滑翔粒子系统指针
	}

	float angle = (sp->getRotation() - r);//计算当前旋转角的偏移量
	if(0<angle)//判断偏移量是否大于0
	{
		sp->setRotation(r + 90);//将方块顺时针旋转90度
	}

	timeCount = 0;//时间计数器置零
	this->isDown = false;//将记录方块下落状态的标志位设为false
	p = Point(sp->getPosition().x,y);//记录方块当前位置
	r = sp->getRotation();//记录方块当前旋转角
	this->sp->setPosition(p);//设置方块精灵位置
}
void JumpCube::explode()
{
	psh->psq1->stopSystem();
	layer->addChild(psh->psq2,BatchNodeZOrder-1);//添加爆炸效果


	psh->psq2->setSourcePosition(Point(sp->getPosition().x-150 , sp->getPosition().y-70));
	psh->psq2->resetSystem();

	sp->setVisible(false);//设置方块精灵不可见

	MusicManager::playExplosionEffect();
}
