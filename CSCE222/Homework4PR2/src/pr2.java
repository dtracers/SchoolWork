import java.util.HashSet;


public class pr2
{
	public static void main(String args[])
	{
		findAddition();
		shortCut();
		findValues();
	}
	public static void shortCut()
	{
		for(int n = 2;n<7;n++)
		{
			double value = 0;
			for(int k=1;k<=8;k++)
			{
				value+= k*Math.pow(9, n-2);
			}
		//	value-=p(8,n-1);
			System.out.println(value+":"+p(9,n-1));
		}
	}

	public static void findAddition()
	{
		int line = 16;
		int n = 11;
		int counter =0;
		for(int k=1;k<n;k++)
		{
			for(int q=1;q<n;q++)
			{
				for(int r=1;r<n;r++)
				{
					if(q!=k&&q!=r&&k!=r)
					{
						if(k+q+r>line)
						{
							counter++;
							System.out.println(k+" "+q+" "+r+" "+(k+q+r));
						}
					}
				}
			}
		}
		System.out.println(counter);
	}

	public static double p(int n,int r)
	{
	//	System.out.println(n+" " +r);
		return factorial(n)/factorial(n-r);
	}

	public static double c(int n,int r)
	{
		return factorial(n)/(factorial(r)*factorial(n-r));
	}

	public static double factorial(int fact)
	{
		if(fact <=1)
			return 1;
		else
			return fact*factorial(fact-1);
	}

	public static void findValues()
	{

	//	boolean only = false;//false is last<first
		for(int i=2; i<10;i++)
		{
			int n = i;
			int counter = 0;
			int counter2 = 0;
			System.out.println("NUMBER OF "+ (int) Math.pow(10,n-1)+" to "+Math.pow(10,n));
			for(int k = (int) Math.pow(10,n-1); k < Math.pow(10,n); k++)
			{
				String str = ""+k;
				boolean valid = true;
				int start=0,last=0;
				HashSet<Integer> set = new HashSet<Integer>();
				for(int q = 0;q<str.length();q++)
				{
					int value = Integer.parseInt(str.substring(q,q+1));
					set.add(value);
					if(value == 0)
					{
						valid = false;
						break;
					}
					if(q == 0)
					{
						start = value;
					}
					if(q == str.length()-1)
					{
						last = value;
					}
				}
				if((set.size()!=str.length())&&start<last)
				{
					counter2++;
				}

				if(!valid||(set.size()!=str.length()))
				{
					continue;
				}
				if(start<last)
				{
					counter++;
				//	System.out.println(k);
				}
			}
			System.out.println("NUMBER OF "+counter+"Not number of "+counter2);
		}
	}
}
