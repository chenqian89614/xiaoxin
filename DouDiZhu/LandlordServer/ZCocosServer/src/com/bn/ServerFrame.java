package com.bn;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.DataOutputStream;

import javax.swing.*;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

import com.bn.util.IOUtil;

public class ServerFrame extends JFrame
{
	private static final long serialVersionUID = 1L;

	JList jlClients=new JList();
	JPanel jpRight=new JPanel();
	JSplitPane jsp=new JSplitPane(JSplitPane.HORIZONTAL_SPLIT,jlClients,jpRight);
	
	JTextArea jta=new JTextArea();
	JScrollPane jsps=new JScrollPane(jta);
	
	JComboBox jcb=new JComboBox(new String[]{"整数","浮点数","字符串"});
	JTextField jtf=new JTextField();
	JButton jb=new JButton("发送");
	JPanel jpx=new JPanel();
	
//	ServerThread st;
	
	public ServerFrame()
	{
		this.setTitle("Cocos2d-x 服务端");
		
		jlClients.addListSelectionListener							//给客户端列表添加监听
		(
		    new ListSelectionListener()
		    {
				@Override
				public void valueChanged(ListSelectionEvent e) 
				{
					if(jlClients.getSelectedValue()!=null)			//如果选择了任意的客户端
					{
//						jta.setText(st.cmap.get(jlClients.getSelectedValue().toString()).receiveContent);	//就在收到的文本框内显示内容
					}					
				}		    	
		    }
		);
		
		jsp.setDividerLocation(250);
		jsp.setDividerSize(4);
		this.add(jsp);
		
		jpx.setLayout(null);
		jcb.setBounds(10, 10, 120, 20);
		jpx.add(jcb);
		jtf.setBounds(10, 40, 200, 20);
		jpx.add(jtf);
		jb.setBounds(10, 70, 60, 20);
		jpx.add(jb);
		jb.addActionListener					//发送按钮监听
		(
			new ActionListener()
			{
				@Override
				public void actionPerformed(ActionEvent e) 
				{
					if(jlClients.getSelectedValue()!=null)
					{
					    try
					    {
					    	int code=jcb.getSelectedIndex();			//发送的类型
							if(code==0)
							{
//								DataOutputStream dout=st.cmap.get(jlClients.getSelectedValue().toString()).dout;
//								IOUtil.sendInt(dout, 0);
//								IOUtil.sendInt(dout, Integer.parseInt(jtf.getText().trim()));
							}
							else if(code==1)
							{
//								DataOutputStream dout=st.cmap.get(jlClients.getSelectedValue().toString()).dout;
//								IOUtil.sendInt(dout, 1);
//								IOUtil.sendFloat(dout, Float.parseFloat(jtf.getText().trim()));
							}
							else if(code==2)
							{
//								DataOutputStream dout=st.cmap.get(jlClients.getSelectedValue().toString()).dout;
//								IOUtil.sendInt(dout, 2);
//								IOUtil.sendStr(dout, jtf.getText().trim());
							}
					    }
						catch(Exception ea)
						{
							ea.printStackTrace();
						}
					}
				}				
			}
		);
		
		JSplitPane jspy=new JSplitPane(JSplitPane.VERTICAL_SPLIT,jsps,jpx);
		jspy.setDividerLocation(250);
		jspy.setDividerSize(4);
		jpRight.setLayout(new BorderLayout());
		jpRight.add(jspy);
		
		
		this.setBounds(100,100,800,600);
		this.setVisible(true);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
//		
//		st=new ServerThread(this);
//		st.start();
		
		
	}
	
	public static void main(String args[])
	{
		new ServerFrame();
	}
}
