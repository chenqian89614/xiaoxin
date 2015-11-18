package com.bn.gp.server;

import java.util.ArrayList;

public class DataUtil
{
	/**
	 * 将数组转化为集合
	 */
	public static ArrayList<Integer> arrayToList(int tempArray[])
	{
		ArrayList<Integer> tempList=new ArrayList<Integer>();
		if(tempArray.length==0)
		{
			return tempList;
		}
		for(int i=0;i<tempArray.length;i++)
		{
			tempList.add(tempArray[i]);
		}
		return tempList;
	}
	
	/**
	 * 将集合转化为数组
	 */
	public static int[] listToArray(ArrayList<Integer> tempList)
	{
		if(tempList.size()==0)
		{
			return null;
		}
		int[] tempArray=new int[tempList.size()];
		for(int i=0;i<tempList.size();i++)
		{
			tempArray[i]=tempList.get(i);
		}
		return tempArray;
	}
}