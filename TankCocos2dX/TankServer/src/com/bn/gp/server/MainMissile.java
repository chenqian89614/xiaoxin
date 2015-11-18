package com.bn.gp.server;

public class MainMissile
{
	float missileX,missileY;
	float angle=90;
	int targetX,targetY;
	float speed=10;
	public MainMissile(int missileX,int missileY,int targetX,int targetY)
	{
		this.missileX=missileX;
		this.missileY=missileY;
		this.targetX=targetX;
		this.targetY=targetY;
	}
	
	public void go()
	{
		missileX=missileX+(float)(speed*Math.cos(Math.toRadians(450-angle)));
		missileY=missileY-(float)(speed*Math.sin(Math.toRadians(450-angle)));
		double temp=Math.toDegrees(Math.atan2(missileY-targetY, targetX-missileX));
		if(temp>90)
		{
			temp=450-temp;
		}
		else
		{
			temp=90-temp;
		}
		float a=(float) ((temp-angle>0)?(temp-angle):(360+angle-temp));
		if(a>180)
		{
			angle=(angle-3>=0)?(angle-3):(angle-3+360);
		}
		else
		{
			angle=(angle+3<360)?(angle+3):(angle+3-360);
		}
	}
}