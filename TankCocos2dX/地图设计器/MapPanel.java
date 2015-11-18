package com.bn;

import java.util.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

public class MapPanel extends JPanel
implements ActionListener
{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	LayerViewPanel lvp=new LayerViewPanel(this);		
	JScrollPane jsp=new JScrollPane(lvp);
	
	Boolean a=true;
	
	JButton jbIn=new JButton("����Ԫ��");
	JButton jDel=new JButton("ɾ��Ԫ��");
//	JButton jdel=new JButton("ɾ��ͼƬ");
	JRadioButton jPic[]={new JRadioButton("���Ƶ�ͼ",true),new JRadioButton("ɾ����ͼ")};
	
	ButtonGroup bg=new ButtonGroup();
	
	JButton jclear=new JButton("��յ�ͼ");
	JButton jSave=new JButton("�����ͼ");
	JButton jDown=new JButton("���ص�ͼ");
	JButton jcreate=new JButton("���ɵ�ͼ");
	
	JLabel jNameL=new JLabel("�ļ�����:");
	JTextField jName=new JTextField();
	
	Image tempImage;
	String imagePath;		//ͼƬ·��
	String num[]={"0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16"};				//���
	
	JList jls=new JList();
	JScrollPane jspL=new JScrollPane(jls);
	
	JLabel jNumL=new JLabel("������:");
	JComboBox jNumC=new JComboBox(num);
	JFileChooser jfOpen=new JFileChooser(".\\res");
	
	ArrayList<Item> alItem=new ArrayList<Item>();			//Ԫ��
	
	ArrayList<Item> alMapItem=new ArrayList<Item>();		//��ͼ
	ArrayList<Integer> ls=new ArrayList<Integer>();			//��ͼ����  ����ţ�X,Y��
	
	MapFrame father;
	public MapPanel(MapFrame father)
	{
		this.father=father;
		
		this.setLayout(null);

		this.add(jsp);						//��ͼ
		jsp.setBounds(10,50,900,540);
		
		this.add(jbIn);						//����ͼƬ��ť
		jbIn.setBounds(930,100,100,30);
		jbIn.addActionListener(this);
		
		this.add(jDel);						//ɾ��Ԫ�ذ�ť
		jDel.setBounds(930,150,100,30);
		jDel.addActionListener(this);
		
//		this.add(jdel);						//ɾ��ͼshangyiƬ��ť
//		jdel.setBounds(930, 200, 100, 30);
//		jdel.addActionListener(this);
		
		this.add(jPic[0]);					//���Ƶ�ͼ
		jPic[0].setBounds(930,250, 100, 30);
		jPic[0].setFont(new Font("����",Font.BOLD,15));
		jPic[0].addActionListener(this);
		
		this.add(jPic[1]);					//ɾ��ָ��ͼƬ
		jPic[1].setBounds(930,300, 100, 30);
		jPic[1].setFont(new Font("����",Font.BOLD,15));
		jPic[1].addActionListener(this);
		
		bg.add(jPic[0]);
		bg.add(jPic[1]);
		
		this.add(jclear);					//��յ�ͼ��ť
		jclear.setBounds(930, 400, 100, 30);
		jclear.addActionListener(this);
		
		this.add(jcreate);					//���ɵ�ͼ���밴ť
		jcreate.setBounds(930,450, 100, 30);
		jcreate.addActionListener(this);
		
		this.add(jNumL);					//��ű�ǩ
		jNumL.setFont(new Font("����",Font.BOLD,15));
		jNumL.setBounds(1050,50,80,30);
		
		this.add(jNumC);					//��������б�
		jNumC.setBounds(1130,50,100,30);
		
		this.add(jspL);						//Ԫ���б�
		jspL.setBounds(1050,100,200,400);
		
		this.add(jSave);					//�洢��ͼ
		jSave.setBounds(1050,550, 100, 30);
		jSave.addActionListener(this);
		
		this.add(jNameL);					//�����ļ����Ʊ�ǩ
		jNameL.setFont(new Font("����",Font.BOLD,13));
		jNameL.setBounds(1050, 510, 70, 30);
		
		this.add(jName);
		jName.setBounds(1130, 510, 80, 30);
		
		this.add(jDown);					//���ص�ͼ
		jDown.setBounds(1170,550, 100, 30);
		jDown.addActionListener(this);
		
		jls.setCellRenderer(new MyCellRenderer());	//Ԫ���б��Զ����ʽ
		
	}
	
	public void flush()		//ˢ��Ԫ��
	{
		jls.setListData(alItem.toArray());
	}
	
	public void actionPerformed(ActionEvent e)
	{
		if(e.getSource()==jbIn)						//����ͼƬ��ť
		{
			int jfile=jfOpen.showOpenDialog(this);
			if(jfile==JFileChooser.APPROVE_OPTION)
			{
				tempImage=(new ImageIcon(jfOpen.getSelectedFile().getAbsolutePath())).getImage();
				imagePath="res\\"+jfOpen.getSelectedFile().getName();
				
				if(tempImage!=null)
				{
					Item item=new Item
					(
						tempImage,
						imagePath,
						tempImage.getWidth(this),
						tempImage.getHeight(this),
						jNumC.getSelectedIndex()
					);
					alItem.add(item);
					this.flush();
					jNumC.setSelectedIndex(jNumC.getSelectedIndex()+1);
				}
			}
		}else if(e.getSource()==jDel)				//ɾ��Ԫ��
		{
			int n=jls.getSelectedIndex();
			if(n>=0)
			{
				alItem.remove(n);
			}
			
			this.flush();							//ˢ��Ԫ���б�
			
		}
		else if(e.getSource()==jcreate)				//���ɵ�ͼ����	
		{
			System.out.println("data "+"asdfasdfasdf");
			String data="public static int[] mapData={";
			String tree="public static int[] mapTree={";
			String tank="public static int[] mapTank={";
			int dataI=0,treeI=0,tankI=0;
			for(int i=0;i<ls.size();i+=3)
			{
				int num=ls.get(i);
				if(num==0||num==1)
				{
					tree = addData(tree, treeI, i, num);
					treeI++;
				}
				else if(num>=8&&num<=11)
				{
					tank = addData(tank, tankI, i, num);
					tankI++;
				}
				else
				{
					data = addData(data, dataI, i, num);
					dataI++;
				}
			}
			tree=tree.substring(0,tree.length()-1)+"\n};";
			tank=tank.substring(0,tank.length()-1)+"\n};";
			data=data.substring(0,data.length()-1)+"\n};";
			
			new CodeFrame(data+"\n\n"+tree+"\n\n"+tank);
		}
		else if(e.getSource()==jSave)							//�����ͼ����
		{	
			String name=jName.getText();
			if(name.equals(""))
			{
				JOptionPane.showMessageDialog(null, "�������ļ���");
				return;
			}
			try 
			{
				FileOutputStream fout=new FileOutputStream(name+"1.wht");	//����Ԫ��
				ObjectOutputStream out=new ObjectOutputStream(fout);
				
				Item []item=ListToArray(alItem);
				Item itemMap[]=ListToArray(alMapItem);
				
				out.writeObject(item);
				out.writeObject(itemMap);
				fout.close();
				out.close();
				
				FileOutputStream fouts=new FileOutputStream(name+"2.wht");	//�����ͼ
				DataOutputStream outs=new DataOutputStream(fouts);

				int []temp=new int[ls.size()];
				for(int i=0;i<ls.size();i++)
				{
					temp[i]=ls.get(i);
				}
				
				outs.writeInt(temp.length);
				
				for(int j=0;j<temp.length;j++)
				{
					outs.writeInt(temp[j]);
				}
				fouts.close();
				outs.close();
				
				System.out.println("  cunru  ");
				JOptionPane.showMessageDialog( null,"�������ݳɹ�");
			} catch (Exception  e1) 
			{
				e1.printStackTrace();
			}
		}
		else if(e.getSource()==jDown)						//���ص�ͼ����
		{
			String name=jName.getText();
			if(name.equals(""))
			{
				JOptionPane.showMessageDialog(null, "�������ļ���");
				return;
			}
			try
			{
				FileInputStream fin=new FileInputStream(name+"1.wht");		//����Ԫ��
				ObjectInputStream oin=new ObjectInputStream(fin);
				
				alItem=ArrayToList((Item[])oin.readObject());
				alMapItem=ArrayToList((Item[])oin.readObject());
				
				fin.close();
				oin.close();
				
				FileInputStream fins=new FileInputStream(name+"2.wht");		//���յ�ͼ
				DataInputStream oins=new DataInputStream(fins);
	
				int length=oins.readInt();
				for(int i=0;i<length;i++)
				{
					ls.add(oins.readInt());
				}
				
				fins.close();
				oins.close();
		
				this.flush();
				lvp.flag=true;
				lvp.repaint();
				JOptionPane.showMessageDialog(null, "��ȡ���");
				
			}catch(Exception e2)
			{
				e2.printStackTrace();
			}
		}
		else if(e.getSource()==jclear)			// ��յ�ͼ
		{
			ls.clear();
			alMapItem.clear();
			lvp.repaint();
		}
		else if(jPic[1].isSelected())
		{
			lvp.del=true;
		}
		else if(jPic[0].isSelected())
		{
			lvp.del=false;
		}
		
	}

	private String addData(String data, int dataI, int i, int num) 
	{
		if(dataI%15==0)
		{
			data=data.substring(0, data.length())+"\n";
		}
		data+=num+",";
		data+=ls.get(i+1)+",";
		data+=ls.get(i+2)-(Constant.Map_height-Constant.Screen_height)+",";
		return data;
	}
	public Item[] ListToArray(ArrayList<Item> tempMap)
	{
		Item []item=new Item[tempMap.size()];
		for(int i=0;i<tempMap.size();i++)
		{
			item[i]=tempMap.get(i);
		}
		return item;
	}
	public ArrayList<Item> ArrayToList(Item []item)
	{
		ArrayList<Item> tempMap=new ArrayList<Item>();
		for(int i=0;i<item.length;i++)
		{
			tempMap.add(item[i]);
		}
		return tempMap;
	}
}