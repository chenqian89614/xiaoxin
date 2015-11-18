package com.bn.gp.server;

import java.util.ArrayList;

import com.bn.gp.action.Action;
import com.bn.gp.boss.BossThread;
import com.bn.gp.data.GameData;

public class Map extends Action
{	
	int  step=1;
	int offset;					//偏移量
	ArrayList<Integer> tempMap=new ArrayList<Integer>();
	ArrayList<Integer> tempTree=new ArrayList<Integer>();
	ArrayList<Integer> tempTank=new ArrayList<Integer>();
	ArrayList<Integer> temp=new ArrayList<Integer>();
	int othertank;
	public void MoveTo(int[] Map,ArrayList<Integer> tempMap)
	{
		int count=2;
		while(count<Map.length)
		{
			if(-offset<Map[count]&&Map[count]<(-offset+GameData.baseHeight))
			{
				tempMap.add(Map[count-2]);
				tempMap.add(Map[count-1]);
				tempMap.add(Map[count]+offset);
			}
			count+=3;
		}	
	}
	@Override
	public void doAction() 
	{
		offset=step*GameData.time;
		int []Map=GameData.mapData;
		int []Tree=GameData.mapTree;
		int []Tank=GameData.mapTank;
		
		int redX,redY,greenX,greenY;
		int tx,ty;
		synchronized(GameData.lock)
		{			
			redX=GameData.redX;
			redY=GameData.redY;
			greenX=GameData.greenX;
			greenY=GameData.greenY;
			GameData.offset=offset;
		}
		
		tempMap.add(offset%(int)GameData.baseHeight);
		MoveTo(Map,tempMap);
		if(tempMap!=null)
		{
			ServerAgent.broadcastMap(tempMap);
		}
		
		MoveTo(Tree,tempTree);
		if(tempTree!=null)
		{
			ServerAgent.broadcastTree(tempTree);
		}
		
		MoveTo(Tank,tempTank);
		if(tempTank!=null)
		{
			for(int i=0;i<tempTank.size();i+=3)
			{
				othertank=tempTank.get(i);
		//		if(othertank!=2&&othertank!=3)
				{
					temp.add(tempTank.get(i));				//编号
					tx=tempTank.get(i+1);
					temp.add(tempTank.get(i+1));				//x
					ty=tempTank.get(i+2);
					temp.add(tempTank.get(i+2));					//y
					
					int t1=(tx-greenX)*(tx-greenX)+(ty-greenY)*(ty-greenY);			//距离绿色坦克的距离
					int t2=(tx-redX)*(tx-redX)+(ty-redY)*(ty-redY);					//与红色坦克的距离
					
					if(t1<t2)											//如果离绿色的近
					{
						temp.add((int)(toAngle(greenX-tx,greenY-ty)));
					}else
					{
						temp.add((int)(toAngle(redX-tx,redY-ty)));
					}
				}
				
			}
			
			synchronized(GameData.lock)
			{
				GameData.tempTank=new ArrayList<Integer>(tempTank);
			}
			ServerAgent.broadcastTank(temp);
		}
		
		GameData.time++;
		
		rollTank();
		rollMissile();
		if(offset==7500)
		{
			synchronized(GameData.lock)
			{
				GameData.bossX=480;
				GameData.bossY=0;
				GameData.bossFlag=true;
			}
			new BossThread().start();
		}
	}
	
	private void rollMissile() 
	{
		synchronized(GameData.lock)
		{
			for(int i=0;i<GameData.mainMissileList.size();i++)
			{
				GameData.mainMissileList.get(i).targetY+=step;
			}
		}
	}
	
	public float toAngle(float dx,float dy)									//获得角度 
	{
		float tankAngle=(float) Math.toDegrees(Math.atan(dy/dx));
		if(dx==0)
		{
			if(dy>0)
			{
				tankAngle=180;
			}else
			{
				tankAngle=0;
			}
		}
		else if(dx>0)
		{	
			tankAngle=(float)Math.toDegrees(Math.atan(dy/dx));
			tankAngle=90+tankAngle;
		}else if(dx<0)
		{	
			tankAngle=(float)Math.toDegrees(Math.atan(dy/dx));
			tankAngle=270+tankAngle;
		}
		return tankAngle;
	}
	
	private void rollTank() 
	{
		int redX,redY,greenX,greenY,redHealth,greenHealth,sideCount=0;
		float redAngle,greenAngle;
		synchronized(GameData.lock)
		{
			redX=GameData.redX;
			redY=GameData.redY;
			greenX=GameData.greenX;
			greenY=GameData.greenY;
			redHealth=GameData.redHealth;
			greenHealth=GameData.greenHealth;
			redAngle=GameData.redTankAngle;
			greenAngle=GameData.greenTankAngle;
		}
		if(GameData.tankFlag[0]==0)
		{
			int redYR=redY;
			redY+=step;
			if(redY>GameData.baseHeight-GameData.sideSize)
			{
				redY=redYR;
				sideCount++;
			}
			if(Collision.checkCollision(redX, redY, greenX, greenY, redAngle, greenAngle, 0, 0))
			{
				redY=redYR;
			}
			if(Collision.checkCollision(redX, redY, redAngle, 0))
			{
				int hurt=10;
				redHealth=(redHealth-hurt>0)?(redHealth-hurt):0;
				if(redHealth==0)
				{
					GameData.redX=-1000;
					GameData.redY=-1000;
				}
			}
		}
		if(GameData.tankFlag[1]==0)
		{
			int greenYR=greenY;
			greenY+=step;
			if(greenY>GameData.baseHeight-GameData.sideSize)
			{
				greenY=greenYR;
				sideCount++;
			}
			if(Collision.checkCollision(greenX, greenY, redX, redY, redAngle, greenAngle, 0, 0))
			{
				greenY=greenYR;
			}
			if(Collision.checkCollision(greenX, greenY, greenAngle, 0))
			{
				int hurt=10;
				greenHealth=(greenHealth-hurt>0)?(greenHealth-hurt):0;
				if(greenHealth==0)
				{
					greenX=-1000;
					greenY=-1000;
				}
			}
		}
		synchronized(GameData.lock)
		{
			GameData.redX=redX;
			GameData.redY=redY;
			GameData.redHealth=redHealth;
			GameData.greenX=greenX;
			GameData.greenY=greenY;
			GameData.greenHealth=greenHealth;
		}
		if(sideCount!=2)
		{
			ServerAgent.broadcastTank();
		}
		for(int i=0;i<2;i++)
		{
			if(GameData.tankFlag[i]!=0)
			{
				GameData.tankFlag[i]--;
			}
		}
	}
}