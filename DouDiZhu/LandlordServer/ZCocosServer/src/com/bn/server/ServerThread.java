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
				String address=sc.getInetAddress().toString().trim();//获取IP地址
				System.out.println(address+"   connect...");
				cmap.put(address,sat);									
				GameData.clientList.add(address);		//添加IP地址到列表中
				sat.broadcastConnect();					//发送已经连接
			}
			catch(Exception e){
				e.printStackTrace();
	}}}
	public static void main(String args[]){
		new ServerThread().start();
}}
