package main;


public class FunctionSender
{
	Input input;
	int index=0;
	public static void main(String args[])
	{
		FunctionSender f=new FunctionSender();
	}
	public FunctionSender()
	{
		input=new Input();
		input.setPortName("/dev/slave");
		input.initialize();
		startSending();
	}
	public void startSending()
	{
		Thread d=new Thread()
		{
			public void run()
			{
				while(true)
				{
					byte[] line =new byte[2];
					line[0]=send1();
					line[1]=send2();
					input.writeArray(line);
				}
			}
		};
		d.start();
	}
	public byte send1()
	{
		double range=index;
		range/=10.;
		double d=Math.sin(range);
		d*=254./2.;
		d+=255./2.;
//		System.out.println(d);
		index++;
		int i=(int)d;
//		System.out.println("AS INT "+i);
		byte b=(byte)i;
//		System.out.println("AS Byte"+i);
		return (byte)b;
	}
	public byte send2()
	{
		double range=index;
		range/=20.;
		double d=Math.cos(range);
		d*=254./2.;
		d+=255./2.;
//		System.out.println(d);
		index++;
		int i=(int)d;
//		System.out.println("AS INT "+i);
		byte b=(byte)i;
//		System.out.println("AS Byte"+i);
		return (byte)b;
	}
}
