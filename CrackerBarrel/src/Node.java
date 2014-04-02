import java.util.ArrayList;


public class Node
{
	int index;
	static Node[] listOfNodes;
	ArrayList<Moves> possibleMoves=new ArrayList<Moves>();
	static int[] leftSide;
	public Node(int index2)
	{
		index=index2;
	}
	public static void main(String args[])
	{
		makeGraph(15,0,5);
		for(Node n:listOfNodes)
		{
			System.out.println("index is "+(n.index+1)+" "+n.possibleMoves);
		}
	}
	public static void makeGraph(int size,int type,int rows)
	{
		listOfNodes=new Node[size];
		int index=0;
		leftSide=new int[rows];
		for(int k=0;k<rows;k++)
		{
			leftSide[k]=index;
			for(int q=0;q<=k;q++)
			{
			//	System.out.println("row "+q+" row# "+k+"index "+index);
				listOfNodes[index]=new Node(index);
				index++;
			}
		}
		index=0;
		int row=0;
		int rowCounter=0;
		while(index<size)
		{
			Node n=listOfNodes[index];
			int placement=index-leftSide[row];
			if(row-2>=0)
			{
				//we can go up
				if(placement-2>=0)
				{
					//it can go left
					n.possibleMoves.add(new Moves(index,leftSide[row-1]+placement-1,leftSide[row-2]+placement-2));
				}
				if(placement<=row-2)
				{
					//it can go right
					n.possibleMoves.add(new Moves(index,leftSide[row-1]+placement,leftSide[row-2]+placement));
				}
			}
			//left and right
			if(placement-2>=0)
			{
				//it can go left
				n.possibleMoves.add(new Moves(index,index-1,index-2));
			}
			if(placement+2<=row)
			{
				//it can go right
				n.possibleMoves.add(new Moves(index,index+1,index+2));
			}
			if(row+2<rows)
			{
				//it doesnt matter for triangle
				if(placement>=0)
				{
					//it can go left
					n.possibleMoves.add(new Moves(index,leftSide[row+1]+placement,leftSide[row+2]+placement));
				}
				if(placement<=row)
				{
					//it can go left
					n.possibleMoves.add(new Moves(index,leftSide[row+1]+placement+1,leftSide[row+2]+placement+2));
				}
			}
		//	System.out.println("row "+rowCounter+" row# "+row+"index "+index);
			if(row==rowCounter)
			{
				row++;
				rowCounter=-1;
			}
			rowCounter++;
			index++;
		}
	}
	/*
	public static int[] makeLeftSide(int[] indexes,int rows)
	{
		int index=0;
		int[] side=new int[rows];
		for(int k=0;k<rows;k++)
		{
			side[k]=indexes[index];
			index+=k;
			/*
			for(int q=0;q<=k;q++)
			{
				System.out.println("row "+q+" row# "+k+"index "+index);
				listOfNodes[index]=new Node(index);
				index++;
			}
		//*//*
		}
		return side;
	}
	*/
}
