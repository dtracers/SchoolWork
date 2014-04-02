package gameplay;

import brains.Move;

/**
 * This class is so that all concurrent threads trying to access the grid will only do so through a synchronized method
 * @author gigemjt
 *
 */
public class GridStorage
{
	private int[][] grid;
	Move lastMove;
	public synchronized int[][] getGrid()
	{
		//Sharath - Can just return grid, than return copy.
		/*int[][] copy=new int[grid.length][grid[0].length];
		for(int k=0;k<grid.length;k++)
		{
			for(int q=0;q<grid[0].length;q++)
			{
				copy[k][q]=grid[k][q];
			}
		}*/ 
		return grid;
	}
	public synchronized void setPiece(int x, int y, int piece)
	{
		int tempy=y;
		while(tempy<grid.length&&grid[tempy][x]==0)
		{
			tempy++;
		}
		tempy-=1;
		grid[tempy][x]=piece;
		lastMove=new Move(x,tempy,piece);
	}
	public synchronized Move lastMove()
	{
		return new Move(lastMove);
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
		//int[][]grid=getGrid(); - Sharath -> Don't do unnecessary getGrids
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
}
