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
	
	String receiveContent;			//�������յ�������
	
	public ServerAgentThread(Socket sc,ServerThread st) throws Exception  //��	
	{
		this.sc=sc;
		this.st=st;		
		din=new DataInputStream(sc.getInputStream());
		dout=new DataOutputStream(sc.getOutputStream());
	}
/*	���͸��ͻ�����Ϣ
 * 
 */
	public void broadcastConnect()				//��������״̬  	0
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
					IOUtil.sendInt(dout,j);						//����id
				}
			}
			catch (Exception e) {
				e.printStackTrace();
			}
		}
	}
	
	private void boradcastpreparetState() 		//���͵�ǰ׼��״̬     	1
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
	
	private void broadcastStart() 				//��ʼ��Ϸ  �����Ƹ����		2
	{
		//����״̬
		GameData.landlordState=new int[3];
		GameData.landlordState[0]=4;
		GameData.landlordState[1]=4;
		GameData.landlordState[2]=4;
		
		//������ת���� �ͻ��˴���
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
		//ת��������ID���ͻ��˵�ID
		client1=CodeChange.serverChangeclient(client1);	
		client2=CodeChange.serverChangeclient(client2);	
		client3=CodeChange.serverChangeclient(client3);
		
		System.out.println(" ����  ....  ");
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
	
	private void broadcastSelectLandlord() 		//ѡ������״̬, �ֵ�˭ѡ����	3
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
				
				for(int j=0;j<3;j++)				//������ҵĽе���״̬
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
	
	private void broadcastLandLord()			//��ʼ����		4
	{
		int landlord=GameData.landlord;			//����
		
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
		
		//ת���ɿͻ��˵��˿˱��
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
				IOUtil.sendInt(dout,landlord);		//	����id
				IOUtil.sendInt(dout, GameData.multiple);//����
				IOUtil.sendInt(dout, 20);		//���� 20��Ϊ �����Ƶı�־
				for(int j=0;j<20;j++)			//����20�ŵ���		
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
				IOUtil.sendInt(dout,3);				//����3��Ϊ���Ƶı�־
				
				for(int j=0;j<3;j++)				//����3�ŵ��Ƶ�ֵ
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
	private void broadcastCanLandlord() 		//��5   ��������  ���ڵ���Ȩ   ���������Գ���
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
					IOUtil.sendInt(dout,GameData.ownState);			//��������״̬  1chu
				}
				catch (Exception e) {
					e.printStackTrace();
				}
			}
		}
			
	}
	private void broadcastCardLandlord() 		//��6  ��������  ���ڵ���Ȩ  ����   �ɲ��ɲ�����,ÿ�ҵ��Ƶ�ʣ����  ����ÿ�ҳ����Ƶĸ���   	�Լ��Ƶ�����  
	{
		int ownCard=GameData.ownCard;			//��ǰӵ����Ȩ�����ID
		for(int i=0;i<3;i++)
		{
			DataOutputStream dout=st.cmap.get(GameData.clientList.get(i)).dout;
			try
			{
				IOUtil.sendInt(dout, 6);
				IOUtil.sendInt(dout,ownCard);				//��Ȩ
				IOUtil.sendInt(dout,GameData.multiple);		//����
				
				IOUtil.sendInt(dout, GameData.effect_Row);	//������Ч�Ķ�ά����
				IOUtil.sendInt(dout, GameData.effect_Col);

				IOUtil.sendInt(dout,GameData.round);		//��� 1���Բ���  0�����
				IOUtil.sendInt(dout, 1);			//��־λ	����Ƶĸ���
				IOUtil.sendInt(dout, GameData.client1.length);
				IOUtil.sendInt(dout, GameData.client2.length);
				IOUtil.sendInt(dout, GameData.client3.length);
				
				
				
				int client1[]=new int[GameData.client1.length];			//�������ʣ����Ƶ�ID
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
				
			//	ת���ɿͻ��˵��˿˱��
				client1=CodeChange.serverChangeclient(client1);	
				client2=CodeChange.serverChangeclient(client2);	
				client3=CodeChange.serverChangeclient(client3);
				//���� ÿλ���ʣ�����
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
				
				if(GameData.card1Sort!=100&&ownCard!=0)					//�����1��״̬��Ϊ100��������ҵ����ڳ��Ƶĸ������Լ��Ƶ�id
				{
					IOUtil.sendInt(dout,0);
					IOUtil.sendInt(dout, GameData.cardId1.length);
					
					int client[]=new int[GameData.cardId1.length];


					for(int n=0;n<GameData.cardId1.length;n++)
					{
						client[n]=GameData.cardId1[n];
					}
					//ת��������ID���ͻ��˵�ID
					client=CodeChange.serverChangeclient(client);	
					for(int j=0;j<GameData.cardId1.length;j++)
					{
						IOUtil.sendInt(dout, client[j]);
					}
				}else 
				{
					IOUtil.sendInt(dout, 100);
				}
				
				if(GameData.card2Sort!=100&&ownCard!=1)					//�����2��״̬��Ϊ100��������ҵ����ڳ��Ƶĸ������Լ��Ƶ�id
				{
					IOUtil.sendInt(dout,1);
					IOUtil.sendInt(dout, GameData.cardId2.length);
					
					int client[]=new int[GameData.cardId2.length];

					for(int n=0;n<GameData.cardId2.length;n++)
					{
						client[n]=GameData.cardId2[n];
					}
					//ת��������ID���ͻ��˵�ID
					client=CodeChange.serverChangeclient(client);	
					
					for(int j=0;j<GameData.cardId2.length;j++)
					{
						IOUtil.sendInt(dout, client[j]);
					}
				}else 
				{
					IOUtil.sendInt(dout, 100);
				}
				
				if(GameData.card3Sort!=100&&ownCard!=2)					//�����3��״̬��Ϊ100��������ҵ����ڳ��Ƶĸ������Լ��Ƶ�id
				{
					IOUtil.sendInt(dout,2);
					IOUtil.sendInt(dout, GameData.cardId3.length);
					
					int client[]=new int[GameData.cardId3.length];
					int card3Length=GameData.cardId3.length;
					for(int n=0;n<card3Length;n++)
					{
						client[n]=GameData.cardId3[n];
					}
					//ת��������ID���ͻ��˵�ID
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
	private void broadcastPrompt(int Prompt,int[] newCards)		//������ʾ	����7
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
					IOUtil.sendInt(dout, 7);				//��־λ 7
					if(Prompt==1)					// ����ʾ
					{
						IOUtil.sendInt(dout, 1);
						
						int length=newCards.length;
						IOUtil.sendInt(dout,length);
						for(int j=0;j<length;j++)
						{
							IOUtil.sendInt(dout, newCards[j]);
						}
					}else							//û����ʾ
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
	private void broadcastVictoryLandlord() 		//��8 ��Ϸ����	
	{
		int ownCard=GameData.ownCard;			//��ǰӵ����Ȩ�����ID
		int victory=-1;							//�ǵ���ʤ��������ũ��ʤ��
		if(ownCard==GameData.landlord)			
		{	
			victory=1;							//����ʤ��
		}else
		{
			victory=0;							//ũ��ʤ��
		}
		for(int i=0;i<3;i++)
		{
			DataOutputStream dout=st.cmap.get(GameData.clientList.get(i)).dout;
			try
			{
				IOUtil.sendInt(dout, 8);
				IOUtil.sendInt(dout,ownCard);			//˭��ȥ��
				IOUtil.sendInt(dout,victory);			//
				IOUtil.sendInt(dout,GameData.multiple);		//����
				
				IOUtil.sendInt(dout, GameData.effect_Row);	//������Ч�Ķ�ά����
				IOUtil.sendInt(dout, GameData.effect_Col);
				
				IOUtil.sendInt(dout, 1);			//��־λ	����Ƶĸ���
				IOUtil.sendInt(dout, GameData.client1.length);
				IOUtil.sendInt(dout, GameData.client2.length);
				IOUtil.sendInt(dout, GameData.client3.length);
				
				int client1[]=new int[GameData.client1.length];			//�������ʣ����Ƶ�ID
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
				
			//	ת���ɿͻ��˵��˿˱��
				client1=CodeChange.serverChangeclient(client1);	
				client2=CodeChange.serverChangeclient(client2);	
				client3=CodeChange.serverChangeclient(client3);
				//���� ÿλ���ʣ�����
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
				
				if(GameData.card1Sort!=100&&ownCard!=0)					//�����1��״̬��Ϊ100��������ҵ����ڳ��Ƶĸ������Լ��Ƶ�id
				{
					IOUtil.sendInt(dout,0);
					IOUtil.sendInt(dout, GameData.cardId1.length);
					
					int client[]=new int[GameData.cardId1.length];


					for(int n=0;n<GameData.cardId1.length;n++)
					{
						client[n]=GameData.cardId1[n];
					}
					//ת��������ID���ͻ��˵�ID
					client=CodeChange.serverChangeclient(client);	
					for(int j=0;j<GameData.cardId1.length;j++)
					{
						IOUtil.sendInt(dout, client[j]);
					}
				}else 
				{
					IOUtil.sendInt(dout, 100);
				}
				
				if(GameData.card2Sort!=100&&ownCard!=1)					//�����2��״̬��Ϊ100��������ҵ����ڳ��Ƶĸ������Լ��Ƶ�id
				{
					IOUtil.sendInt(dout,1);
					IOUtil.sendInt(dout, GameData.cardId2.length);
					
					int client[]=new int[GameData.cardId2.length];

					for(int n=0;n<GameData.cardId2.length;n++)
					{
						client[n]=GameData.cardId2[n];
					}
					//ת��������ID���ͻ��˵�ID
					client=CodeChange.serverChangeclient(client);	
					
					for(int j=0;j<GameData.cardId2.length;j++)
					{
						IOUtil.sendInt(dout, client[j]);
					}
				}else 
				{
					IOUtil.sendInt(dout, 100);
				}
				
				if(GameData.card3Sort!=100&&ownCard!=2)					//�����3��״̬��Ϊ100��������ҵ����ڳ��Ƶĸ������Լ��Ƶ�id
				{
					IOUtil.sendInt(dout,2);
					IOUtil.sendInt(dout, GameData.cardId3.length);
					
					int client[]=new int[GameData.cardId3.length];
					int card3Length=GameData.cardId3.length;
					for(int n=0;n<card3Length;n++)
					{
						client[n]=GameData.cardId3[n];
					}
					//ת��������ID���ͻ��˵�ID
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
/*�յ��ͻ��˵���Ϣ
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
				//ÿһ���Ƚ��ձ�־λ����   0-׼��״̬  1-�е���    2-��ʾ�ַ���
				int code=readInt(din);
				if(code==0)									
				{
					
					int count=++GameData.prepareCount;
					System.out.println(" �Ѿ��� "+count+" �����׼��... ");
					
					GameData.prepareState.add(getAddressIndex());
					
					if(GameData.prepareCount<=2)
					{
							boradcastpreparetState();			//���͵�ǰ׼��״̬
					}
					
					if(GameData.prepareCount==3)
					{
						broadcastStart();			//��ʼ��Ϸ  �����Ƹ����	2
					//	GameData.landlord=(int)(Math.random()*2);		//���ѡһ�����ȥ��ѡ����
						GameData.landlord=2;
						Thread.sleep(2000);
						broadcastSelectLandlord();
					}
					if(GameData.prepareCount==2)			//�����3λ���������Ϸ�󣬿�ʼ�����˿���
					{
						//����   ����
						CardDistribution.startCard();   
					}
					
				}
				else if(code==1)										//data=1�е�����data=0 ����   
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
					//��ÿ���˽е�����״̬�浽������
					
					if(data==1&&GameData.landlordCount!=4)
					{
						GameData.landlordList.add(index);				//��ӽ��� �������б�
						GameData.landlord=((index)/2==1)?0:(index+1);	//��һλ
						if(GameData.landlordCount!=1)
						{
							GameData.multiple=GameData.multiple*2;
						}
					}else if(data==0&&GameData.landlordCount!=4)
					{
						GameData.landlordList.add(index);				//��ӽ��� �������б�
						GameData.landlord=((index)/2==1)?0:(index+1);	//��һλ
					}
					
					if(GameData.landlordCount==4)						//���һ��������
					{
						if(data==0)
						{
							GameData.landlord=GameData.landlordList.get(GameData.landlordList.size()-1);
						}else
						{
							GameData.multiple=GameData.multiple*2;
						}
						//���õ�ǰ��Ȩ
						GameData.ownCard=GameData.landlord;
						CardDistribution.landlordCardChange();									//���������·���20����
						broadcastSelectLandlord();						//ѡ�����
						Thread.sleep(1000);
						broadcastLandLord();	
						Thread.sleep(1000);//����
						continue;
					}else if(GameData.landlordCount==3)					//ÿλ��Ҷ�ѡ�����
					{
						if(GameData.landlordList.size()>1)				//�����1�����ϵ���ҽе�����
						{
							GameData.landlord=GameData.landlordList.get(0);//���һ�λ������һ���е��������
							broadcastSelectLandlord();					//ѡ�����
						}else if(GameData.landlordList.size()==1)
						{
							GameData.landlord=GameData.landlordList.get(0);//���һ�λ������һ���е��������
							CardDistribution.landlordCardChange();								//���������·���20����
							broadcastSelectLandlord();						//ѡ�����
							GameData.ownCard=GameData.landlord;			//�ѵ������óɵ�ǰ����Ȩ
							broadcastLandLord();						//����
						}
						continue;
					}
					
					if(GameData.landlordCount<3)
					{
						broadcastSelectLandlord();						//ѡ�����
					}
					
				}
				else if(code==2)						//Ҫ���Ƹ��� �� �˿��Ƶ� id   �ж��ܲ�����playCard()
				{
					int index=getAddressIndex();		//Ҫ������ҵ�ID
					//����Ҫ���Ƶĸ���
					int cardNum=IOUtil.readInt(din);
					if(cardNum!=0)						
					{
						//����Ҫ���Ƶ�����
						int[] cardIndex=new int[cardNum];
						//����Ҫ�����˿���ID
						for(int i=0;i<cardNum;i++)
						{
							cardIndex[i]=IOUtil.readInt(din);
						}
						
						//���������ƴ���ת������������
						CodeChange.clientChangeserver(cardIndex);
						//�ж��Ƿ��ܳ���
						int sort=RuleUtil.ruleSelf(cardIndex);
						int lastSort=CardDistribution.getLastCardSort(index);
						int nextSort=CardDistribution.getNextCardSort(index);
						if(sort!=100)								// ����������ϳ�������
						{
							if(lastSort==100&&nextSort==100)
							{
								GameData.ownState=1;		//���Գ���
								int finish=CardDistribution.saveCardtoData(index,sort,cardIndex);	//�����Ƶ�������
								
								if(finish==1)																						//????????????????????
								{
									broadcastCanLandlord();		//����5  ������ҿ��Գ���
								}
								continue;
							}else if(lastSort!=100)				//�����һ���Ѿ����ƣ�
							{
								int result=RuleUtil.CARD_ROW_COL[lastSort][sort];
								if(result==0)		//���Գ���
								{
									GameData.ownState=1;		//���Գ���
									CardDistribution.saveCardtoData(index,sort,cardIndex);	//�����Ƶ�������
									broadcastCanLandlord();		//����5  ������ҿ��Գ���
									continue;
								}else if(result==1)				//�����Գ���
								{
									GameData.ownState=0;		// �����Գ���
									broadcastCanLandlord();		//����5  ������Ҳ����Գ���
									continue;
								}else if(result==2)				//����
								{
									int[] lastCard=CardDistribution.getLastCard(index);		//��ȡ��һ����
									boolean bb=RuleUtil.isrule(sort,lastCard, cardIndex);	//�жϱ����ܷ������һ����
									if(bb)
									{
										GameData.ownState=1;		//���Գ���
									}else
									{
										GameData.ownState=0;		// �����Գ���
									}
									
									CardDistribution.saveCardtoData(index,sort,cardIndex);	//�����Ƶ�������
									broadcastCanLandlord();		//����5  ������ҿ��Գ���
									continue;
								}
							}else if(lastSort==100&&nextSort!=100)		// ��һ��û����		
							{
								int result=RuleUtil.CARD_ROW_COL[nextSort][sort];
								if(result==0)		//���Գ���
								{
									GameData.ownState=1;		//���Գ���
									CardDistribution.saveCardtoData(index,sort,cardIndex);	//�����Ƶ�������
									broadcastCanLandlord();		//����5  ������ҿ��Գ���
									continue;
								}else if(result==1)				//�����Գ���
								{
									GameData.ownState=0;		// �����Գ���
									broadcastCanLandlord();		//����5  ������Ҳ����Գ���
									continue;
								}else if(result==2)				//����
								{
									int[] nextCard=CardDistribution.getNextCard(index);		//��ȡ��һ����
									boolean bb=RuleUtil.isrule(sort,nextCard, cardIndex);	//�жϱ����ܷ������һ����
									if(bb)
									{
										GameData.ownState=1;		//���Գ���
									}else
									{
										GameData.ownState=0;		// �����Գ���
									}
									
									CardDistribution.saveCardtoData(index,sort,cardIndex);	//�����Ƶ�������
									broadcastCanLandlord();	//����5  ������ҿ��Գ���
									continue;
								}
							}
						}else 								//����������ϳ�������
						{
							GameData.ownState=0;			
							broadcastCanLandlord();		//����5  ������Ҳ����Գ���
							continue;
						}
					}
				}else if(code==3)		//����յ� 3������� ����6
				{
					//�Ƿ����
					int isChuPai=IOUtil.readInt(din);
					
					int index=getAddressIndex();				//Ҫ������ҵ�ID
					if(isChuPai==1)
					{
						int length=CardDistribution.deleteCards(index);		//��ȡʣ���Ƶ�����
						if(length==0)
						{
							int sort=CardDistribution.getCardSort(index);
							int []playsort=CardDistribution.getPlayerCard(index);	//��ȡ������
							CardDistribution.saveEffect(sort,playsort);	
							if(sort==33||sort==34){			//ը��
								GameData.multiple=GameData.multiple*2;
							}
							broadcastVictoryLandlord();						//ʤ��
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
												//����Ч
					}else
					{
						GameData.noCount++;
						if(GameData.noCount==2)
						{
							GameData.round=0;		//��һ����Ȩ���ܲ���
						}
						//�����ƣ��ѱ�������ա�
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
					//��һ�ҳ���
					
					GameData.ownCard=GameData.ownCard==2?0:GameData.ownCard+1;	//��Ȩ
					broadcastCardLandlord();	//����˭��λ��ҳ�����
					//����״̬
					GameData.noCount=0;
					GameData.round=1;			//��һ�ο��Բ�����
				}
				else if(code==4)				//��ʾ
				{
					int index=getAddressIndex();
					//����������Ƶĸ���Ϊ0����Ϊ��ʾ
					int lastSort=CardDistribution.getLastCardSort(index);
					int nextSort=CardDistribution.getNextCardSort(index);
					int playerCards[]=CardDistribution.getPlayerCardClient(index);
					int []newCards=null;	
					if(lastSort==100&&nextSort==100)		//������û�г���
					{
						newCards=CardDistribution.getNewCards(playerCards);
						if(newCards==null)
						{
							int []a={};
							broadcastPrompt(0,a);
						}else
						{
							int sort=RuleUtil.ruleSelf(newCards);
							CardDistribution.saveCardtoData(index,sort,newCards);	//�����Ƶ�������
							broadcastPrompt(1,newCards);
						}
					}else if(lastSort!=100)					// ��һ���г���
					{
						newCards=RuleUtil.getCompareCards(index,0,playerCards);
						int sort=RuleUtil.ruleSelf(newCards);
						CardDistribution.saveCardtoData(index,sort,newCards);	//�����Ƶ�������
						broadcastPrompt(1,newCards);
					}else if(lastSort==100&&nextSort!=100)	//��һ��û�г��ƣ���һ���г��� 
					{
						newCards=RuleUtil.getCompareCards(index,1,playerCards);
						int sort=RuleUtil.ruleSelf(newCards);
						CardDistribution.saveCardtoData(index,sort,newCards);	//�����Ƶ�������
						broadcastPrompt(1,newCards);
					}
				}
				else if(code==100)
				{
					String data=readStr(din);
					receiveContent=receiveContent+"�յ��ַ�����"+data+"\n";
					//���յ����ַ������˳�ָ��
					if(data.trim().equals("<#EXIT#>"))
					{
						flag=false;
						String address=sc.getInetAddress().toString().trim();	//��ȡ�˳���IP��ַ
						st.cmap.remove(address);								//��map��ɾ��IP
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
	private int getAddressIndex() 						//��ȡ��ַ������
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
