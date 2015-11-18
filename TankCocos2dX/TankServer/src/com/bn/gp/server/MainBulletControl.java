package com.bn.gp.server;

import java.util.ArrayList;

import com.bn.gp.action.Action;
import com.bn.gp.data.GameData;

public class MainBulletControl extends Action
{
	@Override
	public void doAction() 
	{
		createBullet();													//�������ӵ�
		ArrayList<MainBullet> alTemp;
		ArrayList<MainBullet> alDel=new ArrayList<MainBullet>();
		ArrayList<Float> mainbullet=new ArrayList<Float>();
		synchronized(GameData.lock)
		{
			alTemp=new ArrayList<MainBullet>(GameData.mainBulletList);
		}
		for(MainBullet mb:alTemp)										//���������ӵ�		
		{
			mb.go();													//��ÿ���ӵ������Լ��ķ���ǰ��
			if(GameData.bossFlag)
			{
				int bossX,bossY;
				synchronized(GameData.lock)
				{
					bossX=GameData.bossX;
					bossY=GameData.bossY;
				}
				if(Collision.checkCollision((int)mb.bulletX, (int)mb.bulletY, bossX, bossY, 0, 0, 1, 10))
				{
					synchronized(GameData.lock)
					{
						GameData.bossHealth--;
						GameData.explosion.add(25);
						GameData.explosion.add((int)mb.bulletX);
						GameData.explosion.add((int)mb.bulletY);
					}
					alDel.add(mb);
					continue;
				}
			}
			if(mb.bulletX<0||mb.bulletX>GameData.baseWidth||mb.bulletY<0||mb.bulletY>GameData.baseHeight)	//������ͼ���ӵ����������б�
			{
				alDel.add(mb);
			}
			else if(Collision.checkCollision((int)mb.bulletX, (int)mb.bulletY, 0, 1))						//��ײ����������ӵ����������б�
			{
				alDel.add(mb);
			}
			else																							//�ϸ��ӵ��������б�ȴ����ͺͱ���
			{
				mainbullet.add(mb.bulletX);
				mainbullet.add(mb.bulletY);
			}
		}
		synchronized(GameData.lock)
		{
			GameData.mainBullet=mainbullet;
			for(MainBullet mb:alDel)
			{
				GameData.mainBulletList.remove(mb);								//�������ӵ�����
			}
		}
		ServerAgent.broadcastBullet();																		//�����ӵ�����
		
	}

	private void createBullet() {
		int redState,greenState,redTimeCount,greenTimeCount;
		int redTimeSpan,greenTimeSpan,redHealth,greenHealth;
		//��ȡ����
		synchronized(GameData.lock)
		{
			redState=GameData.redState;
			greenState=GameData.greenState;
			redTimeCount=GameData.redTimeCount;
			greenTimeCount=GameData.greenTimeCount;
			redTimeSpan=GameData.redTimeSpan;
			greenTimeSpan=GameData.greenTimeSpan;
			redHealth=GameData.redHealth;
			greenHealth=GameData.greenHealth;
		}
		//�ж��Ƿ���Ҫ������ɫ̹���ӵ�
		redState=(redState==0)?0:(redState-1);
		if(redTimeCount==redTimeSpan&&redHealth>0)
		{
			redTimeCount=0;
			redState=5;
			MainBullet temp=new MainBullet(GameData.redX,GameData.redY,GameData.redGunAngle);
			synchronized(GameData.lock)
			{
				GameData.mainBulletList.add(temp);
			}
		}
		redTimeCount++;
		//�ж��Ƿ���Ҫ������ɫ̹���ӵ�
		greenState=(greenState==0)?0:(greenState-1);
		if(greenTimeCount==greenTimeSpan&&greenHealth>0)
		{
			greenTimeCount=0;
			greenState=5;
			MainBullet temp=new MainBullet(GameData.greenX,GameData.greenY,GameData.greenGunAngle);
			synchronized(GameData.lock)
			{
				GameData.mainBulletList.add(temp);
			}
		}
		greenTimeCount++;
	//	System.out.println("timecount	"+greenTimeCount+"   timespan  "+greenTimeSpan+"	greenstate  "+greenState);
		//��������
		synchronized(GameData.lock)
		{
			GameData.redState=redState;
			GameData.greenState=greenState;
			GameData.redTimeCount=redTimeCount;
			GameData.greenTimeCount=greenTimeCount;
		}
	}
}