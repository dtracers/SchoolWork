package GUI;
/*Created a JButton class because when you click it button, we made it able to call a function 
 * that makes everything easier in our Menu file
 */

import java.awt.Graphics;
import java.awt.Image;
import java.awt.Rectangle;
import java.awt.Toolkit;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.io.File;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.TreeMap;

import javax.swing.ImageIcon;
import javax.swing.JButton;

public class MyJButton extends JButton implements MouseListener
{
	private static boolean defaultloaded=false;
	private static TreeMap<String,Image> images=new TreeMap<String,Image>();
	{
		if(!defaultloaded)
			images.put("defualt", loadDefault("images/N0.png"));
	}
	private Image myImage;
	private String imageName;
	private Rectangle bounds;
	private Method m;
	private Class c;
	private Object declare;
	private boolean normalButton=false;
	private boolean deleted=false;
	boolean loadedImage=false;
	public MyJButton(String name,int x,int y,int w,int h)
	{
		imageName=name;
		bounds=new Rectangle(x,y,w,h);
		myImage=images.get(name);
		if(myImage==null)
		{
			myImage=loadImage(name);
			images.put(name, myImage);
		}
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
		if(bounds.contains(arg0.getPoint())&&!deleted)
		{
			System.out.println("button"+imageName+"pressed");
			try
			{
				System.out.println(""+declare);
				if(m!=null&&declare!=null)
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
		if(images.get(imageName)!=null)
		{
		//	System.out.println("not image"+imageName);
			g.drawImage(images.get(imageName),(int) bounds.getX(), (int)bounds.getY(),(int) bounds.getWidth(),(int) bounds.getHeight(), null);
		}else
		{
		//	System.out.println("def image");
			g.drawImage(images.get("defualt"),(int) bounds.getX(), (int)bounds.getY(),(int) bounds.getWidth(),(int) bounds.getHeight(), null);
		}
	}
	private Image loadImage (String pad){
		loadedImage=true;
		try
		{
			File f=new File(pad);
			if(!f.exists())
			{
				System.out.println("FILE EXIST"+pad);
			}else
			{
				System.out.println("FILE DOESNT EXIST");
			//	return null;
			}
			return Toolkit.getDefaultToolkit().getImage(getClass().getResource(pad));
		}
		catch(Exception e)
		{
			return null;
		}
    }
	private Image loadDefault(String pad)
	{
		if(!defaultloaded)
		{
			return Toolkit.getDefaultToolkit().getImage(getClass().getResource(pad));
		}
		else
			return null;
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
	public String toString()
	{
		return imageName;
	}
	public boolean isDeleted()
	{
		return deleted;
	}
	public void setDeleted(boolean deleted)
	{
		this.deleted = deleted;
	}
	public void resize(double x,double y)
	{
		bounds=scale(bounds,x,y);
	}
	public Rectangle scale(Rectangle r,double sX,double sY)
	{
		return new Rectangle((int)(r.getX()*sX),(int)(r.getY()*sY),(int)(r.getWidth()*sX),(int)(r.getHeight()*sY));
	}
}

