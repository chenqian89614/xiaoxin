#ifndef _Constant_H_
#define _Constant_H_
#include "cocos2d.h"
using namespace cocos2d;
class Constant{
public:
	static int playerCount;//������Ϸ��Ҹ���
	static int playerId;//��ǰ��ҵ�id
	static int lastPlayerId;
	static int nextPlayerId;
	//===================׼��===============
	static int playerReady;
	static int lastPlayerReady;
	static int nextPlayerReady;
	static int readyNum;//��׼����Ҹ���
	//============��
	static int pukeRemainNumber;		//ʣ���˿˵�����
	static int PUKEARRAY[20];
	static int tempPUKE[20];
	static int lastPukeId[3];//ʣ���Ƶ�id����ʣ���������
	static int landlordList[3];//ÿ����ҽе�����״̬�����ζ�Ӧ���0��1��2
	static int playerCards[20];
	static int lastPlayerCards[20];
	static int nextPlayerCards[20];
	static int EFFECT_ROW_COL[4][15];//��Ч����
	static int upCards[54];
	static int tishiCard[20];

	//�����˿˱�־λ��0����δ���գ�1����������
	static bool pukeFlag;//�˿˱�־λ�������жϷ����Ƿ����
	static bool readyFlag;//�������÷��ƺ�ok������ʧ
	static bool landlordHadPuke;//�����Ѿ��õ�20����
	static bool effectFlag;//��Ч��־λ
	static bool musicFlag;//���ֱ�־λ
	static bool isDrawChuPai;//���Ƴ��Ʋ˵����־λ
	static bool clearLandlordState;//�����������������״̬

	static int landLordFlag;//���λ��
	static int whoFlag;//������־λ����ʼ�е��������
	static int whoIsLandlord;//�ж�˭�ǵ���
	//static int playerCardsNum;//��ǰ���������Ŀ
	static int landlordCount;//��/����������������
	static int oldGoldFlag;//�ɵĽ�ұ��
	static int pukeNumber;//�˿���Ŀ
	static int beiNum;//���յ�ǰ����
	static int oldBeiNum;//��һ�α���

	static int landlordListNum;//���ڽ���3�����������ǰ��״̬

	static int soundType;//����������
	static int playerCardsCount;//��ǰ���������Ŀ��id=0;
	static int lastPlayerCardsCount;//��һ���������Ŀ��id=2;
	static int nextPlayerCardsCount;//��һ���������Ŀ��id=1;
	static int upCardsCount;//�����Ƶ���Ŀ
	static int isCanChuPai;//�Ƿ���Գ���,0-���ܳ���1-���Գ���2-����
	static int drawCardsFlag;//����������Ƶı�־λ
	static int isBuChu;//���ڻ��ơ��������ı�־λ
	static bool isDrawReset;//������ѡ���жϱ�־
	static bool drawCards; 	//�������� ���»�һ���Լ�����
	static bool drawAlreadyCard;//���ѳ�����
	//ÿ����ҳ��Ƶ���Ŀ
	static int playerLength;//���0
	static int lastPlayerLength;//���1
	static int nextPlayerLength;//���2
	//��־λ
	static bool playerCardDraw;
	static bool lastPlayerCardDraw;
	static bool nextPlayerCardDraw;

	//ɾ���е������������Ĳ˵�
	static bool deleteMenu;
	//��������ũ��ͷ��
	static bool drawHeadImage;
	//menuitem
	static bool menuItem;
	//�Ƿ������
	static bool drawLogo;
	//����ʾ
	static bool drawTiShi;
	//���ų�����Ч
	static bool isCanPlayEffect;
	static int effectRow;//������
	static int effectCol;//������
	//�Ƿ���ʾ
	static bool isTishi;
	//ʤ��
	static bool drawVictory;
	//��˭Ӯ��
	static int victory;
    static bool drawAct;
};
#endif
