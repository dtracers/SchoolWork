package brains;
/**
 * this is a turned move it will be a move that knows what its turn is
 * @author gigemjt
 *
 */
public class TurnedMove extends Move
{
	int turn;
	int scoreValue;
	public TurnedMove(int x, int y)
	{
		super(x, y);
	}

	public TurnedMove(Move v)
	{
		super(v);
		if(v instanceof TurnedMove)
		{
			this.turn=((TurnedMove) v).turn;
			this.scoreValue=((TurnedMove) v).scoreValue;
		}
	}

	public TurnedMove(int x, int y, int piece)
	{
		super(x, y, piece);
	}
	
	public TurnedMove(int x, int y, int piece,int turn)
	{
		super(x, y, piece);
		this.turn=turn;
	}
	public TurnedMove(int x, int y, int piece,int owner,int turn)
	{
		super(x, y, piece);
		this.turn=turn;
	}
	@Override
	public boolean equals(Object c)
	{
		if(c instanceof TurnedMove)
		{
			return (super.equals(c)&&this.turn==((TurnedMove) c).turn);
		}
		return false;
	}
	public String toString()
	{
		return super.toString()+" V: "+scoreValue+" T: "+turn;
	}

	/**
	 * A shorter string for easy reading
	 * @return
	 */
	public String shortString()
	{
		return "T:"+turn+" "+this.getPlayerPiece()+" "+this.getPiece();
	}
}
