#include "Constant.h"
#include "AppMacros.h"

int Constant::playerCount=0;//������Ϸ�������Ŀ
//���ID
int Constant::playerId=-1;//��ǰ���id
int Constant::lastPlayerId=-1;//��һ��id
int Constant::nextPlayerId=-1;//��һ��id
//���׼��0��ʾû��׼��1��ʾ��׼��
int Constant::playerReady=0;//��ǰ���׼��
int Constant::lastPlayerReady=0;//��һ���׼��
int Constant::nextPlayerReady=0;//��һ���׼��
int Constant::readyNum=0;//׼�������Ŀ
//===========��ʼ����������
int Constant::pukeRemainNumber;	//ʣ������
int Constant::upCards[54];//����ÿ���Ƶı��
int Constant::tishiCard[20];
int	Constant::PUKEARRAY[20]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
								-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int	Constant::tempPUKE[20]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
								-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int Constant::lastPukeId[3]={-1,-1,-1};			//���Ƶ�ID
int Constant::landlordList[3]={-1,-1,-1};		//ÿ����ҽе�����״̬�����ζ�Ӧ���0��1��2
//���ڽ���ÿ����ҳ��Ƶ�����
int	Constant::playerCards[20]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
								-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int	Constant::lastPlayerCards[20]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
								-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int	Constant::nextPlayerCards[20]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
								-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

int Constant::EFFECT_ROW_COL[4][15]={
										{DAN_1,DAN_2,DAN_3,DAN_4,DAN_5,DAN_6,DAN_7,DAN_8,DAN_9,DAN_10,DAN_11,DAN_12,DAN_13,DAN_14,DAN_15},
										{DUI_1,DUI_2,DUI_3,DUI_4,DUI_5,DUI_6,DUI_7,DUI_8,DUI_9,DUI_10,DUI_11,DUI_12,DUI_13,-1,-1},
										{SAN_1,SAN_2,SAN_3,SAN_4,SAN_5,SAN_6,SAN_7,SAN_8,SAN_9,SAN_10,SAN_11,SAN_12,SAN_13,-1,-1},
										{FEI_JI,LIAN_DUI,SAN_DAI_YI,SAN_DAI_DUI,SHUN_ZI,SI_DAI_ER,SI_DAI_DUI,WANG_ZHA,ZHA_DAN,BU_YAO,-1,-1,-1,-1,-1}
									};

bool Constant::pukeFlag = false;//�˿˱�־λ�������ж��Ƿ��Ʒ���
bool Constant::readyFlag = false;//�������÷��ƺ�ok������ʧ
bool Constant::landlordHadPuke = false;//�����Ѿ��õ�20����
bool Constant::clearLandlordState = false;//���������������
bool Constant::effectFlag = true;//��Ч��־λ
bool Constant::musicFlag = true;//���ֱ�־λ	��������
bool Constant::isDrawChuPai = false;//���Ƴ��Ʋ˵����־λ,�����Գ���ʱ����Ϊtrue
bool Constant::isDrawReset = false;//������ѡ���жϱ�־
bool Constant::isCanPlayEffect = false;//Ĭ�ϲ����Բ��ų�����Ч

int Constant::whoFlag = -1;//��ʼ�е��������,����ǰ�����Ȩ
int Constant::whoIsLandlord = -1;//�ж�˭�����ĵ���
int Constant::landlordCount = 0;//����������
int Constant::oldGoldFlag = -1;//��¼ÿ�ν��ı��
int Constant::pukeNumber = 0;//�˿���Ŀ
int Constant::beiNum = 15;//��ǰ����,Ĭ��Ϊ15��
int Constant::oldBeiNum = 15;//��һ�εı���

int Constant::landlordListNum = -1;//���ڽ���3�����������ǰ��״̬
int Constant::soundType = -1;//���������ͣ�������������Ч
//�������������Ŀ
int Constant::playerCardsCount = 17;//��ǰ���������Ŀ��id=0;
int Constant::lastPlayerCardsCount = 17;//��һ���������Ŀ��id=2;
int Constant::nextPlayerCardsCount = 17;//��һ���������Ŀ��id=1;
int Constant::upCardsCount = 0;//��ǰ����Ȩ����ҵ����Ƶ���Ŀ

int Constant::isCanChuPai = 0;//�Ƿ���Գ���,0-���ܳ���1-���Գ���
int Constant::drawCardsFlag = 0;//����������Ƶı�־λ,0-�����ƣ�1-����
bool Constant::drawCards=false;	//���»�һ����
bool Constant::drawAlreadyCard=false;//���ѳ�����
int Constant::isBuChu = 0;//���ڻ��ơ��������ı�־λ,0-���ƣ�1-������

//ÿ����ҵĳ�����Ŀ 0  1  2
int Constant::playerLength = 0;
int Constant::lastPlayerLength = 0;
int Constant::nextPlayerLength = 0;
//��־λ  �Ƿ��ѳ�����
bool Constant::playerCardDraw=true;
bool Constant::lastPlayerCardDraw=true;
bool Constant::nextPlayerCardDraw=true;
//ɾ���е�����������menu
bool Constant::deleteMenu=false;
bool Constant::menuItem=false;
//������ͷ��ũ��ͷ��
bool Constant::drawHeadImage=false;
//������logo
bool Constant::drawLogo=true;
//����ʾ
bool Constant::drawTiShi=false;
//�Ƿ���ʾ
bool Constant::isTishi=true;
//������Ч���������
int Constant::effectRow = -1;
int Constant::effectCol = -1;
//ʤ����־λ
bool Constant::drawVictory=false;
//�����˭Ӯ��
int Constant::victory=-1;
bool Constant::drawAct=false;
