package com.bn.gp.server;

import java.net.*;

import com.bn.gp.action.ActionThread;

public class ServerThread extends Thread
{
	boolean flag=false;
	ServerSocket ss;
	
	@Override
	public void run()
	{
		try
		{
			ss=new ServerSocket(59421);
			System.out.println("Server Listening on 59421...");
			flag=true;
			ServerAgent.count=0;
		}catch(Exception e)
		{
			e.printStackTrace();
		}
		
		while(flag)
		{
			try
			{
				Socket sc=ss.accept();
				System.out.println(sc.getInetAddress()+" connect...");
				ServerAgent.flag=true;
				new ServerAgent(this,sc).start();
			}
			catch(Exception e)
			{
				//e.printStackTrace();
			}
		}
	}
	
	public static void main(String args[])
	{
		new ServerThread().start();
		new ActionThread().start();
	}
}