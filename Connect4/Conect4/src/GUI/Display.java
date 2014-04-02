package GUI;

import java.awt.Color;
import java.awt.Graphics;

import javax.swing.JPanel;

public class Display extends JPanel
{
	Graphics myG;
	private Grid gr;
	public Display()
	{
		setGrid(new Grid(800,800,50,50));
		this.addMouseListener(getGrid());
		//this means when a mouse is pressed or released
	}
	/**
	 * in a jPanel everything in this method that uses g gets shown 
	 * by saving the graphics it is possible to paint to the jPanel from everywhere
	 * a jPanel in a JFrame is doubleBuffered by default
	 */
	public void paint(Graphics g)
	{
		myG=g;
		g.setColor(Color.black);
	//	g.fillRect(10, 20, 100, 100);
		gr.draw(g);
	}
	public Grid getGrid()
	{
		return gr;
	}
	public void setGrid(Grid gr)
	{
		this.gr = gr;
	}
}
