package GUI;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import javax.swing.ImageIcon;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;



class Menu extends MyButtonPanel implements ActionListener {
	
	private static final int FRAME_WIDTH = 1000;
	private static final int FRAME_HEIGHT = 1000;
	private static final int FRAME_X_ORIGIN = 0;
	private static final int FRAME_Y_ORIGIN = 0;
    private static final int PLAYER_BUTTON_WIDTH = 220;
    private static final int PLAYER_BUTTON_HEIGHT = 220;
    private static final int BUTTON_HEIGHT = 100;
    private static final int BUTTON_WIDTH = 300;

	
//***** Back button and start button possibly need to be lower **** ///
//I'll fix that	later when I have a bigger screen
    private static final int STARTING_BUTTON_lEFT_RIGHT= 350;
    private static final int STARTING_BUTTON_UP_DOWN = 600;
    private static final int MENU_BUTTON_WIDTH = 600;
    private static final int MENU_BUTTON_HEIGHT = 150;
    private static final int STARTING_HEIGHT = 200;
    
    private Image backgroundImage=null;
    int playerOption = 0;
    int numberOfPlayers = 0;
	
	private MyJButton startButton;
	private MyJButton playerButton;
	private MyJButton computerButton;
	private MyJButton instructionButton;
	private MyJButton highScoreButton;
	private MyJButton girlButton;
	private MyJButton womanButton;
	private MyJButton grandmaButton;
	private MyJButton boyButton;
	private MyJButton menButton;
	private MyJButton grandpaButton;
	private MyJButton backButton;
	private MyJButton playButton;
	private MyJButton nextButton;
	
	private MyJButton dummyButton;
	private MyJButton easyButton;
	private MyJButton moderateButton;
	private MyJButton perfectButton;
	
	private JLabel image;
	private JLabel prompt;

	private JTextField playerName1;
	private JTextField playerName2;	
	
	private JPanel currentPanel;
	Color coolOrange = new Color(242, 161, 33);
	Color connectBlue = new Color(0, 128, 255);
	/*
	public static void main(String[] args){
		menu frame = new menu();
		frame.setVisible(true);
	}
	*/
	
	public Menu(){
// Background image is called "startScreen.png"
		
		
//		setTitle("Connect 4");
//		setSize (FRAME_WIDTH, FRAME_HEIGHT);
//		setLocation (FRAME_X_ORIGIN, FRAME_Y_ORIGIN);    
		 
		//optionMenu();
		//instructions();
		//playerOption1();
		//player1();
		//selectLevel();
		
		changeBackgroundColor();
	//	JPanel contentPane = new JPanel();
	//	contentPane.setLayout(null);
	//	contentPane.setOpaque(true);
		
		startButton = new MyJButton("New Game");
		startButton.setFont(new Font("Courier", Font.BOLD, 50));
		startButton.setBackground(coolOrange);
		startButton.setBounds( STARTING_BUTTON_lEFT_RIGHT, STARTING_BUTTON_UP_DOWN, BUTTON_WIDTH, BUTTON_HEIGHT);
		add(startButton);
		startButton.addActionListener(this);
		this.currentPanel=this;
	//	this.currentPanel=contentPane;
	//	add(contentPane);
		//When you hit the exit button, program will exit
	//	setDefaultCloseOperation(EXIT_ON_CLOSE);
		
		
	}	
//This is probably not neccessary if we're add the image to the background.	
	// Changes the color of the menu background
	private void changeBackgroundColor(){
		//Container contentPane = getContentPane();
		//contentPane.setBackground(Color.GREEN);
		
		Image backgroundImage;
		
		//ImageIcon icon = new ImageIcon("options.png");
		//David said
		//g.drawImage(icon, 0, 0, this);
		backgroundImage = loadImage("options.png");
		
		
		//backgroundImage = icon.getImage();
		//contentPane.add(backgroundImage);
		//setBackgroundImage(backgroundImage);
	}
	
