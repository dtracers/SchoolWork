package GUI;

import java.awt.Graphics;
import java.util.ArrayList;

import javax.swing.JPanel;

public class MyButtonPanel extends JPanel
{
	ArrayList<MyJButton> paintList;
	ArrayList<MyJButton> otherList;
	public void addMyButton(MyJButton j,boolean b)
	{
		if(b)
		{
			otherList.add(j);
			this.add(j);
		}else
			paintList.add(j);
	}
	public void removeMyButton(MyJButton j)
	{
		paintList.remove(j);
	}
	public void removeAllButtons()
	{
		paintList=new ArrayList<MyJButton>();
		for(MyJButton b:otherList)
		{
			this.remove(b);
		}
		otherList=new ArrayList<MyJButton>();
	}
	public void paint(Graphics g)
	{
		super.paint(g);
		for(MyJButton j:paintList)
		{
			j.draw(g);
		}
	}
	public MyButtonPanel()
	{
		super();
		paintList=new ArrayList<MyJButton>();
		otherList=new ArrayList<MyJButton>();
	}
}
