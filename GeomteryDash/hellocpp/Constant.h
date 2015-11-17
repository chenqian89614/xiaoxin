#ifndef _Constant_H_
#define _Constant_H_

static float HEIGHT = 540.0f;
static float WIDTH = 960.0f;

static float GROUNDX=480.0f;//地面中心点的x坐标
static float GROUNDY=135.0f;//地面中心点的y坐标
static float LENGTHGROUND=960.0f;//地面的长度

static float LENGTHJC=50.0f;//跳跃的方块 的一个边的边长
static float FLYLENGTHX = 65.0f;//飞行器的长

static float JCX=GROUNDX*2*0.36f;//跳跃方块 的x坐标
static float JCY=GROUNDY+LENGTHJC/2.0f;//跳跃方块 的y坐标

static float JCJH=130.0f;//跳跃方块  跳的高度

static float UPPERLIMIT = 370.0f;//跳跃方块  跳跃的上限
static float LOWERLIMIT = 160.0f;//跳跃方块  跳跃的下限

static float LENGTHSJX=50.0f;//三角形的宽
static float LENGTHSJY=50.0f;//三角形的高
static float SJXX=GROUNDX*2+LENGTHSJX;//三角形的位置x
static float SJXY=GROUNDY+LENGTHSJY/2.0f;//三角形的位置y

static float V = 900.0f;//障碍物 移动的速度
static float VBG = 250.0f;//背景移动 的速度
static float INTERVAL = 0.01f;//定时回调的时间间隔
static float INTERVALJC = 0.01f;//定时回调的时间间隔

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
