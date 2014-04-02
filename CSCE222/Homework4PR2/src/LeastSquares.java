
//LeastSquares.java


//Below is the syntax highlighted version of LeastSquares.java from ¤3.6 Case Study: Purple America.


/*************************************************************************
 *  Compilation:  javac LeastSquares.java
 *  Execution:    java LeastSquares
 *  Dependencies: Draw.java DrawListener.java
 *
 *  Plots the points that the user clicks, and plots the least squares
 *  line through them.
 *
 *************************************************************************/

import java.awt.Color;
import java.awt.Graphics;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.JFrame;

public class LeastSquares implements MouseListener {
    private int N = 0;
    private double sumx  = 0.0;                     // sum { x[i],      i = 1..n
    private double sumy  = 0.0;                     // sum { y[i],      i = 1..n
    private double sumx2 = 0.0;                     // sum { x[i]*x[i], i = 1..n
    private double sumy2 = 0.0;                     // sum { y[i]*y[i], i = 1..n
    private double sumxy = 0.0;                     // sum { x[i]*y[i], i = 1..n
    private double[] x = new double[10000];
    private double[] y = new double[10000];

    Graphics myGraphics;
    JFrame draw = new JFrame()
    {
    	public void paint(Graphics g)
    	{
    		myGraphics = g;
    	}
    };

    public LeastSquares() {

        draw.setVisible(false);
        draw.addMouseListener(this);
        draw.setSize(800,800);
        draw.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        draw.setVisible(true);
    }

    public void mousePressed(int x0, int y0) {
        x[N] = x0;
        y[N] = y0;
        sumx  += x[N];
        sumy  += y[N];
        sumx2 += x[N]*x[N];
        sumy2 += y[N]*y[N];
        sumxy += x[N]*y[N];
        N++;

        myGraphics.setColor(Color.white);
        myGraphics.fillRect(0,0,800,800);

        // draw the least squares line
        myGraphics.setColor(Color.BLACK);
        double a = (N*sumxy - sumx*sumy) / (N*sumx2 - sumx*sumx);
        double b = (sumy - a*sumx) / N;
        myGraphics.drawLine(0, (int)b, 1, (int)(a + b));

        // draw the points
        for (int i = 0; i < N; i++) {
        	myGraphics.setColor(Color.BLUE);
        	myGraphics.fillOval((int)x[i], (int)y[i], 1,1);
        	myGraphics.setColor(Color.GRAY);
        	myGraphics.drawLine((int)x[i],(int) y[i], (int)x[i], (int)(a*x[i] + b));
        }

        draw.show();
    }


  //  public void keyTyped(char c) { draw.save("leastsquares" + c + ".png"); }
   // public void mouseDragged(double x, double y) { }
   // public void mouseReleased(double x, double y) { }


    // test client
    public static void main(String[] args) {
        LeastSquares ls = new LeastSquares();
    }



	@Override
	public void mouseClicked(MouseEvent paramMouseEvent) {
	}

	@Override
	public void mousePressed(MouseEvent paramMouseEvent)
	{
		mousePressed(paramMouseEvent.getX(),paramMouseEvent.getX());
	}

	@Override
	public void mouseReleased(MouseEvent paramMouseEvent) {
	}

	@Override
	public void mouseEntered(MouseEvent paramMouseEvent) {
	}

	@Override
	public void mouseExited(MouseEvent paramMouseEvent) {
	}


}