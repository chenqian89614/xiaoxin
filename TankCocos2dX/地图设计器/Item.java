package com.bn;

import java.io.*;
import java.awt.*;
import java.awt.image.*;
import javax.swing.*;

public class Item implements Externalizable
{
	static final long serialVersionUID = 3243660019996329628L;
	
	Image img;
	String imgPath;
	int width;
	int height;
	int X;
	int Y;
	int num;
	
	public Item()
	{
	}
	public Item(Image img,String imgPath,int width,int height,int num)
	{
		this.img=img;
		this.imgPath=imgPath;
		this.width=width;
		this.height=height;
		this.num=num;
		
	}
//	public void setPosition(int x,int y)
//	{
//		this.X=x;
//		this.Y=y;	
//		System.out.println("  x "+x+"  y "+y);
//	}
	
	public void draw(Graphics g,ImageObserver io,int X,int Y)
	{				
		g.drawImage(img,X-width/2,Y-height/2,io);
	}
	
	@Override
	public void readExternal(ObjectInput input) throws IOException,
			ClassNotFoundException 
	{
		imgPath=(String)input.readObject();
		img=new ImageIcon(imgPath).getImage();
		
		width=input.readInt();
		height=input.readInt();
		
	}

	@Override
	public void writeExternal(ObjectOutput output) throws IOException 
	{
		output.writeObject(imgPath);
		output.writeInt(width);
		output.writeInt(height);
	}

}