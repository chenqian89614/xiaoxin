package com.bn.util;
import java.io.*;

public class IOUtil 
{
	public static void sendFloat(DataOutputStream dout,float a) throws Exception
	{
		byte[] buf=ConvertUtil.fromFloatToBytes(a);
		dout.write(buf);		//����
		dout.flush();			//��������
	}
	
	public static void sendInt(DataOutputStream dout,int a) throws Exception
	{
		byte[] buf=ConvertUtil.fromIntToBytes(a);
		dout.write(buf);
		dout.flush();
	}
	
	public static void sendStr(DataOutputStream dout,String str) throws Exception
	{
		byte[] buf=ConvertUtil.fromStringToBytes(str);
		sendInt(dout,buf.length); 	//����
		dout.write(buf);			//����
		dout.flush();				//��������
	}	
	
	//���յ�������ת����int,float,string
	
	public static int readInt(DataInputStream din) throws Exception				//�յ��ĵ�����
	{
		byte[] buf=new byte[4];
		for(int i=0;i<4;i++)
		{
			buf[i]=1;
		}
		int count=0;
		while(count<4)
		{
			int tc=din.read(buf);
			count=count+tc;
		}		
		return ConvertUtil.fromBytesToInt(buf);
	}
	
	public static float readFloat(DataInputStream din) throws Exception			//�յ��ĸ�����
	{
		byte[] buf=new byte[4];
		int count=0;
		while(count<4)
		{
			int tc=din.read(buf);
			count=count+tc;
		}		
		return ConvertUtil.fromBytesToFloat(buf);
	}
	
	public static String readStr(DataInputStream din) throws Exception			//�յ����ַ���
	{
		//�����ַ�������
		int len=readInt(din);	
		byte[] buf=new byte[len];
		int count=0;
		while(count<len)
		{
			int tc=din.read(buf);
			count=count+tc;
		}		
		return ConvertUtil.fromBytesToString(buf);
	}
}
