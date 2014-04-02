package main;

import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;

import jssc.SerialPort;
import jssc.SerialPortException;

public class FakeFileSender
{
	static SerialPort serialPort;
	public static void main(String args[])
	{
		run();
	}
	public static void run()
	{
		
		System.out.println("Running other file");
		serialPort = new SerialPort("/dev/slave");
		System.out.println("finished making serial port");
		try
		{
			System.out.println("Opening port");
		    serialPort.openPort();//Open serial port
		    System.out.println("post open");
		    serialPort.setParams(9600, 8, 1, 0);//Set params.
		}catch(SerialPortException ex)
		{
			ex.printStackTrace();
		}
		Scanner s=new Scanner(System.in);
		String str="";
		do
		{
			str=s.nextLine();
			if(str.startsWith("list"))
			{
				try
				{
					list(str.split(" ")[1]);
				}catch(Exception e)
				{
					System.out.println("You need to command correctly");
				}
			}else
			{
				try
				{
					int i=Integer.parseInt(str);
					byte b=(byte)i;
					serialPort.writeByte(b);
				}catch(Exception e)
				{
					write(str);
				}
			}
		}
		while(str!=null&&!str.equals("")&&!str.equals("done"));
		try
		{
			if(serialPort.closePort())
				System.out.println("Closed nicely");
			else
				System.out.println("I did not close");
		} catch (SerialPortException e)
		{
			e.printStackTrace();
		}
		System.out.println("Program ended");
	}
	public static void list(String list)
	{
		final int i=Integer.parseInt(list);
		int nom=i%10;
		if(nom<3)
			nom=3;
		ArrayList<Thread> threads=new ArrayList<Thread>();
		int count=0;
		while(count<nom)
		{
			final Random r=new Random(count);
			Thread d=new Thread()
			{
				
				public void run()
				{
					
					for(int k=0;k<i;k++)
					{
						write(" "+r.nextInt(255));
					}
					write("I AM DONE");
				}
			};
			threads.add(d);
			count++;
		}
		System.out.println("Final count "+count);
		for(Thread d:threads)
		{
			d.start();
		}
	}
	public static void write(String value)
	{
		try
		{
			serialPort.writeString(value);
		}catch(SerialPortException ex)
		{
			ex.printStackTrace();
		}
	}
}
