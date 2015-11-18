 package com.bn.server;

import java.io.*;
import java.net.*;
import java.util.ArrayList;

import com.bn.data.GameData;
import com.bn.util.CardDistribution;
import com.bn.util.IOUtil;
import com.bn.util.RuleUtil;
import com.bn.util.CodeChange;

import static com.bn.util.IOUtil.*;

public class ServerAgentThread extends Thread
{
	boolean flag=true;
	Socket sc;
	DataInputStream din;		
	DataOutputStream dout;
	ServerThread st;
	
	String receiveContent;			//服务器收到的内容
	
	public ServerAgentThread(Socket sc,ServerThread st) throws Exception  //收	
	{
		this.sc=sc;
		this.st=st;		
		din=new DataInputStream(sc.getInputStream());
		dout=new DataOutputStream(sc.getOutputStream());
	}
/*	发送给客户端信息
 * 
 */
	public void broadcastConnect()				//发送连接状态  	0
	{
		
		for(int i=0;i<GameData.clientList.size();i++)
		{
			DataOutputStream dout=st.cmap.get(GameData.clientList.get(i)).dout;
			try
			{
				System.out.println("  connect  ....");
				IOUtil.sendInt(dout,0);
				IOUtil.sendInt(dout,GameData.clientList.size());
				for(int j=0;j<GameData.clientList.size();j++)
				{
					IOUtil.sendInt(dout,j);						//发送id
				}
			}
			catch (Exception e) {
				e.printStackTrace();
			}
		}
	}
	
	private void boradcastpreparetState() 		//发送当前准备状态     	1
	{
		for(int i=0;i<GameData.clientList.size();i++)
		{
			DataOutputStream dout=st.cmap.get(GameData.clientList.get(i)).dout;
			try
			{
				IOUtil.sendInt(dout,1);
				IOUtil.sendInt(dout,GameData.prepareState.size());
				for(Integer prepare:GameData.prepareState)
				{
					IOUtil.sendInt(dout,prepare);
				}
			}
			catch (Exception e) {
				e.printStackTrace();
			}
		}

	}
	
	private void broadcastStart() 				//开始游戏  发送牌给玩家		2
	{
		//发送状态
		GameData.landlordState=new int[3];
		GameData.landlordState[0]=4;
		GameData.landlordState[1]=4;
		GameData.landlordState[2]=4;
		
		//服务器转换成 客户端代号
		int client1[]=new int[GameData.client1.length];
		int client2[]=new int[GameData.client2.length];
		int client3[]=new int[GameData.client3.length];


		for(int i=0;i<GameData.client1.length;i++)
		{
			client1[i]=GameData.client1[i];
		}
		
		for(int i=0;i<GameData.client2.length;i++)
		{
			client2[i]=GameData.client2[i];
		}
		
		for(int i=0;i<GameData.client3.length;i++)
		{
			client3[i]=GameData.client3[i];
		}
		//转化服务器ID到客户端的ID
		client1=CodeChange.serverChangeclient(client1);	
		client2=CodeChange.serverChangeclient(client2);	
		client3=CodeChange.serverChangeclient(client3);
		
		System.out.println(" 发牌  ....  ");
		for(int i=0;i<3;i++)
		{
			DataOutputStream dout=st.cmap.get(GameData.clientList.get(i)).dout;
			try
			{
				IOUtil.sendInt(dout, 2);
				IOUtil.sendInt(dout, 17);
				for(int j=0;j<17;j++)
				{
					if(i==0)
					{
						IOUtil.sendInt(dout,client1[j]);
					}else if(i==1)
					{
						IOUtil.sendInt(dout,client2[j]);
					}else if(i==2)
					{
						IOUtil.sendInt(dout,client3[j]);
					}
				}
			}
			catch (Exception e)
			{
				e.printStackTrace();
			}
		}
	}
	
