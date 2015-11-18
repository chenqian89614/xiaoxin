package com.bn.gp.server;

import java.util.ArrayList;

import com.bn.gp.data.GameData;

public class Collision
{
	final static int redWhich[]={GameData.tankSize,GameData.bulletSize,GameData.missileSize};									//ײ������İ�߳�		
	final static int greenWhich[]={GameData.tankSize,GameData.barrierSize,GameData.barrierSize,				//��ײ������İ�߳�
									GameData.towerSize,GameData.towerSize,GameData.tankSize,
									GameData.tankSize,GameData.tankSize,GameData.tankSize,
									GameData.propsSize,GameData.bossSize};
	//0		Tree		��
	//1		Tree		��
	//2		mark		С��
	//3		mark		���
	//4		barrier		ɳ��
	//5		barrier		ɳ��
	//6		tower		��     
	//7		tower		��
	//8		tank1		2Ѫ̹��1
	//9		tank2		̹��1=
	//10	tank3		̹��2
	//11	tank4		2Ѫ̹��2
	
	/**
	 * ������������Ƿ�����ײ
	 */
	public static boolean checkCollision(int redX,int redY,int greenX,
			int greenY,float redAngle,float greenAngle,int whichA, int whichB)
	{
		//��ʼ�����ڼ���ı���
		redAngle=450-redAngle;
		greenAngle=450-greenAngle;
		double redRadian=Math.toRadians(redAngle);
		double greenRadian=Math.toRadians(greenAngle);
		int dx1=redX-greenX;
		int dy1=redY-greenY;
		int redSide=redWhich[whichA]/2;						
		int greenSide=greenWhich[whichB]/2;
		
		if((dx1*dx1+dy1*dy1)>(redSide+greenSide)*(redSide+greenSide)*2)						//�������е�֮�����������������Բ
		{
			return false;
		}
		if((dx1*dx1+dy1*dy1)<(redSide-greenSide)*(redSide-greenSide))						//�������е�֮�����С���������ڽ�Բ
		{
			return true;
		}
		else
		{
			float redPoint[][]=getPoint(redX, redY, redRadian, redSide);					//����ײ������4������
			float greenPoint[][]=getPoint(greenX, greenY, greenRadian, greenSide);			//���㱻ײ������4������
			
			for(int i=0;i<4;i++)
			{
				for(int j=0;j<4;j++)
				{
					if(checkIntersect(redPoint[i],greenPoint[j],redPoint[i+1],greenPoint[j+1]))
					{
						if(checkIntersect(greenPoint[j],redPoint[i],greenPoint[j+1],redPoint[i+1]))
						{
							return true;
						}
					}
				}
			}
			return false;
		}
	}
	
	/**
	 * �ط��ӵ������̹����ײ���
	 */
	public static boolean checkCollision(int sort,int bulletX,int bulletY)
	{
		int redX,redY,greenX,greenY,redHealth,greenHealth;
		float redAngle,greenAngle;
		synchronized(GameData.lock)
		{
			redX=GameData.redX;
			redY=GameData.redY;
			greenX=GameData.greenX;
			greenY=GameData.greenY;
			redAngle=GameData.redTankAngle;
			greenAngle=GameData.greenTankAngle;
			redHealth=GameData.redHealth;
			greenHealth=GameData.greenHealth;
		}
		if(checkCollision(bulletX,bulletY,redX,redY,0,redAngle,1,0))
		{
			int hurt=0;
			if(sort==1)
			{
				hurt=8;
			}else if(sort==0)
			{
				hurt=5;
			}else if(sort==2)
			{
				hurt=10;
			}
			redHealth=(redHealth-hurt>0)?(redHealth-hurt):0;
			if(redHealth==0)
			{
				synchronized(GameData.lock)
				{
					GameData.redX=-1000;
					GameData.redY=-1000;
				}
			}
			synchronized(GameData.lock)
			{
				GameData.redHealth=redHealth;
				GameData.explosion.add(25);
				GameData.explosion.add(bulletX);
				GameData.explosion.add(bulletY);
			}
			return true;
		}
		if(checkCollision(bulletX,bulletY,greenX,greenY,0,greenAngle,1,0))
		{
			int hurt=0;
			if(sort==2)
			{
				hurt=10;
			}else if(sort==1)
			{
				hurt=8;
			}else if(sort==0)
			{
				hurt=5;
			}
			greenHealth=(greenHealth-hurt>0)?(greenHealth-hurt):0;
			if(greenHealth==0)
			{
				synchronized(GameData.lock)
				{
					GameData.greenX=-1000;
					GameData.greenY=-1000;
				}
			}
			synchronized(GameData.lock)
			{
				GameData.greenHealth=greenHealth;
				GameData.explosion.add(25);
				GameData.explosion.add(bulletX);
				GameData.explosion.add(bulletY);
			}
			return true;
		}
		return false;
	}

	
	private static float[][] getPoint(int X, int Y, double Radian, int Side) 				//�������ĵ����ꡢ��ת�Ƕȡ���߳����ȼ���4������
	{
		float Point[][]=new float[5][2];
		double pointRadian=Math.PI/4;
		double redR=Side/Math.sin(pointRadian);
		Point[0][0]=(float) (redR*Math.cos(pointRadian+Radian)+X);
		Point[0][1]=(float) (-redR*Math.sin(pointRadian+Radian)+Y);
		Point[1][0]=(float) (redR*Math.cos(Math.PI-pointRadian+Radian)+X);
		Point[1][1]=(float) (-redR*Math.sin(Math.PI-pointRadian+Radian)+Y);
		Point[2][0]=2*X-Point[0][0];
		Point[2][1]=2*Y-Point[0][1];
		Point[3][0]=2*X-Point[1][0];
		Point[3][1]=2*Y-Point[1][1];
		Point[4]=Point[0];																	//5�ŵ���1�ŵ���ͬ
		return Point;
	}
	
