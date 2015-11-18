package com.bn.gp.server;

import com.bn.gp.data.GameData;
import com.bn.gp.data.LevelData;

public class LevelChange
{
	public static boolean changeLevel()
	{
		int level;
		boolean flag=false;
		synchronized(GameData.lock)
		{
			level=GameData.level;
			GameData.bossBulletList.clear();
		}
		if(level<LevelData.mapData.length)
		{
			int tempData[]=new int[LevelData.mapData[level].length];
			int tempTank[]=new int[LevelData.mapTank[level].length];
			int tempTree[]=new int[LevelData.mapTree[level].length];
			System.arraycopy(LevelData.mapData[level], 0, tempData, 0, LevelData.mapData[level].length);
			System.arraycopy(LevelData.mapTank[level], 0, tempTank, 0, LevelData.mapTank[level].length);
			System.arraycopy(LevelData.mapTree[level], 0, tempTree, 0, LevelData.mapTree[level].length);
			synchronized(GameData.lock)
			{
				GameData.mapData=tempData;
				GameData.mapTank=tempTank;
				GameData.mapTree=tempTree;
				GameData.bossHealth=LevelData.bossHealth[level];
				GameData.time=0;
				GameData.offset=0;
				GameData.level++;
				GameData.bossNum=GameData.level;
			}
			flag=true;
		}
		return flag;
	}
	
	public static void resetLevel()
	{
		synchronized(GameData.lock)
		{
			GameData.gameState=0;
			GameData.threadFlag=false;
			GameData.mapData=null;
			GameData.mapTank=null;
			GameData.mapTree=null;
			GameData.score=0;
			GameData.bossHealth=0;
			GameData.time=0;
			GameData.offset=0;
			GameData.level=0;
			GameData.bossNum=0;
			GameData.bossFlag=false;
			GameData.redX=310;				//��ɫ̹��X����
			GameData.redY=400;				//��ɫ̹��Y����
			GameData.greenX=620;			//��ɫ̹��X����
			GameData.greenY=400;			//��ɫ̹��Y����
			GameData.redTankAngle=0;		//��ɫ̹����ת�Ƕ�
			GameData.greenTankAngle=0;		//��ɫ̹����ת�Ƕ�
			GameData.redGunAngle=0;			//��ɫ̹����Ͳ�Ƕ�
			GameData.greenGunAngle=0;		//��ɫ̹����Ͳ�Ƕ�
			GameData.redHealth=100;			//��ɫ̹������ֵ
			GameData.greenHealth=100;		//��ɫ̹������ֵ
			GameData.redTimeCount=20;		//��ɫ�ӵ��Ƿ��������
			GameData.greenTimeCount=20;		//��ɫ�ӵ��Ƿ��������
			GameData.redTimeSpan=40;		//��ɫ�ӵ�������										
			GameData.greenTimeSpan=40;		//��ɫ�ӵ�������
		}
	}
}