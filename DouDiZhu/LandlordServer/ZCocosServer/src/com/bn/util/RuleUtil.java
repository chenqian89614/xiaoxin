package com.bn.util;
import com.bn.data.GameData;
public class RuleUtil
{
	
	public static final int DAN_ZHANG=0;				//单张	1
	public static final int DUI_ZI=1;					//对子	2
	public static final int SAN_ZHANG=2;				//三张	3
	public static final int SAN_DAI_YI=3;				//		4
	public static final int SAN_DAI_ER=4;				//		5
	public static final int SI_DAI_ER=5;				//四带二	6
	public static final int SI_DAI_DUI=6;				//四代对	8
	public static final int SHUN_ZI_FIVE=7;				//顺子	5
	public static final int SHUN_ZI_SIX=8;				//		6
	public static final int SHUN_ZI_SEVEN=9;			//		7
	public static final int SHUN_ZI_EIGHT=10;			//		8
	public static final int SHUN_ZI_NINE=11;			//		9
	public static final int SHUN_ZI_TEN=12;				//		10
	public static final int SHUN_ZI_ELEVEN=13;			//		11
	public static final int SHUN_ZI_TWELVE=14;			//		12
	public static final int LIAN_DUI_3=15;				//连对	6
	public static final int LIAN_DUI_4=16;				//		8
	public static final int LIAN_DUI_5=17;				//		10
	public static final int LIAN_DUI_6=18;				//		12
	public static final int LIAN_DUI_7=19;				//		14
	public static final int LIAN_DUI_8=20;				//		16
	public static final int LIAN_DUI_9=21;				//		18
	public static final int LIAN_DUI_10=22;				//		20
	public static final int FEIJI_ER_ZERO=23;			//飞机	6
	public static final int FEIJI_ER_YI=24;				//飞机31	8
	public static final int FEIJI_ER_ER=25;				//	32	10	
	public static final int FEIJI_SAN_ZERO=26;			//		9
	public static final int FEIJI_SAN_YI=27;			//	31	12
	public static final int FEIJI_SAN_ER=28;			//		15
	public static final int FEIJI_SI_ZERO=29;			//		12
	public static final int FEIJI_SI_YI=30;				//		16
	public static final int FEIJI_SI_ER=31;				//		20
	public static final int FEIJI_WU_ZERO=32;			//		15
	public static final int ZHA_DAN=33;					//炸弹  	4
	public static final int SHUANG_WANG=34;				//		2
	
	
	//0代表可以出牌，1代表不可以出牌，2代表待定
	public static final int[][] CARD_ROW_COL={
		{2,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,1,	1,1,1,0,0},		//0
		{1,2,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,1,	1,1,1,0,0},		//1
		{1,1,2,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,1,	1,1,1,0,0},		//2
		{1,1,1,2,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,1,	1,1,1,0,0},		//3
		{1,1,1,1,2,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,1,	1,1,1,0,0},		//4
		{1,1,1,1,1,2,1,1,1,1,	1,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,1,	1,1,1,0,0},		//5
		{1,1,1,1,1,1,2,1,1,1,	1,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,1,	1,1,1,0,0},		//6
		{1,1,1,1,1,1,1,2,1,1,	1,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,1,	1,1,1,0,0},		//7
		{1,1,1,1,1,1,1,1,2,1,	1,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,1,	1,1,1,0,0},		//8
		{1,1,1,1,1,1,1,1,1,2,	1,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,1,	1,1,1,0,0},		//9
		
		{1,1,1,1,1,1,1,1,1,1,	2,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,1,	1,1,1,0,0},		//10
		{1,1,1,1,1,1,1,1,1,1,	1,2,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,1,	1,1,1,0,0},		//11
		{1,1,1,1,1,1,1,1,1,1,	1,1,2,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,1,	1,1,1,0,0},		//12
		{1,1,1,1,1,1,1,1,1,1,	1,1,1,2,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,1,	1,1,1,0,0},		//13
		{1,1,1,1,1,1,1,1,1,1,	1,1,1,1,2,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,1,	1,1,1,0,0},		//14
		{1,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,2,1,1,1,1,	1,1,1,1,1,1,1,1,1,1,	1,1,1,0,0},		//15
		{1,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,2,1,1,1,	1,1,1,1,1,1,1,1,1,1,	1,1,1,0,0},		//16
		{1,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,2,1,1,	1,1,1,1,1,1,1,1,1,1,	1,1,1,0,0},		//17
		{1,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,2,1,	1,1,1,1,1,1,1,1,1,1,	1,1,1,0,0},		//18
		{1,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,2,	1,1,1,1,1,1,1,1,1,1,	1,1,1,0,0},		//19
		
		{1,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,1,	2,1,1,1,1,1,1,1,1,1,	1,1,1,0,0},		//20
		{1,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,1,	1,2,1,1,1,1,1,1,1,1,	1,1,1,0,0},		//21
		{1,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,1,	1,1,2,1,1,1,1,1,1,1,	1,1,1,0,0},		//22
		{1,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,1,	1,1,1,2,1,1,1,1,1,1,	1,1,1,0,0},		//23
		{1,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,1,	1,1,1,1,2,1,1,1,1,1,	1,1,1,0,0},		//24
		{1,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,2,1,1,1,1,	1,1,1,0,0},		//25
		{1,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,2,1,1,1,	1,1,1,0,0},		//26
		{1,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,2,1,1,	1,1,1,0,0},		//27
		{1,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,2,1,	1,1,1,0,0},		//28
		{1,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,2,	1,1,1,0,0},		//29
		
		{1,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,1,	2,1,1,0,0},		//30
		{1,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,1,	1,2,1,0,0},		//31
		{1,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,1,	1,1,2,0,0},		//32
		{1,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,1,	1,1,1,2,0},		//33  zhadan
		{1,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,1,	1,1,1,1,1},		//34 shaugnwang
		
		};
		
	
	//传来牌，获取牌的类型
	public static int ruleSelf(int cardIndex[])
	{
		int result=100;
		int shunzi=0;
		int num=0;			//相等的个数
		int numId1=0;		//飞机相等的id
		int numId2=0;
		int numId3=0;		
		int numId4=0;
		int numId5=0;		
		int numId6=0;
		int numId7=0;
		int numId8=0;
		
		if(cardIndex==null)
		{
			return 100;
		}
		switch(cardIndex.length)
		{
			case 1:
				result=DAN_ZHANG;
				break;
			case 2:
				if(cardIndex[0]<52&&cardIndex[1]<52&&cardIndex[0]%13==cardIndex[1]%13)	//如果两张牌 不等于大小王  ，而且相等
				{
					result=DUI_ZI;
				}else if(cardIndex[0]==53&&cardIndex[1]==52)
				{
					result=SHUANG_WANG;
				}
				break;
			case 3:
				if(cardIndex[0]<52&&cardIndex[1]<52&&cardIndex[2]<52&&cardIndex[0]%13==cardIndex[1]%13&&cardIndex[1]%13==cardIndex[2]%13)	//如果两张牌 不等于大小王  ，而且相等
				{
					result=SAN_ZHANG;
				}
				break;
			case 4:
				//判断相等的个数
				num=0;
				for(int i=0;i<3;i++)
				{
					if(cardIndex[i]%13==cardIndex[i+1]%13)
					{
						num++;
					}
				}
				if(num==3)
				{
					result=ZHA_DAN;
				}else if(num==2)
				{
					if(cardIndex[0]!=53&&cardIndex[1]%13==cardIndex[2]%13&&cardIndex[2]%13==cardIndex[3]%13)
					{
						result=SAN_DAI_YI;
					}else if(cardIndex[0]!=53&&cardIndex[0]%13==cardIndex[1]%13&&cardIndex[1]%13==cardIndex[2]%13)
					{
						result=SAN_DAI_YI;
					}
				}
				break;
			case 5:
				//判断相等的个数，三代二
				num=0;
				for(int i=0;i<4;i++)
				{
					if(Math.abs(cardIndex[i]%13-cardIndex[i+1]%13)==0)
					{
						num++;
					}
				}
				if(num==3&&cardIndex[0]%13==cardIndex[1]%13&&cardIndex[3]%13==cardIndex[4]%13&&cardIndex[0]<52)
				{
					result=SAN_DAI_ER;
				}
				
				//顺子5
				num=0;
				for(int i=0;i<4;i++)
				{
					if(cardIndex[0]<52&&cardIndex[i]%13-cardIndex[i+1]%13==1)
					{
						num++;
					}
				}
				if(num==4)
				{
					result=SHUN_ZI_FIVE;
				}
				break;
			case 6:			//四带二 		顺子6
				//四代二
				// 判断相等的个数
				num=0;
				for(int i=0;i<5;i++)
				{
					if(cardIndex[i]%13==cardIndex[i+1]%13)
					{
						num++;
					}
				}
				if(num==3&&cardIndex[0]<52)
				{
					if(cardIndex[1]%13==cardIndex[2]%13||cardIndex[3]%13==cardIndex[4]%13)
					{
						result=SI_DAI_ER;
						break;
					}
				}
				// 判断相等的个数  ，连对3
				num=0;
				for(int i=0;i<5;i+=2)
				{
					if(cardIndex[i]%13==cardIndex[i+1]%13)
					{
						num++;
					}
				}
				if(num==3&&cardIndex[0]<52)
				{
					if(cardIndex[0]<52&&cardIndex[0]%13!=12&&
							cardIndex[1]%13-cardIndex[2]%13==1&&cardIndex[3]%13-cardIndex[4]%13==1)
					{
						result=LIAN_DUI_3;
						break;
					}
				}
				
				//顺子6
				num=0;
				shunzi=5;
				for(int i=0;i<shunzi;i++)
				{
					if(cardIndex[i]%13-cardIndex[i+1]%13==1&&cardIndex[0]<52&&cardIndex[i]%13!=12)
					{
						num++;
					}
				}
				if(num==shunzi)
				{
					result=SHUN_ZI_SIX;
					break;
				}
				
				//飞机	20
				// 判断相等的个数
				num=0;
				numId1=0;
				numId2=0;
				for(int i=0;i<5;i++)
				{
					if(cardIndex[i]%13==cardIndex[i+1]%13)
					{
						num++;
						if(num==2&&i<4)
						{
							numId1=cardIndex[i+1];
							numId2=cardIndex[i+2];
						}
						
					}
				}
				if(num==4)
				{
					if(numId1%13-numId2%13==1)
					{
						result=FEIJI_ER_ZERO;
						break;
					}
				}
				break;
			case 7:					//顺子7
				num=0;
				shunzi=6;
				for(int i=0;i<shunzi;i++)
				{
					if(cardIndex[i]%13-cardIndex[i+1]%13==1&&cardIndex[0]<52&&cardIndex[i]%13!=12)
					{
						num++;
					}
				}
				if(num==shunzi)
				{
					result=SHUN_ZI_SEVEN;
					break;
				}
				break;
			case 8: 			//四代对	连对4		顺子8		飞机21
				
				//顺子8
				num=0;
				shunzi=7;
				for(int i=0;i<shunzi;i++)
				{
					if(cardIndex[i]%13-cardIndex[i+1]%13==1&&cardIndex[0]<52&&cardIndex[i]%13!=12)
					{
						num++;
					}
				}
				if(num==shunzi)
				{
					result=SHUN_ZI_EIGHT;
				}
				
				// 判断相等的个数  ，连对4
				num=0;
				for(int i=0;i<7;i+=2)
				{
					if(cardIndex[i]%13==cardIndex[i+1]%13)
					{
						num++;
					}
				}
				if(num==4&&cardIndex[0]<52)
				{
					if(cardIndex[0]<52&&cardIndex[0]%13!=12&&
							cardIndex[1]%13-cardIndex[2]%13==1&&cardIndex[3]%13-cardIndex[4]%13==1
							&&cardIndex[5]%13-cardIndex[6]%13==1)
					{
						result=LIAN_DUI_4;
					}
				}
				
				// 四代dui
				num=0;
				for(int i=0;i<7;i++)
				{
					if(cardIndex[i]%13==cardIndex[i+1]%13)
					{
						num++;
					}
				}
				if(num==5&&cardIndex[0]<52)
				{
					if(cardIndex[1]%13==cardIndex[2]%13||cardIndex[3]%13==cardIndex[4]%13||cardIndex[5]%13==cardIndex[6]%13)
					{
						result=SI_DAI_DUI;
					}
				}
				//飞机	21
				// 判断相等的个数
				num=0;
				numId1=0;
				numId2=0;
				for(int i=0;i<7;i++)
				{
					if(cardIndex[i]%13==cardIndex[i+1]%13)
					{
						num++;
						if(num==2&&i<6)
						{
							numId1=cardIndex[i+1];
							numId2=cardIndex[i+2];
						}
						
					}
				}
				if(num==4)
				{
					if(numId1%13-numId2%13==1)
					{
						result=FEIJI_ER_YI;
					}
				}
				break;
			case 9:
				//顺子9
				num=0;
				shunzi=8;
				for(int i=0;i<shunzi;i++)
				{
					if(cardIndex[i]%13-cardIndex[i+1]%13==1&&cardIndex[0]<52&&cardIndex[i]%13!=12)
					{
						num++;
					}
				}
				if(num==shunzi)
				{
					result=SHUN_ZI_NINE;
				}
				
				//飞机	30
				// 判断相等的个数
				num=0;
				numId1=0;
				numId2=0;
				numId3=0;
				numId4=0;
				for(int i=0;i<8;i++)
				{
					if(cardIndex[i]%13==cardIndex[i+1]%13)
					{
						num++;
						if(num==2)
						{
							numId1=cardIndex[i+1];
							numId2=cardIndex[i+2];
						}else if(num==4&&i<7)
						{
							numId3=cardIndex[i+1];
							numId4=cardIndex[i+2];
						}
						
					}
				}
				if(num==6)
				{
					if(numId1%13-numId2%13==1&&numId3%13-numId4%13==1)
					{
						result=FEIJI_SAN_ZERO;
					}
				}
				break;
			case 10:	//顺子 10，飞机 二二，连对5
				//顺子10
				num=0;
				shunzi=9;
				for(int i=0;i<shunzi;i++)
				{
					if(cardIndex[i]%13-cardIndex[i+1]%13==1&&cardIndex[0]<52&&cardIndex[i]%13!=12)
					{
						num++;
					}
				}
				if(num==shunzi)
				{
					result=SHUN_ZI_TEN;
				}
				//飞机	22
				// 判断相等的个数
				num=0;
				numId1=0;
				numId2=0;
				for(int i=0;i<9;i++)
				{
					if(cardIndex[i]%13==cardIndex[i+1]%13)				///
					{
						num++;
						if(num==2)
						{
							numId1=cardIndex[i+1];
							numId2=cardIndex[i+2];
						}
					}
				}
				if(num==6)
				{
					if(numId1%13-numId2%13==1)
					{
						result=FEIJI_ER_ER;
					}
				}
				
				//连对5
				num=0;
				for(int i=0;i<9;i+=2)
				{
					if(cardIndex[i]%13==cardIndex[i+1]%13)
					{
						num++;
					}
				}
				if(num==5&&cardIndex[0]<52)
				{
					if(cardIndex[0]<52&&cardIndex[0]%13!=12&&
						cardIndex[1]%13-cardIndex[2]%13==1&&cardIndex[3]%13-cardIndex[4]%13==1&&cardIndex[5]%13-cardIndex[6]%13==1&&cardIndex[7]%13-cardIndex[8]%13==1)
					{
						result=LIAN_DUI_5;
					}
				}
				break;
			case 11:			//顺子11
				//顺子11
				num=0;
				shunzi=10;
				for(int i=0;i<shunzi;i++)
				{
					if(cardIndex[i]%13-cardIndex[i+1]%13==1&&cardIndex[0]<52&&cardIndex[i]%13!=12)
					{
						num++;
					}
				}
				if(num==shunzi)
				{
					result=SHUN_ZI_ELEVEN;
				}
				break;
			case 12:			//顺子 12	飞机 31	连对6
				//顺子12
				num=0;
				shunzi=11;
				for(int i=0;i<shunzi;i++)
				{
					if(cardIndex[i]%13-cardIndex[i+1]%13==1&&cardIndex[0]<52&&cardIndex[i]%13!=12)
					{
						num++;
					}
				}
				if(num==shunzi)
				{
					result=SHUN_ZI_TWELVE;
				}
				
				//飞机	31
				// 判断相等的个数
				num=0;
				numId1=0;
				numId2=0;
				numId3=0;
				numId4=0;
				
				for(int i=0;i<11;i++)
				{
					if(cardIndex[i]%13==cardIndex[i+1]%13)
					{
						num++;
						if(num==2)
						{
							numId1=cardIndex[i+1];
							numId2=cardIndex[i+2];
						}else if(num==4)
						{
							numId3=cardIndex[i+1];
							numId4=cardIndex[i+2];
						}
						
					}
				}
				if(num==6)
				{
					if(numId1%13-numId2%13==1&&numId4%13-numId3%13==1)
					{
						result=FEIJI_SAN_YI;
					}
				}
				
				//连对6
				num=0;
				for(int i=0;i<11;i+=2)
				{
					if(cardIndex[i]%13==cardIndex[i+1]%13)
					{
						num++;
					}
				}
				if(num==6&&cardIndex[0]<52)
				{
					if(cardIndex[0]<52&&cardIndex[0]%13!=12&&
							cardIndex[1]%13-cardIndex[2]%13==1&&cardIndex[3]%13-cardIndex[4]%13==1
							&&cardIndex[5]%13-cardIndex[6]%13==1&&cardIndex[7]%13-cardIndex[8]%13==1
							&&cardIndex[9]%13-cardIndex[10]%13==1)
					{
						result=LIAN_DUI_6;
					}
				}
				
				//飞机四0
				// 判断相等的个数
				num=0;
				numId1=0;
				numId2=0;
				numId3=0;
				numId4=0;
				numId5=0;
				numId6=0;
				
				for(int i=0;i<11;i++)
				{
					if(cardIndex[i]%13==cardIndex[i+1]%13)
					{
						num++;
						if(num==2)
						{
							numId1=cardIndex[i+1];
							numId2=cardIndex[i+2];
						}else if(num==4)
						{
							numId3=cardIndex[i+1];
							numId4=cardIndex[i+2];
						}else if(num==6)
						{
							numId5=cardIndex[i+1];
							numId6=cardIndex[i+2];
						}
						
					}
				}
				if(num==8)
				{
					if(numId1%13-numId2%13==1&&numId3%13-numId4%13==1&&numId5%13-numId6%13==1)
					{
						result=FEIJI_SI_ZERO;
					}
				}
				break;
				
			case 14:		//连对	7
				//连对7
				num=0;
				for(int i=0;i<13;i+=2)
				{
					if(cardIndex[i]%13==cardIndex[i+1]%13)
					{
						num++;
					}
				}
				if(num==7&&cardIndex[0]<52)
				{
					if(	cardIndex[0]<52&&cardIndex[0]%13!=12&&cardIndex[1]%13-cardIndex[2]%13==1&&cardIndex[3]%13-cardIndex[4]%13==1
							&&cardIndex[5]%13-cardIndex[6]%13==1&&cardIndex[7]%13-cardIndex[8]%13==1
							&&cardIndex[9]%13-cardIndex[10]%13==1&&cardIndex[11]%13-cardIndex[12]%13==1)
					{
						result=LIAN_DUI_7;
					}
				}
				break;
			case 15:		//飞机32
				// 判断相等的个数
				num=0;
				numId1=0;
				numId2=0;
				numId3=0;
				numId4=0;
				
				for(int i=0;i<14;i++)
				{
					if(cardIndex[i]%13==cardIndex[i+1]%13)
					{
						num++;
						if(num==2)
						{
							numId1=cardIndex[i+1];
							numId2=cardIndex[i+2];
						}else if(num==4)
						{
							numId3=cardIndex[i+1];
							numId4=cardIndex[i+2];
						}
					}
				}
				if(num==9)
				{
					if(numId1%13-numId2%13==1&&numId4%13-numId3%13==1)
					{
						result=FEIJI_SAN_ER;
					}
				}
				
				//飞机50
				// 判断相等的个数
				num=0;
				numId1=0;
				numId2=0;
				numId3=0;
				numId4=0;
				numId5=0;
				numId6=0;
				numId7=0;
				numId8=0;
				
				for(int i=0;i<14;i++)
				{
					if(cardIndex[i]%13==cardIndex[i+1]%13)
					{
						num++;
						if(num==2)
						{
							numId1=cardIndex[i+1];
							numId2=cardIndex[i+2];
						}else if(num==4)
						{
							numId3=cardIndex[i+1];
							numId4=cardIndex[i+2];
						}else if(num==6)
						{
							numId5=cardIndex[i+1];
							numId6=cardIndex[i+2];
						}else if(num==8)
						{
							numId7=cardIndex[i+1];
							numId8=cardIndex[i+2];
						}
						
					}
				}
				if(num==10)
				{
					if(numId1%13-numId2%13==1&&numId3%13-numId4%13==1&&numId5%13-numId6%13==1&&numId7%13-numId8%13==1)
					{
						result=FEIJI_WU_ZERO;
					}
				}
				break;
			case 16:			//连对8	飞机四一
				//连对8
				num=0;
				for(int i=0;i<15;i+=2)
				{
					if(cardIndex[i]%13==cardIndex[i+1]%13)
					{
						num++;
					}
				}
				if(num==8&&cardIndex[0]<52)
				{
					if(cardIndex[0]<52&&cardIndex[0]%13!=12&&
							cardIndex[1]%13-cardIndex[2]%13==1&&cardIndex[3]%13-cardIndex[4]%13==1
							&&cardIndex[5]%13-cardIndex[6]%13==1&&cardIndex[7]%13-cardIndex[8]%13==1
							&&cardIndex[9]%13-cardIndex[10]%13==1&&cardIndex[11]%13-cardIndex[12]%13==1
							&&cardIndex[13]%13-cardIndex[14]%13==1)
					{
						result=LIAN_DUI_8;
					}
				}
				//飞机四一
				// 判断相等的个数
				num=0;
				numId1=0;
				numId2=0;
				numId3=0;
				numId4=0;
				numId5=0;
				numId6=0;
				
				for(int i=0;i<15;i++)
				{
					if(cardIndex[i]%13==cardIndex[i+1]%13)
					{
						num++;
						if(num==2)
						{
							numId1=cardIndex[i+1];
							numId2=cardIndex[i+2];
						}else if(num==4)
						{
							numId3=cardIndex[i+1];
							numId4=cardIndex[i+2];
						}else if(num==6)
						{
							numId5=cardIndex[i+1];
							numId6=cardIndex[i+2];
						}
						
					}
				}
				if(num==8)
				{
					if(numId1%13-numId2%13==1&&numId3%13-numId4%13==1&&numId5%13-numId6%13==1)
					{
						result=FEIJI_SI_YI;
					}
				}
				break;
			case 18:			//连对9
				//连对9
				num=0;
				for(int i=0;i<17;i+=2)
				{
					if(cardIndex[i]%13==cardIndex[i+1]%13)
					{
						num++;
					}
				}
				if(num==9&&cardIndex[0]<52)
				{
					if(cardIndex[0]<52&&cardIndex[0]%13!=12&&
							cardIndex[1]%13-cardIndex[2]%13==1&&cardIndex[3]%13-cardIndex[4]%13==1
							&&cardIndex[5]%13-cardIndex[6]%13==1&&cardIndex[7]%13-cardIndex[8]%13==1
							&&cardIndex[9]%13-cardIndex[10]%13==1&&cardIndex[11]%13-cardIndex[12]%13==1
							&&cardIndex[13]%13-cardIndex[14]%13==1&&cardIndex[15]%13-cardIndex[16]%13==1)
					{
						result=LIAN_DUI_9;
					}
				}
				break;
			case 20:			//连对10	飞机42
				//连对10
				num=0;
				for(int i=0;i<19;i+=2)
				{
					if(cardIndex[i]%13==cardIndex[i+1]%13)
					{
						num++;
					}
				}
				if(num==10&&cardIndex[0]<52)
				{
					if(cardIndex[0]<52&&cardIndex[0]%13!=12&&cardIndex[1]%13-cardIndex[2]%13==1&&cardIndex[3]%13-cardIndex[4]%13==1
							&&cardIndex[5]%13-cardIndex[6]%13==1&&cardIndex[7]%13-cardIndex[8]%13==1
							&&cardIndex[9]%13-cardIndex[10]%13==1&&cardIndex[11]%13-cardIndex[12]%13==1
							&&cardIndex[13]%13-cardIndex[14]%13==1&&cardIndex[15]%13-cardIndex[16]%13==1
							&&cardIndex[17]%13-cardIndex[18]%13==1)
					{
						result=LIAN_DUI_9;
					}
				}
				
				//飞机四二
				// 判断相等的个数
				num=0;
				numId1=0;
				numId2=0;
				numId3=0;
				numId4=0;
				numId5=0;
				numId6=0;
				
				for(int i=0;i<19;i++)
				{
					if(cardIndex[i]%13==cardIndex[i+1]%13)
					{
						num++;
						if(num==2)
						{
							numId1=cardIndex[i+1];
							numId2=cardIndex[i+2];
						}else if(num==4)
						{
							numId3=cardIndex[i+1];
							numId4=cardIndex[i+2];
						}else if(num==6)
						{
							numId5=cardIndex[i+1];
							numId6=cardIndex[i+2];
						}
						
					}
				}
				if(num==12)
				{
					if(numId1%13-numId2%13==1&&numId3%13-numId4%13==1&&numId5%13-numId6%13==1)
					{
						result=FEIJI_SI_ER;
					}
				}
				break;
		}
		
		
		
		return result;
	}
	public static boolean isrule(int sort,int[] lastIndex,int[] cardIndex) 			//判断是否可以出牌
	{
		int lastId=0;
		int ownId=0;
		
		if(lastIndex==null)
		{
			return true;
		}
		switch(sort)
		{
		case DAN_ZHANG: 	//单
			if((lastIndex[0]<52&&cardIndex[0]<52&&lastIndex[0]%13<cardIndex[0]%13)
					||lastIndex[0]>=52&&cardIndex[0]>=52&&lastIndex[0]<cardIndex[0]
						||lastIndex[0]<52&&cardIndex[0]>=52)
			{
				return true;
			}else 
			{
				return false;
			}
		case DUI_ZI:		//对
			if((lastIndex[0]<52&&cardIndex[0]<52&&lastIndex[0]%13<cardIndex[0]%13))
			{
				return true;
			}else 
			{
				return false;
			}
		case SAN_ZHANG:		//三张
			if((lastIndex[0]<52&&cardIndex[0]<52&&lastIndex[0]%13<cardIndex[0]%13))
			{
				return true;
			}else 
			{
				return false;
			}
		case SAN_DAI_YI:	//三带一
			lastId=0;
			ownId=0;
			for(int i=0;i<3;i++)
			{
				if(lastIndex[i]%13==lastIndex[i+1]%13)
				{
					lastId=lastIndex[i]%13;
				}
				if(cardIndex[i]%13==cardIndex[i+1]%13)
				{
					ownId=cardIndex[i]%13;
				}
			}
			if(ownId>lastId)
			{
				return true;
			}else 
			{
				return false;
			}
		case SAN_DAI_ER:	//三代二
			lastId=0;
			ownId=0;
			for(int i=0;i<4;i++)
			{
				if(lastIndex[i]%13==lastIndex[i+1]%13&&lastIndex[i+1]%13==lastIndex[i+2]%13)
				{
					lastId=lastIndex[i]%13;
				}
				if(cardIndex[i]%13==cardIndex[i+1]%13&&cardIndex[i+1]%13==cardIndex[i+2]%13)
				{
					ownId=cardIndex[i]%13;
				}
			}
			if(ownId>lastId)
			{
				return true;
			}else 
			{
				return false;
			}
		case SI_DAI_ER:		//四代二
			lastId=0;
			ownId=0;
			if(lastIndex[3]==lastIndex[4]&&cardIndex[3]==cardIndex[4])
			{
				lastId=lastIndex[3];
				ownId=cardIndex[3];
			}
			if(ownId>lastId)
			{
				return true;
			}else 
			{
				return false;
			}
		case SI_DAI_DUI:	//四代对
			lastId=0;
			ownId=0;
			for(int i=0;i<5;i++)
			{
				if(lastIndex[i]%13==lastIndex[i+1]%13&&lastIndex[i+1]%13==lastIndex[i+2]%13&&lastIndex[i+2]%13==lastIndex[i+3]%13)
				{
					lastId=lastIndex[i]%13;
				}
				if(cardIndex[i]%13==cardIndex[i+1]%13&&cardIndex[i+1]%13==cardIndex[i+2]%13&&cardIndex[i+2]%13==cardIndex[i+3]%13)
				{
					ownId=cardIndex[i]%13;
				}
			}
			if(ownId>lastId)
			{
				return true;
			}else 
			{
				return false;
			}
		case SHUN_ZI_FIVE:		//顺子5
			lastId=lastIndex[0]%13;
			ownId=cardIndex[0]%13;
			if(ownId>lastId)
			{
				return true;
			}else 
			{
				return false;
			}
		case SHUN_ZI_SIX:		//顺子6
			lastId=lastIndex[0]%13;
			ownId=cardIndex[0]%13;
			if(ownId>lastId)
			{
				return true;
			}else 
			{
				return false;
			}
		case SHUN_ZI_SEVEN:		//顺子7
			lastId=lastIndex[0]%13;
			ownId=cardIndex[0]%13;
			if(ownId>lastId)
			{
				return true;
			}else 
			{
				return false;
			}
		case SHUN_ZI_EIGHT:		//顺子8
			lastId=lastIndex[0]%13;
			ownId=cardIndex[0]%13;
			if(ownId>lastId)
			{
				return true;
			}else 
			{
				return false;
			}
		case SHUN_ZI_NINE:		//顺子9
			lastId=lastIndex[0]%13;
			ownId=cardIndex[0]%13;
			if(ownId>lastId)
			{
				return true;
			}else 
			{
				return false;
			}
		case SHUN_ZI_TEN:		//顺子10
			lastId=lastIndex[0]%13;
			ownId=cardIndex[0]%13;
			if(ownId>lastId)
			{
				return true;
			}else 
			{
				return false;
			}
		case SHUN_ZI_ELEVEN:	//顺子11
			lastId=lastIndex[0]%13;
			ownId=cardIndex[0]%13;
			if(ownId>lastId)
			{
				return true;
			}else 
			{
				return false;
			}
		case SHUN_ZI_TWELVE:	//顺子12
			lastId=lastIndex[0]%13;
			ownId=cardIndex[0]%13;
			if(ownId>lastId)
			{
				return true;
			}else 
			{
				return false;
			}
		case LIAN_DUI_3:		//连对3
			lastId=lastIndex[0]%13;
			ownId=cardIndex[0]%13;
			if(ownId>lastId)
			{
				return true;
			}else 
			{
				return false;
			}
		case LIAN_DUI_4:		//连对4
			lastId=lastIndex[0]%13;
			ownId=cardIndex[0]%13;
			if(ownId>lastId)
			{
				return true;
			}else 
			{
				return false;
			}
		case LIAN_DUI_5:		//连对5
			lastId=lastIndex[0]%13;
			ownId=cardIndex[0]%13;
			if(ownId>lastId)
			{
				return true;
			}else 
			{
				return false;
			}
		case LIAN_DUI_6:		//连对6
			lastId=lastIndex[0]%13;
			ownId=cardIndex[0]%13;
			if(ownId>lastId)
			{
				return true;
			}else 
			{
				return false;
			}
		case LIAN_DUI_7:		//连对7
			lastId=lastIndex[0]%13;
			ownId=cardIndex[0]%13;
			if(ownId>lastId)
			{
				return true;
			}else 
			{
				return false;
			}
		case LIAN_DUI_8:		//连对8
			lastId=lastIndex[0]%13;
			ownId=cardIndex[0]%13;
			if(ownId>lastId)
			{
				return true;
			}else 
			{
				return false;
			}
		case LIAN_DUI_9:		//连对9
			lastId=lastIndex[0]%13;
			ownId=cardIndex[0]%13;
			if(ownId>lastId)
			{
				return true;
			}else 
			{
				return false;
			}
		case FEIJI_ER_ZERO:		//飞机 20
			lastId=lastIndex[0]%13;
			ownId=cardIndex[0]%13;
			if(ownId>lastId)
			{
				return true;
			}else 
			{
				return false;
			}
		case FEIJI_ER_YI:		//飞机 21
			lastId=lastIndex[0]%13;
			ownId=cardIndex[0]%13;
			for(int i=7;i>0;i--)
			{
				if(lastIndex[i]%13==lastIndex[i-1]%13&&lastIndex[i-1]%13==lastIndex[i-2]%13)
				{
					lastId=lastIndex[i]%13;
				}
				if(cardIndex[i]%13==cardIndex[i-1]%13&&lastIndex[i-1]%13==lastIndex[i-2]%13)
				{
					ownId=cardIndex[i]%13;
				}
			}
			if(ownId>lastId)
			{
				return true;
			}else 
			{
				return false;
			}
		case FEIJI_ER_ER:		//飞机 22
			lastId=lastIndex[0]%13;
			ownId=cardIndex[0]%13;
			for(int i=9;i>0;i--)
			{
				if(lastIndex[i]%13==lastIndex[i-1]%13&&lastIndex[i-1]%13==lastIndex[i-2]%13)
				{
					lastId=lastIndex[i]%13;
				}
				if(cardIndex[i]%13==cardIndex[i-1]%13&&lastIndex[i-1]%13==lastIndex[i-2]%13)
				{
					ownId=cardIndex[i]%13;
				}
			}
			if(ownId>lastId)
			{
				return true;
			}else 
			{
				return false;
			}
		case FEIJI_SAN_ZERO:		//飞机 30
			lastId=lastIndex[0]%13;
			ownId=cardIndex[0]%13;
			if(ownId>lastId)
			{
				return true;
			}else 
			{
				return false;
			}
		case FEIJI_SAN_YI:			//飞机31
			lastId=lastIndex[0]%13;
			ownId=cardIndex[0]%13;
			for(int i=11;i>0;i--)
			{
				if(lastIndex[i]%13==lastIndex[i-1]%13&&lastIndex[i-1]%13==lastIndex[i-2]%13)
				{
					lastId=lastIndex[i]%13;
				}
				if(cardIndex[i]%13==cardIndex[i-1]%13&&lastIndex[i-1]%13==lastIndex[i-2]%13)
				{
					ownId=cardIndex[i]%13;
				}
			}
			if(ownId>lastId)
			{
				return true;
			}else 
			{
				return false;
			}
		case FEIJI_SAN_ER:			//飞机 32
			lastId=lastIndex[0]%13;
			ownId=cardIndex[0]%13;
			for(int i=14;i>0;i--)
			{
				if(lastIndex[i]%13==lastIndex[i-1]%13&&lastIndex[i-1]%13==lastIndex[i-2]%13)
				{
					lastId=lastIndex[i]%13;
				}
				if(cardIndex[i]%13==cardIndex[i-1]%13&&lastIndex[i-1]%13==lastIndex[i-2]%13)
				{
					ownId=cardIndex[i]%13;
				}
			}
			if(ownId>lastId)
			{
				return true;
			}else 
			{
				return false;
			}
		case FEIJI_SI_ZERO:			//飞机 40
			lastId=lastIndex[0]%13;
			ownId=cardIndex[0]%13;

			if(ownId>lastId)
			{
				return true;
			}else 
			{
				return false;
			}
		
		case FEIJI_SI_YI:			//飞机 41
			lastId=lastIndex[0]%13;
			ownId=cardIndex[0]%13;
			for(int i=15;i>0;i--)
			{
				if(lastIndex[i]%13==lastIndex[i-1]%13&&lastIndex[i-1]%13==lastIndex[i-2]%13)
				{
					lastId=lastIndex[i]%13;
				}
				if(cardIndex[i]%13==cardIndex[i-1]%13&&lastIndex[i-1]%13==lastIndex[i-2]%13)
				{
					ownId=cardIndex[i]%13;
				}
			}
			if(ownId>lastId)
			{
				return true;
			}else 
			{
				return false;
			}
		case FEIJI_SI_ER:			//飞机 42
			lastId=lastIndex[0]%13;
			ownId=cardIndex[0]%13;
			for(int i=19;i>0;i--)
			{
				if(lastIndex[i]%13==lastIndex[i-1]%13&&lastIndex[i-1]%13==lastIndex[i-2]%13)
				{
					lastId=lastIndex[i]%13;
				}
				if(cardIndex[i]%13==cardIndex[i-1]%13&&lastIndex[i-1]%13==lastIndex[i-2]%13)
				{
					ownId=cardIndex[i]%13;
				}
			}
			if(ownId>lastId)
			{
				return true;
			}else 
			{
				return false;
			}
		case FEIJI_WU_ZERO:			//飞机 50
			lastId=lastIndex[0]%13;
			ownId=cardIndex[0]%13;
			if(ownId>lastId)
			{
				return true;
			}else 
			{
				return false;
			}
		
		case ZHA_DAN:				//炸弹
			lastId=lastIndex[0]%13;
			ownId=cardIndex[0]%13;
			if(ownId>lastId)
			{
				return true;
			}else 
			{
				return false;
			}
		}
		return false;
	}
	public static int[] getCompareCards(int index,int lastornext,int[] playerCards) 	//比较
	{
		int newCards[]=null;					//新的数组，提示数组
		int lastSort=-1;
		int lastCards[];		
		if(lastornext==0)				//	0 	上一家
		{
			lastSort=CardDistribution.getLastCardSort(index);	//上一玩家的牌的类型
			lastCards=CardDistribution.getLastCard(index);		//上一玩家牌的索引数组
		}else 							//1		下一家
		{
			lastSort=CardDistribution.getNextCardSort(index);	//上一玩家的牌的类型
			lastCards=CardDistribution.getNextCard(index);		//上一玩家牌的索引数组
		}
		
//		int lastSort=4;
//		int lastCards[]=new int[5];
//		lastCards[0]=21;
//		lastCards[1]=8;
//		lastCards[2]=28;
//		lastCards[3]=15;
//		lastCards[4]=2;
		
		
		int playdan=-1;
		int playsan=-1;
		int playdui=-1;
		int playShun=-1;
		int lastSan=-1;
		int lastShun=-1;
		switch(lastSort)
		{
			case 0:	//单
				newCards=new int[1];
				for(int i=playerCards.length-1;i>=0;i--)			//从扑克牌小的地方遍历，选出一个较小的
				{
					if(playerCards[i]==52&&lastCards[0]!=53)
					{
						newCards[0]=playerCards[i];
						break;
					}else if(playerCards[i]%13>lastCards[0]%13||playerCards[i]==53)
					{
						newCards[0]=playerCards[i];
						break;
					}
				}
				break;
			case 1://dui
				newCards=new int[2];
				for(int i=playerCards.length-1;i>0;i--)			//对子
				{
					if(playerCards[i]%13==playerCards[i-1]%13&&playerCards[i]%13>lastCards[0]%13)
					{
						newCards[0]=playerCards[i-1];
						newCards[1]=playerCards[i];
						break;
					}
				}
				break;
			case 2:
				newCards=new int[3];
				for(int i=playerCards.length-1;i>1;i--)			//三张
				{
					if(playerCards[i]%13==playerCards[i-1]%13&&playerCards[i-1]%13==playerCards[i-2]%13
							&&playerCards[i]%13>lastCards[0]%13)
					{
						newCards[0]=playerCards[i-2];
						newCards[1]=playerCards[i-1];
						newCards[2]=playerCards[i];
						break;
					}
				}
				break;
			case 3:
				playdan=-1;
				playsan=-1;
				lastSan=-1;
				newCards=new int[4];
				for(int i=0;i<3;i++)				//判断上一家牌的三个相同的牌的
				{
					if(lastCards[i]%13==lastCards[i+1]%13)
					{
						lastSan=lastCards[i]%13;
						continue;
					}
				}
				for(int i=0;i<playerCards.length-2;i++)			//  遍历出三个相同的牌的id
				{
					if(i>1&&playerCards[i]%13==playerCards[i+1]%13&&playerCards[i+1]%13==playerCards[i+2]%13
							&&playerCards[i]%13>lastSan)
					{
						playsan=i;				//三个相同的
						continue;
					}
				}
				for(int i=0;i<playerCards.length-1;i++)				// 遍历出单
				{
					if(playerCards[i]%13!=playerCards[i+1]%13)
					{
						playdan=i+1;
						continue;
					}
				}
				if(playsan!=-1&&playdan!=-1)						//如果遍历到三个相同的，和一个单的
				{
					if(playsan>playdan)				//如果相同的id大于单的id
					{
						newCards[0]=playerCards[playdan];
						newCards[1]=playerCards[playsan];
						newCards[2]=playerCards[playsan+1];
						newCards[3]=playerCards[playsan+2];
					}
					else if(playsan<playdan)		//如果相同的id小于单的id
					{	
						newCards[0]=playerCards[playsan];
						newCards[1]=playerCards[playsan+1];
						newCards[2]=playerCards[playsan+2];
						newCards[3]=playerCards[playdan];
					}
				}
				break;
			case 4:							//三代二
				playdui=-1;
				playsan=-1;
				lastSan=-1;
				newCards=new int[5];
				for(int i=0;i<3;i++)				//判断上一家牌的三个相同的牌的
				{
					if(lastCards[i]%13==lastCards[i+1]%13&&lastCards[i+1]%13==lastCards[i+2]%13)
					{
						lastSan=lastCards[i]%13;
						continue;
					}
				}
				for(int i=0;i<playerCards.length-2;i++)			//  遍历出三个相同的牌的id
				{
					if(playerCards[i]%13==playerCards[i+1]%13&&playerCards[i+1]%13==playerCards[i+2]%13
							&&playerCards[i]%13>lastSan)
					{
						playsan=i;				//三个相同的
						continue;
					}
				}
				
				if(playerCards[playerCards.length-2]%13==playerCards[playerCards.length-1]%13
					&&playerCards[playerCards.length-3]%13!=playerCards[playerCards.length-2]%13)
				{
					playdui=playerCards.length-2;
				}else
				{
					for(int i=1;i<playerCards.length-2;i++)				// 遍历出dui
					{
						if(playerCards[i]%13==playerCards[i+1]%13&&playerCards[i-1]%13!=playerCards[i]%13
								&&playerCards[i+1]%13!=playerCards[i+2]%13)
						{
							playdui=i;
							continue;
						}
					}
				}
				if(playdui==-1&&playerCards[0]%13==playerCards[1]%13
						&&playerCards[1]%13!=playerCards[2]%13)
				{
					playdui=0;
				}
				if(playsan!=-1&&playdui!=-1)
				{
					if(playsan>playdui)				//如果相同的id大于单的id
					{
						newCards[0]=playerCards[playdui];
						newCards[1]=playerCards[playdui+1];
						newCards[2]=playerCards[playsan];
						newCards[3]=playerCards[playsan+1];
						newCards[4]=playerCards[playsan+2];
					}
					else if(playsan<playdui)		//如果相同的id小于单的id
					{	
						newCards[0]=playerCards[playsan];
						newCards[1]=playerCards[playsan+1];
						newCards[2]=playerCards[playsan+2];
						newCards[3]=playerCards[playdui];
						newCards[4]=playerCards[playdui+1];
					}
				}
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:	
				playShun=-1;
				lastShun=-1;
				newCards=new int[5];
				if(playsan!=-1&&playdui!=-1)
				{
					if(playsan>playdui)				//如果相同的id大于单的id
					{
						newCards[0]=playerCards[playdui];
						newCards[1]=playerCards[playdui+1];
						newCards[2]=playerCards[playsan];
						newCards[3]=playerCards[playsan+1];
						newCards[4]=playerCards[playsan+2];
					}
					else if(playsan<playdui)		//如果相同的id小于单的id
					{	
						newCards[0]=playerCards[playsan];
						newCards[1]=playerCards[playsan+1];
						newCards[2]=playerCards[playsan+2];
						newCards[3]=playerCards[playdui];
						newCards[4]=playerCards[playdui+1];
					}
				}
				break;
			case 8:
				break;
			case 9:
				break;
			case 10:
				break;
			case 11:
				break;
			case 12:
				break;
			
			
		}

		return newCards;
	}
	
	
}
