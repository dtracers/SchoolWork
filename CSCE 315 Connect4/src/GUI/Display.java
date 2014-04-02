package GUI;
/*Display paints all the images used in the main board game background.
 * It also randomly selects a computer image when playing against the AI.
 */


import gameplay.GameEngine;

import java.awt.Color;
import java.awt.Component;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Rectangle;
import java.awt.TextField;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Random;

import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;

import brains.Move;

public class Display extends JPanel implements ActionListener
{
	Graphics myG;
	private Grid gr;
	//Background Images
	Image basicBackground;
	Image computerImage1;
	Image computerImage2;
	Image computerImage3;
	Image computerImage4;
	Image computerImage5;
	Image computerImage6;
	Image client;
	Image server;
	private JLabel prompt;
	private JLabel prompt2;
	private JLabel size;
	private JLabel setSize;
	private JLabel name;
	private JLabel firstName;
	private JLabel secondName;
	//server
	private JLabel serverName;
	private JLabel clientName;
	private JLabel serverFirstName;
	private JLabel clientSecondName;

	public int numberOfPlayers = 0;
	int randomNumber;
	int player2 = 0;
	int player1 = 0;
	int playerOption = 0;
	private boolean[] drawOnce = new boolean[5];
	private TextField inputFieldx;
	private TextField inputFieldy;
	private JButton createButton;
	private JButton flipItButton;
	private JButton deleteButton;
	
	Menu m;
	private JLabel winnerLabel;
	String winner1;
	String winner2;
	private JButton playAgainButton;
	private JButton quitButton;
	
	boolean showWinnerScreen = false;
	boolean updated=true;
	String firstPlayer = "";
	String firstPlayer2 = "";
	double sX,sY;
	int y = 0;

	public Display(double scaleX, double scaleY)
	{
		sX=scaleX;
		sY=scaleY;
		setGrid(new Grid(800,800,6,7,true));
		setLayout(null);
		basicBackground = Toolkit.getDefaultToolkit().getImage("images/basicBackground.png");
		computerImage1 = Toolkit.getDefaultToolkit().getImage("images/childGirl.png");
		computerImage2 = Toolkit.getDefaultToolkit().getImage("images/childBoy.png");
		computerImage3 = Toolkit.getDefaultToolkit().getImage("images/adultGirl.png");
		computerImage4 = Toolkit.getDefaultToolkit().getImage("images/adultBoy.png");
		computerImage5 = Toolkit.getDefaultToolkit().getImage("images/grandmaGirl.png");
		computerImage6 = Toolkit.getDefaultToolkit().getImage("images/grandpaBoy.png");
		client = Toolkit.getDefaultToolkit().getImage("images/client.png");
		server = Toolkit.getDefaultToolkit().getImage("images/server.png"); 
		
		Random generator = new Random();
		randomNumber = generator.nextInt(5);
		setBoardSize();		
	}
	public Display()
	{
		this(1,1);
	}
	
	public void setNumberOfPlayers(int value){
		numberOfPlayers = value;
		setPlayersNames();
	}
	
	public void setValues1(int value){
		player1 = value;
	}
	
	public void setValues2(int value){
		player2 = value;
	}
	
	public void setName1(String name){
		firstPlayer = name;
		if(numberOfPlayers == 1){
			firstName.setText(firstPlayer);
		}
		else if (numberOfPlayers == 2){
			firstName.setText(firstPlayer);
		}
	}
	
	public void setName2(String name){
		firstPlayer2 = name;
		if(numberOfPlayers == 1){
			secondName.setText(firstPlayer2);
		}
		else if(numberOfPlayers == 2){
			secondName.setText(firstPlayer2);
		}
	}
	
