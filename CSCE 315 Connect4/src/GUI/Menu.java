package GUI;
/*This file contains all the functions and calls that are used in our menu. Here, you can view
 * all the main buttons and see all the images.
 */

import gameplay.GameEngine;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Rectangle;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.net.UnknownHostException;

import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JTextField;

import main.connection;
import main.server;

class Menu extends MyButtonPanel implements ActionListener {
    private static final int PLAYER_BUTTON_WIDTH = 220;
    private static final int PLAYER_BUTTON_HEIGHT = 220;
    private static final int BUTTON_HEIGHT = 100;
    private static final int BUTTON_WIDTH = 300;
    private static final int FRAME_WIDTH = 1280;
    private static final int FRAME_HEIGHT = 1024;
	
    private static final int STARTING_BUTTON_lEFT_RIGHT= 425;
    private static final int STARTING_BUTTON_UP_DOWN = 750;
    private static final int MENU_BUTTON_WIDTH = 600;
    private static final int MENU_BUTTON_HEIGHT = 150;
    private static final int STARTING_HEIGHT = 250;
    
    private Image backgroundImage = null;
    int playerOption = 0;
    int numberOfPlayers = 0;
	
	private JButton startButton;
	private MyJButton playerButton;
	private MyJButton computerButton;
	private MyJButton instructionButton;
	private MyJButton girlButton;
	private MyJButton womanButton;
	private MyJButton grandmaButton;
	private MyJButton boyButton;
	private MyJButton menButton;
	private MyJButton grandpaButton;
	private MyJButton backButton;
	private MyJButton playButton;
	private MyJButton nextButton;
	private MyJButton localButton;
	private MyJButton networkButton;
	private MyJButton createButton;
	private MyJButton joinButton;
	
	private JLabel prompt;
	private JLabel changePlayer;
	//Player names fields
	private JTextField playerName1;
	private JTextField playerName2;	
	//Client server fields
	private JTextField joinNetwork;
	private JTextField joinNameNetwork;
	private JTextField createNetwork;
	private JLabel createNameNetwork;
	//Specifying game board fields
	private JTextField numberOfColumns;
	private JTextField numberOfRows;
	private JTextField firstOrSecond;
	private JTextField timeLimit;
	private JTextField entryRule;
	
	private int playerNumber1 = 0; 
	private int playerNumber2 = 0;
	
	private int numberPlayers = 0;
	
	String namePlayer1 = "";
	String namePlayer2 = "";
	//Specifying network fields
	int createNetworkNumber;
	String createNetworkName;
	int joinNetworkNumber;
	String joinNetworkName;
	
	//Client Server
	String sendMove = "";

	//Default game specifications
	int columnNum = 6;
	int rowNum = 7;
	String moveFS = "s";
	int timePerMove = 0;
	String gameRule = "b";
	
	Color coolOrange = new Color(242, 161, 33);
	Color connectBlue = new Color(0, 128, 255);
	
	Image backgroundImageStart = this.loadImage("images/startScreen.png");
	Image backgroundImageOptions = this.loadImage("images/menu.png");
	Image backgroundImageInstructions = this.loadImage("images/instructionsScreen.png");
	Image backgroundImagePlayer1 = this.loadImage("images/player1.png");
	Image backgroundImagePlayer2 = this.loadImage("images/player2.png");
	Image backgroundImagePort= this.loadImage("images/portMenu.png");
	Image backgroundImageSpecifyGame = this.loadImage("images/specifyGame.png");
	double sX,sY;
	Font font1 = new Font("SansSerif", Font.PLAIN, 40);
	
	public Menu(){
		this(1,1,FRAME_WIDTH, FRAME_HEIGHT);
	}	
	public Rectangle scale(Rectangle r)
	{
		return new Rectangle((int)(r.getX()*sX),(int)(r.getY()*sY),(int)(r.getWidth()*sX),(int)(r.getHeight()*sY));
	}
	public Menu(double scaleX, double scaleY,int width,int height)
	{
		sX=scaleX;
		sY=scaleY;
		System.out.println("this far "+width+" h "+height);
		setSize (width,height);
		setLayout(null);
		
		this.backgroundImage = backgroundImageStart;

		startButton = new JButton("New Game");
		startButton.setFont(new Font("Courier", Font.BOLD, 50));
		startButton.setBackground(coolOrange);
		startButton.setBounds(400, 750, BUTTON_WIDTH, BUTTON_HEIGHT);
		add(startButton);
		startButton.addActionListener(this);
	}

