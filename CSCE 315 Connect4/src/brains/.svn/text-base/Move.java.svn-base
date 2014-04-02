package brains;

public class Move
{
	private int x;	//Column
	private int y;	//Row
	private int type;			//type==-1 then flip board, type==-2 then it is remove piece, type==0 it is a null move
	private int ownersPieceType;
	public Move(int x,int y,int piece)
	{
		this(x,y);
		setPiece(piece);
	}
	public Move(int x,int y)
	{
		this.setX(x);this.setY(y);
	}
	public Move(Move v)
	{
		if(v!=null)
		{
			this.setX(v.getX());this.setY(v.getY());
			this.setPiece(v.getPiece());
		}
	}
	public Move(int xcell, int ycell, int i, int turnCounter)
	{
		this(xcell,ycell,i);
		setPlayerPiece(turnCounter);
	}
	public int getX()
	{
		return x;
	}
	public void setX(int x)
	{
		this.x = x;
	}
	public int getY()
	{
		return y;
	}
	public void setY(int y)
	{
		this.y = y;
	}
	public String toString()
	{
		return "X: "+x+" Y: "+y+" Ty: "+type; 
	}
	
	/**
	 * whether its a flip drop or remove
	 * @param number
	 * @return
	 */
	public int getPiece()
	{
		return type;
	}
	@Override
	public boolean equals(Object c)
	{
		if(c instanceof Move)
		{
			Move c2=((Move) c);
			return c2.x==this.x&&this.getPiece()==c2.getPiece();
		}
		return false;
	}
	//Use this to send the move to the client and sever
	public String sendMove()
	{
		//type
		String sendMove = "";

		//type>0 then it is a drop piece #=player who made move
		if(type == -1){
			sendMove = ("f");
			return sendMove;
		}
		else if(type == -2){
			sendMove = ("r " + x);
			return sendMove;
		}
		else{
			System.out.println("type! "+type);
			sendMove = ("d " + x);
			return sendMove;
		}
	}
	
	//Parses a string and places the client/server's move on the board
	public static Move getMove(String g)
	{
		String[] splits=g.split(" ");
		
		if(splits[0].equals("d"))
		{
			//splits[1] is a number	
			try{
				int columnNumber = 0;
				columnNumber = Integer.parseInt(splits[1]);
				Move m = new Move(columnNumber, 0);
				return m;
			}
			catch(Exception e){
				System.err.println("Error: " + e);
				
			}
		}
		else if(splits[0].equals("f"))
		{
			System.out.println("flipping a move!!");
			//splits[1] is a number	
			try{
				int columnNumber = 0;
			//	columnNumber = Integer.parseInt(splits[1]);
				Move m = new Move(0, 0,-1);
				return m;
			}
			catch(Exception e){
				System.err.println("Error: " + e);
			}
		}
		if(splits[0].equals("r"))
		{
			//splits[1] is a number	
			try{
				int columnNumber = 0;
				columnNumber = Integer.parseInt(splits[1]);
				Move m = new Move(columnNumber, 0,-2);
				return m;
			}
			catch(Exception e){
				System.err.println("Error: " + e);
			}
		}
		return null;
	}
	
	public void setPiece(int type)
	{
		this.type = type;
	}
	
	/**
	 * Returns who owns the piece
	 * @param number
	 * @return
	 */
	public int getPlayerPiece()
	{
		return ownersPieceType;
	}
	public void setPlayerPiece(int ownersPieceType)
	{
		this.ownersPieceType = ownersPieceType;
	}
}