	private static boolean checkIntersect(float[] s1, float[] p1, float[] s2, float[] p2)	//���p1��p2�Ƿ���s1s2��ȷ��ֱ�ߵ�����
	{
		float s1x=p1[0]-s1[0];
		float s1y=p1[1]-s1[1];
		float s2x=s2[0]-s1[0];
		float s2y=s2[1]-s1[1];
		float s3x=p2[0]-s1[0];
		float s3y=p2[1]-s1[1];
		float c1=s1x*s2y-s2x*s1y;
		float c2=s2x*s3y-s3x*s2y;
		if(c1*c2>0)
		{
			return true;
		}
		return false;
	}
	/**
	 * ��������Ƿ������������е�һ��������ײ
	 */
	public static boolean checkCollision(int redX,int redY,float redAngle,int which)				
	{
		ArrayList<Integer> alTemp = new ArrayList<Integer>();
		ArrayList<Integer> alTemp2 = new ArrayList<Integer>();
		int offset;
		synchronized(GameData.lock)															//????????????????
		{
			offset=GameData.offset;															//��ȡ��ͼƫ����
			alTemp=DataUtil.arrayToList(GameData.mapData);									//��ȡ��ͼ����
			alTemp2=DataUtil.arrayToList(GameData.mapTank);									//��ȡ��ͼ̹������
		}
		return check(redX, redY, redAngle, which, alTemp, offset, 0)||check(redX, redY, redAngle, which, alTemp2, offset, 1);//������Ƿ���ײ
	}

	private static boolean check(int redX, int redY, float redAngle,						//�ж��Ƿ���ײ
			int which, ArrayList<Integer> alTemp, int offset, int flag){
		int count=0;
		while(count<alTemp.size())															//�����������ݼ���
		{
			int checkFlag=alTemp.get(count++);
			if(checkFlag>3)																	//�����Ŵ���3�Żᷢ����ײ
			{
				int greenX=alTemp.get(count++);												//��ȡ���嵱ǰXֵ
				int greenY=alTemp.get(count++)+offset;										//��ȡ���嵱ǰYֵ
				if(Math.abs(redX-greenX)<80 && Math.abs(redY-greenY)<80)					//����֮�����С����ֵ80�ż�⡢���ټ�����
				{
					if(checkCollision(redX, redY, greenX, greenY, redAngle, 0, which, checkFlag-3))	//which��ǰ��̹��0���ӵ�1��
					{
						int addScore=GameData.addSocre[checkFlag];
						checkFlag=GameData.doWhat[checkFlag];								//���ȷ�����屻ײ�������̬
						if(which==0)
						{
							do
							{
								addScore+=GameData.addSocre[checkFlag];
								checkFlag=GameData.doWhat[checkFlag];
							}while(checkFlag!=GameData.doWhat[checkFlag]);					//���ײ����Ϊ̹�ˣ���ײ����ֱ�ӱ�Ϊ������̬
							
							alTemp.set(count-3, checkFlag);
							synchronized(GameData.lock)
							{
								if(flag==0)
								{
									GameData.mapData=DataUtil.listToArray(alTemp);
								}else if(flag==1)
								{
									GameData.mapTank=DataUtil.listToArray(alTemp);
								}
								GameData.score+=addScore;
								GameData.explosion.add(0);
								GameData.explosion.add(greenX);
								GameData.explosion.add(greenY);
							}
							award(greenX,greenY);										//��ӵ������б���
						}
						else if(checkFlag==2||checkFlag==3)								//�����ײ����ٻ�������Ʊ�ײ�����ը
						{
							alTemp.set(count-3,checkFlag);
							synchronized(GameData.lock)
							{
								if(flag==0)
								{
									GameData.mapData=DataUtil.listToArray(alTemp);
								}else if(flag==1)
								{
									GameData.mapTank=DataUtil.listToArray(alTemp);
								}
								GameData.score+=addScore;
								GameData.explosion.add(0);
								GameData.explosion.add(greenX);
								GameData.explosion.add(greenY);
							}
							award(greenX,greenY);										//��ӵ������б���
						}
						else															//�����ײ����δ�٣�������ӵ�С��ը
						{
							alTemp.set(count-3,checkFlag);
							synchronized(GameData.lock)
							{
								if(flag==0)
								{
									GameData.mapData=DataUtil.listToArray(alTemp);
								}else if(flag==1)
								{
									GameData.mapTank=DataUtil.listToArray(alTemp);
								}
								GameData.score+=addScore;
								GameData.explosion.add(25);
								GameData.explosion.add(redX);
								GameData.explosion.add(redY);
							}
						}
						return true;
					}
				}
			}
			else
			{
				count+=2;
			}
		}
		return false;
	}
	
	public static void award(int redX,int redY)
	{
		int awardTime;
		synchronized(GameData.lock)
		{
			awardTime=GameData.awardTime++;
		}
		
		if(awardTime%3==0)												//ÿ5�α�ը���ֽ���
		{
			GameData.award.add((int)(Math.random()*3)+12);
			GameData.award.add(redX);									//��ӽ�������ʱ�б�                                          ////////////////
			GameData.award.add(redY);

		}
	}
//	public static void main(String []arg0)
//	{
//		for(int i=0;i<70;i++)
//		{
//			System.out.println(checkRange(i,55,1,1)+""+i);
//		}
//	}
}