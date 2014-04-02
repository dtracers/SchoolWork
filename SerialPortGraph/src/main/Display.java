package main;

import java.awt.Dimension;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.SwingConstants;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

public class Display extends JPanel
{
	
	Input input=new Input();
	Graph graph=new Graph(input);
	public JComboBox listOfPorts;
	public JButton initialize;
	public JButton start;
	public JButton stop;
	public JButton close;
	public JSlider speed;
	JSlider viewingSpeed;
	public JPanel paintPanel;
	int height=0;
	int width=0;
	boolean initializeEnabled;
	boolean running;
	public JPanel makeTopPanel()
	{
		JPanel p=new JPanel();
	//	p.setPreferredSize(new Dimension(width-50,height-170));
		p.setOpaque(false);
		p.setLayout(new GridBagLayout());
		
		GridBagConstraints gbc = new GridBagConstraints();
		gbc.gridx=0;
		paintPanel=getPaintPanel();
		p.add(paintPanel,gbc);
		
		
		JPanel side=getSidePanel();
		gbc = new GridBagConstraints();
		gbc.gridx=1;
		p.add(side,gbc);
		
		return p;
	}
	public void makePanel(int h,int w)
	{
		height=h;width=w;
		setLayout(new GridBagLayout());
		
		GridBagConstraints gbc = new GridBagConstraints();
		gbc.gridy=0;
		JPanel topPanel=/*getPaintPanel();*/makeTopPanel();
		add(topPanel,gbc);
		
		
		JPanel button=getButtonPanel();
		gbc = new GridBagConstraints();
		gbc.gridy=1;
		add(button,gbc);
	}
	public JPanel getSidePanel()
	{
		JPanel p=new JPanel();
		p.setOpaque(false);
		p.setLayout(new GridBagLayout());
	//	p.setPreferredSize(new Dimension(40,height-40));
		
		int y_value=0;
		GridBagConstraints gridBag;
		
		speed=new JSlider(SwingConstants.VERTICAL,10,1000,50);
		speed.addChangeListener(new ChangeListener()
		{
			@Override
			public void stateChanged(ChangeEvent e)
			{
				graph.WaitTill=speed.getValue();
			}	
		});
		gridBag = new GridBagConstraints();
		gridBag.gridy = ++y_value;
		p.add(speed,gridBag);
		
		viewingSpeed=new JSlider(SwingConstants.VERTICAL,1,50,1);
		viewingSpeed.addChangeListener(new ChangeListener()
		{
			@Override
			public void stateChanged(ChangeEvent e)
			{
				graph.windowSkip=viewingSpeed.getValue();
			}	
		});
		gridBag = new GridBagConstraints();
		gridBag.gridy = ++y_value;
		p.add(viewingSpeed,gridBag);
		
		return p;
	}
	public JPanel getButtonPanel()
	{
		//creates panel
		JPanel p=new JPanel();
		p.setOpaque(false);
		p.setLayout(new GridBagLayout());
		p.setPreferredSize(new Dimension(width,40));
		//sets up constants
		int x_value=0;
		GridBagConstraints gridBag;
		
		//Jlabel
		JLabel label=new JLabel("List of Ports:");
		gridBag = new GridBagConstraints();
		gridBag.gridx = ++x_value;
		p.add(label,gridBag);
		
		//listport
		listOfPorts=new JComboBox(Input.getPortNames());
		listOfPorts.addItemListener(new ItemListener()
		{

			@Override
			public void itemStateChanged(ItemEvent arg0)
			{
				input.setPortName(""+arg0.getItem());
				initializeEnabled=true;
				if(initialize!=null)
					initialize.setEnabled(true);
			}
		
		});
		gridBag = new GridBagConstraints();
		gridBag.gridx = ++x_value;
		p.add(listOfPorts,gridBag);
		
		//Initialize
		initialize=new JButton("Initialize Serial Port");
		initialize.addActionListener(new ActionListener()
		{

			@Override
			public void actionPerformed(ActionEvent arg0)
			{
				input.currentPortName=""+listOfPorts.getSelectedItem();
				input.initialize();
				if(close!=null)
					close.setEnabled(true);
				initialize.setEnabled(false);
				initializeEnabled=false;
			}
			
		});
		gridBag = new GridBagConstraints();
		gridBag.gridx = ++x_value;
		p.add(initialize,gridBag);
		
		//Start
		start=new JButton("Start Reading");
		start.addActionListener(new ActionListener()
		{
			@Override
			public void actionPerformed(ActionEvent arg0)
			{
				input.startReading();
				graph.startGraphing();
				start.setEnabled(false);
				if(stop!=null)
					stop.setEnabled(true);
				running=true;
			}
			
		});
		gridBag = new GridBagConstraints();
		gridBag.gridx = ++x_value;
		p.add(start,gridBag);
		
		//stop
		stop=new JButton("Stop Reading");
		stop.addActionListener(new ActionListener()
		{

			@Override
			public void actionPerformed(ActionEvent arg0)
			{
				input.stopReading();
				graph.stopGraphing();
				stop.setEnabled(false);
				if(start!=null)
					start.setEnabled(true);
				running=true;
			}
			
		});
		gridBag = new GridBagConstraints();
		gridBag.gridx = ++x_value;
		p.add(stop,gridBag);
		
		//stop
		close=new JButton("Close port");
		close.setEnabled(false);
		close.addActionListener(new ActionListener()
		{

			@Override
			public void actionPerformed(ActionEvent arg0)
			{
				input.close();
				close.setEnabled(false);
				if(initialize!=null)
					initialize.setEnabled(true);
			}
			
		});
		gridBag = new GridBagConstraints();
		gridBag.gridx = ++x_value;
		p.add(close,gridBag);
		
		
		return p;
	}

	public JPanel getPaintPanel()
	{
		JPanel panel=graph;
		/*
		{
			public void paint(Graphics g)
			{
				g.setColor(Color.white);
				g.fillRect(0, 0, getWidth(), getHeight());
				g.setColor(Color.black);
				g.drawRect(0, 0, getWidth()-1, getHeight()-1);
			}
		};
		*/
		panel.setOpaque(true);
		panel.setPreferredSize(new Dimension(width-20,height-170));
		return panel;
	}
}
