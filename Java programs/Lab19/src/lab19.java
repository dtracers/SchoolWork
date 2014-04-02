

import java.awt.Color;
import java.awt.Frame;
import java.awt.Graphics;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class lab19
{
	Windows w;
	public static void main(String args[])
	{
		Windows win = new Windows();
		win.setSize(2000,1000);
		win.addWindowListener(new WindowAdapter() {public void
		windowClosing(WindowEvent e) {System.exit(0);}});
		win.show();
		Graphics g=win.getGraphics();
		int w=100;
		int h=100;
		MyRun r=new MyRun(500,(int)750/2,w,h,g,1,1,0,new Color(255,255,255),true);
		
		MyRun r1=new MyRun(500,(int)750/2,w,h,g,-1,-1,0,new Color(255,255,255),true);
		
		MyRun r2=new MyRun(500,(int)750/2,w,h,g,1,-1,0,new Color(255,255,255),true);
		
		MyRun r3=new MyRun(500,(int)750/2,w,h,g,-1,1,0,new Color(255,255,255),true);
		r.start();
		r1.start();
		r2.start();
		r3.start();
	}
	static class MyRun extends Thread
	{
		static int tc=0;
		int x,y;
		int threadmax=1000;
		double w,h;
		Graphics g;
		int wh,hw;
		Color c;
		boolean go;
		public MyRun(int x,int y,double width,double height,Graphics g,int wh,int hw,int threadcount,Color c,boolean go)
		{
			this.x=x;this.y=y;w=width;h=height;this.g=g;this.wh=wh;this.hw=hw;this.c=c;this.go=go;
		//	tc=threadcount;
		}
		@Override
		public void run() {
			// TODO Auto-generated method stub
			if(go)
				move2(x,y,w,h,g,wh,hw,c);
			else
				if(isAlive())
				{
					tc--;
				}
		}
		public void move2(int x,int y,double width,double height,Graphics g,int wh,int hw,Color c)
		{
			tc++;
			if(width>1||height>1)
			{
				double w2=width*(1/2.);
				double h2=height*(1/2.);
				if(c.getBlue()<20)
				{
					if(wh==1&&hw==1)
						c=new Color(255,255,255);
					if(wh==-1&&hw==1)
					{
						c=new Color(0,255,0);
					}
					if(wh==-1&&hw==-1)
					{
						c=new Color(255,255,0);
					}
					if(wh==1&&hw==-1)
					{
						c=new Color(0,255,255);
					}
				}
				else
					c=c.darker();
				g.setColor(c);
				g.fillRect(x,y,(int)width,(int)height);
				if(tc>=threadmax&&false)
				{
					move2((int)(x+(wh*w2)+(wh*width/2)*(wh>0?1:0)),(int)(y+(hw*h2)+(hw*height/2)*(hw>0?1:0)),w2,h2,g,-1,-1,c);
					move2((int)(x+(wh*w2)+(wh*width/2)*(wh>0?1:0)),(int)(y+(hw*h2)+(hw*height/2)*(hw>0?1:0)),w2,h2,g,1,1,c);
					move2((int)(x+(wh*w2)+(wh*width/2)*(wh>0?1:0)),(int)(y+(hw*h2)+(hw*height/2)*(hw>0?1:0)),w2,h2,g,1,-1,c);
					move2((int)(x+(wh*w2)+(wh*width/2)*(wh>0?1:0)),(int)(y+(hw*h2)+(hw*height/2)*(hw>0?1:0)),w2,h2,g,-1,1,c);
				}else
				{
					MyRun r1=new MyRun((int)(x+(wh*w2)+(wh*width/2)*(wh>0?1:0)),(int)(y+(hw*h2)+(hw*height/2)*(hw>0?1:0)),w2,h2,g,-1,-1,tc+1,c,(wh==1&&hw==1)?false:true);
					MyRun r2=new MyRun((int)(x+(wh*w2)+(wh*width/2)*(wh>0?1:0)),(int)(y+(hw*h2)+(hw*height/2)*(hw>0?1:0)),w2,h2,g,1,1,tc+1,c,(wh==-1&&hw==-1)?false:true);
					MyRun r3=new MyRun((int)(x+(wh*w2)+(wh*width/2)*(wh>0?1:0)),(int)(y+(hw*h2)+(hw*height/2)*(hw>0?1:0)),w2,h2,g,1,-1,tc+1,c,(wh==-1&&hw==1)?false:true);
					MyRun r4=new MyRun((int)(x+(wh*w2)+(wh*width/2)*(wh>0?1:0)),(int)(y+(hw*h2)+(hw*height/2)*(hw>0?1:0)),w2,h2,g,-1,1,tc+1,c,(wh==1&&hw==-1)?false:true);
					boolean alternate1=((int)(Math.random()*20))%7!=1;
					boolean alternate2=((int)(Math.random()*20))%7!=1;
					boolean alternate3=((int)(Math.random()*20))%7!=1;
					boolean alternate4=((int)(Math.random()*20))%7!=1;
					if((tc<=threadmax&&alternate1))
						r1.start();
					else
						r1.run();
					if(tc<=threadmax&&alternate2)
						r2.start();
					else
						r2.run();
					if(tc<=threadmax&&alternate3)
						r3.start();
					else
						r3.run();
					if(tc<=threadmax&&alternate4)
						r4.start();
					else
						r4.run();
					int alivecount=0;
					
					if(r1.isAlive())
					{
						alivecount++;
					}
					if(r2.isAlive())
					{
						alivecount++;
					}
					if(r3.isAlive())
					{
						alivecount++;
					}
					if(r4.isAlive())
					{
						alivecount++;
					}
					if(alivecount==0)
					{

						tc--;
					}
					/*
					while(activeCount()>tc)
					{
						tc--;
					}
					*/
				}
			}else
			{
			//	System.out.println("Done "+tc);
			}
		}
	}
}

class Windows extends Frame
{
	Integer threadcount;
	public void init()
	{
	}
	public void paint(Graphics g)
	{
		
	}
	public void move(int x,int y,double width,double height,Graphics g,boolean which)
	{
		threadcount++;
		if(which&&width>1&&height>4)
		{
			g.fillRect(x,y,(int)width,(int)height);
			move((int)((int)x-10-((int)width*(3/4.))),y,width*(3/4.),height*(3/4.),g,which);
		}
		if(!which&&width>1&&height>4)
		{
			move((int)(x+10+width),(int)(y+((int)height*(1/4.))),width*(3/4.),height*(3/4.),g,which);
			g.fillRect(x,y,(int)width,(int)height);			
		}
	}
	
	public void move2(int x,int y,double width,double height,Graphics g,int wh,int hw)
	{
		//threadcount++;
		if(width>4&&height>4)
		{
			double w2=width*(3/4.);
			double h2=height*(3/4.);
			g.fillRect(x,y,(int)width,(int)height);
			move2((int)(x+(wh*w2)),(int)(y+(hw*h2)),w2,h2,g,-1,-1);
			move2((int)(x+(wh*w2)),(int)(y+(hw*h2)),w2,h2,g,1,1);
			move2((int)(x+(wh*w2)),(int)(y+(hw*h2)),w2,h2,g,1,-1);
			move2((int)(x+(wh*w2)),(int)(y+(hw*h2)),w2,h2,g,-1,1);
		}else
		{
			System.out.println("finished");
		}
	}
}
