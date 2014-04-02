import java.util.Arrays;


public class pr2HW5
{
	static int overlaps = 0;
	public static void main(String args[])
	{
		for(int n = 5;n<=10;n++)
		{
			//n=5;
			int[] s = new int[n];
			int[] time = new int[6];
			createSwimmers(0,s,time);

			System.out.println(overlaps);
			overlaps = 0;
		}
	}

	public static void createSwimmers(int numberLeft,int[] swimmers,int[]time)
	{
		if(numberLeft == swimmers.length)
			return;
		for(int k = 0;k<time.length;k++)
		{
			swimmers[numberLeft] = k;

			if(numberLeft==swimmers.length-1)
			{
		//		System.out.println(Arrays.toString(swimmers));
				for(int q = 0; q<swimmers.length;q++)
				{
					time[swimmers[q]]++;
				}
				for(int q = 0; q<time.length; q++)
				{
					if(time[q]>=5)
					{
						overlaps++;
					//	System.out.println("OVERLAPING");
					//	System.out.println(Arrays.toString(swimmers));
					}
					time[q] = 0;
				}
			}
			createSwimmers(numberLeft+1,swimmers,time);
		}
	}
}