	/**
	 * in a jPanel everything in this method that uses g gets shown 
	 * by saving the graphics it is possible to paint to the jPanel from everywhere
	 * a jPanel in a JFrame is doubleBuffered by default
	 */
	public void paint(Graphics g)
	{
		g.setColor(Color.black);
		
		g.drawImage(basicBackground, 0, 0,1100,900, null);
		if(basicBackground.getHeight(null)==-1)
		{
			basicBackground = Toolkit.getDefaultToolkit().getImage("src/GUI/images/basicBackground.png");
		}
		getGrid().draw(g);
		
		setLayout(null);
		if(!drawOnce[0]){
			drawOnce[0]=true;
		    prompt = new JLabel();
		    prompt.setText("Player 1");
		    prompt.setFont(new Font("Courier", Font.BOLD, 40));
		    prompt.setForeground(Color.white);
		    prompt.setBounds(850,65, 400, 200);
			add(prompt);
		}
		//A local player and AI are playing
		if(numberOfPlayers == 1){
			if(!drawOnce[1]){
				drawOnce[1]=true;
			    prompt2 = new JLabel();
			    prompt2.setText("Computer");
			    prompt2.setFont(new Font("Courier", Font.BOLD, 40));
			    prompt2.setForeground(Color.white);
			    prompt2.setBounds(850,375, 400, 200);
				add(prompt2);
			}
				if(player1 == 1){
					
					g.drawImage(computerImage1, 840, 220, 220,220, null);
					if(computerImage1.getWidth( null )==-1)
					{
						computerImage1 = Toolkit.getDefaultToolkit().getImage("src/GUI/images/childGirl.png");
					}
				}
				else if(player1 == 2){
					g.drawImage(computerImage2, 840, 220, 220,220, null);
					if(computerImage2.getWidth( null )==-1)
					{
						computerImage2 = Toolkit.getDefaultToolkit().getImage("src/GUI/images/adultGirl.png");
					}
				}
				else if(player1 == 3){
					g.drawImage(computerImage3, 840, 220, 220,220, null);
					if(computerImage3.getWidth( null )==-1)
					{
						computerImage3 = Toolkit.getDefaultToolkit().getImage("src/GUI/images/grandmaGirl.png");
					}
				}
				else if(player1 == 4){
					g.drawImage(computerImage4, 840, 220, 220,220, null);
					if(computerImage4.getWidth( null )==-1)
					{
						computerImage4 = Toolkit.getDefaultToolkit().getImage("src/GUI/images/childBoy.png");
					}
				}
				else if(player1 == 5){
					g.drawImage(computerImage5, 840, 220, 220,220, null);
					if(computerImage5.getWidth( null )==-1)
					{
						computerImage5 = Toolkit.getDefaultToolkit().getImage("src/GUI/images/adultBoy.png");
					}
				}
				else if(player1 == 6){
					g.drawImage(computerImage6, 840, 220, 220,220, null);
					if(computerImage6.getWidth( null )==-1)
					{
						computerImage6 = Toolkit.getDefaultToolkit().getImage("src/GUI/images/grandpaBoy.png");
					}
				}
			//Randomly chooses an opponent	
			//Computer Image
				if(randomNumber == 0){
					g.drawImage(computerImage1, 840, 525, 220,220, null);
					if(computerImage1.getWidth( null )==-1)
					{
						computerImage1 = Toolkit.getDefaultToolkit().getImage("src/GUI/images/childGirl.png");
					}
				}
				else if(randomNumber == 1){
					g.drawImage(computerImage2, 840, 525, 220,220, null);
					if(computerImage2.getWidth( null )==-1)
					{
						computerImage2 = Toolkit.getDefaultToolkit().getImage("src/GUI/images/childBoy.png");
					}
				}
				else if(randomNumber == 2){
					g.drawImage(computerImage3, 840, 525, 220,220, null);
					if(computerImage3.getWidth( null )==-1)
					{
						computerImage3 = Toolkit.getDefaultToolkit().getImage("src/GUI/images/adultGirl.png");
					}
				}
				else if(randomNumber == 3){
					g.drawImage(computerImage4, 840, 525, 220,220, null);
					if(computerImage4.getWidth( null )==-1)
					{
						computerImage4 = Toolkit.getDefaultToolkit().getImage("src/GUI/images/adultBoy.png");
					}
				}
				else if(randomNumber == 4){
					g.drawImage(computerImage5, 840, 525, 220,220, null);
					if(computerImage5.getWidth( null )==-1)
					{
						computerImage5 = Toolkit.getDefaultToolkit().getImage("src/GUI/images/grandmaGirl.png");
					}
				}
				else if(randomNumber == 5){
					g.drawImage(computerImage6, 840, 525, 220,220, null);
					if(computerImage6.getWidth( null )==-1)
					{
						computerImage6 = Toolkit.getDefaultToolkit().getImage("src/GUI/images/grandpaBoy.png");
					}
				}
		}
		//2 local players are playing
		else if(numberOfPlayers == 2){
			if(!drawOnce[1]){
				drawOnce[1]=true;
			    prompt2 = new JLabel();
			    prompt2.setText("Player 2");
			    prompt2.setFont(new Font("Courier", Font.BOLD, 40));
			    prompt2.setForeground(Color.white);
			    prompt2.setBounds(850,370, 400, 200);
				add(prompt2);
			}
			
			// Player 1

			if(player1 == 1){
				g.drawImage(computerImage1, 840, 220, 220,220, null);
				if(computerImage1.getWidth( null )==-1)
				{
					computerImage1 = Toolkit.getDefaultToolkit().getImage("src/GUI/images/childGirl.png");
				}
			}
			else if(player1 == 2){
				g.drawImage(computerImage2, 840, 220, 220,220, null);
				if(computerImage2.getWidth( null )==-1)
				{
					computerImage2 = Toolkit.getDefaultToolkit().getImage("src/GUI/images/adultGirl.png");
				}
			}
			else if(player1 == 3){
				g.drawImage(computerImage3, 840, 220, 220,220, null);
				if(computerImage3.getWidth( null )==-1)
				{
					computerImage3 = Toolkit.getDefaultToolkit().getImage("src/GUI/images/grandmaGirl.png");
				}
			}
			else if(player1 == 4){
				g.drawImage(computerImage4, 840, 220, 220,220, null);
				if(computerImage4.getWidth( null )==-1)
				{
					computerImage4 = Toolkit.getDefaultToolkit().getImage("src/GUI/images/childBoy.png");
				}
			}
			else if(player1 == 5){
				g.drawImage(computerImage5, 840, 220, 220,220, null);
				if(computerImage5.getWidth( null )==-1)
				{
					computerImage5 = Toolkit.getDefaultToolkit().getImage("src/GUI/images/adultBoy.png");
				}
			}
			else if(player1 == 6){
				g.drawImage(computerImage6, 840, 220, 220,220, null);
				if(computerImage6.getWidth( null )==-1)
				{
					computerImage6 = Toolkit.getDefaultToolkit().getImage("src/GUI/images/grandpaBoy.png");
				}
			}
			
			// *************************************************************************************************
			//Player 2

				if(player2 == 1){
					g.drawImage(computerImage1, 840, 525, 220,220, null);
					if(computerImage1.getWidth( null )==-1)
					{
						computerImage1 = Toolkit.getDefaultToolkit().getImage("src/GUI/images/childGirl.png");
					}
				}
				else if(player2 == 2){
					g.drawImage(computerImage2, 840, 525, 220,220, null);
					if(computerImage2.getWidth( null )==-1)
					{
						computerImage2 = Toolkit.getDefaultToolkit().getImage("src/GUI/images/adultGirl.png");
					}
				}
				else if(player2 == 3){
					g.drawImage(computerImage3, 840, 525, 220,220, null);
					if(computerImage3.getWidth( null )==-1)
					{
						computerImage3 = Toolkit.getDefaultToolkit().getImage("src/GUI/images/grandmaGirl.png");
					}
				}
				else if(player2 == 4){
					g.drawImage(computerImage4, 840, 525, 220,220, null);
					if(computerImage4.getWidth( null )==-1)
					{
						computerImage4 = Toolkit.getDefaultToolkit().getImage("src/GUI/images/childBoy.png");
					}
				}
				else if(player2 == 5){
					g.drawImage(computerImage5, 840, 525, 220,220, null);
					if(computerImage5.getWidth( null )==-1)
					{
						computerImage5 = Toolkit.getDefaultToolkit().getImage("src/GUI/images/adultBoy.png");
					}
				}
				else if(player2 == 6){
					g.drawImage(computerImage6, 840, 525, 220,220, null);
					if(computerImage6.getWidth( null )==-1)
					{
						computerImage6 = Toolkit.getDefaultToolkit().getImage("src/GUI/images/grandpaBoy.png");
					}
				}
		}
		//We're running a client/server game
		else if(numberOfPlayers ==3){
		    prompt2 = new JLabel();
		    prompt2.setText("Player 2");
		    prompt2.setFont(new Font("Courier", Font.BOLD, 40));
		    prompt2.setForeground(Color.white);
		    prompt2.setBounds(850,370, 400, 200);
			add(prompt2);
			g.drawImage(server, 840, 220, 220,220, null);
			if(server.getWidth( null )==-1)
			{
				server = Toolkit.getDefaultToolkit().getImage("src/GUI/images/server.png");
			}
			
			g.drawImage(client, 840, 525, 220,220, null);
			if(client.getWidth( null )==-1)
			{
				client = Toolkit.getDefaultToolkit().getImage("src/GUI/images/client.png");
			}
		}
	super.paintComponents(g);
	}
	
