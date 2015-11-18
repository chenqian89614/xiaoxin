#ifndef __GameLayer_H__
#define __GameLayer_H__

#include "cocos2d.h"
#include <Box2d/Box2d.h>
#include "../bnBox2DHelp/PhyObject.h"
#include "../bnBox2DHelp/MyContactListener.h"
#include "../bnGeolibHelper/BNPolyObject.h"
#include "../bnGeolibHelper/IsNotCut.h"
#include "GameSceneManager.h"
#include "../bnGeolibHelper/WDHelp.h"
#include "WelcomeLayer.h"
#include "MyFCData.h"
using namespace cocos2d;

class GameLayer : public cocos2d::Layer
{
public:
	Label *label;//Ŀ�������ǩ
	Label *labelLast;//ʣ������ٷֱȱ�ǩ
	//�и��ߵ�����յ�����
	float lxs;
	float lys;
	float lxe;
	float lye;
	//ԭʼ�����
	float areaInit;
	float areaCurr;//��ǰʣ�µ����
	float winArea;//ʤ�����ﵽ�������
	int pers=0;//��ǰ����ٷֱ�
	//��ǰ����״
	BNPolyObject* bpoCurrMain;
	//��������
	b2World* world;
	std::map<std::string,PhyObject*> pom;//�������ڴ洢����id������ָ���map
	std::map<std::string,PhyObject*> pomCircle;//�������ڴ洢����id������ָ���map
	Size visibleSize;//�ɼ�����ߴ�
	Point origin;//ԭ������

	std::string* ids;//���ڴ�id���ַ���ָ��
	float* data;//���ڴ涥������
	PhyObject* po;//�������ָ��
	std::vector<Point> circlePoint;
	Sprite* backgroundsp;//��������
	Sprite* winBgSp;//ʤ���󵯳��������
	bool isDelete=false;//�����ܷ�ɾ��
	bool isWin=false;//���ؿ��Ƿ�ʤ��
	bool phyZanTing=false;//���������Ƿ���ͣ
	bool isZanTingEnble=true;//��ͣ�˵��ܲ�����
	Sprite* buffCutSp;//ǿ���и�ħ������
	bool isBuff=false;//�Ƿ���ǿ���и�ħ��
	float tempArea;
	static int escCount;//��¼���·��ؼ�����
	bool isCutFe=false;//�ж��Ƿ��е���Ƥ
	GameSceneManager* gsm;//���������ߵ�ָ��
	WelcomeLayer* wl;//��ӭ����ָ��
	MyFCData* mfcd;//

	Sprite* toumingBgSp;//͸����������
	bool isZanting=false;//�Ƿ���ͣ�ı�־λ
	Sprite* zantingSp;//��ͣʱ������ľ��
	int cutNum=1;//��¼�и����
	Label *cutLabel;//��ʾ�и�����ǩ
	Label *timeLabel;//��ʾ����ʱ���ǩ
	Label *lastLabel;//��ʾʣ�������ǩ
	int time=0;//����ʱ��
	Menu* menu;//��ͣ�˵�ָ��

	//��������ָ��
	Animate* anmiAc;
	Sprite* sparkSp;//�𻨾������ָ��
	bool anmiPlayEnd=false;//��������ʱ�����

	Sprite* lightSp;//���⾫�����ָ��
	float angle;//�����ƫת��
	Point t;//��ǰ����λ������

	Sprite* lineSp;//�и��߾������ָ��
	Point touchS;//������ʼ��
	Point touchE;//����������

	bool isBlink=false;//�и�����˸��־λ
	bool cutLine=true;//�и����Ƿ�ɼ���trueΪ�ɼ�
	int touchID=-1;//��ǰ����id
	//��ʼ���ķ���
	virtual bool init();
	void initLevel(int levelNum);//��ʼ���ؿ�
	void initAnmi();//��ʼ�����Ż𻨶����ķ���
	void preloadAllSound();//Ԥ����������Ч
	void playsuccMusic();//���Ź�����Ч
	void playfailMusic();//����ʧ����Ч
	void playcutSound();//�����и���Ч
	void playNotCutSound();//����δ�и���Ч
	void playcutFeSound();//�����е���������Ч
	//��ͣ�˵��ص�����
    void menuZantingCallback(Object* pSender);
    void guanQia(Object* pSender);//����ؿ���Ļص�����
    void chongWan(Object* pSender);//���������Ļص�����
    void jiXu(Object* pSender);//���������Ļص�����
    void addLine(Point ps, Point pe,Sprite* edgeS);//����и��ߵķ���
    void addCutLight();//����и��Ч��
    float lengthPointToLine(float x,float y,float xs,float ys,float xm,float ym);//С���и��ߵ�֮��ľ���
    //��������ģ��
	void step();
	//��������
	void update(float delta);
	void createEdge(float* coorData,int lengthCoorData);//�����߸���ķ���
	void deleteEdge();//ɾ���߸���ķ���

	//��ʼ�����¼��Ĵ�����
	bool onMyTouchBegan(Touch *touch, Event *event);
	//�����ƶ��¼��Ĵ�����
	void onMyTouchMoved(Touch *touch, Event *event);
	//���ؽ����¼��Ĵ�����
	void onMyTouchEnded(Touch *touch, Event *event);

	void restartGame();//ʧ�����¿�ʼ��Ϸ�ķ���
	void round3SparkAnmi();//��3�ز��Ż𻨶����ķ���
	void round4SparkAnmi();//��4�ز��Ż𻨶����ķ���
	void round5SparkAnmi();//��5�ز��Ż𻨶����ķ���
	void round6SparkAnmi();//��6�ز��Ż𻨶����ķ���

	void popWinBoard();//����ʤ��ľ��ķ���
	void recordMessage();//���ؼ�¼����ʾ����Ϣ
	void xiaYiGuan(Object* pSender);//�����һ�غ�Ļص�����
	void popBuff();//������buff��������ʧ�ķ���


	void trueCut(float lxs,float lys,float lxe,float lye,IsNotCut* inc);//��ȷ�и�ķ���
//	void recordTime();//��¼ʱ��ķ���
//	void gameTimeUpdate();//������Ϸʱ��Ļص�����



    //Cocos2d-x�ж����һ���꣬����ָ�����͵Ķ���
    //��������Ӧ�ĳ�ʼ�����ͷŹ���
    CREATE_FUNC(GameLayer);
};

#endif
