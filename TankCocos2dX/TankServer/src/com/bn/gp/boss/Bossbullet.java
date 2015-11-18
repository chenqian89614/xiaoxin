package com.bn.gp.boss;

import com.bn.gp.data.GameData;

public class Bossbullet 
{
	public float bulletX;
	public float bulletY;
	public float angle;
	public float sort;
	
	public Bossbullet(int sort,int bulletX,int bulletY,int Angle)
	{
		this.sort=sort;
		this.bulletX=(bulletX+(float) (40*Math.cos(Math.toRadians(450-angle))));
		this.bulletY=(bulletY-(float) (40*Math.sin(Math.toRadians(450-angle))));
		this.angle=Angle;
	}
	
	public void go()
	{
		bulletX=(bulletX+(float)(GameData.bossbulletSpeed*Math.cos(Math.toRadians(450-angle))));
		bulletY=(bulletY-(float)(GameData.bossbulletSpeed*Math.sin(Math.toRadians(450-angle))));
	}

}
