package com.bn.gp.boss;

import java.util.ArrayList;

import com.bn.gp.data.GameData;
import com.bn.gp.server.Collision;
import com.bn.gp.server.LevelChangeThread;
import com.bn.gp.server.ServerAgent;

public class SecondBoss extends Boss
{
	int bossX;
	int bossY;
	
	@Override
	public void doAction() 
	{
		int redX,redY,greenX,greenY;
		int bossHealth,bossDirection;
		float redAngle,greenAngle;
		boolean bossFlag;
		
		synchronized(GameData.lock)
		{
			redX=GameData.redX;	//红色坦克状态
			redY=GameData.redY;
			redAngle=GameData.redTankAngle;
			
			greenX=GameData.greenX;		//绿色坦克状态
			greenY=GameData.greenY;
			greenAngle=GameData.greenTankAngle;
			
			bossFlag=GameData.bossFlag;	//boss是否出现
			bossHealth=GameData.bossHealth;	//boss血量
			bossX=GameData.bossX;
			bossY=GameData.bossY;
			bossDirection=GameData.bossDirection; //boss方向
		}
		if(bossHealth<=0)
		{
			synchronized(GameData.lock)
			{
				GameData.bossFlag=false;	//设置boss消失
			}
			for(int i=0;i<10;i++)			//在死亡的boss上随机加爆炸
			{
				int tempX=(int) (bossX+Math.random()*GameData.bossSize/2);
				int tempY=(int) (bossY+Math.random()*GameData.bossSize/2);
				synchronized(GameData.lock)
				{
					GameData.explosion.add(0);
					GameData.explosion.add(tempX);
					GameData.explosion.add(tempY);
				}
			}
			new LevelChangeThread().start();
		}
		if(bossFlag)							//如果boss存在
		{
			moveBoss(bossX, bossY, bossDirection);	//boss移动方法
			
			bulletBoss();

			ServerAgent.broadcastBoss();	//发送boss		
			
			if(Collision.checkCollision(redX,redY,bossX,bossY,redAngle,0,0,10))//红色坦克碰撞到奖励
			{
				synchronized(GameData.lock)
				{
					GameData.redHealth=0;
					GameData.redX=-1000;
					GameData.redY=-1000;
					GameData.explosion.add(0);
					GameData.explosion.add(redX);
					GameData.explosion.add(redY);
				}
			}
			if(Collision.checkCollision(greenX,greenY,bossX,bossY,greenAngle,0,0,10))//绿色坦克碰撞到奖励
			{						
				synchronized(GameData.lock)
				{
					GameData.greenHealth=0;
					GameData.greenX=-1000;
					GameData.greenY=-1000;
					GameData.explosion.add(0);
					GameData.explosion.add(greenX);
					GameData.explosion.add(greenY);
				}
			}
		}
	}
	
	private void bulletBoss() 					//boss子弹
	{
		int Angle=30;			//分散角度
		int n=(int)(360/Angle);	//几个方向
		int sort2=2;				//子弹列别
	//	int sort0=0;
		int timecount;			
		int direction;
		
		synchronized(GameData.lock)
		{
			timecount=GameData.timecount;
			direction=GameData.bossDirection;
		}
		if(timecount%70==0)
		{
			if(bossY==270)		//boss走到屏幕中央
			{
				for(int i=0;i<n;i++)
				{
					synchronized(GameData.lock)
					{
						GameData.bossBulletList.add(new Bossbullet(sort2,bossX+direction*5,bossY+48,Angle*i));
					}
				}
				
			}
		}
		timecount++;
		synchronized(GameData.lock)
		{
			GameData.timecount=timecount;
		}
		
		ArrayList<Bossbullet> bossTemp;
		ArrayList<Bossbullet> bossDel=new ArrayList<Bossbullet>();
		ArrayList<Float> bossbullet=new ArrayList<Float>();
		
		synchronized(GameData.lock)
		{
			bossTemp=new ArrayList<Bossbullet>(GameData.bossBulletList);
			System.out.println("game  Bullet "+GameData.bossBulletList.size());
		}
		
		for(Bossbullet ob:bossTemp)
		{
			ob.go();
			if(ob.bulletX<0||ob.bulletX>GameData.baseWidth||ob.bulletY<0||ob.bulletY>GameData.baseHeight)
			{
				bossDel.add(ob);
			}else if(Collision.checkCollision((int)ob.sort, (int)ob.bulletX, (int)ob.bulletY))
			{
				bossDel.add(ob);
			}else
			{
				bossbullet.add(ob.sort);
				bossbullet.add(ob.bulletX);
				bossbullet.add(ob.bulletY);
				bossbullet.add(ob.angle);
			}
		}
		synchronized(GameData.lock)
		{
			System.out.println("bossbullet size "+bossbullet.size());
			for(Bossbullet bb:bossDel)
			{
				GameData.bossBulletList.remove(bb);
			}
			GameData.bossBullet=bossbullet;
		}
		
	}

	private void moveBoss(int bossX, int bossY, int bossDirection) //boss移动轨迹
	{
		if(bossY<270)
		{
			bossY+=2;
			synchronized(GameData.lock)
			{
				GameData.bossY=bossY;
			}
			return;
		}
		bossX+=bossDirection;
		if(bossX<210||bossX>750) //boss方向 取反
		{
			bossDirection=-bossDirection;
		}
		synchronized(GameData.lock)
		{
			GameData.bossX=bossX;
			GameData.bossDirection=bossDirection;
		}
	}
}

