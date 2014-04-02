package brains;

import gameplay.GameEngine;
import gameplay.GridStorage;

import java.util.ArrayList;
import java.util.LinkedList;

import javax.swing.JFrame;
import javax.swing.JScrollPane;

public class MinMaxTree
{
	AI ai;
	GridStorage g;//this will be the fake gridstorage object
	boolean changed=false;
	int level;
	Move bestMove;
	TurnedMove changedMove;
	MinMaxTreeNode farthestLeft;
	MinMaxTreeNode topity;
	LinkedList<MinMaxTreeNode> currentLevel;//maybe change to an array
//	LinkedList<MinMaxTreeNode> LevelBeforeCurrent;//this will only have the previous level that is not the current one
	MinMaxTreeNode previous;
	ArrayList<MinMaxTreeNode> realMoves;//this will be the level directly after the last tree has been made
	int playersTurn=0;
	int numberOfPlayers=2;
	boolean debug=false;
	DebugFrame Debugframe;
	public MinMaxTree(AI ai2,GridStorage g)
	{
		this.g=g;
		playersTurn=GameEngine.getTurnCounter();
		ai=ai2;
		currentLevel=new LinkedList<MinMaxTreeNode>();
		MinMaxTreeNode start=new MinMaxTreeNode(new TurnedMove(0,0,0),null,this);
		topity=start;
		start.addPossibleMoves(currentLevel, g.getGrid(), GameEngine.getTurnCounter(),0);
		realMoves=new ArrayList<MinMaxTreeNode>();
		MinMaxTreeNode.height=g.getGrid().length;
		if(debug)
		{
			JFrame f=new JFrame();
			f.setVisible(false);
			f.setSize(1440,800);
			Debugframe=new DebugFrame();
			Debugframe.top=start;
			Debugframe.setSize(10000, 300);
			Debugframe.setTree(topity);
			JScrollPane p=new JScrollPane(Debugframe); 
			f.add(p);
			f.setVisible(true);
		}
	}
	
	/**
	 * this will evaluate the current level and will determine the best move
	 */
	/*
	 * Decision do the next level after this? or do it during eval?
	 */
	public Move EvaluateCurrentLevel()
	{
		if(isChanged())
		{
			removeLeafsExcept(changedMove);
//			TurnedMove best=node.bestMove;
			changed=false;//if it returns null immediately reevaluate level
			//then we need to find which one to keep and which ones to remove
			//put this somewhere else
		}
		if(debug)
			Debugframe.repaint();
		long startTime=System.currentTimeMillis();
		System.out.println("EVALUATING CURRENT LEVEL: "+level);
		System.out.println("Number of nodes at this level is "+currentLevel.size());
		MinMaxTreeNode node=null;
		if(realMoves.size()>0)
		{
			node=realMoves.get(realMoves.size()-1);
		}else
		{
			node=topity;
		}
		if(node==null)
			node=topity;
		LinkedList<MinMaxTreeNode> nextLevel=new LinkedList<MinMaxTreeNode>();
		MinMaxTreeNode newLeft=currentLevel.peek();//this will be the leftest for the next row
		if(newLeft!=null)
			newLeft.doMoves(newLeft,node,g);//its not removing a move done from here... find out why
		incrementTurn();
		int size=currentLevel.size()/4;
		int counter=0;
		while(!currentLevel.isEmpty())
		{
			if(isChanged())
			{
				previous.undoMoves(previous, node, g);
				//reset grid
				GameEngine.resetBoard();
				removeLeafsExcept(changedMove);
				changed=false;
				return null;//if it returns null immediately reevaluate level
				//then we need to find which one to keep and which ones to remove
				//put this somewhere else
			}
			MinMaxTreeNode tn=currentLevel.poll();
			if(tn!=newLeft)
				tn.ParentMove(previous,g);
			tn.evaluate(g,playersTurn, level);
			previous=tn;
			if(counter==size*3)
			{
				System.out.println("three4fway reached");
			}
			counter++;
		}
		//the level has been evaluated
		previous.undoMoves(previous,node,g);
		Move result=null;
		System.out.println("level");
		if(node!=null)
			if(node.currentMove==null||node.currentMove.getPlayerPiece()==ai.getMyPieceType())
			{
				result=node.alphaCut(currentLevel,1,level+1,true);
			}else
			{
				//result=node.alphaCut(currentLevel,1,level+1,true);
			}

		System.out.println("The best move for this level is !"+result);
		node.bestMove=(TurnedMove) result;
		Move best=result;
		if(isChanged())
		{
			removeLeafsExcept(changedMove);
//			TurnedMove best=node.bestMove;
			ai.setBestMove(best,true);
			changed=false;
			return result;//if it returns null immediately reevaluate level
			//then we need to find which one to keep and which ones to remove
			//put this somewhere else
		}
		ai.setBestMove(best,true);
//		System.out.println("The best move so far is! "+result);
		//a bunch have been removed!
		//sets the best move
		
		

		
		/*
		while(!currentLevel.isEmpty())
		{
			currentLevel.poll().
		}
		*/
		//sets up the next Level
//		currentLevel=null;
//		currentLevel=nextLevel;
		System.gc();//do collection please
		long endTime=System.currentTimeMillis();
		System.out.println("time is "+(endTime-startTime));	
		return result;
		//returning null interesting concept!
	}
	/**
	 * returns if there has been a new move placed
	 * @return
	 */
	public boolean isChanged()
	{
		return changed;
	}
	/**
	 * This will be what the new move is changed to
	 * @param turnLevel
	 * @param newMove
	 */
	public synchronized void setTurnLevel(int turnLevel,Move newMove)
	{
	//	level=turnLevel;
		changedMove=new TurnedMove(newMove);
		changedMove.turn=turnLevel;
		changed=true;
	}
	/**
	 * if a new move has been placed then this will be called
	 */
	public synchronized void Changed()
	{
		System.out.println("Something has changed!");
		changedMove=new TurnedMove(ai.lastMove);
		changedMove.turn=GameEngine.getTotalTurns();
		changed=true;
	}
	
