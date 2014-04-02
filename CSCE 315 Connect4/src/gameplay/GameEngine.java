package gameplay;

import java.awt.Image;
import java.awt.Toolkit;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;

import GUI.Display;
import GUI.MainFrame;
import brains.AI;
import brains.DebugFrame;
import brains.Move;

public class GameEngine extends Thread
{
	public static int previous_Move;
	private static MainFrame mainframe;
	private static Display d;
	private static GridStorage grid;
	private static AI ai1;
	private static AI ai2;
	private static int turnCounter=1;
	static int numberOfPlayers=2;
	static boolean removePieceState=false;
	Image winnerScreen;
	static boolean movemade=true;
	static boolean playerWinner = false;
	static boolean computerWinner = false;
	private static int turnLevel;
	private JLabel winner;
	private DebugFrame Debugframe;
	private static int totalTurns;
	public static long previousMoveTime;
	public static long waitTime=0;
	static boolean started=false;
	static boolean outOfTime = false;
	static boolean debug=false;
	private static int startingType=0;
	public static boolean local=true;
	static boolean playedonce=false;
	public GameEngine()
	{
		if(debug)
		{
			JFrame f=new JFrame();
			f.setVisible(false);
			f.setSize(1440,800);
			Debugframe=new DebugFrame();
			f.add(Debugframe);
			f.setVisible(true);
		}
		winnerScreen = Toolkit.getDefaultToolkit().getImage("images/winnerScreen.png");
	
		previous_Move=0;
		if(grid==null)
		{
			grid=new GridStorage();
		}
		createFrame();
	}
	public void createFrame()
	{
		if(mainframe==null)
		{
			MainFrame frame = new MainFrame();
			frame.setGame(this);
			GameEngine.setMainFrame(frame);
			frame.setVisible(true);
			mainframe=frame;
		}
	}
	public static void setTime(int _time){
		waitTime = _time;
	}
	
