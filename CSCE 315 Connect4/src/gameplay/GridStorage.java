package gameplay;

import java.util.ArrayList;

import javax.swing.JFrame;

import brains.DebugFrame;
import brains.Move;

/**
 * This class is so that all concurrent threads trying to access the grid will only do so through a synchronized method
 * @author gigemjt
 *
 */
public class GridStorage
{
	DebugFrame Debugframe;
	public GridStorage fakeGrid=null;//this will be a copy that can only be affected by all types of set pieces but wont affect other grid
	private int[][] grid;
	Move lastMove;
	ArrayList<Move> moves;
	boolean debug=false;
	int piecesOnBoard=0;
	public GridStorage()
	{
		moves=new ArrayList<Move>();
		grid=new int[1][1];

		if(debug)
		{
			JFrame f=new JFrame();
			f.setVisible(false);
			f.setSize(1440,800);
			Debugframe=new DebugFrame();
			Debugframe.setList(moves);
			f.add(Debugframe);
			f.setVisible(true);
		}
	}
	public GridStorage(GridStorage gridStorage)
	{
		this();
		grid=new int[gridStorage.grid.length][gridStorage.grid[0].length];
		lastMove=gridStorage.lastMove;
	}
	public synchronized int[][] getGrid()
	{
		int[][] copy=new int[grid.length][grid[0].length];
		for(int k=0;k<grid.length;k++)
		{
			for(int q=0;q<grid[0].length;q++)
			{
				copy[k][q]=grid[k][q];
			}
		}
		return copy;
	}

	public synchronized Move lastMove()
	{
		return lastMove;
	}
	public synchronized void setGrid(int[][] grid)
	{
		this.grid = grid;
	}
	public synchronized void setGridLengths(int yNum, int xNum)
	{
		grid=new int[yNum][xNum];
	}

	public void printGrid()
	{
		for(int[]arr: grid)
		{
			for(int inx:arr)
			{
				System.out.print(inx);
			}
			System.out.println();
		}
	}
	public static void printGrid(int[][]grid)
	{
		for(int[]arr: grid)
		{
			for(int inx:arr)
			{
				System.out.print(inx);
			}
			System.out.println();
		}
	}
	public void createFakeGrid()
	{
		fakeGrid=new GridStorage(this);
		if(debug)
		{
			JFrame f=new JFrame();
			f.setVisible(false);
			f.setSize(1440,800);
			fakeGrid.Debugframe=new DebugFrame();
			fakeGrid.Debugframe.setList(fakeGrid.moves);
			f.add(fakeGrid.Debugframe);
			f.setVisible(true);
		}
	}
	public void setPiece(Move m)
	{
		if(debug)
		{
			Debugframe.repaint();
		}
		moves.add(m);
		int x=m.getX();
		int y=m.getY();
		int piece=m.getPiece();
		if(piece==-1)
		{
			flipBoard();
			lastMove=new Move(0,0,piece);
			return;
		}
		if(piece==-2)
		{
			removePiece(x,y,piece,m.getPlayerPiece());
			lastMove=new Move(x,0,piece);
			return;
		}
		int tempy=0;
		piecesOnBoard+=1;
		
		while(tempy<grid.length&&grid[tempy][x]==0)
		{
			tempy++;
		}
		tempy-=1;
		if(tempy<0)
			return;
		m.setY(tempy);
		if(grid[tempy][x]==0||piece==0)
			grid[tempy][x]=piece;
		lastMove=new Move(x,tempy,piece);
		if(fakeGrid!=null)
		{
			fakeGrid.setPiece(m);
		}
	}
	public void flipBoard()
	{
		//create new board
		int [][] gridFlip = grid;
		int numRows=gridFlip.length;
		int numCols=gridFlip[0].length;	
		//Get rows and columns not empty
		for(int j=0; j<numCols; j++){
			int [] pieceArray = new int[100];
			int pieceArrayLen = 0;
			//pieceArray -> get all the pieces 
			for(int i=0; i< numRows; i++){
				//Initialize the pieceArray
				if(gridFlip[i][j] != 0){
					pieceArray[pieceArrayLen] = gridFlip[i][j];
					pieceArrayLen++;			
				}	
			}
			//Add the pieceArray back to column
			for(int i=0; i< pieceArrayLen; i++){
				gridFlip[numRows - i - 1][j] = pieceArray[i];
			}
		}
		grid = gridFlip;
	}
	
