package com.bn.data;

import java.util.ArrayList;

public class GameData 
{
	public static ArrayList<String> clientList=new ArrayList<String>();		//�����ͻ��˵� ip��ַ

	public static int connectCount=0;				// ��¼��ǰ���ӵĿͻ�������
	public static int prepareCount=0;				//��¼�ͻ���׼��������
	public static ArrayList<Integer> prepareState=new ArrayList<Integer>();	//��¼׼����״̬
	public static int client;
	
	//����  0~53
	public static int client1[];		
	public static int client2[];
	public static int client3[];
	public static int endCard[];	//����
	public static int endIndex[];
	
	//��ҳ����Ƶ�����  100Ϊ�գ�û����
	public static int card1Sort=100;
	public static int card2Sort=100;
	public static int card3Sort=100;
	//��ҳ����Ƶ�����
	public static int cardId1[];
	public static int cardId2[];
	public static int cardId3[];
	//�����˶��ٻغ�
	public static int round=1;		//��ǰΪһ�ֵĿ�ʼ �������Բ�����  	1������0�����
	public static int ownCard=-1;	//ӵ����Ȩ��ID
	public static int ownState=0;	//��ǰ��ҵ��ܷ���� 	1Ϊ���Գ��ƣ�0�����Գ���
	public static int noCount=0;
	
	public static int landlord;		//��ǰ��Ȩ
	public static ArrayList<Integer> landlordList=new ArrayList<Integer>();	//�е������б�
	public static int landlordCount=0;	//��������
	public static int landlordState[];
	
	
	public static  int multiple=15;	//��Ϸ����
	
	public static int num=0;
	//��Ч
	public static int effect_Row=-1;
	public static int effect_Col=-1;
	
	
	
}
