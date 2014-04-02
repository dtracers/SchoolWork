package GUI;
/*This file is called by the Game Engine and starts the game as well as displays the menu()
 * 
 */

import gameplay.GameEngine;

import java.awt.DisplayMode;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.UIManager;

public class MainFrame extends JFrame implements ActionListener
{
	boolean started = true;
	public static MainFrame thisFrame;
	private Display d;
	Menu m;
	Rectangle bounds;
	Rectangle fullBounds;
	double scaleX,scaleY;
	boolean updated;
	boolean fullScreen=false;
	public GameEngine i;
	/**
	 * Creates the frame.
	 */
	public MainFrame()
	{
		try
		{
			UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
		} catch (Exception e)
		{
			e.printStackTrace();
		}

		thisFrame=this;
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		JMenuBar menuBar = new JMenuBar();
		setJMenuBar(menuBar);
		
		JMenu mnFile = new JMenu("File");
		menuBar.add(mnFile);
		
		JMenuItem mntmSave = new JMenuItem("New Game");
		mntmSave.addActionListener(this);

		mnFile.add(mntmSave);
		mnFile.addSeparator();

		JMenuItem mntmQuit = new JMenuItem("Quit");
		mntmQuit.addActionListener(this);
		mnFile.add(mntmQuit);
		
		JMenu mnDebug = new JMenu("Debug");
		menuBar.add(mnDebug);
		
		JMenuItem mntmAI = new JMenuItem("AI MOVE");
		mntmAI.addActionListener(this);
		mnDebug.add(mntmAI);
		
		JMenuItem mntmUndo = new JMenuItem("UNDO MOVE");
		mntmUndo.addActionListener(this);
		mnDebug.add(mntmUndo);
		
		init();
		if(started)
		{
			addMenu();
		}else
		{
			addMenu();
		}
	}

	public void init()
	{
		bounds=new Rectangle(0,0,1280,1024);
		if(fullScreen)
		{
		}else
		{
			setSize(1100,900);
			this.setResizable(false);
		}
		fullBounds=new Rectangle(this.getBounds());
		System.out.println("fullbounds are: "+fullBounds);
		System.out.println("reg bounds are: "+bounds);
		scaleX=fullBounds.getWidth()/bounds.getWidth();
		scaleY=fullBounds.getHeight()/bounds.getHeight();
		System.out.println("scae x "+scaleX+" scae y "+scaleY);
	}
	/**
	 * If a menu item is clicked and it has this class as an actionListener
	 * then this method is called
	 * command for a JMenuItem is the name of the JMenuItem
	 */
	@Override
	public void actionPerformed(ActionEvent arg0)
	{
		String command=arg0.getActionCommand();
		if(command.equals("AI MOVE"))
		{
			GameEngine.makeAiMove();
		}
		if(command.equals("UNDO MOVE"))
		{
			GameEngine.undoMove();
		}
		
		if(command.equals("New Game"))
		{
			addMenu();
		}

		if(command.equalsIgnoreCase("Quit"))
		{
			System.exit(0);
		}

		System.out.println("ACTIONED");
	}


	public void start()
	{
		System.out.println("starting game");
		int player1 = 0;
		int player2 = 0;
		int numberOfPlayers = 0;
		String name1 = "";
		String name2 = "";
		
		if(m != null){
			//stores the values for the players image and name
			player1 = m.getValues1();
			player2 = m.getValues2();
			name1 = m.getName1();
			name2 = m.getName2();
			numberOfPlayers = m.setPlayerValues();
			
			remove(m);
		}
		if(getDisplay() != null){
			remove(getDisplay());
		}else
		{	//Display the game board
			setDisplay(new Display(scaleX,scaleY));
			this.addMouseListener(getDisplay().getGrid());
			this.addKeyListener(getDisplay().getGrid());
		}
		getDisplay().setNumberOfPlayers(numberOfPlayers);
		//Playing against computer, so only set the first players information
		if(numberOfPlayers == 1){
			getDisplay().setValues1(player1);
			getDisplay().setName1(name1);
		}
		//Sets the two local players information
		else if (numberOfPlayers == 2){
			getDisplay().setValues1(player1);
			getDisplay().setName1(name1);
			getDisplay().setValues2(player2);
			getDisplay().setName2(name2);
		}
		//Sets the client server information
		else if (numberOfPlayers == 3){
			getDisplay().setName1(name1);
			getDisplay().setName2(name2);
		}
		add(getDisplay());
		i.RealStart();
		this.validate();
	}

	public void addMenu()
	{
		if(getDisplay()!=null)
		{
			remove(getDisplay());
		}
		if(m!=null)
		{
			remove(m);
		}
		if(started)
		{
			m = new Menu(scaleX,scaleY,this.getWidth(),this.getHeight());
			add(m);
			started=false;
			this.validate();
		}
	}
	
	public void switchPanel(JPanel ret,Menu m)
	{
		if(ret!=null)
		{
			System.out.println("Switching panel");
			this.setContentPane(ret);
		}
	}

	//Updates the display
	public void updated()
	{
		updated=true;
		if(getDisplay()!=null)
		{
			getDisplay().updated();
		}
	}

	public void setGame(GameEngine gameEngine) {
		// TODO Auto-generated method stub
		i=gameEngine;
	}

	public Display getDisplay() {
		return d;
	}

	public void setDisplay(Display d) {
		this.d = d;
	}
}
