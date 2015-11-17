#include "GameLayer.h"
#include "../frameHelp/ParticleSystemHelp.h"
#include "../frameHelp/MusicManager.h"
#include "Constant.h"

bool GameLayer::init()
{
	//���ø���ĳ�ʼ��
    if (!Layer::init())
    {
        return false;
    }

    this->setTag(INDEX_GRAMLAYER);//���ýڵ�ı�ǩ

    visibleSize = Director::getInstance()->getVisibleSize();//��ȡ�ɼ�����ߴ�
	origin = Director::getInstance()->getVisibleOrigin();//��ȡ�ɼ�����ԭ������

	new ParticleSystemHelp();
	//���������
	sh = new SpriteManager(this);
	sh->SpPause();//��� ��ͣͼƬ����
	sh->backgroundRoll();

	pc = new PauseCode(this);

	initObjectOrSprite();//��ʼ��   ���� ��  ��������  ��  ��Ծ�ķ���

	//�ؿ�����
	gdData = new GDData(this);
	if(indexGK == 1)
	{
		gdData->createData();
	}
	else if(indexGK == 3)
	{
		gdData->createData3();
	}

	//���ö�ʱ�ص�ָ�������ɻ�
	Director* director = Director::getInstance();
	auto sched = director->getScheduler();

	sched->scheduleSelector(SEL_SCHEDULE(&GameLayer::updateAll), this, INTERVAL, false);//���ϻص�

	return true;
}

void GameLayer::updateAll()
{
	if(timeCount == 1300)
	{
		//����ֹͣ�ƶ�
		spMap["bg"]->stopAllActions();
		spMap["bg1"]->stopAllActions();
		//�����澲ֹ  �Ĵ���
		iter=barrierVector.begin();
		for(;iter!=barrierVector.end();iter++)
		{
			if(((std::string*)((*iter)->st))->at(0) == 'd')
			{
				(*iter)->sp->stopAllActions();
			}
		}
		sh->win();
		return;
	}
	timeCount++;
	if(isUpdateAll == false)
	{
		timeCountCollision++;
		//����ֹͣ�ƶ�
		spMap["bg"]->stopAllActions();
		spMap["bg1"]->stopAllActions();
		//�����澲ֹ  �Ĵ���
		iter=barrierVector.begin();
		for(;iter!=barrierVector.end();iter++)
		{
			if(((std::string*)((*iter)->st))->at(0) == 'd')
			{
				(*iter)->sp->stopAllActions();
			}
		}
		if(timeCountCollision * INTERVAL >= 0.2)//��ײ����0.2s��ͣ��ʱ��
		{
			timeCountCollision = 0;
			gsm->goGameLayer(indexGK);
		}
		return;
	}
	if(indexGK == 1)
	{
		gdData->createData();
	}
	else if(indexGK == 3)
	{
		gdData->createData3();
	}
//	CCLOG("%d",timeCount);

	if(jc->isJump == true && jc->isDown == false)
	{
		jc->Jump();
	}
	if(jc->isJump == false && jc->isDown == true)
	{
		jc->Down();
	}
	if(jc->isJump == false && jc->isDown == false)
	{
		refleshJumpCube();//����  ��Ծ����  ��״̬
	}
	//ʵ�� ��ָһֱ������Ļ   ��Ծ����  һֱ��Ծ�Ĺ���
	if( isTouch == true )//�ж��Ƿ���
	{
		if(jc->isDown == false && jc->isJump == false)//��Ծ����  �Ȳ����� ��Ծ״̬  �ֲ�����  ����״̬
		{
			jc->isJump = true;
		}
	}

	collisionDetection();
	updateBarrier();//���� �ϰ���ķ���
	deleteBarrier();
}

void GameLayer::updateBarrier()
{
	if(barrierVector.empty())
		return;
	bool flagUpdateBarrier = false;
	iter=barrierVector.begin();
	for(;iter!=barrierVector.end();iter++)
	{
		(*iter)->reflesh();
		if(((std::string*)((*iter)->st))->at(0) == 'd')
		{
			if((*iter)->sp->getPosition().x+(*iter)->lengthX/2 <= 0)
			{
				float x = zh->sp->getPosition().x + visibleSize.width/4;
				float y = zh->sp->getPosition().y;
				ids = new std::string("dm5");//���ε���id
				zh=new RectBarrier(ids,this,Rect(129,685,243-129,802-685), x, y, visibleSize.width/4, visibleSize.height*0.25, GroundZOrder);//��������
				zh->sp->setColor(Color3B(125,7,216));
				flagUpdateBarrier = true;
				zh->reflesh();
			}
		}
	}
	if(flagUpdateBarrier == true)
		barrierVector.push_back(zh);
}
void GameLayer::collisionDetection()
{
	if(barrierVector.empty())
		return;
	iter=barrierVector.begin();
	for(;iter!=barrierVector.end();iter++)
	{
		float min = jc->sp->getPosition().x-jc->lengthX/2;//��Ծ�������߶�
		float max = jc->sp->getPosition().x+jc->lengthX/2;//��Ծ������ұ߶�
		float target1 = (*iter)->sp->getPosition().x - (*iter)->lengthX/2;//�ϰ�������
		float target2 = (*iter)->sp->getPosition().x + (*iter)->lengthX/2;//�ϰ�����ұ�
		if(min<=target2&&target1<=max)
		{
			if((*iter)->collision(jc))//��ײ���
			{
				isUpdateAll = false;
			}
		}
	}
}
//����Ծ����  ����   isJump==false  ��   isDown==false  ��״̬ʱ    ���ø÷���
void GameLayer::refleshJumpCube()
{
	if(barrierVector.empty())
		return;
	float maxH = 0;
	for(std::vector<Barrier*>::iterator iter=barrierVector.begin();iter!=barrierVector.end();iter++)
	{
		float center = jc->sp->getPosition().x;//��Ծ���������
		float target1 = (*iter)->sp->getPosition().x - (*iter)->lengthX/2;//�ϰ�������
		float target2 = (*iter)->sp->getPosition().x + (*iter)->lengthX/2;//�ϰ�����ұ�

		if(target1<=center&&center<=target2)//��Ծ��������� ���ڵ���  �ϰ�������  && ��Ծ��������� С�ڵ���  �ϰ�����ұ�
		{
			if((*iter)->sp->getPosition().y + (*iter)->lengthY/2 + jc->lengthY/2 > maxH)
			{
				maxH = (*iter)->sp->getPosition().y + (*iter)->lengthY/2 + jc->lengthY/2;
			}
		}
	}
	jc->reflesh(maxH);//��Ծ���� ��  ���·���
}

