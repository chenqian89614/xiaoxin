package com.bn.gp.action;

import com.bn.gp.data.GameData;
import com.bn.gp.server.ServerAgent;

public class ActionThread extends Thread
{
	public void run()
	{
		while(true)
		{
			Action a=null;
			synchronized(GameData.lock)
			{
				a=ServerAgent.aq.poll();
			}
			if(a!=null)
			{
				try
				{
					a.doAction();
				}
				catch(Exception e)
				{
					break;
				}
			}
		}
	}
}