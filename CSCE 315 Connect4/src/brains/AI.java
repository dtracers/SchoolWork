package brains;

import gameplay.GameEngine;

import java.util.ArrayList;
import java.util.Random;

public class AI extends Thread
{
	int width;
	int height;
	private boolean boardMade;
	ArrayList<Move> enemyThreats;//possible winning moves for enemy
	ArrayList<Move> myThreats;//possible winning moves for me
	int[][] board;
	Move lastMove;
	Move bestMove;
	private int enemyPieceType;
	private int myPieceType;
	int turn;
	int emptySquaresLeft;//this can be computed as a subtraction each time a move is made
	//an even or odd number of squares matter
	boolean changed=false;
	boolean bestMoveset=false;
	Random rand=new Random();
	MinMaxTree tree;
	Move returnMove=null;
	int deepness=0;
	/**
	 * Inside here it will constantly make a move and show the best one so far
	 * at this point it is random
	 */
	@Override
	public void run()
	{
		if(board==null)
		{
			board=new int[2][2];
		}
		if(enemyThreats==null)
		{
			enemyThreats=new ArrayList<Move>();
		}
		if(myThreats==null)
		{
			myThreats=new ArrayList<Move>();
		}
		if(tree==null)
		{
			System.out.println("Tree is being created!");
			System.out.println(GameEngine.getGridCopy().length);
			tree=new MinMaxTree(this,GameEngine.getFakeGrid());
		}
		setBestMove(new Move(rand.nextInt(board.length),rand.nextInt(board[0].length),2));
		while(true)
		{
			if(changed)
			{
				setBestMove(new Move(rand.nextInt(board.length),rand.nextInt(board[0].length),2));
				computeThreats(false);//this will compute my threats
				computeThreats(true);//this will compute there threats
				changed=false;
			}
			
			while(tree.level-GameEngine.getTotalTurns()<3||returnMove==null)
			{
				returnMove=tree.EvaluateCurrentLevel();
				if(returnMove==null)
				{
					System.out.println("WHY IS M NULL??");
					//int i=6/0;
				}
			}
		}
	}
	public void getLatestMove(Move m)
	{
		setLatestMove(m);
	}
	public synchronized void newTurnLevel(int level,Move m)
	{
		if(tree!=null)
			tree.setTurnLevel(level,m);
	}
	public synchronized void setLatestMove(Move m)
	{
		lastMove=new Move(m);
		changed=true;
		bestMoveset=false;
		if(tree!=null)
		{
			tree.Changed();
		}
		setBestMove(new Move(rand.nextInt(board.length),rand.nextInt(board[0].length),2));
		computeThreats(false);//this will compute my threats
		computeThreats(true);//this will compute there threats
		changed=false;
	}
	/*
	 * Only done once then board is the same object as grid
	 */
	public synchronized void retrieveBoard(int[][] grid)
	{
		setBoardMade(true);
		board=grid;
		height=board.length;
		width=board[0].length;
	}
	public synchronized Move getBestMove()
	{
		return new Move(bestMove);
	}
	public synchronized void setBestMove(Move v)
	{
		if(!bestMoveset)
			bestMove=new Move(v);
	}
	public synchronized void setBestMove(Move v,boolean set)
	{
		System.out.println("THE BEST MOVE IS SET TO BE "+v);
		bestMoveset=set;
		bestMove=new Move(v);
	}

