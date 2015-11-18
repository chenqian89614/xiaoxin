package com.bn.server;

import java.net.*;
import java.util.*;

import com.bn.data.GameData;

public class ServerThread extends Thread
{
	boolean flag=true;
	Map<String,ServerAgentThread> cmap=new HashMap<String,ServerAgentThread>();	
	ServerSocket ss;
	public void run()
	{
		try{
			ss=new ServerSocket(9999);
			System.out.println("Server Listening on 9999...");
		}catch(Exception e){
			e.printStackTrace();
		}
		while(flag){
			try{
				Socket sc=ss.accept();
				ServerAgentThread sat=new ServerAgentThread(sc,this);
				sat.start();			
				String address=sc.getInetAddress().toString().trim();//��ȡIP��ַ
				System.out.println(address+"   connect...");
				cmap.put(address,sat);									
				GameData.clientList.add(address);		//���IP��ַ���б���
				sat.broadcastConnect();					//�����Ѿ�����
			}
			catch(Exception e){
				e.printStackTrace();
	}}}
	public static void main(String args[]){
		new ServerThread().start();
}}
