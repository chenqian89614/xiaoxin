package com.bn.util;

import java.util.ArrayList;

import com.bn.data.GameData;

public class CardDistribution
{
	//随机分发54张扑克牌 3个17张 ，1个3张
	public static  void startCard()
	{
		GameData.client1=new int[17];
		GameData.client2=new int[17];
		GameData.client3=new int[17];
		GameData.endCard=new int[3];
		
		ArrayList<Integer> tempList=new ArrayList<Integer>();	//随机分配扑克pai
		int tempInt;
		while(tempList.size()<54)				
		{
			tempInt=(int)(Math.random()*54);
			if(!tempList.contains(tempInt))
			{
				tempList.add(tempInt);
			}
		}
		
		for(int i=0;i<54;i++)				
		{
			if(i<17)
			{
				GameData.client1[i]=tempList.get(i);
			}else if(i>=17&&i<34)
			{
				GameData.client2[i-17]=tempList.get(i);
			}else if(i>=34&&i<51)
			{
				GameData.client3[i-34]=tempList.get(i);
			}else 
			{
				GameData.endCard[i-51]=tempList.get(i);
			}
		}
		
		//排序
		selectSort(GameData.client1);
		selectSort(GameData.client2);
		selectSort(GameData.client3);
		selectSort(GameData.endCard);
	}
	public static int saveCardtoData(int index,int sort,int card[])	//把收到的牌存到数据库中
	{
		if(card==null)
		{
			return 0;
		}
		if(index==0)
		{
			GameData.card1Sort=sort;
			GameData.cardId1=new int[card.length];
		}else if(index==1)
		{
			GameData.card2Sort=sort;
			GameData.cardId2=new int[card.length];
		}else if(index==2)
		{
			GameData.card3Sort=sort;
			GameData.cardId3=new int[card.length];
		}
		
		for(int i=0;i<card.length;i++)
		{
			if(index==0)
			{
				GameData.cardId1[i]=card[i];
			}else if(index==1)
			{
				GameData.cardId2[i]=card[i];
			}else if(index==2)
			{
				GameData.cardId3[i]=card[i];
			}
		}
		return 1;
	}
	
