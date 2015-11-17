#ifndef _Constant_H_
#define _Constant_H_

static float HEIGHT = 540.0f;
static float WIDTH = 960.0f;

static float GROUNDX=480.0f;//�������ĵ��x����
static float GROUNDY=135.0f;//�������ĵ��y����
static float LENGTHGROUND=960.0f;//����ĳ���

static float LENGTHJC=50.0f;//��Ծ�ķ��� ��һ���ߵı߳�
static float FLYLENGTHX = 65.0f;//�������ĳ�

static float JCX=GROUNDX*2*0.36f;//��Ծ���� ��x����
static float JCY=GROUNDY+LENGTHJC/2.0f;//��Ծ���� ��y����

static float JCJH=130.0f;//��Ծ����  ���ĸ߶�

static float UPPERLIMIT = 370.0f;//��Ծ����  ��Ծ������
static float LOWERLIMIT = 160.0f;//��Ծ����  ��Ծ������

static float LENGTHSJX=50.0f;//�����εĿ�
static float LENGTHSJY=50.0f;//�����εĸ�
static float SJXX=GROUNDX*2+LENGTHSJX;//�����ε�λ��x
static float SJXY=GROUNDY+LENGTHSJY/2.0f;//�����ε�λ��y

static float V = 900.0f;//�ϰ��� �ƶ����ٶ�
static float VBG = 250.0f;//�����ƶ� ���ٶ�
static float INTERVAL = 0.01f;//��ʱ�ص���ʱ����
static float INTERVALJC = 0.01f;//��ʱ�ص���ʱ����

static float timeJump = 0.13f;
static float timeDown = 0.13f;


static int PauseBGZOrder = 10;
static int BatchNodeZOrder = 8;
static int GoBackZOrder = 5;
static int BackgroundZOrder = 1;
static int GroundZOrder = 2;

static int INDEX_LEVELLAYER = 0;
static int INDEX_GRAMLAYER = 1;
static int INDEX_MENULAYER = 2;
static int INDEX_FLYLAYER = 3;
static int INDEX_CHOICECUBELAYER = 4;
static int INDEX_MUSICLAYER = 5;

static float HEIGHT_EDGE = 15.0f;

#endif
