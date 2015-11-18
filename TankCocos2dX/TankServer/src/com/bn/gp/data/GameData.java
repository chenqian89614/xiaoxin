package com.bn.gp.data;

import java.util.ArrayList;

import com.bn.gp.boss.Bossbullet;
import com.bn.gp.server.MainBullet;
import com.bn.gp.server.MainMissile;
import com.bn.gp.server.OtherBullet;

public class GameData
{
	public static Object lock=new Object();		//锁
	
	public final static float baseWidth=960;	//基础分辨率宽度
	public final static float baseHeight=540;	//基础分辨率高度

	public static float bulletSpeed=3;			//玩家子弹速度
	public static float otherbulletSpeed=2;		//敌军子弹速度
	public static int tankSpeed=10;				//坦克移动速度

	//各种物品大小
	public final static int tankSize=50;
	public final static int towerSize=110;
	public static final int bulletSize=10;
	public static final int missileSize=30;
	public static final int sideSize=30;
	public static final int barrierSize=56;
	public static final int propsSize = 40;
	public static final int bossSize=284;

	public final static int doWhat[]={0,1,2,3,2,4,3,6,9,2,2,10};				//碰撞后的物体的编号
	public final static int addSocre[]={0,0,0,0,50,50,100,100,70,70,70,70};
	//0		Tree		暗
	//1		Tree		亮
	//2		mark		小坑
	//3		mark		大坑
	//4		barrier		沙包
	//5		barrier		沙包
	//6		tower		塔
	//7		tower		塔
	//8		tank1		2血坦克1
	//9		tank2		坦克1
	//10	tank3		坦克2
	//11	tank4		2血坦克2
	
	public static int gameState=0;							//0--停止  2--游戏开始  3--游戏失败  4--游戏暂停
	public static int num=12;								//奖励的编号
	public static int awardTime=0;							//奖励出现的几率
	public static int score=0;								//得分
	public static int time=7000;							//时间进度
	public static int offset=7000;							//偏移量
	public static int level=0;								//关卡
	public static boolean threadFlag=false;					//线程标志位
	
	public static int otherState;							//敌军子弹是否处于发射状态
	public static int otherTimeCount=200;
	public static int otherTimeSpan=200;
	
	public static int bossHealth=10;
	public static boolean bossFlag=false;	
	public static int bossNum=0;			//第几个boss
	public static int bossX;
	public static int bossY;
	public static int bossDirection=2;
	public static int bossbulletSpeed=5;	
	public static int timecount=0;

	public static int redOrGreen;							//客户端标志位 0--红色坦克  1--绿色坦克
	public static int redX=310;				//红色坦克X坐标
	public static int redY=400;				//红色坦克Y坐标
	public static int greenX=620;			//绿色坦克X坐标
	public static int greenY=400;			//绿色坦克Y坐标
	public static float redTankAngle=0;		//红色坦克旋转角度
	public static float greenTankAngle=0;	//绿色坦克旋转角度
	public static float redGunAngle=0;		//红色坦克炮筒角度
	public static float greenGunAngle=0;	//绿色坦克炮筒角度
	public static int redTimeCount=20;		//红色子弹是否发射计数器
	public static int greenTimeCount=20;	//绿色子弹是否发射计数器
	public static int redTimeSpan=40;		//红色子弹发射间隔										
	public static int greenTimeSpan=40;		//绿色子弹发射间隔
	public static int redState;				//红色坦克炮筒是否处于发射状态
	public static int greenState;			//绿色坦克炮筒是否处于发射状态
	public static int redHealth=100;		//红色坦克生命值
	public static int greenHealth=100;		//绿色坦克生命值
	public static int redMissileSpan=100;	//红色导弹阀值
	public static int greenMissileSpan=100;	//绿色导弹阀值
	public static int redMissileCount=100;	//红色导弹计数器
	public static int greenMissileCount=100;//绿色导弹计数器
	public static int tankFlag[]={0,0};		//坦克是否随地图下落标志位
	
//	public static int redRank=3;			//坦克等级
//	public static int greenRank=3;
	
	public static int[] mapData=null;
	public static int[] mapTree=null;
	public static int[] mapTank=null;
		
	public static ArrayList<Integer> tempTank;												//敌方坦克 编号，坐标，角度
	public static ArrayList<Integer> mapTemp;
	public static ArrayList<Integer> explosion=new ArrayList<Integer>();					//地图临时列表
	public static ArrayList<Float> mainBullet=new ArrayList<Float>();						//玩家子弹数据列表
	public static ArrayList<Float> otherBullet=new ArrayList<Float>();						//敌方子弹数据列表
	public static ArrayList<Float> mainMissile=new ArrayList<Float>();						//玩家导弹数据列表
	public static ArrayList<Float> bossBullet=new ArrayList<Float>();						//boss子弹数据列表
	
	public static ArrayList<Bossbullet> bossBulletList=new ArrayList<Bossbullet>();				//boss的子弹
	public static ArrayList<MainBullet> mainBulletList=new ArrayList<MainBullet>(); 			//玩家子弹列表
	public static ArrayList<OtherBullet> otherBulletList=new ArrayList<OtherBullet>();			//地方子弹列表
	public static ArrayList<MainMissile> mainMissileList=new ArrayList<MainMissile>();			//玩家导弹列表
	
	public static ArrayList<Integer> mapDataTemp=new ArrayList<Integer>();					
	public static ArrayList<Integer> award=new ArrayList<Integer>();						//CHP
}