	public static void landlordCardChange() 	//给地主重新分配扑克牌			
	{
		int landlord=GameData.landlord;
		int landlordAfter[]=new int[20];		//分配地主后的牌
		
		if(landlord==0)							//玩家1
		{
			for(int i=0;i<20;i++)
			{
				if(i<17)
				{
					landlordAfter[i]=GameData.client1[i];
				}else
				{
					landlordAfter[i]=GameData.endCard[i-17];
				}
			}
		}else if(landlord==1)					//玩家2
		{
			for(int i=0;i<20;i++)
			{
				if(i<17)
				{
					landlordAfter[i]=GameData.client2[i];
				}else
				{
					landlordAfter[i]=GameData.endCard[i-17];
				}
			}
		}else if(landlord==2)					//玩家3
		{
			for(int i=0;i<20;i++)
			{
				if(i<17)
				{
					landlordAfter[i]=GameData.client3[i];
				}else
				{
					landlordAfter[i]=GameData.endCard[i-17];
				}
			}
		}
		
		selectSort(landlordAfter);
		
		//赋值
		if(landlord==0)							//玩家1
		{
			GameData.client1=new int[20];
			for(int i=0;i<20;i++)
			{
				GameData.client1[i]=landlordAfter[i];
			}
		}else if(landlord==1)					//玩家2
		{
			GameData.client2=new int[20];
			for(int i=0;i<20;i++)
			{
				GameData.client2[i]=landlordAfter[i];
			}
		}else if(landlord==2)					//玩家3
		{
			GameData.client3=new int[20];
			for(int i=0;i<20;i++)
			{
				GameData.client3[i]=landlordAfter[i];
			}
		}
	}
	private static  int[] selectSort(int client[]) 					//扑克牌排序  选择排序
	{
		for(int i=0;i<client.length-1;i++)
		{
			int max=i;
			if(i==0&&(client[i]==53||client[0]==52))
			{
				continue;
			}
			for(int j=i+1;j<client.length;j++)
			{
				if(client[j]==52||client[j]==53)					//大小王 直接换位置
				{
					max=j;
					break;
				}
				if(client[max]%13<client[j]%13)
				{
					max=j;
				}
				else if(client[max]%13==client[j]%13)
				{
					if(client[max]/13<client[j]/13)
					{
						max=j;
					}
				}
			}
			if(max!=i)
			{
				int temp=client[i];
				client[i]=client[max];
				client[max]=temp;
			}
		}
		if(client[0]==52&&client[1]==53)
		{
			client[0]=53;
			client[1]=52;
		}else if(client[0]!=52&&client[0]!=53&&(client[1]==52||client[1]==53))
		{
			int temp=client[0];
			client[0]=client[1];
			client[1]=temp;
		}
		
		int dawang=0;
		for(int i=1;i<client.length;i++)
		{
			if(client[i]==53)
			{
				dawang=i;
				break;
			}
		}
		for(int i=dawang;i>0;i--)
		{
			client[i]=client[i-1];
		}
		if(dawang!=0)
		{
			client[0]=53;
		}
		
		
		int xiaowangId=0;
		for(int i=1;i<client.length;i++)
		{
			if(client[i]==52)
			{
				xiaowangId=i;
				break;
			}
		}
		if(xiaowangId!=0)
		{
			if(client[0]==53)
			{
				for(int i=xiaowangId;i>1;i--)
				{
					client[i]=client[i-1];
				}
				client[1]=52;
			}
		}
		
		return client;
		
	}
	public static int deleteCards(int index) 
	{
		int tempArray[] = null;		//要出的牌的列表
		ArrayList<Integer> tempDelete=new ArrayList<Integer>();
		ArrayList<Integer> ForeCardList=new ArrayList<Integer>();
		if(index==0)
		{
			tempArray=new int[GameData.cardId1.length];
			for(int i=0;i<GameData.cardId1.length;i++)
			{
				tempArray[i]=GameData.cardId1[i];
			}
			for(int i=0;i<GameData.client1.length;i++)
			{
				ForeCardList.add(GameData.client1[i]);
			}
		}else if(index==1)
		{
			tempArray=new int[GameData.cardId2.length];
			for(int i=0;i<GameData.cardId2.length;i++)
			{
				tempArray[i]=GameData.cardId2[i];
			}
			
			for(int i=0;i<GameData.client2.length;i++)
			{
				ForeCardList.add(GameData.client2[i]);
			}
		}else if(index==2)
		{
			tempArray=new int[GameData.cardId3.length];
			for(int i=0;i<GameData.cardId3.length;i++)
			{
				tempArray[i]=GameData.cardId3[i];
			}
			
			for(int i=0;i<GameData.client3.length;i++)
			{
				ForeCardList.add(GameData.client3[i]);
			}
		}
		for(int i=0;i<ForeCardList.size();i++){		//遍历两个列表
			for(int j=0;j<tempArray.length;j++){
				if(tempArray[j]==ForeCardList.get(i)){	//如果有相等的，则需要添加到删除列表中
					tempDelete.add(tempArray[j]);
				}
			}
		}
		//删除扑克列表
		for(int i=0;i<tempDelete.size();i++)
		{
			ForeCardList.remove(tempDelete.get(i));
		}
		
		int length=ForeCardList.size();
		if(index==0)
		{
			GameData.client1=new int[length];
			for(int i=0;i<length;i++)
			{
				GameData.client1[i]=ForeCardList.get(i);
			}
		}else if(index==1)
		{
			GameData.client2=new int[length];
			for(int i=0;i<length;i++)
			{
				GameData.client2[i]=ForeCardList.get(i);
			}
		}else if(index==2)
		{
			GameData.client3=new int[length];
			for(int i=0;i<length;i++)
			{
				GameData.client3[i]=ForeCardList.get(i);
			}
		}
		return length;
	}	
	//获取本家牌
	public static int[] getPlayerCard(int index)
	{
		int playerCard[] = null;
		switch(index)
		{
			case 0:
				playerCard=new int[GameData.cardId1.length];
				for(int i=0;i<GameData.cardId1.length;i++)
				{
					playerCard[i]=GameData.cardId1[i];
				}
				break;
			case 1:
				playerCard=new int[GameData.cardId2.length];
				for(int i=0;i<GameData.cardId2.length;i++)
				{
					playerCard[i]=GameData.cardId2[i];
				}
				break;
			case 2:
				playerCard=new int[GameData.cardId3.length];
				for(int i=0;i<GameData.cardId3.length;i++)
				{
					playerCard[i]=GameData.cardId3[i];
				}
				break;
		}
		return playerCard;
	}
	//获取本家牌
		public static int[] getPlayerCardClient(int index)
		{
			int playerCard[] = null;
			switch(index)
			{
				case 0:
					playerCard=new int[GameData.client1.length];
					for(int i=0;i<GameData.client1.length;i++)
					{
						playerCard[i]=GameData.client1[i];
					}
					break;
				case 1:
					playerCard=new int[GameData.client2.length];
					for(int i=0;i<GameData.client2.length;i++)
					{
						playerCard[i]=GameData.client2[i];
					}
					break;
				case 2:
					playerCard=new int[GameData.client3.length];
					for(int i=0;i<GameData.client3.length;i++)
					{
						playerCard[i]=GameData.client3[i];
					}
					break;
			}
			return playerCard;
		}
	//获取上一家牌
	public static int[] getLastCard(int index)
	{
		//获取上一个玩家的ID
		int lastPlayer=(index==0)?2:index-1;
		
		//获取上一个玩家已出牌的ID数组
		int lastCard[] = null;
		switch(lastPlayer)
		{
			case 0:
				lastCard=new int[GameData.cardId1.length];
				for(int i=0;i<GameData.cardId1.length;i++)
				{
					lastCard[i]=GameData.cardId1[i];
				}
				break;
			case 1:
				lastCard=new int[GameData.cardId2.length];
				for(int i=0;i<GameData.cardId2.length;i++)
				{
					lastCard[i]=GameData.cardId2[i];
				}
				break;
			case 2:
				lastCard=new int[GameData.cardId3.length];
				for(int i=0;i<GameData.cardId3.length;i++)
				{
					lastCard[i]=GameData.cardId3[i];
				}
				break;
		}
		return lastCard;
	}
	//获取下一家牌
	public static int[] getNextCard(int index)
	{
		//获取上一个玩家的ID
		int NextPlayer=(index==2)?0:index+1;
		
		//获取上一个玩家已出牌的ID数组
		int nextCard[] = null;
		switch(NextPlayer)
		{
			case 0:
				nextCard=new int[GameData.cardId1.length];
				for(int i=0;i<GameData.cardId1.length;i++)
				{
					nextCard[i]=GameData.cardId1[i];
				}
				break;
			case 1:
				nextCard=new int[GameData.cardId2.length];
				for(int i=0;i<GameData.cardId2.length;i++)
				{
					nextCard[i]=GameData.cardId2[i];
				}
				break;
			case 2:
				nextCard=new int[GameData.cardId3.length];
				for(int i=0;i<GameData.cardId3.length;i++)
				{
					nextCard[i]=GameData.cardId3[i];
				}
				break;
		}
		return nextCard;
	}
	public static int getLastCardSort(int index)
	{
		//获取上一个玩家的ID
		int lastPlayer=(index==0)?2:index-1;
		int lastCardSort=100;
		if(lastPlayer==0)
		{
			lastCardSort=GameData.card1Sort;
		}else if(lastPlayer==1)
		{
			lastCardSort=GameData.card2Sort;
		}else if(lastPlayer==2)
		{
			lastCardSort=GameData.card3Sort;
		}
		
		return lastCardSort;
	}
	//获取下一的牌的类型
	public static int getNextCardSort(int index)
	{
		//获取上一个玩家的ID
		int nextPlayer=(index==2)?0:index+1;
		int nextCardSort=100;
		if(nextPlayer==0)
		{
			nextCardSort=GameData.card1Sort;
		}else if(nextPlayer==1)
		{
			nextCardSort=GameData.card2Sort;
		}else if(nextPlayer==2)
		{
			nextCardSort=GameData.card3Sort;
		}
		
		return nextCardSort;
	}
	