	/**
	 * This will remove the leafs of the current Move
	 * needs to do two things!
	 * Number one get the current level of moves... like a list which should only be a single tree or single level
	 * 
	 * IM GOING TO SLEEP
	 * REMEMBER!!!!
	 * TODO:
	 * THE ALPHA BETA CUTTING WILL ACTUALLY REMOVE POSSIBLE MOVES SO THEn THE GAME FREAKS OUT
	 * THIS NEEDS TO BE HANDLED
	 * THE ONLY MOVES THAT SHOULD BE CUT ARE ONES THAT WIN OR LOSE A GAME BECAUSE THEN IT DOESNT MATTER
	 * @param v
	 */
	public void removeLeafsExcept(TurnedMove v)
	{
		System.out.println("removing leafs!");
		long startTime=System.currentTimeMillis();
		MinMaxTreeNode saved=null;
		//O(boardLength*2+1)
		MinMaxTreeNode lastMove=null;
		int size=realMoves.size();
		System.out.println("size is "+size);
		if(size>0)
			lastMove=realMoves.get(size-1);
		else
			lastMove=topity;
		System.out.println("last move is "+lastMove+" the move is "+lastMove.currentMove);
		ArrayList<MinMaxTreeNode> levelAfterLastTurn=lastMove.nextLevel;
		boolean movefound=false;
		for(int k=0;k<levelAfterLastTurn.size();k++)
		{
			MinMaxTreeNode node=levelAfterLastTurn.get(k);
			if(node!=null)
			{
				System.out.println("going through the levels! "+node.currentMove+" compared to "+v);
				if(!movefound&&node.currentMove.equals(v))
				{
					movefound=true;
					saved=node;
				}else
				{
					levelAfterLastTurn.remove(k);
					k--;
				}
			}
		}
		if(saved==null)
		{
			System.out.println("huh freak out! "+lastMove.currentMove);
		}
		realMoves.add(saved);
		if(saved!=null&&saved.parent!=null)
			saved.parent.nextLevel=null;
		if(saved!=null)
			currentLevel=new LinkedList<MinMaxTreeNode>();//  new queue here! instead
		
		//O(2^(n-1))   n is number of levels... this needs to be made faster!  but it is only once per a move!
		//n= depth of tree-current turn level
		//meaning after this the level is one less
		if(saved!=null)
			saved.addAll(currentLevel,g.getGrid(),-1,-1);
		/*
		LinkedList<MinMaxTreeNode> newLevelBefore=new LinkedList<MinMaxTreeNode>();
		
		while(!LevelBeforeCurrent.isEmpty())//we only need this queue for this purpose
		{
			MinMaxTreeNode n=LevelBeforeCurrent.poll();
			if(n.HighestParent==saved)
			{
				newLevelBefore.add(n);//only these are kept
				n.addPossibleMoves(currentLevel);
			}
		}
		//new queue has been made
		LevelBeforeCurrent=null;
		LevelBeforeCurrent=newLevelBefore;//now the shortened queue is here
		*/
		//hopefully java will gc!
		//ill tell to do it for now... ill remove it later
		System.gc();
		long endTime=System.currentTimeMillis();
		System.out.println("time is "+(endTime-startTime));	
	}
	
	public void incrementTurn()
	{
		level++;
		playersTurn++;
		if(playersTurn>numberOfPlayers)
		{
			playersTurn=1;
		}
	}
	//moves that result in the tree not going further
		//moves that lead to a win are kept over all other moves in the same level
		//moves that lead to a loss are instantly taken as wrong choices
	
	//moves that actually change the gameplay
		//flipping board
		//removing a piece
	
	//moves that can be determined by solved method
		//all other moves
}
