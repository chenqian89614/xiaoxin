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
	Label *label;//目标面积标签
	Label *labelLast;//剩余面积百分比标签
	//切割线的起点终点坐标
	float lxs;
	float lys;
	float lxe;
	float lye;
	//原始的面积
	float areaInit;
	float areaCurr;//当前剩下的面积
	float winArea;//胜利所达到最大的面积
	int pers=0;//当前面积百分比
	//当前的形状
	BNPolyObject* bpoCurrMain;
	//物理世界
	b2World* world;
	std::map<std::string,PhyObject*> pom;//声明用于存储物体id和物体指针的map
	std::map<std::string,PhyObject*> pomCircle;//声明用于存储物体id和物体指针的map
	Size visibleSize;//可见区域尺寸
	Point origin;//原点坐标

	std::string* ids;//用于存id的字符串指针
	float* data;//用于存顶点数据
	PhyObject* po;//物体类的指针
	std::vector<Point> circlePoint;
	Sprite* backgroundsp;//背景精灵
	Sprite* winBgSp;//胜利后弹出结果精灵
	bool isDelete=false;//刚体能否删除
	bool isWin=false;//本关卡是否胜利
	bool phyZanTing=false;//物理世界是否暂停
	bool isZanTingEnble=true;//暂停菜单能不能用
	Sprite* buffCutSp;//强力切割魔法精灵
	bool isBuff=false;//是否有强力切割魔法
	float tempArea;
	static int escCount;//记录按下返回键次数
	bool isCutFe=false;//判断是否切到铁皮
	GameSceneManager* gsm;//场景管理者的指针
	WelcomeLayer* wl;//欢迎布景指针
	MyFCData* mfcd;//

	Sprite* toumingBgSp;//透明背景精灵
	bool isZanting=false;//是否暂停的标志位
	Sprite* zantingSp;//暂停时弹出的木板
	int cutNum=1;//记录切割次数
	Label *cutLabel;//显示切割数标签
	Label *timeLabel;//显示所用时间标签
	Label *lastLabel;//显示剩余面积标签
	int time=0;//所用时间
	Menu* menu;//暂停菜单指针

	//动画动作指针
	Animate* anmiAc;
	Sprite* sparkSp;//火花精灵对象指针
	bool anmiPlayEnd=false;//动画播放时候结束

	Sprite* lightSp;//刀光精灵对象指针
	float angle;//刀光的偏转角
	Point t;//当前触摸位置坐标

	Sprite* lineSp;//切割线精灵对象指针
	Point touchS;//触摸开始点
	Point touchE;//触摸结束点

	bool isBlink=false;//切割线闪烁标志位
	bool cutLine=true;//切割线是否可见，true为可见
	int touchID=-1;//当前触摸id
	//初始化的方法
	virtual bool init();
	void initLevel(int levelNum);//初始化关卡
	void initAnmi();//初始化播放火花动画的方法
	void preloadAllSound();//预加载所有音效
	void playsuccMusic();//播放过关音效
	void playfailMusic();//播放失败音效
	void playcutSound();//播放切割音效
	void playNotCutSound();//播放未切割音效
	void playcutFeSound();//播放切到金属的音效
	//暂停菜单回调方法
    void menuZantingCallback(Object* pSender);
    void guanQia(Object* pSender);//点击关卡后的回调方法
    void chongWan(Object* pSender);//点击重来后的回调方法
    void jiXu(Object* pSender);//点击继续后的回调方法
    void addLine(Point ps, Point pe,Sprite* edgeS);//添加切割线的方法
    void addCutLight();//添加切割刀光效果
    float lengthPointToLine(float x,float y,float xs,float ys,float xm,float ym);//小球到切割线的之间的距离
    //物理世界模拟
	void step();
	//更新数据
	void update(float delta);
	void createEdge(float* coorData,int lengthCoorData);//创建边刚体的方法
	void deleteEdge();//删除边刚体的方法

	//开始触控事件的处理方法
	bool onMyTouchBegan(Touch *touch, Event *event);
	//触控移动事件的处理方法
	void onMyTouchMoved(Touch *touch, Event *event);
	//触控结束事件的处理方法
	void onMyTouchEnded(Touch *touch, Event *event);

	void restartGame();//失败重新开始游戏的方法
	void round3SparkAnmi();//第3关播放火花动画的方法
	void round4SparkAnmi();//第4关播放火花动画的方法
	void round5SparkAnmi();//第5关播放火花动画的方法
	void round6SparkAnmi();//第6关播放火花动画的方法

	void popWinBoard();//弹出胜利木板的方法
	void recordMessage();//过关记录牌显示的信息
	void xiaYiGuan(Object* pSender);//点击下一关后的回调方法
	void popBuff();//关于铁buff弹出和消失的方法


	void trueCut(float lxs,float lys,float lxe,float lye,IsNotCut* inc);//正确切割的方法
//	void recordTime();//记录时间的方法
//	void gameTimeUpdate();//更新游戏时间的回调方法



    //Cocos2d-x中定义的一个宏，创建指定类型的对象
    //并做好相应的初始化与释放工作
    CREATE_FUNC(GameLayer);
};

#endif
