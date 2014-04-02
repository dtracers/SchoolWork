package main;

/* This file establishes the client side.
 * 
 */

import gameplay.GameEngine;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintStream;
import java.net.Socket;
import java.net.UnknownHostException;

import javax.swing.JOptionPane;

import GUI.Display;
import GUI.MainFrame;
import brains.Move;


public class connection{
	
	private Socket c_socket = null;	 //clientServer
	InputStream input;
	OutputStream output;
	boolean connection;
	private BufferedReader buff;
	Display d;
	Move previous;
	String connectionName;
	int connectionNumber;
	private boolean outOfTime = false;
	int type = 0;
	
	public connection(String connectionName, int connectionNumber){
		this.connectionName=connectionName;
		this.connectionNumber=connectionNumber;
		try {
			GameEngine.local=false;
			//you can use "linux.cs.tamu.edu" in connectionName to run it on 2 different computers or use java by using "localhost"
				c_socket = new Socket(connectionName, connectionNumber);
				System.out.println("WORKS");
				buff = new BufferedReader(new InputStreamReader(c_socket.getInputStream()));
				System.out.println("client reads: " + read());	//reads WELCOME
				String[] information = read().split(" ");	//reads Information & parses it
				
				write("READY");	//sends READY
				System.out.println("client reads: " + read());	//reads BEGIN
			
				String info;
				int _row;
				int _column;
				String _move;
				int _time;
				String _entry;
		
				info = information[0];
				_row = Integer.parseInt(information[1]);
				_column = Integer.parseInt(information[2]);
				_move = information[3];
				_time = Integer.parseInt(information[4]);
				_entry = information[5];
					
				if(_move.toLowerCase().equals("f")){
					type = 1;
					GameEngine.setFirst(true);
					//client goes first
				}
				else if(_move.toLowerCase().equals("s")){
					type = 2;
					GameEngine.setFirst(false);
					//server goes first
				}
				
				if(_entry.toLowerCase().equals("f")){	//start game allow flips with row & columns & specify whether first or second
					GameEngine i=MainFrame.thisFrame.i;
					
					GameEngine.waitTime=_time;
					MainFrame.thisFrame.setVisible(false);
					MainFrame.thisFrame.start();
					MainFrame.thisFrame.setVisible(true);
					MainFrame.thisFrame.i.setGridLengths(_row, _column);
					MainFrame.thisFrame.i.setTime(_time);
					MainFrame.thisFrame.i.setMyPieceType(type);
					MainFrame.thisFrame.getDisplay().flipsOnly();
					if(type == 1){
						startReading();
					}
					else{
						String red=read();
						Move mo=Move.getMove(red);
						if(mo.getPiece()==0)
							mo.setPiece(3-type);
						GameEngine.otherMakeMove(mo);
						previous=mo;
						startReading();
					}
					System.out.println('f');
						if(type == 1){
							System.out.print("**********Client's Turn*********" );
						}
						else if(type == 2){
							System.out.print("*********Server's Turn********" );
						}
				}
				else if(_entry.toLowerCase().equals("r")){	//start game allow removals only with row & columns & specify whether first or second
					GameEngine i=MainFrame.thisFrame.i;
					GameEngine.waitTime=_time;
					MainFrame.thisFrame.setVisible(false);
					MainFrame.thisFrame.start();
					MainFrame.thisFrame.setVisible(true);
					MainFrame.thisFrame.i.setGridLengths(_row, _column);
					MainFrame.thisFrame.i.setTime(_time);
					MainFrame.thisFrame.i.setMyPieceType(type);
					MainFrame.thisFrame.getDisplay().deleteOnly();
					if(type == 1){
						GameEngine.previousMoveTime=System.currentTimeMillis();
						startReading();
					}
					else{
						String red=read();
						Move mo=Move.getMove(red);
						if(mo.getPiece()==0)
							mo.setPiece(3-type);
						GameEngine.otherMakeMove(mo);
						previous=mo;
						startReading();
					}
					System.out.println('r');	
				}		
				else if(_entry.toLowerCase().equals("b")){	//start game allow both with row & columns & specify whether first or second
					GameEngine i=MainFrame.thisFrame.i;
					
					MainFrame.thisFrame.setVisible(false);
					MainFrame.thisFrame.start();
					MainFrame.thisFrame.setVisible(true);
					MainFrame.thisFrame.i.setGridLengths(_row, _column);
					MainFrame.thisFrame.i.setTime(_time);
					MainFrame.thisFrame.i.setMyPieceType(type);
					MainFrame.thisFrame.getDisplay().allowBoth();
					if(type == 1){
						GameEngine.previousMoveTime=System.currentTimeMillis();
						startReading();
					}
					else{
						String red=read();
						Move mo=Move.getMove(red);
						if(mo.getPiece()==0)
							mo.setPiece(3-type);
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
					MainFrame.thisFrame.i.setMyPieceType(type);
					MainFrame.thisFrame.getDisplay().allowNeither();
					if(type == 1){
						GameEngine.previousMoveTime=System.currentTimeMillis();
						startReading();
					}
					else{
						String red=read();
						Move mo=Move.getMove(red);
						if(mo.getPiece()==0)
							mo.setPiece(3-type);
						GameEngine.otherMakeMove(mo);
						previous=mo;
						startReading();
					}
					System.out.println('n');
				}	
			} 
			catch (UnknownHostException e) {System.err.println("Connection UnknownHost Exception: " + e); System.exit(1);} 
			catch(IOException e){System.err.println("Connection IOException: " + e);System.exit(1);}
			}
	
	//reads a move and send a move where ever the player placed a piece
	public void startReading()
	{
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
					mo.setPiece(3-type);
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
	
	public void getMove(){
		String read = read();
		Move m = GameEngine.getPreviousMove();
		m.getMove(read);
		write("Ok");
		write(m.sendMove());
	}
	
	//Reads what was send to the client
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
		catch (UnknownHostException e) {System.err.println("Connection read() UnknownHostException: " + e); System.exit(1);} 
		catch(IOException e){System.err.println("Connection read() IOException: " + e);}
		catch (Exception e){System.err.println("Connection read() Exception Error: " + e);	System.exit(1);}
		return null;
	}
	
	//Closes the connection
	public void closeConnection(){
		try {
			c_socket.close();
		} 
		catch (UnknownHostException e) {System.err.println("Connectoin closeConnection() UnknownHost Exception: " + e); System.exit(1);} 
		catch (IOException e) {e.printStackTrace();}
		catch (Exception e){System.err.println("Connectoin closeConnection() Exception Error: " + e);	System.exit(1);}
	}
	
	public void insert(char _char){
		insert(_char, 0);
	}
	
	public void insert(char _char, int number){
		if(_char == 'f'){
			write(_char + "");
		}
		else if (_char == 'r' || _char == 'd'){
			write(_char + " " + number);
		}
	}
	
	//When we run out of time, we send the following
	public void timeIsUp(){
		outOfTime = GameEngine.timesOut();
		if(outOfTime == true){
			write("OK");
			write("ILLEGAL");
			write("LOSER");
		}
	}
	
	//Send the information to the server 
	public void write(String _string){
		try {	
			OutputStream sockOutput = c_socket.getOutputStream();
			PrintStream m=new PrintStream(sockOutput);
			m.println(_string);	
		} 
		catch (UnknownHostException e) {System.err.println("Connection write() UnknownHost Exception: "+ e); System.exit(1);} 
		catch(IOException e){System.err.println("Connection write() IOException Exception: " + e );}
		catch (Exception e){System.err.println("Connection write() Exception error: " + e);	System.exit(1);}
	}
}
