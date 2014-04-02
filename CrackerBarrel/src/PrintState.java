import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Queue;



public class PrintState
{
	static MyHashMap myMap;
	static Queue<State> listOfStates=new LinkedList<State>();
	public static void main(String args[])
	{
		//(4,10)(5,15)(6,21)(7,28)
		int rows =6;
		int startingSize=21;
		System.out.print("Intilizing");
		myMap=new MyHashMap();
		Node.makeGraph(startingSize, 0,rows);
		System.out.print(".1");
		State.initialize(startingSize,rows, true);
		System.out.print(".2");
		State start=new State();
		for(int k=0;k<startingSize;k++)
		{
			start.makeMove(k,true);
		}
		System.out.print(".3");
		for(int k=0;k<startingSize;k++)
		{
			State copy=(State) start.clone();
			copy.makeMove(k, false);
			if(!myMap.put(copy))
				listOfStates.add(copy);
			System.out.println(".done");
			System.out.println("warmingup");
		//	System.out.println(listOfStates);
		//	System.out.println(myMap.map);
			System.out.println("Starting");
			
			
			long startTime=System.currentTimeMillis();
			Evaluate();
			long endTime=System.currentTimeMillis();
			System.out.println("total time in millis is "+(endTime-startTime));
			listOfStates.clear();
			myMap.moveMap.clear();
			myMap.map.clear();
			System.gc();
		}
		
	}
	public static void Evaluate()
	{
		ArrayList<State> solutionStates=new ArrayList<State>();
		int index=0;
		int oldSize=0;
		int hold=0;
		while(!listOfStates.isEmpty())
		{
			State toEval=listOfStates.poll();
			if(toEval.moveIndex!=oldSize)
			{
				myMap.map=new HashMap<Integer,State>();
				System.out.println("new index "+toEval.moveIndex+" old index "+oldSize);
				oldSize=toEval.moveIndex;
				
				if(hold>9)
					System.gc();
				
				hold++;
			}
			/*
			if(index%1000==0)
			{
			//	System.out.println("map   size "+myMap.map.size());
			//	System.out.println("list  size "+listOfStates.size());
			//	System.out.println("index size "+index);
			//	System.gc();
			}
			
			if(index%10000==0)
			{
			//	System.gc();
			}
			*/
			index++;
			//it is true that once we are on move two we have none left on move one
			//so if that is true then we can in face delete the previous map as it is of no use to us
	//		System.out.println("list size "+listOfStates.size());
	//		System.out.println("state to evaluate "+toEval);
			for(int k=0;k<State.listSize;k++)
			{
				//returns true if a 1 is there
				if(!toEval.getMove(k))
				{
					for(Moves m:Node.listOfNodes[k].possibleMoves)
					{
						if(toEval.canDoAction(m))
						{
							State result=(State) toEval.clone();
							boolean finished=result.doAction(m);
							boolean exist=myMap.put(result);
							if(!finished&&!exist)
							{
								listOfStates.add(result);//adds the next one to add to the list
							}else if(exist)
							{
		//						System.out.println("duplicate state");
							}else if(finished)
							{
								solutionStates.add(myMap.get(result));//only used at end
								//return;
							}
						}
					}
				}
			}
		}
		
		int numsolutions=0;
		for(State t:solutionStates)
		{		
		//	System.out.println("solution! "+t);
			/*
			for(int k=t.moves.length;k>=0;k--)
			{
				
			}
			*/
			/*
			for(Moves m:t.moves)
			{
				System.out.println("\t"+m);
			}
			*/
			numsolutions+=countStates(t.moves,t.moves.length-1);
		//	System.out.println("t}SOLUTION ENDING "+numsolutions);
		}
		System.out.println("t}SOLUTION ENDING "+numsolutions);
		if(true)
			return;
		System.out.println("Total Solutions "+numsolutions);
		System.out.println("Total mapped solutions "+myMap.moveMap.size());
		System.out.println("Total hashings "+myMap.countHash);
		/*
		for(String keys:myMap.moveMap.keySet())
		{
			Moves[] move=myMap.moveMap.get(keys);
			State start=new State();
			for(int k=0;k<move.length+2;k++)
			{
				start.makeMove(k,true);
			}
		//	System.out.println("Starting state "+start);
			/*
			for(int q=0;q<move.length;q++)
			{
				Moves m=move[q];
				if(q==0)
				{
				//	System.out.println("Making move index "+m.indexTo);
				//	System.out.println("Making start "+start);
					start.makeMove(m.indexFrom, false);
				//	System.out.println("Making start "+start);
				}
				if(start.canDoAction(m))
				{
					start.doAction(m);
				//	System.out.println("index "+q);
				//	System.out.println("After action "+start+" move: "+m);
				}else
				{
				//	System.out.println("THIS IS CHEATING!"+q +" "+m);
				}
			}
			*/
	//	}
	//	*/
		//IM DONE!!!!
	}
	public static int countStates(Moves[] m,int index)
	{
		int counter=1;
//		myMap.moveMap.put(myMap.hash(m), m);
		for(int k=index;k>=0;k--)
		{
			if(m[k] instanceof SharedMoves)
			{
				SharedMoves shared=(SharedMoves) m[k];
				for(Moves[] path:shared.paths)
				{
					/*
					for(int q=k+1;q<path.length;q++)
					{
						if(m[q] instanceof SharedMoves)
						{
							Moves move=m[q];
							path[q]=new Moves(move.indexFrom,move.indexAcross,move.indexTo);
						}else
						{
							path[q]=m[q];
						}
					}
					*/
					counter+=countStates(path,k);
				}
			}
		}
		//System.out.println("Moves "+Arrays.toString(m));
		return counter;
	}
}