	private void broadcastSelectLandlord() 		//选地主的状态, 轮到谁选地主	3
	{
		int landlord=GameData.landlord;
		for(int i=0;i<3;i++)
		{
			DataOutputStream dout=st.cmap.get(GameData.clientList.get(i)).dout;
			try
			{
				IOUtil.sendInt(dout, 3);
				IOUtil.sendInt(dout,landlord);
				IOUtil.sendInt(dout,GameData.multiple);
				IOUtil.sendInt(dout, 3);
				
				for(int j=0;j<3;j++)				//发送玩家的叫地主状态
				{
					if(landlord==j)
					{
						IOUtil.sendInt(dout,4);
						continue;
					}
					IOUtil.sendInt(dout, GameData.landlordState[j]);
				}
				
				
			}
			catch (Exception e) {
				e.printStackTrace();
			}
		}
	}
	
	private void broadcastLandLord()			//初始地主		4
	{
		int landlord=GameData.landlord;			//地主
		
		int client1[]=new int[GameData.client1.length];
		int client2[]=new int[GameData.client2.length];
		int client3[]=new int[GameData.client3.length];
		int endCard[]=new int[3];

		for(int i=0;i<GameData.client1.length;i++)
		{
			client1[i]=GameData.client1[i];
		}
		
		for(int i=0;i<GameData.client2.length;i++)
		{
			client2[i]=GameData.client2[i];
		}
		
		for(int i=0;i<GameData.client3.length;i++)
		{
			client3[i]=GameData.client3[i];
		}
		
		for(int i=0;i<GameData.endCard.length;i++)
		{
			endCard[i]=GameData.endCard[i];
		}
		
		//转换成客户端的扑克编号
		client1=CodeChange.serverChangeclient(client1);	
		client2=CodeChange.serverChangeclient(client2);	
		client3=CodeChange.serverChangeclient(client3);
		endCard=CodeChange.serverChangeclient(endCard);
		
		for(int i=0;i<3;i++)
		{
			DataOutputStream dout=st.cmap.get(GameData.clientList.get(i)).dout;
			try
			{
				IOUtil.sendInt(dout,4);				// 
				IOUtil.sendInt(dout,landlord);		//	地主id
				IOUtil.sendInt(dout, GameData.multiple);//倍数
				IOUtil.sendInt(dout, 20);		//发送 20作为 地主牌的标志
				for(int j=0;j<20;j++)			//发送20张底牌		
				{
					if(landlord==0)
					{
						IOUtil.sendInt(dout,client1[j]);
					}else if(landlord==1)
					{
						IOUtil.sendInt(dout,client2[j]);
					}else if(landlord==2)
					{
						IOUtil.sendInt(dout,client3[j]);
					}
				}
				IOUtil.sendInt(dout,3);				//发送3作为底牌的标志
				
				for(int j=0;j<3;j++)				//发送3张底牌的值
				{
					IOUtil.sendInt(dout, endCard[j]);
				}
			}
			catch (Exception e) 
			{
				e.printStackTrace();
			}
		}
	}
	private void broadcastCanLandlord() 		//发5   给所用人  现在的牌权   告诉它可以出牌
	{
		int ownCard=GameData.ownCard;
		for(int i=0;i<3;i++)
		{
			DataOutputStream dout=st.cmap.get(GameData.clientList.get(i)).dout;
			if(i==ownCard)
			{
				try
				{
					IOUtil.sendInt(dout, 5);
					IOUtil.sendInt(dout,ownCard);
					IOUtil.sendInt(dout,GameData.ownState);			//出不出的状态  1chu
				}
				catch (Exception e) {
					e.printStackTrace();
				}
			}
		}
			
	}
	private void broadcastCardLandlord() 		//发6  给所用人  现在的牌权  倍数   可不可不出牌,每家的牌的剩余量  告诉每家出的牌的个数   	以及牌的索引  
	{
		int ownCard=GameData.ownCard;			//当前拥有牌权的玩家ID
		for(int i=0;i<3;i++)
		{
			DataOutputStream dout=st.cmap.get(GameData.clientList.get(i)).dout;
			try
			{
				IOUtil.sendInt(dout, 6);
				IOUtil.sendInt(dout,ownCard);				//牌权
				IOUtil.sendInt(dout,GameData.multiple);		//倍数
				
				IOUtil.sendInt(dout, GameData.effect_Row);	//发送音效的二维数组
				IOUtil.sendInt(dout, GameData.effect_Col);

				IOUtil.sendInt(dout,GameData.round);		//如果 1可以不出  0必须出
				IOUtil.sendInt(dout, 1);			//标志位	玩家牌的个数
				IOUtil.sendInt(dout, GameData.client1.length);
				IOUtil.sendInt(dout, GameData.client2.length);
				IOUtil.sendInt(dout, GameData.client3.length);
				
				
				
				int client1[]=new int[GameData.client1.length];			//发送玩家剩余的牌的ID
				int client2[]=new int[GameData.client2.length];
				int client3[]=new int[GameData.client3.length];
				
				for(int j=0;j<GameData.client1.length;j++)
				{
					client1[j]=GameData.client1[j];
				}
				
				for(int j=0;j<GameData.client2.length;j++)
				{
					client2[j]=GameData.client2[j];
				}
				
				for(int j=0;j<GameData.client3.length;j++)
				{
					client3[j]=GameData.client3[j];
				}
				
			//	转换成客户端的扑克编号
				client1=CodeChange.serverChangeclient(client1);	
				client2=CodeChange.serverChangeclient(client2);	
				client3=CodeChange.serverChangeclient(client3);
				//发送 每位玩家剩余的牌
				if(i==0)
				{
					IOUtil.sendInt(dout,GameData.client1.length);
					for(int z=0;z<GameData.client1.length;z++)
					{
						IOUtil.sendInt(dout,client1[z]);
					}
				}else if(i==1)
				{
					IOUtil.sendInt(dout,GameData.client2.length);
					for(int z=0;z<GameData.client2.length;z++)
					{
						IOUtil.sendInt(dout,client2[z]);
					}
				}else if(i==2)
				{
					IOUtil.sendInt(dout,GameData.client3.length);
					for(int z=0;z<GameData.client3.length;z++)
					{
						IOUtil.sendInt(dout,client3[z]);
					}
				}
				
				if(GameData.card1Sort!=100&&ownCard!=0)					//当玩家1的状态不为100，发送玩家的现在出牌的个数，以及牌的id
				{
					IOUtil.sendInt(dout,0);
					IOUtil.sendInt(dout, GameData.cardId1.length);
					
					int client[]=new int[GameData.cardId1.length];


					for(int n=0;n<GameData.cardId1.length;n++)
					{
						client[n]=GameData.cardId1[n];
					}
					//转化服务器ID到客户端的ID
					client=CodeChange.serverChangeclient(client);	
					for(int j=0;j<GameData.cardId1.length;j++)
					{
						IOUtil.sendInt(dout, client[j]);
					}
				}else 
				{
					IOUtil.sendInt(dout, 100);
				}
				
				if(GameData.card2Sort!=100&&ownCard!=1)					//当玩家2的状态不为100，发送玩家的现在出牌的个数，以及牌的id
				{
					IOUtil.sendInt(dout,1);
					IOUtil.sendInt(dout, GameData.cardId2.length);
					
					int client[]=new int[GameData.cardId2.length];

					for(int n=0;n<GameData.cardId2.length;n++)
					{
						client[n]=GameData.cardId2[n];
					}
					//转化服务器ID到客户端的ID
					client=CodeChange.serverChangeclient(client);	
					
					for(int j=0;j<GameData.cardId2.length;j++)
					{
						IOUtil.sendInt(dout, client[j]);
					}
				}else 
				{
					IOUtil.sendInt(dout, 100);
				}
				
				if(GameData.card3Sort!=100&&ownCard!=2)					//当玩家3的状态不为100，发送玩家的现在出牌的个数，以及牌的id
				{
					IOUtil.sendInt(dout,2);
					IOUtil.sendInt(dout, GameData.cardId3.length);
					
					int client[]=new int[GameData.cardId3.length];
					int card3Length=GameData.cardId3.length;
					for(int n=0;n<card3Length;n++)
					{
						client[n]=GameData.cardId3[n];
					}
					//转化服务器ID到客户端的ID
					client=CodeChange.serverChangeclient(client);	
					for(int j=0;j<GameData.cardId3.length;j++)
					{
						IOUtil.sendInt(dout, client[j]);
					}
				}else 
				{
					IOUtil.sendInt(dout, 100);
				}
			}
			catch (Exception e) {
				e.printStackTrace();
			}
		}
	}
	private void broadcastPrompt(int Prompt,int[] newCards)		//发送提示	发送7
	{
		if(newCards==null)
		{
			return; 
		}
		int ownCard=GameData.ownCard;
		newCards=CodeChange.serverChangeclient(newCards);
		for(int i=0;i<3;i++)
		{
			DataOutputStream dout=st.cmap.get(GameData.clientList.get(i)).dout;
			try
			{
				
				if(ownCard==i)
				{
					IOUtil.sendInt(dout, 7);				//标志位 7
					if(Prompt==1)					// 有提示
					{
						IOUtil.sendInt(dout, 1);
						
						int length=newCards.length;
						IOUtil.sendInt(dout,length);
						for(int j=0;j<length;j++)
						{
							IOUtil.sendInt(dout, newCards[j]);
						}
					}else							//没有提示
					{
						IOUtil.sendInt(dout, 0);
					}
				}
			}
			catch (Exception e) {
				e.printStackTrace();
			}
		}
	}
	private void broadcastVictoryLandlord() 		//发8 游戏结束	
	{
		int ownCard=GameData.ownCard;			//当前拥有牌权的玩家ID
		int victory=-1;							//是地主胜利，还是农民胜利
		if(ownCard==GameData.landlord)			
		{	
			victory=1;							//地主胜利
		}else
		{
			victory=0;							//农民胜利
		}
		for(int i=0;i<3;i++)
		{
			DataOutputStream dout=st.cmap.get(GameData.clientList.get(i)).dout;
			try
			{
				IOUtil.sendInt(dout, 8);
				IOUtil.sendInt(dout,ownCard);			//谁出去了
				IOUtil.sendInt(dout,victory);			//
				IOUtil.sendInt(dout,GameData.multiple);		//倍数
				
				IOUtil.sendInt(dout, GameData.effect_Row);	//发送音效的二维数组
				IOUtil.sendInt(dout, GameData.effect_Col);
				
				IOUtil.sendInt(dout, 1);			//标志位	玩家牌的个数
				IOUtil.sendInt(dout, GameData.client1.length);
				IOUtil.sendInt(dout, GameData.client2.length);
				IOUtil.sendInt(dout, GameData.client3.length);
				
				int client1[]=new int[GameData.client1.length];			//发送玩家剩余的牌的ID
				int client2[]=new int[GameData.client2.length];
				int client3[]=new int[GameData.client3.length];
				
				for(int j=0;j<GameData.client1.length;j++)
				{
					client1[j]=GameData.client1[j];
				}
				
				for(int j=0;j<GameData.client2.length;j++)
				{
					client2[j]=GameData.client2[j];
				}
				
				for(int j=0;j<GameData.client3.length;j++)
				{
					client3[j]=GameData.client3[j];
				}
				
			//	转换成客户端的扑克编号
				client1=CodeChange.serverChangeclient(client1);	
				client2=CodeChange.serverChangeclient(client2);	
				client3=CodeChange.serverChangeclient(client3);
				//发送 每位玩家剩余的牌
				if(i==0)
				{
					IOUtil.sendInt(dout,GameData.client1.length);
					for(int z=0;z<GameData.client1.length;z++)
					{
						IOUtil.sendInt(dout,client1[z]);
					}
				}else if(i==1)
				{
					IOUtil.sendInt(dout,GameData.client2.length);
					for(int z=0;z<GameData.client2.length;z++)
					{
						IOUtil.sendInt(dout,client2[z]);
					}
				}else if(i==2)
				{
					IOUtil.sendInt(dout,GameData.client3.length);
					for(int z=0;z<GameData.client3.length;z++)
					{
						IOUtil.sendInt(dout,client3[z]);
					}
				}
				
				if(GameData.card1Sort!=100&&ownCard!=0)					//当玩家1的状态不为100，发送玩家的现在出牌的个数，以及牌的id
				{
					IOUtil.sendInt(dout,0);
					IOUtil.sendInt(dout, GameData.cardId1.length);
					
					int client[]=new int[GameData.cardId1.length];


					for(int n=0;n<GameData.cardId1.length;n++)
					{
						client[n]=GameData.cardId1[n];
					}
					//转化服务器ID到客户端的ID
					client=CodeChange.serverChangeclient(client);	
					for(int j=0;j<GameData.cardId1.length;j++)
					{
						IOUtil.sendInt(dout, client[j]);
					}
				}else 
				{
					IOUtil.sendInt(dout, 100);
				}
				
				if(GameData.card2Sort!=100&&ownCard!=1)					//当玩家2的状态不为100，发送玩家的现在出牌的个数，以及牌的id
				{
					IOUtil.sendInt(dout,1);
					IOUtil.sendInt(dout, GameData.cardId2.length);
					
					int client[]=new int[GameData.cardId2.length];

					for(int n=0;n<GameData.cardId2.length;n++)
					{
						client[n]=GameData.cardId2[n];
					}
					//转化服务器ID到客户端的ID
					client=CodeChange.serverChangeclient(client);	
					
					for(int j=0;j<GameData.cardId2.length;j++)
					{
						IOUtil.sendInt(dout, client[j]);
					}
				}else 
				{
					IOUtil.sendInt(dout, 100);
				}
				
				if(GameData.card3Sort!=100&&ownCard!=2)					//当玩家3的状态不为100，发送玩家的现在出牌的个数，以及牌的id
				{
					IOUtil.sendInt(dout,2);
					IOUtil.sendInt(dout, GameData.cardId3.length);
					
					int client[]=new int[GameData.cardId3.length];
					int card3Length=GameData.cardId3.length;
					for(int n=0;n<card3Length;n++)
					{
						client[n]=GameData.cardId3[n];
					}
					//转化服务器ID到客户端的ID
					client=CodeChange.serverChangeclient(client);	
					for(int j=0;j<GameData.cardId3.length;j++)
					{
						IOUtil.sendInt(dout, client[j]);
					}
				}else 
				{
					IOUtil.sendInt(dout, 100);
				}
			}
			catch (Exception e) {
				e.printStackTrace();
			}
		}
	}
/*收到客户端的信息
 * code=0	
 */
	/* (non-Javadoc)
	 * @see java.lang.Thread#run()
	 */
	/* (non-Javadoc)
	 * @see java.lang.Thread#run()
	 */
	public void run()
	{
		while(flag)
		{
			try
			{
				//每一轮先接收标志位整数   0-准备状态  1-叫地主    2-表示字符串
				int code=readInt(din);
				if(code==0)									
				{
					
					int count=++GameData.prepareCount;
					System.out.println(" 已经有 "+count+" 个玩家准备... ");
					
					GameData.prepareState.add(getAddressIndex());
					
					if(GameData.prepareCount<=2)
					{
							boradcastpreparetState();			//发送当前准备状态
					}
					
					if(GameData.prepareCount==3)
					{
						broadcastStart();			//开始游戏  发送牌给玩家	2
					//	GameData.landlord=(int)(Math.random()*2);		//随机选一个玩家去先选地主
						GameData.landlord=2;
						Thread.sleep(2000);
						broadcastSelectLandlord();
					}
					if(GameData.prepareCount==2)			//如果有3位玩家连接游戏后，开始分配扑克牌
					{
						//分牌   排序
						CardDistribution.startCard();   
					}
					
				}
				else if(code==1)										//data=1叫地主，data=0 不叫   
				{
					
					int data=readInt(din);								
					int index=getAddressIndex();
					GameData.landlordCount++;
					
					if(GameData.landlordCount==1)
					{
						GameData.landlordState[index]=data;
					}else 
					{
						GameData.landlordState[index]=data+2;
					}
					//把每个人叫地主的状态存到数组中
					
					if(data==1&&GameData.landlordCount!=4)
					{
						GameData.landlordList.add(index);				//添加进叫 地主的列表
						GameData.landlord=((index)/2==1)?0:(index+1);	//下一位
						if(GameData.landlordCount!=1)
						{
							GameData.multiple=GameData.multiple*2;
						}
					}else if(data==0&&GameData.landlordCount!=4)
					{
						GameData.landlordList.add(index);				//添加进叫 地主的列表
						GameData.landlord=((index)/2==1)?0:(index+1);	//下一位
					}
					
					if(GameData.landlordCount==4)						//最后一轮抢地主
					{
						if(data==0)
						{
							GameData.landlord=GameData.landlordList.get(GameData.landlordList.size()-1);
						}else
						{
							GameData.multiple=GameData.multiple*2;
						}
						//设置当前牌权
						GameData.ownCard=GameData.landlord;
						CardDistribution.landlordCardChange();									//给地主重新分配20张牌
						broadcastSelectLandlord();						//选择地主
						Thread.sleep(1000);
						broadcastLandLord();	
						Thread.sleep(1000);//开牌
						continue;
					}else if(GameData.landlordCount==3)					//每位玩家都选择完后
					{
						if(GameData.landlordList.size()>1)				//如果有1个以上的玩家叫地主后
						{
							GameData.landlord=GameData.landlordList.get(0);//最后一次机会给第一个叫地主的玩家
							broadcastSelectLandlord();					//选择地主
						}else if(GameData.landlordList.size()==1)
						{
							GameData.landlord=GameData.landlordList.get(0);//最后一次机会给第一个叫地主的玩家
							CardDistribution.landlordCardChange();								//给地主重新分配20张牌
							broadcastSelectLandlord();						//选择地主
							GameData.ownCard=GameData.landlord;			//把地主设置成当前的牌权
							broadcastLandLord();						//开牌
						}
						continue;
					}
					
					if(GameData.landlordCount<3)
					{
						broadcastSelectLandlord();						//选择地主
					}
					
				}
				else if(code==2)						//要出牌个数 和 扑克牌的 id   判断能不出牌playCard()
				{
					int index=getAddressIndex();		//要出牌玩家的ID
					//接收要出牌的个数
					int cardNum=IOUtil.readInt(din);
					if(cardNum!=0)						
					{
						//定义要出牌的数组
						int[] cardIndex=new int[cardNum];
						//接收要出的扑克牌ID
						for(int i=0;i<cardNum;i++)
						{
							cardIndex[i]=IOUtil.readInt(din);
						}
						
						//把收来的牌代码转换到服务器端
						CodeChange.clientChangeserver(cardIndex);
						//判断是否能出牌
						int sort=RuleUtil.ruleSelf(cardIndex);
						int lastSort=CardDistribution.getLastCardSort(index);
						int nextSort=CardDistribution.getNextCardSort(index);
						if(sort!=100)								// 如果本身布复合出牌类型
						{
							if(lastSort==100&&nextSort==100)
							{
								GameData.ownState=1;		//可以出牌
								int finish=CardDistribution.saveCardtoData(index,sort,cardIndex);	//存入牌到数据中
								
								if(finish==1)																						//????????????????????
								{
									broadcastCanLandlord();		//发送5  告诉玩家可以出牌
								}
								continue;
							}else if(lastSort!=100)				//如果上一家已经出牌，
							{
								int result=RuleUtil.CARD_ROW_COL[lastSort][sort];
								if(result==0)		//可以出牌
								{
									GameData.ownState=1;		//可以出牌
									CardDistribution.saveCardtoData(index,sort,cardIndex);	//存入牌到数据中
									broadcastCanLandlord();		//发送5  告诉玩家可以出牌
									continue;
								}else if(result==1)				//不可以出牌
								{
									GameData.ownState=0;		// 不可以出牌
									broadcastCanLandlord();		//发送5  告诉玩家不可以出牌
									continue;
								}else if(result==2)				//待定
								{
									int[] lastCard=CardDistribution.getLastCard(index);		//获取上一家牌
									boolean bb=RuleUtil.isrule(sort,lastCard, cardIndex);	//判断本家能否管上上一家牌
									if(bb)
									{
										GameData.ownState=1;		//可以出牌
									}else
									{
										GameData.ownState=0;		// 不可以出牌
									}
									
									CardDistribution.saveCardtoData(index,sort,cardIndex);	//存入牌到数据中
									broadcastCanLandlord();		//发送5  告诉玩家可以出牌
									continue;
								}
							}else if(lastSort==100&&nextSort!=100)		// 下一家没出牌		
							{
								int result=RuleUtil.CARD_ROW_COL[nextSort][sort];
								if(result==0)		//可以出牌
								{
									GameData.ownState=1;		//可以出牌
									CardDistribution.saveCardtoData(index,sort,cardIndex);	//存入牌到数据中
									broadcastCanLandlord();		//发送5  告诉玩家可以出牌
									continue;
								}else if(result==1)				//不可以出牌
								{
									GameData.ownState=0;		// 不可以出牌
									broadcastCanLandlord();		//发送5  告诉玩家不可以出牌
									continue;
								}else if(result==2)				//待定
								{
									int[] nextCard=CardDistribution.getNextCard(index);		//获取上一家牌
									boolean bb=RuleUtil.isrule(sort,nextCard, cardIndex);	//判断本家能否管上上一家牌
									if(bb)
									{
										GameData.ownState=1;		//可以出牌
									}else
									{
										GameData.ownState=0;		// 不可以出牌
									}
									
									CardDistribution.saveCardtoData(index,sort,cardIndex);	//存入牌到数据中
									broadcastCanLandlord();	//发送5  告诉玩家可以出牌
									continue;
								}
							}
						}else 								//如果本身布符合出牌类型
						{
							GameData.ownState=0;			
							broadcastCanLandlord();		//发送5  告诉玩家不可以出牌
							continue;
						}
					}
				}else if(code==3)		//如果收到 3，则出牌 发送6
				{
					//是否出牌
					int isChuPai=IOUtil.readInt(din);
					
					int index=getAddressIndex();				//要出牌玩家的ID
					if(isChuPai==1)
					{
						int length=CardDistribution.deleteCards(index);		//获取剩下牌的数量
						if(length==0)
						{
							int sort=CardDistribution.getCardSort(index);
							int []playsort=CardDistribution.getPlayerCard(index);	//获取本家牌
							CardDistribution.saveEffect(sort,playsort);	
							if(sort==33||sort==34){			//炸弹
								GameData.multiple=GameData.multiple*2;
							}
							broadcastVictoryLandlord();						//胜利
							dataReset();
							continue;
						}else
						{
							int sort=CardDistribution.getCardSort(index);
							int []playsort=CardDistribution.getPlayerCard(index);
							CardDistribution.saveEffect(sort,playsort);	
							if(sort==33||sort==34)
							{
								GameData.multiple=GameData.multiple*2;
							}
						}
												//存音效
					}else
					{
						GameData.noCount++;
						if(GameData.noCount==2)
						{
							GameData.round=0;		//下一次牌权不能不出
						}
						//不出牌，把本家牌清空、
						if(index==0)
						{
							GameData.card1Sort=100;
						}else if(index==1)
						{
							GameData.card2Sort=100;
						}else if(index==2)
						{
							GameData.card3Sort=100;
						}
						GameData.effect_Row=3;
						GameData.effect_Col=9;
					}
					//下一家出牌
					
					GameData.ownCard=GameData.ownCard==2?0:GameData.ownCard+1;	//牌权
					broadcastCardLandlord();	//发送谁哪位玩家出牌了
					//更新状态
					GameData.noCount=0;
					GameData.round=1;			//下一次可以不出牌
				}
				else if(code==4)				//提示
				{
					int index=getAddressIndex();
					//如果发过来牌的个数为0，则为提示
					int lastSort=CardDistribution.getLastCardSort(index);
					int nextSort=CardDistribution.getNextCardSort(index);
					int playerCards[]=CardDistribution.getPlayerCardClient(index);
					int []newCards=null;	
					if(lastSort==100&&nextSort==100)		//上两家没有出牌
					{
						newCards=CardDistribution.getNewCards(playerCards);
						if(newCards==null)
						{
							int []a={};
							broadcastPrompt(0,a);
						}else
						{
							int sort=RuleUtil.ruleSelf(newCards);
							CardDistribution.saveCardtoData(index,sort,newCards);	//存入牌到数据中
							broadcastPrompt(1,newCards);
						}
					}else if(lastSort!=100)					// 上一家有出牌
					{
						newCards=RuleUtil.getCompareCards(index,0,playerCards);
						int sort=RuleUtil.ruleSelf(newCards);
						CardDistribution.saveCardtoData(index,sort,newCards);	//存入牌到数据中
						broadcastPrompt(1,newCards);
					}else if(lastSort==100&&nextSort!=100)	//上一家没有出牌，下一家有出牌 
					{
						newCards=RuleUtil.getCompareCards(index,1,playerCards);
						int sort=RuleUtil.ruleSelf(newCards);
						CardDistribution.saveCardtoData(index,sort,newCards);	//存入牌到数据中
						broadcastPrompt(1,newCards);
					}
				}
				else if(code==100)
				{
					String data=readStr(din);
					receiveContent=receiveContent+"收到字符串："+data+"\n";
					//若收到的字符串是退出指令
					if(data.trim().equals("<#EXIT#>"))
					{
						flag=false;
						String address=sc.getInetAddress().toString().trim();	//获取退出的IP地址
						st.cmap.remove(address);								//从map中删除IP
//						st.clientIP.clear();
//						
//						Set<String> ks=st.cmap.keySet();
//						for(String key:ks)
//						{
//							st.clientIP.add(key);
//						}						
					}
				}
			}
			catch(Exception e)
			{
				e.printStackTrace();
				break;
			}
		}		
	}
	
