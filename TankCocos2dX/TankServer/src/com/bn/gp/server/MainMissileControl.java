package com.bn.gp.server;

import java.util.ArrayList;

import com.bn.gp.action.Action;
import com.bn.gp.data.GameData;

public class MainMissileControl extends Action
{
	@Override
	public void doAction()
	{
		createMissile();
		ArrayList<MainMissile> alTemp;
		ArrayList<MainMissile> alDel=new ArrayList<MainMissile>();
		ArrayList<Float> mainmissile=new ArrayList<Float>();
		synchronized(GameData.lock)
		{
			alTemp=new ArrayList<MainMissile>(GameData.mainMissileList);
		}
		for(MainMissile mm:alTemp)										//遍历所有子弹		
		{
			mm.go();													//让每个子弹根据自己的方向前进
			if(mm.missileX<0||mm.missileX>GameData.baseWidth||mm.missileY<0||mm.missileY>GameData.baseHeight)	//将出地图的子弹加入销毁列表
			{
				alDel.add(mm);
			}
			else if(Collision.checkCollision((int)mm.missileX, (int)mm.missileY, 0, 2))						//将撞击到物体的子弹加入销毁列表
			{
				alDel.add(mm);
			}
			else if(GameData.bossFlag)
			{
				int bossX,bossY;
				synchronized(GameData.lock)
				{
					bossX=GameData.bossX;
					bossY=GameData.bossY;
				}
				if(Collision.checkCollision((int)mm.missileX, (int)mm.missileY, bossX, bossY, 0, 0, 1, 10))
				{
					synchronized(GameData.lock)
					{
						GameData.bossHealth-=2;
					}
					alDel.add(mm);
				}
			}
			else																							//合格子弹加入新列表等待发送和保存
			{
				mainmissile.add(mm.missileX);
				mainmissile.add(mm.missileY);
				mainmissile.add(mm.angle);
			}
		}
		synchronized(GameData.lock)
		{
			GameData.mainMissile=mainmissile;
			for(MainMissile mm:alDel)
			{
				GameData.mainMissileList.remove(mm);								//将过期子弹销毁
			}
		}
		ServerAgent.broadcastMissile();
	}

	private void createMissile() 
	{
		int tankSpeed,redMissileSpan,greenMissileSpan,redMissileCount,greenMissileCount;
		int redX,redY,greenX,greenY,redHealth,greenHealth;
		ArrayList<Integer> alTemp = new ArrayList<Integer>();
		int offset;
		//读取数据
		synchronized(GameData.lock)
		{
			offset=GameData.offset;
			tankSpeed=GameData.tankSpeed;
			redX=GameData.redX;
			redY=GameData.redY;
			greenX=GameData.greenX;
			greenY=GameData.greenY;
			redMissileSpan=GameData.redMissileSpan;
			greenMissileSpan=GameData.greenMissileSpan;
			redMissileCount=GameData.redMissileCount;
			greenMissileCount=GameData.greenMissileCount;
			redHealth=GameData.redHealth;
			greenHealth=GameData.greenHealth;
			alTemp.addAll(DataUtil.arrayToList(GameData.mapData));									//获取地图数据
			alTemp.addAll(DataUtil.arrayToList(GameData.mapTank));	
		}
		if(tankSpeed>=10&&redMissileSpan==redMissileCount&&redHealth>0)
		{
			redMissileCount=0;
			create(redX, redY, alTemp, offset);
		}
		redMissileCount++;
		if(tankSpeed>=10&&greenMissileSpan==greenMissileCount&&greenHealth>0)
		{
			greenMissileCount=0;
			create(greenX, greenY, alTemp, offset);
		}
		greenMissileCount++;
		synchronized(GameData.lock)
		{
			GameData.redMissileSpan=redMissileSpan;
			GameData.greenMissileSpan=greenMissileSpan;
			GameData.redMissileCount=redMissileCount;
			GameData.greenMissileCount=greenMissileCount;
		}
	}

	private void create(int X, int Y, ArrayList<Integer> alTemp, int offset) 
	{
		int count=0,x=0,y=(int) GameData.baseHeight;
		boolean flag=false;
		if(GameData.bossFlag)
		{
			MainMissile temp=new MainMissile(X,Y,GameData.bossX,GameData.bossY);
			synchronized(GameData.lock)
			{
				GameData.mainMissileList.add(temp);
			}
			return;
		}
		while(count<alTemp.size())
		{
			int ctemp=alTemp.get(count++);
			int xtemp=alTemp.get(count++);
			int ytemp=alTemp.get(count++)+offset;
			if(ctemp>3&&ytemp>0&&ytemp<GameData.baseHeight&&ytemp<y)
			{
				x=xtemp;
				y=ytemp;
				flag=true;
			}
		}
		if(flag)
		{
			MainMissile temp=new MainMissile(X,Y,x,y);
			synchronized(GameData.lock)
			{
				GameData.mainMissileList.add(temp);
			}
		}
	}
}