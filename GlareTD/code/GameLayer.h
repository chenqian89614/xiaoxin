#ifndef _GameLayer_H_
#define _GameLayer_H_
#include "GameSceneManager.h"
#include "Weapon.h"
#include "DialogLayer.h"
#include "BulletSprite.h"
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class GameLayer : public cocos2d::Layer
{
public:
	//���캯��
	GameLayer();
	//��������
	virtual ~GameLayer();
	//���صĸ���ĳ�ʼ����
	virtual bool init();
	Menu* pMenu;
	void zanTing(Object* pSender);
	//����·��֮ǰ��һЩ�����ĳ�ʼ��
	void initForCalculate();
	//�������label
	void addLabel();
	//�������A*�㷨
    bool BFSAStar();
	//��ʼ��ȥ��δȥ��������
	void initVisitedArr();
	//�ͷ��ڴ�
	void freeMemory();
	//��������·���ķ���
    bool calculatePath();
	//��ӡ����·��
	void printPath();
	//��ӷ������˵�����
	void addMenuSprite();
	//���÷������˵�����ɼ�
	void setWeaponTrue();
    //׼������--��Բ��
    void ready();
    //�����ִ�action��������������ߵķ���
    void run();
    //���������
    void foundMonsters();
    //���ֵķ���
    void monsterRun(Node* node);
    void removeSpriteAdd();
    //ɾ������ķ���
    void removeSprite(Node* node);
    //����ͼ�������к�ת��Ϊ��Ӧ���ӵ���ͼ����
    Point fromColRowToXY(int col, int row);
    //�����ص�λ��ת��Ϊ��ͼ�������к�
    Point fromXYToColRow(int xPos, int yPos);
	//���۷������ķ���
	void sellWeapon(Weapon* weapon);
	//���������˵�����ɼ�
	void setUpdateTrue();
	//�����������
	void setValue();
	//���ؿ�ʼ�ķ���
    bool onTouchBegan(Touch *pTouch, Event *pEvent);
    //�����ƶ��ķ���
    void onTouchMoved(Touch *pTouch, Event *pEvent);
    //����̧��ķ���
    void onTouchEnded(Touch *pTouch, Event *pEvent);
    //��Ұ��ʱ����Ч
	void addParticle(Point point,float time);
	//Ұ�ֵ��յ�ʱ����Ч
	void addParticle(Point point,int id,float time);
	//Ұ����ʱ����Ч
	void addParticle1(Point point,int id,float time);
	//��Ϸ����ʱ�ı�ը��Ч
	void addParticle(Point point,int id,float time,float angle);
	void addParticle2(Point point,float time);
	//�ص�����
	void menuCallbackItem0(Object *pSender);
	//�����ֵķ���
    void attack();
    //��һ�������������ֵ�Ѫ�ķ���
	void fireBulletOne(int weap,int target,float dirction,Point position,float lengthVector);
	//�ڶ��������������ֵ�Ѫ�ķ���
	void fireBulletTwo(int weap,int target,float dirction,Point position);
	//�����������������ֵ�Ѫ�ķ���
	void fireBulletThree(int weap,int target,float dirction,Point position);
	//�����ӵ��ķ���
	void runBullet();
	//�ֵ�Ѫ�ķ���
	void cutBloodOne(Node* node);
    //ִ����Ч�˵��Ļص�����
    void playGameCallback();
    //��Ϸ�����ķ���
	void loseGame();
public:
	int bulletData[10];
	//����ָ��DrawNode������ָ��
	DrawNode* dn;
	//TMXLayerָ��
	TMXLayer* tmxLayer;
	Point endWorld;
	//��������ָ��
	ProgressTimer *left;
	Sprite* particle;
	Sprite* bullet1;
	Sprite* cc;
	float TIME_MAIN;
	//���ͼ��Ĵ�С����������·�ߵ�ƫ�������˴�Ҫ��һ������ֵ������Ϊ��ƬͼƬ�İ�߿���ƬͼƬ�İ�߸ߣ�
	Point trans;
	//��ǰ������label
	LabelTTF *scoreL;
	//��ǰ�غ�����label
	LabelTTF *passL;
	//��ǰ��Ǯ
	LabelTTF *moneyL;
	//��ǰ������
	LabelTTF *tenL;
	//��ʾ�������������Ǯ��label
	LabelTTF *uMoneyL;
	//��ʾ����������õĽ�Ǯ��label
	LabelTTF *sMoneyL;
	//��Źֵ�����
	Array* arrMon;
	//��ŷ�����
	Array* arrWeap;
	//��Ų˵�����������
	Array* arrMenu;
	//���action����
	Array* arrAction;
	//��Ÿ���
	Array* arrBullet;
	//��������Ĳ˵���ť����
	Array* arrSellUpdate;
	//������������ϵ
	Point startWorld;
	//���˶���־λ
	bool isMonsterRun ;
	//�����ֵı�־λ
	bool isfoundMonster;
	//����������ָ��
	GameSceneManager* man;
	//�㷨������ϵı�־λ
	bool isCaulateOver;
	//������ʾ����ֵ�Ķ���
	int ten;
	//��ҵĽ��
	int money;
	//��ʼ��־����
	Sprite* startSprite;
	//Ұ�־������
	Sprite *ygSprite;
	//Ŀ�꾫��
	Sprite* targetSprite;
	//��ͼ��row
	int row;
	//��ͼ��col
	int col;
	//���������������������ң��������£�����Ϊ��̬��ά����Ĵ���
	int** MAP_DATA;
	//���·��������
	vector <Point > way;
	vector <int> bulletArray;
	//��¼·������
	int** length;
	//����������ö���
	queue<int(*)[2]>* myQueue;
	//���·����¼
	map<string, int(*)[2]>* hm;
	//typedef�Զ�������
	typedef vector<int(*)[2]>* INTPVECTORP;
	//��һ�ε���ڲ˵�λ�ñ�־λ
	bool touchMove = false;
	//��touchEnd���Ƿ��Ƴ��������ı�־λ
	bool removeWeap;
	//�������ּ���
	int pass;
	//��ǰ�ܵ÷���
	int score;
	//����������
	Weapon* updateWeapon;
	//���������ı�־λ
	bool WeaponUpdate;
	//������Ϸ�����ı�־λ
	bool GameOver;
	//��ͣ��Ϸ�ı�־λ
	static bool isPause;

	//��������������ʱ�Ĺ�Ȧ�������
	Weapon* trSprite;
	//�����ĸ��˵��������ľ������
	Weapon *onePlayer;
	Weapon *twoPlayer;
	Weapon *threePlayer;
	Weapon *fourPlayer;

	CREATE_FUNC(GameLayer);
};

#endif
