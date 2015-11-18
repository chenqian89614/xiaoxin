package com.bn.gp.server;

import com.bn.gp.action.Action;
import com.bn.gp.data.GameData;

public class MainMissileThread extends Thread
{
	int SLEEP=40;
	
	public MainMissileThread()
	{
		this.setName("MainMissile");
	}
	
	@Override
	public void run()
	{
		while(GameData.threadFlag)
		{
			if(GameData.gameState==2)
			{
				Action a=new MainMissileControl();
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
