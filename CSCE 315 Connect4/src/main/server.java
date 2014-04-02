package main;
/*This file establishes the server side of the connection
 * 
 */

import gameplay.GameEngine;

import java.awt.Menu;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.UnknownHostException;

import javax.swing.JLabel;
import javax.swing.JOptionPane;

import GUI.Display;
import GUI.MainFrame;
import brains.Move;

public class server{
	
	private ServerSocket serverSocket;
	private Socket clientSocket;
	private BufferedReader buff;
	Display	d;
	int type = 0;
	String move;
	Move previous;
	Menu m;
	private boolean outOfTime = false;
	JLabel turnLabel;
	JLabel turnLabel2;

	//Constructor specifies size of board, who goes first, time, and the rules
	public server(int _port, int _row, int _column, String _move, int _time, String _entry){
		try {
			GameEngine.local=false;
				serverSocket = new ServerSocket(_port);
				clientSocket = serverSocket.accept();
				buff = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
				
				write("WELCOME");	//sends WELCOME
				write("info " + _row + " " + _column + " " + _move + " " + _time + " " + _entry);	//send information
				System.out.println("Server reads: " + read());	//reads in READY
				write("BEGIN");		//sends BEGIN
					
				if(_move.toLowerCase().equals("f")){
					type = 1;
					//client goes first
					System.out.println("Type1: " + type);
					GameEngine.setFirst(false);
				}
				else if(_move.toLowerCase().equals("s")){
					type = 2;
					//server goes first
					System.out.println("type2: " + type);
					GameEngine.setFirst(true);
				}
		
				if(_entry.toLowerCase().equals("f")){	//start game allow flips with row & columns & specify whether first or second
			
					GameEngine i=MainFrame.thisFrame.i;
					GameEngine.waitTime=_time;
					//i.setMyPieceType(type);
					MainFrame.thisFrame.setVisible(false);
					MainFrame.thisFrame.start();
					MainFrame.thisFrame.setVisible(true);
					MainFrame.thisFrame.i.setGridLengths(_row, _column);
					MainFrame.thisFrame.i.setTime(_time);
					MainFrame.thisFrame.i.setMyPieceType(type);
					MainFrame.thisFrame.getDisplay().flipsOnly();
					if(type == 1){
						System.out.print("********Client's Turn******" );
					}
					else if(type == 2){
						System.out.print("*******Server's Turn******" );
					}
					if(type == 2){
						startReading();
					}
					else{
						String red=read();
						Move mo=Move.getMove(red);
						if(mo.getPiece()==0)
							mo.setPiece(3-(3-type));
						GameEngine.otherMakeMove(mo);
						previous=mo;
						startReading();
					}
					System.out.println('f');				
				}
				else if(_entry.toLowerCase().equals("r")){	//start game allow removals only with row & columns & specify whether first or second
					GameEngine i=MainFrame.thisFrame.i;
					MainFrame.thisFrame.setVisible(false);
					MainFrame.thisFrame.start();
					MainFrame.thisFrame.setVisible(true);
					MainFrame.thisFrame.i.setGridLengths(_row, _column);
					MainFrame.thisFrame.i.setTime(_time);
					System.out.println("hey "+type);
					MainFrame.thisFrame.i.setMyPieceType(type);
					MainFrame.thisFrame.getDisplay().deleteOnly();

					if(type == 2){
						GameEngine.previousMoveTime=System.currentTimeMillis();
						startReading();
					}
					else{
						String red=read();
						Move mo=Move.getMove(red);
						if(mo.getPiece()==0)
							mo.setPiece(3-(3-type));
						GameEngine.otherMakeMove(mo);
						previous=mo;
						startReading();
					}
					
					System.out.println('r');	
				}		
				else if(_entry.toLowerCase().equals("b")){	//start game allow both with row & columns & specify whether first or second
					GameEngine i=MainFrame.thisFrame.i;
					//i.setMyPieceType(type);
					MainFrame.thisFrame.setVisible(false);
					MainFrame.thisFrame.start();
					MainFrame.thisFrame.setVisible(true);
					MainFrame.thisFrame.i.setGridLengths(_row, _column);
					MainFrame.thisFrame.i.setTime(_time);
					System.out.println("hey "+type);
					MainFrame.thisFrame.i.setMyPieceType(type);
					MainFrame.thisFrame.getDisplay().allowBoth();
					if(type == 2){
						GameEngine.previousMoveTime=System.currentTimeMillis();
						startReading();
					}
					else{
						String red=read();
						Move mo=Move.getMove(red);
						if(mo.getPiece()==0)
							mo.setPiece(3-(3-type));
						GameEngine.otherMakeMove(mo);
						previous=mo;
						startReading();
					}
					System.out.println('b');
				}
				else if(_entry.toLowerCase().equals("n")){	// 	start game allow neither with row & columns & specify whether first or second
					GameEngine i=MainFrame.thisFrame.i;
					
					MainFrame.thisFrame.setVisible(false);
					MainFrame.thisFrame.start();
					MainFrame.thisFrame.setVisible(true);
					MainFrame.thisFrame.i.setGridLengths(_row, _column);
					MainFrame.thisFrame.i.setTime(_time);
					System.out.println("hey "+type);
					MainFrame.thisFrame.i.setMyPieceType(type);
					MainFrame.thisFrame.getDisplay().allowNeither();
					if(type == 2){
						GameEngine.previousMoveTime=System.currentTimeMillis();
						//write
						startReading();
					}
					else{
						String red=read();
						Move mo=Move.getMove(red);
						if(mo.getPiece()==0)
							mo.setPiece(3-(3-type));
						GameEngine.otherMakeMove(mo);
						previous=mo;
						startReading();
					}
					System.out.println('n');
				}	
			}	
			catch (UnknownHostException e) {e.printStackTrace();System.err.println("Server() UnknownHost Exception: " + e); System.exit(1);} 
			catch(IOException e){e.printStackTrace();System.err.println("Server() IOException Exception: " + e);}
			catch (Exception e){e.printStackTrace();System.err.println("Server() Exception error: " + e);	System.exit(1);}	
		}
	
