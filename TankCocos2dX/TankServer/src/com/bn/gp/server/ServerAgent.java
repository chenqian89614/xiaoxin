package com.bn.gp.server;

import java.io.*;
import java.net.*;
import java.util.*;

import com.bn.gp.action.Action;
import com.bn.gp.data.GameData;
import static com.bn.gp.util.IOUtil.*;

public class ServerAgent extends Thread
{
	//客户端计数器
	static int count=0;
	//客户端列表
	static List<ServerAgent> ulist=new ArrayList<ServerAgent>();
	//动作队列
	public static Queue<Action> aq=new LinkedList<Action>();
	
	Socket sc;
	static ServerThread st;
	DataInputStream din;
	DataOutputStream dout;
	int redOrGreen;
	static boolean flag=true;
	int i=0;
	
	public static void broadcastMap(ArrayList<Integer> tempMap)
	{
		for(ServerAgent sa:ulist)
		{
			try
			{
				synchronized(GameData.lock)
				{
					sendStr(sa.dout, "<#GAME_MAP#>");
					sendInt(sa.dout, tempMap.size());
					for(int j=0;j<tempMap.size();j++)
					{
						sendInt(sa.dout,tempMap.get(j));
					}
				}
			}
			catch(Exception e)
			{
				e.printStackTrace();
			}
		}
	}
	
	public static void broadcastAward()							//发送爆炸后的奖励坐标
	{
		for(ServerAgent sa:ulist)
		{
			try
			{
				synchronized(GameData.lock)
				{
					sendStr(sa.dout, "<#GAME_AWARD#>");
					sendInt(sa.dout, GameData.award.size());
					for(int i=0;i<GameData.award.size();i++)
					{
						sendInt(sa.dout, GameData.award.get(i));
					}
				}
			}catch(Exception e)
			{
				e.printStackTrace();
			}
		}
	}
	
	public static void broadcastExplosion()						//发送爆炸坐标
	{
		for(ServerAgent sa:ulist)
		{
			try
			{
				synchronized(GameData.lock)
				{
					sendStr(sa.dout, "<#GAME_EXPLOSION#>");
					sendInt(sa.dout, GameData.explosion.size());
					for(int i=0;i<GameData.explosion.size();i++)
					{
						sendInt(sa.dout, GameData.explosion.get(i));
					}
				}
			}catch(Exception e)
			{
				e.printStackTrace();
			}
		}
	}
	
	public static void broadcastData() 
	{
		for(ServerAgent sa:ulist)
		{
			try
			{
				synchronized(GameData.lock)
				{
					sendStr(sa.dout, "<#GAME_DATA#>");
					sendInt(sa.dout, GameData.redHealth);
					sendInt(sa.dout, GameData.greenHealth);
					sendInt(sa.dout, GameData.score);
				}
			}catch(Exception e)
			{
				e.printStackTrace();
			}
		}
	}
	public static void broadcastGameState() 
	{
		for(ServerAgent sa:ulist)
		{
			try
			{
				synchronized(GameData.lock)
				{
					sendStr(sa.dout, "<#GAME_GAMESTATE#>");
					sendInt(sa.dout, GameData.gameState);
				}
			}catch(Exception e)
			{
				e.printStackTrace();
			}
		}
	}	
	
