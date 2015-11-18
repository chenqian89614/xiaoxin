package com.bn.gp.data;

import java.util.ArrayList;

import com.bn.gp.boss.Bossbullet;
import com.bn.gp.server.MainBullet;
import com.bn.gp.server.MainMissile;
import com.bn.gp.server.OtherBullet;

public class GameData
{
	public static Object lock=new Object();		//��
	
	public final static float baseWidth=960;	//�����ֱ��ʿ��
	public final static float baseHeight=540;	//�����ֱ��ʸ߶�

	public static float bulletSpeed=3;			//����ӵ��ٶ�
	public static float otherbulletSpeed=2;		//�о��ӵ��ٶ�
	public static int tankSpeed=10;				//̹���ƶ��ٶ�

	//������Ʒ��С
	public final static int tankSize=50;
	public final static int towerSize=110;
	public static final int bulletSize=10;
	public static final int missileSize=30;
	public static final int sideSize=30;
	public static final int barrierSize=56;
	public static final int propsSize = 40;
	public static final int bossSize=284;

	public final static int doWhat[]={0,1,2,3,2,4,3,6,9,2,2,10};				//��ײ�������ı��
	public final static int addSocre[]={0,0,0,0,50,50,100,100,70,70,70,70};
	//0		Tree		��
	//1		Tree		��
	//2		mark		С��
	//3		mark		���
	//4		barrier		ɳ��
	//5		barrier		ɳ��
	//6		tower		��
	//7		tower		��
	//8		tank1		2Ѫ̹��1
	//9		tank2		̹��1
	//10	tank3		̹��2
	//11	tank4		2Ѫ̹��2
	
	public static int gameState=0;							//0--ֹͣ  2--��Ϸ��ʼ  3--��Ϸʧ��  4--��Ϸ��ͣ
	public static int num=12;								//�����ı��
	public static int awardTime=0;							//�������ֵļ���
	public static int score=0;								//�÷�
	public static int time=7000;							//ʱ�����
	public static int offset=7000;							//ƫ����
	public static int level=0;								//�ؿ�
	public static boolean threadFlag=false;					//�̱߳�־λ
	
	public static int otherState;							//�о��ӵ��Ƿ��ڷ���״̬
	public static int otherTimeCount=200;
	public static int otherTimeSpan=200;
	
	public static int bossHealth=10;
	public static boolean bossFlag=false;	
	public static int bossNum=0;			//�ڼ���boss
	public static int bossX;
	public static int bossY;
	public static int bossDirection=2;
	public static int bossbulletSpeed=5;	
	public static int timecount=0;

	public static int redOrGreen;							//�ͻ��˱�־λ 0--��ɫ̹��  1--��ɫ̹��
	public static int redX=310;				//��ɫ̹��X����
	public static int redY=400;				//��ɫ̹��Y����
	public static int greenX=620;			//��ɫ̹��X����
	public static int greenY=400;			//��ɫ̹��Y����
	public static float redTankAngle=0;		//��ɫ̹����ת�Ƕ�
	public static float greenTankAngle=0;	//��ɫ̹����ת�Ƕ�
	public static float redGunAngle=0;		//��ɫ̹����Ͳ�Ƕ�
	public static float greenGunAngle=0;	//��ɫ̹����Ͳ�Ƕ�
	public static int redTimeCount=20;		//��ɫ�ӵ��Ƿ��������
	public static int greenTimeCount=20;	//��ɫ�ӵ��Ƿ��������
	public static int redTimeSpan=40;		//��ɫ�ӵ�������										
	public static int greenTimeSpan=40;		//��ɫ�ӵ�������
	public static int redState;				//��ɫ̹����Ͳ�Ƿ��ڷ���״̬
	public static int greenState;			//��ɫ̹����Ͳ�Ƿ��ڷ���״̬
	public static int redHealth=100;		//��ɫ̹������ֵ
	public static int greenHealth=100;		//��ɫ̹������ֵ
	public static int redMissileSpan=100;	//��ɫ������ֵ
	public static int greenMissileSpan=100;	//��ɫ������ֵ
	public static int redMissileCount=100;	//��ɫ����������
	public static int greenMissileCount=100;//��ɫ����������
	public static int tankFlag[]={0,0};		//̹���Ƿ����ͼ�����־λ
	
//	public static int redRank=3;			//̹�˵ȼ�
//	public static int greenRank=3;
	
	public static int[] mapData=null;
	public static int[] mapTree=null;
	public static int[] mapTank=null;
		
	public static ArrayList<Integer> tempTank;												//�з�̹�� ��ţ����꣬�Ƕ�
	public static ArrayList<Integer> mapTemp;
	public static ArrayList<Integer> explosion=new ArrayList<Integer>();					//��ͼ��ʱ�б�
	public static ArrayList<Float> mainBullet=new ArrayList<Float>();						//����ӵ������б�
	public static ArrayList<Float> otherBullet=new ArrayList<Float>();						//�з��ӵ������б�
	public static ArrayList<Float> mainMissile=new ArrayList<Float>();						//��ҵ��������б�
	public static ArrayList<Float> bossBullet=new ArrayList<Float>();						//boss�ӵ������б�
	
	public static ArrayList<Bossbullet> bossBulletList=new ArrayList<Bossbullet>();				//boss���ӵ�
	public static ArrayList<MainBullet> mainBulletList=new ArrayList<MainBullet>(); 			//����ӵ��б�
	public static ArrayList<OtherBullet> otherBulletList=new ArrayList<OtherBullet>();			//�ط��ӵ��б�
	public static ArrayList<MainMissile> mainMissileList=new ArrayList<MainMissile>();			//��ҵ����б�
	
	public static ArrayList<Integer> mapDataTemp=new ArrayList<Integer>();					
	public static ArrayList<Integer> award=new ArrayList<Integer>();						//CHP
}