	public static int getCardSort(int index)
	{
		if(index==0)
		{
			index=GameData.card1Sort;
		}else if(index==1)
		{
			index=GameData.card2Sort;
		}else if(index==2)
		{
			index=GameData.card3Sort;
		}
		return index;
	}
	
	public static int[] getNewCards(int[] playerCards) 	//上两家没有牌，获取新的提示扑克牌
	{
		int newCards[]=null;
		for(int i=playerCards.length-1;i>0;i--)			//从扑克牌小的地方遍历，选出一个较小的
		{
			if(playerCards[i]%13==playerCards[i-1]%13)//&&playerCards[i+1]%13==playerCards[i+2]%13)
			{
				newCards=new int[2];
				newCards[0]=playerCards[i-1];
				newCards[1]=playerCards[i];
				break;
			}else
			{
				newCards=new int[1];
				newCards[0]=playerCards[playerCards.length-1];
				break;
			}
		}

		return newCards;
	}
	public static void saveEffect(int sort, int[] playsort) 	//存音效
	{
		if(sort==0||sort==1||sort==2)	//单张，对子，三张
		{
			GameData.effect_Row=sort;
			int playersort=playsort[0];			//取出扑克牌的索引值
			if(playsort[0]!=52&&playsort[0]!=53)	//如果不是大小王
			{
				playersort=playsort[0]%13;
			}
			int col=CodeChange.serverChangeclientInt(playersort);
			GameData.effect_Col=col;
		}else if(sort>22&&sort<33)		//飞机
		{
			GameData.effect_Row=3;
			GameData.effect_Col=0;
		}else if(sort>14&&sort<23)		//连对
		{
			GameData.effect_Row=3;
			GameData.effect_Col=1;
		}else if(sort==3)				//三带一
		{
			GameData.effect_Row=3;
			GameData.effect_Col=2;
		}else if(sort==4)				//三代二
		{
			GameData.effect_Row=3;
			GameData.effect_Col=3;
		}else if(sort>6&&sort<15)		//顺子
		{
			GameData.effect_Row=3;
			GameData.effect_Col=4;
		}else if(sort==5)				//四代二
		{
			GameData.effect_Row=3;
			GameData.effect_Col=5;
		}else if(sort==6)				//四代一对
		{
			GameData.effect_Row=3;
			GameData.effect_Col=6;
		}else if(sort==34)				//王炸
		{
			GameData.effect_Row=3;
			GameData.effect_Col=7;
		}else if(sort==33)				//炸弹
		{
			GameData.effect_Row=3;
			GameData.effect_Col=8;
		}
	}
}