	//reads a move and then passes a move
	public void startReading()
	{
		System.out.println("I started reading");
		while(true)
		{
			Move m=GameEngine.getPreviousMove();
			if((previous!=m)&&m!=null&&!m.equals(previous))
			{
				System.out.println("MAKING A NEW MOVE YAY! "+m);
				previous=m;
				System.out.println("sending "+m.sendMove());
				write(m.sendMove());
				String red=read();
				System.out.println("reading "+red);
				Move mo=Move.getMove(red);
				if(mo.getPiece()==0)
					mo.setPiece(3-(3-type));
				GameEngine.otherMakeMove(mo);
				previous=mo;
				System.out.println("other move "+mo);
			}
			try {
				Thread.sleep(200);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

	//If you run out of time, you lose
	public void timeIsUp(){
		outOfTime = GameEngine.timesOut();
		if(outOfTime == true){
			write("OK");
			write("ILLEGAL");
			write("LOSER");
		}
	}
	
	//Closes the server
	public void close(){
		try {
			clientSocket.close();
			serverSocket.close();
		} 
		catch (UnknownHostException e) {System.err.println("Server close() UnknownHost Exception: " + e); System.exit(1);} 
		catch (IOException e) {e.printStackTrace();}
		catch (Exception e){System.err.println("Server close() Exception error: " + e);	System.exit(1);}
	}
	
	//Sending the information to the server
	public void write(String _string){
		try {
			OutputStream sockOutput = clientSocket.getOutputStream();
			PrintStream m=new PrintStream(sockOutput);
			m.println(_string);
		} 
		catch (UnknownHostException e) {System.err.println("Server write() UnknownHost Exception: " + e); System.exit(1);} 
		catch(IOException e){System.err.println("Server write() IOException error: " + e);}
		catch (Exception e){System.err.println("Server write() Exception error: " + e);	System.exit(1);}
	}
	
	public void insert(char _char){
		insert(_char, 0);
	}
	
	public void insert(char _char, int number){
		if(_char == 'f'){
			write(_char + " ");
		}
		else if (_char == 'r' || _char == 'd'){
			write(_char + " " + number);
		}
	}
	
	public void sendMoves(){
		Move m = GameEngine.getPreviousMove();
		write(m.sendMove());
		
	}
	
	//reads the information that is coming in 
	public String read(){
		try {
			String start = buff.readLine();
			if(start.equals("LOSER")){
				JOptionPane.showMessageDialog(null, "You ran out of Time. You Lose");
			}
			else if(start.equals("WINNER")){
				JOptionPane.showMessageDialog(null, "Congrats! You win!");
			}
			else if(start.equals("TIE")){
				JOptionPane.showMessageDialog(null, "It's a tie! You both win!");
			}
			return start;
		} 
		catch (UnknownHostException e) {System.err.println("Server read() UnknownHost Exception: " + e); System.exit(1);} 
		catch(IOException e){System.err.println("Server read() IOException error: " + e);}
		catch (Exception e){System.err.println("Server read() Exception Error: " + e);	System.exit(1);}
		
		return null;
	}


	public static void main(String args[])
	{
		/*Start game using the menu()
		 *  Then you decide what type of game you want to run
		 */
		GameEngine i = new GameEngine();
		i.repainting();
		i.start();
		
	}

}