	private Image loadImage (String pad){
        return Toolkit.getDefaultToolkit().getImage(getClass().getResource(pad));
    }

	//The main menu page that has 3 options to chose from 
	public void optionMenu(){
		this.removeAllButtons();
		this.backgroundImage = backgroundImageOptions;
		
		instructionButton = new MyJButton("images/instructions.png",STARTING_HEIGHT, 90, MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT);
		instructionButton.setAction("instructions", this.getClass(),this);
		addMyButton(instructionButton,false);
		
		localButton = new MyJButton("images/localButton.png",STARTING_HEIGHT, 242, MENU_BUTTON_WIDTH, 260);
		localButton.setAction("playLocal", this.getClass(),this);
		addMyButton(localButton,false);
		
		networkButton = new MyJButton("images/networkButton.png",STARTING_HEIGHT, 504, MENU_BUTTON_WIDTH, 260);
		networkButton.setAction("serverClient", this.getClass(),this);
		addMyButton(networkButton,false);
			
		this.addMouseListener(instructionButton);
		this.addMouseListener(localButton);
		this.addMouseListener(networkButton);
		
		System.out.println("BUTTON!!!");
		return;
	}
	
	//Let's you decide whether you want to play against an AI or not
	public void playLocal(){
		this.removeAllButtons();
		this.backgroundImage = backgroundImageOptions;
		
		playerButton = new MyJButton("images/playerVsPlayer.png",STARTING_HEIGHT, 242, MENU_BUTTON_WIDTH, 260);
		playerButton.setAction("playerVsPlayer", this.getClass(),this);
		addMyButton(playerButton,false);
		
		computerButton = new MyJButton("images/playerVsComputer.png",STARTING_HEIGHT, 504, MENU_BUTTON_WIDTH, 260);
		computerButton.setAction("playerVsComputer", this.getClass(),this);
		addMyButton(computerButton,false);
		
		this.addMouseListener(playerButton);
		this.addMouseListener(computerButton);
	}
	
	//GUI for creating a server or client
	public void playNetwork(){
		this.removeAllButtons();
		this.backgroundImage = backgroundImagePort;
		
		numberOfPlayers = 3;
		
		createButton = new MyJButton("images/createPort.png",140, 700, 249, 100);
		createButton.setAction("specifyGame", this.getClass(),this);
		addMyButton(createButton,false);
		
		createNameNetwork = new JLabel();
		createNameNetwork.setFont(new Font("Courier", Font.BOLD, 20));
		createNameNetwork.setBounds(80,475, 600, 50);
		
		createNetwork = new JTextField();
		createNetwork.setColumns(25);
		createNetwork.setBounds(100,625, 300, 50);
		createNetwork.setFont(font1);
				
		try {
			java.net.InetAddress addr;
			addr = java.net.InetAddress.getLocalHost();
		    String hostname = addr.getHostName();     
		    System.out.println("Hostname = " + hostname); 
		    createNameNetwork.setText(hostname);
		} catch (UnknownHostException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}     
		
		joinButton = new MyJButton("images/joinPort.png",750, 700, 249, 100);
		joinButton.setAction("client", this.getClass(),this);
		addMyButton(joinButton,false);
		
		joinNameNetwork = new JTextField();
		joinNameNetwork.setColumns(25);
		joinNameNetwork.setBounds(700,475, 300, 50);
		joinNameNetwork.setFont(font1);
		
		joinNetwork = new JTextField();
		joinNetwork.setColumns(25);
		joinNetwork.setBounds(700,625, 300, 50);
		joinNetwork.setFont(font1);
		
		add(createNetwork);
		add(createNameNetwork);
		add(joinNetwork);
		add(joinNameNetwork);
		this.addMouseListener(createButton);
		this.addMouseListener(joinButton);
	}
	