	public static void broadcastTree(ArrayList<Integer> tempTree)	//发送树的地图
	{
		for(ServerAgent sa:ulist)
		{
			try
			{
				synchronized(GameData.lock)
				{
					sendStr(sa.dout, "<#GAME_TREE#>");
					sendInt(sa.dout, tempTree.size());
					for(int k=0;k<tempTree.size();k++)
					{
						sendInt(sa.dout, tempTree.get(k));
					}
				}
			}catch(Exception e)
			{
				e.printStackTrace();
			}
		}
	}
	public static void broadcastTank(ArrayList<Integer> tempTank)	//发送敌军坦克的地图
	{
		for(ServerAgent sa:ulist)
		{
			try
			{
				synchronized(GameData.lock)
				{
					sendStr(sa.dout, "<#GAME_OTANK#>");
					sendInt(sa.dout, tempTank.size());
					for(int k=0;k<tempTank.size();k++)
					{
						sendInt(sa.dout, tempTank.get(k));
					}
				}
			}catch(Exception e)
			{
				e.printStackTrace();
			}
		}
	}
	public static void broadcastMissile() 
	{
		for(ServerAgent sa:ulist)
		{
			try
			{
				boolean flag=false;
				if(GameData.redMissileCount==1||GameData.greenMissileCount==1)
				{
					flag=true;
				}
				synchronized(GameData.lock)
				{
					sendStr(sa.dout, "<#GAME_MISSILE#>");
					sendInt(sa.dout, flag?1:0);
					sendInt(sa.dout, GameData.mainMissile.size());
					for(int i=0;i<GameData.mainMissile.size();i++)
					{
						sendFloat(sa.dout, GameData.mainMissile.get(i));
					}
					
				}
			}catch(Exception e)
			{
				e.printStackTrace();
			}
		}
	}
	public static void broadcastBullet()								//子弹
	{
		for(ServerAgent sa:ulist)
		{
			try
			{
				synchronized(GameData.lock)
				{
					sendStr(sa.dout, "<#GAME_BULLET#>");
					sendInt(sa.dout, GameData.redState);
					sendInt(sa.dout, GameData.greenState);
					sendInt(sa.dout, GameData.mainBullet.size());
					for(int i=0;i<GameData.mainBullet.size();i++)
					{
						sendFloat(sa.dout, GameData.mainBullet.get(i));
					}
					
				}
			}catch(Exception e)
			{
				e.printStackTrace();
			}
		}
	}
	public static void broadcastOtherBullet()
	{
		for(ServerAgent sa:ulist)
		{
			try
			{
				synchronized(GameData.lock)
				{
					sendStr(sa.dout, "<#GAME_OTHERBULLET#>");
					sendInt(sa.dout, GameData.otherState);
					sendInt(sa.dout, GameData.otherBullet.size());
					for(int i=0;i<GameData.otherBullet.size();i++)
					{
						sendFloat(sa.dout, GameData.otherBullet.get(i));
					}
					
				}
			}catch(Exception e)
			{
				e.printStackTrace();
			}
			
		}
	}
	
	public static void broadcastTank()
	{
		for(ServerAgent sa:ulist)
		{
			try
			{
				synchronized(GameData.lock)
				{
					sendStr(sa.dout, "<#GAME_TANK#>");
					sendInt(sa.dout, GameData.redX);
					sendInt(sa.dout, GameData.redY);
					sendInt(sa.dout, GameData.greenX);
					sendInt(sa.dout, GameData.greenY);
					sendFloat(sa.dout, GameData.redTankAngle);
					sendFloat(sa.dout, GameData.greenTankAngle);
					sendFloat(sa.dout, GameData.redGunAngle);
					sendFloat(sa.dout, GameData.greenGunAngle);
				}
			}
			catch(Exception e)
			{
				e.printStackTrace();
			}
		}
	}
	
	public static void broadcastBoss()
	{
		for(ServerAgent sa:ulist)
		{
			try
			{
				synchronized(GameData.lock)
				{
					boolean b=(GameData.bossBullet!=null);
					sendStr(sa.dout, "<#GAME_BOSS#>");
					sendInt(sa.dout, GameData.bossNum);
					sendInt(sa.dout, GameData.bossX);
					sendInt(sa.dout, GameData.bossY);
					sendInt(sa.dout, GameData.bossFlag?1:0);
					sendInt(sa.dout, b?1:0);
					if(b)
					{
						int length=GameData.bossBullet.size();
						sendInt(sa.dout, length);
						for(int i=0;i<length;i++)
						{
							sendFloat(sa.dout, GameData.bossBullet.get(i));
						}
					}
				}
			}
			catch(Exception e)
			{
				e.printStackTrace();
			}
		}
	}
	
	public static void broadcastClear() 
	{
		for(ServerAgent sa:ulist)
		{
			try
			{
				synchronized(GameData.lock)
				{
					sendStr(sa.dout, "<#CLEAR#>");
				}
			}
			catch(Exception e)
			{
				//e.printStackTrace();
			}
		}
	}
	public ServerAgent(Socket sc)
	{
		this.sc=sc;
		try
		{
			din=new DataInputStream(sc.getInputStream());
			dout=new DataOutputStream(sc.getOutputStream());
		}
		catch(Exception e)
		{
			//e.printStackTrace();
		}
	}
	
