package com.bn.gp.server;

import com.bn.gp.action.Action;

public class Update extends Action
{
	UpdateEnum updateEnum;
	public Update(UpdateEnum updateEnum)
	{
		this.updateEnum=updateEnum;
	}
	@Override
	public void doAction() 
	{
		switch(updateEnum)
		{
		case date:
			ServerAgent.broadcastData();
			break;
		case gameState:
			ServerAgent.broadcastGameState();
			break;
		}
	}	
	
	public enum UpdateEnum
	{
	    date,gameState
	}
}
