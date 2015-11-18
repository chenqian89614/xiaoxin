package com.bn.gp.server;

import com.bn.gp.data.GameData;


public class OtherBullet
{
	public float bulletX;
	public float bulletY;
	public float angle;
	public float sort;
	
	public OtherBullet(int sort,int bulletX, int bulletY, float angle)
	{
		this.bulletX=(bulletX+(float) (40*Math.cos(Math.toRadians(450-angle))));
		this.bulletY=(bulletY-(float) (40*Math.sin(Math.toRadians(450-angle))));
		this.angle=angle;
		this.sort=sort;
	}
	
	public void go()
	{
		bulletX=(bulletX+(float)(GameData.otherbulletSpeed*Math.cos(Math.toRadians(450-angle))));
		bulletY=(bulletY-(float)(GameData.otherbulletSpeed*Math.sin(Math.toRadians(450-angle))));
	}

}