	//Determines the game specifications
	public void specifyGame(){
		this.removeAll();
		this.removeAllButtons();
		this.backgroundImage = backgroundImageSpecifyGame;
		
		numberOfColumns = new JTextField();
		numberOfColumns.setColumns(25);
		numberOfColumns.setBounds(300,200, 300, 50);
		numberOfColumns.setFont(font1);
		
		numberOfRows = new JTextField();
		numberOfRows.setColumns(25);
		numberOfRows.setBounds(300,300, 300, 50);
		numberOfRows.setFont(font1);
		
		firstOrSecond = new JTextField();
		firstOrSecond.setColumns(25);
		firstOrSecond.setBounds(300,390, 300, 50);
		firstOrSecond.setFont(font1);
		
		timeLimit = new JTextField();
		timeLimit.setColumns(25);
		timeLimit.setBounds(300,480, 300, 50);
		timeLimit.setFont(font1);
		
		entryRule = new JTextField();
		entryRule.setColumns(25);
		entryRule.setBounds(300,700, 300, 50);
		entryRule.setFont(font1);
		
		joinButton = new MyJButton("images/play.png",950, 870, 300, 100);
		joinButton.setAction("serverClass", this.getClass(),this);
		joinButton.resize(sX, sY);
		addMyButton(joinButton,false);
		
		add(numberOfColumns);
		add(numberOfRows);
		add(firstOrSecond);
		add(timeLimit);
		add(entryRule);
		this.addMouseListener(joinButton);
		
		setNetworkInformation();
		
	}
	
	public void readingMoves(String _move){
		sendMove = _move;
	}
	
	public String sendReadingMoves(){
		return sendMove;
	}
	
	//Creates a server
	public void serverClass(){
		setGameBoardInformation();

		ServerThread t=new ServerThread(this);
		t.start();
	}
	
	//Creates a client
	public void client(){
		setJoinNetwork();
		ClientThread t=new ClientThread(this);
		t.start();
	}
	
	public void setNetworkInformation(){
		//Stores the server's information
		createNetworkNumber = Integer.parseInt(createNetwork.getText());
		System.out.println("createNetworkNumber: '" + createNetworkNumber + "'");
	}
	
	public void setJoinNetwork(){
		//Stores the clients information
		joinNetworkNumber = Integer.parseInt(joinNetwork.getText());
		System.out.println("JoinNetworkNumebr: '" + joinNetworkNumber + "'");
		joinNetworkName = joinNameNetwork.getText();
		System.out.println("JoinNetworkName: '" + joinNetworkName + "'");
	}
	
	public void setGameBoardInformation(){
		//Set board information
		columnNum = Integer.parseInt(numberOfColumns.getText());
		System.out.println("ColumnNumber: " + columnNum);
		rowNum = Integer.parseInt(numberOfRows.getText());
		System.out.println("rowNum: " + rowNum);
		moveFS = firstOrSecond.getText();
		System.out.println("moveFS: " + moveFS);
		timePerMove = Integer.parseInt(timeLimit.getText());
		System.out.println("timePerMove: " + timePerMove);
		gameRule = entryRule.getText();
		System.out.println("gameRule: " + gameRule);
	}
	
	public int setColumns(){
		int setColumns = columnNum;
		return setColumns;
	}
	
	public int setRows(){
		int setRows = rowNum;
		return setRows;
	}
	
	public String setMove(){
		String setMove = moveFS;
		return setMove;
	}
	
	public int setTime(){
		int setTime = timePerMove;
		return setTime;
	}
	
	public String setRule(){
		String setRule = gameRule;
		return setRule;
	}
	//Sets the players names
	public String getName1(){
		String newName = namePlayer1;
		System.out.println("namePlayer 1 : " + namePlayer1);
		return newName;
	}
	
	public String getName2(){
		String newName = namePlayer2;
		System.out.println("namePlayer 2 : " +namePlayer2);
		return newName;
	}
	
