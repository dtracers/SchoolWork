package main;

import java.util.ArrayList;
import java.util.Queue;

import jssc.SerialPort;
import jssc.SerialPortException;
import jssc.SerialPortList;


/**
 * This sets up to and receives input from the serial port.
 * It will continually set up snapShots which will then add to an array with a thread.
 * Then there will be a queue that will read from the array.
 * This extra step provides a secondary buffer to the first buffer
 * This Queue will then be read at certain times so that the data is then saved correctly
 * initialize
 * @author gigemjt
 *
 */
public class Input
{
	public static final int SERIAL_PORT=1;
	snapShot[] buffer1;
	Queue<snapShot> buffer2;
	ArrayList<Byte> byteQueue;
	static String[] portNames = SerialPortList.getPortNames();
	String currentPortName;
	SerialPort serialPort;
	boolean read;
	public void initialize()
	{
	//	currentPortName="/dev/master";
		System.out.println("Current port name is "+currentPortName);
		serialPort = new SerialPort(currentPortName);
		byteQueue=new ArrayList<Byte>();
		try
		{
			System.out.println("Opening port");
		    serialPort.openPort();//Open serial port
		    System.out.println("port open");
		    serialPort.setParams(9600, 8, 1, 0);//Set params.
		}catch(SerialPortException ex)
		{
			ex.printStackTrace();
		}
	}
	public void writeArray(byte[] array)
	{
		byte array2[]=new byte[array.length+6];
		for(byte k=0;k<=5;k++)
		{
			array2[k]=(byte) (k+1);
		}
		for(int k=0;k<array.length;k++)
		{
			array2[k+6]=array[k];
		}
		try
		{
		//	System.out.println("Output is "+Arrays.toString(array2));
			serialPort.writeBytes(array2);
		} catch (SerialPortException e)
		{
			e.printStackTrace();
		}
	}
	public synchronized void adding(byte[] buffer)
	{
		if(buffer!=null)
			for(byte b:buffer)
			{
				byteQueue.add(b);
			}
	}
	public void startReading()
	{
		if(!serialPort.isOpened())
		{
			return;
		}
		read=true;
		//this is how you read a serial port
		Thread d=new Thread()
		{
			public void run()
			{
				while(read)
				{
		            try
					{
		           // 	System.out.println("Ready to read");
		           // 	System.out.println("Bytes to be read "+serialPort.getInputBufferBytesCount());
		            	int minByteRead=512;
		            	int numbytes=Math.min(minByteRead, serialPort.getInputBufferBytesCount());
						byte[] buffer = serialPort.readBytes(numbytes);
						if(buffer==null||numbytes==0)
						{
				//			System.out.println("buffer is empty");
						}else
						{
					//		System.out.println(Arrays.toString(buffer));
						}
						adding(buffer);
						if(byteQueue.size()>15000)
						{
							while(byteQueue.size()>1000)
							{
								//just wait here
								try
								{
									Thread.sleep(50);
								} catch (InterruptedException e)
								{
									e.printStackTrace();
								}
							}
						}
					} catch (SerialPortException e)
					{
						e.printStackTrace();
					}//Read 10 bytes from serial port
		            try
					{
						Thread.sleep(20);
					} catch (InterruptedException e)
					{
						e.printStackTrace();
					}
				}
			}
		};
		d.start();
	}
	public void stopReading()
	{
		read=false;
	//	serialPort.closePort();//Close serial port
	}
	public void setPortName(String st)
	{
		currentPortName=st;
	}
	public static String[] getPortNames()
	{
		if(portNames.length==0)
			return new String[]{"/com3"};
		
		int off=3;
		String[] ret=new String[portNames.length+off];
		for(int k=off;k<ret.length;k++)
		{
			ret[k]=portNames[k-off];
		}
		ret[0]="/Com3";
		//ret[0]="/dev/master";
		ret[1]="/dev/slave";
		//ret[2]="/Com3";
		return ret;
	}
	public void close()
	{
		read=false;
		System.out.println("trying to close port");
		boolean closed=false;
		try
		{
			closed=serialPort.closePort();
		} catch (SerialPortException e)
		{
			e.printStackTrace();
		}
		if(closed)
		System.out.println("port closed successfully");
		else
			System.out.println("port closing failed");
	}
	public synchronized byte remove()
	{
		if(byteQueue.size()<=0)
			return -1;
		byte b=byteQueue.remove(0);
		return b;
	}
}
/**
 * This just contains the snapShot of the serial port so that it will set up the graph correctly
 * @author gigemjt
 *
 */
class snapShot
{
	
}