	public static void setMyPieceType(int type)
	{
		mainframe.getDisplay().getGrid().setPieceType(type);
	//	d.getGrid().setPieceType(type);
	}
	public void RealStart()
	{
		if(false&&ai1==null)
		{
			ai1=new AI();
			System.out.println("Starting lengths"+grid.getGrid().length);
		//	JOptionPane.showMessageDialog(null, "Continue?");
			ai1.start();
			ai1.setMyPieceType(1);
			ai1.setEnemyPieceType(2);
		}
		
		if(ai2==null)//TODO ONLY NEEDED IF TWO AI PLAY EACH OTHER
		{
			ai2=new AI();
			ai2.start();
			ai2.setMyPieceType(2);
			ai2.setEnemyPieceType(1);
		}
	}
	public void start()
	{
		super.start();
		started=true;
	}
	public static boolean otherMakeMove(Move m)
	{
		if(!playedonce)
		{
			waitTime=20000;
			previousMoveTime=System.currentTimeMillis();
		}
		playedonce=true;
		System.out.println("I am making a move!");
		if(isRemoved())
		{
			removePieceState=false;
		}
		if(m.getPiece()==-2)
		{
			JOptionPane.showMessageDialog(getMainFrame(), "Removing a piece");
		}
		//DO IT HERE
		
		if(previous_Move==-1&&m.getPiece()==-1)
		{
			JOptionPane.showMessageDialog(getMainFrame(), "The other player tried to flip twice...\npoint and laugh at that person");
			return false;
		}
		//DO IT HERE
		movemade=true;
		int piece=m.getPiece();
		if(turnCounter==startingType)
		{
			System.out.print("Error: Not your turn!");
			JOptionPane.showMessageDialog(getMainFrame(), "It is not your turn... please wait");
			return false;
		}
		System.out.println("moving "+piece);
		grid.setPiece(m);
		if(local)
		{
			if(ai1!=null)
			{
				try
				{
					ai1.getLatestMove(grid.lastMove());
					if(!ai1.isBoardMade())
						ai1.retrieveBoard(grid.getGrid());//TODO CHANGE THIS IT SHOULDNT GET A NEW BOARD
				}catch(Exception e)
				{
					
				}
				
			}
			if(ai2!=null)
			{
				try
				{
					ai2.getLatestMove(grid.lastMove());
					if(!ai2.isBoardMade())
						ai2.retrieveBoard(grid.getGrid());
				}catch(Exception e)
				{
					
				}
			}
		}
		previous_Move = piece;
		incrementTurn();
		
	//	getMainFrame().makeMove(x,y,piece);
	//Check for Gamewon
		int ret=grid.gameWon();
		if(ret!=0)
		{
			if(ret>numberOfPlayers)
			{
				JOptionPane.showMessageDialog(null,"There was a draw :)");
			}else
			{
				JOptionPane.showMessageDialog(null,"Player "+ret+"wins!");
			}
		}
		previousMoveTime=System.currentTimeMillis();
		
		return true;
	}
	/**
	 * This is will handle movement
	 * right now the grid is in the class grid it should be later moved to accommodate other things
	 * @param x
	 * @param y
	 * @param piece
	 */
	public static boolean makeMove(Move m)
	{
		if(!playedonce)
		{
			waitTime=20000;
			previousMoveTime=System.currentTimeMillis();
		}
		playedonce=true;
		System.out.println("I am making a move! ");
		if(isRemoved())
		{
			removePieceState=false;
		}
		if(m.getPiece()==-2)
		{
		//	JOptionPane.showMessageDialog(getMainFrame(), "Removing a piece");
		}
		//DO IT HERE
		
		if(previous_Move==-1&&m.getPiece()==-1)
		{
			JOptionPane.showMessageDialog(getMainFrame(), "You can't flip twice");
			return false;
		}
		movemade=true;
		previous_Move=m.getPiece();//gets the piece type so you don't go twice in a row
		if(turnCounter!=startingType&&!local)
		{
			System.out.print("Error: Not your turn!");
			JOptionPane.showMessageDialog(getMainFrame(), "It is not your turn... please wait");
			return false;
		}
		grid.setPiece(m);
		if(local)
		{
			if(ai1!=null)
			{
				try
				{
					ai1.getLatestMove(grid.lastMove());
					if(!ai1.isBoardMade())
						ai1.retrieveBoard(grid.getGrid());//TODO CHANGE THIS IT SHOULDNT GET A NEW BOARD
				}catch(Exception e)
				{
					
				}
				
			}
			if(ai2!=null)
			{
				try
				{
					ai2.getLatestMove(grid.lastMove());
					if(!ai2.isBoardMade())
						ai2.retrieveBoard(grid.getGrid());
				}catch(Exception e)
				{
					
				}
			}
		}
		incrementTurn();
		
	//	getMainFrame().makeMove(x,y,piece);
	//Check for Gamewon
		int ret=grid.gameWon();
		if(ret!=0)
		{
			if(ret>numberOfPlayers)
			{
				JOptionPane.showMessageDialog(null,"There was a draw :)");
			}else
			{
				JOptionPane.showMessageDialog(null,"Player "+ret+"wins!");
			}
		}
		previousMoveTime=System.currentTimeMillis();
		if(local&&mainframe.getDisplay().numberOfPlayers==1&&GameEngine.turnCounter==2)
		{
			
			try
			{
				Thread.sleep(500);
			} catch (InterruptedException e)
			{
				e.printStackTrace();
			}
			makeAiMove();
			
		//	makeAiMove();
		}
		return true;
	}
	public static void incrementTurn()
	{
		totalTurns++;
		turnCounter++;
		if(turnCounter>numberOfPlayers)
		{
			setTurnLevel(turnLevel + 1,new Move(grid.lastMove));
			turnCounter=1;
		}
	}
	
