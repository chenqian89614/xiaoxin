#include "FlyLayer.h"
#include "../frameHelp/ParticleSystemHelp.h"
#include "../frameHelp/MusicManager.h"
#include "Constant.h"

bool FlyLayer::init()
{
	//���ø���ĳ�ʼ��
    if (!Layer::init())
    {
        return false;
    }

    this->setTag(INDEX_FLYLAYER);//���ýڵ�ı�ǩ

    visibleSize = Director::getInstance()->getVisibleSize();//��ȡ�ɼ�����ߴ�
	origin = Director::getInstance()->getVisibleOrigin();//��ȡ�ɼ�����ԭ������

	setTouchEnabled(true);
	auto listenerET = EventListenerTouchOneByOne::create();//����һ����������
	listenerET->setSwallowTouches(true);//�����´�����
	listenerET->onTouchBegan = CC_CALLBACK_2(FlyLayer::myOnTouchBegan, this);//��ʼ����ʱ�ص�onTouchBegan����
	listenerET->onTouchMoved = CC_CALLBACK_2(FlyLayer::myOnTouchMoved, this);//�����ƶ�ʱ�ص�onTouchMoved����
	listenerET->onTouchEnded = CC_CALLBACK_2(FlyLayer::myOnTouchEnded, this);//̧��ʱ�ص�onTouchEnded����
	listenerET->onTouchCancelled = CC_CALLBACK_2(FlyLayer::myOnTouchCancelled, this);//��ֹ����ʱ�ص�onTouchCancelled����

	sh = new SpriteManager(this);
	sh->SpPause();//��� ��ͣͼƬ����
	sh->backgroundRoll();

	new ParticleSystemHelp();
	pc = new PauseCode(this);

	//ȡ���ݵĴ���
	int p1 = UserDefault::getInstance()->getIntegerForKey("1",779);
	int p2 = UserDefault::getInstance()->getIntegerForKey("2",110);
	int p3 = UserDefault::getInstance()->getIntegerForKey("3",30);
	int p4 = UserDefault::getInstance()->getIntegerForKey("4",30);

	ids = new std::string("JC");//��Ծ������
	fo =new FlyObject(ids, this, Rect(568,23,606-568,46-23), 32, 18, 64, 36,
					  Rect(p1,p2,p3,p4), 32, 35, 26, 26,
								 3);//����������
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerET->clone(), fo->sp);//ע�������

	//�ؿ�����
	gdData = new GDData(this);
	gdData->createFlyData();

	if(MusicManager::onSound == true)
	{
		MusicManager::playFlyLayerMusic();//���ű�������
	}
	else
	{
		MusicManager::noPlaySound = true;
	}


	//���ö�ʱ�ص�ָ�������ɻ�
	Director* director = Director::getInstance();
	auto sched = director->getScheduler();

	sched->scheduleSelector(SEL_SCHEDULE(&FlyLayer::updateAll), this, INTERVAL, false);//���ϻص�

	return true;
}

void FlyLayer::updateAll()
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

	if(isUpdateAll == false)
	{
		timeCountCollision++;
		//����ֹͣ�ƶ�
		spMap["bg"]->stopAllActions();
		spMap["bg1"]->stopAllActions();

		if(timeCountCollision * INTERVAL >= 0.2)//��ײ����0.2s��ͣ��ʱ��
		{
			timeCountCollision = 0;
			gsm->goFlyLayer();
		}
		return;
	}

	timeCount++;
	gdData->createFlyData();

	fo->updata();//���·�������״̬

	updateBarrier();//���� �ϰ���ķ���
	collisionDetection();
	deleteBarrier();
}

void FlyLayer::collisionDetection()
{
	if(barrierVector.empty())
		return;
	iter=barrierVector.begin();
	for(;iter!=barrierVector.end();iter++)
	{
		if((*iter)->collisionFo(fo))//��ײ���
		{
			isUpdateAll = false;
		}
	}
}
void FlyLayer::updateBarrier()
{
	if(barrierVector.empty())
		return;
	iter=barrierVector.begin();
	for(;iter!=barrierVector.end();iter++)
	{
		(*iter)->reflesh();
	}
}
void FlyLayer::deleteBarrier()//ɾ�� ����Ļ�� �ϰ���
{
	if(barrierVector.empty())//���ϰ����б� Ϊ��  �򷵻�
		return;

	iter=barrierVector.begin();
	for(;iter!=barrierVector.end();)
	{
		if((*iter)->sp->getPosition().x+(*iter)->lengthX/2 < 0)
		{
			this->removeChild((*iter)->sp,true);
			iter = barrierVector.erase(iter);//iter = ָ��iter����һ��   ����barrierVectorɾ��iter
		}
		else{iter++;}
	}
}


//��ʼ�����¼��Ĵ�����
bool FlyLayer::myOnTouchBegan(Touch *touch, Event *event)
{
	isTouch = true;
	return true;
}
//�����ƶ��¼��Ĵ�����
void FlyLayer::myOnTouchMoved(Touch *touch, Event *event){}
//���ؽ����¼��Ĵ�����
void FlyLayer::myOnTouchEnded(Touch *touch, Event *event)
{
	isTouch = false;
}
//������ֹ�¼��Ĵ�����
void FlyLayer::myOnTouchCancelled(Touch *touch, Event *event){myOnTouchEnded(touch,event);}
