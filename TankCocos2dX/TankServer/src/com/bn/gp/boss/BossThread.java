package com.bn.gp.boss;

import com.bn.gp.data.GameData;
import com.bn.gp.server.ServerAgent;

public class BossThread extends Thread
{
	public BossThread()
	{
		this.setName("boss");
	}
	
	public void run()
	{
		while(GameData.bossFlag)
		{
			if(GameData.gameState==2)
			{
				Boss boss[]={new FirstBoss(),new SecondBoss()};
				synchronized(GameData.lock)							//此处锁为serveragent的锁
				{
					ServerAgent.aq.offer(boss[GameData.level-1]);
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