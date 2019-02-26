package Modele;

import java.awt.Point;
import java.io.File;
import java.io.IOException;
import java.io.Serializable;
import java.rmi.RemoteException;
import java.util.ArrayList;

import javax.imageio.ImageIO;
import javax.swing.ImageIcon;

import View.MainFrame;
import View.PCanva;
public class Canvas implements Serializable {
//	public String name;
	public ImageIcon drawing;
	public final static Integer width = 500;
	public final static Integer height = 500;
	
	public Canvas() {}
	
	public void setDrawing(ImageIcon image) {
		this.drawing = image;
	}
	public ImageIcon getDrawing() {
		return this.drawing;
	}

    public void save(String name) throws IOException{
        ImageIO.write(Converter.toBufferedImage(drawing), "PNG", new File("drawings/" + name +".png"));
    }
    public void drawPath(Member drawer, ArrayList<Point> path) throws RemoteException {
        // repaint panel with the modified painting
        MainFrame.pCanva.drawPath(drawer, path);
    }
}