	public void setBoardSize(){
		Font font1 = new Font("SansSerif", Font.PLAIN, 40);
		if(!drawOnce[2]){
			drawOnce[2]=true;
		    setSize = new JLabel();
		    setSize.setText("Set Board size: ");
		    setSize.setFont(new Font("Courier", Font.BOLD, 30));
		    setSize.setForeground(Color.black);
		    setSize.setBounds(10, 805, 288, 50);
			add(setSize);	
			
			inputFieldx = new TextField();
			inputFieldx.setBounds(350, 915, 100, 50);
			inputFieldx.setFont(font1);
			Resize(inputFieldx);
			add(inputFieldx);	 	
			
		    size = new JLabel();
		    size.setText("by");
		    size.setFont(new Font("Courier", Font.BOLD, 30));
		    size.setForeground(Color.black);
		    size.setBounds(407, 805, 40, 50);
			add(size);
			
			inputFieldy = new TextField(); 
			inputFieldy.setBounds(550, 915, 100, 50);
			inputFieldy.setFont(font1);
			Resize(inputFieldy);
			add(inputFieldy); 
				
			createButton = new MyJButton("Create"); 
			createButton.setBounds(570,800, 200, 50);
			createButton.setFont(new Font("Courier", Font.PLAIN, 25));
			createButton.setBackground(Color.orange);
			add(createButton); 	
			
			flipItButton = new MyJButton("Flip it"); 
			flipItButton.setBounds(800,750, 150, 100);
			flipItButton.setFont(new Font("Courier", Font.PLAIN, 20));
			flipItButton.setBackground(Color.green);
			add(flipItButton); 

			deleteButton = new MyJButton("Remove it"); 
			deleteButton.setBounds(950,750,145, 100);
			deleteButton.setFont(new Font("Courier", Font.PLAIN, 20));
			deleteButton.setBackground(Color.green);
			add(deleteButton); 
			setVisible(true); 
		}	
		createButton.addActionListener(this);
		flipItButton.addActionListener(this);
		deleteButton.addActionListener(this);
	}
	