	private void dataReset()
	{
		GameData.multiple=15;
		GameData.round=1;
		GameData.prepareCount=0;
		GameData.card1Sort=100;
		GameData.card2Sort=100;
		GameData.card3Sort=100;
		GameData.landlordCount=0;
		GameData.landlordState=null;
		GameData.client1=null;
		GameData.client2=null;
		GameData.client3=null;
		GameData.endCard=null;
		GameData.endIndex=null;
		GameData.cardId1=null;
		GameData.cardId2=null;
		GameData.cardId3=null;
		GameData.prepareState.clear();
		GameData.landlordList.clear();
		GameData.num=0;
		GameData.ownCard=-1;
		GameData.ownState=0;
		GameData.noCount=0;
	}
	private int getAddressIndex() 						//获取地址的索引
	{
		String address=sc.getInetAddress().toString().trim();
		
		for(int i=0;i<GameData.clientList.size();i++)
		{
			if(GameData.clientList.get(i).equals(address))
			{
				return i;
			}
		}
		return 0;
	}
	
	/**
	 * @param args
	 */
	public static void main(String args[])
	{
		int landlord=GameData.landlord=1;
		CardDistribution.startCard();
		CardDistribution.landlordCardChange();
		
		int client1[]=new int[GameData.client1.length];
		int client2[]=new int[GameData.client2.length];
		int client3[]=new int[GameData.client3.length];
		int endCard[]=new int[3];

		for(int i=0;i<GameData.client1.length;i++)
		{
			client1[i]=GameData.client1[i];
		}
		
		for(int i=0;i<GameData.client2.length;i++)
		{
			client2[i]=GameData.client2[i];
		}
		
		for(int i=0;i<GameData.client3.length;i++)
		{
			client3[i]=GameData.client3[i];
		}
		
		for(int i=0;i<GameData.endCard.length;i++)
		{
			endCard[i]=GameData.endCard[i];
		}
		
		
		client1=CodeChange.serverChangeclient(client1);	
		client2=CodeChange.serverChangeclient(client2);	
		client3=CodeChange.serverChangeclient(client3);
		endCard=CodeChange.serverChangeclient(endCard);
		
		ArrayList<Integer> ForeCardList=new ArrayList<Integer>();
		int a[]={1,2,3,4,5,6,7,8,9};
		for(int i=0;i<a.length;i++)
		{
			ForeCardList.add(a[i]);
		}
		
		int temp[]={3,4};
		
		for(int i=0;i<ForeCardList.size();i++)
		{
			for(int j=0;j<temp.length;j++)
			{
				if(temp[j]==ForeCardList.get(i))
				{
					ForeCardList.remove(i);
				}
			}
		
		}
		try 
		{
			Thread.sleep(100);
		} catch (InterruptedException e) 
		{
			e.printStackTrace();
		}
	}
	

}