	private Image loadImage (String pad){
        return Toolkit.getDefaultToolkit().getImage(getClass().getResource(pad));
    }
	
//If you do this function, then for some reason, my player1() & player2() won't show ? 	
	/*
	public void paint(Graphics g)
	{
		//background
		Image i=null;
		try
		{
			System.out.println("here");
			i=loadImage("options.png");
			System.out.println("made it");
		}catch(Exception e)
		{
			System.out.println("ERROR");
			e.printStackTrace();
		}
		if(i!=null)
			g.drawImage(i,0,0,1000,1000,this);
		else
		{
			g.setColor(Color.black);
			g.drawRect(0, 0, 1000, 1000);
		}
	//	super.paint(g);
	}
	*/

	public JPanel optionMenu(){
		this.removeAllButtons();
		
		//	this.backgroundImage=this.loadImage("IMAGE HERE!");
		
		//WORKING CORRECT EXAMPLE
		instructionButton = new MyJButton("instructions.png",STARTING_HEIGHT, 115, MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT);
		instructionButton.setAction("instructions", this.getClass(),this);
		addMyButton(instructionButton,false);
		
		//WORKING CORRECT EXAMPLE
		playerButton = new MyJButton("playerVsPlayer.png",STARTING_HEIGHT, 270, MENU_BUTTON_WIDTH, 275);
		playerButton.setAction("playerOption1", this.getClass(),this);
		addMyButton(playerButton,false);
		
		
		//EVEYTHING ELSE NEEDS TO BE CHANGED
		ImageIcon computer = new ImageIcon("playerVsComputer.png");
		computerButton = new MyJButton(computer);
		computerButton.setBounds(STARTING_HEIGHT, 550, MENU_BUTTON_WIDTH, 275);
		computerButton.setBackground(connectBlue);
		computerButton.setFont(new Font("Courier", Font.BOLD, 50));
		computerButton.setForeground(Color.white);
		addMyButton(computerButton,true);
	
		ImageIcon highScore = new ImageIcon("highScores.png");
		highScoreButton = new MyJButton(highScore);
		highScoreButton.setBounds(STARTING_HEIGHT, 830, MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT);
		highScoreButton.setBackground(connectBlue);
		highScoreButton.setFont(new Font("Courier", Font.BOLD, 50));
		highScoreButton.setForeground(Color.white);
		addMyButton(highScoreButton,true);
		
		
		playerButton.addActionListener(this);
		computerButton.addActionListener(this);
		instructionButton.addActionListener(this);
		this.addMouseListener(instructionButton);
		highScoreButton.addActionListener(this);
		System.out.println("BUTTON!!!");
		return null;
		//return contentPane;
	}
	
