package brains;

/**
 * This will hold up to three moves (any more and the game should already be over)
 * It will hold two possible moves needed to complete the row
 * @author gigemjt
 *
 */
public class Row
{
	Move one,two,three;
	Move LBPossible,TRPossible;
	int direction;
	int numberInRow;
	int piecetype;
	public Row(int direction,int piecetype)
	{
		this.direction=direction;
		this.piecetype=piecetype;
	}
	public void setMove(int newX,int newY,int number)
	{
		switch(number)
		{
			case 1:
				one=new Move(newX,newY);break;
			case 2:
				two=new Move(newX,newY);break;
			case 3:
				three=new Move(newX,newY);break;
			default:
				//too many pieces crash
		}
	}
	public void setMove(Move m,int number)
	{
		switch(number)
		{
			case 1:
				one=m;break;
			case 2:
				two=m;break;
			case 3:
				three=m;break;
			default:
				System.err.println("NUmber is "+number);
				System.err.println("THE GAME SHOULD HAVE ALREADY BEEN ONE OR LOST");
				//too many pieces crash
		}
	}
	public Move getMove(int number)
	{
		switch(number)
		{
			case 1:
				return one;
			case 2:
				return two;
			case 3:
				return three;
			default:
				return null;
				//too many pieces crash
		}
	}
	public String toString()
	{
		return one+"\n"+two+"\n"+three+"\n"+LBPossible+"\n"+TRPossible+"";
	}
}
