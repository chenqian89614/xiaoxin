package com.bn.gp.server;

import com.bn.gp.action.Action;
import com.bn.gp.data.GameData;

public class MainTank extends Action
{
	
	int redOrGreen;//0-red 1-green	
	float offsetX;
	float offsetY;
	float offX;
	float offY;
	float gunOffsetX;
	float gunOffsetY;
	
	public MainTank(int redOrGreen,float leftOffsetX,float leftOffsetY,float rightOffsetX,float rightOffsetY)
	{
		this.redOrGreen=redOrGreen;
		this.offsetX=leftOffsetX;
		this.offsetY=leftOffsetY;
		this.gunOffsetX=rightOffsetX;
		this.gunOffsetY=rightOffsetY;
	}
	
	@Override
	public void doAction()
	{
		if(gunOffsetX!=0&&gunOffsetY!=0)
		{
			if(redOrGreen==0)
			{
				float f1=toAngle(gunOffsetX, gunOffsetY);
				synchronized(GameData.lock)
				{
					GameData.redGunAngle=f1;
				}
			}
			else
			{
				float f2=toAngle(gunOffsetX, gunOffsetY);
				synchronized(GameData.lock)
				{
					GameData.greenGunAngle=f2;
				}
			}
		}
		if(offsetY!=0||offsetX!=0)
		{
			moveTank();
		}
		ServerAgent.broadcastTank();
	}

	private void moveTank() {
		int redX,redY,greenX,greenY,redHealth,greenHealth;
		float redAngle,greenAngle;
		synchronized(GameData.lock)
		{
			redX=GameData.redX;
			redY=GameData.redY;
			greenX=GameData.greenX;
			greenY=GameData.greenY;
			redHealth=GameData.redHealth;
			greenHealth=GameData.greenHealth;
			redAngle=GameData.redTankAngle;
			greenAngle=GameData.greenTankAngle;
		}
		float angle=(float) Math.atan(offsetY/offsetX);
		if(offsetX>0)
		{
			offX=(float) (GameData.tankSpeed*Math.cos(angle));
			offY=(float) (GameData.tankSpeed*Math.sin(angle));
		}
		else
		{
			offX=(float) (-GameData.tankSpeed*Math.cos(angle));
			offY=(float) (-GameData.tankSpeed*Math.sin(angle));
		}
		if(redOrGreen==0&&redHealth>0)
		{
			int redXR=redX;
			int redYR=redY;
			redX+=offX;
			redY+=offY;
			redAngle=toAngle(offX,offY);
			if(redX>GameData.baseWidth-GameData.sideSize||redX<GameData.sideSize)
			{
				redX=redXR;
			}
			if(redY>GameData.baseHeight-GameData.sideSize||redY<GameData.sideSize)
			{
				redY=redYR;
			}
			if(Collision.checkCollision(redX, redY, greenX, greenY, redAngle, greenAngle, 0, 0))
			{
				redX=redXR;
				redY=redYR;
			}
			if(Collision.checkCollision(redX, redY, redAngle, 0))
			{
				int hurt=10;
				redHealth=(redHealth-hurt>0)?(redHealth-hurt):0;
				if(redHealth==0)
				{
					synchronized(GameData.lock)
					{
						GameData.redX=-1000;
						GameData.redY=-1000;
					}
				}
			}
			synchronized(GameData.lock)
			{
				GameData.redHealth=redHealth;
				GameData.redX=redX;
				GameData.redY=redY;
				GameData.redTankAngle=redAngle;
				GameData.tankFlag[0]=10;
			}
		}
		else if(greenHealth>0)
		{
			int greenXR=greenX;
			int greenYR=greenY;
			greenX+=offX;
			greenY+=offY;
			greenAngle=toAngle(offX,offY);
			if(greenX>GameData.baseWidth-GameData.sideSize||greenX<GameData.sideSize)
			{
				greenX=greenXR;
			}
			if(greenY>GameData.baseHeight-GameData.sideSize||greenY<GameData.sideSize)
			{
				greenY=greenYR;
			}
			if(Collision.checkCollision(redX, redY, greenX, greenY, redAngle, greenAngle, 0, 0))
			{
				greenX=greenXR;
				greenY=greenYR;
			}
			if(Collision.checkCollision(greenX, greenY, greenAngle, 0))
			{
				int hurt=10;
				greenHealth=(greenHealth-hurt>0)?(greenHealth-hurt):0;
				if(greenHealth==0)
				{
					synchronized(GameData.lock)
					{
						GameData.greenX=-1000;
						GameData.greenY=-1000;
					}
				}
			}
			synchronized(GameData.lock)
			{
				GameData.greenHealth=greenHealth;
				GameData.greenX=greenX;
				GameData.greenY=greenY;
				GameData.greenTankAngle=greenAngle;
				GameData.tankFlag[1]=10;
			}
		}
	}
	
	private float toAngle(float dx, float dy) 
	{
		float tempAngle=(float) Math.toDegrees(Math.atan(dy/dx));
		if(dx==0)
		{
			if(dy>0)
			{
				tempAngle=180;
			}else
			{
				tempAngle=0;
			}
		}
		else if(dx>0)
		{
			tempAngle=90+tempAngle;
		}else if(dx<0)
		{
			tempAngle=270+tempAngle;
		}
		return tempAngle;
	}
}