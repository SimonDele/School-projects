package View;

import java.awt.BorderLayout;

import javax.swing.JColorChooser;
import javax.swing.JDialog;

public class JDialogColorChooser extends JDialog{
	public JColorChooser jcolorchooser;
	
	public JDialogColorChooser(JDialog parent){
		super(parent, "Connexion/Inscription", true);
		this.setTitle("Selectionne une couleur");
		this.setSize(500,500);
		this.setLocationRelativeTo(null);
		this.setResizable(false);
		
		jcolorchooser = new JColorChooser();
		
		this.getContentPane().setLayout(new BorderLayout());
		this.getContentPane().add(jcolorchooser, BorderLayout.CENTER);
		this.setVisible(true);
	}
}
