package com.bn.gp.server;

import java.util.ArrayList;

import com.bn.gp.action.Action;
import com.bn.gp.data.GameData;

public class Explosion extends Action									
{
	int step=2;
	int Astep=4;
	@Override
	public void doAction() 													//��ⱬը�Ƿ��ѽ�����û�������ϰɡ�ƫ����
	{
		int screen_height;
		int tempAll[];
		int tempAward[];
		ArrayList<Integer> ls;
		ArrayList<Integer> award;
		synchronized(GameData.lock)
		{
			screen_height=(int)GameData.baseHeight;
			ls=new ArrayList<Integer>(GameData.explosion);
			award=new ArrayList<Integer>(GameData.award);
		}
		tempAll=DataUtil.listToArray(ls);
		
		tempAward=DataUtil.listToArray(award);
		if(tempAll!=null)
		{
			ArrayList<Integer> tempSave=new ArrayList<Integer>();
			
			for(int i=0;i<tempAll.length;i=i+3)									//ÿ��ִ��ͼƬ��ż�1
			{
				tempAll[i]++; 
				if(tempAll[i]==24||tempAll[i]==49)								//�����ը�����ˣ���������һ����ը
				{
					continue;
				}
				tempSave.add(tempAll[i]);
				tempSave.add(tempAll[i+1]);
				tempSave.add(tempAll[i+2]+step);								//��ը����ͼͬ��
			}
			synchronized(GameData.lock)											//����ը���ݱ����GameData
			{
				GameData.explosion=tempSave;
			}
			ServerAgent.broadcastExplosion();									//�����ݷ���
		}
		
		if(tempAward==null)														//�жϽ����б��Ƿ�Ϊ��
		{
			return;
		}
		ArrayList<Integer> tempaward=new ArrayList<Integer>();
		
		int redX,redY,greenX,greenY,offest;
		float redAngle,greenAngle;
		
		synchronized(GameData.lock)
		{
			redX=GameData.redX;
			redY=GameData.redY;
			redAngle=GameData.redTankAngle;
			greenX=GameData.greenX;
			greenY=GameData.greenY;
			greenAngle=GameData.greenTankAngle;
			offest=GameData.offset;
		}
		for(int j=0;j<tempAward.length;j=j+3)									//���������б�
		{
			if(tempAward[j+2]>screen_height-offest)
			{
				if(Collision.checkCollision(redX,redY,tempAward[j+1],tempAward[j+2],redAngle,0,0,9))//��ɫ̹����ײ������
				{						
					Award(tempAward[j],1);	
					continue;
				}
				else if(Collision.checkCollision(greenX,greenY,tempAward[j+1],tempAward[j+2],greenAngle,0,0,9))	//��ɫ̹����ײ������
				{
					Award(tempAward[j],2);
					continue;
				}
				else
				{
					tempaward.add(tempAward[j]);
					tempaward.add(tempAward[j+1]);
					tempaward.add(tempAward[j+2]+Astep);
				}
			}
		}
		synchronized(GameData.lock)
		{
			GameData.award=tempaward;
		}
		ServerAgent.broadcastAward();
	}
	
	public void Award(int temp,int id)							
	{
		if(temp==12)					//��Ұ�ڵ����嶼��ը	C
		{
			Allexplode();			
		}
		else if(temp==13)				//̹�˼�Ѫ   	H
		{
			if(id==1)
			{
				GameData.redHealth+=5;
			}else
			{
				GameData.greenHealth+=5;
			}
		}
		else if(temp==14)				//̹�������ƶ��ٶȣ��ӵ�����Ƶ��	P
		{
			synchronized(GameData.lock)
			{
				if(GameData.tankSpeed<12)	//����6����															///????????????????????????????//
				{
					GameData.tankSpeed+=2;
				}
				if(id==1)
				{
					if(GameData.redTimeSpan>16)
					{
						GameData.redTimeSpan-=4;
						GameData.redTimeCount-=4;
					}
				}else
				{
					if(GameData.greenTimeSpan>16)
					{
						GameData.greenTimeSpan-=4;
						GameData.greenTimeCount-=4;
					}
				}
			}
		}
	}
	
	public void Allexplode()						//�����̹�˳Ե�  Cʱ��������ǰ��Ұ����ȫ����ը
	{
		ArrayList<Integer> tempMap=new ArrayList<Integer>();
		ArrayList<Integer> tempTank=new ArrayList<Integer>();
		int offest;
		int screen_height;
		
		synchronized(GameData.lock)
		{
			tempMap=DataUtil.arrayToList(GameData.mapData);			//ȡ����ͼ���б���
			tempTank=DataUtil.arrayToList(GameData.mapTank);		//ȡ��̹�˵��б���
			offest=GameData.offset;
			screen_height=(int)GameData.baseHeight;
		}
	//	System.out.println("offest  "+offest);
		int count=0;
		while(count<tempMap.size())									//������ͼ
		{
			if((tempMap.get(count+2)>-offest)&&(tempMap.get(count+2)<(screen_height-offest)))	//����ڵ�ǰ��Ұ��
			{
				if(tempMap.get(count)!=2&&tempMap.get(count)!=3)
				{
					tempMap.set(count,2);								//����ΪС��
					
					GameData.explosion.add(0);							//��ӵ���ը�б�
					GameData.explosion.add(tempMap.get(count+1));
					GameData.explosion.add(tempMap.get(count+2)+offest);
					
	//				GameData.award.add((int)(Math.random()*3)+12);
	//				//		GameData.award.add(14);
	//				GameData.award.add(tempMap.get(count+1));									//��ӽ�������ʱ�б�                                          ////////////////
	//				GameData.award.add(tempMap.get(count+2)+offest);
				}
				
			}
			count+=3;
		}
		count=0;
		while(count<tempTank.size())								//����̹��
		{
			if((tempTank.get(count+2)>-offest)&&(tempTank.get(count+2)<(screen_height-offest)))		//����ڵ�ǰ��Ұ��
			{
				if(tempTank.get(count)!=2&&tempTank.get(count)!=3)
				{
					tempTank.set(count,2);								//����ΪС��
					
					GameData.explosion.add(0);							//��ӵ���ը�б���
					GameData.explosion.add(tempTank.get(count+1));
					GameData.explosion.add(tempTank.get(count+2)+offest);
					
					//GameData.award.add((int)(Math.random()*3)+12);
					synchronized(GameData.lock)
					{
						GameData.award.add(12);
						GameData.award.add(tempTank.get(count+1));			//��ӽ�������ʱ�б�                                          ////////////////
						GameData.award.add(tempTank.get(count+2)+offest);
					}
				}
			}
			count+=3;			
		}
		
		synchronized(GameData.lock)									//�ѵ�ͼ���ݴ���ȫ��������
		{
			GameData.mapData=DataUtil.listToArray(tempMap);	
			GameData.mapTank=DataUtil.listToArray(tempTank);
		}
	}
}