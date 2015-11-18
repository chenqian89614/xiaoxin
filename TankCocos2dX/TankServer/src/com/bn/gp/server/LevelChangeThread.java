package com.bn.gp.server;

import com.bn.gp.data.GameData;

public class LevelChangeThread extends Thread
{
	public LevelChangeThread()
	{
		this.setName("levelChange");
	}
	
	@Override
	public void run()
	{
		ServerAgent.broadcastClear();
		try
		{
			Thread.sleep(2000);
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		if(LevelChange.changeLevel())
		{
			GameData.gameState=2;
		}else
		{
			ServerAgent.broadcastVictory();
			ServerAgent.closeGame();
		}
	}
}