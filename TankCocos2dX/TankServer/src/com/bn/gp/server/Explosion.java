package com.bn.gp.server;

import java.util.ArrayList;

import com.bn.gp.action.Action;
import com.bn.gp.data.GameData;

public class Explosion extends Action									
{
	int step=2;
	int Astep=4;
	@Override
	public void doAction() 													//检测爆炸是否已结束，没结束加上吧、偏移量
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
			
			for(int i=0;i<tempAll.length;i=i+3)									//每次执行图片标号加1
			{
				tempAll[i]++; 
				if(tempAll[i]==24||tempAll[i]==49)								//如果爆炸结束了，继续看下一个爆炸
				{
					continue;
				}
				tempSave.add(tempAll[i]);
				tempSave.add(tempAll[i+1]);
				tempSave.add(tempAll[i+2]+step);								//爆炸跟地图同步
			}
			synchronized(GameData.lock)											//将爆炸数据保存进GameData
			{
				GameData.explosion=tempSave;
			}
			ServerAgent.broadcastExplosion();									//将数据发送
		}
		
		if(tempAward==null)														//判断奖励列表是否为空
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
		for(int j=0;j<tempAward.length;j=j+3)									//遍历奖励列表
		{
			if(tempAward[j+2]>screen_height-offest)
			{
				if(Collision.checkCollision(redX,redY,tempAward[j+1],tempAward[j+2],redAngle,0,0,9))//红色坦克碰撞到奖励
				{						
					Award(tempAward[j],1);	
					continue;
				}
				else if(Collision.checkCollision(greenX,greenY,tempAward[j+1],tempAward[j+2],greenAngle,0,0,9))	//绿色坦克碰撞到奖励
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
		if(temp==12)					//视野内的物体都爆炸	C
		{
			Allexplode();			
		}
		else if(temp==13)				//坦克加血   	H
		{
			if(id==1)
			{
				GameData.redHealth+=5;
			}else
			{
				GameData.greenHealth+=5;
			}
		}
		else if(temp==14)				//坦克增加移动速度，子弹发射频率	P
		{
			synchronized(GameData.lock)
			{
				if(GameData.tankSpeed<12)	//共有6个档															///????????????????????????????//
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
	
	public void Allexplode()						//当玩家坦克吃到  C时，产生当前视野物体全部爆炸
	{
		ArrayList<Integer> tempMap=new ArrayList<Integer>();
		ArrayList<Integer> tempTank=new ArrayList<Integer>();
		int offest;
		int screen_height;
		
		synchronized(GameData.lock)
		{
			tempMap=DataUtil.arrayToList(GameData.mapData);			//取出地图到列表中
			tempTank=DataUtil.arrayToList(GameData.mapTank);		//取出坦克到列表中
			offest=GameData.offset;
			screen_height=(int)GameData.baseHeight;
		}
	//	System.out.println("offest  "+offest);
		int count=0;
		while(count<tempMap.size())									//遍历地图
		{
			if((tempMap.get(count+2)>-offest)&&(tempMap.get(count+2)<(screen_height-offest)))	//如果在当前视野内
			{
				if(tempMap.get(count)!=2&&tempMap.get(count)!=3)
				{
					tempMap.set(count,2);								//设置为小坑
					
					GameData.explosion.add(0);							//添加到爆炸列表
					GameData.explosion.add(tempMap.get(count+1));
					GameData.explosion.add(tempMap.get(count+2)+offest);
					
	//				GameData.award.add((int)(Math.random()*3)+12);
	//				//		GameData.award.add(14);
	//				GameData.award.add(tempMap.get(count+1));									//添加奖励的临时列表                                          ////////////////
	//				GameData.award.add(tempMap.get(count+2)+offest);
				}
				
			}
			count+=3;
		}
		count=0;
		while(count<tempTank.size())								//遍历坦克
		{
			if((tempTank.get(count+2)>-offest)&&(tempTank.get(count+2)<(screen_height-offest)))		//如果在当前视野内
			{
				if(tempTank.get(count)!=2&&tempTank.get(count)!=3)
				{
					tempTank.set(count,2);								//设置为小坑
					
					GameData.explosion.add(0);							//添加到爆炸列表中
					GameData.explosion.add(tempTank.get(count+1));
					GameData.explosion.add(tempTank.get(count+2)+offest);
					
					//GameData.award.add((int)(Math.random()*3)+12);
					synchronized(GameData.lock)
					{
						GameData.award.add(12);
						GameData.award.add(tempTank.get(count+1));			//添加奖励的临时列表                                          ////////////////
						GameData.award.add(tempTank.get(count+2)+offest);
					}
				}
			}
			count+=3;			
		}
		
		synchronized(GameData.lock)									//把地图数据存入全局数据中
		{
			GameData.mapData=DataUtil.listToArray(tempMap);	
			GameData.mapTank=DataUtil.listToArray(tempTank);
		}
	}
}