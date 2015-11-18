package com.bn;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class LayerViewPanel extends JPanel
implements MouseListener
{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	MapPanel father;
	int num=0;
	int Map_num=Constant.Map_height/Constant.Screen_height;
	public boolean flag=false;
	public boolean del=false;
	
	public LayerViewPanel(MapPanel father)		//构造器
	{
		this.father=father;
		this.setPreferredSize(new Dimension(Constant.Map_width,Constant.Map_height));	//画布大小
		this.addMouseListener(this);

	}
	
	public void paint(Graphics g)
	{
		Image imgBack=(new ImageIcon("res\\"+"gameBackground.png")).getImage();				//画背景
		for(int i=0;i<=Map_num;i++)
		{
			g.drawImage(imgBack,0,i*Constant.Screen_height,Constant.Map_width,Constant.Screen_height,this);
		}
		
		if(flag)
		{
			
			
			for(int i=0;i<father.alMapItem.size();i++)
			{
				Item item=((Item)(father.alMapItem.get(i)));		
				item.draw(g, this,father.ls.get(i*3+1),father.ls.get(i*3+2));
			//	item.draw(g, this);
			}
			System.out.println("alMapItem "+father.alMapItem.size());
		}
		
	}
	public void mousePressed(MouseEvent e){}
	public void mouseReleased(MouseEvent e){}
	public void mouseEntered(MouseEvent e){}
	public void mouseExited(MouseEvent e){}
	
	public void mouseClicked(MouseEvent e)
	{
		int mx=e.getX();
		int my=e.getY();
		
		if(del)
		{
			flag=false;
			int length=father.ls.size();
			int a[]=new int[length/3];
			int temp=0;
			int count=0;
			
			for(int i=0;i<length;i+=3)
			{
				a[i/3]=(father.ls.get(i+1)-mx)*(father.ls.get(i+1)-mx)+(father.ls.get(i+2)-my)*(father.ls.get(i+2)-my);
			}
			temp=a[0];
			for(int j=0;j<length/3;j++)
			{
				if(a[j]<temp)
				{
					temp=a[j];
					count=j;
				}
			}
			father.ls.remove(count*3+2);
			father.ls.remove(count*3+1);
			father.ls.remove(count*3);
			father.alMapItem.remove(count);
			System.out.println("count "+count);
			flag=true;
		//	del=false;
		}
		else
		{
			Item item=((Item)(father.jls.getSelectedValue()));
			if(item==null)
			{
				return;
			}
	
			father.alMapItem.add(item);
//			item.setPosition(mx, my);
			
			father.ls.add(item.num);
			father.ls.add(mx);
			father.ls.add(my);
		}

		flag=true;

		this.repaint();
			
	}
	
}