package com.bn.gp.server;

import com.bn.gp.action.Action;
import com.bn.gp.data.GameData;

public class MainBulletThread extends Thread
{
	public MainBulletThread()
	{
		this.setName("MainBullet");
	}
	
	@Override
	public void run()
	{
		while(GameData.threadFlag)
		{
			if(GameData.gameState==2)
			{
				Action a=new MainBulletControl();
				synchronized(GameData.lock)
				{
					ServerAgent.aq.offer(a);
				}
			}
			try
			{
				Thread.sleep(20);
			}
			catch(Exception e)
			{
				e.printStackTrace();
			}
		}
	}
}