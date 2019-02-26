package View;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.BorderFactory;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

import Controller.ListenerSignIn_Up;
import Modele.Member;

public class SignIn_Up extends JDialog {
	
	JPanel content, title, body;
	JLabel labpseudo;
	JLabel labpassword;
	JTextField pseudo;
	JTextField password;
	JButton signIn, signUp, submit;
	JButton buttonColor;
	JPanel pPseudo;
	JPanel pPassword;
	JDialog signIn_Up;
	private Member member;
	public Color color;
	JDialogColorChooser jDialogColorChooser;
	public SignIn_Up(JFrame parent) {
		super(parent, "Sign In or Sign Up", true);
		this.setSize(500,500);
		this.setLocationRelativeTo(null);
		this.setResizable(false);
		//this.setDefaultCloseOperation(JDialog.DO_NOTHING_ON_CLOSE);
		
		signIn_Up = this;
		
		content = new JPanel();
		content.setLayout(new BoxLayout(content, BoxLayout.PAGE_AXIS));
		content.setAlignmentX(LEFT_ALIGNMENT);
		content.setBorder(BorderFactory.createEmptyBorder(10,10,10,10));
		
		//Pseudo
		labpseudo = new JLabel("Pseudo : ");
		pseudo = new JTextField();
		pseudo.setMaximumSize(new Dimension(100,25));
		pPseudo = new JPanel();
		pPseudo.setLayout(new BoxLayout(pPseudo, BoxLayout.LINE_AXIS));
		pPseudo.add(labpseudo);
		pPseudo.add(pseudo);
		pPseudo.setAlignmentX(LEFT_ALIGNMENT);
		//Password
		labpassword = new JLabel("Mot de passe :");
		password = new JTextField();
		password.setMaximumSize(new Dimension(100,25));
		pPassword = new JPanel();
		pPassword.setLayout(new BoxLayout(pPassword, BoxLayout.LINE_AXIS));
		pPassword.add(labpassword);
		pPassword.add(password);
		pPassword.setAlignmentX(LEFT_ALIGNMENT);
		
		//Pick Color
		buttonColor = new JButton("Couleur");
		buttonColor.setVisible(false);
		buttonColor.addActionListener(new ColorActionListener(this));
		
		signIn = new JButton("Connexion");
		signIn.setEnabled(false); // Sign In by default
		signIn.addActionListener(new ActionListener() { //Change to Sign In 
			@Override
			public void actionPerformed(ActionEvent arg0) {
				signIn.setEnabled(false);
				signUp.setEnabled(true); 
				buttonColor.setVisible(false);// No need to pick up a color to Sign In
			}
		});
		signUp = new JButton("Inscription");
		signUp.addActionListener(new ActionListener() { // Change to Sign Up
			@Override
			public void actionPerformed(ActionEvent arg0) {
				signIn.setEnabled(true);
				signUp.setEnabled(false);
				buttonColor.setVisible(true); // Must pick up a color to Sign Up

			}
		});
		
		submit = new JButton("Valider");
		submit.addActionListener(new ListenerSignIn_Up(pseudo, password, signUp,this, this.jDialogColorChooser));
		title = new JPanel();
		title.setLayout(new BoxLayout(title, BoxLayout.LINE_AXIS));
		title.setAlignmentX(CENTER_ALIGNMENT);
		title.add(signIn);
		title.add(signUp);
		
		
		body = new JPanel();
		body.setLayout(new BoxLayout(body,BoxLayout.PAGE_AXIS));
		body.add(pPseudo);
		body.add(pPassword);
		body.add(buttonColor);
		
		content.add(title);
		content.add(body);
		content.add(submit);
		
		//Add everything in the JDialog
		this.getContentPane().add(content);
		this.setVisible(true);
	}
	public Color getColor() {
		return color; 
	}
	public Member getMember() {
		return this.member;
	}
	public void setMember(Member member) {
		this.member = member;		
	}
	public class ColorActionListener implements ActionListener{
		
		SignIn_Up signIn_Up;
		
		public ColorActionListener(SignIn_Up signIn_Up) {
			this.signIn_Up = signIn_Up;
		}
		@Override
		public void actionPerformed(ActionEvent arg0) {
			jDialogColorChooser = new JDialogColorChooser(signIn_Up);
			this.signIn_Up.color = jDialogColorChooser.jcolorchooser.getColor();
			System.out.println(this.signIn_Up.color);
			
		}
		
	}
}
