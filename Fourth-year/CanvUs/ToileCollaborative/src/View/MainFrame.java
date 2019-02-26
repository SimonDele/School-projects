package View;

import java.awt.BorderLayout;

import javax.swing.JFrame;
import javax.swing.JPanel;

import Controller.SaveOnWindowClosed;
import Modele.Canvas;
import Modele.Group;
import Modele.Member;

public class MainFrame extends JFrame{
	private String title;
	//Different Panels :
	public static Menu menu;
	public static PCanva pCanva;
	private PToolBox pToolBox;
	public static Canvas canvas;
	public static Group currentGroup;
	
	public MainFrame(Member user) {
		//Things related to JFrame properties
		title = "CanvUs";
		this.setTitle(title);
		this.setLocationRelativeTo(null);               
	    this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	    this.setSize(500, 500);
	    	    
	    //Content
	    JPanel container = new JPanel(); //will contain all other JPanel
	    container.setLayout(new BorderLayout()); // BorderLayout enables to have 4 Panels define by WEST, CENTER, EAST, NORTH and SOUTH 
    
//	    user.setCurrentCanvas(user.getGroupList().get(0).getCanvas());
	    MainFrame.currentGroup = user.getCurrentGroup();
	    MainFrame.canvas = currentGroup.getCanvas();
	    menu = new Menu(MainFrame.currentGroup, user, canvas);

	    container.add(menu, BorderLayout.WEST); //Say it will be displayed on the left

	    pCanva = new PCanva(user.getToolbox());
	    container.add(pCanva, BorderLayout.CENTER);
	    pToolBox = new PToolBox(user.getToolbox());
	    container.add(pToolBox, BorderLayout.NORTH);
	    
	    this.setContentPane(container); //Finally set the container as the Panel of "MainFrame"
	    
	    this.addWindowListener(new SaveOnWindowClosed(user));
	    
	}
}
