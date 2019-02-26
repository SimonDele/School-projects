package Controller;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import Modele.Toolbox;

public class ListenersShapes implements ActionListener {
	JButton circle;
	Toolbox toolbox;
	public ListenersShapes(Toolbox toolbox, JButton circle) {
		this.circle = circle;
		this.toolbox = toolbox;
	}
	@Override
	public void actionPerformed(ActionEvent e) {
		if(circle == e.getSource()) {
			toolbox.setShapeSelected("CIRCLE");
		}
	}
	
}
