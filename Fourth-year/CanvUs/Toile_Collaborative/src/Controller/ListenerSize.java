package Controller;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;

import Modele.Toolbox;

public class ListenerSize implements ActionListener {
	JButton size;
	Toolbox toolbox;

	public ListenerSize(Toolbox toolbox, JButton size) {
		this.size = size;
		this.toolbox = toolbox;
	}
	@Override
	public void actionPerformed(ActionEvent e) {
		if(e.getActionCommand().equals("Small")) {
			toolbox.setSize(3);
		}
		if(e.getActionCommand().equals("Normal")) {
			toolbox.setSize(10);
		}
		if(e.getActionCommand().equals("Large")) {
			toolbox.setSize(20);
		}
	}

}
