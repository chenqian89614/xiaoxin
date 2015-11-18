package com.bn.gp.server;

import com.bn.gp.action.Action;
import com.bn.gp.data.GameData;

public class UpdateThread extends Thread
{
	int redHealth;
	int greenHealth;
	int score;
	int gameState;
	public UpdateThread()
	{
		this.setName("Update");
		synchronized(GameData.lock)
		{
			this.redHealth=GameData.redHealth;
			this.greenHealth=GameData.greenHealth;
			this.score=GameData.score;
			this.gameState=GameData.gameState;
		}
	}
	
	@Override
	public void run()
	{
		while(GameData.threadFlag)
		{
			if(check())
			{
				Action a=new Update(Update.UpdateEnum.date);
				synchronized(GameData.lock)
				{
					ServerAgent.aq.offer(a);
				}
			}
			if(checkState())
			{
				Update temp=new Update(Update.UpdateEnum.gameState);
				synchronized(GameData.lock)
				{
					ServerAgent.aq.offer(temp);
				}
			}
			try
			{
				Thread.sleep(200);
			}
			catch(Exception e)
			{
				e.printStackTrace();
			}
		}
	}
	
	private boolean checkState()
	{
		boolean flag=false;
		int gameState;
		synchronized(GameData.lock)
		{
			gameState=GameData.gameState;
		}
		if(gameState==2&&this.redHealth==0&&this.greenHealth==0)
		{
			gameState=3;
			synchronized(GameData.lock)
			{
				GameData.gameState=3;
			}
			new Thread()
			{
				public void run()
				{
					try 
					{
						Thread.sleep(3000);
					} catch (InterruptedException e) 
					{
						e.printStackTrace();
					}
					ServerAgent.closeGame();
				}
			}.start();
		}
		if(this.gameState!=gameState)
		{
			flag=true;
		}
		this.gameState=gameState;
		return flag;
	}

	private boolean check() 
	{
		int redHealth,greenHealth,score;
		boolean flag=false;
		synchronized(GameData.lock)
		{
			redHealth=GameData.redHealth;
			greenHealth=GameData.greenHealth;
			score=GameData.score;
		}
		if(redHealth>100)
		{
			redHealth=100;
			synchronized(GameData.lock)
			{
				GameData.redHealth=redHealth;
			}
		}
		if(greenHealth>100)
		{
			greenHealth=100;
			synchronized(GameData.lock)
			{
				GameData.greenHealth=greenHealth;
			}
		}
		if(this.redHealth!=redHealth||this.greenHealth!=greenHealth||this.score!=score)
		{
			flag=true;
		}
		this.redHealth=redHealth;
		this.greenHealth=greenHealth;
		this.score=score;
		return flag;
	}
}