	/**
	 * This will start at the last move looking for new possible threats that could occur
	 * @return
	 */
	public ArrayList<Move> computeThreats(boolean mine)
	{
		ArrayList<Move> threats=new ArrayList<Move>();
		Row[]rows=getNextRow(mine?myPieceType:enemyPieceType,lastMove);
		//now we can compute the threats!!!!!
		for(Row r:rows)
		{
			if(r.numberInRow==3)
			{
				Move lb=r.LBPossible;
				Move rt=r.TRPossible;
				if(lb!=null)
				{
					threats.add(lb);
				}
				if(rt!=null)
				{
					threats.add(rt);
				}
			}
		}
		
		if(threats.size()>0)
		{
			//TODO this is a horrible move but it is not one of the worse ones
			threats.get(0).setPiece(myPieceType);
			setBestMove(threats.get(0),true);
			System.out.println("Computed threats are "+threats);
		}else
		{
			System.out.println("No new threats formed");
		}
		for(Move m: threats)
		{
			if(mine)
			{
				myThreats.add(m);
			}
			else
			{
				enemyThreats.add(m);
			}
			
		}
		return threats;
	}
	/**
	 * This will take the next possible row and compute it
	 * @return
	 */
	public Row[] getNextRow(int pieceType,Move m)
	{
		System.out.println("Looking for the next threat at "+m.getX()+" "+m.getY());
		Row[] rows=new Row[4];
		for(int k=0;k<rows.length;k++)
		{
			int direction=k+1;
			Row temp=new Row(direction,pieceType);
			getNextRowLB(m.getX(),m.getY(),temp);
			rows[k]=temp;
		}
		return rows;
	}
	/**
	 * This will go to the left and the bottom then it will work its way up the tree
	 * 
	 * TODO:  remove 1
	 * @param x
	 * @param y
	 * @param r
	 * @param numberInRow
	 * @return
	 */
	public void getNextRowLB(int x,int y,Row r)
	{
		r.setMove(x, y, r.numberInRow+1);
		r.numberInRow++;
		int newX=-1,newY=-1;
		//going down the recursion chain can only go left and down
		boolean quit=false;
		switch(r.direction)
		{
			case 1://top left
				if(x-1<0||y-1<0)
					if(r.numberInRow!=1)
						return;
					else
						quit=true;
				newX=x-1;
				newY=y-1;
				break;
			case 2://left
				if(x-1<0)
					return;
				newX=x-1;
				newY=y;
				break;
			case 3://bottom left
				if(x-1<0||y+1>=height)
					if(r.numberInRow!=1)
						return;
					else
						quit=true;
				newX=x-1;
				newY=y+1;
				break;
			case 4://bottom
				if(y+1>=height)
					return;
				newX=x;
				newY=y+1;
				break;
			case 5://bottom right
				if(x+1>=width||y+1>=height)
					if(r.numberInRow!=1)
						return;
					else
						quit=true;
				newX=x+1;
				newY=y+1;
				break;
		}
		boolean leftMostCase=false;
		int number=r.numberInRow;//this means that there is at least 1
		if(!quit)
		{
			int piece=0;
	//		System.out.println("NEW PLACES "+newX+" "+newY);
			if(newY<board.length&&newX<board[0].length)
				piece=board[newY][newX];
	//		System.out.println("Piece is "+piece);
			if(piece!=r.piecetype&&piece!=0)
				return;
			if(piece==0)
			{
	//			System.out.println("SETTING THREAT");
				r.LBPossible=new Move(newX,newY);
				if(r.numberInRow!=1)
				{
					return;
				}else
					 leftMostCase=true;
			}
			
			//GowDown
	//		System.out.println("Going down! "+newX+" "+newY);
			if(!leftMostCase)
				getNextRowLB(newX,newY,r);
	//		System.out.println("Done Gooing Down");
			//going up
		}else
		{
	//		System.out.println("QUIT after first time");
	//		System.out.println("Go other way");
		}
		if(number!=r.numberInRow)//added only the third one
		{
			//Pieces were added
			if(number==1)//only one was added so far the first one
			{
				//then it is middle
				if(number+1==r.numberInRow)
				{
					//WORKS
					//we need to move the second one over one and this one over one two
					r.setMove(r.getMove(2),3);
					r.setMove(r.getMove(1),2);
					r.setMove(null, 1);//makes it null
				}else
				{
					//WORKS
					getNextRowRT(x,y,r);
					//it is full be happy
					return;
				}
			}
			else
			{
				return;//only zero can go the other way
			}
		}else
		{
			if(number>1)//if it isnt the first one return
				return;			
			//put the first one in the last spot
			r.setMove(r.getMove(1), 3);//put the last move on the first one because it is going rt now
			r.setMove(null, 1);
	//		System.out.println();
	//		System.out.println("IT is the first one");
		}
		//going up now
		if(r.numberInRow<=3)
		{
			//if it is less than three it is not full
			getNextRowRT(x,y,r);
		}
		return;
	}
	/**
	 * 
	 * This goes up the row to finish adding the threat
	 * it is already in the row so you do not add it at the beginning
	 */
	public void getNextRowRT(int x,int y,Row r)
	{
//		System.out.println("going up X:"+x+" Y:"+y+"\n"+r);
		int newX=-1,newY=-1;
		
		switch(r.direction)
		{
			case 1://top left - needs to go bottom right
				if(x+1>=width||y+1>=height)
					return;
				newX=x+1;
				newY=y+1;
				break;
			case 2://left - needs to go right
				if(x+1>=width)
					return;
				newX=x+1;
				newY=y;
				break;
			case 3://bottom left - needs to go top right
				if(x+1>=width||y-1<0)
					return;
				newX=x+1;
				newY=y-1;
				break;
			case 4://bottom - need to go top
				if(y-1<0)
					return;
				newX=x;
				newY=y-1;
				break;
			case 5://bottom right - needs to go top left
				if(x-1<0||y-1<0)
					return;
				newX=x-1;
				newY=y-1;
				break;
		}
//		System.out.println("Up move is valid");
		int piece=board[newY][newX];
		if(piece!=r.piecetype&&piece!=0)
			return;
		if(piece==0)
		{
//			System.out.println("SETTING THREAT");
			r.TRPossible=new Move(newX,newY);
			return;
		}
		if(r.numberInRow<3)
		{
			r.setMove(newX, newY, 3-r.numberInRow);
			r.numberInRow++;
		}else
		{
			r.TRPossible=new Move(newX,newY);
		}
		//everything is ordered correctly so just go up
		if(r.numberInRow<=3)
		{
			getNextRowRT(newX,newY,r);
		}
	}
	/*
	 * just converts it
	 */
	private int[] lb(int direction,int x,int y)
	{
		int newX=-1,newY=-1;
		int[] hold=new int[2];
		hold[0]=-1;
		hold[1]=-1;
		switch(direction)
		{
			case 1://top left
				if(x-1<0||y-1<0)
					return hold;
				newX=x-1;
				newY=y-1;
				break;
			case 2://left
				if(x-1<0)
					return hold;
				newX=x-1;
				newY=y;
				break;
			case 3://bottom left
				if(x-1<0||y+1>=height)
					return hold;
				newX=x-1;
				newY=y+1;
				break;
			case 4://bottom
				if(y+1>=height)
					return hold;
				newX=x;
				newY=y+1;
				break;
			case 5://bottom right
				if(x+1>=width||y+1>=height)
					return hold;
				newX=x+1;
				newY=y+1;
				break;
		}
		hold[0]=newX;
		hold[1]=newY;
		return hold;
	}
	private int[] rt(int direction,int x,int y)
	{
		int newX=-1,newY=-1;
		int[] hold=new int[2];
		hold[0]=-1;
		hold[1]=-1;
		
		switch(direction)
		{
			case 1://top left - needs to go bottom right
				if(x+1>=width||y+1>=height)
					return hold;
				newX=x+1;
				newY=y+1;
				break;
			case 2://left - needs to go right
				if(x+1>=width)
					return hold;
				newX=x+1;
				newY=y;
				break;
			case 3://bottom left - needs to go top right
				if(x+1>=width||y-1<0)
					return hold;
				newX=x+1;
				newY=y-1;
				break;
			case 4://bottom - need to go top
				if(y-1<0)
					return hold;
				newX=x;
				newY=y-1;
				break;
			case 5://bottom right - needs to go top left
				if(x-1<0||y-1<0)
					return hold;
				newX=x-1;
				newY=y-1;
				break;
		}
		
		hold[0]=newX;
		hold[1]=newY;
		return hold;
	}
	public int getMyPieceType()
	{
		return myPieceType;
	}
	public void setMyPieceType(int myPieceType)
	{
		this.myPieceType = myPieceType;
	}
	public int getEnemyPieceType()
	{
		return enemyPieceType;
	}
	public void setEnemyPieceType(int enemyPieceType)
	{
		this.enemyPieceType = enemyPieceType;
	}
	public boolean isBoardMade()
	{
		return boardMade;
	}
	public void setBoardMade(boolean boardMade)
	{
		this.boardMade = boardMade;
	}
}


/**
HOW AI WORKS
This will compute all possible moves to an end game
It will use threats to see who can when and where
It will not move to a spot where an enemy threat can be completed unless force
It will block all threats that the enemy can complete on its next turn
If it sees an end threat (one that when forced will end the game)
it will stop computing that game and will instead spend resources on other moves
it is threaded with the game so it will continue to think as the opponent moves
*/

/**
 * Sample
 * 
 * direction
 * 187
 * 2 6
 * 345
 */


/**
How AI WORKS NOW!!!  UPDATED!!!!

 It will have its own copy of the grid
 It works on an independent thread to everything else
 It will continuously update turns ahead
 It will go through one layer per a turn
 If it encounters a move that will make the AI lose the the move above it will not be chosen
 If it encounters a move that will make the AI win then that move will be chosen
 
 Once the player moves then all other parts of the tree that are not a part of that move are removed (may take a while?)
 So it needs to know what moves are part of what tree!
 
 ex:
 			1
 	2	2	2	2	2
   333 ### 333 ### 333
   if the last 2 is the chosen move by the other player
   then everything except that is discarded and instead it will continue going down that set of moves
*/