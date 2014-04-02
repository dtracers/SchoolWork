package GUI;
/* Grid draws the game board onto the JFrame. 
 * It also sets the pieces to red and black depending on who's turn it is.
 */

import gameplay.GameEngine;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Toolkit;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.image.BufferedImage;

import brains.Move;

/**
 * The grid object will listen for a mouse and tell you where the mouse was clicked
 * it will also hold all of the peices
 * @author gigemjt
 *
 */
public class Grid implements MouseListener,KeyListener
{
	BufferedImage img;
	boolean updated;
	int lastx,lasty;
	int totalWidth,totalHeight,boxWidth,boxHeight;
	int[][] grid;
	//image 
	Image blackPiece;
	Image redPiece;
	private boolean bRedPiece = false;
	private boolean bBlackPiece = false;
	boolean debug=true;
	int myPieceType=0;

	public Grid(int totalWidth,int totalHeight,int boxWidth,int boxHeight,boolean rows)
	{
		this.totalWidth=totalWidth;
		this.totalHeight=totalHeight;
		if(!rows)
		{
			this.boxWidth=boxWidth;
			this.boxHeight=boxHeight;
			int xNum=totalWidth/boxWidth;
			int yNum=totalHeight/boxHeight;
			grid=new int[yNum][xNum];
			GameEngine.setGridLengths(yNum,xNum);
		}else
		{
			this.boxWidth=totalWidth/boxWidth;
			this.boxHeight=totalHeight/boxHeight;
			grid=new int[boxHeight][boxWidth];
			GameEngine.setGridLengths(boxHeight,boxWidth);
		}
		img=new BufferedImage(totalWidth,totalHeight,1);
		if(img!=null)
		{
			Graphics g=img.getGraphics();
			g.setColor(new Color(254,241,0));
			g.fillRect(0, 0,totalWidth,totalHeight);
		}
		redPiece = Toolkit.getDefaultToolkit().getImage("src/GUI/images/redPiece.png");
		blackPiece = Toolkit.getDefaultToolkit().getImage("src/GUI/images/blackPiece.png");
	}
	public void draw(Graphics g2)//this is called by another method
	{
		if(debug||updated||img==null||redPiece.getHeight(null)==0||blackPiece.getHeight(null)==0)
		{
			updated=false;
			Graphics g;
			if(img!=null)
			{
				g=img.getGraphics();
				g.setColor(new Color(254,241,0));
				g.fillRect(0, 0,totalWidth,totalHeight);
			}else
			{
				g=g2;
			}
			int currentpiece=-1;
			boolean colorchange=false;
			int[][] grid=GameEngine.getGridCopy();
			for(int k=0;k<grid.length;k++)
			{
				int yplace=k*boxHeight;
				for(int q=0;q<grid[k].length;q++)
				{
					int xplace=q*boxWidth;
					if(grid[k][q]!=0)
					{
						switch(grid[k][q])
						{
							case 1://drawing image=black image
								bBlackPiece = true;
								g.drawImage(blackPiece, xplace, yplace,boxWidth,boxHeight, null);	
								break;
								
							case 2://same for red
								bRedPiece = true;				
								g.drawImage(redPiece, xplace, yplace,boxWidth,boxHeight, null);
								break;
						}
					}
				}
				colorchange=true;
				g.setColor(Color.black);
				g.drawLine(0,yplace,grid[k].length*boxWidth, yplace);
			}
			g.drawLine(0,(grid.length)*boxHeight,grid[0].length*boxWidth,(grid.length)*boxHeight);
			g.drawLine((grid[0].length)*boxWidth,0,(grid[0].length)*boxWidth, grid.length*boxHeight);
			g.setColor(Color.black);
			for(int q=0;q<grid[0].length;q++)
			{
				int xplace=q*boxWidth;
				g.drawLine(xplace,0,xplace, grid.length*boxHeight);
			}
			updated=false;
		}
		if(img!=null)
			g2.drawImage(img, 0, 0,null);
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
			GameEngine.makeMove(new Move(xcell, ycell,GameEngine.isRemoved()?-2:GameEngine.getTurnCounter(),
					(myPieceType!=0)?myPieceType:GameEngine.getTurnCounter()));
			GameEngine.update();

			
	}
	@Override
	public void keyPressed(KeyEvent arg0)
	{
		System.out.println("KEY PRESSED");
		int code=arg0.getKeyCode();
		if(code==KeyEvent.VK_A)
		{
			System.out.println("A pressed");
			GameEngine.makeAiMove();
		}
	}
	@Override
	public void keyReleased(KeyEvent arg0)
	{
		
	}
	@Override
	public void keyTyped(KeyEvent arg0)
	{
	}
	public void updated()
	{
		updated=true;
	}
	public void resize(int totalWidth,int totalHeight,int boxWidth,int boxHeight,boolean rows)
	{
		updated=true;
		System.out.println("RESIZE!");
		this.totalWidth=totalWidth;
		this.totalHeight=totalHeight;
		if(!rows)
		{
			this.boxWidth=boxWidth;
			this.boxHeight=boxHeight;
			int xNum=totalWidth/boxWidth;
			int yNum=totalHeight/boxHeight;
			grid=new int[yNum][xNum];
			GameEngine.setGridLengths(yNum,xNum);
		}else
		{
			this.boxWidth=totalWidth/boxWidth;
			this.boxHeight=totalHeight/boxHeight;
			grid=new int[boxHeight][boxWidth];
			GameEngine.setGridLengths(boxHeight,boxWidth);
		}
		img=new BufferedImage(totalWidth,totalHeight,1);
		if(img!=null)
		{
			Graphics g=img.getGraphics();
			g.setColor(new Color(254,241,0));
			g.fillRect(0, 0,totalWidth,totalHeight);
		}
		redPiece = Toolkit.getDefaultToolkit().getImage("src/GUI/images/redPiece.png");
		blackPiece = Toolkit.getDefaultToolkit().getImage("src/GUI/images/blackPiece.png");
	}
	public void setPieceType(int type)
	{
		myPieceType=type;
	}
}