	//Only show the Flip button
	public void flipsOnly(){
		setSize.setVisible(false);
		size.setVisible(false);
		inputFieldx.setVisible(false);
		inputFieldy.setVisible(false);
		createButton.setVisible(false);
		deleteButton.setVisible(false);
	}
	
	//Only show the delete button
	public void deleteOnly(){
		setSize.setVisible(false);
		size.setVisible(false);
		inputFieldx.setVisible(false);
		inputFieldy.setVisible(false);
		createButton.setVisible(false);
		flipItButton.setVisible(false);
		deleteButton.setVisible(true);
	}
	
	//Show both the flip and delete button
	public void allowBoth(){
		setSize.setVisible(false);
		size.setVisible(false);
		inputFieldx.setVisible(false);
		inputFieldy.setVisible(false);
		createButton.setVisible(false);
		flipItButton.setVisible(true);
		deleteButton.setVisible(true);
	}
	
	//Don't show the flip and delete button
	public void allowNeither(){
		//numberOfPlayers = 3;
		setSize.setVisible(false);
		size.setVisible(false);
		inputFieldx.setVisible(false);
		inputFieldy.setVisible(false);
		createButton.setVisible(false);
		flipItButton.setVisible(false);
		deleteButton.setVisible(false);
	}
	
	public void updated()
	{
		updated=true;
		getGrid().updated();
	}
	