	//This isn't starting the game
	public void startGame(){
		if(numberOfPlayers == 1){
		namePlayer1 = playerName1.getText();
		System.out.println(namePlayer1);
		}
		else if(numberOfPlayers == 2){
			namePlayer1 = playerName1.getText();
			System.out.println(namePlayer1);
			namePlayer2 = playerName2.getText();
			System.out.println(namePlayer2);
		}
		else if(numberOfPlayers == 3){
			System.out.println("ana");
		}
		MainFrame.thisFrame.start();
	}
	
	public void playerVsComputer(){
		numberOfPlayers = 1;
		playerOption1();
	}
	
	public void playerVsPlayer(){
		numberOfPlayers = 2;
		playerOption1();
	}
	
	public void serverClient(){
		numberOfPlayers = 3;
		playNetwork();
	}
	
	public int setPlayerValues(){
		if(numberOfPlayers == 1){
			numberPlayers = 1;
		}
		else if (numberOfPlayers ==2){
			numberPlayers = 2;
		}
		else if(numberOfPlayers == 3){
			numberPlayers = 3;
		}
		return numberPlayers;
	}
	
	//The player has 6 images to chose from 
	public void playerOption1(){
//Background image is called "player1.png" 
		this.removeAllButtons();
		this.backgroundImage = backgroundImagePlayer1;		
		
		girlButton = new MyJButton("images/childGirl.png", 200, 275, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
		girlButton.setAction("player1Number1", this.getClass(),this);
		addMyButton(girlButton,false);
		
		womanButton = new MyJButton("images/adultGirl.png", 420,275, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
		womanButton.setAction("player1Number2", this.getClass(),this);
		addMyButton(womanButton,false);
		
		grandmaButton = new MyJButton("images/grandmaGirl.png", 640,275, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
		grandmaButton.setAction("player1Number3", this.getClass(),this);
		addMyButton(grandmaButton,false);
		
		boyButton = new MyJButton("images/childBoy.png", 200,495, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
		boyButton.setAction("player1Number4", this.getClass(),this);
		addMyButton(boyButton,false);
		
		menButton = new MyJButton("images/adultBoy.png", 420,495, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
		menButton.setAction("player1Number5", this.getClass(),this);
		addMyButton(menButton,false);

		grandpaButton = new MyJButton("images/grandpaBoy.png", 640,495, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
		grandpaButton.setAction("player1Number6", this.getClass(),this);
		addMyButton(grandpaButton,false);	
		
		this.addMouseListener(girlButton);
		this.addMouseListener(womanButton);
		this.addMouseListener(grandmaButton);
		this.addMouseListener(boyButton);
		this.addMouseListener(menButton);
		this.addMouseListener(grandpaButton);

		return;
	}
	
	public void player1Number1(){
		playerOption = 1;
		player1();
	}
	
	public void player1Number2(){
		playerOption = 2;
		player1();
	}
	
	public void player1Number3(){
		playerOption = 3;
		player1();
	}
	
	public void player1Number4(){
		playerOption = 4;
		player1();
	}
	
	public void player1Number5(){
		playerOption = 5;
		player1();
	}
	
	public void player1Number6(){
		playerOption = 6;
		player1();
	}
	
	//The player has 6 images to chose from 
	public void playerOption2(){
//Background image is called "player2.png"
		this.removeAllButtons();
		this.removeAll();
		this.backgroundImage = backgroundImagePlayer2;		
		
		girlButton = new MyJButton("images/childGirl.png", 200, 275, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
		girlButton.setAction("player2Number1", this.getClass(),this);
		addMyButton(girlButton,false);
		
		womanButton = new MyJButton("images/adultGirl.png", 420,275, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
		womanButton.setAction("player2Number2", this.getClass(),this);
		addMyButton(womanButton,false);
		
		grandmaButton = new MyJButton("images/grandmaGirl.png", 640,275, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
		grandmaButton.setAction("player2Number3", this.getClass(),this);
		addMyButton(grandmaButton,false);
		
		boyButton = new MyJButton("images/childBoy.png", 200,495, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
		boyButton.setAction("player2Number4", this.getClass(),this);
		addMyButton(boyButton,false);
		
		menButton = new MyJButton("images/adultBoy.png", 420,495, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
		menButton.setAction("player2Number5", this.getClass(),this);
		addMyButton(menButton,false);

		grandpaButton = new MyJButton("images/grandpaBoy.png", 640,495, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
		grandpaButton.setAction("player2Number6", this.getClass(),this);
		addMyButton(grandpaButton,false);	
		
		this.addMouseListener(girlButton);
		this.addMouseListener(womanButton);
		this.addMouseListener(grandmaButton);
		this.addMouseListener(boyButton);
		this.addMouseListener(menButton);
		this.addMouseListener(grandpaButton);

		return;
	}
	
	public void player2Number1(){
		playerOption = 1;
		player2();
	}
	
	public void player2Number2(){
		playerOption = 2;
		player2();
	}
	
	public void player2Number3(){
		playerOption = 3;
		player2();
	}
	
	public void player2Number4(){
		playerOption = 4;
		player2();
	}
	
	public void player2Number5(){
		playerOption = 5;
		player2();
	}
	
	public void player2Number6(){
		playerOption = 6;
		player2();
	}
	
	//Displays the instructions page
	public void instructions(){
		this.removeAllButtons();
		this.backgroundImage = backgroundImageInstructions;		
		
		backButton = new MyJButton("images/back.png",
				STARTING_BUTTON_lEFT_RIGHT, STARTING_BUTTON_UP_DOWN, BUTTON_WIDTH, BUTTON_HEIGHT);//copied from set bounds
		//backButton.resize(sX, sY);
		addMyButton(backButton,false);
		backButton.setAction("optionMenu", this.getClass(), this);
		
		this.addMouseListener(backButton);
		
		return;
	}
	
	//Store the players image and name
	public void player1(){
// Background image is called "menu.png"
		this.removeAllButtons();
		this.backgroundImage = backgroundImageOptions;
		Font font1 = new Font("SansSerif", Font.PLAIN, 40);
		
		System.out.println(numberOfPlayers);

		//This will decide on depending on which player they chose, it will save it
		if(playerOption == 1){	
			playerNumber1 = 1;
			//image is called "childGirl.png"
			girlButton = new MyJButton("images/childGirl.png", 450, 200, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
			girlButton.setAction("playerOption1", this.getClass(),this);
			addMyButton(girlButton,false);	
			this.addMouseListener(girlButton);
		}
		else if (playerOption == 2){
			//image is called "adultGirl.png"
			playerNumber1 = 2;
			womanButton = new MyJButton("images/adultGirl.png", 450, 200, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
			womanButton.setAction("playerOption1", this.getClass(),this);
			addMyButton(womanButton,false);	
			this.addMouseListener(womanButton);		
		}
		else if (playerOption == 3){
			playerNumber1 = 3;
			//image is called "grandmaGirl.png"
			grandmaButton = new MyJButton("images/grandmaGirl.png", 450, 200, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
			grandmaButton.setAction("playerOption1", this.getClass(),this);
			addMyButton(grandmaButton,false);	
			this.addMouseListener(grandmaButton);	
		}
		else if (playerOption == 4){	
			playerNumber1 = 4;
			//image is called "childBoy.png"
			boyButton = new MyJButton("images/childBoy.png", 450, 200, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
			boyButton.setAction("playerOption1", this.getClass(),this);
			addMyButton(boyButton,false);	
			this.addMouseListener(boyButton);	
		}
		else if (playerOption == 5){	
			playerNumber1 = 5;
			//image is called "adultBoy.png"
			menButton = new MyJButton("images/adultBoy.png", 450, 200, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
			menButton.setAction("playerOption1", this.getClass(),this);
			addMyButton(menButton,false);	
			this.addMouseListener(menButton);	
		}
		else if (playerOption == 6){
			playerNumber1 = 6;
			//image is called "grandpaBoy.png"
			grandpaButton = new MyJButton("images/grandpaBoy.png", 450, 200, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
			grandpaButton.setAction("playerOption1", this.getClass(),this);
			addMyButton(grandpaButton,false);	
			this.addMouseListener(grandpaButton);
		}
		
		changePlayer = new JLabel();
		changePlayer.setText("To change your player, click on it");
		changePlayer.setFont(new Font("Courier", Font.ITALIC, 18));
		changePlayer.setBounds(400,85, 400, 200);
		
	    prompt = new JLabel();
	    prompt.setText("Please enter Player 1's name.\n");
	    prompt.setFont(new Font("Courier", Font.BOLD, 20));
	    prompt.setBounds(400,350, 400, 200);

		playerName1 = new JTextField();
		playerName1.setColumns(25);
	    playerName1.setBounds(420,480, 300, 50);
	    playerName1.setFont(font1);

	    add(prompt);
		add(playerName1);
		add(changePlayer);
		
	    playerName1.addActionListener(this);

	   System.out.println(numberOfPlayers);
	    if(numberOfPlayers == 1){
	    	playButton = new MyJButton("images/play.png", STARTING_BUTTON_lEFT_RIGHT, 580, BUTTON_WIDTH, BUTTON_HEIGHT);
	    	playButton.setAction("startGame", this.getClass(),this);
	    	addMyButton(playButton,false);
			this.addMouseListener(playButton);
	    }
	    //If they choose to play against another player then a next button appears
	    else if(numberOfPlayers == 2) {
	    	nextButton = new MyJButton("images/next.png", STARTING_BUTTON_lEFT_RIGHT, 580, BUTTON_WIDTH, BUTTON_HEIGHT);
	    	nextButton.setAction("playerOption2", this.getClass(),this);
	    	addMyButton(nextButton,false);
			this.addMouseListener(nextButton);
	    }
	    
	    setVisible(true);
	    return;
	}

	//Store the players image and name
	public void player2(){		
// Background image is called "menu.png"	
		this.removeAllButtons();
		this.backgroundImage = backgroundImageOptions;		
		Font font1 = new Font("SansSerif", Font.PLAIN, 40);
		
		//This will decide on depending on which player they chose, it will save it
		if(playerOption == 1){	
			playerNumber2 = 1;
			//image is called "childGirl.png"
			girlButton = new MyJButton("images/childGirl.png", 450, 200, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
			girlButton.setAction("playerOption2", this.getClass(),this);
			addMyButton(girlButton,false);	
			this.addMouseListener(girlButton);
		}
		else if (playerOption == 2){
			//image is called "adultGirl.png"
			playerNumber2 = 2;
			womanButton = new MyJButton("images/adultGirl.png", 450, 200, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
			womanButton.setAction("playerOption2", this.getClass(),this);
			addMyButton(womanButton,false);	
			this.addMouseListener(womanButton);	
		}
		else if (playerOption == 3){
			//image is called "grandmaGirl.png"
			playerNumber2 = 3;
			grandmaButton = new MyJButton("images/grandmaGirl.png", 450, 200, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
			grandmaButton.setAction("playerOption2", this.getClass(),this);
			addMyButton(grandmaButton,false);	
			this.addMouseListener(grandmaButton);	
		}
		else if (playerOption == 4){	
			//image is called "childBoy.png"
			playerNumber2 = 4;
			boyButton = new MyJButton("images/childBoy.png", 450, 200, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
			boyButton.setAction("playerOption2", this.getClass(),this);
			addMyButton(boyButton,false);	
			this.addMouseListener(boyButton);	
		}
		else if (playerOption == 5){	
			//image is called "adultBoy.png"
			playerNumber2 = 5;
			menButton = new MyJButton("images/adultBoy.png", 450, 200, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
			menButton.setAction("playerOption2", this.getClass(),this);
			addMyButton(menButton,false);	
			this.addMouseListener(menButton);
		}
		else if (playerOption == 6){
			//image is called "grandpaBoy.png"
			playerNumber2 = 6;
			grandpaButton = new MyJButton("images/grandpaBoy.png", 450, 200, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
			grandpaButton.setAction("playerOption2", this.getClass(),this);
			addMyButton(grandpaButton,false);	
			this.addMouseListener(grandpaButton);
		}
		
		changePlayer = new JLabel();
		changePlayer.setText("To change your player, click on it");
		changePlayer.setFont(new Font("Courier", Font.ITALIC, 18));
		changePlayer.setBounds(400,85, 400, 200);

	    playerName2 = new JTextField();
	    playerName2.setColumns(25);
	    playerName2.setBounds(400,480, 300, 50);
	    playerName2.setFont(font1);
	    
	    prompt = new JLabel();
	    prompt.setText("Please enter Player 2's name.\n");
	    prompt.setFont(new Font("Courier", Font.BOLD, 20));
	    prompt.setBounds(420,350, 400, 200);
	   
    	playButton = new MyJButton("images/play.png", STARTING_BUTTON_lEFT_RIGHT, 580, BUTTON_WIDTH, BUTTON_HEIGHT);
    	playButton.setAction("startGame", this.getClass(),this);
    	addMyButton(playButton,false);
	    
		add(changePlayer);
	    add(prompt);
	    add(playerName2);
	    setVisible(true);
	        
	    this.addMouseListener(playButton);
	    playerName2.addActionListener(this);
	}
	
	//Stores the image that the player selected
	public int getValues1(){
		if(playerNumber1 == 1){
			playerOption = 1;
		}
		else if(playerNumber1 == 2){
			playerOption = 2;
		}
		else if(playerNumber1 == 3){
			playerOption = 3;
		}
		else if(playerNumber1 == 4){
			playerOption = 4;
		}
		else if(playerNumber1 == 5){
			playerOption = 5;
		}
		else if(playerNumber1 == 6){
			playerOption = 6;
		}
		return playerOption;
	}
	
	//Stores the image that the player selected
	public int getValues2(){
		if(playerNumber2 == 1){
			playerOption = 1;
		}
		else if(playerNumber2 == 2){
			playerOption = 2;
		}
		else if(playerNumber2 == 3){
			playerOption = 3;
		}
		else if(playerNumber2 == 4){
			playerOption = 4;
		}
		else if(playerNumber2 == 5){
			playerOption = 5;
		}
		else if(playerNumber2 == 6){
			playerOption = 6;
		}
		return playerOption;
	}
	
	public void actionPerformed(ActionEvent event){
	//actions for button
		String command=event.getActionCommand();
			if(command.equals("New Game")){ 
				System.out.println("new game!!");
				//Display option screen
				this.remove(startButton);
				optionMenu();
			}
	}
	public void paint(Graphics g)
	{
		//paints all the backgrounds
		if(backgroundImage != null)
			g.drawImage(backgroundImage, 0, 0,(int)(1280.*sX),(int)(1024.*sY),null);
		//foreground below
		super.paint(g);
		super.paintComponents(g);
	}
	
	public void Resize(JComponent j)
	{
		j.setBounds(scale(j.getBounds()));
	}
}

class ServerThread extends Thread
{
	Menu m;
	public ServerThread(Menu k)
	{
		m=k;
	}
	public void run()
	{
		server s = new server(m.createNetworkNumber, m.columnNum, m.rowNum, m.moveFS, m.timePerMove, m.gameRule);	//creates the board with specified data
		
		boolean timeIsUp = false;
		boolean winner = false;
		boolean tie = false;
		
		timeIsUp = GameEngine.timesOut();
		if(timeIsUp == true){
			s.read();
			s.read();
			s.read();
		}
		else if(winner == true){
			s.read();	//reads OK
			s.read();	//reads Winner
		}
		else if(tie == true){
			s.read();	//reads OK
			s.read();	//reads tie
		}
		s.close();
	}
}

class ClientThread extends Thread
{
	Menu m;
	public ClientThread(Menu k)
	{
		m=k;
	}
	public void run()
	{
		connection r = new connection(m.joinNetworkName, m.joinNetworkNumber);
		boolean timeIsUp = false;
		boolean winner = false;
		boolean tie = false;
		
		timeIsUp = GameEngine.timesOut();
		if(timeIsUp == true){
			r.read();	//reads OK
			r.read();	//reads ILLEGAL
			r.read();	//reads LOSER
		}
		else if(winner == true){
			r.read();	//reads OK
			r.read();	//reads Winner
		}
		else if(tie == true){
			r.read();	//reads OK
			r.read();	//reads tie
		}
		
		r.closeConnection();
	}
}
