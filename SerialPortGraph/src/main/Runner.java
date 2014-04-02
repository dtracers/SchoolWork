package main;

import java.io.File;
import java.util.ArrayList;
import java.util.TreeSet;

import javax.swing.JFrame;

import jssc.SerialPortList;

public class Runner
{
	public static void main(String[] args) {
	//	checkFiles();
	//	checkFiles();
		Thread one=new Thread()
		{
			public void run()
			{
				runOutput();
			}
		};
		Thread two=new Thread()
		{
			public void run()
			{
				runInput();
			}
		};
	//	one.start();
		two.start();
    }

	public static Display display=new Display();
	
	public static void runInput()
	{
		System.out.println("I am running here");
        String[] portNames = SerialPortList.getPortNames();
        System.out.println("number of ports "+portNames.length);
        for(int i = 0; i < portNames.length; i++){
            System.out.println(portNames[i]);
        }
        
        JFrame f=new JFrame();
        f.setVisible(false);
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        f.setSize(900,800);
        display.makePanel(900,800);
        f.add(display);
        f.setVisible(true);
	}
	public static void runOutput()
	{
		FakeFileSender.run();
	}
	
	public static void checkFiles()
	{
		String[] returnArray = new String[]{};
        File dir = new File("/dev");
        if(dir.exists() && dir.isDirectory()){
            File[] files = dir.listFiles();
            if(files.length > 0){
                TreeSet<String> portsTree = new TreeSet<String>();
                ArrayList<String> portsList = new ArrayList<String>();
                for(File file : files){
                	System.out.println(""+file.getAbsolutePath());
                	System.out.println("Is this file a file "+file.isFile());
                	System.out.println("Is this file a directory "+file.isDirectory());
                    if(!file.isDirectory() && !file.isFile() && file.getName().matches("tty.(serial.*|usbserial.*)")){
                        portsTree.add("/dev/" + file.getName());
                    }
                }
                for(String portName : portsTree){
                    portsList.add(portName);
                }
                portsList.add("Com3");
                returnArray = portsList.toArray(returnArray);
            }
        }
	}

	public static void checkForMatching(String test)
	{
		System.out.println(test+"= "+test.matches("tty.(serial.*|usbserial.*)"));
	}
	/*
	 * SerialPort serialPort = new SerialPort("master");
	        try {
	            System.out.println("Port opened: " + serialPort.openPort());
	            System.out.println("Params setted: " + serialPort.setParams(9600, 8, 1, 0));
	            System.out.println("\"Hello World!!!\" successfully writen to port: " + serialPort.writeBytes("Hello World!!!".getBytes()));
	            System.out.println("Port closed: " + serialPort.closePort());
	        }
	        catch (SerialPortException ex){
	            System.out.println(ex);
	        }
	 */
}