	/*
	 * assuming its a valid move
	 */
	public void removePiece(int x_row,int y_column,int piece, int owner)
	{
		piecesOnBoard-=1;
		//remove a piece in grid
		y_column = grid.length-1;
		int i=y_column;
			//pieceArray -> get all the pieces 
		for(; i>=1; i--){
			//Initialize the pieceArray
			if(grid[i-1][x_row]==0)
			{
				break;
			}
			grid[i][x_row] = grid[i-1][x_row];
		}
		//Add a zero to the top
		grid[i][x_row] = 0;
	}
	//the return of gameWon will be an int of the player who won
	//if its a zero nobody won
	//need to check for a draw... if its a draw
	//if it is a draw it needs to return the number of players plus 1
	//(meaning that if there are two players it returns 3)
	//Returns a 0 if nobody won, 
	public int gameWon()
	{
	//	int totalsum=0;
	//	int piece = lastMove.getPiece();
		int[][] gridarr=grid;
		int rows=gridarr.length;
		int cols=gridarr[0].length;
		int player1 = 1;
		int player2 = 2;
		int sameCnt_up, sameCnt_right, sameCnt_diag_right, sameCnt_diag_left;
		int returnval=0;
		for(int j=cols-1;j>=0;j--){
			for(int i=rows-1;i>=0;i--){
				sameCnt_up = 0;
				sameCnt_right = 0;
				sameCnt_diag_right = 0;
				sameCnt_diag_left = 0;
				//Go four up, right, Diag and check for same
				for(int k=0; k<4; k++){
					if(i+k<rows)
						if(gridarr[i][j]==gridarr[i+k][j] && gridarr[i][j]!=0)
							sameCnt_up+=1;
					if(j+k<cols)
						if(gridarr[i][j]==gridarr[i][j+k] && gridarr[i][j]!=0)
							sameCnt_right+=1;
					if(i+k<rows && j-k>0)
						if(gridarr[i][j]==gridarr[i+k][j-k] && gridarr[i][j]!=0)
							sameCnt_diag_left+=1;
					if(i+k<rows && j+k<cols)
						if(gridarr[i][j]==gridarr[i+k][j+k] && gridarr[i][j]!=0)
							sameCnt_diag_right+=1;
				}
				
				//Check if connect4
				if(sameCnt_up==4 
						|| sameCnt_right==4 
						|| sameCnt_diag_right==4 
						|| sameCnt_diag_left==4){
					
					if(grid[i][j] == player1 && returnval==0)
						returnval = player1;
					else if(grid[i][j] == player2 && returnval==0)
						returnval = player2;
					else
						returnval = 3;
				}
				//For speeding things up
				if(gridarr[i][j] == 0)
					i = 0; //stop search up
			}
		}  
		
		return returnval;
	}
	
	/*
	 * returns #of player who won
	 * 0 if nobody won
	 * <0 if the person who played it lost
	 * and -(num_of_players+1) if it is a draw
	 */
	public int gameWonMove(Move m)
	{
		if(m.getPiece()<0)
		{
			int winner=gameWon();
			if(winner!=m.getPiece())
			{
				winner*=-1;
			}
			return winner;
		}
		int x=m.getX();
		int y=m.getY();
		int piece=m.getPiece();
		int numberInRow=4;
		int totalsum=numberInRow;//piece*numberInRow;
		boolean left,right,up,down;
			left=(x-numberInRow)>=0;
			right=(x+numberInRow)<grid[0].length;
			up=y-numberInRow>=0;
			down=y+numberInRow<grid.length;
			
		int sumLeft=0;
		int sumUpLeft=0;
		int sumDownLeft=0;
		
		int sumRight=0;
		int sumUpRight=0;
		int sumDownRight=0;
		
		int sumUp=0;
		int sumDown=0;
		
		for(int k=0;k>-numberInRow;k--)
		{
			if(left)
			{
				sumLeft+=grid[y][k+x]==piece?1:0;
				if(up)
					sumUpLeft+=grid[k+y][k+x]==piece? 1:0;
				if(down)
					sumDownLeft+=grid[y-k][k+x]==piece? 1:0;
			}
			if(right)
			{
				sumRight+=grid[y][x-k]==piece?1:0;
				if(up)
					sumUpRight+=grid[k+y][x-k]==piece?1:0;
				if(down)
					sumDownRight+=grid[y-k][x-k]==piece?1:0;
			}
			if(up)
			{
				sumUp+=grid[y+k][x]==piece?1:0;
			}
			if(down)
			{
				sumDown+=grid[y-k][x]==piece?1:0;
			}
		}
		boolean won=sumLeft==totalsum||sumUpLeft==totalsum||sumDownLeft==totalsum;
		won=won||sumRight==totalsum||sumUpRight==totalsum||sumDownRight==totalsum;
		won=won||sumUp==totalsum||sumDown==totalsum;
		if(won)
		{
			return 1*m.getPlayerPiece();
		}
		return 0;
	}
	public int gameWonLastMove()
	{
		return gameWonMove(lastMove);
	}
	public int[][] getGridObject()
	{
		return grid;
	}
	public void undoRemovePiece(Move undoingMove)
	{
		int col=undoingMove.getX();
		for(int k=1;k<grid.length;k++)
		{
			if(grid[k][col]!=0)
			{
				grid[k-1][col]=grid[k][col];
			}
		}
//		LowestEmptyPiece[col]--;//move the space up one/
//		System.out.println("undoin!" +undoingMove);
		grid[grid.length-1][col]=undoingMove.getPlayerPiece();
	}
	public int numberOfPieceOnBoard()
	{
	//	System.out.println("pieces on board is "+piecesOnBoard);
		return Math.min(moves.size(),piecesOnBoard);
	}
	public void undoMove(Move currentMove)
	{
	//	moves.remove(currentMove);
		int size=moves.size()-1;
		if(size>=0)
			moves.remove(size);
		if(moves.size()>0)
			this.lastMove=moves.get(moves.size()-1);
	//	System.out.println("Removing "+currentMove);
		int piece=currentMove.getPiece();
		if(piece==-1)
		{
			flipBoard();
		}
		if(piece==-2)
		{
			piecesOnBoard+=1;
			undoRemovePiece(currentMove);
			//undoes remove piece
		}
		if(piece>0)
		{
			piecesOnBoard-=1;
			int x=currentMove.getX();
			grid[currentMove.getY()][x]=0;
//			LowestEmptyPiece[x]++;
			//this.setPiece(currentMove.getX(),currentMove.getY(),0);
		}
//		long delay=75;
//		long start=System.currentTimeMillis();
//		while(System.currentTimeMillis()-start<delay);
	}
}
