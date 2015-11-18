#ifndef __PokerLayer_H__
#define __PokerLayer_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "PokerSceneManager.h"
#include "PuKe.h"

using namespace cocos2d;
using namespace std;
using namespace ui;

class GameLayer : public cocos2d::Layer
{
public:
	//������ʾʱ���
	LabelTTF* timeLabel;
	//����ͷ��
	Sprite *dizhuHeadImage[3];
	//ũ��ͷ��
	Sprite *nongminHeadImage[3];
	//���ͼ��
	Sprite *unKnow[3];
	//����Ȩ״̬
	Sprite *actKnow[3];
	//δ�õ���Ȩ״̬
	Sprite *deKnow[3];
	//�Ƶı���ͼ������ʣ�����ŵĺ���ҵ�
	Sprite *poke[5];
	//׼������
	Sprite *ready[3];
	//����
	Sprite *buchu[3];
	//�ӱ�����
	Sprite *bei2;			//�ӱ�
	//=====Ϊÿ����Ҵ�������===
	Sprite *playerSprite[5];
	Sprite *nextPlayerSprite[5];
	Sprite *lastPlayerSprite[5];
	//========������
	Sprite *setBack;		//���ñ�����
	Sprite *yesOrNo;		//�뿪������
	Sprite *mask[54];		//ѡ�б�����
	//���ܴ����ľ���
	Sprite *chuSprite;		//���ƻ�ɫ
	Sprite *resetSprite;	//��ѡ��ɫ
	//���ڷ��Ƶľ���===
	//�����Ƶľ���
	Sprite* firstCard;
	Sprite* secondCard;
	Sprite* thirdCard;
	//��Ϸ����
	Sprite* gameOverSprite[4];
	//��ըͼƬ
	Sprite* wangDropSprite;
	//ը��
	Sprite* zhaDropSprite;
	Sprite* planeSprite;
    //�����Ƶķ����Լ����е�����ͼ
    Texture2D* pzm;		//������ͼ
    Texture2D* pfm;		//�Ʒ���ͼ
    //�����ƣ���ǰ������
    Texture2D* zm;		//��ǰ�ƾ�������ͼ
    Texture2D* fm;		//��ǰ�ƾ��鷴��ͼ
    //��ʱ�����Ƶ�X���꣬��������
    float firstX;
    float secondX;
    float thirdX;
	//ÿ���Ƶ���ת�Ƕ�
    float angle=0;
    //ÿ���Ƶ��к���
    int firstRow;
    int firstCol;
    int secondRow;
    int secondCol;
    int thirdRow;
    int thirdCol;
	//=============�˵�
	Menu *orderMenu;		//�е���
	Menu *noOrderMenu;		//����
	Menu *readyMenu;		//׼��
	Menu *qdzMenu;			//������
	Menu *bqMenu;			//��������
	Menu *chuMenu;			//����
	Menu *resetMenu;		//��ѡ
	Menu *buChuMenu;		//����
	Menu *tiShiMenu;		//��ʾ
	//vector
	std::vector<Sprite*> *tempCardVector0;	//
	std::vector<Sprite*> *tempCardVector1;	//
	std::vector<Sprite*> *tempCardVector2;	//
	std::vector<Sprite*> *vecPuKe;		//	��ű����˿�id������
	//animate ��ը
	Animate *animateWang;
	SpriteFrame *SpriteFrameWang[10];
	Sprite *wangSprite;
	//Animate ը��
	Animate *animateZha;
	SpriteFrame *SpriteFrameZha[9];
	Sprite *zhaSprite;

	LabelAtlas *bLabelAtlas;
	LabelAtlas *labelAtlas;//��ǰ��ҵ�LabelAtlas,id=0
	LabelAtlas *lastLabelAtlas;//��һ���LabelAtlas��id=2
	LabelAtlas *nextLabelAtlas;//��һ���LabelAtlas��id=1
	bool checkCreate = false;//�Ƿ񴴽���ѡ��
	bool exit = false;//�Ƿ񴴽��뿪�Ի���
	bool set = false;//�����ж����ñ������Ƿ�ɼ�
	bool first = true;//�Ƿ��һ�ΰ��·��ؼ�
	bool animZha=false;//ɾ����֡�����־λ

	double beginX;
	double beginY;
	double moveX;
	double moveY;



	int iCount=0;//�˿�
	int rulePuKe=0;
	int array[17];
	PuKe*(puke) [54];
	PuKe*(player) [20];
	PuKe*(last) [20];
	PuKe*(next) [20];

public:
	PokerSceneManager *psm;
	//�����Ϸ���õ��ľ���
	void addSprite();
	//���LabelAltals
	void addLabel();
	//��Ӳ˵���
	void addMenuItem();
	//��ʼ�е���
	void addOrderOrNo();
	//����������Ͳ�������
	void addQiangOrNo();
	//��Ӷ�ʱ�ص�
	void addUpdate();
	//������������ת
	void createRotate();
	//��ը��֡����
	void initWang();

	void initZhaDan();
	//��ʼ���˿ˣ��ָ�
	void initPuKe();
	//���ñ���˳��ִ��
	void setBeiMove();

	//��ʼ���ķ���
	virtual bool init();
	int random();
	void preloadMuiscOrEffect();
	//������Ч
	void playOrderOrRob();
	//��Ϸ��ʼ����ť�Ĵ���
	void playGameBtn();
	//�����������һЩ����ǰ���ж�
	void isChuPai();
	//���Ѿ�������
	void HadCard();
	//ɾ����֡����
	void removeAnimSprite();
	//���÷ɻ���λ��
	void setPlaneMess();

	//touch
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	//call back
	void menuReadyCallback(Ref* sender);
	void menuSetCallback(Ref* sender);
	void menuExitCallback(Ref* sender);//�뿪��Ϸ
	void menuQiangCallback(Ref* sender);//�������¼�������
	void menuNoQiangCallback(Ref* sender);//���������¼�������
	void menuChaCallback(Ref* sender);//2������λ���Լ���ʾ
	void menuPlayCallback(Ref* sender);//��ʼ��Ϸ,����
	void menuResetCallback(Ref* sender);//��ѡ
	void menuBuChuCallback(Ref* sender);//�����ص�����
	void menuTishi(Ref* sender);	//tishi

	void menuOkCallback(Ref* sender);
	void menuCancelCallback(Ref* sender);
	void menuOrderCallback(Ref* sender);//��
	void menuNoOrderCallback(Ref* sender);//����
	void gameOver(Ref* sender);	//��Ϸ����
	//��ѡ��ص�����
	void menuEffectCallback(Ref* pSender,CheckBox::EventType type);
	void menuMusicCallback(Ref* pSender,CheckBox::EventType type);

	//=========��ʱ�ص�����==============
	//��ʱ�ص�17�Σ�����
	void update_puke();
	//����������ҵ�״̬
	void updateDrawOther(float dt);
	//��ʱ�ص������Ƶ���ת
	void updateRotate(float ft);
	//�����������������Ŀ��
	void updateDrawOtherCards();
	//��������
	void updatePuke(float dt);
	//��ȡϵͳʱ��
	void getSystemTime(float dt);
	//���Ÿ�����Ч
	void updatePlayEffect(float dt);
	void gameDataReset();
    //Cocos2d-x�ж����һ���꣬����ָ�����͵Ķ���
    //��������Ӧ�ĳ�ʼ�����ͷŹ���
    CREATE_FUNC(GameLayer);
};

#endif
