package com.bn;

import javax.swing.*;

public class CodeFrame extends JFrame
{

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	JTextArea  jta=new JTextArea();
	JScrollPane jsp=new JScrollPane(jta);
	
	public CodeFrame(String s)
	{
		this.setTitle("生成的地图数据");
		this.setBounds(200, 100,400,300);
		
		jta.setText(s);
		this.add(jsp);
		this.setVisible(true);
	}
}
