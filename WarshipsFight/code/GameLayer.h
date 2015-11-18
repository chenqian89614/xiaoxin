#ifndef _GameLayer_H_
#define _GameLayer_H_
#include "cocos2d.h"
#include "WarshipsFightSceneManager.h"
#include "WarShipObject.h"
#include "HKMJObject.h"
#include "Weapon.h"
#include <list>
#include <queue>
using namespace cocos2d;
class GameLayer :public Layer
{
public:
	WarshipsFightSceneManager* wfsm;		//����ָ�򳡾���������ָ��
	TMXTiledMap* map;						//����ָ���ͼ�����ָ��
	Point firstTouchPoint;					//��һ�α������ĵ�
	Point mapPoint;							//��ͼ������
	Point touchPoint ;						//����������
	MenuItemImage* jjbgSp[5];				//����������������˵���
	MenuItemImage* shipWeapon [3];			//�����˵���
	Sprite* selectedSp;						//ѡ�п�ľ������
	int selectIndex = -1;					//ѡ�о���������
	Sprite* lifeBarSp [20];					//���ص�Ѫ��
	HKMJObject* playerHKMJ;					//��һ��ض���
	bool selectItem = false;				//�Ƿ�ѡ�о����ı�־λ
	int** Map_DATA;							//��ͼ����
	TMXLayer *colliLayer;					//��ͼ��ײ����
	int row;								//�к�
	int col;								//�к�
	std::vector<Point>* path;				//������ʻ·��������
	std::vector<Point>* tempPath;			//������ʻ·��������
	WarShipObject* lastTouchSprite ;		//��һ�ε���ľ�������
	WarShipObject* currTouchSprite ;		//��ǰ����ľ�������
	bool selectShip = false;				//��־�Ƿ�ѡ�о����ı�־λ
	Animate* anmiAc[2];						//����֡����
	int waveNum = 1;						//�о������Ĳ���
	Label* labelWaveIndex;					//��ʾ�������ı���ǩ
	int enemyShipCount = 10;				//�д�������
	bool isGameOver = false;				//��Ϸ�Ƿ����
	bool gameResult = false;				//��Ϸ��ʤ������ʧ��
	int myGold = 3000;						//�����ҽ�Ǯ
	LabelAtlas* moneyLabel;					//��ʾ��ҽ�Ǯ���ı���ǩ
	int sdsNum = 0;							//ɱ����
	int currLevelSds = 0;					//��ǰ�ؿ�
	int curGetGold = 0;						//��ý��
	LabelAtlas* sdsLabel;					//��ʾɱ�������ı���ǩ
	//��ͣ�˵���
	MenuItemImage* puaseMenu;
	//��ͣ����
	Sprite* gamePausebb;
	//���󱳾�
	Sprite* oceanbg1Sp[2];
	//��ɱ����ȴ����
	Sprite* coolSp [2];
	Sprite* (weaponeSprite) [2];			//������ȴ�������
	Sprite* (ShipCoolSprite) [5];			//������ȴ�������
	bool coolSpb = false;

	bool coolSpp = false;
	//���·����¼
	std::map<std::string, int(*)[2]>* hm;
	//����������ö���
	std::queue<int(*)[2]>* myQueue;
	//���ͼ��Ĵ�С����������·�ߵ�ƫ�������˴�Ҫ��һ������ֵ������Ϊ��ƬͼƬ�İ�߿���ƬͼƬ�İ�߸ߣ�
	Point trans;

	std::vector<Weapon*>* 	allWeaponVCT;			//����
	std::vector<Weapon*>* 	delWeaponVCT;			//����

	std::vector<WarShipObject*>* 	allShipVCT;	//���о���
	std::vector<WarShipObject*>* 	delShipVCT;
    
	int resultSequence [8][2];				//���淽������˳�������

	Sprite3D* plane3D[2];					//3D�ɻ��������
	bool planeFlag = false;					//�ɻ����еı�־λ
	int step = 1;							//�ɻ����н׶�

