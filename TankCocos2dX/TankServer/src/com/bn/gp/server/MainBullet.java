package com.bn.gp.server;

import com.bn.gp.data.GameData;

public class MainBullet
{
	public float bulletX;
	public float bulletY;
	public float angle;
	public int sort;
	
	public MainBullet(int bulletX, int bulletY, float angle)
	{
		this.bulletX=bulletX+(float) (40*Math.cos(Math.toRadians(450-angle)));
		this.bulletY=bulletY-(float) (40*Math.sin(Math.toRadians(450-angle)));
		this.angle=angle;
	}
	
	public void go()
	{
		bulletX=bulletX+(float)(GameData.bulletSpeed*Math.cos(Math.toRadians(450-angle)));
		bulletY=bulletY-(float)(GameData.bulletSpeed*Math.sin(Math.toRadians(450-angle)));
	}

}