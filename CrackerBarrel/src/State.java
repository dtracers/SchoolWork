import java.util.ArrayList;
import java.util.Arrays;



public class State implements Cloneable
{
	//ArrayList<Moves[]> paths=new ArrayList<Moves[]>();//there are only listSize-1 possible moves,  also the first one will be the only complete one
	Moves[] moves;//the 13 index is used for terminating moves as it should not actually be used by a move
	int moveIndex;
	static int[] BitNumbersOne;//this will contain a bunch of zeros and one 1 at the correct spot - or function
	static int[] BitNumbersZero;//this will contain a bunch of ones and one zero at the correct spot and function
	static int[] rotation1;//this contains the index for rotations for the first rotation
	static int[] rotation2;//this contains the index for rotations for the second rotation
	int state;
	static int listSize;
	public State()
	{
	//	paths=new ArrayList<Moves[]>();
		moves=new Moves[listSize-2];
	//	paths.add(moves);
	}
	public State(State t)
	{
	//	int index=t.paths.indexOf(t.moves);	
	//	paths=new ArrayList<Moves[]>();
	//	paths.addAll(t.paths);
		moves=Arrays.copyOf(t.moves, t.moves.length);
		state=t.state;
	//	paths.set(index, moves);
		moveIndex=t.moveIndex;
	}
	//true is 1
	//false is zero
	public void makeMove(int index,boolean to)
	{
		
		if(!to&&false)
		{
			System.out.println("index is "+index+" before \t"+by(state));
			System.out.println("bit at one is \t\t"+by(BitNumbersOne[index]));
			System.out.println("bit at zero is \t\t"+by(BitNumbersZero[index]));
		}
		state=to?(state|BitNumbersOne[index]):(state&BitNumbersZero[index]);
		//if(to&&index==0)
		//	System.out.println("adding 1 is "+to+"after \t"+by(state));
	}
	public int makeMoveReturnLoc(int num,int index,boolean to)
	{
		return to?(num|BitNumbersOne[index]):(num&BitNumbersZero[index]);
	}
	/*
	 * returns true if the move is a 1 false other wise
	 */
	public boolean getMove(int index)
	{
		return (state&BitNumbersOne[index])==BitNumbersOne[index];
	}
	public boolean canDoAction(Moves m)
	{
		/*
		if(m.indexFrom==9&&m.indexTo==7&&m.indexAcross==8&&false)
		{
			boolean from=getMove(m.indexFrom);
			boolean to=getMove(m.indexTo);
			boolean across=getMove(m.indexAcross);
			System.out.println("state "+this);
			System.out.println("from is empty "+from);
			System.out.println("to   is empty "+to);
			System.out.println("Ac   is empty "+across);
		}
		*/
		return !getMove(m.indexFrom)&&getMove(m.indexTo)&&getMove(m.indexAcross);
	}
	/**
	 * Assumes action can get done
	 * returns true if the end is met
	 * @param m
	 */
	public boolean doAction(Moves m)
	{
		makeMove(m.indexFrom,true);//removes it from where it was
		makeMove(m.indexTo,false);//puts it where it is
		makeMove(m.indexAcross,false);//removes the one it went across
		moves[moveIndex]=m;
		moveIndex++;
		if(moveIndex+2==listSize)
		{
		//	System.out.println("huh huh?");
			return true;
		}
		return false;
	}
	public void combineState(State t)
	{
		
		if(moveIndex>0//&&false
								)
		{
			Moves m=moves[moveIndex-1];
			if(m!=null)
			{
				if(m instanceof SharedMoves)
				{
					((SharedMoves)m).add(t.moves);
				}else
				{
					SharedMoves m2=new SharedMoves(moveIndex-1,m,t.moves);
					moves[moveIndex-1]=m2;
				}
			}
		}
		
		//System.out.println("combining");
	//	paths.addAll(t.paths);
		/*
		for(Moves[] m:t.paths)
		{
			if(m[0]!=null)
			{
				paths.add(m);
			}
		}
		*/
		//t.paths.clear();
		
		//SharedMoves m=new SharedMoves(moveIndex,t.paths,moves[moveIndex]);
		//moves[moveIndex]=m;
		/*
		if(paths!=null&&t.paths!=null)
		{
			for(Moves[] moves:t.paths)
			{
			//	moves[13]=new SharedMoves(state,moveIndex,this.moves);
				paths.add(moves);
			}
		}
		*/
	}
	public Object clone()
	{
		return new State(this);
	}
	//returns a hash based on the three states
	public int hash(int rot)
	{
		int ret=0;
		if(rot==1)
		{
			if(rotation1==null)
				return state;
			int hash=0;
			for(int k=0;k<rotation1.length;k++)
			{
	//			System.out.println("rot1 k "+k+"st "+by(state)+":"+by(hash));
				hash=hash|makeMoveReturnLoc(0,rotation1[k],getMove(k));
			}
			return hash;
		}
		if(rot==2)
		{
			if(rotation2==null)
				return state;
			int hash=0;
			for(int k=0;k<rotation2.length;k++)
			{
				hash=hash|makeMoveReturnLoc(0,rotation2[k],getMove(k));
			}
			return hash;
		}
		return 0;
	}
	public static void initialize(int graphsize,int rows,boolean triangle)
	{
		listSize=graphsize;
		//makes the bit numbers
		BitNumbersOne=new int[graphsize];
		BitNumbersZero=new int[graphsize];
		for(int k=0;k<BitNumbersOne.length;k++)
		{
			int number=1<<k;
			BitNumbersOne[k]=number;
			BitNumbersZero[k]=~number;
		}
		//needs to make the rotation
		if(triangle)
		{
			int[] defaultrot=new int[graphsize];
			rotation1=new int[graphsize];
			rotation2=new int[graphsize];
			for(int k=0;k<graphsize;k++)
			{
				defaultrot[k]=k;
			}
	//		System.out.println("orignal rotation "+Arrays.toString(defaultrot));
	//		System.out.println("orignal rotation grid \n"+printAsGrid(defaultrot));
	//		System.out.println("left side "+Arrays.toString(Node.leftSide));
			MakeRotation(defaultrot,rotation1,rows);
	//		System.out.println("post rotation "+Arrays.toString(rotation1));
	//		System.out.println("post rotation grid \n"+printAsGrid(rotation1));
			MakeRotation(rotation1,rotation2,rows);
	//		System.out.println("post rotation2 "+Arrays.toString(rotation2));
	//		System.out.println("post rotation2 grid \n"+printAsGrid(rotation2));
			//find the rule for the rotations now
		}else
		{
			//else do this!
		}
	}
	public static void main(String args[])
	{
		initialize(15,5,false);
	}
	public String toString()
	{
		return by(state);
	}
	public static void MakeRotation(int[] from,int[]to,int rows)
	{
		ArrayList<int[]> arrays=new ArrayList<int[]>();
		int index=0;
		for(int k=0;k<rows;k++)
		{
			int[] list=new int[rows-k];
			index=k;
			while(index<rows)
			{
				list[index-k]=from[Node.leftSide[index]+k];
				System.out.println("index "+index+" k "+k+" number "+list[index-k]);
				index++;
			}
			arrays.add(list);
		}
		System.out.println(arrays);
		index=0;
		for(int k=arrays.size()-1;k>=0;k--)
		{
			int[] list=arrays.get(k);
			for(int q=0;q<list.length;q++)
			{
				to[index]=list[q];
				index++;
			}
		}
	}
	public static String printAsGrid(int[] list)
	{
		int index=0;
		int row=0;
		int rowCounter=0;
		String printout="";
		while(index<list.length)
		{
			printout+=list[index]+"\t";
			if(row==rowCounter)
			{
				printout+="\n";
				row++;
				rowCounter=-1;
			}
			rowCounter++;
			index++;
		}
		return printout;
	}
	public static String by(int i)
	{
		String result=Integer.toBinaryString(i);
		while(result.length()<8)
		{
			result="0"+result;
		}
		return result;
	}
}
