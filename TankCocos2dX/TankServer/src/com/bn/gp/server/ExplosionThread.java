package com.bn.gp.server;

import com.bn.gp.action.Action;
import com.bn.gp.data.GameData;

public class ExplosionThread extends Thread
{
	public ExplosionThread()
	{
		this.setName("explosion");
	}
	
	@Override
	public void run()
	{
		while(GameData.threadFlag)
		{
			if(GameData.gameState==2)
			{
				Action a=new Explosion();
				synchronized(GameData.lock)							//此处锁为serveragent的锁
				{
					ServerAgent.aq.offer(a);
				}
			}
			try
			{
				Thread.sleep(40);
			}
			catch(Exception e)
			{
				e.printStackTrace();
			}
		}
	}
}