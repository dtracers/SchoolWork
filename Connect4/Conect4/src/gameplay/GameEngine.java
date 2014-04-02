package gameplay;

import java.awt.EventQueue;

import GUI.MainFrame;
import brains.AI;
import brains.Move;

public class GameEngine extends Thread
{
	public static int previousMove;
	public GameEngine()
	{
		previousMove=0;
		if(grid==null)
		{
			grid=new GridStorage();
		}
		if(m==null)
		{
			EventQueue.invokeLater(new Runnable()
			{
				public void run()
				{
					try
					{
						MainFrame frame = new MainFrame();
						GameEngine.setMainFrame(frame);
						frame.setVisible(true);
						m=frame;
					} catch (Exception e)
					{
						e.printStackTrace();
					}
				}
			});
		}
		if(ai==null)
		{
			ai=new AI();
			ai.start();
		}
	}
	private static MainFrame m;
	private static GridStorage grid;
	private static AI ai;
	/**
	 * This is will handle movement
	 * right now the grid is in the class grid it should be later moved to accommodate other things
	 * @param x
	 * @param y
	 * @param piece
	 */
	public static void makeMove(int x,int y,int piece)
	{
		if(previousMove!=0 && piece==previousMove) {
				System.out.print("Error: Not your turn!");
     	}		
		grid.setPiece(x,y,piece);
		ai.retrieveBoard(grid.getGrid());//these two are synchronized so that it will be safe :)
		ai.getLatestMove(grid.lastMove());
		previousMove = piece;
	//	getMainFrame().makeMove(x,y,piece);
	}
	public static synchronized void update()
	{
		m.repaint();
		//other updating things happen here
	}
	public static MainFrame getMainFrame()
	{
		return m;
	}
	public static void setMainFrame(MainFrame m)
	{
		GameEngine.m = m;
	}
	@Override
	public void run()
	{
		while(true)
		{
			try
			{
	//			System.out.println("UPDATE THREAD");
				update();
				this.sleep(20);
			}catch(Exception e)
			{
				
			}
		}
	}
	public static void makeAiMove()
	{
		Move b=ai.getBestMove();
		//AI Move is 1
		makeMove(b.getX(),b.getY(),1);
	}
	public static int[][] getGridCopy()
	{
		return grid.getGrid();
	}
	public static void setGridLengths(int yNum, int xNum)
	{
		grid.setGridLengths(yNum,xNum);
	}
}
