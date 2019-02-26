package View;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Point;
import java.awt.image.BufferedImage;
import java.io.Serializable;
import java.util.ArrayList;

import javax.swing.JPanel;

import Controller.ListenersPCanva;
import Main.Main;
import Modele.Canvas;
import Modele.Converter;
import Modele.Member;
import Modele.Toolbox;

public class PCanva extends JPanel implements Serializable{
	
	private transient BufferedImage drawing;	
	private Boolean toDrawPath;
	private transient ListenersPCanva listenersPCanva;
	private Toolbox toolbox;
	public Converter converter;

	public PCanva(Toolbox toolbox) {
		toDrawPath = false;
		this.toolbox = toolbox;
		//Listeners
		listenersPCanva = new ListenersPCanva(this);
		this.addMouseMotionListener(listenersPCanva);
		this.addMouseListener(listenersPCanva);
	}
	
	public void drawPath(Member drawer, ArrayList<Point> path) {
		if(Main.USER.getCurrentGroup().getCanvas().getDrawing() == null) {
        	drawing = new BufferedImage(Canvas.width, Canvas.height, BufferedImage.TYPE_INT_RGB);  		
    	}else {
    		drawing = Converter.toBufferedImage(Main.USER.getCurrentGroup().getCanvas().getDrawing());
    	}

        Graphics g = drawing.createGraphics();
        System.out.println(drawer.getColor());
		g.setColor(drawer.getColor()); 
		for(Point p : path) { //We iterate over our list of point in the path ArrayList
			 g.fillRect((int)p.getX(),(int) p.getY(), drawer.getToolbox().getSize(), drawer.getToolbox().getSize());
		}
		

        g.dispose();
        // repaint panel with the modified painting
        repaint();
        //Save in Canvas
        Main.USER.getCurrentGroup().getCanvas().setDrawing(Converter.toIcon(drawing));
	}
	
	@Override
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		if(Main.USER.getCurrentGroup().getCanvas().getDrawing() == null) {

		}else {
			g.drawImage(Converter.toBufferedImage(Main.USER.getCurrentGroup().getCanvas().getDrawing()), 0, 0, null);  
		}
		
	}
    public void switchCanvas() {
    	this.repaint();
    	this.listenersPCanva.changeServer(Main.USER.getCurrentGroup().getName());
    }
	
}
