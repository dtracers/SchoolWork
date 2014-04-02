package GUI;

import gameplay.GameEngine;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
 
public class MainFrame extends JFrame implements ActionListener
{
	boolean started=false;
	static MainFrame thisFrame;
	Display d;
	Menu m;
	/**
	 * Create the frame.
	 */
	public MainFrame()
	{
		thisFrame=this;
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 1000, 1000);
		
		JMenuBar menuBar = new JMenuBar();
		setJMenuBar(menuBar);
		
		JMenu mnFile = new JMenu("File");
		menuBar.add(mnFile);
		
		JMenuItem mntmSave = new JMenuItem("Save");
		mntmSave.addActionListener(this);
		//adding this as an action listener means that if an action happens
		//this will handle it
		mnFile.add(mntmSave);
		
		JMenuItem mntmLoad = new JMenuItem("Load");
		
		mntmLoad.addActionListener(this);
		mnFile.add(mntmLoad);
		
		JMenuItem mntmQuit = new JMenuItem("Quit");
		mntmQuit.addActionListener(this);
		mnFile.add(mntmQuit);
		
		JMenu mnOptions = new JMenu("Options");
		menuBar.add(mnOptions);	
		
		JMenu mnDebug = new JMenu("Debug");
		menuBar.add(mnDebug);
		
		JMenuItem mntmAI = new JMenuItem("AI MOVE");
		mntmAI.addActionListener(this);
		mnDebug.add(mntmAI);
		
		d=new Display();
		if(started)
		{
			this.addMouseListener(d.getGrid());
			add(d);
		}else
		{
			m=new Menu();
		//	this.addMouseListener(m);
			add(m);
		}
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
		System.out.println("ACTIONED");
		System.out.println(arg0.getActionCommand());
	}

	public void start()
	{
		if(!started)
		{
			this.addMouseListener(d.getGrid());
			add(d);
			started=true;
		}
	}
	
	public void switchPanel(JPanel ret,Menu m)
	{
		if(ret!=null)
		{
			System.out.println("Switching panel");
//			if(m.getCurrentPanel()!=null)
//			this.remove(m.getCurrentPanel());
//			this.add(ret);
			this.setContentPane(ret);
	//		m.setCurrentPanel(ret);
		}
	}
}
