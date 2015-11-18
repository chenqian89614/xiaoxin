package com.bn.gp.server;

import com.bn.gp.action.Action;
import com.bn.gp.data.GameData;

public class OtherBulletThread extends Thread
{
	int SLEEP=20;
	
	public OtherBulletThread()
	{
		this.setName("OtherBullet");
	}
	
	@Override
	public void run()
	{
		while(GameData.threadFlag)
		{
			if(GameData.gameState==2)
			{
				Action a=new OtherBulletControl();
				synchronized(GameData.lock)
				{
					ServerAgent.aq.add(a);
				}
			}
			try
			{
				Thread.sleep(SLEEP);
			}catch(Exception e)
			{
				e.printStackTrace();
			}
		}
	}
}
