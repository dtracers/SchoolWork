package GUI;

import gameplay.GameEngine;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

/**
 * The grid object will listen for a mouse and tell you where the mouse was clicked
 * it will also hold all of the peices
 * @author gigemjt
 *
 */
public class Grid implements MouseListener
{
	int lastx,lasty;
	int totalWidth,totalHeight,boxWidth,boxHeight;
	int[][] grid;
	public Grid(int totalWidth,int totalHeight,int boxWidth,int boxHeight)
	{
		this.totalWidth=totalWidth;
		this.totalHeight=totalHeight;
		this.boxWidth=boxWidth;
		this.boxHeight=boxHeight;
		int xNum=totalWidth/boxWidth;
		int yNum=totalHeight/boxHeight;
		grid=new int[yNum][xNum];
		GameEngine.setGridLengths(yNum,xNum);
	}
	public void draw(Graphics g)//this is called by another method
	{
		int[][] grid=GameEngine.getGridCopy();
		for(int k=0;k<grid.length;k++)
		{
			for(int q=0;q<grid[k].length;q++)
			{
				if(grid[k][q]!=0)
				{
					switch(grid[k][q])
					{
						case -1:
							g.setColor(Color.green);break;
						case -5:
							g.setColor(Color.red);break;
						default:
							g.setColor(Color.black);
					}
				//	g.fillRect(q*boxWidth, k*boxHeight, boxWidth, boxHeight);
					g.fillOval(q*boxWidth, k*boxHeight, boxWidth, boxHeight);
				}
				if(k==grid.length-1)
				{
					g.setColor(Color.black);
					g.drawLine(q*boxWidth,0,q*boxWidth, grid.length*boxHeight);
				}
			}
			g.setColor(Color.black);
			g.drawLine(0,k*boxHeight,grid[k].length*boxWidth, k*boxHeight);
		}
		g.drawLine(0,(grid.length)*boxHeight,grid[0].length*boxWidth,(grid.length)*boxHeight);
		g.drawLine((grid[0].length)*boxWidth,0,(grid[0].length)*boxWidth, grid.length*boxHeight);
	}
	
	@Override
	public void mouseClicked(MouseEvent arg0)//if the mouse is clicked (very unreliable dont use this)
	{
	}
	
	@Override
	public void mouseEntered(MouseEvent arg0)//if mouse exits jpanel (doesnt really matter for anything)
	{
	}

	@Override
	public void mouseExited(MouseEvent arg0)//if mouse enters jpanel (doesnt really matter for anything)
	{
		
	}

	@Override
	public void mousePressed(MouseEvent arg0)//called while a mouse button is pressed
	{
	}

	@Override
	public void mouseReleased(MouseEvent arg0)//called when a mouse button is released
	{
//		System.out.println("Mouse clicked");
		int x=arg0.getX();
		int y=arg0.getY();
		//*
		if(x>totalWidth||y>totalHeight)
			return;
		//*/
		int xcell=x/boxWidth;
		int ycell=y/boxHeight;
		lastx=xcell;
		lasty=ycell;
//		System.out.println("Mouse clicked"+lastx+" "+lasty);
		if(GameEngine.previousMove!=-1) {
		GameEngine.makeMove(xcell, ycell, -1);
		GameEngine.update();
		}
		else {
			System.out.print("Error: Not your turn!\n");
		}	
			
		}

}
