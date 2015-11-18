package com.bn;

import javax.swing.*;
import java.awt.*;

class MyCellRenderer extends JLabel implements ListCellRenderer 
{
     /**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	public MyCellRenderer() 
	{
	     setOpaque(true);
	}

    public Component getListCellRendererComponent(JList list,
                                                   Object value,
                                                   int index,
                                                   boolean isSelected,
                                                   boolean cellHasFocus) 
	{
	
		 Item item=(Item)value;
		 this.setIcon(new ImageIcon(item.img));
		 this.setText("���:"+item.num+" ���: "+item.width+"�߶�: "+item.height);
		 
		 if(isSelected)
		 {
		 	setBackground(Color.red);//ѡ�е���ɫ
		 }
		 else
		 {
			 setBackground(Color.yellow);//δѡ�е���ɫ
		 }
		 
			 this.setPreferredSize(new Dimension(300,66));
			 
			 return this;
		 }
}
