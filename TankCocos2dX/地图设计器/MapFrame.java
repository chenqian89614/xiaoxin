package com.bn;
 
import javax.swing.*;

public class MapFrame extends JFrame
{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	MapPanel mp;
	
	public MapFrame(int width,int height)
	{

		this.setTitle("µØÍ¼Éè¼ÆÆ÷");
		this.setBounds(30,30,1300,650);	
		
		Constant.Map_width=width;
		Constant.Map_height=height;
		
		mp=new MapPanel(this);
		this.add(mp);
		this.setVisible(true);
	}

}