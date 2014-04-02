import java.util.ArrayList;


public class SharedMoves extends Moves
{
	//int state;//int state of the object
	int moveNumber;//note that this is the state of the terminating move in the other array
	ArrayList<Moves[]> paths;
	public SharedMoves(int moveNumber,Moves current,Moves[] newSet)
	{
		super();
		paths=new ArrayList<Moves[]>();
		paths.add(newSet);
		this.moveNumber=moveNumber;
		if(current!=null)
		{
			indexTo=current.indexTo;
			indexFrom=current.indexFrom;
			indexAcross=current.indexAcross;
		}
	}
	
	public String toString()
	{
		return super.toString();//+" Shared Move ";
	}
	 
	public void add(Moves[] moves)
	{
		paths.add(moves);
	}
}
