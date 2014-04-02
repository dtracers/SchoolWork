package brains;

import gameplay.GameEngine;

import java.awt.Canvas;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.image.BufferedImage;
import java.util.ArrayList;

public class DebugFrame extends Canvas
{
	boolean Tree=true;
	ArrayList<Move> list;
	MinMaxTreeNode top;
	int maxLevel;
	int width;
	int height;
	int levels[];
	BufferedImage i;
	boolean print=false;
	public void setTree(MinMaxTreeNode top)
	{
		this.top=top;
	}
	public void setList(ArrayList<Move> list)
	{
		this.list=list;
	}
	public void setList(int[] list)
	{
		levels=list;
	}
	public void addMove(Move m)
	{
		list.add(m);
	}
	public void removeMove()
	{
		list.remove(list.size()-1);
	}
	public void paint(Graphics g)
	{
		g.setColor(Color.white);
		g.fillRect(0, 0, 1000, 1000);
		if(print)
		{
			if(!Tree)
			{
				
				g.setColor(Color.black);
				String total="";
				if(levels!=null)
					for(int k=0;k<levels.length;k++)
					{
						total+=levels[k]+" ";
					}
				g.drawString(total, 10, 10);
				for(int k=0;k<list.size();k++)
				{
					g.drawString(""+list.get(k), 10, 30+20*k);
				}
			}else
			{
				g.fillRect(0, 0, 10000, 500);
				g.setColor(Color.black);
				paintTree(top,g,null,5000,10,8000,0);
			}
		}else
		{
			g.setColor(Color.black);
			g.drawString(""+GameEngine.getTurnCounter(), 10,10);
		}
	}
	public void paintTree(MinMaxTreeNode n,Graphics g,Graphics g2,int x,int y,int width,int depth)
	{
		if(n.currentMove!=null)
			g.drawString(""+n.currentMove.shortString(), x, y);
			if(n.nextLevel!=null)
			{
				ArrayList<MinMaxTreeNode> nextLevel=n.nextLevel;
				int newWidth=width/nextLevel.size();
				int leftX=x-width/2;
				if(depth<3)
				{
					for(int k=0;k<nextLevel.size();k++)
					{
						int newX=leftX+k*newWidth;
						int newY=y+100;
						g.drawLine(x, y, newX, newY);
						paintTree(nextLevel.get(k),g,g2,newX,newY,newWidth,depth+1);
					}
				}
			}
	}
}
