package View;

import java.awt.Color;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JPanel;

import Controller.ListenerSize;
import Controller.ListenersShapes;
import Modele.Toolbox;


public class PToolBox extends JPanel {

	JButton circle;
	JButton sizeSmall,sizeNormal,sizeLarge;

	ListenersShapes listenersToolBox;
	ListenerSize listenerSize;

	public PToolBox(Toolbox toolbox) {
		circle = new JButton(new ImageIcon(this.getClass().getResource("ressources/circle.png")));
		sizeSmall = new JButton("Small");
		sizeNormal = new JButton("Normal");
		sizeLarge = new JButton("Large");

		listenersToolBox = new ListenersShapes(toolbox, circle);
		circle.addActionListener(listenersToolBox);

		listenerSize = new ListenerSize(toolbox,sizeSmall);
		sizeSmall.addActionListener(listenerSize);
		sizeNormal.addActionListener(listenerSize);
		sizeLarge.addActionListener(listenerSize);



		this.add(circle);
		this.add(sizeSmall);
		this.add(sizeNormal);
		this.add(sizeLarge);


		this.setBackground(Color.black);
	}
}

