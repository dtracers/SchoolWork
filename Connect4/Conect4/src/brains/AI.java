package brains;

import java.util.ArrayList;
import java.util.Random;

public class AI extends Thread
{
	int width;
	int height;
	ArrayList<Move> enemyThreats;//possible winning moves for enemy
	ArrayList<Move> myThreats;//possible winning moves for me
	int[][] board;
	Move lastMove;
	Move bestMove;
	int enemyPieceType=-1;
	int myPieceType;
	int turn;
	int emptySquaresLeft;//this can be computed as a subtraction each time a move is made
	//an even or odd number of squares matter
	boolean changed=false;
	boolean bestMoveset=false;
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
		while(true)
		{
			try
			{
				if(changed)
				{
					System.out.println("AI BOARD");
					computeThreats(false);
					changed=false;
				}
			//	System.out.println("AI THREAD");
				this.sleep(100);
				Random r=new Random();
				//if a better move has not already been set randomly choose
				setBestMove(new Move(r.nextInt(board.length),r.nextInt(board[0].length)));
			} catch (InterruptedException e)
			{
				e.printStackTrace();
			}
		}
	}
	public synchronized void getLatestMove(Move m)
	{
		lastMove=new Move(m);
		changed=true;
		bestMoveset=false;
	}
	public synchronized void retrieveBoard(int[][] grid)
	{
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
		Row[]rows=getNextRow(mine?this.myPieceType:this.enemyPieceType,lastMove);
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
			setBestMove(threats.get(0),true);
			System.out.println("Computed threats are "+threats);
		}else
		{
			System.out.println("No new threats formed");
		}
		for(Move m: threats)
		{
			if(mine)
				myThreats.add(m);
			else
				enemyThreats.add(m);
	//		GameEngine.makeMove(m.getX(), m.getY(), -5);
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
//			System.out.println("Direction "+direction);
			getNextRowLB(m.getX(),m.getY(),temp);
//			System.out.println("finished rowing");
//			System.out.println(temp);
//			System.out.println("next");
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
		if(r.numberInRow==3)
		{
	//		System.out.println("THREES COMPANAY");
		}
		r.setMove(x, y, r.numberInRow+1);
	//	System.out.println("Getting next Row at X: "+x+" Y: "+y);
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
	//		System.out.println("NEW PLACES "+newX+" "+newY);
			int piece=board[newY][newX];
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