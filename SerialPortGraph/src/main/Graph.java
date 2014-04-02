package main;

import java.awt.Color;
import java.awt.Graphics;
import java.util.ArrayList;

import javax.swing.JPanel;

/**
 * Rules every arry is separated by the numbers 1 2 3 4 5 6
 * all other numbers that are not those are the actual values of each line with each one being separated by a different byte
 * @author gigemjt
 *
 */
public class Graph extends JPanel
{
	ArrayList<GraphLine> list=new ArrayList<GraphLine>();
	ArrayList<Color> colors;
	Input input;
	int lines=-1;
	int counter=1;
	boolean running=true;
	boolean onLines=false;
	int currentSyncNumber=0;
	boolean halfSync=false;
	boolean fullSync=false;
	byte myByte=0;
	int numberOfReads=0;
	int countWait=0;
	int WaitTill=100;
	int windowSkip=1;
	public Graph(Input input2)
	{
		input=input2;
	}
	public void initialize()
	{
		list=new ArrayList<GraphLine>();
		fullSync=false;
		halfSync=false;
		onLines=false;
		currentSyncNumber=0;
		counter=0;
		lines=-1;
		colors=new ArrayList<Color>();
		colors.add(Color.black);
		colors.add(Color.blue);
		colors.add(Color.red);
		colors.add(Color.green);
	}
	public void startGraphing()
	{
		running=true;
		initialize();
		readQueue();
		updating();
	}
	public void stopGraphing()
	{
		running=false;
	}
	public void updating()
	{
		Thread d=new Thread()
		{
			public void run()
			{
				while(running)
				{
					repaint();
					try
					{
						Thread.sleep(1);
					} catch (InterruptedException e)
					{
						e.printStackTrace();
					}
				}
			}
		};
		d.start();
	}
	public void paint(Graphics g)
	{
		g.setColor(Color.white);
		g.fillRect(0, 0, this.getWidth(), this.getHeight());
		g.setColor(Color.black);
		graphState(g,0,0);
		g.drawRect(0, 0, getWidth()-1, getHeight()-1);
		for(GraphLine l:list)
		{
			l.drawLine(g,0,100,windowSkip,true);
		}
	}
	
	public void readQueue()
	{
		Thread d=new Thread()
		{
			public void run()
			{
				while(running)
				{
					byte b=input.remove();
				//	numberOfReads++;
					
				//	System.out.println("Graphing Byte is "+b);
				//	System.out.println("States:\n");
				//	System.out.println("\tFullSync:\t"+fullSync);
				//	System.out.println("\tFullSync:\t"+fullSync);
					if(b!=-1)
					{
						list.get(counter).addPoint(b);
						if(false)
						{
							myByte=b;
						//	System.out.println("Byte Read "+myByte);
						//	System.out.println("Byte Number is "+numberOfReads);
							if(fullSync)
							{
								
								if(!onLines&&counter==5)
								{
									counter=0;
									onLines=true;
					//				System.out.println("onLines!");
								}else
								if(!onLines)
								{
									counter++;
								}else if(onLines)
								{
									list.get(counter).addPoint(b);
									if(counter==lines)
									{
					//					System.out.println("Not onLines!");
										onLines=false;
										counter=0;
									}else
									{
										counter++;
									}
								}
							}else
							{
								if(halfSync&&b!=1)
								{
									lines++;
									if(lines>=colors.size())
										colors.add(new Color((int)Math.random()*255,(int)Math.random()*255,(int)Math.random()*255));
									list.add(new GraphLine(colors.get(lines)));
								}else if(halfSync&&b==1)
								{
									fullSync=true;
									onLines=false;
									halfSync=false;
									counter=1;
								}
								if(!halfSync)
								{
									if(b==currentSyncNumber+1)
									{
										currentSyncNumber++;
									}else
									{
										currentSyncNumber=0;
									}
									if(currentSyncNumber==6)
									{
										halfSync=true;//next Byte is a line
									}
								}
							}
						
							if(countWait>=WaitTill)
							{
								countWait=0;
								try
								{
									Thread.sleep(1);
								} catch (InterruptedException e)
								{
									e.printStackTrace();
								}
							}else
							{
		
								countWait++;
							}
						}else
						{
							try
							{
								Thread.sleep(5);
							} catch (InterruptedException e)
							{
								e.printStackTrace();
							}
						}
					}
					try
					{
						Thread.sleep(1);
					} catch (InterruptedException e)
					{
						e.printStackTrace();
					}
				}
			}
		};
		d.start();
	}
	public void graphState(Graphics g,int x,int y)
	{
	//	y+=15;
	//	g.drawString("States: ", x, y);
		y+=15;
		g.drawString("FullSync: "+fullSync, x, y);
		y+=15;
		g.drawString("HalfSync: "+halfSync, x, y);
		y+=15;
		g.drawString("onLines: "+onLines, x, y);
		y+=15;
		g.drawString("Number of Lines: "+(lines+1), x, y);
		y+=15;
		if(list.size()>0)
		{
			GraphLine first=list.get(0);
			int lag=first.dataPoints.size()-first.currentWindow;
			g.drawString("Lag: "+(lag), x, y);
		}
//		y+=15;
//		g.drawString("Current Byte: "+myByte, x, y);
//		y+=15;
//		g.drawString("counter: "+counter, x, y);
//		y+=15;
//		g.drawString("Reading: "+numberOfReads, x, y);
		if(input.byteQueue!=null)
		{
			y+=15;
			g.drawString("Queue size is : "+input.byteQueue.size(), x, y);
		}
	}
}
class GraphLine
{
	Color drawColor;
	ArrayList<Integer> dataPoints;
	int currentWindow;
	int width=750;
	public GraphLine(Color c)
	{
		dataPoints=new ArrayList<Integer>();
		drawColor=c;
	}
	public void addPoint(byte b)
	{
		int i=b;
		if(i<0)
			i+=255;
		//	i+=255/2;
//		i=Math.abs(b);
//		System.out.println("Adding Point "+i);
		dataPoints.add(i);
	}
	public void drawLine(Graphics g,int offX,int offY,int windowAddition,boolean method)
	{
		g.setColor(drawColor);
		if(method)
		{
			int minSize=Math.min(currentWindow+width,dataPoints.size());
			for(int k=currentWindow;k<minSize-1;k++)
			{
				int x=k-currentWindow;
//				System.out.println("Drawing Points "+k);
				g.drawLine(x+offX, dataPoints.get(k)+offY, x+1+offX, dataPoints.get(k+1)+offY);
			}
			if(currentWindow+width<dataPoints.size())
			{
				currentWindow+=windowAddition;
			}
		}else
		{
			int startingPoint=Math.max(0, dataPoints.size()-width);
			for(int k=startingPoint;k<dataPoints.size()-1;k++)
			{
				int x=k-startingPoint;
	//			System.out.println("Drawing Points "+k);
				g.drawLine(x+offX, dataPoints.get(k)+offY, x+1+offX, dataPoints.get(k+1)+offY);
			}
		}
		
	}
}