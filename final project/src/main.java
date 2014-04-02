import java.awt.Color;
import java.awt.Graphics;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.Random;

import javax.swing.JFrame;

import sun.audio.AudioStream;

public class main extends JFrame {
	public static void main(String args[]) throws IOException
	{
		main m=new main();
		m.setVisible(false);
		m.setSize(1000,1000);
		m.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		m.setVisible(true);
		//** add this into your application code as appropriate
		// Open an input stream  to the audio file.
		InputStream in = new FileInputStream("Final project.wav");
		//System.out.println(in.toString());
		// Create an AudioStream object from the input stream.
		AudioStream as = new AudioStream(in);
		// Use the static class member "player" from class AudioPlayer to play
		// clip.
	//	AudioPlayer.player.start(as);
		Graphics g=m.getGraphics();
	//	AudioData d=as.getData();
		int value=in.read();
		int average=1000;
		int counter=1;
		long start=System.currentTimeMillis();
		Random r=new Random();
		int caverage=0;
		while(counter<as.getLength())
		{
			int x=counter/(value==0?1:value);
			while(x>1000)
			{
				x-=1000;
			}
			if(counter%5==0)
			g.drawRect(x, average, value/50,value);
			caverage+=value;
			if(counter%10==0)
			{
				average=caverage/10;
				caverage=10;
			}
			if(counter%1000==0)
			{
				int other=Math.abs(value);
				while(other>255)
					other/=2;
				int other2=Math.abs(average);
				while(other2>255)
					other2/=2;
				g.setColor(new Color(other,125,other2));
			}
			counter++;
			value=in.read();
			for(int k=0;k<1000000;k++);
		//	System.out.println("counter "+counter);
		}
		long end=System.currentTimeMillis();
	//	System.out.println(start-end);
		// Similarly, to stop the audio.
	//	AudioPlayer.player.stop(as); 
	}
}

