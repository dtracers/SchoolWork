package GUI;
/*This Class contains methods used within the Display and Menu files.
 * It's a simpler way of creating buttons with images;
 */

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
			System.out.println("ADDING A TRUE BUTTON");
			otherList.add(j);
		}else
			paintList.add(j);
	}
	//remove an individual button
	public void removeMyButton(MyJButton j)
	{
		paintList.remove(j);
	}
	//remove all the buttons
	public void removeAllButtons()
	{
		for(MyJButton b:paintList)
		{
			b.setDeleted(true);
		}
		paintList=new ArrayList<MyJButton>();
		for(MyJButton b:otherList)
		{
			System.out.println("OTHER LIST");
			this.remove(b);
		}
		otherList=new ArrayList<MyJButton>();
	}
	//paints the button images 
	public void paint(Graphics g)
	{
		super.paintComponents(g);
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