void GameLayer::deleteBarrier()//ɾ�� ����Ļ�� �ϰ���
{
	if(barrierVector.empty())//���ϰ����б� Ϊ��  �򷵻�
		return;

	iter=barrierVector.begin();
	for(;iter!=barrierVector.end();)
	{
		if((*iter)->sp->getPosition().x+(*iter)->lengthX/2 < 0)
		{
			this->removeChild((*iter)->sp,true);
			iter = barrierVector.erase(iter);//iter = ָ��iter����һ��
		}
		else{iter++;}
	}
}

//��ʼ�����¼��Ĵ�����
bool GameLayer::myOnTouchBegan(Touch *touch, Event *event)
{
	isTouch = true;
	return true;
}
//�����ƶ��¼��Ĵ�����
void GameLayer::myOnTouchMoved(Touch *touch, Event *event){}
//���ؽ����¼��Ĵ�����
void GameLayer::myOnTouchEnded(Touch *touch, Event *event)
{
	isTouch = false;
}
//������ֹ�¼��Ĵ�����
void GameLayer::myOnTouchCancelled(Touch *touch, Event *event){myOnTouchEnded(touch,event);}
void GameLayer::initObjectOrSprite()
{
	setTouchEnabled(true);
	auto listenerET = EventListenerTouchOneByOne::create();//����һ����������
	listenerET->setSwallowTouches(true);//�����´�����
	listenerET->onTouchBegan = CC_CALLBACK_2(GameLayer::myOnTouchBegan, this);//��ʼ����ʱ�ص�onTouchBegan����
	listenerET->onTouchMoved = CC_CALLBACK_2(GameLayer::myOnTouchMoved, this);//�����ƶ�ʱ�ص�onTouchMoved����
	listenerET->onTouchEnded = CC_CALLBACK_2(GameLayer::myOnTouchEnded, this);//̧��ʱ�ص�onTouchEnded����
	listenerET->onTouchCancelled = CC_CALLBACK_2(GameLayer::myOnTouchCancelled, this);//��ֹ����ʱ�ص�onTouchCancelled����


	//======����====
	ids = new std::string("dm1");//���ε���id
	tb=new RectBarrier(ids,this,Rect(129,685,243-129,802-685),visibleSize.width/8,visibleSize.height/8, visibleSize.width/4, visibleSize.height*0.25, GroundZOrder);//��������
	tb->sp->setColor(Color3B(125,7,216));
	barrierVector.push_back(tb);

	ids = new std::string("dm2");//���ε���id
	tb=new RectBarrier(ids,this,Rect(129,685,243-129,802-685),visibleSize.width/8*3,visibleSize.height/8, visibleSize.width/4, visibleSize.height*0.25, GroundZOrder);//��������
	tb->sp->setColor(Color3B(125,7,216));
	barrierVector.push_back(tb);

	ids = new std::string("dm3");//���ε���id
	tb=new RectBarrier(ids,this,Rect(129,685,243-129,802-685),visibleSize.width/8*5,visibleSize.height/8, visibleSize.width/4, visibleSize.height*0.25, GroundZOrder);//��������
	tb->sp->setColor(Color3B(125,7,216));
	barrierVector.push_back(tb);

	ids = new std::string("dm4");//���ε���id
	tb=new RectBarrier(ids,this,Rect(129,685,243-129,802-685),visibleSize.width/8*7,visibleSize.height/8, visibleSize.width/4, visibleSize.height*0.25, GroundZOrder);//��������
	tb->sp->setColor(Color3B(125,7,216));
	barrierVector.push_back(tb);

	ids = new std::string("dm5");//���ε���id
	zh=new RectBarrier(ids,this,Rect(129,685,243-129,802-685),visibleSize.width/8*9,visibleSize.height/8, visibleSize.width/4, visibleSize.height*0.25, GroundZOrder);//��������
	zh->sp->setColor(Color3B(125,7,216));
	barrierVector.push_back(zh);

	//ȡ���ݵĴ���
	int p1 = UserDefault::getInstance()->getIntegerForKey("1",779);
	int p2 = UserDefault::getInstance()->getIntegerForKey("2",110);
	int p3 = UserDefault::getInstance()->getIntegerForKey("3",30);
	int p4 = UserDefault::getInstance()->getIntegerForKey("4",30);

	ids = new std::string("JC");//��Ծ����id
	jc =new JumpCube(ids, this, Rect(p1,p2,p3,p4), JCX, JCY, LENGTHJC, 3);//������Ծ����   SPIC[1]
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerET, jc->sp);//ע�������

	if(MusicManager::onSound == true)
	{
		MusicManager::playGameLayerMusic();//���ű�������
	}
	else
	{
		MusicManager::noPlaySound = true;
	}
}
