package GUI;

import java.awt.Graphics;
import java.awt.Image;
import java.awt.Rectangle;
import java.awt.Toolkit;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.TreeMap;

import javax.swing.ImageIcon;
import javax.swing.JButton;

public class MyJButton extends JButton implements MouseListener
{
	private static TreeMap<String,Image> images=new TreeMap<String,Image>();
	private Image myImage;
	private Rectangle bounds;
	private Method m;
	private Class c;
	private Object declare;
	private boolean normalButton=false; 
	public MyJButton(String name,int x,int y,int w,int h)
	{
		myImage=images.get(name);
		if(myImage==null)
		{
			myImage=loadImage(name);
			images.put(name, myImage);
		}
		bounds=new Rectangle(x,y,w,h);
	}
	public MyJButton(String name,int x,int y,int w,int h,String methodName,Class c,Object declare)
	{
		this(name,x,y,w,h);
		setAction(methodName,c,declare);
	}
	@Override
	public void mouseClicked(MouseEvent arg0)
	{
		
	}
	@Override
	public void mouseEntered(MouseEvent arg0)
	{
	}
	@Override
	public void mouseExited(MouseEvent arg0)
	{
	}
	@Override
	public void mousePressed(MouseEvent arg0)
	{
		if(bounds.contains(arg0.getPoint()))
		{
			System.out.println("button preessed");
			try
			{
				if(m!=null)
				{
					m.invoke(declare,null);
				}else
				{
					System.out.println("M is null");
				}
			} catch (IllegalArgumentException e)
			{
				e.printStackTrace();
			} catch (IllegalAccessException e)
			{
				e.printStackTrace();
			} catch (InvocationTargetException e)
			{
				e.printStackTrace();
			}
		}
	}
	@Override
	public void mouseReleased(MouseEvent arg0)
	{
	}
	public void draw(Graphics g)
	{
		if(!normalButton)
		{
		if(myImage!=null)
			g.drawImage(myImage,(int) bounds.getX(), (int)bounds.getY(),(int) bounds.getWidth(),(int) bounds.getHeight(), null);
		}else
		{
			//this.paintComponent(g);
		}
		//else
		//	System.out.println("My Image is NUll");
	}
	private Image loadImage (String pad){
        return Toolkit.getDefaultToolkit().getImage(getClass().getResource(pad));
    }
	public void setAction(String methodName,Class c,Object declare)
	{
		this.declare=declare;
		this.c=c;
		try
		{
			m=c.getMethod(methodName, null);
		} catch (SecurityException e)
		{
			e.printStackTrace();
		} catch (NoSuchMethodException e)
		{
			e.printStackTrace();
		}
	}
	public MyJButton(ImageIcon c)
	{
		super (c);
		normalButton=true;
	}
	public MyJButton(String string)
	{
		super(string);
		normalButton=true;
	}
	@Override
	public void setBounds(int x,int y,int w,int h)
	{
		super.setBounds(x, y, w, h);
		bounds=new Rectangle(x,y,w,h);
	}
}
