
public class Moves
{
	public Moves()
	{
		
	}
	public Moves(int from,int ac,int to)
	{
		indexFrom=from;
		indexAcross=ac;
		indexTo=to;
	}
	int indexFrom;
	int indexAcross;
	int indexTo;
	/*
	public String toString()
	{
		return "from "+(indexFrom)+" across "+(indexAcross)+" to "+(indexTo);
	}
	*/
	public String toString()
	{
		return " ["+(indexFrom+1)+
			//	" "+(indexAcross+1)+ 
				"->"+
				" "+(indexTo+1)+"]";
	}
}
