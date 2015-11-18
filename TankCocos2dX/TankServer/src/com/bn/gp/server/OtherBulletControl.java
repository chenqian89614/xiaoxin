package com.bn.gp.server;

import java.util.ArrayList;

import com.bn.gp.action.Action;
import com.bn.gp.data.GameData;

public class OtherBulletControl extends Action 
{
	
	@Override
	public void doAction() 
	{
		int length;
		int redX=0,redY=0,greenX=0,greenY=0,timeCount=0,timeSpan=0,State=0;
		
		ArrayList<Integer> tempData=new ArrayList<Integer>();
		
		synchronized(GameData.lock)
		{
			if(GameData.tempTank!=null)
			{
				length=GameData.tempTank.size();	
				
				for(int i=0;i<length;i+=3)									//两个ArrayList 赋值
				{
					if(GameData.tempTank.get(i)!=2&&GameData.tempTank.get(i)!=3)
					{
						tempData.add(GameData.tempTank.get(i));
						tempData.add(GameData.tempTank.get(i+1));
						tempData.add(GameData.tempTank.get(i+2));
					}
				}
				redX=GameData.redX;
				redY=GameData.redY;
				greenX=GameData.greenX;
				greenY=GameData.greenY;
				timeCount=GameData.otherTimeCount;
				timeSpan=GameData.otherTimeSpan;
				State=GameData.otherState;
			}
		}
		
		State=(State==0)?0:(State-1);
		
		if((timeCount==timeSpan))
		{
			int x=0,y=0,angle=0,sort;
			timeCount=0;
			State=20;														//?????????????????????????
			for(int i=0;i<tempData.size();i++)
			{
				sort=tempData.get(i++);
				x=tempData.get(i++);
				y=tempData.get(i);
				
				int t1=(x-greenX)*(x-greenX)+(y-greenY)*(y-greenY);			//距离绿色坦克的距离
				int t2=(x-redX)*(x-redX)+(y-redY)*(y-redY);					//与红色坦克的距离
				
				if(t1<t2)													//如果离绿色的近
				{
					angle=((int)(toAngle(greenX-x,greenY-y)));
				}else
				{
					angle=((int)(toAngle(redX-x,redY-y)));
				}
				
				if(sort==11||sort==8)
				{
					OtherBullet temp1=new OtherBullet(1,x,y,angle);
					synchronized(GameData.lock)
					{
						GameData.otherBulletList.add(temp1);         		//
					}
				}else
				{
					OtherBullet temp2=new OtherBullet(0,x,y,angle);
					synchronized(GameData.lock)
					{
						GameData.otherBulletList.add(temp2);         		//
					}
				}
				
			}
			
		}
		
		timeCount++;
		
		synchronized(GameData.lock)
		{
			GameData.otherTimeCount=timeCount;
			GameData.otherState=State;
		}

		ArrayList<OtherBullet> alTemp;
		ArrayList<OtherBullet> alDel=new ArrayList<OtherBullet>();
		ArrayList<Float> otherbullet=new ArrayList<Float>();
		synchronized(GameData.lock)
		{
			alTemp=new ArrayList<OtherBullet>(GameData.otherBulletList);
		}

		for(OtherBullet ob:alTemp)
		{
			ob.go();
			if(ob.bulletX<0||ob.bulletX>GameData.baseWidth||ob.bulletY<0||ob.bulletY>GameData.baseHeight)
			{
				alDel.add(ob);
			}
			else if(Collision.checkCollision((int)ob.sort,(int)ob.bulletX, (int)ob.bulletY))						//将撞击到物体的子弹加入销毁列表
			{
				alDel.add(ob);
			}else
			{
				otherbullet.add(ob.sort);
				otherbullet.add(ob.bulletX);
				otherbullet.add(ob.bulletY);
				otherbullet.add(ob.angle);
			}
		}
		
		synchronized(GameData.lock)
		{
			GameData.otherBullet=otherbullet;
			for(OtherBullet ob:alDel)
			{
				GameData.otherBulletList.remove(ob);
			}
		}
		
		ServerAgent.broadcastOtherBullet();											//发送子弹数据
		
	}
	
	
	
	
	private float toAngle(float dx, float dy) 
	{
		float tempAngle=(float) Math.toDegrees(Math.atan(dy/dx));
		if(dx==0)
		{
			if(dy>0)
			{
				tempAngle=180;
			}else
			{
				tempAngle=0;
			}
		}
		else if(dx>0)
		{
			tempAngle=90+tempAngle;
		}else if(dx<0)
		{
			tempAngle=270+tempAngle;
		}
		return tempAngle;
	}

}
