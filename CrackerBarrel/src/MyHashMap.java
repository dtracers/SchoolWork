import java.util.HashMap;

public class MyHashMap
{
	HashMap<Integer,State> map=new HashMap<Integer,State>();
	HashMap<String,Moves[]> moveMap=new HashMap<String,Moves[]>();
	int countHash=0;
	public boolean put(State t)
	{
		int i1=t.state;
	//	System.out.println();
	//	System.out.println("hash 1\t"+Integer.toBinaryString(i1));
		int i2=t.hash(1);
	//	System.out.println("hash 2\t"+Integer.toBinaryString(i2));
		int i3=t.hash(2);
	//	System.out.println("hash 3\t"+Integer.toBinaryString(i3));
	//	int i4=t.hash(3);//this is for mirroring
		State oldState=map.get(i1);
		if(oldState!=null)
		{
			oldState.combineState(t);
			return true;
		}
		oldState=map.get(i2);
		if(oldState!=null)
		{
			oldState.combineState(t);
			return true;
		}
		oldState=map.get(i3);
		if(oldState!=null)
		{
			oldState.combineState(t);
			return true;
		}
		/*
		oldState=map.get(i4);
		if(oldState!=null)
		{
			oldState.combineState(t);
			return true;
		}
		*/
		map.put(i1, t);
		return false;
	}
	/**
	 * Tries to return duplicate
	 * if duplicate doesn't exist then it returns itself
	 * @param t
	 * @return
	 */
	public State get(State t)
	{
		int i1=t.state;
		/*
		System.out.println();
		System.out.println("hash 1\t"+Integer.toBinaryString(i1));
		*/
		int i2=t.hash(1);
		
		//System.out.println("hash 2\t"+Integer.toBinaryString(i2));
		
		int i3=t.hash(2);
		
		int i4=t.hash(3);
		//System.out.println("hash 3\t"+Integer.toBinaryString(i3));
		State oldState=map.get(i1);
		if(oldState!=null)
		{
			return oldState;
		}
		oldState=map.get(i2);
		if(oldState!=null)
		{
			return oldState;
		}
		oldState=map.get(i3);
		if(oldState!=null)
		{
			return oldState;
		}
		/*
		oldState=map.get(i4);
		if(oldState!=null)
		{
			return oldState;
		}
		*/
		return t;
	}
	public String hash(Moves[] m)
	{
		String hash="";
		for(int k=0;k<m.length;k++)
		{
			if(m[k]!=null)
				hash+=m[k].toString();
		//	else
		//		hash+=" null";
		}
	//	System.out.println("hashed moves "+hash);
		countHash++;
		return hash;
	}
}