	//Sets up the players information depending on the numberOfPlayers
	public void setPlayersNames(){
			if(numberOfPlayers == 1){
				if(!drawOnce[3]){
					drawOnce[3]=true;
					name = new JLabel();
					name.setText("Name:");
					name.setFont(new Font("Courier", Font.BOLD, 27));
					name.setForeground(Color.white);
					name.setBounds(810, 145, 100, 100);
					add(name);
					
					firstName = new JLabel();
					firstName.setFont(new Font("Courier", Font.BOLD, 27));
					firstName.setForeground(Color.white);
					firstName.setBounds(885, 145, 100, 100);
					firstName.setVisible(true);
					add(firstName);
				}
			}
			else if(numberOfPlayers == 2){
				System.out.println("***********************************************");
				if(!drawOnce[3]){
					drawOnce[3]=true;
					//Player 1's information
					name = new JLabel();
					name.setText("Name:");
					name.setFont(new Font("Courier", Font.BOLD, 27));
					name.setForeground(Color.white);
					name.setBounds(810, 145, 100, 100);
					add(name);
					
					firstName = new JLabel();
					firstName.setFont(new Font("Courier", Font.BOLD, 27));
					firstName.setForeground(Color.white);
					firstName.setBounds(885, 145, 100, 100);

					add(firstName);
					//Players 2 Information
					name = new JLabel();
					name.setText("Name:");
					name.setFont(new Font("Courier", Font.BOLD, 27));
					name.setForeground(Color.white);
					name.setBounds(810, 445, 100, 100);
					add(name);
									
					secondName = new JLabel();
					secondName.setFont(new Font("Courier", Font.BOLD, 27));
					secondName.setForeground(Color.white);
					secondName.setBounds(885, 445, 100, 100);

					add(secondName);
					}
				}
				else if(numberOfPlayers == 3){
					System.out.println("*Number 3*");
					if(!drawOnce[3]){
						drawOnce[3]=true;
						
						//Player 1's information
						serverName = new JLabel();
						serverName.setText("Name:");
						serverName.setFont(new Font("Courier", Font.BOLD, 27));
						serverName.setForeground(Color.white);
						serverName.setBounds(810, 145, 100, 100);
						add(serverName);
						
						serverFirstName = new JLabel();
						serverFirstName.setFont(new Font("Courier", Font.BOLD, 27));
						serverFirstName.setForeground(Color.white);
						serverFirstName.setBounds(885, 145, 100, 100);
						serverFirstName.setText("Server");
						add(serverFirstName);
						//Players 2 Information
						clientName = new JLabel();
						clientName.setText("Name:");
						clientName.setFont(new Font("Courier", Font.BOLD, 27));
						clientName.setForeground(Color.white);
						clientName.setBounds(810, 445, 100, 100);
						add(clientName);
										
						clientSecondName = new JLabel();
						clientSecondName.setFont(new Font("Courier", Font.BOLD, 27));
						clientSecondName.setForeground(Color.white);
						clientSecondName.setText("Client");
						clientSecondName.setBounds(885, 445, 100, 100);
						add(clientSecondName);
			} 
		}	
	}
	
	public void actionPerformed(ActionEvent arg0)
	{
		String command=arg0.getActionCommand();
		
		if(command.equals("Create"))
		{	
			int x = Integer.parseInt(inputFieldx.getText());
			int y = Integer.parseInt(inputFieldy.getText());
			changeDimensions(800,800,x,y,true);
		}
		
		if(command.equals("Flip it"))
		{
			System.out.println("Flip Board here");
			//Flip board
			GameEngine.makeMove(new Move(0,0,-1,GameEngine.getTurnCounter()));
		}
		
		if(command.equals("Remove it"))
		{
			GameEngine.removePiece(true);
		}
		//This will start the game
		if(command.equals("Play Again"))
		{
			MainFrame.thisFrame.start();
		}
		
		if(command.equals("Quit"))
		{
			System.exit(-1);
		}
	}

	public Grid getGrid()
	{
		return gr;
	}
	public void changeDimensions(int totalWidth,int totalHeight,int boxWidth,int boxHeight,boolean rows)
	{
		GameEngine.resetBoard();
		getGrid().resize(totalWidth, totalHeight, boxWidth, boxHeight, rows);
	}
	public void setGrid(Grid gr)
	{
		this.gr = gr;
	}
	public Rectangle scale(Rectangle r)
	{
		return new Rectangle((int)(r.getX()*sX),(int)(r.getY()*sY),(int)(r.getWidth()*sX),(int)(r.getHeight()*sY));
	}
	public void Resize(JComponent j)
	{
		j.setBounds(scale(j.getBounds()));
	}
	public void Resize(Component j)
	{
		j.setBounds(scale(j.getBounds()));
	}
}
