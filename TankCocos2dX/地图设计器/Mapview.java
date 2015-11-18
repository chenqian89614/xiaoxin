package com.bn;

import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JTextField;

public class Mapview extends JFrame
implements ActionListener
{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	JLabel widthL=new JLabel("地图长度:");
	JLabel heightL=new JLabel("地图宽度:");
	
	JTextField widthT=new JTextField();
	JTextField heightT=new JTextField();
	
	JButton jOk=new JButton("确定");
	
	public Mapview()
	{
		this.setLayout(null);
		this.setTitle("地图大小");
		this.setBounds(500, 250, 400,180);
		
		this.add(widthL);
		widthL.setFont(new Font("宋体",Font.BOLD,15));
		widthL.setBounds(20, 30, 100, 30);
		
		this.add(heightL);
		heightL.setFont(new Font("宋体",Font.BOLD,15));
		heightL.setBounds(20, 80, 100, 30);
		
		this.add(widthT);
		widthT.setBounds(150, 30, 100, 30);
		
		this.add(heightT);
		heightT.setBounds(150, 80, 100, 30);
		
		this.add(jOk);
		jOk.setBounds(280, 30, 100, 30);
		jOk.addActionListener(this);
		
		this.setVisible(true);
	}

	@Override
	public void actionPerformed(ActionEvent e) 
	{
		if(e.getSource()==jOk)
		{
			int width= Integer.parseInt(widthT.getText().trim());
			int height=Integer.parseInt(heightT.getText().trim());
			
			new MapFrame(width,height);
			this.dispose();
		}
	}
	
	public static void main(String args[])
	{
		new Mapview();
	}
}
