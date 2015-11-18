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
		 this.setText("编号:"+item.num+" 宽度: "+item.width+"高度: "+item.height);
		 
		 if(isSelected)
		 {
		 	setBackground(Color.red);//选中的颜色
		 }
		 else
		 {
			 setBackground(Color.yellow);//未选中的颜色
		 }
		 
			 this.setPreferredSize(new Dimension(300,66));
			 
			 return this;
		 }
}