	//Time is not working
	public static boolean timesOut(){
		//System.out.println("LOSER");
	//	outOfTime = true;
		JOptionPane.showMessageDialog(null, "You ran out of time");
	//	System.exit(0);
		return outOfTime;
	}
	
	public static synchronized void update()
	{
	//	System.out.println("repainting!");
		if(waitTime!=0&&System.currentTimeMillis()-previousMoveTime>waitTime)
		{
			if(playedonce)
			{
			//	timesOut();
			}
			//SOMEONE LOST HAHA!!
		}
		if(movemade)
		{
			movemade=false;
			mainframe.updated();
		}
		mainframe.repaint();
		//other updating things happen here
	}
	public static MainFrame getMainFrame()
	{
		return mainframe;
	}
	public static void setMainFrame(MainFrame m)
	{
		GameEngine.mainframe = m;
	}
	@Override
	public void run()
	{
		while(true)
		{
			try
			{
				if(Debugframe!=null)
					Debugframe.repaint();
	//			System.out.println("UPDATE THREAD");
				update();
		//		this.sleep(20);
			}catch(Exception e)
			{
				
			}
		}
	}
	public static void makeAiMove()
	{
		Move b=null;
		if(turnCounter==1)
		{
			b=ai1.getBestMove();
		}else if(turnCounter==2)
		{
			if(ai2!=null)
				b=ai2.getBestMove();
		}
		System.out.println("AI MAKING A MOVE "+b);
		makeMove(b);
	}
	public static int[][] getGridCopy()
	{
		return grid.getGrid();
	}
	public static int[][] getGridNotCopy()
	{
		return grid.getGridObject();
	}
	public static void setGridLengths(int yNum, int xNum)
	{
		grid.setGridLengths(yNum,xNum);
	}
	public synchronized static int getTurnCounter()
	{
		return turnCounter;
	}

	public static void setTurnCounter(int turnCounter)
	{
		GameEngine.turnCounter = turnCounter;
	}
	
	public static int getTurnLevel()
	{
		return turnLevel;
	}
	public static void setTurnLevel(int turnLevel,Move m)
	{
		GameEngine.turnLevel = turnLevel;
		if(ai1!=null)
		{
			ai1.newTurnLevel(turnLevel, m);
		}
		if(ai2!=null)
		{
			ai2.newTurnLevel(turnLevel, m);
		}
	}
	public static void undoMove()
	{
		grid.undoMove(grid.lastMove());
	}
	public static void flipGrid() {
		// TODO Auto-generated method stub
		makeMove(new Move(0, 0, -1,getTurnCounter()));//this will increment turn
	}
	public static void resetBoard()
	{
		if(ai1!=null)
		{
			ai1.setBoardMade(false);
		}
		if(ai2!=null)
		{
			ai2.setBoardMade(false);
		}
	}
	
	public static void removePiece(boolean piece) {
		System.out.println(piece+"remove command");
		removePieceState=piece;
	}
	public static boolean isRemoved()
	{
		return removePieceState;
	}
	public static GridStorage getFakeGrid()
	{
		if(grid.fakeGrid==null)
		{
			grid.createFakeGrid();
		}
		return grid.fakeGrid;
		//return grid;
	}
	public static int getTotalTurns()
	{
		return totalTurns;
	}
	public static void setTotalTurns(int totalTurns)
	{
		GameEngine.totalTurns = totalTurns;
	}
	public static synchronized Move getPreviousMove()
	{
		return grid.lastMove();
	}
	public void repainting() {
		// TODO Auto-generated method stub
		Thread t=new Thread()
		{
			public void run()
			{
				while(!GameEngine.started)
				{
			//		System.out.println("rep");
					GameEngine.mainframe.repaint();
				}
			}
		};
		t.start();
	}
	public static void setFirst(boolean b)
	{
		if(b)
		{
			startingType=1;
		}else
		{
			startingType=2;
		}
	}
	
}