	//��ʼ����������
	virtual bool init();
	void initMiscellaneous();
	void initSound();
	void initListenerTouchAndCallback();
	void initRaning();
	//��ը��֡����
	void initBoomFrame();
	void initBigBoomFrame();
	void expansionRing();
	//��ʼ������ѡ��ķ���
	void initJJItem();
	//��ʼ����ͼ
	void initTMXMap();
	//��ʼ�����󱳾�
	void initOceanBg();
	//��ʼ����ĸ
	void initHKMJ();
	//��ʼ����ͼ��ײ��������
	void initTMXPZJCArray();
	//��ʼ��·����������
	void initVisitedArr();
	//��ʼ����ͣ�˵���
	void initPauseMenu();
	void puaseCallback();
	void backCallback();
	//����ҷ������ķ���
	void addWarShip(Point touchPoint ,int seleteNum);
	//���������ķ���
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	bool onShipTouchBegan(Touch* touch, Event* event);
	void onShipTouchEnded(Touch* touch, Event* event);
	//����˵����л�ѡ�д�ֻ�ķ���
	void jjbgSpCallback0();
	void jjbgSpCallback1();
	void jjbgSpCallback2();
	void jjbgSpCallback3();
	void jjbgSpCallback4();
	//�л���������
	void shipWeaponCallback0();
	void shipWeaponCallback1();
	//ȡ���˵���
	void shipWeaponCallback2();
	//������ֻ·��
	void searchPath(WarShipObject* warShip);
	//��������㷨Ѱ��
	void BFSCalPath(WarShipObject* wso);
	void transformBTMapandVector(WarShipObject* wso);
	void createFiniteTimeActionByVector(WarShipObject* warShip);
	//
//	void moveFlagCallback();
	void transformPath();//�ŵ�������ʻ·����������
	//ָ����װ��Ϊ�������кŵķ���
	Point touchPointToRowCol(Point touchPoint);
	//��ȡ����ת��
	int orderDirection(float dx,float dy);
	//����ֻ��Ӽ���
	void addTouchListener(WarShipObject* WarShipSprite);
	//����������ֵľ���
	void warShipAddChild(WarShipObject* wso);

	//��ʾ��ǰѡ�еĴ�ֻ�ĵ���
	void showWarShipItem(WarShipObject* wsoSprite);
	//��ӵ���
	bool addWeapon(int selectIndex,Point startPoint,Point finalPoint,WarShipObject* ship,int launchForm);
	//�����׼��ֻ�ľ���
	void addAimSprite();
	//�����ʾ��ֻ������Χ�ľ���
	void addSaveSprite(WarShipObject* wsoSprite);
	//��Ӵ�����ʾ
	void addWrongPrompt(Point locationMap);
	//��ӵд�
	void addEnemyShip();
	//������·���ķ�������˳�������������
	void randomSort();
	//����������ȴʱ��Ķ�ʱ�ص�����
	void weaponsCoolTimeUpdate();
	//ɾ����ֻ�ķ���
	void removeShipUpdate();
	//��Ϸ��ʼ�Ļص�����
	void startCallback();
	//��Ϸ��ʼǰ����ʱ�ķ���
	void gameStartDJS();
	//��ʱ��������״̬�ķ���
	void weaponeStateUpdate();
	//���㵼��Z����ķ���
	float callPointZ(float x,Weapon* weaponSp);
	//���㵼��Y����ķ���
	float callPointY(float x,Weapon* weaponSp);
	//���㵼�������й����е���ת�Ƕȵķ���
	float callDegree(float x,Weapon* weaponSp);
	//��������ָ��λ�ú��ж��ڳ����Χ���Ƿ��ڴ�ֻ�ܱ��ݻٵķ���
	void destroyEnemyShip(Weapon* weapone);
	//ɾ����ֻʱ���ŵı�ըЧ���ķ���
	void removeShipPlayEffect(Point tempP);
	//���㴬ֻ
	void calNearestSmartIn();
	//����������ֻ����ķ���
	float dis(WarShipObject* d1,WarShipObject* d2);
	//��������֮��ľ���
	float callTwoPointDis(Point startPoint,Point EndPoint);
	//���д��ں�ĸ��Χʱ
	void enemyShipAtHKMJUpdate();
	//����ĸ����Ѫ
	void reduceBlood();
	//��Ϸ�����ķ���               1Ϊ��Ϸʧ�ܣ�0Ϊʤ��
	void gameOver();
	//���¿�ʼ�������Ϸ
	void restartCallback();
	//�˳���Ϸ�������˵�
	void tcCallback();
	//����Ч������
	void oceanUpdate();
	//˲��ɱ��ȫ���д�
	void desAllEnemyShip();
	//����ĸ���ı�ɱ����ȴ��ʱ�ص�
	void playerHKMJCoolTimeUpdate();
	//����ĸ���ı�ɱ�����ɻ�
	void planeFlyAtShip();
	void planeUpdate();
	void RecoveryStateCallback();
	void playSound();
	CREATE_FUNC(GameLayer);
};

#endif