	public JPanel playerOption1(){
//Background image is called "player1.png" 
		
		JPanel contentPane = new JPanel();
		contentPane.setLayout(null);
	
		//image is called "childGirl.png"
		ImageIcon girl = new ImageIcon("childGirl.png");
		girlButton = new MyJButton(girl);
		//The size of the icons
		girlButton.setBounds(170,210, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
	    contentPane.add(girlButton);

	    //image is called "adultGirl.png"
		ImageIcon woman = new ImageIcon("adultGirl.png");
		womanButton = new MyJButton(woman);
		womanButton.setBounds(390,210, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
		contentPane.add(womanButton);
		
		//image is called "grandmaGirl.png"
		ImageIcon grandma = new ImageIcon("grandmaGirl.png");
		grandmaButton = new MyJButton(grandma);
		grandmaButton.setBounds(610,210, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
		contentPane.add(grandmaButton);
		
		//image is called "childBoy.png"
		ImageIcon boy = new ImageIcon("childBoy.png");
		boyButton = new MyJButton(boy);
		boyButton.setBounds(170,430, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
		contentPane.add(boyButton);
		
		//image is called "adultBoy.png"
		ImageIcon men = new ImageIcon("adultBoy.png");
		menButton = new MyJButton(men);
		menButton.setBounds(390,430, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
		contentPane.add(menButton);
		
		//image is called "grandpaBoy.png"
		ImageIcon grandpa = new ImageIcon("grandpaBoy.png");
		grandpaButton = new MyJButton(grandpa);
		grandpaButton.setBounds(610,430, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
		contentPane.add(grandpaButton);
		
			
		girlButton.addActionListener(this);
		womanButton.addActionListener(this);
		grandmaButton.addActionListener(this);
		boyButton.addActionListener(this);
		menButton.addActionListener(this);
		grandpaButton.addActionListener(this);
		return contentPane;
	}
	
	public JPanel playerOption2(){
		
//Background image is called "player2.png"
		JPanel contentPane = new JPanel();
		contentPane.setLayout(null);
	
		//image is called "childGirl.png"
		ImageIcon girl = new ImageIcon("childGirl.png");
		girlButton = new MyJButton(girl);
		//The size of the icons
		girlButton.setBounds(170,210, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
	    contentPane.add(girlButton);

	  //image is called "adultGirl.png"
		ImageIcon woman = new ImageIcon("adultGirl.png");
		womanButton = new MyJButton(woman);
		womanButton.setBounds(390,210, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
		contentPane.add(womanButton);
		
		//image is called "grandmaGirl.png"
		ImageIcon grandma = new ImageIcon("grandmaGirl.png");
		grandmaButton = new MyJButton(grandma);
		grandmaButton.setBounds(610,210, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
		contentPane.add(grandmaButton);
		
		//image is called "childBoy.png"
		ImageIcon boy = new ImageIcon("childBoy.png");
		boyButton = new MyJButton(boy);
		boyButton.setBounds(170,430, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
		contentPane.add(boyButton);
		
		//image is called "adultBoy.png"
		ImageIcon men = new ImageIcon("adultBoy.png");
		menButton = new MyJButton(men);
		menButton.setBounds(390,430, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
		contentPane.add(menButton);
		
		//image is called "grandpaBoy.png"
		ImageIcon grandpa = new ImageIcon("grandpaBoy.png");
		grandpaButton = new MyJButton(grandpa);
		grandpaButton.setBounds(610,430, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
		contentPane.add(grandpaButton);
			
		girlButton.addActionListener(this);
		womanButton.addActionListener(this);
		grandmaButton.addActionListener(this);
		boyButton.addActionListener(this);
		menButton.addActionListener(this);
		grandpaButton.addActionListener(this);
		return contentPane;
	}
	
	public JPanel instructions(){
		removeAllButtons();//IMPORTANT alsways at tio
		System.out.println("INSTRUCTIONS");
		
		backButton = new MyJButton("back.png",//copied from image icon
				STARTING_BUTTON_lEFT_RIGHT, STARTING_BUTTON_UP_DOWN, BUTTON_WIDTH, BUTTON_HEIGHT);//copied from set bounds
		addMyButton(backButton,false);
		backButton.setAction("optionMenu", this.getClass(), this);//method name of next method
		this.addMouseListener(backButton);//IMPORTANT
		return null;
	}
	
	
	public JPanel highScore(){
// Background image is called "highScoresScreen.png"
		JPanel contentPane = new JPanel();
		contentPane.setLayout(null);
		
		ImageIcon back = new ImageIcon("back.png");
		backButton = new MyJButton(back);
		backButton.setBounds( STARTING_BUTTON_lEFT_RIGHT, STARTING_BUTTON_UP_DOWN, BUTTON_WIDTH, BUTTON_HEIGHT);
		backButton.setFont(new Font("Courier", Font.BOLD, 50));
		contentPane.add(backButton);
		
		backButton.addActionListener(this);
		return contentPane;
	}
	
	public JPanel player1(){
// Background image is called "menu.png"
		JPanel contentPane = new JPanel();
		contentPane.setLayout(null);
		
		//This will decide on depending on which player they chose, it will save it
		if(playerOption == 1){		
			//image is called "childGirl.png"
			image = new JLabel (new ImageIcon("childGirl.png"));
			image.setBounds(390, 200, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
			contentPane.add(image);
		}
		else if (playerOption == 2){
			//image is called "adultGirl.png"
			image = new JLabel (new ImageIcon("adultGirl.png"));
			image.setBounds(390, 200, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
			contentPane.add(image);
		
		}
		else if (playerOption == 3){
			//image is called "grandmaGirl.png"
			image = new JLabel (new ImageIcon("grandmaGirl.png"));
			image.setBounds(390, 200, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
			contentPane.add(image);
		}
		else if (playerOption == 4){	
			//image is called "childBoy.png" 
			image = new JLabel (new ImageIcon("childBoy.png" ));
			image.setBounds(390, 200, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
			contentPane.add(image);
		}
		else if (playerOption == 5){	
			//image is called "adultBoy.png"
			image = new JLabel (new ImageIcon("adultBoy.png"));
			image.setBounds(390, 200, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
			contentPane.add(image);
		}
		else if (playerOption == 6){
			//image is called "grandpaBoy.png"
			image = new JLabel (new ImageIcon("grandpaBoy.png"));
			image.setBounds(390, 200, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
			contentPane.add(image);
		}

		playerName1 = new JTextField();
		playerName1.setColumns(25);
	    playerName1.setBounds(350,480, 300, 50);
	  
	    prompt = new JLabel();
	    prompt.setText("Please enter Player 1's name.\n");
	    prompt.setFont(new Font("Courier", Font.BOLD, 20));
	    prompt.setBounds(330,350, 400, 200);
	    
	    contentPane.add(prompt);
		contentPane.add(playerName1);
	    
	    playerName1.addActionListener(this);
	    setVisible(true);
		
	    //If they choose to play against computer then a play button appears
	   // numberOfPlayers = 1;
	    if(numberOfPlayers == 1){
	    	playButton = new MyJButton("Play");
	 		playButton.setBackground(connectBlue);
	 		playButton.setBounds(STARTING_BUTTON_lEFT_RIGHT, 580, BUTTON_WIDTH, BUTTON_HEIGHT);
	 		playButton.setFont(new Font("Courier", Font.BOLD, 50));
	 		contentPane.add(playButton);
	    	playButton.addActionListener(this);
	    }
	    //If they choose to play against another player then a next button appears
	    else {
	    	nextButton = new MyJButton("Next");
	    	nextButton.setBackground(connectBlue);
	    	nextButton.setBounds(STARTING_BUTTON_lEFT_RIGHT, 580, BUTTON_WIDTH, BUTTON_HEIGHT);
	    	nextButton.setFont(new Font("Courier", Font.BOLD, 50));
	    	contentPane.add(nextButton);
	    	nextButton.addActionListener(this);
	    }
	    return contentPane;
	}

	
	public JPanel player2(){		
// Background image is called "menu.png"	
		JPanel contentPane = new JPanel();
		contentPane.setLayout(null);
		
		//This will decide on depending on which player they chose, it will save it
		if(playerOption == 1){		
			//image is called "childGirl.png"
			image = new JLabel (new ImageIcon("childGirl.png"));
			image.setBounds(390, 200, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
			contentPane.add(image);
		}
		else if (playerOption == 2){
			//image is called "adultGirl.png"
			image = new JLabel (new ImageIcon("adultGirl.png"));
			image.setBounds(390, 200, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
			contentPane.add(image);
		
		}
		else if (playerOption == 3){
			//image is called "grandmaGirl.png"
			image = new JLabel (new ImageIcon("grandmaGirl.png"));
			image.setBounds(390, 200, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
			contentPane.add(image);
		}
		else if (playerOption == 4){	
			//image is called "childBoy.png" 
			image = new JLabel (new ImageIcon("childBoy.png" ));
			image.setBounds(390, 200, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
			contentPane.add(image);
		}
		else if (playerOption == 5){	
			//image is called "adultBoy.png"
			image = new JLabel (new ImageIcon("adultBoy.png"));
			image.setBounds(390, 200, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
			contentPane.add(image);
		}
		else if (playerOption == 6){
			
			image = new JLabel (new ImageIcon("grandpaBoy.png"));
			image.setBounds(390, 200, PLAYER_BUTTON_WIDTH, PLAYER_BUTTON_HEIGHT);
			contentPane.add(image);
		}
		

	    playerName2 = new JTextField();
	    playerName2.setColumns(25);
	    playerName2.setBounds(350,480, 300, 50);
	    prompt = new JLabel();
	    prompt.setText("Please enter Player 2's name.\n");
	    prompt.setFont(new Font("Courier", Font.BOLD, 20));
	    prompt.setBounds(330,350, 400, 200);
	    //prompt.setSize(122,32);
	   
	    playButton = new MyJButton("Play");
		playButton.setBackground(connectBlue);
		playButton.setBounds(STARTING_BUTTON_lEFT_RIGHT, 580, BUTTON_WIDTH, BUTTON_HEIGHT);
		playButton.setFont(new Font("Courier", Font.BOLD, 50));
		
	    contentPane.add(prompt);
	    contentPane.add(playerName2);
	    contentPane.add(playButton);
	    setVisible(true);
	    
	    //Saving the string?
		String nameOfPlayer1 = playerName1.getText();
	    System.out.print(nameOfPlayer1);
		
		playButton.addActionListener(this);
	    playerName2.addActionListener(this);
	    //setSize(300, 170);
	    return contentPane;
	}
	
	
	public JPanel selectLevel(){
// Background image is called "selectLevel.png" 
		
	
		//image is called "dummy.png" 
		ImageIcon dummy = new ImageIcon("dummy.png");
		dummyButton = new MyJButton(dummy);
		//The size of the icons
		dummyButton.setAction("start", MainFrame.thisFrame.getClass(),MainFrame.thisFrame);
		dummyButton.setBounds(190,250, 600, 150);
	    addMyButton(dummyButton,false);

	    //image is called "easy.png"
		ImageIcon easy = new ImageIcon("easy.png");
		easyButton = new MyJButton(easy);
		easyButton.setBounds(190,400, 600, 150);
		easyButton.setAction("start", MainFrame.thisFrame.getClass(),MainFrame.thisFrame);
		addMyButton(easyButton,false);
		
		//image is called "moderate.png"
		ImageIcon moderate = new ImageIcon("moderate.png");
		moderateButton = new MyJButton(moderate);
		moderateButton.setBounds(190,550, 600, 150);
		moderateButton.setAction("start", MainFrame.thisFrame.getClass(),MainFrame.thisFrame);
		addMyButton(moderateButton,false);
		
		//image is called "perfect.png"
		ImageIcon perfect = new ImageIcon("perfect.png");
		perfectButton = new MyJButton(perfect);
		perfectButton.setBounds(190,700, 600, 150);
		perfectButton.setAction("start", MainFrame.thisFrame.getClass(),MainFrame.thisFrame);
		addMyButton(perfectButton,false);
			
		dummyButton.addActionListener(this);
		easyButton.addActionListener(this);
		moderateButton.addActionListener(this);
		perfectButton.addActionListener(this);
		return null;
	}
	
	/**
	 * This will switch the panel by using the command of the method name of the new panel
	 * This is slightly advance and isnt normally used.
	 * a different way to do it is to instead use a switch statement and have each method in there
	 * but it is longer than this and menus can be added at will
	 * @param command
	 */
	public void switchPanel(String command)
	{
		Method m=null;
		try
		{
			m=this.getClass().getMethod(command);
		} catch (SecurityException e)
		{
			e.printStackTrace();
		} catch (NoSuchMethodException e)
		{
			e.printStackTrace();
		}
		JPanel ret=null;
		try
		{
			ret=(JPanel) m.invoke(this, null);
		} catch (IllegalArgumentException e)
		{
			e.printStackTrace();
		} catch (IllegalAccessException e)
		{
			e.printStackTrace();
		} catch (InvocationTargetException e)
		{
			e.printStackTrace();
		}
		if(ret!=null)
		{
			switchPanel(ret);
		}
	}
	/**
	 * This switches the panel
	 * @param ret
	 */
	public void switchPanel(JPanel ret)
	{
		if(ret!=null)
		{
			MainFrame.thisFrame.switchPanel(ret,this);
			this.setCurrentPanel(ret);
		}
	}
	public void actionPerformed(ActionEvent event){
	//actions for button
		if(event.getSource() instanceof MyJButton){	
			MyJButton clickedButton = (MyJButton) event.getSource();
			String buttonText = clickedButton.getText();
			String command=event.getActionCommand();
			if(buttonText.equals("START")){
				
				//blah blah
			}else
			{
			//	switchPanel(command);
			}
			
			JPanel p=null;
			if(buttonText.equals("New Game")){ 
				System.out.println("new game!!");
				//Display option screen
				this.remove(startButton);
				p=optionMenu();
			}
			
			if(buttonText.equals("instructions")){ 
				//Display Instructions Screen with Back Button
				p=instructions();
			}
			
			if(buttonText.equals("player")){ 
			//Display the 2 X 3 player option with text field
				numberOfPlayers = 2;
				p=playerOption1();
				
				//Nested if's because this option will start game
				if(buttonText.equals("girlButton")){
					//call the 6 player function every time?
					playerOption = 1;
					p=player1();
					//Displays Player 2 with text field
					
					
				}
				
				if(buttonText.equals("womanButton")){ 
					playerOption = 2;
					p=player1();
					
				}
				
				if(buttonText.equals("grandmaButton")){ 
					playerOption = 3;
					p=player1();
				}
				
				if(buttonText.equals("boyButton")){ 
					playerOption = 4;
					p=player1();
				}
				
				if(buttonText.equals("menButton")){ 
					playerOption = 5;
					p=player1();
				}
				
				if(buttonText.equals("grandpaButton")){ 
					playerOption = 6;
					p=player1();
				}
			}
			
			if(buttonText.equals("computer")){ 
				//Display the 2 X 3 player option with text field
				numberOfPlayers = 1;
				playerOption2();
				
				if(buttonText.equals("girlButton")){
					//call the 6 player function every time?
					//Displays Player 2 with text field
					playerOption = 1;
					p=player1();
				}
				
				if(buttonText.equals("womanButton")){ 
					playerOption = 2;
					p=player1();
				}
				
				if(buttonText.equals("grandmaButton")){ 
					playerOption = 3;
					p=player1();
				}
				
				if(buttonText.equals("boyButton")){ 
					playerOption = 4;
					p=player1();
				}
				
				if(buttonText.equals("menButton")){ 
					playerOption = 5;
					p=player1();
				}
				
				if(buttonText.equals("grandpaButton")){ 
					playerOption = 6;
					p=player1();
				}
			}
			
			if(buttonText.equals("highScore")){ 
				//Displays HighScore page with back button
				p=highScore();
			}
			
			
			if(buttonText.equals("back")){ 
				//Displays options menu
				p=optionMenu();
			}
			
			//Don't need play button
			if(buttonText.equals("Play")){ 
				//Starts Game
				p=selectLevel();
				if(buttonText.equals("dummy")){ 
					//starts Game

					MainFrame.thisFrame.start();
				}
				else if(buttonText.equals("easy")){ 
					//starts Game
					MainFrame.thisFrame.start();
				}
				else if(buttonText.equals("moderate")){ 
					//starts Game
					MainFrame.thisFrame.start();
				}
				else if(buttonText.equals("hardButton")){ 
					//starts Game
					MainFrame.thisFrame.start();
				}
			}			
			
			if(buttonText.equals("Next")){ 
				//Will go to player 2 screen 
				p=player2();
				//setTitle("Name is " + playerName1.getText());
				//System.out.print("next");
				
			}
			switchPanel(p);
		}
	}
	public JPanel getCurrentPanel()
	{
		return currentPanel;
	}
	public void setCurrentPanel(JPanel currentPanel)
	{
		this.currentPanel = currentPanel;
	}
	public void paint(Graphics g)
	{
		//background here!!!!
		if(backgroundImage!=null)
		{
			g.drawImage(backgroundImage, 0, 0, this);
		}
		//foreground below
		super.paint(g);
	}
}



