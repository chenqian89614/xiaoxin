package com.bn.util;

public class CodeChange 
{
	public static int[] serverChangeclient(int client[])					//服务器对 客户端的扑克牌的 代号转换
	{
		if(client==null)
		{
			return null;
		}
		for(int i=0;i<client.length;i++)
		{
			if(client[i]==11||client[i]==12||client[i]==24||client[i]==25||client[i]==37||client[i]==38||client[i]==50||client[i]==51)
			{
				client[i]=client[i]-11;
			}else if(client[i]==52||client[i]==53)
			{
				client[i]=client[i];
			}else 
			{
				client[i]=client[i]+2;
			}
		}
		return client;
	}
	public static int serverChangeclientInt(int client)					//服务器对 客户端的扑克牌的 代号转换
	{
		if(client==11||client==12||client==24||client==25||client==37||client==38||client==50||client==51)
		{
			client=client-11;
		}else if(client==52)
		{
			client=13;
		}else if(client==53)
		{
			client=14;
		}else
		{
			client=client+2;
		}
		return client;
	}
	public static int[] clientChangeserver(int server[])					//客户端 对 服务器的扑克牌代号的转换
	{
		for(int i=0;i<server.length;i++)
		{
			if(server[i]==0||server[i]==1||server[i]==13||server[i]==14||server[i]==26||server[i]==27||server[i]==39||server[i]==40)
			{
				server[i]=server[i]+11;
			}else if(server[i]==52||server[i]==53)
			{
				server[i]=server[i];
			}else 
			{
				server[i]=server[i]-2;
			}
		}
		return server;
	}
}
