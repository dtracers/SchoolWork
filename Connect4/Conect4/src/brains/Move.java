package brains;

public class Move
{
	private int x;
	private int y;
	int scoreValue;
	int type;
	public Move(int x,int y,int piece)
	{
		this(x,y);
		type=piece;
	}
	public Move(int x,int y)
	{
		this.setX(x);this.setY(y);
	}
	public Move(Move v)
	{
		this.setX(v.getX());this.setY(v.getY());
		this.scoreValue=v.scoreValue;
		this.type=type;
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
		return "X: "+x+" Y: "+y+" V: "+scoreValue; 
	}
}