	public ServerAgent(ServerThread st,Socket sc)
	{
		this.sc=sc;
		ServerAgent.st=st;
		try
		{
			din=new DataInputStream(sc.getInputStream());
			dout=new DataOutputStream(sc.getOutputStream());
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
	}
	
	public void run()
	{
		while(flag)
		{
			try
			{
				String msg=readStr(din);
				if(msg.startsWith("<#CONNECT#>"))
				{
//					count++;
					if(count==0)
					{
						sendStr(dout, "<#OK#>");
						redOrGreen=0;
						sendInt(dout, redOrGreen);
						sendInt(dout, GameData.level);
						ulist.add(this);
						count++;
						System.out.println("red connect...");
					}
					else if(count==1)
					{
						sendStr(dout, "<#OK#>");
						redOrGreen=1;
						sendInt(dout, redOrGreen);
						sendInt(dout, GameData.level);
						ulist.add(this);
						count++;
						System.out.println("green connect...");
					}
					else
					{
						sendStr(dout, "<#FULL#>");
						break;
					}
				}
				else if(msg.startsWith("<#SELECT#>"))
				{
					int level=readInt(din);
					System.out.println("level"+level);
					try
					{
						for(ServerAgent sa:ulist)
						{
							synchronized(GameData.lock)
							{
								sendStr(sa.dout, "<#SELECT2#>");
								sendInt(sa.dout, level);
							}
							System.out.println("level----------"+level);
						}
					}
					catch(Exception e)
					{
						e.printStackTrace();
					}
				}
				else if(msg.startsWith("<#LEVEL#>"))
				{
					int level=readInt(din);
					System.out.println("start");
					synchronized(GameData.lock)
					{
						GameData.level=level;
					}
					broadcastData();
					initStart();
				}
				else if(msg.startsWith("<#KEY#>"))
				{
					float leftOffsetX,leftOffsetY,rightOffsetX,rightOffsetY;
					leftOffsetX=readFloat(din);
					leftOffsetY=readFloat(din);
					rightOffsetX=readFloat(din);
					rightOffsetY=readFloat(din);
					MainTank m=new MainTank(redOrGreen,leftOffsetX,leftOffsetY,rightOffsetX,rightOffsetY);
					synchronized(GameData.lock)
					{
						aq.offer(m);
					}
				}
				else if(msg.startsWith("<#STATE#>"))
				{
					int gameState=readInt(din);
					synchronized(GameData.lock)
					{
						GameData.gameState=gameState;
					}
				}else if(msg.startsWith("<#EXIT#>"))
				{
					closeGame();
				}
			}
			catch(Exception e)
			{
				closeGame();
				break;
			}
		}
		try
		{
			din.close();
			dout.close();
			sc.close();
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
	}
	
	public static void closeGame() 
	{
		LevelChange.resetLevel();
		flag=false;
		st.flag=false;
		ulist.clear();
		try 
		{
			st.ss.close();
		} catch (IOException e) 
		{
			e.printStackTrace();
		}
		new ServerThread().start();
	}

	private void initStart() 
	{
		GameData.threadFlag=true;
		new MainBulletThread().start();
		new MainMissileThread().start();
		new OtherBulletThread().start();
		new ExplosionThread().start();
		new MapThread().start();
		new UpdateThread().start();
		LevelChange.changeLevel();
		GameData.gameState=2;
		MainTank m=new MainTank(0,0,0,0,0);
		Action a=new Update(Update.UpdateEnum.date);
		synchronized(GameData.lock)
		{
			aq.offer(m);
			aq.offer(a);
		}
	}

	public static void broadcastVictory() 
	{
		for(ServerAgent sa:ulist)
		{
			try
			{
				synchronized(GameData.lock)
				{
					sendStr(sa.dout, "<#VICTORY#>");
				}
			}
			catch(Exception e)
			{
				//e.printStackTrace();
			}
		}
	}
}